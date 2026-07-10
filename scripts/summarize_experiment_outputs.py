from __future__ import annotations

import argparse
import json
from pathlib import Path

from transformers import DataCollatorWithPadding, Trainer

from vulnbooster.config import load_experiment_config
from vulnbooster.jsonl import iter_jsonl
from vulnbooster.training import CodeDataset, compute_metrics, load_cached_sequence_classifier, load_cached_tokenizer


def evaluate_detector(config_path: str, model_dir: Path, test_path: Path, target_key: str) -> dict[str, float]:
    config = load_experiment_config(config_path)
    tokenizer = load_cached_tokenizer(str(model_dir))
    model = load_cached_sequence_classifier(str(model_dir), num_labels=2)
    dataset = CodeDataset(test_path, tokenizer, config.training.max_length, target_key)
    trainer = Trainer(
        model=model,
        processing_class=tokenizer,
        data_collator=DataCollatorWithPadding(tokenizer=tokenizer),
        compute_metrics=compute_metrics(config.training.prediction_threshold),
    )
    metrics = trainer.evaluate(dataset)
    keep = ("eval_loss", "eval_accuracy", "eval_precision", "eval_recall", "eval_f1", "eval_b_acc", "eval_mcc")
    return {key: float(metrics[key]) for key in keep if key in metrics}


def count_rows(path: Path) -> int:
    return sum(1 for _ in iter_jsonl(path)) if path.exists() else 0


def main() -> None:
    parser = argparse.ArgumentParser(description="Summarize saved VulnBooster experiment outputs.")
    parser.add_argument("--config", default="configs/full.toml")
    parser.add_argument("--experiment-root", required=True)
    parser.add_argument("--target-key", default="func")
    args = parser.parse_args()

    root = Path(args.experiment_root).resolve()
    test_path = root / "data" / "cleaned" / "primevul_test_cleaned.jsonl"
    baseline_metrics = evaluate_detector(args.config, root / "baseline_detector" / "model", test_path, args.target_key)
    augmented_metrics = evaluate_detector(args.config, root / "augmented_detector" / "model", test_path, args.target_key)

    payload = {
        "baseline_test_metrics": baseline_metrics,
        "augmented_test_metrics": augmented_metrics,
        "baseline_false_negatives": count_rows(root / "baseline_detector" / "valid_false_negatives.jsonl"),
        "augmented_false_negatives": count_rows(root / "augmented_detector" / "valid_false_negatives.jsonl"),
        "generated_total": count_rows(root / "augmentation" / "generated.jsonl"),
        "validated_total": count_rows(root / "augmentation" / "validated.jsonl"),
        "merged_train_total": count_rows(root / "augmentation" / "train_augmented.jsonl"),
        "gains": {
            key: augmented_metrics[key] - baseline_metrics[key]
            for key in baseline_metrics.keys()
            if key in augmented_metrics
        },
    }
    print(json.dumps(payload, ensure_ascii=False, indent=2))


if __name__ == "__main__":
    main()
