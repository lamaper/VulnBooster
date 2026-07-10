from __future__ import annotations

from pathlib import Path
import os


def configure_hf_endpoint(endpoint: str | None) -> str | None:
    if not endpoint:
        return None

    os.environ["HF_ENDPOINT"] = endpoint
    os.environ["HUGGINGFACE_HUB_ENDPOINT"] = endpoint
    return endpoint


def apply_java_home(java_home: str | None = None) -> str | None:
    resolved = java_home or os.environ.get("VULNBOOSTER_JAVA_HOME", "")
    if not resolved:
        return None

    os.environ["JAVA_HOME"] = resolved
    java_bin = str(Path(resolved) / "bin")
    current_path = os.environ.get("PATH", "")
    path_parts = current_path.split(os.pathsep) if current_path else []
    if java_bin not in path_parts:
        os.environ["PATH"] = java_bin if not current_path else f"{java_bin}{os.pathsep}{current_path}"
    return resolved


def load_local_env(env_path: str | Path = ".env.local") -> Path | None:
    path = Path(env_path)
    if not path.exists():
        return None

    for raw_line in path.read_text(encoding="utf-8").splitlines():
        line = raw_line.strip()
        if not line or line.startswith("#") or "=" not in line:
            continue
        key, value = line.split("=", 1)
        key = key.strip()
        value = value.strip().strip('"').strip("'")
        if key and key not in os.environ:
            os.environ[key] = value
    return path
