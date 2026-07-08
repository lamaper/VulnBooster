from __future__ import annotations

import json
import random
from pathlib import Path


def build_balanced_smoke_set(input_path: Path, output_path: Path, seed: int = 42, num_per_class: int = 50) -> dict[str, int]:
    random.seed(seed)

    safe_samples: list[str] = []
    vuln_samples: list[str] = []

    with input_path.open("r", encoding="utf-8") as handle:
        for line in handle:
            line = line.strip()
            if not line:
                continue
            try:
                row = json.loads(line)
            except json.JSONDecodeError:
                continue
            if row.get("target", 0) == 1:
                vuln_samples.append(line)
            else:
                safe_samples.append(line)

    actual_safe = min(num_per_class, len(safe_samples))
    actual_vuln = min(num_per_class, len(vuln_samples))

    selected = random.sample(safe_samples, actual_safe) + random.sample(vuln_samples, actual_vuln)
    random.shuffle(selected)

    output_path.parent.mkdir(parents=True, exist_ok=True)
    with output_path.open("w", encoding="utf-8") as handle:
        for line in selected:
            handle.write(line + "\n")

    return {
        "safe": actual_safe,
        "vuln": actual_vuln,
        "written": len(selected),
    }
