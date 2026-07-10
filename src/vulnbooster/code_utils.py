from __future__ import annotations

from collections import Counter
import re


FUNCTION_HEADER_PATTERN = re.compile(
    r"^\s*[A-Za-z_~][\w\s\*\:&<>\[\],]*\([^;{}]*\)\s*(?:const\s*)?(?:\{|$)"
)
CONTROL_HEADER_PATTERN = re.compile(r"^\s*(if|for|while|switch|return|else|do|catch)\b", re.IGNORECASE)
DECLARED_FUNCTION_NAME_PATTERN = re.compile(r"^\s*[A-Za-z_~][\w\s\*\:&<>\[\],]*?\b([A-Za-z_]\w*)\s*\([^;{}]*\)")
IDENTIFIER_PATTERN = re.compile(r"\b[A-Za-z_]\w*\b")
FUNCTION_CALL_PATTERN = re.compile(r"\b([A-Za-z_]\w*)\s*\(")

C_LIKE_STOPWORDS = {
    "auto",
    "bool",
    "break",
    "case",
    "catch",
    "char",
    "class",
    "const",
    "continue",
    "default",
    "do",
    "double",
    "else",
    "enum",
    "extern",
    "false",
    "float",
    "for",
    "goto",
    "if",
    "inline",
    "int",
    "long",
    "namespace",
    "new",
    "null",
    "nullptr",
    "operator",
    "private",
    "protected",
    "public",
    "register",
    "restrict",
    "return",
    "short",
    "signed",
    "sizeof",
    "static",
    "struct",
    "switch",
    "template",
    "this",
    "throw",
    "true",
    "try",
    "typedef",
    "typename",
    "union",
    "unsigned",
    "using",
    "virtual",
    "void",
    "volatile",
    "while",
}


def normalize_code_line(line: str) -> str:
    return re.sub(r"\s+", " ", line).strip()


def count_brace_delta(line: str) -> int:
    return line.count("{") - line.count("}")


def collapse_duplicate_lines(lines: list[str]) -> list[str]:
    collapsed: list[str] = []
    for line in lines:
        if collapsed and normalize_code_line(collapsed[-1]) == normalize_code_line(line):
            continue
        collapsed.append(line)
    return collapsed


def looks_like_function_header(line: str) -> bool:
    normalized = normalize_code_line(line)
    if not normalized or CONTROL_HEADER_PATTERN.match(normalized):
        return False
    return FUNCTION_HEADER_PATTERN.match(line) is not None


def _header_block_length(lines: list[str]) -> int:
    for index, line in enumerate(lines, start=1):
        if "{" in line:
            return index
    return 0


def deduplicate_leading_header_blocks(lines: list[str]) -> list[str]:
    if not lines or not looks_like_function_header(lines[0]):
        return lines

    block_len = _header_block_length(lines)
    if block_len <= 0 or len(lines) < block_len * 2:
        return lines

    header_block = [normalize_code_line(line) for line in lines[:block_len]]
    cursor = block_len
    while cursor + block_len <= len(lines):
        next_block = [normalize_code_line(line) for line in lines[cursor : cursor + block_len]]
        if next_block != header_block:
            break
        cursor += block_len
    return lines[:block_len] + lines[cursor:]


def extract_first_function_block(code: str) -> str:
    lines = code.splitlines()
    if not lines:
        return ""

    start = 0
    for index, line in enumerate(lines):
        if looks_like_function_header(line):
            start = index
            break

    selected = lines[start:]
    if not selected:
        return ""

    selected = deduplicate_leading_header_blocks(selected)
    selected = collapse_duplicate_lines(selected)

    saw_open_brace = False
    brace_balance = 0
    for index, line in enumerate(selected):
        brace_balance += count_brace_delta(line)
        if "{" in line:
            saw_open_brace = True
        if saw_open_brace and brace_balance <= 0:
            return "\n".join(selected[: index + 1]).strip()

    return "\n".join(selected).strip()


def sanitize_generated_function(code: str) -> str:
    if not code:
        return ""
    code = code.replace("\r\n", "\n").replace("\r", "\n").strip()
    return extract_first_function_block(code)


def fingerprint_code(code: str) -> str:
    sanitized = sanitize_generated_function(code)
    if not sanitized:
        return ""
    normalized_lines = [normalize_code_line(line) for line in sanitized.splitlines() if normalize_code_line(line)]
    return "\n".join(normalized_lines)


def extract_code_identifiers(code: str) -> set[str]:
    sanitized = sanitize_generated_function(code)
    if not sanitized:
        return set()
    return {
        token
        for token in IDENTIFIER_PATTERN.findall(sanitized)
        if token not in C_LIKE_STOPWORDS and len(token) > 1
    }


def _unique_in_order(tokens: list[str]) -> list[str]:
    seen: set[str] = set()
    ordered: list[str] = []
    for token in tokens:
        if token in seen:
            continue
        seen.add(token)
        ordered.append(token)
    return ordered


def extract_ordered_code_identifiers(code: str) -> list[str]:
    sanitized = sanitize_generated_function(code)
    if not sanitized:
        return []
    tokens = [
        token
        for token in IDENTIFIER_PATTERN.findall(sanitized)
        if token not in C_LIKE_STOPWORDS and len(token) > 1
    ]
    return _unique_in_order(tokens)


def extract_function_calls(code: str) -> set[str]:
    sanitized = sanitize_generated_function(code)
    if not sanitized:
        return set()
    return {
        token
        for token in FUNCTION_CALL_PATTERN.findall(sanitized)
        if token not in C_LIKE_STOPWORDS and len(token) > 1
    }


def extract_ordered_function_calls(code: str) -> list[str]:
    sanitized = sanitize_generated_function(code)
    if not sanitized:
        return []
    tokens = [
        token
        for token in FUNCTION_CALL_PATTERN.findall(sanitized)
        if token not in C_LIKE_STOPWORDS and len(token) > 1
    ]
    return _unique_in_order(tokens)


def extract_declared_function_name(code: str) -> str:
    sanitized = sanitize_generated_function(code)
    if not sanitized:
        return ""
    first_line = sanitized.splitlines()[0] if sanitized.splitlines() else ""
    match = DECLARED_FUNCTION_NAME_PATTERN.match(first_line)
    if not match:
        return ""
    return match.group(1)


def overlap_ratio(reference_tokens: set[str], candidate_tokens: set[str]) -> float:
    if not reference_tokens or not candidate_tokens:
        return 0.0
    return len(reference_tokens & candidate_tokens) / max(1, min(len(reference_tokens), len(candidate_tokens)))


def compute_seed_alignment_metrics(seed_code: str, candidate_code: str) -> dict[str, float]:
    seed_identifiers = extract_code_identifiers(seed_code)
    candidate_identifiers = extract_code_identifiers(candidate_code)
    seed_calls = extract_function_calls(seed_code)
    candidate_calls = extract_function_calls(candidate_code)
    identifier_overlap = overlap_ratio(seed_identifiers, candidate_identifiers)
    call_overlap = overlap_ratio(seed_calls, candidate_calls)
    return {
        "identifier_overlap": identifier_overlap,
        "call_overlap": call_overlap,
        "alignment_score": max(identifier_overlap, call_overlap),
    }


def count_code_lines(code: str) -> int:
    sanitized = sanitize_generated_function(code)
    if not sanitized:
        return 0
    return sum(1 for line in sanitized.splitlines() if normalize_code_line(line))


def compute_code_length_similarity(reference_code: str, candidate_code: str) -> float:
    reference_count = count_code_lines(reference_code)
    candidate_count = count_code_lines(candidate_code)
    if reference_count <= 0 or candidate_count <= 0:
        return 0.0
    return min(reference_count, candidate_count) / max(reference_count, candidate_count)


def build_anchor_signature(
    prompt_code: str,
    seed_code: str = "",
    *,
    max_identifier_anchors: int = 8,
    max_call_anchors: int = 4,
) -> dict[str, list[str]]:
    sanitized_prompt = sanitize_generated_function(prompt_code)
    prompt_identifier_tokens = [
        token
        for token in IDENTIFIER_PATTERN.findall(sanitized_prompt)
        if token not in C_LIKE_STOPWORDS and len(token) > 1
    ] if sanitized_prompt else []
    prompt_identifier_counts = Counter(prompt_identifier_tokens)
    prompt_identifier_positions = {token: index for index, token in enumerate(_unique_in_order(prompt_identifier_tokens))}
    prompt_identifiers = _unique_in_order(prompt_identifier_tokens)
    prompt_calls = extract_ordered_function_calls(prompt_code)
    prompt_declared_name = extract_declared_function_name(prompt_code)
    if prompt_declared_name:
        prompt_calls = [token for token in prompt_calls if token != prompt_declared_name]
    seed_identifier_set = extract_code_identifiers(seed_code) if seed_code else set(prompt_identifiers)
    seed_call_set = extract_function_calls(seed_code) if seed_code else set(prompt_calls)
    seed_declared_name = extract_declared_function_name(seed_code) if seed_code else ""
    if seed_declared_name:
        seed_call_set.discard(seed_declared_name)

    prioritized_calls = [token for token in prompt_calls if token in seed_call_set] or prompt_calls
    prioritized_identifiers = [token for token in prompt_identifiers if token in seed_identifier_set] or prompt_identifiers
    prioritized_identifiers = [token for token in prioritized_identifiers if token not in prioritized_calls]
    prioritized_identifiers.sort(
        key=lambda token: (
            -prompt_identifier_counts[token],
            prompt_identifier_positions.get(token, len(prompt_identifier_positions)),
        )
    )

    return {
        "calls": prioritized_calls[:max_call_anchors],
        "identifiers": prioritized_identifiers[:max_identifier_anchors],
    }


def compute_anchor_hit_metrics(
    candidate_code: str,
    *,
    anchor_calls: list[str] | None = None,
    anchor_identifiers: list[str] | None = None,
) -> dict[str, float | int | list[str] | bool]:
    candidate_call_set = extract_function_calls(candidate_code)
    candidate_identifier_set = extract_code_identifiers(candidate_code)
    anchor_calls = anchor_calls or []
    anchor_identifiers = anchor_identifiers or []

    matched_calls = [token for token in anchor_calls if token in candidate_call_set]
    matched_identifiers = [token for token in anchor_identifiers if token in candidate_identifier_set]
    call_ratio = len(matched_calls) / len(anchor_calls) if anchor_calls else 0.0
    identifier_ratio = len(matched_identifiers) / len(anchor_identifiers) if anchor_identifiers else 0.0
    return {
        "matched_calls": matched_calls,
        "matched_identifiers": matched_identifiers,
        "call_hits": len(matched_calls),
        "identifier_hits": len(matched_identifiers),
        "call_ratio": call_ratio,
        "identifier_ratio": identifier_ratio,
        "has_anchor_signal": bool(matched_calls or matched_identifiers),
    }


def _match_slice_lines_to_original(original_code: str, extracted_code: str) -> tuple[list[int], int]:
    original_lines = original_code.splitlines()
    extracted_lines = [line for line in extracted_code.splitlines() if normalize_code_line(line)]
    normalized_original = [normalize_code_line(line) for line in original_lines]
    normalized_extracted = [normalize_code_line(line) for line in extracted_lines]

    matched_line_numbers: list[int] = []
    selected = set()
    search_start = 0

    for normalized_line in normalized_extracted:
        found_index: int | None = None
        for idx in range(search_start, len(normalized_original)):
            if normalized_original[idx] == normalized_line:
                found_index = idx
                search_start = idx + 1
                break
        if found_index is None:
            for idx, original_line in enumerate(normalized_original):
                if original_line == normalized_line and idx not in selected:
                    found_index = idx
                    break
        if found_index is None:
            continue
        selected.add(found_index)
        matched_line_numbers.append(found_index + 1)

    return matched_line_numbers, len(normalized_extracted)


def project_slice_onto_original(extracted_code: str, original_code: str, min_match_ratio: float = 0.35) -> str:
    extracted_code = sanitize_generated_function(extracted_code)
    if not extracted_code or not original_code:
        return extracted_code

    matched_line_numbers, extracted_count = _match_slice_lines_to_original(original_code, extracted_code)
    if not matched_line_numbers or extracted_count == 0:
        return stitch_function_header(extracted_code, original_code)

    unique_matches = sorted(set(matched_line_numbers))
    match_ratio = len(unique_matches) / max(extracted_count, 1)
    if match_ratio < min_match_ratio and len(unique_matches) < min(3, extracted_count):
        return stitch_function_header(extracted_code, original_code)

    original_lines = original_code.splitlines()
    balanced_lines = ensure_block_balance(original_lines, unique_matches)
    projected = "\n".join(original_lines[index - 1] for index in balanced_lines if 1 <= index <= len(original_lines))
    return stitch_function_header(projected, original_code)


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
