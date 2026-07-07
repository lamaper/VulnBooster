"""
基于特征切片 (VRR-SRR) 的漏洞二分类模型消融实验脚本
核心特性：
1. 涵盖 5 组独立的消融实验配置（数据增强、特征提取、微调损失等维度的全面消融）。
2. 全局路径与 I/O 严格遵循全量与 Smoke 沙盒的物理隔离原则，各消融组数据互不污染。

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
# 共享模块 1：动态损失函数（供激活了动态损失的消融实验调用）
# ============================================================
class LinearCombinationLoss(nn.Module):
    def __init__(self, focal_alpha=0.85, focal_gamma=2.0, ls_epsilon=0.1, lambda_fl=1.0, lambda_ls=1.0, reduction='mean'):
        super().__init__()
        self.focal_alpha = focal_alpha
        self.focal_gamma = focal_gamma
        self.ls_epsilon = ls_epsilon
        self.lambda_fl = lambda_fl
        self.lambda_ls = lambda_ls
        self.reduction = reduction

    def forward(self, inputs, targets):
        ce_loss = F.cross_entropy(inputs, targets, reduction='none')
        pt = torch.exp(-ce_loss)
        alpha_t = torch.where(targets == 1, self.focal_alpha, 1.0 - self.focal_alpha)
        focal_loss = alpha_t * (1 - pt) ** self.focal_gamma * ce_loss
        smooth_loss = -F.log_softmax(inputs, dim=-1).mean(dim=-1)
        ls_ce_loss = (1.0 - self.ls_epsilon) * ce_loss + self.ls_epsilon * smooth_loss
        combined_loss = self.lambda_fl * focal_loss + self.lambda_ls * ls_ce_loss
        
        if self.reduction == 'mean':
            return combined_loss.mean()
        elif self.reduction == 'sum':
            return combined_loss.sum()
        return combined_loss

class CustomTrainer(Trainer):
    def compute_loss(self, model, inputs, return_outputs=False, **kwargs):
        labels = inputs.get("labels")
        outputs = model(**inputs)
        logits = outputs.get("logits")
        t = int(self.state.epoch) if self.state.epoch is not None else 0
        lambda_fl_t = max(0.60, 0.80 - 0.02 * t)
        mu_ls_t = 1.0 - lambda_fl_t
        loss_fct = LinearCombinationLoss(lambda_fl=lambda_fl_t, lambda_ls=mu_ls_t)
        loss = loss_fct(logits.view(-1, self.model.config.num_labels), labels.view(-1))
        return (loss, outputs) if return_outputs else loss

# ============================================================
# 共享模块 2：数据流挂载与评价指标
# ============================================================
class VulnerabilityDataset(Dataset):
    def __init__(self, file_path, tokenizer, max_length=512):
        self.data = []
        if not os.path.exists(file_path):
            print(f"[Warning] 数据集文件未定位: {file_path}")
            return
            
        with open(file_path, 'r', encoding='utf-8') as f:
            for line in f:
                if not line.strip():
                    continue
                try:
                    obj = json.loads(line)
                    # 优先级获取代码特征：双路融合精炼 > LLM单路切片 > 原始代码
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
            item["code"], truncation=True, padding="max_length", max_length=self.max_length, return_tensors="pt"
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
    
    precision, recall, f1, _ = precision_recall_fscore_support(labels, preds, average="binary", zero_division=0)
    acc = accuracy_score(labels, preds)
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
# 共享模块 3：漏报样本 (FN) 提取引擎
# ============================================================
def extract_false_negatives(trainer, valid_dataset, valid_data_path, fn_output_path, predict_output_path):
    """
    执行模型推理，分离并导出真实标签为漏洞但被模型预测为安全的漏报样本 (False Negatives)，
    以此支撑下一阶段（CoT / CWE）的数据演化与增强。
    """
    print("\n[系统调度] 启动预测阶段，提取漏报样本 (False Negatives)...")
    os.makedirs(os.path.dirname(fn_output_path), exist_ok=True)
    os.makedirs(os.path.dirname(predict_output_path), exist_ok=True)
    
    val_data = []
    with open(valid_data_path, 'r', encoding='utf-8') as f:
        val_data = [json.loads(line) for line in f if line.strip()]

    probs = torch.softmax(torch.tensor(trainer.predict(valid_dataset).predictions), dim=-1).numpy()
    preds = (probs[:, 1] >= PREDICTION_THRESHOLD).astype(int)

    fn_count = 0
    with open(predict_output_path, 'w', encoding='utf-8') as tp_out, open(fn_output_path, 'w', encoding='utf-8') as tn_out:
        for i, item in tqdm(enumerate(val_data), total=len(val_data), desc="[数据路由] 分离漏报验证集", unit="样本"):
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
                
    print(f"[执行结果] 预测分离完毕。共捕获 {fn_count} 条漏报样本。")
    print(f"           漏报归档路径: {fn_output_path}")


# ============================================================
# 消融实验配置 1：不增强（原始数据基线）
# 目标：使用未经任何特征切片的原始长函数与标准交叉熵，测定绝对基线性能。
# ============================================================
def run_ablation_1_raw_data():
    print(f"\n{'='*60}\n[环境初始化] 正在执行消融实验 (1): 不增强（原始数据基线）")
    print(f"当前运行模式: {RUN_MODE.upper()} | 迭代轮次: {CURRENT_ITERATION} | Epochs: {EPOCHS}\n{'='*60}")
    
    TRAIN_DATA_PATH = f"../dataset/primevul_train_cleaned.jsonl" if RUN_MODE == "deepseek" else f"../{DATASET_DIR}/primevul_train_cleaned.jsonl"
    VALID_DATA_PATH = f"../dataset/primevul_valid_cleaned.jsonl" if RUN_MODE == "deepseek" else f"../{DATASET_DIR}/primevul_valid_cleaned.jsonl"
    TEST_DATA_PATH  = f"../dataset/primevul_test_cleaned.jsonl"  if RUN_MODE == "deepseek" else f"../{DATASET_DIR}/primevul_test_cleaned.jsonl"
    
    BASE_OUTPUT_DIR = f"../slice/{DATASET_DIR}/ablation_1_raw_data"
    MODEL_SAVE_DIR  = f"{BASE_OUTPUT_DIR}/codebert"
    FN_OUTPUT_PATH  = f"{BASE_OUTPUT_DIR}/iteration{CURRENT_ITERATION}/valvul_nofind.jsonl"
    PRED_OUTPUT_PATH = f"{BASE_OUTPUT_DIR}/iteration{CURRENT_ITERATION}/val_predictions.jsonl"

    if not os.path.exists(TRAIN_DATA_PATH):
        print(f"[终止] 训练集未就绪: {TRAIN_DATA_PATH}")
        return

    tokenizer = AutoTokenizer.from_pretrained(MODEL_NAME)
    model = AutoModelForSequenceClassification.from_pretrained(MODEL_NAME, num_labels=2)
    train_dataset = VulnerabilityDataset(TRAIN_DATA_PATH, tokenizer)
    valid_dataset = VulnerabilityDataset(VALID_DATA_PATH, tokenizer)
    test_dataset  = VulnerabilityDataset(TEST_DATA_PATH, tokenizer)

    training_args = TrainingArguments(
        output_dir=MODEL_SAVE_DIR, learning_rate=LEARNING_RATE, 
        per_device_train_batch_size=BATCH_SIZE, per_device_eval_batch_size=BATCH_SIZE, 
        num_train_epochs=EPOCHS, weight_decay=0.01, 
        eval_strategy="epoch", save_strategy="epoch", 
        load_best_model_at_end=True, metric_for_best_model="f1", logging_steps=50, seed=42
    )
    
    print("[系统调度] 启动标准微调流水线 (原始函数 + 标准交叉熵)...")
    trainer = Trainer(
        model=model, args=training_args, train_dataset=train_dataset, 
        eval_dataset=valid_dataset, processing_class=tokenizer, 
        data_collator=DataCollatorWithPadding(tokenizer=tokenizer), compute_metrics=compute_metrics
    )
    trainer.train()
    
    print("\n[性能评估] 测试集指标计算中...")
    print(f"[测试集结果] {trainer.evaluate(test_dataset)}")
    extract_false_negatives(trainer, valid_dataset, VALID_DATA_PATH, FN_OUTPUT_PATH, PRED_OUTPUT_PATH)


# ============================================================
# 消融实验配置 2：移除漏洞数据增强方案
# 目标：仅使用经过特征切片提取的数据，并使用动态损失，但不并入任何 CoT/CWE 生成的变体。
# ============================================================
def run_ablation_2_no_data_aug():
    print(f"\n{'='*60}\n[环境初始化] 正在执行消融实验 (2): 移除漏洞数据增强方案")
    print(f"当前运行模式: {RUN_MODE.upper()} | 迭代轮次: {CURRENT_ITERATION} | Epochs: {EPOCHS}\n{'='*60}")
    
    # 始终采用初始精炼数据，不加载后续迭代的扩充数据
    TRAIN_DATA_PATH = f"../slice/{DATASET_DIR}/refined_train.jsonl" 
    VALID_DATA_PATH = f"../slice/{DATASET_DIR}/refined_valid.jsonl"
    TEST_DATA_PATH  = f"../slice/{DATASET_DIR}/refined_test.jsonl"
    
    BASE_OUTPUT_DIR = f"../slice/{DATASET_DIR}/ablation_2_no_data_aug"
    MODEL_SAVE_DIR  = f"{BASE_OUTPUT_DIR}/codebert"
    FN_OUTPUT_PATH  = f"{BASE_OUTPUT_DIR}/iteration{CURRENT_ITERATION}/valvul_nofind.jsonl"
    PRED_OUTPUT_PATH = f"{BASE_OUTPUT_DIR}/iteration{CURRENT_ITERATION}/val_predictions.jsonl"

    if not os.path.exists(TRAIN_DATA_PATH):
        print(f"[终止] 训练集未就绪: {TRAIN_DATA_PATH}")
        return

    tokenizer = AutoTokenizer.from_pretrained(MODEL_NAME)
    model = AutoModelForSequenceClassification.from_pretrained(MODEL_NAME, num_labels=2)
    train_dataset = VulnerabilityDataset(TRAIN_DATA_PATH, tokenizer)
    valid_dataset = VulnerabilityDataset(VALID_DATA_PATH, tokenizer)
    test_dataset  = VulnerabilityDataset(TEST_DATA_PATH, tokenizer)

    training_args = TrainingArguments(
        output_dir=MODEL_SAVE_DIR, learning_rate=LEARNING_RATE, 
        per_device_train_batch_size=BATCH_SIZE, per_device_eval_batch_size=BATCH_SIZE, 
        num_train_epochs=EPOCHS, weight_decay=0.01, 
        eval_strategy="epoch", save_strategy="epoch", 
        load_best_model_at_end=True, metric_for_best_model="f1", logging_steps=50, seed=42
    )
    
    print("[系统调度] 启动动态损失微调流水线 (特征切片 + 无数据增强)...")
    trainer = CustomTrainer(
        model=model, args=training_args, train_dataset=train_dataset, 
        eval_dataset=valid_dataset, processing_class=tokenizer, 
        data_collator=DataCollatorWithPadding(tokenizer=tokenizer), compute_metrics=compute_metrics
    )
    trainer.train()
    
    print("\n[性能评估] 测试集指标计算中...")
    print(f"[测试集结果] {trainer.evaluate(test_dataset)}")
    extract_false_negatives(trainer, valid_dataset, VALID_DATA_PATH, FN_OUTPUT_PATH, PRED_OUTPUT_PATH)


# ============================================================
# 消融实验配置 3：移除漏洞特征提取方案
# 目标：使用原始长函数微调，混合在长函数上生成的增强样本，以验证特征切片的必要性。
# ============================================================
def run_ablation_3_no_feature_extract():
    print(f"\n{'='*60}\n[环境初始化] 正在执行消融实验 (3): 移除漏洞特征提取方案")
    print(f"当前运行模式: {RUN_MODE.upper()} | 迭代轮次: {CURRENT_ITERATION} | Epochs: {EPOCHS}\n{'='*60}")
    
    if CURRENT_ITERATION == 1:
        TRAIN_DATA_PATH = f"../dataset/primevul_train_cleaned.jsonl" if RUN_MODE == "deepseek" else f"../{DATASET_DIR}/primevul_train_cleaned.jsonl"
    else:
        TRAIN_DATA_PATH = f"../slice/{DATASET_DIR}/ablation_3_no_feature_extract/iteration{CURRENT_ITERATION-1}/raw_aug_train.jsonl"
        
    VALID_DATA_PATH = f"../dataset/primevul_valid_cleaned.jsonl" if RUN_MODE == "deepseek" else f"../{DATASET_DIR}/primevul_valid_cleaned.jsonl"
    TEST_DATA_PATH  = f"../dataset/primevul_test_cleaned.jsonl"  if RUN_MODE == "deepseek" else f"../{DATASET_DIR}/primevul_test_cleaned.jsonl"
    
    BASE_OUTPUT_DIR = f"../slice/{DATASET_DIR}/ablation_3_no_feature_extract"
    MODEL_SAVE_DIR  = f"{BASE_OUTPUT_DIR}/codebert"
    FN_OUTPUT_PATH  = f"{BASE_OUTPUT_DIR}/iteration{CURRENT_ITERATION}/valvul_nofind.jsonl"
    PRED_OUTPUT_PATH = f"{BASE_OUTPUT_DIR}/iteration{CURRENT_ITERATION}/val_predictions.jsonl"

    if not os.path.exists(TRAIN_DATA_PATH):
        print(f"[终止] 训练集未就绪: {TRAIN_DATA_PATH}")
        return

    tokenizer = AutoTokenizer.from_pretrained(MODEL_NAME)
    model = AutoModelForSequenceClassification.from_pretrained(MODEL_NAME, num_labels=2)
    train_dataset = VulnerabilityDataset(TRAIN_DATA_PATH, tokenizer)
    valid_dataset = VulnerabilityDataset(VALID_DATA_PATH, tokenizer)
    test_dataset  = VulnerabilityDataset(TEST_DATA_PATH, tokenizer)
    
    training_args = TrainingArguments(
        output_dir=MODEL_SAVE_DIR, learning_rate=LEARNING_RATE, 
        per_device_train_batch_size=BATCH_SIZE, per_device_eval_batch_size=BATCH_SIZE, 
        num_train_epochs=EPOCHS, weight_decay=0.01, 
        eval_strategy="epoch", save_strategy="epoch", 
        load_best_model_at_end=True, metric_for_best_model="f1", logging_steps=50, seed=42
    )
    
    print("[系统调度] 启动微调流水线 (动态损失 + 原始长函数及增强数据)...")
    trainer = CustomTrainer(
        model=model, args=training_args, train_dataset=train_dataset, 
        eval_dataset=valid_dataset, processing_class=tokenizer, 
        data_collator=DataCollatorWithPadding(tokenizer=tokenizer), compute_metrics=compute_metrics
    )
    trainer.train()
    
    print("\n[性能评估] 测试集指标计算中...")
    print(f"[测试集结果] {trainer.evaluate(test_dataset)}")
    extract_false_negatives(trainer, valid_dataset, VALID_DATA_PATH, FN_OUTPUT_PATH, PRED_OUTPUT_PATH)


# ============================================================
# 消融实验配置 4：移除微调损失适配方案
# 目标：提供已完成特征提取与数据增强的优质数据，但退回标准交叉熵损失，验证动态加权的平滑效用。
# ============================================================
def run_ablation_4_no_loss_adapt():
    print(f"\n{'='*60}\n[环境初始化] 正在执行消融实验 (4): 移除微调损失适配方案")
    print(f"当前运行模式: {RUN_MODE.upper()} | 迭代轮次: {CURRENT_ITERATION} | Epochs: {EPOCHS}\n{'='*60}")
    
    if CURRENT_ITERATION == 1:
        TRAIN_DATA_PATH = f"../slice/{DATASET_DIR}/refined_train.jsonl"
    else:
        TRAIN_DATA_PATH = f"../slice/{DATASET_DIR}/iteration{CURRENT_ITERATION-1}/refined_train.jsonl"
        
    VALID_DATA_PATH = f"../slice/{DATASET_DIR}/refined_valid.jsonl"
    TEST_DATA_PATH  = f"../slice/{DATASET_DIR}/refined_test.jsonl"
    
    BASE_OUTPUT_DIR = f"../slice/{DATASET_DIR}/ablation_4_no_loss_adapt"
    MODEL_SAVE_DIR  = f"{BASE_OUTPUT_DIR}/codebert"
    FN_OUTPUT_PATH  = f"{BASE_OUTPUT_DIR}/iteration{CURRENT_ITERATION}/valvul_nofind.jsonl"
    PRED_OUTPUT_PATH = f"{BASE_OUTPUT_DIR}/iteration{CURRENT_ITERATION}/val_predictions.jsonl"

    if not os.path.exists(TRAIN_DATA_PATH):
        print(f"[终止] 训练集未就绪，请核对前置流水线产物: {TRAIN_DATA_PATH}")
        return

    tokenizer = AutoTokenizer.from_pretrained(MODEL_NAME)
    model = AutoModelForSequenceClassification.from_pretrained(MODEL_NAME, num_labels=2)
    train_dataset = VulnerabilityDataset(TRAIN_DATA_PATH, tokenizer)
    valid_dataset = VulnerabilityDataset(VALID_DATA_PATH, tokenizer)
    test_dataset  = VulnerabilityDataset(TEST_DATA_PATH, tokenizer)

    training_args = TrainingArguments(
        output_dir=MODEL_SAVE_DIR, learning_rate=LEARNING_RATE, 
        per_device_train_batch_size=BATCH_SIZE, per_device_eval_batch_size=BATCH_SIZE, 
        num_train_epochs=EPOCHS, weight_decay=0.01, 
        eval_strategy="epoch", save_strategy="epoch", 
        load_best_model_at_end=True, metric_for_best_model="f1", logging_steps=50, seed=42
    )

    # 不使用 CustomTrainer，回退到 HuggingFace 默认 Trainer (使用标准 CrossEntropyLoss)
    print("[系统调度] 启动消融实验微调流水线 (标准交叉熵 + 特征切片及增强数据)...")
    trainer = Trainer(
        model=model, args=training_args, train_dataset=train_dataset, 
        eval_dataset=valid_dataset, processing_class=tokenizer, 
        data_collator=DataCollatorWithPadding(tokenizer=tokenizer), compute_metrics=compute_metrics
    )
    trainer.train()

    print("\n[性能评估] 测试集指标计算中...")
    print(f"[测试集结果] {trainer.evaluate(test_dataset)}")
    extract_false_negatives(trainer, valid_dataset, VALID_DATA_PATH, FN_OUTPUT_PATH, PRED_OUTPUT_PATH)


# ============================================================
# 消融实验配置 5：完整系统 (Ours)
# 目标：全组件激活（包含切片、数据增强、动态损失）。
# ============================================================
def run_ablation_5_complete_system():
    print(f"\n{'='*60}\n[环境初始化] 正在执行实验 (5): 完整系统闭环效能验证")
    print(f"当前运行模式: {RUN_MODE.upper()} | 迭代轮次: {CURRENT_ITERATION} | Epochs: {EPOCHS}\n{'='*60}")
    
    if CURRENT_ITERATION == 1:
        TRAIN_DATA_PATH = f"../slice/{DATASET_DIR}/refined_train.jsonl"
    else:
        TRAIN_DATA_PATH = f"../slice/{DATASET_DIR}/iteration{CURRENT_ITERATION-1}/refined_train.jsonl"
        
    VALID_DATA_PATH = f"../slice/{DATASET_DIR}/refined_valid.jsonl"
    TEST_DATA_PATH  = f"../slice/{DATASET_DIR}/refined_test.jsonl"
    
    BASE_OUTPUT_DIR = f"../slice/{DATASET_DIR}/ablation_5_complete"
    MODEL_SAVE_DIR  = f"{BASE_OUTPUT_DIR}/codebert"
    FN_OUTPUT_PATH  = f"{BASE_OUTPUT_DIR}/iteration{CURRENT_ITERATION}/valvul_nofind.jsonl"
    PRED_OUTPUT_PATH = f"{BASE_OUTPUT_DIR}/iteration{CURRENT_ITERATION}/val_predictions.jsonl"

    if not os.path.exists(TRAIN_DATA_PATH):
        print(f"[终止] 训练集未就绪: {TRAIN_DATA_PATH}")
        return

    tokenizer = AutoTokenizer.from_pretrained(MODEL_NAME)
    model = AutoModelForSequenceClassification.from_pretrained(MODEL_NAME, num_labels=2)
    train_dataset = VulnerabilityDataset(TRAIN_DATA_PATH, tokenizer)
    valid_dataset = VulnerabilityDataset(VALID_DATA_PATH, tokenizer)
    test_dataset  = VulnerabilityDataset(TEST_DATA_PATH, tokenizer)
    
    training_args = TrainingArguments(
        output_dir=MODEL_SAVE_DIR, learning_rate=LEARNING_RATE, 
        per_device_train_batch_size=BATCH_SIZE, per_device_eval_batch_size=BATCH_SIZE, 
        num_train_epochs=EPOCHS, weight_decay=0.01, 
        eval_strategy="epoch", save_strategy="epoch", 
        load_best_model_at_end=True, metric_for_best_model="f1", logging_steps=50, seed=42
    )
    
    print("[系统调度] 启动全组件闭环微调流水线 (动态损失 + 特征切片增强)...")
    trainer = CustomTrainer(
        model=model, args=training_args, train_dataset=train_dataset, 
        eval_dataset=valid_dataset, processing_class=tokenizer, 
        data_collator=DataCollatorWithPadding(tokenizer=tokenizer), compute_metrics=compute_metrics
    )
    trainer.train()
    
    print("\n[性能评估] 测试集指标计算中...")
    print(f"[测试集结果] {trainer.evaluate(test_dataset)}")
    extract_false_negatives(trainer, valid_dataset, VALID_DATA_PATH, FN_OUTPUT_PATH, PRED_OUTPUT_PATH)


if __name__ == "__main__":
    # 调度中心：通过取消对应函数的注释以激活对应的消融验证方案
    
    # run_ablation_1_raw_data()
    # run_ablation_2_no_data_aug()
    # run_ablation_3_no_feature_extract()
    run_ablation_4_no_loss_adapt()
    # run_ablation_5_complete_system()