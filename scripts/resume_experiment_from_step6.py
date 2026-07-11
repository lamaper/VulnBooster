from __future__ import annotations

import argparse
import json
from pathlib import Path

from vulnbooster.augmentation import CoTAugmenter, CWEAugmenter
from vulnbooster.codet5_slicer import predict_codet5_slices
from vulnbooster.config import load_experiment_config
from vulnbooster.env import load_local_env
from vulnbooster.merge import merge_jsonl
from vulnbooster.training import train_classifier
from vulnbooster.validation import filter_valid_samples
from vulnbooster.jsonl import iter_jsonl


def _count_rows(path: Path) -> int:
    return sum(1 for _ in iter_jsonl(path)) if path.exists() else 0


def _metric_subset(metrics: dict[str, float]) -> dict[str, float]:
    keep = ("eval_accuracy", "eval_precision", "eval_recall", "eval_f1", "eval_b_acc", "eval_mcc", "eval_loss")
    return {key: float(metrics[key]) for key in keep if key in metrics}


def main() -> None:
    parser = argparse.ArgumentParser(description="Resume a saved small-model augmentation experiment from detector training.")
    parser.add_argument("--config", default="configs/full.toml")
    parser.add_argument("--experiment-root", required=True)
    parser.add_argument("--slicer-backend", choices=["codet5"], default="codet5")
    parser.add_argument("--augmentation", choices=["cwe", "cot"], default="cwe")
    parser.add_argument("--detector-epochs", type=int, default=3)
    parser.add_argument("--detector-batch-size", type=int, default=16)
    parser.add_argument("--generate-k", type=int, default=3)
    parser.add_argument("--augmentation-detector-min-prob", type=float, default=0.45)
    parser.add_argument("--augmentation-min-quality-score", type=float, default=0.38)
    parser.add_argument("--augmentation-max-per-seed", type=int, default=1)
    parser.add_argument("--prompt-slice-min-static-precision", type=float, default=0.20)
    parser.add_argument("--prompt-slice-min-static-recall", type=float, default=0.30)
    parser.add_argument("--prompt-slice-max-ratio", type=float, default=0.65)
    parser.add_argument("--summary-name", default="summary_resume.json")
    args = parser.parse_args()

    load_local_env()
    config = load_experiment_config(args.config)
    config.training.epochs = args.detector_epochs
    config.training.batch_size = args.detector_batch_size
    config.augmentation.generate_k = args.generate_k

    output_root = Path(args.experiment_root).resolve()
    data_root = output_root / "data"
    teacher_root = output_root / "teacher"
    slicer_root = output_root / "codet5_slicer"
    baseline_root = output_root / "baseline_detector"
    aug_root = output_root / "augmentation"
    augmented_root = output_root / "augmented_detector"

    print("[resume 1/5] Training baseline detector")
    baseline_result = train_classifier(
        config=config,
        train_path=data_root / "cleaned" / "primevul_train_cleaned.jsonl",
        valid_path=data_root / "cleaned" / "primevul_valid_cleaned.jsonl",
        test_path=data_root / "cleaned" / "primevul_test_cleaned.jsonl",
        output_dir=baseline_root / "model",
        false_negative_path=baseline_root / "valid_false_negatives.jsonl",
        prediction_path=baseline_root / "valid_predictions.jsonl",
        target_key="func",
    )

    print("[resume 2/5] Predicting FN slices with CodeT5")
    fn_line_slice_path = slicer_root / "valid_false_negatives_line_slice.jsonl"
    fn_slice_stats = predict_codet5_slices(
        config=config,
        input_path=baseline_root / "valid_false_negatives.jsonl",
        model_dir=slicer_root / "model",
        output_path=fn_line_slice_path,
        metadata_paths=[
            slicer_root / "valid_line_labels.jsonl",
            teacher_root / "valid" / "valid_refined.jsonl",
            teacher_root / "valid" / "valid_static.jsonl",
        ],
    )

    print("[resume 3/5] Generating and validating augmentations")
    aug_root.mkdir(parents=True, exist_ok=True)
    generated_path = aug_root / "generated.jsonl"
    validated_path = aug_root / "validated.jsonl"
    merged_train_path = aug_root / "train_augmented.jsonl"

    if args.augmentation == "cwe":
        generator = CWEAugmenter(config)
    else:
        generator = CoTAugmenter(config)
    generation_stats = generator.run(fn_line_slice_path, generated_path)
    validation_stats = filter_valid_samples(
        generated_path,
        validated_path,
        config=config,
        detector_model_dir=baseline_root / "model",
        detector_min_prob=args.augmentation_detector_min_prob,
        min_seed_alignment=0.0,
        min_prompt_alignment=0.0,
        min_quality_score=args.augmentation_min_quality_score,
        max_per_seed=args.augmentation_max_per_seed,
        min_anchor_identifier_hits=config.augmentation.min_identifier_anchor_hits,
        min_anchor_call_hits=config.augmentation.min_call_anchor_hits,
        require_anchor_signal=config.augmentation.require_anchor_signal,
        min_novel_line_count=config.augmentation.min_novel_line_count,
        min_novel_line_ratio=config.augmentation.min_novel_line_ratio,
        min_structural_novel_line_count=config.augmentation.min_structural_novel_line_count,
        max_abstract_token_similarity=config.augmentation.max_abstract_token_similarity,
        reject_trivial_variants=config.augmentation.reject_trivial_variants,
        min_prompt_slice_static_precision=args.prompt_slice_min_static_precision,
        min_prompt_slice_static_recall=args.prompt_slice_min_static_recall,
        max_prompt_slice_ratio=args.prompt_slice_max_ratio,
    )
    merge_stats = merge_jsonl(
        [data_root / "cleaned" / "primevul_train_cleaned.jsonl", validated_path],
        merged_train_path,
    )

    print("[resume 4/5] Training augmented detector")
    augmented_result = train_classifier(
        config=config,
        train_path=merged_train_path,
        valid_path=data_root / "cleaned" / "primevul_valid_cleaned.jsonl",
        test_path=data_root / "cleaned" / "primevul_test_cleaned.jsonl",
        output_dir=augmented_root / "model",
        false_negative_path=augmented_root / "valid_false_negatives.jsonl",
        prediction_path=augmented_root / "valid_predictions.jsonl",
        target_key="func",
    )

    print("[resume 5/5] Writing summary")
    baseline_metrics = _metric_subset(baseline_result.test_metrics)
    augmented_metrics = _metric_subset(augmented_result.test_metrics)
    gains = {
        key: augmented_metrics[key] - baseline_metrics[key]
        for key in baseline_metrics.keys()
        if key in augmented_metrics
    }
    summary = {
        "baseline_detector": {
            "test_metrics": baseline_metrics,
            "false_negative_count": baseline_result.false_negative_count,
        },
        "fn_line_slices": fn_slice_stats,
        "augmentation": {
            "generation": generation_stats,
            "validation": validation_stats,
            "merge": merge_stats,
            "validated_rows": _count_rows(validated_path),
            "merged_train_rows": _count_rows(merged_train_path),
        },
        "augmented_detector": {
            "test_metrics": augmented_metrics,
            "false_negative_count": augmented_result.false_negative_count,
        },
        "gains": gains,
    }
    summary_path = output_root / args.summary_name
    summary_path.write_text(json.dumps(summary, ensure_ascii=False, indent=2), encoding="utf-8")
    print(json.dumps(summary, ensure_ascii=False, indent=2))
    print(f"summary saved to: {summary_path}")


if __name__ == "__main__":
    main()
