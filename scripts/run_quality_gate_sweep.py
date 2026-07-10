from __future__ import annotations

import argparse
import json
from pathlib import Path

from transformers import DataCollatorWithPadding, Trainer

from vulnbooster.config import load_experiment_config
from vulnbooster.env import load_local_env
from vulnbooster.jsonl import iter_jsonl
from vulnbooster.merge import merge_jsonl
from vulnbooster.training import (
    CodeDataset,
    compute_metrics,
    load_cached_sequence_classifier,
    load_cached_tokenizer,
    train_classifier,
)
from vulnbooster.validation import filter_valid_samples


def _count_rows(path: Path) -> int:
    return sum(1 for _ in iter_jsonl(path)) if path.exists() else 0


def _parse_float_list(value: str) -> list[float]:
    return [float(item.strip()) for item in value.split(",") if item.strip()]


def _parse_int_list(value: str) -> list[int]:
    return [int(item.strip()) for item in value.split(",") if item.strip()]


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


def main() -> None:
    parser = argparse.ArgumentParser(description="Sweep stricter augmentation quality gates on an existing experiment.")
    parser.add_argument("--config", default="configs/full.toml")
    parser.add_argument("--experiment-root", required=True)
    parser.add_argument("--output-root", required=True)
    parser.add_argument("--detector-probs", default="0.0,0.35,0.4,0.45")
    parser.add_argument("--seed-alignments", default="0.0,0.05,0.1")
    parser.add_argument("--prompt-alignments", default="0.0,0.05,0.1,0.15")
    parser.add_argument("--quality-scores", default="0.0,0.3,0.35,0.4")
    parser.add_argument("--max-per-seed-options", default="1,2")
    parser.add_argument("--min-anchor-identifier-hits", type=int)
    parser.add_argument("--min-anchor-call-hits", type=int)
    parser.add_argument("--require-anchor-signal", action="store_true")
    parser.add_argument("--min-novel-line-count", type=int)
    parser.add_argument("--min-novel-line-ratio", type=float)
    parser.add_argument("--min-structural-novel-line-count", type=int)
    parser.add_argument("--max-abstract-token-similarity", type=float)
    parser.add_argument("--reject-trivial-variants", action="store_true")
    parser.add_argument("--min-kept", type=int, default=4)
    parser.add_argument("--detector-epochs", type=int, default=3)
    parser.add_argument("--detector-batch-size", type=int, default=16)
    parser.add_argument("--target-key", default="func")
    args = parser.parse_args()

    load_local_env()
    config = load_experiment_config(args.config)
    config.training.epochs = args.detector_epochs
    config.training.batch_size = args.detector_batch_size
    min_anchor_identifier_hits = (
        config.augmentation.min_identifier_anchor_hits
        if args.min_anchor_identifier_hits is None
        else args.min_anchor_identifier_hits
    )
    min_anchor_call_hits = (
        config.augmentation.min_call_anchor_hits
        if args.min_anchor_call_hits is None
        else args.min_anchor_call_hits
    )
    require_anchor_signal = args.require_anchor_signal or config.augmentation.require_anchor_signal
    min_novel_line_count = (
        config.augmentation.min_novel_line_count
        if args.min_novel_line_count is None
        else args.min_novel_line_count
    )
    min_novel_line_ratio = (
        config.augmentation.min_novel_line_ratio
        if args.min_novel_line_ratio is None
        else args.min_novel_line_ratio
    )
    min_structural_novel_line_count = (
        config.augmentation.min_structural_novel_line_count
        if args.min_structural_novel_line_count is None
        else args.min_structural_novel_line_count
    )
    max_abstract_token_similarity = (
        config.augmentation.max_abstract_token_similarity
        if args.max_abstract_token_similarity is None
        else args.max_abstract_token_similarity
    )
    reject_trivial_variants = args.reject_trivial_variants or config.augmentation.reject_trivial_variants

    experiment_root = Path(args.experiment_root).resolve()
    output_root = Path(args.output_root).resolve()
    generated_path = experiment_root / "augmentation" / "generated.jsonl"
    baseline_model_dir = experiment_root / "baseline_detector" / "model"
    train_path = experiment_root / "data" / "cleaned" / "primevul_train_cleaned.jsonl"
    valid_path = experiment_root / "data" / "cleaned" / "primevul_valid_cleaned.jsonl"
    test_path = experiment_root / "data" / "cleaned" / "primevul_test_cleaned.jsonl"

    baseline_metrics = evaluate_detector(args.config, baseline_model_dir, test_path, args.target_key)
    detector_probs = _parse_float_list(args.detector_probs)
    seed_alignments = _parse_float_list(args.seed_alignments)
    prompt_alignments = _parse_float_list(args.prompt_alignments)
    quality_scores = _parse_float_list(args.quality_scores)
    max_per_seed_options = _parse_int_list(args.max_per_seed_options)

    results: list[dict] = []
    best_result: dict | None = None
    best_key: tuple[float, float, float] | None = None

    for detector_prob in detector_probs:
        for seed_alignment in seed_alignments:
            for prompt_alignment in prompt_alignments:
                for quality_score in quality_scores:
                    for max_per_seed in max_per_seed_options:
                        run_name = (
                            f"prob_{detector_prob:.2f}_seed_{seed_alignment:.2f}_"
                            f"prompt_{prompt_alignment:.2f}_score_{quality_score:.2f}_top_{max_per_seed}"
                        ).replace(".", "p")
                        run_root = output_root / run_name
                        validated_path = run_root / "validated.jsonl"
                        merged_train_path = run_root / "train_augmented.jsonl"
                        augmented_model_dir = run_root / "model"
                        prediction_path = run_root / "valid_predictions.jsonl"
                        fn_path = run_root / "valid_false_negatives.jsonl"

                        print(
                            "[sweep] "
                            f"prob={detector_prob:.2f} seed={seed_alignment:.2f} "
                            f"prompt={prompt_alignment:.2f} score={quality_score:.2f} topk={max_per_seed}"
                        )
                        validation_stats = filter_valid_samples(
                            generated_path,
                            validated_path,
                            config=config,
                            detector_model_dir=baseline_model_dir,
                            detector_min_prob=detector_prob,
                            min_seed_alignment=seed_alignment,
                            min_prompt_alignment=prompt_alignment,
                            min_quality_score=quality_score,
                            max_per_seed=max_per_seed,
                            min_anchor_identifier_hits=min_anchor_identifier_hits,
                            min_anchor_call_hits=min_anchor_call_hits,
                            require_anchor_signal=require_anchor_signal,
                            min_novel_line_count=min_novel_line_count,
                            min_novel_line_ratio=min_novel_line_ratio,
                            min_structural_novel_line_count=min_structural_novel_line_count,
                            max_abstract_token_similarity=max_abstract_token_similarity,
                            reject_trivial_variants=reject_trivial_variants,
                        )
                        kept = _count_rows(validated_path)
                        if kept < args.min_kept:
                            result = {
                                "detector_min_prob": detector_prob,
                                "seed_min_alignment": seed_alignment,
                                "prompt_min_alignment": prompt_alignment,
                                "min_quality_score": quality_score,
                                "max_per_seed": max_per_seed,
                                "skipped": True,
                                "reason": f"validated_rows<{args.min_kept}",
                                "validation": validation_stats,
                            }
                            results.append(result)
                            continue

                        merge_stats = merge_jsonl([train_path, validated_path], merged_train_path)
                        training_result = train_classifier(
                            config=config,
                            train_path=merged_train_path,
                            valid_path=valid_path,
                            test_path=test_path,
                            output_dir=augmented_model_dir,
                            false_negative_path=fn_path,
                            prediction_path=prediction_path,
                            target_key=args.target_key,
                        )
                        augmented_metrics = evaluate_detector(args.config, augmented_model_dir, test_path, args.target_key)
                        gains = {
                            key: augmented_metrics[key] - baseline_metrics[key]
                            for key in baseline_metrics.keys()
                            if key in augmented_metrics
                        }
                        result = {
                            "detector_min_prob": detector_prob,
                            "seed_min_alignment": seed_alignment,
                            "prompt_min_alignment": prompt_alignment,
                            "min_quality_score": quality_score,
                            "max_per_seed": max_per_seed,
                            "skipped": False,
                            "validation": validation_stats,
                            "merge": merge_stats,
                            "validated_rows": kept,
                            "merged_train_rows": _count_rows(merged_train_path),
                            "augmented_test_metrics": augmented_metrics,
                            "baseline_test_metrics": baseline_metrics,
                            "augmented_false_negatives": training_result.false_negative_count,
                            "gains": gains,
                        }
                        results.append(result)

                        candidate_key = (
                            augmented_metrics.get("eval_mcc", float("-inf")),
                            augmented_metrics.get("eval_precision", float("-inf")),
                            augmented_metrics.get("eval_f1", float("-inf")),
                        )
                        if best_key is None or candidate_key > best_key:
                            best_key = candidate_key
                            best_result = result

    payload = {
        "config": {
            "config_path": str(Path(args.config).resolve()),
            "experiment_root": str(experiment_root),
            "output_root": str(output_root),
            "detector_probs": detector_probs,
            "seed_alignments": seed_alignments,
            "prompt_alignments": prompt_alignments,
            "quality_scores": quality_scores,
            "max_per_seed_options": max_per_seed_options,
            "min_anchor_identifier_hits": min_anchor_identifier_hits,
            "min_anchor_call_hits": min_anchor_call_hits,
            "require_anchor_signal": require_anchor_signal,
            "min_novel_line_count": min_novel_line_count,
            "min_novel_line_ratio": min_novel_line_ratio,
            "min_structural_novel_line_count": min_structural_novel_line_count,
            "max_abstract_token_similarity": max_abstract_token_similarity,
            "reject_trivial_variants": reject_trivial_variants,
            "min_kept": args.min_kept,
        },
        "best_result": best_result,
        "results": results,
    }
    output_root.mkdir(parents=True, exist_ok=True)
    (output_root / "sweep_summary.json").write_text(json.dumps(payload, ensure_ascii=False, indent=2), encoding="utf-8")
    print(json.dumps(payload, ensure_ascii=False, indent=2))


if __name__ == "__main__":
    main()
