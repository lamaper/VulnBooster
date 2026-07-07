"""
基于特征切片 (VRR-SRR) 的漏洞二分类模型微调脚本
核心特性：
1. 支持动态权重调度策略 (λ * FocalLoss + μ * LabelSmoothingCE)
2. 兼容图谱特征抽取与数据增强的迭代闭环架构
3. 全链路 I/O 进度监控与内存态对齐
"""
import os
os.environ["HF_ENDPOINT"] = "https://hf-mirror.com"
import json
import torch
import torch.nn as nn
import torch.nn.functional as F
import numpy as np
from collections import Counter
from torch.utils.data import Dataset
from sklearn.metrics import (
    accuracy_score, 
    precision_recall_fscore_support, 
    roc_curve,
    balanced_accuracy_score,
    matthews_corrcoef
)
from transformers import (
    AutoTokenizer,
    AutoModelForSequenceClassification,
    Trainer,
    TrainingArguments,
    DataCollatorWithPadding
)
from tqdm import tqdm

# ============================================================
# 全局运行态与路径配置中心
# ============================================================
# 可选值: "smoke" 或 "full"
RUN_MODE = "smoke" 
# 当前迭代轮次，控制漏报数据输出的目录级别
CURRENT_ITERATION = 2 

MODEL_NAME = "microsoft/codebert-base"
BATCH_SIZE = 16
LEARNING_RATE = 2e-5
PREDICTION_THRESHOLD = 0.5

if RUN_MODE == "smoke":
    EPOCHS = 2  # 测试环境仅需验证流程连通性
    # TRAIN_DATA_PATH = "../slice/smoke/refined_train.jsonl"
    TRAIN_DATA_PATH = f"../slice/smoke/iteration{CURRENT_ITERATION-1}/refined_train.jsonl"
    VALID_DATA_PATH = "../slice/smoke/refined_valid.jsonl"
    TEST_DATA_PATH  = "../slice/smoke/refined_test.jsonl"
    MODEL_SAVE_DIR  = "../smoke/codebert"
    FN_OUTPUT_PATH  = f"../slice/smoke/iteration{CURRENT_ITERATION}/valvul_nofind.jsonl"
    PREDICT_OUTPUT_PATH = f"../slice/smoke/iteration{CURRENT_ITERATION}/val_predictions.jsonl"
else: 
    EPOCHS = 10 # 全量数据环境需要充足的迭代以保证模型收敛
    # 如果是第 2 次及以上迭代，训练集路径应根据 merge_dataset.py 的输出调整
    TRAIN_DATA_PATH = "../slice/deepseek/refined_train.jsonl"
    # TRAIN_DATA_PATH = f"../slice/deepseek/iteration{CURRENT_ITERATION-1}/refined_train.jsonl"
    VALID_DATA_PATH = "../slice/deepseek/refined_valid.jsonl"
    TEST_DATA_PATH  = "../slice/deepseek/refined_test.jsonl"
    MODEL_SAVE_DIR  = "../codebert"
    FN_OUTPUT_PATH  = f"../slice/deepseek/iteration{CURRENT_ITERATION}/valvul_nofind.jsonl"
    PREDICT_OUTPUT_PATH = f"../slice/deepseek/iteration{CURRENT_ITERATION}/val_predictions.jsonl"

# ============================================================
# 损失函数模块：动态线性组合损失
# ============================================================
class LinearCombinationLoss(nn.Module):
    def __init__(self, focal_alpha=0.85, focal_gamma=2.0, ls_epsilon=0.1, lambda_fl=1.0, lambda_ls=1.0, reduction='mean'):
        super().__init__()
        # 正类基础权重为 0.85，负类为 0.15
        self.focal_alpha = focal_alpha
        self.focal_gamma = focal_gamma
        # 标签平滑系数设定为 0.1
        self.ls_epsilon = ls_epsilon
        # 动态权重系数
        self.lambda_fl = lambda_fl
        self.lambda_ls = lambda_ls
        self.reduction = reduction

    def forward(self, inputs, targets):
        # 1. 计算基础交叉熵损失
        ce_loss = F.cross_entropy(inputs, targets, reduction='none')
        pt = torch.exp(-ce_loss)
        
        # 2. 计算动态 alpha_t: 正类(1)赋 alpha=0.85, 负类(0)赋 1-alpha=0.15
        alpha_t = torch.where(targets == 1, self.focal_alpha, 1.0 - self.focal_alpha)
        
        # 3. Focal Loss 公式 
        focal_loss = alpha_t * (1 - pt) ** self.focal_gamma * ce_loss
        
        # 4. Label Smoothing Loss 公式 
        smooth_loss = -F.log_softmax(inputs, dim=-1).mean(dim=-1)
        ls_ce_loss = (1.0 - self.ls_epsilon) * ce_loss + self.ls_epsilon * smooth_loss

        # 5. 动态加权复合 
        combined_loss = self.lambda_fl * focal_loss + self.lambda_ls * ls_ce_loss
        
        if self.reduction == 'mean':
            return combined_loss.mean()
        elif self.reduction == 'sum':
            return combined_loss.sum()
        return combined_loss

# ============================================================
# 模型训练器重载模块
# ============================================================
class CustomTrainer(Trainer):
    def compute_loss(self, model, inputs, return_outputs=False, **kwargs):
        labels = inputs.get("labels")
        outputs = model(**inputs)
        logits = outputs.get("logits")
        
        # 获取当前训练轮次 t (epoch)，向下取整
        t = int(self.state.epoch) if self.state.epoch is not None else 0
        
        # 初始 λ 为 0.80，每轮衰减 0.02，下限为 0.60
        lambda_fl_t = max(0.60, 0.80 - 0.02 * t)
        
        # μ = 1 - λ
        mu_ls_t = 1.0 - lambda_fl_t
        
        # 实例化损失函数
        loss_fct = LinearCombinationLoss(
            focal_alpha=0.85,        
            focal_gamma=2.0,         
            ls_epsilon=0.1,          
            lambda_fl=lambda_fl_t,   
            lambda_ls=mu_ls_t        
        )
        
        loss = loss_fct(logits.view(-1, self.model.config.num_labels), labels.view(-1))
        
        return (loss, outputs) if return_outputs else loss
    
# ============================================================
# 数据流挂载模块
# ============================================================
class VulnerabilityDataset(Dataset):
    def __init__(self, file_path, tokenizer, max_length=512):
        self.data = []
        if not os.path.exists(file_path):
            print(f"[异常] 数据集文件未找到: {file_path}")
            return
            
        with open(file_path, 'r', encoding='utf-8') as f:
            for line in f:
                if not line.strip():
                    continue
                try:
                    obj = json.loads(line)
                    # 优先级：融合代码 > 大模型初筛代码 > 原始代码
                    code = obj.get('refined_code', obj.get('llm_slice', obj.get('func', '')))
                    target = obj.get('target')
                    
                    if code and target is not None:
                        self.data.append({"code": code, "label": int(target)})
                except json.JSONDecodeError:
                    continue
                    
        self.tokenizer = tokenizer
        self.max_length = max_length

    def __len__(self):
        return len(self.data)

    def __getitem__(self, idx):
        item = self.data[idx]
        encoding = self.tokenizer(
            item["code"],
            truncation=True,
            padding="max_length",
            max_length=self.max_length,
            return_tensors="pt"
        )
        return {
            "input_ids": encoding["input_ids"].squeeze(0),
            "attention_mask": encoding["attention_mask"].squeeze(0),
            "labels": torch.tensor(item["label"], dtype=torch.long)
        }

def compute_metrics(eval_pred):
    """
    综合性能评估函数
    包含基础分类指标 (Acc, Pre, Rec, F1) 与抗不平衡指标 (B.Acc, MCC)
    """
    logits, labels = eval_pred
    probs = torch.softmax(torch.tensor(logits), dim=-1).numpy()
    preds = (probs[:, 1] >= PREDICTION_THRESHOLD).astype(int)
    
    # 基础指标计算
    precision, recall, f1, _ = precision_recall_fscore_support(labels, preds, average="binary", zero_division=0)
    acc = accuracy_score(labels, preds)
    
    # 抗不平衡指标计算
    b_acc = balanced_accuracy_score(labels, preds)
    mcc = matthews_corrcoef(labels, preds)
    
    return {
        "accuracy": acc, 
        "precision": precision, 
        "recall": recall, 
        "f1": f1,
        "b_acc": b_acc,
        "mcc": mcc
    }

# ============================================================
# 自动化执行总线
# ============================================================
def main():
    print(f"\n{'='*60}\n[环境初始化] 运行模式: {RUN_MODE.upper()} | 迭代轮次: {CURRENT_ITERATION} | Epochs: {EPOCHS}\n{'='*60}")
    
    if not os.path.exists(TRAIN_DATA_PATH):
        print(f"[终止] 核心训练集未就绪，请核对前置融合精炼流水线产物: {TRAIN_DATA_PATH}")
        return

    print("[加载配置] 正在初始化 CodeBERT 预训练模型...")
    tokenizer = AutoTokenizer.from_pretrained(MODEL_NAME)
    model = AutoModelForSequenceClassification.from_pretrained(MODEL_NAME, num_labels=2)

    print("[数据挂载] 解析并加载训练、验证、测试数据集...")
    train_dataset = VulnerabilityDataset(TRAIN_DATA_PATH, tokenizer)
    valid_dataset = VulnerabilityDataset(VALID_DATA_PATH, tokenizer)
    test_dataset  = VulnerabilityDataset(TEST_DATA_PATH, tokenizer)

    train_labels = [item["label"] for item in train_dataset.data]
    label_counts = Counter(train_labels)
    print(f"[数据分布] 训练集总量: {len(train_dataset)} | 类别比例 (0:正常, 1:漏洞) -> {dict(label_counts)}")

    # 依赖 F1 分数保存最优权重的核心配置项
    training_args = TrainingArguments(
        output_dir=MODEL_SAVE_DIR,
        learning_rate=LEARNING_RATE,
        per_device_train_batch_size=BATCH_SIZE,
        per_device_eval_batch_size=BATCH_SIZE,
        num_train_epochs=EPOCHS,
        weight_decay=0.01,
        eval_strategy="epoch",            # 每轮评估
        save_strategy="epoch",            # 每轮保存
        load_best_model_at_end=True,      # 结束时回滚加载最佳模型
        metric_for_best_model="f1",       # 以 F1 作为最优评判指标
        logging_steps=50,
        seed=42
    )

    data_collator = DataCollatorWithPadding(tokenizer=tokenizer)

    trainer = CustomTrainer(
        model=model,
        args=training_args,
        train_dataset=train_dataset,
        eval_dataset=valid_dataset,
        processing_class=tokenizer,
        data_collator=data_collator,
        compute_metrics=compute_metrics
    )

    print("\n[系统调度] 启动模型闭环微调流水线...")
    trainer.train()

    print("\n[性能评估] 测试集指标计算中...")
    test_results = trainer.evaluate(test_dataset)
    print(f"[测试集结果] {test_results}")

    print("\n[系统调度] 启动预测阶段，提取漏报样本 (False Negatives)...")
    
    os.makedirs(os.path.dirname(FN_OUTPUT_PATH), exist_ok=True)
    
    val_data = []
    with open(VALID_DATA_PATH, 'r', encoding='utf-8') as f:
        val_data = [json.loads(line) for line in f if line.strip()]

    probs = torch.softmax(torch.tensor(trainer.predict(valid_dataset).predictions), dim=-1).numpy()
    preds = (probs[:, 1] >= PREDICTION_THRESHOLD).astype(int)

    fn_count = 0
    with open(PREDICT_OUTPUT_PATH, 'w', encoding='utf-8') as tp_out, open(FN_OUTPUT_PATH, 'w', encoding='utf-8') as tn_out:
        for i, item in tqdm(enumerate(val_data), total=len(val_data), desc="[数据路由] 分离漏报验证集", unit="样本"):
            item.update({"pred_label": int(preds[i]), "pred_prob_0": float(probs[i][0]), "pred_prob_1": float(probs[i][1])})
            
            is_fn = (item["target"] == 1 and item["pred_label"] == 0)
                
            if is_fn:
                tn_out.write(json.dumps(item, ensure_ascii=False) + '\n')
                fn_count += 1
            else:
                tp_out.write(json.dumps(item, ensure_ascii=False) + '\n')
                
    print(f"[执行结果] 预测完成。共抽取 {fn_count} 条漏报样本，已输出至: {FN_OUTPUT_PATH}")

if __name__ == "__main__":
    main()