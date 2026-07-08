from __future__ import annotations

import importlib
import shutil
from dataclasses import dataclass

from .config import ExperimentConfig


@dataclass(slots=True)
class CheckResult:
    name: str
    ok: bool
    detail: str
    required: bool = True


def _check_module(module_name: str) -> CheckResult:
    try:
        importlib.import_module(module_name)
        return CheckResult(module_name, True, "import ok")
    except Exception as exc:
        return CheckResult(module_name, False, f"import failed: {exc}")


def _check_optional_module(module_name: str) -> CheckResult:
    result = _check_module(module_name)
    result.required = False
    return result


def run_doctor(config: ExperimentConfig) -> list[CheckResult]:
    results: list[CheckResult] = []

    results.append(
        CheckResult(
            "config.root_dir",
            config.root_dir.exists(),
            str(config.root_dir),
        )
    )

    for split in ("train", "valid", "test"):
        path = config.dataset_split_path(split, cleaned=False)
        results.append(CheckResult(f"dataset.{split}", path.exists(), str(path)))

    results.append(
        CheckResult(
            "slice.script",
            config.static_slice.slice_script.exists(),
            str(config.static_slice.slice_script),
        )
    )

    results.append(
        CheckResult(
            "joern-parse",
            shutil.which(config.static_slice.joern_parse_cmd) is not None,
            config.static_slice.joern_parse_cmd,
        )
    )
    results.append(
        CheckResult(
            "joern",
            shutil.which(config.static_slice.joern_cmd) is not None,
            config.static_slice.joern_cmd,
        )
    )

    for module_name in (
        "bs4",
        "requests",
        "tree_sitter",
        "tree_sitter_c",
        "tree_sitter_cpp",
    ):
        results.append(_check_module(module_name))

    for module_name in (
        "openai",
        "sklearn",
        "torch",
        "transformers",
        "numpy",
    ):
        results.append(_check_optional_module(module_name))

    return results
