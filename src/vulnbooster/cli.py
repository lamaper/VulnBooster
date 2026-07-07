from __future__ import annotations

import argparse
from pathlib import Path

from .augmentation import CoTAugmenter, CWEAugmenter
from .cleaning import clean_dataset
from .config import load_experiment_config
from .llm import LLMFusionRefiner, LLMPreFilter
from .merge import merge_jsonl
from .pipeline import build_research_paths
from .static_slice import JoernSlicer
from .training import train_classifier
from .validation import filter_valid_samples


def _config_argument(parser: argparse.ArgumentParser) -> None:
    parser.add_argument("--config", default="configs/smoke.toml", help="Path to experiment config TOML.")


def build_parser() -> argparse.ArgumentParser:
    parser = argparse.ArgumentParser(description="Research pipeline for vulnerability detection.")
    subparsers = parser.add_subparsers(dest="command", required=True)

    show_config = subparsers.add_parser("show-config", help="Print resolved research paths.")
    _config_argument(show_config)

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
    parser = build_parser()
    args = parser.parse_args()
    config = load_experiment_config(args.config)
    research_paths = build_research_paths(config)

    if args.command == "show-config":
        print(research_paths)
        return

    if args.command == "clean":
        input_path = config.dataset_split_path(args.split, cleaned=False)
        output_path = config.dataset_split_path(args.split, cleaned=True)
        print(clean_dataset(input_path, output_path))
        return

    if args.command == "static-slice":
        slicer = JoernSlicer(config)
        input_path = config.dataset_split_path(args.split, cleaned=True)
        output_path = config.slice_output_path(args.output_name)
        source_dir = output_path.parent / f"{args.split}_c"
        cpg_dir = output_path.parent / f"{args.split}_cpg"
        print(slicer.slice_dataset(input_path, source_dir, cpg_dir, output_path))
        return

    if args.command == "llm-pre-filter":
        pipeline = LLMPreFilter(config)
        print(pipeline.run(Path(args.input), Path(args.output)))
        return

    if args.command == "llm-fuse":
        pipeline = LLMFusionRefiner(config)
        print(pipeline.run(Path(args.static_input), Path(args.llm_input), Path(args.output)))
        return

    if args.command == "augment-cot":
        augmenter = CoTAugmenter(config)
        print(augmenter.run(Path(args.input), Path(args.output)))
        return

    if args.command == "augment-cwe":
        augmenter = CWEAugmenter(config)
        print(augmenter.run(Path(args.input), Path(args.output)))
        return

    if args.command == "validate":
        print(filter_valid_samples(Path(args.input), Path(args.output)))
        return

    if args.command == "merge":
        print(merge_jsonl([Path(item) for item in args.inputs], Path(args.output)))
        return

    if args.command == "train":
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
