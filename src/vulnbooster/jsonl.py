from __future__ import annotations

import json
from pathlib import Path
from typing import Iterable, Iterator

from .models import CodeSample


def iter_jsonl(path: Path) -> Iterator[dict]:
    with path.open("r", encoding="utf-8") as handle:
        for line in handle:
            line = line.strip()
            if not line:
                continue
            try:
                yield json.loads(line)
            except json.JSONDecodeError:
                continue


def load_samples(path: Path) -> list[CodeSample]:
    return [CodeSample.from_dict(obj) for obj in iter_jsonl(path)]


def write_jsonl(path: Path, rows: Iterable[dict]) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    with path.open("w", encoding="utf-8") as handle:
        for row in rows:
            handle.write(json.dumps(row, ensure_ascii=False) + "\n")


def write_samples(path: Path, samples: Iterable[CodeSample]) -> None:
    write_jsonl(path, (sample.to_dict() for sample in samples))
