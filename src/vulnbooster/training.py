from __future__ import annotations

import json
from collections import Counter
from dataclasses import dataclass
from pathlib import Path

import torch
import torch.nn as nn
import torch.nn.functional as F
from sklearn.metrics import accuracy_score, balanced_accuracy_score, matthews_corrcoef, precision_recall_fscore_support
from torch.utils.data import Dataset
from tqdm import tqdm
from transformers import AutoModelForSequenceClassification, AutoTokenizer, DataCollatorWithPadding, Trainer, TrainingArguments

from .config import ExperimentConfig
from .env import configure_hf_endpoint
from .jsonl import iter_jsonl


@dataclass(slots=True)
class TrainingResult:
    test_metrics: dict[str, float]
    false_negative_count: int
    false_negative_path: Path
    prediction_path: Path


class LinearCombinationLoss(nn.Module):
    def __init__(self, config: ExperimentConfig, lambda_fl: float, lambda_ls: float):
        super().__init__()
        self.config = config
        self.lambda_fl = lambda_fl
        self.lambda_ls = lambda_ls

    def forward(self, inputs, targets):
        ce_loss = F.cross_entropy(inputs, targets, reduction="none")
        pt = torch.exp(-ce_loss)
        alpha_t = torch.where(targets == 1, self.config.loss.focal_alpha, 1.0 - self.config.loss.focal_alpha)
        focal_loss = alpha_t * (1 - pt) ** self.config.loss.focal_gamma * ce_loss
        smooth_loss = -F.log_softmax(inputs, dim=-1).mean(dim=-1)
        ls_ce_loss = (1.0 - self.config.loss.label_smoothing) * ce_loss + self.config.loss.label_smoothing * smooth_loss
        return (self.lambda_fl * focal_loss + self.lambda_ls * ls_ce_loss).mean()


class CodeDataset(Dataset):
    def __init__(self, file_path: Path, tokenizer, max_length: int, target_key: str):
        self.data = []
        self.tokenizer = tokenizer
        self.max_length = max_length
        for row in iter_jsonl(file_path):
            code = row.get(target_key) or row.get("refined_code") or row.get("llm_slice") or row.get("func") or ""
            target = row.get("target")
            if code and target is not None:
                self.data.append({"code": code, "label": int(target)})

    def __len__(self):
        return len(self.data)

    def __getitem__(self, index):
        item = self.data[index]
        encoding = self.tokenizer(
            item["code"],
            truncation=True,
            padding="max_length",
            max_length=self.max_length,
            return_tensors="pt",
        )
        return {
            "input_ids": encoding["input_ids"].squeeze(0),
            "attention_mask": encoding["attention_mask"].squeeze(0),
            "labels": torch.tensor(item["label"], dtype=torch.long),
        }


class DynamicLossTrainer(Trainer):
    def __init__(self, experiment_config: ExperimentConfig, *args, **kwargs):
        super().__init__(*args, **kwargs)
        self.experiment_config = experiment_config

    def compute_loss(self, model, inputs, return_outputs=False, **kwargs):
        labels = inputs.get("labels")
        outputs = model(**inputs)
        logits = outputs.get("logits")

        epoch = int(self.state.epoch) if self.state.epoch is not None else 0
        lambda_fl = max(
            self.experiment_config.loss.focal_lambda_min,
            self.experiment_config.loss.focal_lambda_start - self.experiment_config.loss.focal_lambda_decay * epoch,
        )
        lambda_ls = 1.0 - lambda_fl
        loss = LinearCombinationLoss(self.experiment_config, lambda_fl=lambda_fl, lambda_ls=lambda_ls)(
            logits.view(-1, self.model.config.num_labels),
            labels.view(-1),
        )
        return (loss, outputs) if return_outputs else loss


def compute_metrics(threshold: float):
    def _inner(eval_pred):
        logits, labels = eval_pred
        probs = torch.softmax(torch.tensor(logits), dim=-1).numpy()
        preds = (probs[:, 1] >= threshold).astype(int)
        precision, recall, f1, _ = precision_recall_fscore_support(labels, preds, average="binary", zero_division=0)
        return {
            "accuracy": accuracy_score(labels, preds),
            "precision": precision,
            "recall": recall,
            "f1": f1,
            "b_acc": balanced_accuracy_score(labels, preds),
            "mcc": matthews_corrcoef(labels, preds),
        }

    return _inner


def load_cached_tokenizer(model_name_or_path: str):
    def _load(local_files_only: bool, use_fast: bool | None = None):
        kwargs = {"local_files_only": local_files_only}
        if use_fast is not None:
            kwargs["use_fast"] = use_fast
        return AutoTokenizer.from_pretrained(model_name_or_path, **kwargs)

    try:
        return _load(local_files_only=True)
    except OSError:
        pass
    except (TypeError, ValueError, Exception) as exc:
        message = str(exc).lower()
        if "addedtoken" not in message and "backend tokenizer" not in message and "modelwrapper" not in message:
            raise
        try:
            return _load(local_files_only=True, use_fast=False)
        except OSError:
            return _load(local_files_only=False, use_fast=False)

    try:
        return _load(local_files_only=False)
    except (TypeError, ValueError, Exception) as exc:
        message = str(exc).lower()
        if "addedtoken" not in message and "backend tokenizer" not in message and "modelwrapper" not in message:
            raise
        return _load(local_files_only=False, use_fast=False)


def load_cached_sequence_classifier(model_name_or_path: str, num_labels: int):
    try:
        return AutoModelForSequenceClassification.from_pretrained(
            model_name_or_path,
            num_labels=num_labels,
            local_files_only=True,
        )
    except OSError:
        return AutoModelForSequenceClassification.from_pretrained(model_name_or_path, num_labels=num_labels)


def train_classifier(
    config: ExperimentConfig,
    train_path: Path,
    valid_path: Path,
    test_path: Path,
    output_dir: Path,
    false_negative_path: Path,
    prediction_path: Path,
    target_key: str = "refined_code",
) -> TrainingResult:
    configure_hf_endpoint(config.runtime.hf_endpoint)

    tokenizer = load_cached_tokenizer(config.training.model_name)
    model = load_cached_sequence_classifier(config.training.model_name, num_labels=2)

    train_dataset = CodeDataset(train_path, tokenizer, config.training.max_length, target_key)
    valid_dataset = CodeDataset(valid_path, tokenizer, config.training.max_length, target_key)
    test_dataset = CodeDataset(test_path, tokenizer, config.training.max_length, target_key)

    label_counts = Counter(item["label"] for item in train_dataset.data)
    print(f"Training set size: {len(train_dataset)} | label counts: {dict(label_counts)}")

    training_args = TrainingArguments(
        output_dir=str(output_dir),
        learning_rate=config.training.learning_rate,
        per_device_train_batch_size=config.training.batch_size,
        per_device_eval_batch_size=config.training.batch_size,
        num_train_epochs=config.training.epochs,
        weight_decay=config.training.weight_decay,
        eval_strategy="epoch",
        save_strategy="epoch",
        load_best_model_at_end=True,
        metric_for_best_model="f1",
        logging_steps=50,
        seed=config.training.seed,
        dataloader_pin_memory=torch.cuda.is_available(),
        report_to=[],
        save_total_limit=2,
    )

    trainer = DynamicLossTrainer(
        config,
        model=model,
        args=training_args,
        train_dataset=train_dataset,
        eval_dataset=valid_dataset,
        tokenizer=tokenizer,
        data_collator=DataCollatorWithPadding(tokenizer=tokenizer),
        compute_metrics=compute_metrics(config.training.prediction_threshold),
    )
    trainer.train()
    output_dir.mkdir(parents=True, exist_ok=True)
    trainer.save_model(str(output_dir))
    tokenizer.save_pretrained(output_dir)

    test_metrics = trainer.evaluate(test_dataset)

    prediction_path.parent.mkdir(parents=True, exist_ok=True)
    false_negative_path.parent.mkdir(parents=True, exist_ok=True)

    valid_rows = list(iter_jsonl(valid_path))
    probs = torch.softmax(torch.tensor(trainer.predict(valid_dataset).predictions), dim=-1).numpy()
    preds = (probs[:, 1] >= config.training.prediction_threshold).astype(int)

    false_negative_count = 0
    with prediction_path.open("w", encoding="utf-8") as safe_out, false_negative_path.open("w", encoding="utf-8") as fn_out:
        for i, row in tqdm(enumerate(valid_rows), total=len(valid_rows), desc="Extract False Negatives", unit="sample"):
            row.update(
                {
                    "pred_label": int(preds[i]),
                    "pred_prob_0": float(probs[i][0]),
                    "pred_prob_1": float(probs[i][1]),
                }
            )
            if row["target"] == 1 and row["pred_label"] == 0:
                fn_out.write(json.dumps(row, ensure_ascii=False) + "\n")
                false_negative_count += 1
            else:
                safe_out.write(json.dumps(row, ensure_ascii=False) + "\n")

    return TrainingResult(
        test_metrics=test_metrics,
        false_negative_count=false_negative_count,
        false_negative_path=false_negative_path,
        prediction_path=prediction_path,
    )
