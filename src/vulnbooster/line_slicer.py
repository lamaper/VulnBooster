from __future__ import annotations

import json
import os
from collections import Counter
from dataclasses import dataclass
from pathlib import Path

from .code_utils import ensure_block_balance, normalize_code_line, stitch_function_header
from .config import ExperimentConfig
from .jsonl import iter_jsonl, write_jsonl


@dataclass(slots=True)
class AlignmentResult:
    labels: list[int]
    matched_line_numbers: list[int]
    unmatched_teacher_lines: list[str]


def align_teacher_slice_to_function(function_code: str, teacher_slice: str) -> AlignmentResult:
    function_lines = function_code.splitlines()
    teacher_lines = [line for line in teacher_slice.splitlines() if normalize_code_line(line)]

    normalized_function = [normalize_code_line(line) for line in function_lines]
    normalized_teacher = [normalize_code_line(line) for line in teacher_lines]

    labels = [0] * len(function_lines)
    matched_line_numbers: list[int] = []
    unmatched_teacher_lines: list[str] = []

    search_start = 0
    for teacher_raw, teacher_norm in zip(teacher_lines, normalized_teacher):
        found_index: int | None = None
        for idx in range(search_start, len(normalized_function)):
            if normalized_function[idx] == teacher_norm:
                found_index = idx
                search_start = idx + 1
                break

        if found_index is None:
            for idx, function_norm in enumerate(normalized_function):
                if function_norm == teacher_norm and labels[idx] == 0:
                    found_index = idx
                    break

        if found_index is None:
            unmatched_teacher_lines.append(teacher_raw)
            continue

        labels[found_index] = 1
        matched_line_numbers.append(found_index + 1)

    return AlignmentResult(
        labels=labels,
        matched_line_numbers=matched_line_numbers,
        unmatched_teacher_lines=unmatched_teacher_lines,
    )


def infer_static_line_numbers(row: dict) -> list[int]:
    raw_lines = row.get("raw_lines")
    if isinstance(raw_lines, list):
        numbers: list[int] = []
        for item in raw_lines:
            try:
                numbers.append(int(item))
            except (TypeError, ValueError):
                continue
        return sorted(set(numbers))

    static_slice = row.get("static_slice", "")
    if isinstance(row.get("code_lines"), list):
        static_slice = "\n".join(row["code_lines"])

    if not static_slice or not row.get("func"):
        return []

    alignment = align_teacher_slice_to_function(row["func"], static_slice)
    return alignment.matched_line_numbers


def build_line_slice_alignment_dataset(input_path: Path, output_path: Path) -> dict[str, int]:
    stats = Counter()
    output_rows: list[dict] = []

    for row in iter_jsonl(input_path):
        function_code = row.get("func", "")
        if not function_code.strip():
            stats["missing_function"] += 1
            continue

        teacher_source = ""
        teacher_slice = ""
        for field in ("refined_code", "line_slice", "llm_slice", "static_slice"):
            value = row.get(field, "")
            if isinstance(value, list):
                value = "\n".join(value)
            if isinstance(value, str) and value.strip():
                teacher_source = field
                teacher_slice = value
                break

        if not teacher_slice:
            stats["missing_teacher"] += 1
            continue

        alignment = align_teacher_slice_to_function(function_code, teacher_slice)
        static_line_numbers = infer_static_line_numbers(row)
        output_row = {
            "idx": row.get("idx"),
            "target": row.get("target"),
            "func": function_code,
            "teacher_slice": teacher_slice,
            "teacher_source": teacher_source,
            "line_labels": alignment.labels,
            "matched_teacher_line_numbers": alignment.matched_line_numbers,
            "static_line_numbers": static_line_numbers,
            "unmatched_teacher_lines": alignment.unmatched_teacher_lines,
            "cwe": row.get("cwe", []),
            "cve": row.get("cve", []),
        }
        output_rows.append(output_row)
        stats["written"] += 1
        stats[f"teacher_{teacher_source}"] += 1
        if alignment.unmatched_teacher_lines:
            stats["partial_alignments"] += 1

    write_jsonl(output_path, output_rows)
    stats["total"] = stats["written"] + stats["missing_function"] + stats["missing_teacher"]
    return dict(stats)


def reconstruct_line_slice(function_code: str, line_scores: list[float], threshold: float) -> tuple[str, list[int]]:
    function_lines = function_code.splitlines()
    selected_line_numbers = [index + 1 for index, score in enumerate(line_scores) if score >= threshold]
    if not selected_line_numbers:
        return "", []

    selected_line_numbers = ensure_block_balance(function_lines, selected_line_numbers)
    selected_code = "\n".join(function_lines[index - 1] for index in selected_line_numbers if 1 <= index <= len(function_lines))
    selected_code = stitch_function_header(selected_code, function_code)
    return selected_code, selected_line_numbers


class LineSlicerDataset:
    def __init__(self, file_path: Path, tokenizer, max_length: int, context_radius: int):
        import torch

        self.examples: list[dict] = []
        self.tokenizer = tokenizer
        self.max_length = max_length
        self.context_radius = context_radius
        self.torch = torch

        for row in iter_jsonl(file_path):
            func = row.get("func", "")
            line_labels = row.get("line_labels", [])
            static_line_numbers = set(int(item) for item in row.get("static_line_numbers", []))
            if not func or not line_labels:
                continue
            function_lines = func.splitlines()
            if len(function_lines) != len(line_labels):
                continue
            for line_index, label in enumerate(line_labels, start=1):
                prompt = build_line_prompt(
                    function_lines=function_lines,
                    candidate_line_number=line_index,
                    static_line_numbers=static_line_numbers,
                    context_radius=context_radius,
                )
                self.examples.append(
                    {
                        "idx": row.get("idx"),
                        "line_number": line_index,
                        "text": prompt,
                        "label": int(label),
                    }
                )

    def __len__(self) -> int:
        return len(self.examples)

    def __getitem__(self, index: int):
        item = self.examples[index]
        encoding = self.tokenizer(
            item["text"],
            truncation=True,
            padding="max_length",
            max_length=self.max_length,
            return_tensors="pt",
        )
        return {
            "input_ids": encoding["input_ids"].squeeze(0),
            "attention_mask": encoding["attention_mask"].squeeze(0),
            "labels": self.torch.tensor(item["label"], dtype=self.torch.long),
        }


def build_line_prompt(
    function_lines: list[str],
    candidate_line_number: int,
    static_line_numbers: set[int],
    context_radius: int,
) -> str:
    lower = max(1, candidate_line_number - context_radius)
    upper = min(len(function_lines), candidate_line_number + context_radius)
    selected_numbers = set(range(lower, upper + 1))
    selected_numbers.update(static_line_numbers)
    selected_numbers.add(candidate_line_number)

    rendered_lines: list[str] = []
    for line_number in sorted(selected_numbers):
        line = function_lines[line_number - 1]
        tags: list[str] = []
        if line_number == candidate_line_number:
            tags.append("TARGET")
        if line_number in static_line_numbers:
            tags.append("STATIC")
        tag_text = f"[{'|'.join(tags)}]" if tags else "[CTX]"
        rendered_lines.append(f"{tag_text}[L{line_number:03d}] {line}")

    static_summary = ",".join(str(num) for num in sorted(static_line_numbers)) if static_line_numbers else "none"
    return (
        "Task: predict whether the TARGET line belongs to a vulnerability-relevant slice.\n"
        f"StaticSliceLines: {static_summary}\n"
        "Context:\n"
        + "\n".join(rendered_lines)
    )


@dataclass(slots=True)
class LineSlicerTrainingResult:
    eval_metrics: dict[str, float]
    test_metrics: dict[str, float]
    output_dir: Path


def train_line_slicer(
    config: ExperimentConfig,
    train_path: Path,
    valid_path: Path,
    test_path: Path,
    output_dir: Path,
) -> LineSlicerTrainingResult:
    import numpy as np
    import torch
    from sklearn.metrics import accuracy_score, precision_recall_fscore_support
    from transformers import AutoModelForSequenceClassification, AutoTokenizer, DataCollatorWithPadding, Trainer, TrainingArguments

    os.environ["HF_ENDPOINT"] = config.runtime.hf_endpoint

    tokenizer = AutoTokenizer.from_pretrained(config.line_slicer.model_name)
    model = AutoModelForSequenceClassification.from_pretrained(config.line_slicer.model_name, num_labels=2)

    train_dataset = LineSlicerDataset(
        file_path=train_path,
        tokenizer=tokenizer,
        max_length=config.line_slicer.max_length,
        context_radius=config.line_slicer.context_radius,
    )
    valid_dataset = LineSlicerDataset(
        file_path=valid_path,
        tokenizer=tokenizer,
        max_length=config.line_slicer.max_length,
        context_radius=config.line_slicer.context_radius,
    )
    test_dataset = LineSlicerDataset(
        file_path=test_path,
        tokenizer=tokenizer,
        max_length=config.line_slicer.max_length,
        context_radius=config.line_slicer.context_radius,
    )

    label_counts = Counter(example["label"] for example in train_dataset.examples)
    print(f"Line slicer train examples: {len(train_dataset)} | label counts: {dict(label_counts)}")

    def compute_metrics(eval_pred):
        logits, labels = eval_pred
        probs = torch.softmax(torch.tensor(logits), dim=-1).numpy()
        preds = (probs[:, 1] >= config.line_slicer.threshold).astype(int)
        precision, recall, f1, _ = precision_recall_fscore_support(labels, preds, average="binary", zero_division=0)
        return {
            "accuracy": accuracy_score(labels, preds),
            "precision": precision,
            "recall": recall,
            "f1": f1,
        }

    training_args = TrainingArguments(
        output_dir=str(output_dir),
        learning_rate=config.line_slicer.learning_rate,
        per_device_train_batch_size=config.line_slicer.batch_size,
        per_device_eval_batch_size=config.line_slicer.batch_size,
        num_train_epochs=config.line_slicer.epochs,
        weight_decay=config.training.weight_decay,
        eval_strategy="epoch",
        save_strategy="epoch",
        load_best_model_at_end=True,
        metric_for_best_model="f1",
        logging_steps=50,
        seed=config.training.seed,
    )

    trainer = Trainer(
        model=model,
        args=training_args,
        train_dataset=train_dataset,
        eval_dataset=valid_dataset,
        processing_class=tokenizer,
        data_collator=DataCollatorWithPadding(tokenizer=tokenizer),
        compute_metrics=compute_metrics,
    )
    trainer.train()
    eval_metrics = trainer.evaluate(valid_dataset)
    test_metrics = trainer.evaluate(test_dataset)
    return LineSlicerTrainingResult(eval_metrics=eval_metrics, test_metrics=test_metrics, output_dir=output_dir)


def predict_line_slices(
    config: ExperimentConfig,
    input_path: Path,
    model_dir: Path,
    output_path: Path,
) -> dict[str, int]:
    import torch
    from transformers import AutoModelForSequenceClassification, AutoTokenizer

    tokenizer = AutoTokenizer.from_pretrained(model_dir)
    model = AutoModelForSequenceClassification.from_pretrained(model_dir)
    model.eval()

    output_rows: list[dict] = []
    stats = Counter()

    for row in iter_jsonl(input_path):
        function_code = row.get("func", "")
        if not function_code.strip():
            continue
        function_lines = function_code.splitlines()
        static_line_numbers = set(infer_static_line_numbers(row))

        line_scores: list[float] = []
        for line_number in range(1, len(function_lines) + 1):
            prompt = build_line_prompt(
                function_lines=function_lines,
                candidate_line_number=line_number,
                static_line_numbers=static_line_numbers,
                context_radius=config.line_slicer.context_radius,
            )
            encoding = tokenizer(
                prompt,
                truncation=True,
                padding="max_length",
                max_length=config.line_slicer.max_length,
                return_tensors="pt",
            )
            with torch.no_grad():
                logits = model(**encoding).logits
                probs = torch.softmax(logits, dim=-1)
            line_scores.append(float(probs[0][1]))

        line_slice, selected_line_numbers = reconstruct_line_slice(
            function_code=function_code,
            line_scores=line_scores,
            threshold=config.line_slicer.threshold,
        )
        new_row = dict(row)
        new_row["line_slice"] = line_slice
        new_row["line_slice_line_numbers"] = selected_line_numbers
        output_rows.append(new_row)
        stats["written"] += 1
        if line_slice.strip():
            stats["non_empty_slices"] += 1

    write_jsonl(output_path, output_rows)
    stats["total"] = stats["written"]
    return dict(stats)
