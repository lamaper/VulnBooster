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
        "Task: select vulnerability-relevant line tags from the function.\n"
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
) -> dict[str, int]:
    import torch

    configure_hf_endpoint(config.runtime.hf_endpoint)

    resolved_model_dir = resolve_model_artifact_dir(model_dir)
    tokenizer = load_seq2seq_tokenizer(resolved_model_dir)
    model = load_seq2seq_model(resolved_model_dir)
    model.eval()
    device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
    model.to(device)

    output_rows: list[dict] = []
    stats = Counter()

    for row in iter_jsonl(input_path):
        function_code = row.get("func", "")
        if not function_code.strip():
            continue
        function_lines = function_code.splitlines()
        static_line_numbers = infer_static_line_numbers(row)
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
            )
        decoded = tokenizer.decode(generated[0], skip_special_tokens=True)
        predicted_line_numbers = parse_line_tags(decoded, max_line_number=len(function_lines))
        if not predicted_line_numbers and config.codet5_slicer.use_static_slice_fallback:
            predicted_line_numbers = static_line_numbers
            stats["fallback_static"] += 1

        line_slice, selected_line_numbers = reconstruct_slice_from_line_numbers(function_code, predicted_line_numbers)
        new_row = dict(row)
        new_row["line_slice"] = line_slice
        new_row["line_slice_line_numbers"] = selected_line_numbers
        new_row["line_slice_backend"] = "codet5"
        new_row["line_slice_raw_prediction"] = decoded
        output_rows.append(new_row)

        stats["written"] += 1
        if predicted_line_numbers:
            stats["predicted_non_empty"] += 1
        if line_slice.strip():
            stats["non_empty_slices"] += 1

    write_jsonl(output_path, output_rows)
    stats["total"] = stats["written"]
    return dict(stats)
