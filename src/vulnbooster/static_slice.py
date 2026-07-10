from __future__ import annotations

import json
import os
import subprocess
from pathlib import Path

from tqdm import tqdm

from .config import ExperimentConfig
from .env import apply_java_home
from .jsonl import iter_jsonl


class JoernSlicer:
    def __init__(self, config: ExperimentConfig):
        self.config = config
        self.java_home = apply_java_home()

    def _subprocess_env(self) -> dict[str, str]:
        env = os.environ.copy()
        if self.java_home:
            env["JAVA_HOME"] = self.java_home
            java_bin = str(Path(self.java_home) / "bin")
            current_path = env.get("PATH", "")
            if java_bin not in current_path.split(os.pathsep):
                env["PATH"] = java_bin if not current_path else f"{java_bin}{os.pathsep}{current_path}"
        return env

    def prepare_sources(self, input_path: Path, source_dir: Path) -> int:
        source_dir.mkdir(parents=True, exist_ok=True)
        count = 0
        for row in tqdm(list(iter_jsonl(input_path)), desc="Prepare Source Files", unit="sample"):
            idx = row.get("idx", "unknown")
            target = row.get("target", 0)
            source_path = source_dir / f"{idx}_{target}.c"
            source_path.write_text((row.get("func", "") or "") + "\n", encoding="utf-8")
            count += 1
        return count

    def parse_single_file(self, source_path: Path, cpg_path: Path) -> dict[str, str]:
        try:
            cmd = [
                self.config.static_slice.joern_parse_cmd,
                str(source_path),
                "--output",
                str(cpg_path),
            ]
            result = subprocess.run(
                cmd,
                capture_output=True,
                text=True,
                encoding="utf-8",
                errors="ignore",
                timeout=self.config.static_slice.parse_timeout_seconds,
                env=self._subprocess_env(),
            )
            if result.returncode == 0:
                return {"status": "success"}
            error = (result.stderr or result.stdout or "").strip()
            return {"status": "error", "error": error}
        except subprocess.TimeoutExpired:
            return {"status": "timeout", "error": "parse timeout"}

    def build_cpgs(self, input_path: Path, source_dir: Path, cpg_dir: Path) -> int:
        cpg_dir.mkdir(parents=True, exist_ok=True)
        success = 0
        for row in tqdm(list(iter_jsonl(input_path)), desc="Build CPG", unit="sample"):
            idx = row.get("idx", "unknown")
            target = row.get("target", 0)
            source_path = source_dir / f"{idx}_{target}.c"
            cpg_path = cpg_dir / f"{idx}_{target}.cpg.bin"
            result = self.parse_single_file(source_path, cpg_path)
            if result["status"] == "success":
                success += 1
        return success

    def run_slice_script(
        self,
        cpg_path: Path,
        source_dir: Path,
        output_path: Path,
        sample_id: str,
        target: int | None,
    ) -> bool:
        env = self._subprocess_env()
        env["JOERN_SOURCE_ROOT"] = str(source_dir.resolve()).replace("\\", "/")
        env["TARGET_CPG_PATH"] = str(cpg_path.resolve()).replace("\\", "/")

        cmd = [
            self.config.static_slice.joern_cmd,
            "--script",
            str(self.config.static_slice.slice_script.resolve()).replace("\\", "/"),
        ]
        result = subprocess.run(
            cmd,
            capture_output=True,
            text=True,
            encoding="utf-8",
            errors="ignore",
            timeout=self.config.static_slice.slice_timeout_seconds,
            env=env,
        )
        if result.returncode != 0:
            return False

        output_path.parent.mkdir(parents=True, exist_ok=True)
        written = 0
        with output_path.open("a", encoding="utf-8") as handle:
            for line in result.stdout.strip().splitlines():
                line = line.strip()
                if not line or line.startswith("[*]") or line.startswith("[!]"):
                    continue
                try:
                    row = json.loads(line)
                except json.JSONDecodeError:
                    continue
                row["fromIdx"] = sample_id
                row["target"] = target
                handle.write(json.dumps(row, ensure_ascii=False) + "\n")
                written += 1
        return written > 0

    def slice_dataset(self, input_path: Path, source_dir: Path, cpg_dir: Path, output_path: Path) -> dict[str, int]:
        self.prepare_sources(input_path, source_dir)
        self.build_cpgs(input_path, source_dir, cpg_dir)

        if output_path.exists():
            output_path.unlink()

        success = 0
        total = 0
        for row in tqdm(list(iter_jsonl(input_path)), desc="Run Static Slice", unit="sample"):
            idx = str(row.get("idx", "unknown"))
            target = row.get("target")
            cpg_path = cpg_dir / f"{idx}_{target}.cpg.bin"
            total += 1
            if self.run_slice_script(cpg_path, source_dir, output_path, idx, target):
                success += 1
        return {"total": total, "success": success}
