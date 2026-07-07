# -*- coding: utf-8 -*-
"""
基于特征切片 (VRR-SRR) 的漏洞二分类模型消融实验脚本

目标模块：微调损失适配方案内的消融实验

核心特性：
1. 涵盖微调损失适配方案内的 4 组消融实验配置。
2. 全局路径与 I/O 严格遵循全量 (deepseek) 与 Smoke 隔离原则，各消融组数据互不污染。

实验配置说明：
- (1) 移除微调损失适配方案: 使用标准 CrossEntropy Loss，作为基线。
- (2) 移除焦点损失函数: 仅保留 Label Smoothing，移除难分样本加权机制。
- (3) 移除标签平滑策略: 仅保留 Focal Loss，移除概率校准与防过拟合机制。
- (4) 完整系统 (Ours): 融合 Focal Loss 与标签平滑正则化的协同动态加权损失适配策略。
"""

import os
os.environ["HF_ENDPOINT"] = "https://hf-mirror.com"
import json
import torch
import torch.nn as nn
import torch.nn.functional as F
from collections import Counter
from torch.utils.data import Dataset
from sklearn.metrics import (
    accuracy_score, 
    precision_recall_fscore_support, 
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
# 全局运行态配置中心
# ============================================================
RUN_MODE = "smoke"  # 可选值: "smoke" 或 "deepseek"
CURRENT_ITERATION = 1

MODEL_NAME = "microsoft/codebert-base"
BATCH_SIZE = 16
LEARNING_RATE = 2e-5
PREDICTION_THRESHOLD = 0.5
EPOCHS = 2 if RUN_MODE == "smoke" else 10

# 统配基础路径
DATASET_DIR = "smoke" if RUN_MODE == "smoke" else "deepseek"

# ============================================================
# 共享模块 1：动态损失定制 Trainer 
# ============================================================
class CustomTrainer(Trainer):
    def __init__(self, loss_mode="complete", *args, **kwargs):
        """
        通过 loss_mode 控制不同的损失函数消融配置：
        - "no_adapt" : 标准交叉熵 (CE)
        - "no_focal" : 仅标签平滑 (LS)
        - "no_ls"    : 仅焦点损失 (FL)
        - "complete" : 动态协同加权 (Ours)
        """
        super().__init__(*args, **kwargs)
        self.loss_mode = loss_mode
        self.focal_alpha = 0.85
        self.focal_gamma = 2.0
        self.ls_epsilon = 0.1

    def compute_loss(self, model, inputs, return_outputs=False, **kwargs):
        labels = inputs.get("labels")
        outputs = model(**inputs)
        logits = outputs.get("logits")
        
        # 将 Logits 和 Labels 展平对齐
        logits_flat = logits.view(-1, self.model.config.num_labels)
        labels_flat = labels.view(-1)

        # 1. 基础交叉熵损失 (Cross Entropy)
        ce_loss = F.cross_entropy(logits_flat, labels_flat, reduction='none')
        
        # 2. 焦点损失核心计算 (Focal Loss)
        pt = torch.exp(-ce_loss)
        alpha_t = torch.where(labels_flat == 1, self.focal_alpha, 1.0 - self.focal_alpha)
        focal_loss_raw = alpha_t * (1 - pt) ** self.focal_gamma * ce_loss
        
        # 3. 标签平滑核心计算 (Label Smoothing)
        smooth_loss = -F.log_softmax(logits_flat, dim=-1).mean(dim=-1)
        ls_ce_loss_raw = (1.0 - self.ls_epsilon) * ce_loss + self.ls_epsilon * smooth_loss

        # ================= 动态消融路由 =================
        if self.loss_mode == "no_adapt":
            # 配置 1：退回标准交叉熵
            loss = ce_loss.mean()
            
        elif self.loss_mode == "no_focal":
            # 配置 2：仅使用标签平滑
            loss = ls_ce_loss_raw.mean()
            
        elif self.loss_mode == "no_ls":
            # 配置 3：仅使用 Focal Loss
            loss = focal_loss_raw.mean()
            
        elif self.loss_mode == "complete":
            # 配置 4：动态协同加权 (Ours)
            # 获取当前训练轮次 t (向下取整)
            t = int(self.state.epoch) if self.state.epoch is not None else 0
            
            # 动态权重演化：初始 0.80，每轮下降 0.02，底线 0.60
            lambda_fl_t = max(0.60, 0.80 - 0.02 * t)
            mu_ls_t = 1.0 - lambda_fl_t
            
            loss = (lambda_fl_t * focal_loss_raw + mu_ls_t * ls_ce_loss_raw).mean()
        else:
            loss = ce_loss.mean()

        return (loss, outputs) if return_outputs else loss

# ============================================================
# 共享模块 2：数据流挂载与评价指标
# ============================================================
class VulnerabilityDataset(Dataset):
    def __init__(self, file_path, tokenizer, target_key='refined_code', max_length=512):
        self.data = []
        if not os.path.exists(file_path):
            print(f"[Warning] 数据集文件未找到，将返回空数据集: {file_path}")
            return
            
        with open(file_path, 'r', encoding='utf-8') as f:
            for line in f:
                if not line.strip(): continue
                try:
                    obj = json.loads(line)
                    code = obj.get(target_key, '')
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
            item["code"], truncation=True, padding="max_length", max_length=self.max_length, return_tensors="pt"
        )
        return {
            "input_ids": encoding["input_ids"].squeeze(0),
            "attention_mask": encoding["attention_mask"].squeeze(0),
            "labels": torch.tensor(item["label"], dtype=torch.long)
        }

def compute_metrics(eval_pred):
    """
    综合性能评估函数 (包含 F1, B.Acc, MCC 等平衡性指标)
    """
    logits, labels = eval_pred
    probs = torch.softmax(torch.tensor(logits), dim=-1).numpy()
    preds = (probs[:, 1] >= PREDICTION_THRESHOLD).astype(int)
    
    precision, recall, f1, _ = precision_recall_fscore_support(labels, preds, average="binary", zero_division=0)
    acc = accuracy_score(labels, preds)
    b_acc = balanced_accuracy_score(labels, preds)
    mcc = matthews_corrcoef(labels, preds)
    
    return {
        "accuracy": acc, "precision": precision, "recall": recall, "f1": f1, "b_acc": b_acc, "mcc": mcc
    }

# ============================================================
# 共享模块 3：漏报样本 (FN) 提取引擎
# ============================================================
def extract_false_negatives(trainer, valid_dataset, valid_data_path, fn_output_path, predict_output_path):
    """
    执行模型推理，分离并导出真实标签为漏洞但被模型预测为安全的漏报样本 (False Negatives)。
    """
    print("\n[Task] 启动推理阶段，正在提取漏报验证集 (False Negatives)...")
    os.makedirs(os.path.dirname(fn_output_path), exist_ok=True)
    os.makedirs(os.path.dirname(predict_output_path), exist_ok=True)
    
    val_data = []
    with open(valid_data_path, 'r', encoding='utf-8') as f:
        val_data = [json.loads(line) for line in f if line.strip()]

    probs = torch.softmax(torch.tensor(trainer.predict(valid_dataset).predictions), dim=-1).numpy()
    preds = (probs[:, 1] >= PREDICTION_THRESHOLD).astype(int)

    fn_count = 0
    with open(predict_output_path, 'w', encoding='utf-8') as tp_out, open(fn_output_path, 'w', encoding='utf-8') as tn_out:
        for i, item in tqdm(enumerate(val_data), total=len(val_data), desc="[Process] 分离漏报样本", unit=" samples"):
            item.update({
                "pred_label": int(preds[i]), 
                "pred_prob_0": float(probs[i][0]), 
                "pred_prob_1": float(probs[i][1])
            })
            
            is_fn = (item["target"] == 1 and item["pred_label"] == 0)
            
            if is_fn:
                tn_out.write(json.dumps(item, ensure_ascii=False) + '\n')
                fn_count += 1
            else:
                tp_out.write(json.dumps(item, ensure_ascii=False) + '\n')
                
    print(f"[Task Report] 预测分离完毕。共捕获 {fn_count} 条漏报样本。")
    print(f"  - 漏报归档路径: {fn_output_path}")

# ============================================================
# 公共配置提取器
# ============================================================
def get_common_config(ablation_name):
    """统一管理各消融实验的输入输出路径，确保实验组物理隔离"""
    if CURRENT_ITERATION == 1:
        train_path = f"../slice/{DATASET_DIR}/refined_train.jsonl"
    else:
        train_path = f"../slice/{DATASET_DIR}/iteration{CURRENT_ITERATION-1}/refined_train.jsonl"
        
    valid_path = f"../slice/{DATASET_DIR}/refined_valid.jsonl"
    test_path  = f"../slice/{DATASET_DIR}/refined_test.jsonl"
    
    base_out = f"../slice/{DATASET_DIR}/{ablation_name}"
    model_dir = f"{base_out}/codebert"
    fn_out = f"{base_out}/iteration{CURRENT_ITERATION}/valvul_nofind.jsonl"
    pred_out = f"{base_out}/iteration{CURRENT_ITERATION}/val_predictions.jsonl"
    
    return train_path, valid_path, test_path, model_dir, fn_out, pred_out

# ============================================================
# 损失函数消融配置区
# ============================================================

def run_ablation(loss_mode: str, ablation_name: str, desc: str):
    """通用消融实验执行框架"""
    print(f"\n{'='*60}\n[环境初始化] 微调损失消融实验: {desc}")
    print(f"当前运行模式: {RUN_MODE.upper()} | 损失策略: {loss_mode.upper()} | Epochs: {EPOCHS}\n{'='*60}")
    
    TRAIN_PATH, VALID_PATH, TEST_PATH, MODEL_DIR, FN_OUT, PRED_OUT = get_common_config(ablation_name)

    if not os.path.exists(TRAIN_PATH):
        print(f"[Error] 训练集未就绪，流程终止: {TRAIN_PATH}")
        return

    print("[Info] 初始化 CodeBERT 预训练模型...")
    tokenizer = AutoTokenizer.from_pretrained(MODEL_NAME)
    model = AutoModelForSequenceClassification.from_pretrained(MODEL_NAME, num_labels=2)
    
    train_dataset = VulnerabilityDataset(TRAIN_PATH, tokenizer, target_key='refined_code')
    valid_dataset = VulnerabilityDataset(VALID_PATH, tokenizer, target_key='refined_code')
    test_dataset  = VulnerabilityDataset(TEST_PATH, tokenizer, target_key='refined_code')

    training_args = TrainingArguments(
        output_dir=MODEL_DIR, learning_rate=LEARNING_RATE, 
        per_device_train_batch_size=BATCH_SIZE, per_device_eval_batch_size=BATCH_SIZE, 
        num_train_epochs=EPOCHS, weight_decay=0.01, 
        eval_strategy="epoch", save_strategy="epoch", 
        load_best_model_at_end=True, metric_for_best_model="f1", logging_steps=50, seed=42
    )
    
    # 针对不适配任何微调损失的对照组，直接调用原生 Trainer
    if loss_mode == "no_adapt":
        print("[Task] 启动标准微调流水线 (完全依赖 HuggingFace 原生交叉熵损失)...")
        trainer = Trainer(
            model=model, args=training_args, train_dataset=train_dataset, 
            eval_dataset=valid_dataset, processing_class=tokenizer, 
            data_collator=DataCollatorWithPadding(tokenizer=tokenizer), compute_metrics=compute_metrics
        )
    else:
        print(f"[Task] 启动动态损失微调流水线 (注入自定义 CustomTrainer, 模式: {loss_mode})...")
        trainer = CustomTrainer(
            loss_mode=loss_mode,
            model=model, args=training_args, train_dataset=train_dataset, 
            eval_dataset=valid_dataset, processing_class=tokenizer, 
            data_collator=DataCollatorWithPadding(tokenizer=tokenizer), compute_metrics=compute_metrics
        )
        
    trainer.train()
    
    print("\n[性能评估] 测试集指标计算中...")
    print(f"[测试集评估结果] {trainer.evaluate(test_dataset)}")
    extract_false_negatives(trainer, valid_dataset, VALID_PATH, FN_OUT, PRED_OUT)


# --- Ablation 1: 移除微调损失适配方案 (纯交叉熵) ---
def run_loss_ablation_1_no_adapt():
    run_ablation(
        loss_mode="no_adapt", 
        ablation_name="loss_ablation_1_no_adapt", 
        desc="(1) 移除微调损失适配方案 (采用原生 CrossEntropy Loss)"
    )

# --- Ablation 2: 移除焦点损失函数 (仅标签平滑) ---
def run_loss_ablation_2_no_focal():
    run_ablation(
        loss_mode="no_focal", 
        ablation_name="loss_ablation_2_no_focal", 
        desc="(2) 移除焦点损失函数 (仅应用 Label Smoothing)"
    )

# --- Ablation 3: 移除标签平滑策略 (仅 Focal Loss) ---
def run_loss_ablation_3_no_ls():
    run_ablation(
        loss_mode="no_ls", 
        ablation_name="loss_ablation_3_no_ls", 
        desc="(3) 移除标签平滑策略 (仅应用 Focal Loss)"
    )

# --- Ablation 4: 完整系统 (Ours) ---
def run_loss_ablation_4_complete():
    run_ablation(
        loss_mode="complete", 
        ablation_name="loss_ablation_4_complete", 
        desc="(4) 完整系统 Ours (融合 Focal Loss 与 LS 的动态协同加权)"
    )

if __name__ == "__main__":
    # 调度中心：通过取消对应函数的注释以激活对应的损失函数消融方案
    
    # run_loss_ablation_1_no_adapt()
    # run_loss_ablation_2_no_focal()
    run_loss_ablation_3_no_ls()
    # run_loss_ablation_4_complete()