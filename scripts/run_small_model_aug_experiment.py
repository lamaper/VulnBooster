from __future__ import annotations

import argparse
import json
from pathlib import Path
from typing import Any

def _count_rows(path: Path) -> int:
    from vulnbooster.jsonl import iter_jsonl

    return sum(1 for _ in iter_jsonl(path)) if path.exists() else 0


def _write_summary(path: Path, payload: dict[str, Any]) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(json.dumps(payload, ensure_ascii=False, indent=2), encoding="utf-8")


def _sample_subset(root_dir: Path, output_dir: Path, split: str, per_class: int, seed: int) -> dict[str, int]:
    from vulnbooster.sampling import build_balanced_smoke_set

    input_path = root_dir / "dataset" / f"primevul_{split}.jsonl"
    output_path = output_dir / "raw" / f"primevul_{split}.jsonl"
    return build_balanced_smoke_set(input_path=input_path, output_path=output_path, seed=seed, num_per_class=per_class)


def _clean_split(raw_path: Path, cleaned_path: Path) -> dict[str, int]:
    from vulnbooster.cleaning import clean_dataset

    return clean_dataset(raw_path, cleaned_path)


def _slice_split(config, cleaned_path: Path, split_root: Path, output_name: str) -> dict[str, int]:
    from vulnbooster.static_slice import JoernSlicer

    slicer = JoernSlicer(config)
    source_dir = split_root / "source"
    cpg_dir = split_root / "cpg"
    output_path = split_root / output_name
    return slicer.slice_dataset(cleaned_path, source_dir, cpg_dir, output_path)


def _metric_subset(metrics: dict[str, float]) -> dict[str, float]:
    keep = ("eval_accuracy", "eval_precision", "eval_recall", "eval_f1", "eval_b_acc", "eval_mcc", "eval_loss")
    return {key: float(metrics[key]) for key in keep if key in metrics}


def main() -> None:
    parser = argparse.ArgumentParser(description="Run a reusable line-slicer-guided augmentation experiment.")
    parser.add_argument("--config", default="configs/full.toml")
    parser.add_argument("--output-root", required=True)
    parser.add_argument("--train-per-class", type=int, default=100)
    parser.add_argument("--valid-per-class", type=int, default=40)
    parser.add_argument("--test-per-class", type=int, default=40)
    parser.add_argument("--seed", type=int, default=42)
    parser.add_argument("--line-slicer-epochs", type=int, default=3)
    parser.add_argument("--detector-epochs", type=int, default=3)
    parser.add_argument("--line-slicer-batch-size", type=int, default=4)
    parser.add_argument("--detector-batch-size", type=int, default=16)
    parser.add_argument("--llm-concurrency", type=int, default=8)
    parser.add_argument("--augmentation", choices=["cwe", "cot"], default="cwe")
    parser.add_argument("--generate-k", type=int, default=3)
    parser.add_argument("--augmentation-detector-min-prob", type=float, default=0.55)
    parser.add_argument("--augmentation-seed-min-alignment", type=float, default=0.2)
    parser.add_argument("--augmentation-prompt-min-alignment", type=float, default=0.1)
    parser.add_argument("--augmentation-min-quality-score", type=float, default=0.35)
    parser.add_argument("--augmentation-max-per-seed", type=int, default=1)
    args = parser.parse_args()

    from vulnbooster.augmentation import CoTAugmenter, CWEAugmenter
    from vulnbooster.config import load_experiment_config
    from vulnbooster.env import load_local_env
    from vulnbooster.line_slicer import build_line_slice_alignment_dataset, predict_line_slices, train_line_slicer
    from vulnbooster.llm import LLMFusionRefiner, LLMPreFilter
    from vulnbooster.merge import merge_jsonl
    from vulnbooster.training import train_classifier
    from vulnbooster.validation import filter_valid_samples

    load_local_env()
    config = load_experiment_config(args.config)
    config.line_slicer.epochs = args.line_slicer_epochs
    config.training.epochs = args.detector_epochs
    config.line_slicer.batch_size = args.line_slicer_batch_size
    config.training.batch_size = args.detector_batch_size
    config.llm.concurrency_limit = args.llm_concurrency
    config.augmentation.generate_k = args.generate_k

    output_root = Path(args.output_root).resolve()
    data_root = output_root / "data"
    teacher_root = output_root / "teacher"
    line_root = output_root / "line_slicer"
    baseline_root = output_root / "baseline_detector"
    aug_root = output_root / "augmentation"
    augmented_root = output_root / "augmented_detector"

    stats: dict[str, Any] = {
        "config": {
            "config_path": str(Path(args.config).resolve()),
            "output_root": str(output_root),
            "train_per_class": args.train_per_class,
            "valid_per_class": args.valid_per_class,
            "test_per_class": args.test_per_class,
            "seed": args.seed,
            "line_slicer_epochs": args.line_slicer_epochs,
            "detector_epochs": args.detector_epochs,
            "llm_concurrency": args.llm_concurrency,
            "augmentation": args.augmentation,
            "generate_k": args.generate_k,
            "augmentation_detector_min_prob": args.augmentation_detector_min_prob,
            "augmentation_seed_min_alignment": args.augmentation_seed_min_alignment,
            "augmentation_prompt_min_alignment": args.augmentation_prompt_min_alignment,
            "augmentation_min_quality_score": args.augmentation_min_quality_score,
            "augmentation_max_per_seed": args.augmentation_max_per_seed,
        }
    }

    print("[1/10] Sampling balanced subset")
    stats["sampling"] = {
        "train": _sample_subset(config.root_dir, data_root, "train", args.train_per_class, args.seed),
        "valid": _sample_subset(config.root_dir, data_root, "valid", args.valid_per_class, args.seed + 1),
        "test": _sample_subset(config.root_dir, data_root, "test", args.test_per_class, args.seed + 2),
    }

    print("[2/10] Cleaning subset")
    clean_stats: dict[str, Any] = {}
    for split in ("train", "valid", "test"):
        clean_stats[split] = _clean_split(
            data_root / "raw" / f"primevul_{split}.jsonl",
            data_root / "cleaned" / f"primevul_{split}_cleaned.jsonl",
        )
    stats["cleaning"] = clean_stats

    print("[3/10] Building teacher slices")
    teacher_stats: dict[str, Any] = {}
    prefilter = LLMPreFilter(config)
    fusion = LLMFusionRefiner(config)
    for split in ("train", "valid", "test"):
        cleaned_path = data_root / "cleaned" / f"primevul_{split}_cleaned.jsonl"
        split_teacher_root = teacher_root / split
        static_output = split_teacher_root / f"{split}_static.jsonl"
        llm_output = split_teacher_root / f"{split}_llm.jsonl"
        refined_output = split_teacher_root / f"{split}_refined.jsonl"

        teacher_stats[split] = {
            "static": _slice_split(config, cleaned_path, split_teacher_root, f"{split}_static.jsonl"),
            "llm_prefilter": prefilter.run(cleaned_path, llm_output),
            "llm_fusion": fusion.run(static_output, llm_output, refined_output),
            "refined_rows": _count_rows(refined_output),
        }
    stats["teacher"] = teacher_stats

    print("[4/10] Building line-level labels")
    label_stats: dict[str, Any] = {}
    for split in ("train", "valid", "test"):
        refined_path = teacher_root / split / f"{split}_refined.jsonl"
        label_path = line_root / f"{split}_line_labels.jsonl"
        label_stats[split] = build_line_slice_alignment_dataset(refined_path, label_path)
    stats["line_labels"] = label_stats

    print("[5/10] Training line slicer")
    line_model_dir = line_root / "model"
    line_train_result = train_line_slicer(
        config=config,
        train_path=line_root / "train_line_labels.jsonl",
        valid_path=line_root / "valid_line_labels.jsonl",
        test_path=line_root / "test_line_labels.jsonl",
        output_dir=line_model_dir,
    )
    stats["line_slicer_train"] = {
        "eval_metrics": dict(line_train_result.eval_metrics),
        "test_metrics": dict(line_train_result.test_metrics),
        "output_dir": str(line_train_result.output_dir),
    }

    print("[6/10] Training baseline detector")
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
    stats["baseline_detector"] = {
        "test_metrics": _metric_subset(baseline_result.test_metrics),
        "false_negative_count": baseline_result.false_negative_count,
    }

    print("[7/10] Predicting FN line slices")
    fn_line_slice_path = line_root / "valid_false_negatives_line_slice.jsonl"
    fn_slice_stats = predict_line_slices(
        config=config,
        input_path=baseline_root / "valid_false_negatives.jsonl",
        model_dir=line_model_dir,
        output_path=fn_line_slice_path,
    )
    stats["fn_line_slices"] = fn_slice_stats

    print("[8/10] Generating augmented vulnerable samples")
    generated_path = aug_root / "generated.jsonl"
    if args.augmentation == "cwe":
        generator = CWEAugmenter(config)
    else:
        generator = CoTAugmenter(config)
    generation_stats = generator.run(fn_line_slice_path, generated_path)
    validated_path = aug_root / "validated.jsonl"
    validation_stats = filter_valid_samples(
        generated_path,
        validated_path,
        config=config,
        detector_model_dir=baseline_root / "model",
        detector_min_prob=args.augmentation_detector_min_prob,
        min_seed_alignment=args.augmentation_seed_min_alignment,
        min_prompt_alignment=args.augmentation_prompt_min_alignment,
        min_quality_score=args.augmentation_min_quality_score,
        max_per_seed=args.augmentation_max_per_seed,
    )
    merged_train_path = aug_root / "train_augmented.jsonl"
    merge_stats = merge_jsonl(
        [data_root / "cleaned" / "primevul_train_cleaned.jsonl", validated_path],
        merged_train_path,
    )
    stats["augmentation"] = {
        "generation": generation_stats,
        "validation": validation_stats,
        "merge": merge_stats,
        "validated_rows": _count_rows(validated_path),
        "merged_train_rows": _count_rows(merged_train_path),
    }

    print("[9/10] Training augmented detector")
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
    stats["augmented_detector"] = {
        "test_metrics": _metric_subset(augmented_result.test_metrics),
        "false_negative_count": augmented_result.false_negative_count,
    }

    print("[10/10] Summarizing gains")
    baseline_metrics = stats["baseline_detector"]["test_metrics"]
    augmented_metrics = stats["augmented_detector"]["test_metrics"]
    gains = {}
    for metric_name, baseline_value in baseline_metrics.items():
        if metric_name not in augmented_metrics:
            continue
        gains[metric_name] = augmented_metrics[metric_name] - baseline_value
    stats["gains"] = gains

    summary_path = output_root / "summary.json"
    _write_summary(summary_path, stats)
    print(json.dumps(stats, ensure_ascii=False, indent=2))
    print(f"summary saved to: {summary_path}")


if __name__ == "__main__":
    main()
