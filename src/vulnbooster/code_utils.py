from __future__ import annotations

import re


def normalize_code_line(line: str) -> str:
    return re.sub(r"\s+", " ", line).strip()


def count_brace_delta(line: str) -> int:
    return line.count("{") - line.count("}")


def ensure_block_balance(function_lines: list[str], selected_line_numbers: list[int]) -> list[int]:
    if not function_lines or not selected_line_numbers:
        return []

    selected = set(num for num in selected_line_numbers if 1 <= num <= len(function_lines))
    ordered = sorted(selected)
    lower = ordered[0]
    upper = ordered[-1]

    running_delta = 0
    for line_number in ordered:
        running_delta += count_brace_delta(function_lines[line_number - 1])

    if running_delta > 0:
        for line_number in range(upper + 1, len(function_lines) + 1):
            selected.add(line_number)
            running_delta += count_brace_delta(function_lines[line_number - 1])
            if running_delta <= 0:
                break

    if running_delta < 0:
        for line_number in range(lower - 1, 0, -1):
            selected.add(line_number)
            running_delta += count_brace_delta(function_lines[line_number - 1])
            if running_delta >= 0:
                break

    return sorted(selected)


def stitch_function_header(refined_code: str, original_code: str) -> str:
    if not refined_code or not original_code:
        return refined_code

    first_line = refined_code.strip().split("\n")[0].strip()
    missing_header = False
    if re.match(r"^(if|while|for|return|switch|else|do|try|catch)\b", first_line, re.IGNORECASE):
        missing_header = True
    elif not re.search(r"\w+\s*\(.*?\)", first_line):
        missing_header = True

    if missing_header:
        header_match = re.search(r"^(.*?\{)", original_code, re.DOTALL)
        if header_match:
            header = header_match.group(1).strip()
            return f"{header}\n{refined_code}\n}}"
    return refined_code
