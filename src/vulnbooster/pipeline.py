from __future__ import annotations

from dataclasses import dataclass
from pathlib import Path

from .config import ExperimentConfig


@dataclass(slots=True)
class ResearchPaths:
    raw_train: Path
    raw_valid: Path
    raw_test: Path
    cleaned_train: Path
    cleaned_valid: Path
    cleaned_test: Path
    slice_root: Path
    model_root: Path


def build_research_paths(config: ExperimentConfig) -> ResearchPaths:
    variant_dir = "smoke" if config.project.dataset_variant == "smoke" else "deepseek"
    return ResearchPaths(
        raw_train=config.dataset_split_path("train", cleaned=False),
        raw_valid=config.dataset_split_path("valid", cleaned=False),
        raw_test=config.dataset_split_path("test", cleaned=False),
        cleaned_train=config.dataset_split_path("train", cleaned=True),
        cleaned_valid=config.dataset_split_path("valid", cleaned=True),
        cleaned_test=config.dataset_split_path("test", cleaned=True),
        slice_root=config.root_dir / config.paths.slice_dir / variant_dir,
        model_root=config.root_dir / config.paths.model_dir / variant_dir,
    )
