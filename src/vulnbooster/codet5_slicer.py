from __future__ import annotations

from collections import Counter
from dataclasses import dataclass
from pathlib import Path
import re

from .code_utils import ensure_block_balance, stitch_function_header
from .config import ExperimentConfig
from .env import configure_hf_endpoint
from .jsonl import iter_jsonl, write_jsonl
from .line_slicer import infer_static_line_numbers, resolve_model_artifact_dir


LINE_TAG_PATTERN = re.compile(r"\bL(\d{1,6})\b")


def format_line_tag(line_number: int, width: int = 3) -> str:
    return f"L{int(line_number):0{width}d}"


def parse_line_tags(text: str, *, max_line_number: int | None = None) -> list[int]:
    seen: set[int] = set()
    parsed: list[int] = []
    for match in LINE_TAG_PATTERN.finditer(text or ""):
        line_number = int(match.group(1))
        if line_number <= 0:
            continue
        if max_line_number is not None and line_number > max_line_number:
            continue
        if line_number in seen:
            continue
        seen.add(line_number)
        parsed.append(line_number)
    return parsed


def render_line_tags(line_numbers: list[int], width: int = 3) -> str:
    if not line_numbers:
        return "NONE"
    return " ".join(format_line_tag(line_number, width=width) for line_number in sorted(set(line_numbers)))


def render_numbered_function(function_code: str, width: int = 3) -> str:
    function_lines = function_code.splitlines()
    return "\n".join(f"{format_line_tag(index, width=width)} {line}" for index, line in enumerate(function_lines, start=1))


def build_codet5_input(function_code: str, static_line_numbers: list[int], width: int = 3) -> str:
    static_hints = render_line_tags(static_line_numbers, width=width)
    return (
        "Task: select the minimal vulnerability-relevant line tags from the function.\n"
        "Prefer a concise slice centered on the vulnerable data/control flow.\n"
        "Use static hints as anchors, but exclude unrelated header/footer/context lines.\n"
        "Do not output the whole function unless every line is required.\n"
        "Return only line tags separated by spaces.\n"
        f"StaticSliceHints: {static_hints}\n"
        "Function:\n"
        f"{render_numbered_function(function_code, width=width)}"
    )


def reconstruct_slice_from_line_numbers(function_code: str, line_numbers: list[int]) -> tuple[str, list[int]]:
    function_lines = function_code.splitlines()
    if not function_lines or not line_numbers:
        return "", []
    selected_line_numbers = ensure_block_balance(function_lines, sorted(set(line_numbers)))
    if not selected_line_numbers:
        return "", []
    selected_code = "\n".join(function_lines[index - 1] for index in selected_line_numbers if 1 <= index <= len(function_lines))
    return stitch_function_header(selected_code, function_code), selected_line_numbers


class CodeT5SliceDataset:
    def __init__(self, file_path: Path, tokenizer, max_input_length: int, max_target_length: int, line_number_width: int):
        self.examples: list[dict[str, str]] = []
        self.tokenizer = tokenizer
        self.max_input_length = max_input_length
        self.max_target_length = max_target_length
        self.line_number_width = line_number_width

        for row in iter_jsonl(file_path):
            function_code = row.get("func", "")
            target_line_numbers = [int(item) for item in row.get("matched_teacher_line_numbers", []) if int(item) > 0]
            if not function_code.strip() or not target_line_numbers:
                continue
            static_line_numbers = [int(item) for item in row.get("static_line_numbers", []) if int(item) > 0]
            self.examples.append(
                {
                    "input_text": build_codet5_input(function_code, static_line_numbers, width=line_number_width),
                    "target_text": render_line_tags(target_line_numbers, width=line_number_width),
                }
            )

    def __len__(self) -> int:
        return len(self.examples)

    def __getitem__(self, index: int) -> dict[str, list[int]]:
        item = self.examples[index]
        model_inputs = self.tokenizer(
            item["input_text"],
            truncation=True,
            max_length=self.max_input_length,
        )
        labels = self.tokenizer(
            text_target=item["target_text"],
            truncation=True,
            max_length=self.max_target_length,
        )
        model_inputs["labels"] = labels["input_ids"]
        return model_inputs


def _normalize_line_numbers(values, *, max_line_number: int | None = None) -> list[int]:
    numbers: list[int] = []
    seen: set[int] = set()
    if not isinstance(values, list):
        return numbers
    for item in values:
        try:
            line_number = int(item)
        except (TypeError, ValueError):
            continue
        if line_number <= 0:
            continue
        if max_line_number is not None and line_number > max_line_number:
            continue
        if line_number in seen:
            continue
        seen.add(line_number)
        numbers.append(line_number)
    return numbers


def build_sample_lookup_keys(row: dict) -> list[str]:
    keys: list[str] = []
    seen: set[str] = set()
    for field in ("idx", "fromIdx", "original_idx"):
        value = row.get(field)
        if value is None:
            continue
        candidates = [str(value).strip()]
        try:
            candidates.append(str(int(str(value).strip())))
        except (TypeError, ValueError):
            pass
        for candidate in candidates:
            if not candidate or candidate in seen:
                continue
            seen.add(candidate)
            keys.append(candidate)
    return keys


def _merge_metadata_row(base: dict, incoming: dict) -> dict:
    merged = dict(base)
    for field in (
        "static_line_numbers",
        "raw_lines",
        "code_lines",
        "static_slice",
        "teacher_slice",
        "teacher_source",
        "llm_slice",
        "line_slice",
        "refined_code",
    ):
        current = merged.get(field)
        if current in (None, "", []):
            candidate = incoming.get(field)
            if candidate not in (None, "", []):
                merged[field] = candidate
    return merged


def load_slice_metadata_lookup(*paths: Path) -> dict[str, dict]:
    lookup: dict[str, dict] = {}
    for path in paths:
        if path is None or not path.exists():
            continue
        for row in iter_jsonl(path):
            for key in build_sample_lookup_keys(row):
                existing = lookup.get(key, {})
                lookup[key] = _merge_metadata_row(existing, row)
    return lookup


def enrich_row_with_slice_metadata(row: dict, metadata_lookup: dict[str, dict]) -> tuple[dict, bool]:
    if not metadata_lookup:
        return dict(row), False
    enriched = dict(row)
    matched = False
    for key in build_sample_lookup_keys(row):
        metadata = metadata_lookup.get(key)
        if metadata is None:
            continue
        matched = True
        enriched = _merge_metadata_row(enriched, metadata)
    return enriched, matched


def prune_codet5_predicted_lines(
    predicted_line_numbers: list[int],
    static_line_numbers: list[int],
    *,
    function_length: int,
    static_hint_window: int,
    overpredict_function_ratio: float,
    overpredict_static_ratio: float,
    overpredict_static_margin: int,
) -> tuple[list[int], dict[str, int]]:
    predicted = _normalize_line_numbers(predicted_line_numbers, max_line_number=function_length)
    static = _normalize_line_numbers(static_line_numbers, max_line_number=function_length)
    stats: dict[str, int] = {}

    if not predicted:
        return predicted, stats
    if not static:
        return predicted, stats

    full_function_prediction = predicted == list(range(1, function_length + 1))
    too_wide_for_function = len(predicted) / max(1, function_length) >= overpredict_function_ratio
    too_wide_for_static = len(predicted) > max(
        len(static) + max(0, overpredict_static_margin),
        int(len(static) * overpredict_static_ratio),
    )
    if not (full_function_prediction or too_wide_for_function or too_wide_for_static):
        return predicted, stats

    allowed: set[int] = set()
    for line_number in static:
        lower = max(1, line_number - max(0, static_hint_window))
        upper = min(function_length, line_number + max(0, static_hint_window))
        allowed.update(range(lower, upper + 1))

    pruned = [line_number for line_number in predicted if line_number in allowed]
    if not pruned:
        pruned = list(static)
        stats["pruned_to_static_fallback"] = 1

    stats["overpredict_pruned"] = 1
    if full_function_prediction:
        stats["full_function_prediction"] = 1
    return pruned, stats


def _count_line_segments(line_numbers: list[int]) -> int:
    if not line_numbers:
        return 0
    segment_count = 1
    for prev, current in zip(line_numbers, line_numbers[1:]):
        if current != prev + 1:
            segment_count += 1
    return segment_count


def score_codet5_candidate(
    predicted_line_numbers: list[int],
    static_line_numbers: list[int],
    *,
    function_length: int,
) -> dict[str, float | int]:
    predicted = sorted(set(int(item) for item in predicted_line_numbers if int(item) > 0))
    static = sorted(set(int(item) for item in static_line_numbers if int(item) > 0))
    if not predicted:
        return {
            "score": -1.0,
            "static_precision": 0.0,
            "static_recall": 0.0,
            "static_f1": 0.0,
            "compactness": 0.0,
            "density": 0.0,
            "continuity": 0.0,
            "segment_count": 0,
            "slice_ratio": 0.0,
        }

    overlap = len(set(predicted) & set(static))
    static_precision = overlap / len(predicted) if predicted else 0.0
    static_recall = overlap / len(static) if static else 0.0
    static_f1 = (
        2.0 * static_precision * static_recall / (static_precision + static_recall)
        if (static_precision + static_recall)
        else 0.0
    )

    span = max(1, predicted[-1] - predicted[0] + 1)
    density = len(predicted) / span
    slice_ratio = len(predicted) / max(1, function_length)
    compactness = 1.0 - min(1.0, slice_ratio)
    segment_count = _count_line_segments(predicted)
    continuity = 1.0 / max(1, segment_count)

    if static:
        score = (
            0.45 * static_f1
            + 0.20 * static_precision
            + 0.10 * static_recall
            + 0.10 * compactness
            + 0.10 * density
            + 0.05 * continuity
        )
    else:
        score = 0.40 * compactness + 0.35 * density + 0.25 * continuity

    return {
        "score": score,
        "static_precision": static_precision,
        "static_recall": static_recall,
        "static_f1": static_f1,
        "compactness": compactness,
        "density": density,
        "continuity": continuity,
        "segment_count": segment_count,
        "slice_ratio": slice_ratio,
    }


def select_best_codet5_candidate(
    decoded_candidates: list[str],
    static_line_numbers: list[int],
    *,
    function_length: int,
    static_hint_window: int,
    overpredict_function_ratio: float,
    overpredict_static_ratio: float,
    overpredict_static_margin: int,
) -> tuple[list[int], dict[str, float | int], list[dict[str, float | int | str | list[int]]]]:
    candidate_debug: list[dict[str, float | int | str | list[int]]] = []
    seen_predictions: set[tuple[int, ...]] = set()
    best_lines: list[int] = []
    best_metrics: dict[str, float | int] = {
        "score": -1.0,
        "static_precision": 0.0,
        "static_recall": 0.0,
        "static_f1": 0.0,
        "compactness": 0.0,
        "density": 0.0,
        "continuity": 0.0,
        "segment_count": 0,
        "slice_ratio": 0.0,
    }

    for rank, decoded in enumerate(decoded_candidates, start=1):
        parsed = parse_line_tags(decoded, max_line_number=function_length)
        pruned, prune_stats = prune_codet5_predicted_lines(
            parsed,
            static_line_numbers,
            function_length=function_length,
            static_hint_window=static_hint_window,
            overpredict_function_ratio=overpredict_function_ratio,
            overpredict_static_ratio=overpredict_static_ratio,
            overpredict_static_margin=overpredict_static_margin,
        )
        key = tuple(pruned)
        if key in seen_predictions:
            continue
        seen_predictions.add(key)
        metrics = score_codet5_candidate(pruned, static_line_numbers, function_length=function_length)
        candidate_entry: dict[str, float | int | str | list[int]] = {
            "rank": rank,
            "decoded": decoded,
            "parsed_line_numbers": parsed,
            "selected_line_numbers": pruned,
            **metrics,
            **prune_stats,
        }
        candidate_debug.append(candidate_entry)

        candidate_sort_key = (
            float(metrics["score"]),
            float(metrics["static_precision"]),
            float(metrics["density"]),
            -len(pruned),
        )
        best_sort_key = (
            float(best_metrics["score"]),
            float(best_metrics["static_precision"]),
            float(best_metrics["density"]),
            -len(best_lines),
        )
        if candidate_sort_key > best_sort_key:
            best_lines = pruned
            best_metrics = metrics

    return best_lines, best_metrics, candidate_debug


def load_seq2seq_tokenizer(model_name_or_path: str | Path):
    from transformers import AutoTokenizer

    def _load(local_files_only: bool, use_fast: bool | None = None):
        kwargs = {"local_files_only": local_files_only}
        if use_fast is not None:
            kwargs["use_fast"] = use_fast
        return AutoTokenizer.from_pretrained(model_name_or_path, **kwargs)

    try:
        return _load(local_files_only=True)
    except OSError:
        pass
    except (TypeError, ValueError) as exc:
        message = str(exc).lower()
        if "addedtoken" not in message and "backend tokenizer" not in message and "input must be a list" not in message:
            raise
        try:
            return _load(local_files_only=True, use_fast=False)
        except OSError:
            return _load(local_files_only=False, use_fast=False)

    try:
        return _load(local_files_only=False)
    except (TypeError, ValueError) as exc:
        message = str(exc).lower()
        if "addedtoken" not in message and "backend tokenizer" not in message and "input must be a list" not in message:
            raise
        return _load(local_files_only=False, use_fast=False)


def load_seq2seq_model(model_name_or_path: str | Path):
    from transformers import AutoModelForSeq2SeqLM

    try:
        return AutoModelForSeq2SeqLM.from_pretrained(model_name_or_path, local_files_only=True)
    except (OSError, ValueError, AttributeError):
        return AutoModelForSeq2SeqLM.from_pretrained(model_name_or_path)


def _decode_predictions(tokenizer, token_ids) -> list[str]:
    import numpy as np

    if isinstance(token_ids, tuple):
        token_ids = token_ids[0]
    token_ids = np.where(token_ids == -100, tokenizer.pad_token_id, token_ids)
    return tokenizer.batch_decode(token_ids, skip_special_tokens=True)


def compute_line_set_metrics(predicted_texts: list[str], reference_texts: list[str], *, max_line_number: int = 4096) -> dict[str, float]:
    true_positive = 0
    false_positive = 0
    false_negative = 0
    exact_match = 0
    empty_predictions = 0

    for predicted_text, reference_text in zip(predicted_texts, reference_texts):
        predicted = set(parse_line_tags(predicted_text, max_line_number=max_line_number))
        reference = set(parse_line_tags(reference_text, max_line_number=max_line_number))
        if not predicted:
            empty_predictions += 1
        if predicted == reference:
            exact_match += 1
        true_positive += len(predicted & reference)
        false_positive += len(predicted - reference)
        false_negative += len(reference - predicted)

    precision = true_positive / max(1, true_positive + false_positive)
    recall = true_positive / max(1, true_positive + false_negative)
    f1 = (2 * precision * recall / (precision + recall)) if (precision + recall) else 0.0
    total = max(1, len(reference_texts))
    return {
        "precision": precision,
        "recall": recall,
        "f1": f1,
        "exact_match": exact_match / total,
        "empty_rate": empty_predictions / total,
    }


@dataclass(slots=True)
class CodeT5SlicerTrainingResult:
    eval_metrics: dict[str, float]
    test_metrics: dict[str, float]
    output_dir: Path


def train_codet5_slicer(
    config: ExperimentConfig,
    train_path: Path,
    valid_path: Path,
    test_path: Path,
    output_dir: Path,
) -> CodeT5SlicerTrainingResult:
    import torch
    from transformers import DataCollatorForSeq2Seq, Seq2SeqTrainer, Seq2SeqTrainingArguments

    configure_hf_endpoint(config.runtime.hf_endpoint)

    tokenizer = load_seq2seq_tokenizer(config.codet5_slicer.model_name)
    model = load_seq2seq_model(config.codet5_slicer.model_name)

    train_dataset = CodeT5SliceDataset(
        train_path,
        tokenizer,
        max_input_length=config.codet5_slicer.max_input_length,
        max_target_length=config.codet5_slicer.max_target_length,
        line_number_width=config.codet5_slicer.line_number_width,
    )
    valid_dataset = CodeT5SliceDataset(
        valid_path,
        tokenizer,
        max_input_length=config.codet5_slicer.max_input_length,
        max_target_length=config.codet5_slicer.max_target_length,
        line_number_width=config.codet5_slicer.line_number_width,
    )
    test_dataset = CodeT5SliceDataset(
        test_path,
        tokenizer,
        max_input_length=config.codet5_slicer.max_input_length,
        max_target_length=config.codet5_slicer.max_target_length,
        line_number_width=config.codet5_slicer.line_number_width,
    )

    print(
        "CodeT5 slicer examples:"
        f" train={len(train_dataset)} valid={len(valid_dataset)} test={len(test_dataset)}"
    )

    def compute_metrics(eval_pred):
        predictions, labels = eval_pred
        decoded_predictions = _decode_predictions(tokenizer, predictions)
        decoded_labels = _decode_predictions(tokenizer, labels)
        return compute_line_set_metrics(decoded_predictions, decoded_labels)

    training_args = Seq2SeqTrainingArguments(
        output_dir=str(output_dir),
        learning_rate=config.codet5_slicer.learning_rate,
        per_device_train_batch_size=config.codet5_slicer.batch_size,
        per_device_eval_batch_size=config.codet5_slicer.batch_size,
        num_train_epochs=config.codet5_slicer.epochs,
        weight_decay=config.training.weight_decay,
        eval_strategy="epoch",
        save_strategy="epoch",
        load_best_model_at_end=True,
        metric_for_best_model="f1",
        predict_with_generate=True,
        generation_max_length=config.codet5_slicer.generation_max_length,
        generation_num_beams=config.codet5_slicer.num_beams,
        logging_steps=20,
        seed=config.training.seed,
        dataloader_pin_memory=torch.cuda.is_available(),
        report_to=[],
        save_total_limit=2,
        save_only_model=True,
    )

    trainer = Seq2SeqTrainer(
        model=model,
        args=training_args,
        train_dataset=train_dataset,
        eval_dataset=valid_dataset,
        tokenizer=tokenizer,
        data_collator=DataCollatorForSeq2Seq(tokenizer=tokenizer, model=model),
        compute_metrics=compute_metrics,
    )
    trainer.train()
    output_dir.mkdir(parents=True, exist_ok=True)
    trainer.save_model(str(output_dir))
    tokenizer.save_pretrained(output_dir)
    eval_metrics = trainer.evaluate(valid_dataset, metric_key_prefix="eval")
    test_metrics = trainer.evaluate(test_dataset, metric_key_prefix="test")
    return CodeT5SlicerTrainingResult(eval_metrics=eval_metrics, test_metrics=test_metrics, output_dir=output_dir)


def predict_codet5_slices(
    config: ExperimentConfig,
    input_path: Path,
    model_dir: Path,
    output_path: Path,
    metadata_paths: list[Path] | None = None,
) -> dict[str, int]:
    import torch

    configure_hf_endpoint(config.runtime.hf_endpoint)

    resolved_model_dir = resolve_model_artifact_dir(model_dir)
    tokenizer = load_seq2seq_tokenizer(resolved_model_dir)
    model = load_seq2seq_model(resolved_model_dir)
    model.eval()
    device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
    model.to(device)
    metadata_lookup = load_slice_metadata_lookup(*(metadata_paths or []))
    candidate_count = max(1, min(config.codet5_slicer.candidate_count, config.codet5_slicer.num_beams))

    output_rows: list[dict] = []
    stats = Counter()

    for row in iter_jsonl(input_path):
        enriched_row, metadata_hit = enrich_row_with_slice_metadata(row, metadata_lookup)
        if metadata_hit:
            stats["metadata_hits"] += 1

        function_code = enriched_row.get("func", "")
        if not function_code.strip():
            continue
        function_lines = function_code.splitlines()
        static_line_numbers = infer_static_line_numbers(enriched_row)
        if static_line_numbers:
            stats["static_hint_rows"] += 1
        input_text = build_codet5_input(
            function_code=function_code,
            static_line_numbers=static_line_numbers,
            width=config.codet5_slicer.line_number_width,
        )
        encoding = tokenizer(
            input_text,
            truncation=True,
            max_length=config.codet5_slicer.max_input_length,
            return_tensors="pt",
        )
        encoding = {key: value.to(device) for key, value in encoding.items()}
        with torch.no_grad():
            generated = model.generate(
                **encoding,
                max_new_tokens=config.codet5_slicer.generation_max_length,
                num_beams=config.codet5_slicer.num_beams,
                num_return_sequences=candidate_count,
            )
        decoded_candidates = tokenizer.batch_decode(generated, skip_special_tokens=True)
        predicted_line_numbers, selection_metrics, candidate_debug = select_best_codet5_candidate(
            decoded_candidates,
            static_line_numbers,
            function_length=len(function_lines),
            static_hint_window=config.codet5_slicer.static_hint_window,
            overpredict_function_ratio=config.codet5_slicer.overpredict_function_ratio,
            overpredict_static_ratio=config.codet5_slicer.overpredict_static_ratio,
            overpredict_static_margin=config.codet5_slicer.overpredict_static_margin,
        )
        stats["candidate_rows"] += 1
        stats["candidate_total"] += len(decoded_candidates)
        stats["unique_candidate_total"] += len(candidate_debug)
        if candidate_debug:
            stats["candidate_rows_non_empty"] += 1
        if any(int(item.get("overpredict_pruned", 0)) for item in candidate_debug):
            stats["candidate_rows_pruned"] += 1
        if not predicted_line_numbers and config.codet5_slicer.use_static_slice_fallback:
            predicted_line_numbers = static_line_numbers
            stats["fallback_static"] += 1

        line_slice, selected_line_numbers = reconstruct_slice_from_line_numbers(function_code, predicted_line_numbers)
        new_row = dict(enriched_row)
        new_row["line_slice"] = line_slice
        new_row["line_slice_line_numbers"] = selected_line_numbers
        new_row["line_slice_backend"] = "codet5"
        new_row["line_slice_raw_prediction"] = decoded_candidates[0] if decoded_candidates else ""
        new_row["line_slice_raw_candidates"] = decoded_candidates
        new_row["line_slice_candidate_debug"] = candidate_debug
        new_row["line_slice_selection_score"] = float(selection_metrics["score"])
        new_row["line_slice_selection_static_precision"] = float(selection_metrics["static_precision"])
        new_row["line_slice_selection_static_recall"] = float(selection_metrics["static_recall"])
        new_row["line_slice_selection_slice_ratio"] = float(selection_metrics["slice_ratio"])
        output_rows.append(new_row)

        stats["written"] += 1
        if predicted_line_numbers:
            stats["predicted_non_empty"] += 1
        if line_slice.strip():
            stats["non_empty_slices"] += 1

    write_jsonl(output_path, output_rows)
    stats["total"] = stats["written"]
    return dict(stats)
