from __future__ import annotations

import importlib
import os
import shutil
import subprocess
from dataclasses import dataclass

from .config import ExperimentConfig
from .env import apply_java_home


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


def _parse_java_major(version_text: str) -> int | None:
    marker = 'version "'
    if marker not in version_text:
        return None
    fragment = version_text.split(marker, 1)[1].split('"', 1)[0]
    major_text = fragment.split(".", 1)[0]
    if major_text == "1":
        parts = fragment.split(".")
        if len(parts) > 1:
            major_text = parts[1]
    try:
        return int(major_text)
    except ValueError:
        return None


def _check_java_runtime() -> CheckResult:
    try:
        result = subprocess.run(
            ["java", "-version"],
            capture_output=True,
            text=True,
            encoding="utf-8",
            errors="ignore",
            timeout=10,
        )
    except Exception as exc:
        return CheckResult("java", False, f"probe failed: {exc}")

    if result.returncode != 0:
        detail = (result.stderr or result.stdout or "").strip() or "java -version failed"
        return CheckResult("java", False, detail)

    version_output = (result.stderr or result.stdout or "").strip()
    major = _parse_java_major(version_output)
    if major is None:
        return CheckResult("java", False, version_output)
    return CheckResult("java", major >= 17, f"major={major} | {version_output.splitlines()[0]}")


def run_doctor(config: ExperimentConfig) -> list[CheckResult]:
    results: list[CheckResult] = []
    apply_java_home()

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
    results.append(
        CheckResult(
            "JAVA_HOME",
            bool(os.environ.get("JAVA_HOME")),
            os.environ.get("JAVA_HOME", "(not set)"),
            required=False,
        )
    )
    results.append(_check_java_runtime())

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
        "accelerate",
    ):
        results.append(_check_optional_module(module_name))

    return results
