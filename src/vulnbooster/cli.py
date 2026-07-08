from __future__ import annotations

import argparse
from pathlib import Path

from .config import load_experiment_config
from .doctor import run_doctor
from .env import load_local_env
from .pipeline import build_research_paths


def _config_argument(parser: argparse.ArgumentParser) -> None:
    parser.add_argument("--config", default="configs/smoke.toml", help="Path to experiment config TOML.")


def build_parser() -> argparse.ArgumentParser:
    parser = argparse.ArgumentParser(description="Research pipeline for vulnerability detection.")
    subparsers = parser.add_subparsers(dest="command", required=True)

    show_config = subparsers.add_parser("show-config", help="Print resolved research paths.")
    _config_argument(show_config)

    doctor = subparsers.add_parser("doctor", help="Run environment and dependency checks.")
    _config_argument(doctor)

    build_smoke = subparsers.add_parser("build-smoke", help="Build balanced smoke datasets from full splits.")
    _config_argument(build_smoke)
    build_smoke.add_argument("--num-per-class", type=int, default=50)
    build_smoke.add_argument("--seed", type=int, default=42)

    clean = subparsers.add_parser("clean", help="Clean one dataset split.")
    _config_argument(clean)
    clean.add_argument("--split", choices=["train", "valid", "test"], required=True)

    static_slice = subparsers.add_parser("static-slice", help="Run Joern slicing for one cleaned split.")
    _config_argument(static_slice)
    static_slice.add_argument("--split", choices=["train", "valid", "test"], required=True)
    static_slice.add_argument("--output-name", required=True, help="Relative path under slice/<variant>/")

    prefilter = subparsers.add_parser("llm-pre-filter", help="Run LLM pre-filter on one input JSONL.")
    _config_argument(prefilter)
    prefilter.add_argument("--input", required=True)
    prefilter.add_argument("--output", required=True)

    fuse = subparsers.add_parser("llm-fuse", help="Fuse static and LLM slices.")
    _config_argument(fuse)
    fuse.add_argument("--static-input", required=True)
    fuse.add_argument("--llm-input", required=True)
    fuse.add_argument("--output", required=True)

    cot = subparsers.add_parser("augment-cot", help="Generate CoT-based augmentations.")
    _config_argument(cot)
    cot.add_argument("--input", required=True)
    cot.add_argument("--output", required=True)

    cwe = subparsers.add_parser("augment-cwe", help="Generate CWE-based augmentations.")
    _config_argument(cwe)
    cwe.add_argument("--input", required=True)
    cwe.add_argument("--output", required=True)

    validate = subparsers.add_parser("validate", help="Filter syntax-valid generated samples.")
    _config_argument(validate)
    validate.add_argument("--input", required=True)
    validate.add_argument("--output", required=True)

    build_line_labels = subparsers.add_parser("build-line-labels", help="Build teacher-aligned line-level slice labels.")
    _config_argument(build_line_labels)
    build_line_labels.add_argument("--input", required=True)
    build_line_labels.add_argument("--output", required=True)

    train_line_slicer = subparsers.add_parser("train-line-slicer", help="Train the line-level slicer.")
    _config_argument(train_line_slicer)
    train_line_slicer.add_argument("--train", required=True)
    train_line_slicer.add_argument("--valid", required=True)
    train_line_slicer.add_argument("--test", required=True)
    train_line_slicer.add_argument("--output-dir", required=True)

    predict_line_slicer = subparsers.add_parser("predict-line-slicer", help="Predict slices with the trained line-level slicer.")
    _config_argument(predict_line_slicer)
    predict_line_slicer.add_argument("--input", required=True)
    predict_line_slicer.add_argument("--model-dir", required=True)
    predict_line_slicer.add_argument("--output", required=True)

    merge = subparsers.add_parser("merge", help="Merge JSONL datasets with de-duplication.")
    _config_argument(merge)
    merge.add_argument("--output", required=True)
    merge.add_argument("--inputs", nargs="+", required=True)

    train = subparsers.add_parser("train", help="Fine-tune the detector on a prepared dataset.")
    _config_argument(train)
    train.add_argument("--train", required=True)
    train.add_argument("--valid", required=True)
    train.add_argument("--test", required=True)
    train.add_argument("--output-dir", required=True)
    train.add_argument("--false-negatives", required=True)
    train.add_argument("--predictions", required=True)
    train.add_argument("--target-key", default="refined_code")

    return parser


def main() -> None:
    load_local_env()
    parser = build_parser()
    args = parser.parse_args()
    config = load_experiment_config(args.config)
    research_paths = build_research_paths(config)

    if args.command == "show-config":
        print(research_paths)
        return

    if args.command == "doctor":
        results = run_doctor(config)
        for item in results:
            status = "OK" if item.ok else ("WARN" if not item.required else "FAIL")
            print(f"[{status}] {item.name}: {item.detail}")
        return

    if args.command == "build-smoke":
        from .sampling import build_balanced_smoke_set

        if config.project.dataset_variant != "smoke":
            raise SystemExit("build-smoke should be used with a smoke config.")

        for split in ("train", "valid", "test"):
            input_path = config.root_dir / config.paths.dataset_dir / f"primevul_{split}.jsonl"
            output_path = config.root_dir / config.paths.smoke_dir / f"primevul_{split}.jsonl"
            stats = build_balanced_smoke_set(
                input_path=input_path,
                output_path=output_path,
                seed=args.seed,
                num_per_class=args.num_per_class,
            )
            print(f"{split}: {stats}")
        return

    if args.command == "clean":
        from .cleaning import clean_dataset

        input_path = config.dataset_split_path(args.split, cleaned=False)
        output_path = config.dataset_split_path(args.split, cleaned=True)
        print(clean_dataset(input_path, output_path))
        return

    if args.command == "static-slice":
        from .static_slice import JoernSlicer

        slicer = JoernSlicer(config)
        input_path = config.dataset_split_path(args.split, cleaned=True)
        output_path = config.slice_output_path(args.output_name)
        source_dir = output_path.parent / f"{args.split}_c"
        cpg_dir = output_path.parent / f"{args.split}_cpg"
        print(slicer.slice_dataset(input_path, source_dir, cpg_dir, output_path))
        return

    if args.command == "llm-pre-filter":
        from .llm import LLMPreFilter

        pipeline = LLMPreFilter(config)
        print(pipeline.run(Path(args.input), Path(args.output)))
        return

    if args.command == "llm-fuse":
        from .llm import LLMFusionRefiner

        pipeline = LLMFusionRefiner(config)
        print(pipeline.run(Path(args.static_input), Path(args.llm_input), Path(args.output)))
        return

    if args.command == "augment-cot":
        from .augmentation import CoTAugmenter

        augmenter = CoTAugmenter(config)
        print(augmenter.run(Path(args.input), Path(args.output)))
        return

    if args.command == "augment-cwe":
        from .augmentation import CWEAugmenter

        augmenter = CWEAugmenter(config)
        print(augmenter.run(Path(args.input), Path(args.output)))
        return

    if args.command == "validate":
        from .validation import filter_valid_samples

        print(filter_valid_samples(Path(args.input), Path(args.output)))
        return

    if args.command == "build-line-labels":
        from .line_slicer import build_line_slice_alignment_dataset

        print(build_line_slice_alignment_dataset(Path(args.input), Path(args.output)))
        return

    if args.command == "train-line-slicer":
        from .line_slicer import train_line_slicer

        result = train_line_slicer(
            config=config,
            train_path=Path(args.train),
            valid_path=Path(args.valid),
            test_path=Path(args.test),
            output_dir=Path(args.output_dir),
        )
        print(result)
        return

    if args.command == "predict-line-slicer":
        from .line_slicer import predict_line_slices

        print(
            predict_line_slices(
                config=config,
                input_path=Path(args.input),
                model_dir=Path(args.model_dir),
                output_path=Path(args.output),
            )
        )
        return

    if args.command == "merge":
        from .merge import merge_jsonl

        print(merge_jsonl([Path(item) for item in args.inputs], Path(args.output)))
        return

    if args.command == "train":
        from .training import train_classifier

        result = train_classifier(
            config=config,
            train_path=Path(args.train),
            valid_path=Path(args.valid),
            test_path=Path(args.test),
            output_dir=Path(args.output_dir),
            false_negative_path=Path(args.false_negatives),
            prediction_path=Path(args.predictions),
            target_key=args.target_key,
        )
        print(result)
        return


if __name__ == "__main__":
    main()
