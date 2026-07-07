from __future__ import annotations

import re
from pathlib import Path

from tqdm import tqdm

from .jsonl import iter_jsonl, write_jsonl


COMMENT_PATTERN = re.compile(
    r'(?P<string>"(?:\\.|[^\\"])*")|'
    r"(?P<char>'(?:\\.|[^\\'])*')|"
    r'(?P<block_comment>/\*.*?\*/)|'
    r'(?P<line_comment>//.*?$)',
    re.DOTALL | re.MULTILINE,
)


def clean_c_code(code: str) -> str:
    if not code:
        return ""

    def replacer(match: re.Match[str]) -> str:
        if match.group("block_comment") or match.group("line_comment"):
            return ""
        return match.group(0)

    code_no_comments = COMMENT_PATTERN.sub(replacer, code)

    cleaned_lines: list[str] = []
    for line in code_no_comments.splitlines():
        line_stripped = re.sub(r"[ \t]+", " ", line).strip()
        if line_stripped:
            cleaned_lines.append(line_stripped)

    return "\n".join(cleaned_lines)


def clean_dataset(input_path: Path, output_path: Path) -> dict[str, int]:
    rows = list(iter_jsonl(input_path))
    stats = {
        "total": len(rows),
        "written": 0,
    }

    cleaned_rows: list[dict] = []
    for row in tqdm(rows, desc="Code Sanitization", unit="sample"):
        new_row = dict(row)
        new_row["func"] = clean_c_code(row.get("func", ""))
        cleaned_rows.append(new_row)
        stats["written"] += 1

    write_jsonl(output_path, cleaned_rows)
    return stats
