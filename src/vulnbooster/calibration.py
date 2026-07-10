from __future__ import annotations

from pathlib import Path

import numpy as np
import torch
from sklearn.metrics import accuracy_score, balanced_accuracy_score, matthews_corrcoef, precision_recall_fscore_support

from .config import ExperimentConfig
from .training import CodeDataset, load_cached_sequence_classifier, load_cached_tokenizer


def compute_binary_metrics(labels: np.ndarray, probs: np.ndarray, threshold: float) -> dict[str, float]:
    preds = (probs >= threshold).astype(int)
    precision, recall, f1, _ = precision_recall_fscore_support(labels, preds, average="binary", zero_division=0)
    return {
        "threshold": float(threshold),
        "accuracy": float(accuracy_score(labels, preds)),
        "precision": float(precision),
        "recall": float(recall),
        "f1": float(f1),
        "b_acc": float(balanced_accuracy_score(labels, preds)),
        "mcc": float(matthews_corrcoef(labels, preds)),
    }


def select_best_threshold(
    labels: np.ndarray,
    probs: np.ndarray,
    *,
    objective: str = "mcc",
    threshold_min: float = 0.3,
    threshold_max: float = 0.8,
    num_thresholds: int = 51,
) -> dict[str, float]:
    thresholds = np.linspace(threshold_min, threshold_max, num_thresholds)
    metrics = [compute_binary_metrics(labels, probs, float(threshold)) for threshold in thresholds]
    if objective == "precision":
        key = lambda row: (row["precision"], row["mcc"], row["f1"])
    elif objective == "f1":
        key = lambda row: (row["f1"], row["mcc"], row["precision"])
    else:
        key = lambda row: (row["mcc"], row["precision"], row["f1"])
    return max(metrics, key=key)


def predict_classifier_probabilities(
    config: ExperimentConfig,
    model_dir: Path,
    data_path: Path,
    *,
    target_key: str = "func",
    batch_size: int | None = None,
) -> tuple[np.ndarray, np.ndarray]:
    tokenizer = load_cached_tokenizer(str(model_dir))
    model = load_cached_sequence_classifier(str(model_dir), num_labels=2)
    dataset = CodeDataset(data_path, tokenizer, config.training.max_length, target_key)

    device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
    model.to(device)
    model.eval()

    labels = np.array([int(item["label"]) for item in dataset.data], dtype=np.int64)
    probabilities: list[float] = []
    effective_batch_size = batch_size or max(1, min(config.training.batch_size, 32))
    for start in range(0, len(dataset.data), effective_batch_size):
        batch_codes = [
            dataset.data[index]["code"]
            for index in range(start, min(start + effective_batch_size, len(dataset.data)))
        ]
        encoding = tokenizer(
            batch_codes,
            truncation=True,
            padding=True,
            max_length=config.training.max_length,
            return_tensors="pt",
        )
        encoding = {key: value.to(device) for key, value in encoding.items()}
        with torch.no_grad():
            logits = model(**encoding).logits
            batch_probs = torch.softmax(logits, dim=-1)[:, 1].detach().cpu().numpy().tolist()
        probabilities.extend(float(value) for value in batch_probs)

    return labels, np.array(probabilities, dtype=np.float32)
