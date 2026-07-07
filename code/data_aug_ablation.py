# -*- coding: utf-8 -*-
"""
基于特征切片 (VRR-SRR) 的漏洞二分类模型消融实验脚本

目标模块：漏洞数据增强方案内的消融实验

核心特性：
1. 涵盖漏洞数据增强方案内的 4 组消融实验配置。
2. 默认挂载 CustomTrainer 动态损失函数，确保仅对“增强策略”进行单一变量控制。

实验配置说明：
- (1) 移除漏洞数据增强方案: 仅使用特征提取后的基础精炼数据，不引入任何迭代变体。
- (2) 移除 CWE Prompt 模板: 仅保留 CoT 推理生成的增强样本。
- (3) 移除 CoT 推理: 仅保留基于 CWE 知识模板生成的增强样本。
- (4) 完整系统 (Ours): 融合 CWE 知识引导与 CoT 逻辑推理的双轨增强样本。
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
# 共享模块 1：动态损失函数 (控制变量：始终保持开启)
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
    def __init__(self, file_path, tokenizer, target_key='refined_code', max_length=512):
        self.data = []
        if not os.path.exists(file_path):
            print(f"[Warning] 数据集文件未找到，将返回空数据集: {file_path}")
            return
            
        with open(file_path, 'r', encoding='utf-8') as f:
            for line in f:
                if not line.strip():
                    continue
                try:
                    obj = json.loads(line)
                    if target_key == 'code_lines':
                        code_list = obj.get('code_lines', [])
                        code = '\n'.join(code_list) if isinstance(code_list, list) else str(code_list)
                    else:
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
    执行模型推理，分离并导出被错误预测为安全的漏报样本 (False Negatives)。
    为后续数据增强模块提供目标样本。
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
# 消融实验配置：漏洞数据增强模块内
# ============================================================

# --- Ablation 1: 移除漏洞数据增强方案 (仅使用基础精炼特征，无增强数据) ---
def run_data_aug_ablation_1_no_aug():
    print(f"\n{'='*60}\n[环境初始化] 数据增强消融实验 (1): 移除增强方案 (仅使用基础精炼特征)")
    print(f"当前运行模式: {RUN_MODE.upper()} | 迭代轮次: {CURRENT_ITERATION} | Epochs: {EPOCHS}\n{'='*60}")
    
    # 因为是不增强，所以始终使用未经迭代的精炼数据
    TRAIN_DATA_PATH = f"../slice/{DATASET_DIR}/refined_train.jsonl" 
    VALID_DATA_PATH = f"../slice/{DATASET_DIR}/refined_valid.jsonl"
    TEST_DATA_PATH  = f"../slice/{DATASET_DIR}/refined_test.jsonl"
    
    BASE_OUTPUT_DIR = f"../slice/{DATASET_DIR}/data_aug_ablation_1_no_aug"
    MODEL_SAVE_DIR  = f"{BASE_OUTPUT_DIR}/codebert"
    FN_OUTPUT_PATH  = f"{BASE_OUTPUT_DIR}/iteration{CURRENT_ITERATION}/valvul_nofind.jsonl"
    PRED_OUTPUT_PATH = f"{BASE_OUTPUT_DIR}/iteration{CURRENT_ITERATION}/val_predictions.jsonl"

    if not os.path.exists(TRAIN_DATA_PATH):
        print(f"[Error] 训练集未就绪，流程终止: {TRAIN_DATA_PATH}")
        return

    print("[Info] 初始化 CodeBERT 预训练模型...")
    tokenizer = AutoTokenizer.from_pretrained(MODEL_NAME)
    model = AutoModelForSequenceClassification.from_pretrained(MODEL_NAME, num_labels=2)
    
    train_dataset = VulnerabilityDataset(TRAIN_DATA_PATH, tokenizer, target_key='refined_code')
    valid_dataset = VulnerabilityDataset(VALID_DATA_PATH, tokenizer, target_key='refined_code')
    test_dataset  = VulnerabilityDataset(TEST_DATA_PATH, tokenizer, target_key='refined_code')

    training_args = TrainingArguments(
        output_dir=MODEL_SAVE_DIR, learning_rate=LEARNING_RATE, 
        per_device_train_batch_size=BATCH_SIZE, per_device_eval_batch_size=BATCH_SIZE, 
        num_train_epochs=EPOCHS, weight_decay=0.01, 
        eval_strategy="epoch", save_strategy="epoch", 
        load_best_model_at_end=True, metric_for_best_model="f1", logging_steps=50, seed=42
    )
    
    print("[Task] 启动动态损失微调流水线 (基准源: 基础精炼特征，无增强)...")
    trainer = CustomTrainer(
        model=model, args=training_args, train_dataset=train_dataset, 
        eval_dataset=valid_dataset, processing_class=tokenizer, 
        data_collator=DataCollatorWithPadding(tokenizer=tokenizer), compute_metrics=compute_metrics
    )
    trainer.train()
    
    print("\n[性能评估] 测试集指标计算中...")
    print(f"[测试集评估结果] {trainer.evaluate(test_dataset)}")
    extract_false_negatives(trainer, valid_dataset, VALID_DATA_PATH, FN_OUTPUT_PATH, PRED_OUTPUT_PATH)


# --- Ablation 2: 移除 CWE Prompt 模板 (仅保留 CoT 推理增强) ---
def run_data_aug_ablation_2_no_cwe():
    print(f"\n{'='*60}\n[环境初始化] 数据增强消融实验 (2): 移除 CWE 知识引导 (仅保留 CoT 推理增强)")
    print(f"当前运行模式: {RUN_MODE.upper()} | 迭代轮次: {CURRENT_ITERATION} | Epochs: {EPOCHS}\n{'='*60}")
    
    # 挂载专为该消融任务合成的单路增强数据集 (Base + Only CoT)
    TRAIN_DATA_PATH = f"../slice/{DATASET_DIR}/data_aug_ablation_2_no_cwe/iteration{CURRENT_ITERATION}/refined_train_only_cot.jsonl"
    VALID_DATA_PATH = f"../slice/{DATASET_DIR}/refined_valid.jsonl"
    TEST_DATA_PATH  = f"../slice/{DATASET_DIR}/refined_test.jsonl"
    
    BASE_OUTPUT_DIR = f"../slice/{DATASET_DIR}/data_aug_ablation_2_no_cwe"
    MODEL_SAVE_DIR  = f"{BASE_OUTPUT_DIR}/codebert"
    FN_OUTPUT_PATH  = f"{BASE_OUTPUT_DIR}/iteration{CURRENT_ITERATION}/valvul_nofind.jsonl"
    PRED_OUTPUT_PATH = f"{BASE_OUTPUT_DIR}/iteration{CURRENT_ITERATION}/val_predictions.jsonl"

    if not os.path.exists(TRAIN_DATA_PATH):
        print(f"[Error] 训练集未就绪，请核对前置合并脚本产出路径: {TRAIN_DATA_PATH}")
        return

    print("[Info] 初始化 CodeBERT 预训练模型...")
    tokenizer = AutoTokenizer.from_pretrained(MODEL_NAME)
    model = AutoModelForSequenceClassification.from_pretrained(MODEL_NAME, num_labels=2)

    train_dataset = VulnerabilityDataset(TRAIN_DATA_PATH, tokenizer, target_key='refined_code')
    valid_dataset = VulnerabilityDataset(VALID_DATA_PATH, tokenizer, target_key='refined_code')
    test_dataset  = VulnerabilityDataset(TEST_DATA_PATH, tokenizer, target_key='refined_code')

    train_labels = [item["label"] for item in train_dataset.data]
    label_counts = Counter(train_labels)
    print(f"[Info] 数据分布 -> 训练集总量: {len(train_dataset)} | 类别比例: {dict(label_counts)}")

    training_args = TrainingArguments(
        output_dir=MODEL_SAVE_DIR, learning_rate=LEARNING_RATE, 
        per_device_train_batch_size=BATCH_SIZE, per_device_eval_batch_size=BATCH_SIZE, 
        num_train_epochs=EPOCHS, weight_decay=0.01, 
        eval_strategy="epoch", save_strategy="epoch", 
        load_best_model_at_end=True, metric_for_best_model="f1", logging_steps=50, seed=42
    )

    print("[Task] 启动动态损失微调流水线 (基准源: 基础精炼特征 + CoT单向变体)...")
    trainer = CustomTrainer(
        model=model, args=training_args, train_dataset=train_dataset, 
        eval_dataset=valid_dataset, processing_class=tokenizer, 
        data_collator=DataCollatorWithPadding(tokenizer=tokenizer), compute_metrics=compute_metrics
    )
    trainer.train()

    print("\n[性能评估] 测试集指标计算中...")
    print(f"[测试集评估结果] {trainer.evaluate(test_dataset)}")
    extract_false_negatives(trainer, valid_dataset, VALID_DATA_PATH, FN_OUTPUT_PATH, PRED_OUTPUT_PATH)


# --- Ablation 3: 移除 CoT 推理 (仅保留 CWE Prompt 增强) ---
def run_data_aug_ablation_3_no_cot():
    print(f"\n{'='*60}\n[环境初始化] 数据增强消融实验 (3): 移除 CoT 推理 (仅保留 CWE 模板增强)")
    print(f"当前运行模式: {RUN_MODE.upper()} | 迭代轮次: {CURRENT_ITERATION} | Epochs: {EPOCHS}\n{'='*60}")
    
    TRAIN_DATA_PATH = f"../slice/{DATASET_DIR}/data_aug_ablation_3_no_cot/iteration{CURRENT_ITERATION}/refined_train_only_cwe.jsonl"
    VALID_DATA_PATH = f"../slice/{DATASET_DIR}/refined_valid.jsonl"
    TEST_DATA_PATH  = f"../slice/{DATASET_DIR}/refined_test.jsonl"
    
    BASE_OUTPUT_DIR = f"../slice/{DATASET_DIR}/data_aug_ablation_3_no_cot"
    MODEL_SAVE_DIR  = f"{BASE_OUTPUT_DIR}/codebert"
    FN_OUTPUT_PATH  = f"{BASE_OUTPUT_DIR}/iteration{CURRENT_ITERATION}/valvul_nofind.jsonl"
    PRED_OUTPUT_PATH = f"{BASE_OUTPUT_DIR}/iteration{CURRENT_ITERATION}/val_predictions.jsonl"

    if not os.path.exists(TRAIN_DATA_PATH):
        print(f"[Error] 训练集未就绪，请核对前置合并脚本产出路径: {TRAIN_DATA_PATH}")
        return

    print("[Info] 初始化 CodeBERT 预训练模型...")
    tokenizer = AutoTokenizer.from_pretrained(MODEL_NAME)
    model = AutoModelForSequenceClassification.from_pretrained(MODEL_NAME, num_labels=2)
    
    train_dataset = VulnerabilityDataset(TRAIN_DATA_PATH, tokenizer, target_key='refined_code')
    valid_dataset = VulnerabilityDataset(VALID_DATA_PATH, tokenizer, target_key='refined_code')
    test_dataset  = VulnerabilityDataset(TEST_DATA_PATH, tokenizer, target_key='refined_code')

    training_args = TrainingArguments(
        output_dir=MODEL_SAVE_DIR, learning_rate=LEARNING_RATE, 
        per_device_train_batch_size=BATCH_SIZE, per_device_eval_batch_size=BATCH_SIZE, 
        num_train_epochs=EPOCHS, weight_decay=0.01, 
        eval_strategy="epoch", save_strategy="epoch", 
        load_best_model_at_end=True, metric_for_best_model="f1", logging_steps=50, seed=42
    )
    
    print("[Task] 启动动态损失微调流水线 (基准源: 基础精炼特征 + CWE单向变体)...")
    trainer = CustomTrainer(
        model=model, args=training_args, train_dataset=train_dataset, 
        eval_dataset=valid_dataset, processing_class=tokenizer, 
        data_collator=DataCollatorWithPadding(tokenizer=tokenizer), compute_metrics=compute_metrics
    )
    trainer.train()
    
    print("\n[性能评估] 测试集指标计算中...")
    print(f"[测试集评估结果] {trainer.evaluate(test_dataset)}")
    extract_false_negatives(trainer, valid_dataset, VALID_DATA_PATH, FN_OUTPUT_PATH, PRED_OUTPUT_PATH)


# --- Ablation 4: 完整系统 (Ours) (双轨协同增强策略) ---
def run_data_aug_ablation_4_complete():
    print(f"\n{'='*60}\n[环境初始化] 数据增强消融实验 (4): 完整系统 (双轨协同增强)")
    print(f"当前运行模式: {RUN_MODE.upper()} | 迭代轮次: {CURRENT_ITERATION} | Epochs: {EPOCHS}\n{'='*60}")
    
    TRAIN_DATA_PATH = f"../slice/{DATASET_DIR}/iteration{CURRENT_ITERATION}/refined_train.jsonl"
    VALID_DATA_PATH = f"../slice/{DATASET_DIR}/refined_valid.jsonl"
    TEST_DATA_PATH  = f"../slice/{DATASET_DIR}/refined_test.jsonl"
    
    BASE_OUTPUT_DIR = f"../slice/{DATASET_DIR}/data_aug_ablation_4_complete"
    MODEL_SAVE_DIR  = f"{BASE_OUTPUT_DIR}/codebert"
    FN_OUTPUT_PATH  = f"{BASE_OUTPUT_DIR}/iteration{CURRENT_ITERATION}/valvul_nofind.jsonl"
    PRED_OUTPUT_PATH = f"{BASE_OUTPUT_DIR}/iteration{CURRENT_ITERATION}/val_predictions.jsonl"

    if not os.path.exists(TRAIN_DATA_PATH):
        print(f"[Error] 训练集未就绪，流程终止: {TRAIN_DATA_PATH}")
        return

    print("[Info] 初始化 CodeBERT 预训练模型...")
    tokenizer = AutoTokenizer.from_pretrained(MODEL_NAME)
    model = AutoModelForSequenceClassification.from_pretrained(MODEL_NAME, num_labels=2)
    
    train_dataset = VulnerabilityDataset(TRAIN_DATA_PATH, tokenizer, target_key='refined_code')
    valid_dataset = VulnerabilityDataset(VALID_DATA_PATH, tokenizer, target_key='refined_code')
    test_dataset  = VulnerabilityDataset(TEST_DATA_PATH, tokenizer, target_key='refined_code')

    training_args = TrainingArguments(
        output_dir=MODEL_SAVE_DIR, learning_rate=LEARNING_RATE, 
        per_device_train_batch_size=BATCH_SIZE, per_device_eval_batch_size=BATCH_SIZE, 
        num_train_epochs=EPOCHS, weight_decay=0.01, 
        eval_strategy="epoch", save_strategy="epoch", 
        load_best_model_at_end=True, metric_for_best_model="f1", logging_steps=50, seed=42
    )
    
    print("[Task] 启动动态损失微调流水线 (基准源: 基础精炼特征 + 协同双向变体)...")
    trainer = CustomTrainer(
        model=model, args=training_args, train_dataset=train_dataset, 
        eval_dataset=valid_dataset, processing_class=tokenizer, 
        data_collator=DataCollatorWithPadding(tokenizer=tokenizer), compute_metrics=compute_metrics
    )
    trainer.train()
    
    print("\n[性能评估] 测试集指标计算中...")
    print(f"[测试集评估结果] {trainer.evaluate(test_dataset)}")
    extract_false_negatives(trainer, valid_dataset, VALID_DATA_PATH, FN_OUTPUT_PATH, PRED_OUTPUT_PATH)


if __name__ == "__main__":
    # 调度中心：通过取消对应函数的注释以激活对应的消融验证方案
    
    # run_data_aug_ablation_1_no_aug()
    run_data_aug_ablation_2_no_cwe()
    # run_data_aug_ablation_3_no_cot()
    # run_data_aug_ablation_4_complete()