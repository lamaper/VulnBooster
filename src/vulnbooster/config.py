from __future__ import annotations

from dataclasses import dataclass
from pathlib import Path
import tomllib


@dataclass(slots=True)
class ProjectConfig:
    name: str
    root_dir: Path
    dataset_variant: str
    iteration: int


@dataclass(slots=True)
class PathConfig:
    dataset_dir: Path
    smoke_dir: Path
    slice_dir: Path
    model_dir: Path
    cache_dir: Path


@dataclass(slots=True)
class RuntimeConfig:
    hf_endpoint: str


@dataclass(slots=True)
class TrainingConfig:
    model_name: str
    batch_size: int
    learning_rate: float
    epochs: int
    max_length: int
    prediction_threshold: float
    seed: int
    weight_decay: float


@dataclass(slots=True)
class LineSlicerConfig:
    model_name: str
    batch_size: int
    learning_rate: float
    epochs: int
    max_length: int
    threshold: float
    context_radius: int


@dataclass(slots=True)
class CodeT5SlicerConfig:
    model_name: str
    batch_size: int
    learning_rate: float
    epochs: int
    max_input_length: int
    max_target_length: int
    generation_max_length: int
    num_beams: int
    candidate_count: int
    line_number_width: int
    use_static_slice_fallback: bool
    static_hint_window: int
    overpredict_function_ratio: float
    overpredict_static_ratio: float
    overpredict_static_margin: int


@dataclass(slots=True)
class LossConfig:
    focal_alpha: float
    focal_gamma: float
    label_smoothing: float
    focal_lambda_start: float
    focal_lambda_min: float
    focal_lambda_decay: float


@dataclass(slots=True)
class StaticSliceConfig:
    joern_parse_cmd: str
    joern_cmd: str
    slice_script: Path
    parse_timeout_seconds: int
    slice_timeout_seconds: int


@dataclass(slots=True)
class LLMConfig:
    provider: str
    base_url: str
    model_name: str
    api_key_env: str
    concurrency_limit: int
    max_retries: int
    retry_delay_seconds: float
    temperature: float
    max_tokens: int


@dataclass(slots=True)
class AugmentationConfig:
    generate_k: int
    max_identifier_anchors: int
    max_call_anchors: int
    min_identifier_anchor_hits: int
    min_call_anchor_hits: int
    require_anchor_signal: bool
    min_novel_line_count: int
    min_novel_line_ratio: float
    min_structural_novel_line_count: int
    max_abstract_token_similarity: float
    reject_trivial_variants: bool


@dataclass(slots=True)
class CWEConfig:
    cache_file: Path


@dataclass(slots=True)
class ExperimentConfig:
    project: ProjectConfig
    paths: PathConfig
    runtime: RuntimeConfig
    training: TrainingConfig
    line_slicer: LineSlicerConfig
    codet5_slicer: CodeT5SlicerConfig
    loss: LossConfig
    static_slice: StaticSliceConfig
    llm: LLMConfig
    augmentation: AugmentationConfig
    cwe: CWEConfig

    @property
    def root_dir(self) -> Path:
        return self.project.root_dir

    def dataset_split_path(self, split: str, cleaned: bool = False) -> Path:
        base_dir = self.paths.smoke_dir if self.project.dataset_variant == "smoke" else self.paths.dataset_dir
        suffix = "_cleaned" if cleaned else ""
        return self.root_dir / base_dir / f"primevul_{split}{suffix}.jsonl"

    def slice_output_path(self, name: str) -> Path:
        variant_dir = "smoke" if self.project.dataset_variant == "smoke" else "deepseek"
        return self.root_dir / self.paths.slice_dir / variant_dir / name


def _resolve(root: Path, value: str) -> Path:
    return (root / value).resolve()


def load_experiment_config(config_path: str | Path) -> ExperimentConfig:
    config_file = Path(config_path).resolve()
    raw = tomllib.loads(config_file.read_text(encoding="utf-8"))

    project_root = _resolve(config_file.parent, raw["project"]["root_dir"])

    raw_codet5 = raw.get("codet5_slicer", {})

    return ExperimentConfig(
        project=ProjectConfig(
            name=raw["project"]["name"],
            root_dir=project_root,
            dataset_variant=raw["project"]["dataset_variant"],
            iteration=int(raw["project"]["iteration"]),
        ),
        paths=PathConfig(
            dataset_dir=Path(raw["paths"]["dataset_dir"]),
            smoke_dir=Path(raw["paths"]["smoke_dir"]),
            slice_dir=Path(raw["paths"]["slice_dir"]),
            model_dir=Path(raw["paths"]["model_dir"]),
            cache_dir=Path(raw["paths"]["cache_dir"]),
        ),
        runtime=RuntimeConfig(hf_endpoint=raw["runtime"]["hf_endpoint"]),
        training=TrainingConfig(**raw["training"]),
        line_slicer=LineSlicerConfig(**raw["line_slicer"]),
        codet5_slicer=CodeT5SlicerConfig(
            model_name=raw_codet5.get("model_name", "Salesforce/codet5-small"),
            batch_size=int(raw_codet5.get("batch_size", max(1, int(raw["line_slicer"]["batch_size"])))),
            learning_rate=float(raw_codet5.get("learning_rate", raw["line_slicer"]["learning_rate"])),
            epochs=int(raw_codet5.get("epochs", raw["line_slicer"]["epochs"])),
            max_input_length=int(raw_codet5.get("max_input_length", raw["line_slicer"]["max_length"])),
            max_target_length=int(raw_codet5.get("max_target_length", 64)),
            generation_max_length=int(raw_codet5.get("generation_max_length", 64)),
            num_beams=int(raw_codet5.get("num_beams", 4)),
            candidate_count=int(raw_codet5.get("candidate_count", raw_codet5.get("num_beams", 4))),
            line_number_width=int(raw_codet5.get("line_number_width", 3)),
            use_static_slice_fallback=bool(raw_codet5.get("use_static_slice_fallback", True)),
            static_hint_window=int(raw_codet5.get("static_hint_window", 1)),
            overpredict_function_ratio=float(raw_codet5.get("overpredict_function_ratio", 0.6)),
            overpredict_static_ratio=float(raw_codet5.get("overpredict_static_ratio", 2.5)),
            overpredict_static_margin=int(raw_codet5.get("overpredict_static_margin", 3)),
        ),
        loss=LossConfig(**raw["loss"]),
        static_slice=StaticSliceConfig(
            joern_parse_cmd=raw["static_slice"]["joern_parse_cmd"],
            joern_cmd=raw["static_slice"]["joern_cmd"],
            slice_script=_resolve(project_root, raw["static_slice"]["slice_script"]),
            parse_timeout_seconds=int(raw["static_slice"]["parse_timeout_seconds"]),
            slice_timeout_seconds=int(raw["static_slice"]["slice_timeout_seconds"]),
        ),
        llm=LLMConfig(**raw["llm"]),
        augmentation=AugmentationConfig(**raw["augmentation"]),
        cwe=CWEConfig(cache_file=_resolve(project_root, raw["cwe"]["cache_file"])),
    )
