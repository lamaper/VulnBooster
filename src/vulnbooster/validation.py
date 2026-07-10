from __future__ import annotations

from collections import deque
import re
from pathlib import Path

from tqdm import tqdm
from tree_sitter import Language, Parser
import tree_sitter_c
import tree_sitter_cpp

from .code_utils import (
    build_anchor_signature,
    compute_code_length_similarity,
    compute_anchor_hit_metrics,
    compute_seed_alignment_metrics,
    fingerprint_code,
    sanitize_generated_function,
)
from .config import ExperimentConfig
from .jsonl import iter_jsonl, write_jsonl


C_LANGUAGE = Language(tree_sitter_c.language())
CPP_LANGUAGE = Language(tree_sitter_cpp.language())
C_PARSER = Parser(C_LANGUAGE)
CPP_PARSER = Parser(CPP_LANGUAGE)

COMMENT_PATTERN = re.compile(
    r'(?P<string>"(?:\\.|[^\\"])*")|'
    r"(?P<char>'(?:\\.|[^\\'])*')|"
    r'(?P<block_comment>/\*.*?\*/)|'
    r'(?P<line_comment>//.*?$)',
    re.DOTALL | re.MULTILINE,
)


def remove_comments_and_blank_lines(code: str) -> str:
    if not code:
        return ""

    def replacer(match: re.Match[str]) -> str:
        if match.group("block_comment") or match.group("line_comment"):
            return ""
        return match.group(0)

    code_no_comments = COMMENT_PATTERN.sub(replacer, code)
    return "\n".join(line for line in code_no_comments.splitlines() if line.strip())


def validate_ast_structure(root_node) -> bool:
    has_function = False
    queue = deque([root_node])

    while queue:
        current = queue.popleft()
        if current.type == "ERROR" or getattr(current, "is_missing", False):
            return False
        if current.type == "function_definition":
            has_function = True
        queue.extend(current.children)
    return has_function


def is_valid_syntax(code: str) -> bool:
    if not code.strip():
        return False

    for parser in (C_PARSER, CPP_PARSER):
        try:
            tree = parser.parse(bytes(code, "utf-8"))
            root = tree.root_node
            if root.has_error:
                continue
            if validate_ast_structure(root):
                return True
        except Exception:
            continue
    return False


def score_rows_with_detector(
    rows: list[dict],
    config: ExperimentConfig,
    model_dir: Path,
    target_key: str = "func",
) -> list[float]:
    import torch

    from .env import configure_hf_endpoint
    from .training import load_cached_sequence_classifier, load_cached_tokenizer

    configure_hf_endpoint(config.runtime.hf_endpoint)

    tokenizer = load_cached_tokenizer(str(model_dir))
    model = load_cached_sequence_classifier(str(model_dir), num_labels=2)
    device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
    model.to(device)
    model.eval()

    probabilities: list[float] = []
    batch_size = max(1, min(config.training.batch_size, 32))
    for start in range(0, len(rows), batch_size):
        batch = rows[start : start + batch_size]
        codes = [str(row.get(target_key, "") or "") for row in batch]
        encoding = tokenizer(
            codes,
            truncation=True,
            padding=True,
            max_length=config.training.max_length,
            return_tensors="pt",
        )
        encoding = {key: value.to(device) for key, value in encoding.items()}
        with torch.no_grad():
            logits = model(**encoding).logits
            batch_probs = torch.softmax(logits, dim=-1)[:, 1].detach().cpu().tolist()
        probabilities.extend(float(value) for value in batch_probs)
    return probabilities


def _pick_prompt_seed_code(row: dict) -> str:
    for field in ("augmentation_seed_code", "line_slice", "refined_code", "llm_slice", "static_slice"):
        value = row.get(field, "")
        if isinstance(value, list):
            value = "\n".join(str(item) for item in value)
        if isinstance(value, str) and value.strip():
            return value
    return ""


def _seed_group_key(row: dict) -> str:
    for field in ("original_idx", "fromIdx", "idx"):
        value = row.get(field)
        if value is None:
            continue
        text = str(value).strip()
        if text:
            return text
    return "unknown_seed"


def _composite_quality_score(
    detector_prob: float | None,
    full_metrics: dict[str, float],
    prompt_metrics: dict[str, float],
    anchor_metrics: dict[str, float],
    length_similarity: float,
) -> float:
    full_score = 0.7 * full_metrics["alignment_score"] + 0.3 * full_metrics["call_overlap"]
    prompt_score = 0.65 * prompt_metrics["alignment_score"] + 0.35 * prompt_metrics["call_overlap"]
    anchor_score = 0.6 * anchor_metrics["call_ratio"] + 0.4 * anchor_metrics["identifier_ratio"]
    if detector_prob is None:
        return 0.45 * prompt_score + 0.25 * full_score + 0.20 * anchor_score + 0.10 * length_similarity
    return 0.35 * detector_prob + 0.25 * prompt_score + 0.15 * full_score + 0.20 * anchor_score + 0.05 * length_similarity


def _rerank_rows_by_quality(
    rows: list[dict],
    *,
    min_quality_score: float = 0.0,
    max_per_seed: int | None = None,
) -> tuple[list[dict], dict[str, int]]:
    grouped: dict[str, list[dict]] = {}
    for row in rows:
        grouped.setdefault(str(row["quality_seed_group"]), []).append(row)

    kept_rows: list[dict] = []
    low_quality = 0
    over_seed_budget = 0
    for seed_key, group_rows in grouped.items():
        ranked_rows = sorted(
            group_rows,
            key=lambda item: (
                float(item.get("quality_score", 0.0)),
                float(item.get("quality_anchor_call_hits", 0.0)),
                float(item.get("quality_anchor_identifier_hits", 0.0)),
                float(item.get("quality_prompt_call_overlap", 0.0)),
                float(item.get("quality_prompt_alignment_score", 0.0)),
                float(item.get("generated_pred_prob_1", -1.0)),
                str(item.get("idx", "")),
            ),
            reverse=True,
        )

        kept_for_seed = 0
        for rank, row in enumerate(ranked_rows, start=1):
            row["quality_rank_within_seed"] = rank
            if float(row.get("quality_score", 0.0)) < min_quality_score:
                low_quality += 1
                continue
            if max_per_seed is not None and kept_for_seed >= max_per_seed:
                over_seed_budget += 1
                continue
            row["quality_seed_group"] = seed_key
            kept_rows.append(row)
            kept_for_seed += 1

    return kept_rows, {
        "low_quality_score": low_quality,
        "over_seed_budget": over_seed_budget,
    }


def filter_valid_samples(
    input_path: Path,
    output_path: Path,
    *,
    config: ExperimentConfig | None = None,
    detector_model_dir: Path | None = None,
    detector_min_prob: float | None = None,
    min_seed_alignment: float = 0.0,
    min_prompt_alignment: float = 0.0,
    min_quality_score: float = 0.0,
    max_per_seed: int | None = None,
    min_anchor_identifier_hits: int = 0,
    min_anchor_call_hits: int = 0,
    require_anchor_signal: bool = False,
) -> dict[str, int]:
    rows = list(iter_jsonl(input_path))
    prelim_rows: list[dict] = []
    seen_fingerprints: set[str] = set()
    empty_after_sanitize = 0
    invalid_syntax = 0
    duplicate_generated = 0
    same_as_seed = 0
    low_seed_alignment = 0
    low_prompt_alignment = 0
    low_anchor_signal = 0
    low_anchor_hits = 0
    for row in tqdm(rows, desc="AST Validation", unit="sample"):
        sanitized_code = sanitize_generated_function(row.get("func", ""))
        if not sanitized_code:
            empty_after_sanitize += 1
            continue
        cleaned_code = remove_comments_and_blank_lines(sanitized_code)
        code_fingerprint = fingerprint_code(cleaned_code)
        if not cleaned_code or not code_fingerprint:
            empty_after_sanitize += 1
            continue
        if not is_valid_syntax(cleaned_code):
            invalid_syntax += 1
            continue

        seed_code = str(row.get("seed_func", "") or "")
        prompt_seed_code = _pick_prompt_seed_code(row)
        seed_fingerprint = fingerprint_code(remove_comments_and_blank_lines(sanitize_generated_function(seed_code))) if seed_code else ""
        if seed_fingerprint and code_fingerprint == seed_fingerprint:
            same_as_seed += 1
            continue
        full_alignment_metrics = compute_seed_alignment_metrics(seed_code, cleaned_code) if seed_code else {
            "identifier_overlap": 0.0,
            "call_overlap": 0.0,
            "alignment_score": 0.0,
        }
        prompt_alignment_metrics = compute_seed_alignment_metrics(prompt_seed_code, cleaned_code) if prompt_seed_code else {
            "identifier_overlap": 0.0,
            "call_overlap": 0.0,
            "alignment_score": 0.0,
        }
        if seed_code and full_alignment_metrics["alignment_score"] < min_seed_alignment:
            low_seed_alignment += 1
            continue
        if prompt_seed_code and prompt_alignment_metrics["alignment_score"] < min_prompt_alignment:
            low_prompt_alignment += 1
            continue
        anchor_calls = list(row.get("augmentation_anchor_calls", []) or [])
        anchor_identifiers = list(row.get("augmentation_anchor_identifiers", []) or [])
        if not anchor_calls and not anchor_identifiers:
            inferred_anchors = build_anchor_signature(prompt_seed_code or seed_code, seed_code)
            anchor_calls = inferred_anchors["calls"]
            anchor_identifiers = inferred_anchors["identifiers"]
        anchor_metrics = compute_anchor_hit_metrics(
            cleaned_code,
            anchor_calls=anchor_calls,
            anchor_identifiers=anchor_identifiers,
        )
        expected_call_hits = min(min_anchor_call_hits, len(anchor_calls))
        expected_identifier_hits = min(min_anchor_identifier_hits, len(anchor_identifiers))
        if require_anchor_signal and not bool(anchor_metrics["has_anchor_signal"]):
            low_anchor_signal += 1
            continue
        if expected_call_hits and int(anchor_metrics["call_hits"]) < expected_call_hits:
            low_anchor_hits += 1
            continue
        if expected_identifier_hits and int(anchor_metrics["identifier_hits"]) < expected_identifier_hits:
            low_anchor_hits += 1
            continue
        if code_fingerprint in seen_fingerprints:
            duplicate_generated += 1
            continue

        seen_fingerprints.add(code_fingerprint)
        primary_alignment = max(full_alignment_metrics["alignment_score"], prompt_alignment_metrics["alignment_score"])
        length_similarity = compute_code_length_similarity(seed_code or prompt_seed_code, cleaned_code)
        new_row = dict(row)
        new_row["func"] = cleaned_code
        new_row["quality_seed_group"] = _seed_group_key(row)
        new_row["quality_full_identifier_overlap"] = full_alignment_metrics["identifier_overlap"]
        new_row["quality_full_call_overlap"] = full_alignment_metrics["call_overlap"]
        new_row["quality_full_alignment_score"] = full_alignment_metrics["alignment_score"]
        new_row["quality_prompt_identifier_overlap"] = prompt_alignment_metrics["identifier_overlap"]
        new_row["quality_prompt_call_overlap"] = prompt_alignment_metrics["call_overlap"]
        new_row["quality_prompt_alignment_score"] = prompt_alignment_metrics["alignment_score"]
        new_row["quality_identifier_overlap"] = max(
            full_alignment_metrics["identifier_overlap"],
            prompt_alignment_metrics["identifier_overlap"],
        )
        new_row["quality_call_overlap"] = max(
            full_alignment_metrics["call_overlap"],
            prompt_alignment_metrics["call_overlap"],
        )
        new_row["quality_alignment_score"] = primary_alignment
        new_row["quality_length_similarity"] = length_similarity
        new_row["quality_anchor_calls"] = anchor_calls
        new_row["quality_anchor_identifiers"] = anchor_identifiers
        new_row["quality_anchor_call_hits"] = anchor_metrics["call_hits"]
        new_row["quality_anchor_identifier_hits"] = anchor_metrics["identifier_hits"]
        new_row["quality_anchor_call_ratio"] = anchor_metrics["call_ratio"]
        new_row["quality_anchor_identifier_ratio"] = anchor_metrics["identifier_ratio"]
        new_row["quality_has_anchor_signal"] = anchor_metrics["has_anchor_signal"]
        prelim_rows.append(new_row)

    kept_rows = prelim_rows
    low_detector_confidence = 0
    detector_probabilities: list[float] | None = None
    if kept_rows and config is not None and detector_model_dir is not None and detector_min_prob is not None:
        detector_probabilities = score_rows_with_detector(kept_rows, config, detector_model_dir)
        filtered_rows: list[dict] = []
        for row, probability in zip(kept_rows, detector_probabilities, strict=True):
            row["generated_pred_prob_1"] = float(probability)
            row["generated_pred_label"] = int(probability >= detector_min_prob)
            if probability < detector_min_prob:
                low_detector_confidence += 1
                continue
            filtered_rows.append(row)
        kept_rows = filtered_rows
    elif kept_rows and config is not None and detector_model_dir is not None:
        detector_probabilities = score_rows_with_detector(kept_rows, config, detector_model_dir)
        for row, probability in zip(kept_rows, detector_probabilities, strict=True):
            row["generated_pred_prob_1"] = float(probability)

    for row in kept_rows:
        detector_prob = row.get("generated_pred_prob_1")
        row["quality_score"] = _composite_quality_score(
            float(detector_prob) if detector_prob is not None else None,
            {
                "alignment_score": float(row.get("quality_full_alignment_score", 0.0)),
                "call_overlap": float(row.get("quality_full_call_overlap", 0.0)),
            },
            {
                "alignment_score": float(row.get("quality_prompt_alignment_score", 0.0)),
                "call_overlap": float(row.get("quality_prompt_call_overlap", 0.0)),
            },
            {
                "call_ratio": float(row.get("quality_anchor_call_ratio", 0.0)),
                "identifier_ratio": float(row.get("quality_anchor_identifier_ratio", 0.0)),
            },
            float(row.get("quality_length_similarity", 0.0)),
        )

    rerank_stats = {
        "low_quality_score": 0,
        "over_seed_budget": 0,
    }
    if kept_rows:
        kept_rows, rerank_stats = _rerank_rows_by_quality(
            kept_rows,
            min_quality_score=min_quality_score,
            max_per_seed=max_per_seed,
        )

    write_jsonl(output_path, kept_rows)
    return {
        "total": len(rows),
        "kept": len(kept_rows),
        "empty_after_sanitize": empty_after_sanitize,
        "invalid_syntax": invalid_syntax,
        "duplicate_generated": duplicate_generated,
        "same_as_seed": same_as_seed,
        "low_seed_alignment": low_seed_alignment,
        "low_prompt_alignment": low_prompt_alignment,
        "low_anchor_signal": low_anchor_signal,
        "low_anchor_hits": low_anchor_hits,
        "low_detector_confidence": low_detector_confidence,
        "low_quality_score": rerank_stats["low_quality_score"],
        "over_seed_budget": rerank_stats["over_seed_budget"],
    }
