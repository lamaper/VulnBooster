from __future__ import annotations

import json
from pathlib import Path

from tqdm import tqdm

from .jsonl import iter_jsonl


def merge_jsonl(input_files: list[Path], output_path: Path) -> dict[str, int]:
    output_path.parent.mkdir(parents=True, exist_ok=True)
    seen_ids: set[str] = set()
    written = 0
    duplicates = 0

    with output_path.open("w", encoding="utf-8") as handle:
        for input_file in input_files:
            if not input_file.exists():
                continue
            for row in tqdm(list(iter_jsonl(input_file)), desc=f"Merge {input_file.name}", unit="sample"):
                idx = row.get("idx")
                if idx is None:
                    continue
                idx_str = str(idx)
                if idx_str in seen_ids:
                    duplicates += 1
                    continue
                seen_ids.add(idx_str)
                handle.write(json.dumps(row, ensure_ascii=False) + "\n")
                written += 1

    return {"written": written, "duplicates": duplicates}
