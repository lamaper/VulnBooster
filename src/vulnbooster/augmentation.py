from __future__ import annotations

import asyncio
import copy
import re
from pathlib import Path
from typing import Any

from tqdm.asyncio import tqdm

from .code_utils import build_anchor_signature, compute_anchor_hit_metrics, fingerprint_code, sanitize_generated_function
from .config import ExperimentConfig
from .jsonl import iter_jsonl, write_jsonl
from .knowledge import CWEKnowledgeBase
from .llm import DeepSeekChatClient, TICK3


def _expected_anchor_requirements(config: ExperimentConfig, anchor_signature: dict[str, list[str]]) -> tuple[int, int]:
    expected_call_hits = min(config.augmentation.min_call_anchor_hits, len(anchor_signature["calls"]))
    expected_identifier_hits = min(config.augmentation.min_identifier_anchor_hits, len(anchor_signature["identifiers"]))
    return expected_call_hits, expected_identifier_hits


def _build_anchor_constraints(config: ExperimentConfig, source_code: str, seed_code: str) -> tuple[dict[str, list[str]], str]:
    anchor_signature = build_anchor_signature(
        source_code,
        seed_code,
        max_identifier_anchors=config.augmentation.max_identifier_anchors,
        max_call_anchors=config.augmentation.max_call_anchors,
    )
    expected_call_hits, expected_identifier_hits = _expected_anchor_requirements(config, anchor_signature)

    call_rule = "No API/function anchors are available; stay semantically close to the seed slice."
    if anchor_signature["calls"]:
        call_rule = (
            "Preserve the same vulnerability mechanism and reuse "
            f"at least {expected_call_hits or 1} of these API/function anchors: "
            f"{', '.join(anchor_signature['calls'])}."
        )

    identifier_rule = "No stable identifier anchors are available; preserve the same data/control-flow pattern."
    if anchor_signature["identifiers"]:
        identifier_rule = (
            "Reuse at least "
            f"{expected_identifier_hits or 1} of these variable/type/context anchors: "
            f"{', '.join(anchor_signature['identifiers'])}."
        )

    constraint_block = (
        "[Semantic Anchor Constraints]\n"
        "- Stay in the same software context as the seed. Do not switch to unrelated demos such as generic config readers, "
        "network utilities, or array toy examples unless the seed itself is about that context.\n"
        f"- {call_rule}\n"
        f"- {identifier_rule}\n"
        "- Keep the same critical operation order as the seed slice, including the same kind of guard checks, data movement, "
        "resource handling, or pointer/index usage that triggers the vulnerability.\n"
        "- Small renaming is allowed, but do not replace the seed's core APIs, data objects, or control structure with unrelated logic.\n"
        "- Do not copy the seed verbatim. Each candidate should change several non-comment lines, auxiliary state, or branch details while preserving the same vulnerability mechanism.\n"
        "- If you cannot satisfy these constraints, output nothing for that candidate."
    )
    return anchor_signature, constraint_block


def _passes_anchor_gate(config: ExperimentConfig, anchor_signature: dict[str, list[str]], candidate_code: str) -> tuple[bool, dict[str, float | int | list[str] | bool]]:
    metrics = compute_anchor_hit_metrics(
        candidate_code,
        anchor_calls=anchor_signature["calls"],
        anchor_identifiers=anchor_signature["identifiers"],
    )
    expected_call_hits, expected_identifier_hits = _expected_anchor_requirements(config, anchor_signature)
    meets_call_requirement = expected_call_hits == 0 or int(metrics["call_hits"]) >= expected_call_hits
    meets_identifier_requirement = expected_identifier_hits == 0 or int(metrics["identifier_hits"]) >= expected_identifier_hits
    if config.augmentation.require_anchor_signal and not bool(metrics["has_anchor_signal"]):
        return False, metrics
    return meets_call_requirement and meets_identifier_requirement, metrics


class CoTAugmenter:
    def __init__(self, config: ExperimentConfig):
        self.config = config
        self.client = DeepSeekChatClient(config)

    async def _run_chain(self, code: str, seed_code: str, semaphore: asyncio.Semaphore) -> tuple[list[str], dict[str, list[str]]]:
        anchor_signature, anchor_constraints = _build_anchor_constraints(self.config, code, seed_code)
        messages = [
            {
                "role": "system",
                "content": (
                    "I need your help to generate vulnerable C functions for data augmentation. "
                    "The generated functions must remain tightly aligned with the supplied seed slice and preserve its vulnerability mechanism."
                ),
            }
        ]
        steps = [
            f"\n```c\n{code}\n```\nStep 1: Summarize the application scenario in one short paragraph.",
            "Step 2: Identify the concrete vulnerability type and trigger condition.",
            (
                "Step 3: Extract the vulnerability pattern, critical data/control dependencies, "
                "and the key APIs/identifiers that must stay semantically aligned."
            ),
            (
                f"Step 4: Generate Similar Examples. Create exactly {self.config.augmentation.generate_k} "
                f"independent vulnerable C functions. Wrap each one in a single {TICK3}c block.\n\n"
                f"{anchor_constraints}"
            ),
        ]

        async with semaphore:
            for index, step in enumerate(steps):
                response = await self.client.complete(
                    messages + [{"role": "user", "content": step}],
                    temperature=0.25 if index == 3 else 0.1,
                    timeout=60.0,
                )
                messages.extend(
                    [
                        {"role": "user", "content": step},
                        {"role": "assistant", "content": response},
                    ]
                )
            matches = re.findall(r"```[a-zA-Z]*\s*(.*?)```", response, flags=re.DOTALL)
            return [match.strip() for match in matches if match.strip()], anchor_signature

    def run(self, input_path: Path, output_path: Path, code_field_priority: tuple[str, ...] = ("line_slice", "refined_code", "llm_slice", "func")) -> dict[str, int]:
        rows = list(iter_jsonl(input_path))

        def pick_code(row: dict[str, Any]) -> tuple[str, str]:
            for field in code_field_priority:
                value = row.get(field, "")
                if isinstance(value, str) and value.strip():
                    return field, value
            return "", ""

        async def _generate_for_row(
            row: dict[str, Any],
            semaphore: asyncio.Semaphore,
        ) -> tuple[dict[str, Any], str, str, list[str], dict[str, list[str]]]:
            source_field, code = pick_code(row)
            return row, source_field, code, *(await self._run_chain(code, str(row.get("func", "") or ""), semaphore))

        async def _run_all() -> tuple[list[list[dict[str, Any]]], int, int]:
            semaphore = asyncio.Semaphore(self.config.llm.concurrency_limit)
            task_rows = [row for row in rows if pick_code(row)[1]]
            tasks = [asyncio.create_task(_generate_for_row(row, semaphore)) for row in task_rows]
            results: list[list[dict[str, Any]]] = []
            anchor_rejected = 0
            copy_rejected = 0
            for task in tqdm(asyncio.as_completed(tasks), total=len(tasks), desc="CoT Augment", unit="sample"):
                row, source_field, source_code, generated_codes, anchor_signature = await task
                generated_rows: list[dict[str, Any]] = []
                seed_fingerprint = fingerprint_code(str(row.get("func", "") or ""))
                for i, gen_code in enumerate(generated_codes):
                    cleaned_code = sanitize_generated_function(gen_code)
                    if not cleaned_code:
                        continue
                    if seed_fingerprint and fingerprint_code(cleaned_code) == seed_fingerprint:
                        copy_rejected += 1
                        continue
                    passes_anchor_gate, anchor_metrics = _passes_anchor_gate(self.config, anchor_signature, cleaned_code)
                    if not passes_anchor_gate:
                        anchor_rejected += 1
                        continue
                    new_row = copy.deepcopy(row)
                    new_row["func"] = cleaned_code
                    new_row["seed_func"] = row.get("func", "")
                    new_row["original_idx"] = row.get("idx")
                    new_row["augmentation_seed_field"] = source_field
                    new_row["augmentation_seed_code"] = source_code
                    new_row["augmentation_anchor_calls"] = anchor_signature["calls"]
                    new_row["augmentation_anchor_identifiers"] = anchor_signature["identifiers"]
                    new_row["augmentation_anchor_call_hits"] = anchor_metrics["call_hits"]
                    new_row["augmentation_anchor_identifier_hits"] = anchor_metrics["identifier_hits"]
                    new_row["idx"] = f"{row.get('idx')}_cot_{i}"
                    new_row["is_cot_enhanced"] = True
                    generated_rows.append(new_row)
                results.append(generated_rows)
            return results, anchor_rejected, copy_rejected

        grouped_rows, anchor_rejected, copy_rejected = asyncio.run(_run_all())
        flat_rows = [row for group in grouped_rows for row in group]
        write_jsonl(output_path, flat_rows)
        return {
            "total": len(rows),
            "generated": len(flat_rows),
            "anchor_rejected": anchor_rejected,
            "copy_rejected": copy_rejected,
        }


class CWEAugmenter:
    SYSTEM_PROMPT = (
        "You are an expert C/C++ security analyst. Your task is to generate precise, "
        "semantically complete vulnerable functions strictly adhering to the provided rules."
    )

    def __init__(self, config: ExperimentConfig):
        self.config = config
        self.client = DeepSeekChatClient(config)
        self.kb = CWEKnowledgeBase(config.cwe.cache_file)

    def _build_prompt(
        self,
        row: dict[str, Any],
        source_field: str,
        code: str,
        seed_code: str,
        anchor_signature: dict[str, list[str]],
        anchor_constraints: str,
    ) -> str:
        cwe_raw = row.get("cwe", ["Unknown"])
        cwe_name = cwe_raw[0] if isinstance(cwe_raw, list) and cwe_raw else str(cwe_raw)
        kb_info = self.kb.get(cwe_name)
        seed_block = f"[Seed Full Function]\n{seed_code}\n\n" if seed_code and sanitize_generated_function(seed_code) != sanitize_generated_function(code) else ""
        slice_label = "Critical Seed Slice" if source_field != "func" else "Seed Code"
        anchor_summary = (
            f"[Required API Anchors]\n{', '.join(anchor_signature['calls']) or '(none)'}\n\n"
            f"[Required Identifier Anchors]\n{', '.join(anchor_signature['identifiers']) or '(none)'}\n\n"
        )
        if kb_info:
            return (
                "You are working on a software security task that requires generating semantically equivalent vulnerable C functions.\n\n"
                f"{seed_block}"
                f"[{slice_label}]\n{code}\n\n"
                f"[Vulnerability Definition]\n{kb_info['def']}\n\n"
                f"[Vulnerability Manifestation]\n{kb_info['manifest']}\n\n"
                f"{anchor_summary}"
                f"{anchor_constraints}\n\n"
                f"[Your Task]\nGenerate {self.config.augmentation.generate_k} new vulnerable C functions that stay semantically near the seed.\n\n"
                "[Additional Rules]\n"
                "- Preserve the same vulnerability trigger and the same kind of vulnerable operation.\n"
                "- Keep the same major API family, object family, and control-flow style as the seed.\n"
                "- Do not output unrelated examples that only share the same CWE label.\n\n"
                f"[Output Format]\nWrap EACH generated function in {TICK3}c blocks."
            )
        return (
            "You are working on a software security task that requires generating semantically equivalent vulnerable C functions.\n\n"
            f"{seed_block}"
            f"[{slice_label}]\n{code}\n\n"
            f"[CWE Type]\n{cwe_name}\n\n"
            f"{anchor_summary}"
            f"{anchor_constraints}\n\n"
            f"[Your Task]\nGenerate {self.config.augmentation.generate_k} new vulnerable C functions that stay semantically near the seed.\n\n"
            f"[Output Format]\nWrap EACH generated function in {TICK3}c blocks."
        )

    async def _generate(self, prompt: str, semaphore: asyncio.Semaphore) -> list[str]:
        async with semaphore:
            response = await self.client.complete(
                [
                    {"role": "system", "content": self.SYSTEM_PROMPT},
                    {"role": "user", "content": prompt},
                ],
                temperature=0.25,
                timeout=120.0,
            )
        text_no_think = re.sub(r"<think>.*?</think>", "", response, flags=re.DOTALL | re.IGNORECASE).strip()
        matches = re.findall(TICK3 + r"(?:cpp|c|c\+\+)?\s*\n(.*?)\n\s*" + TICK3, text_no_think, flags=re.DOTALL | re.IGNORECASE)
        return [match.strip() for match in matches if match.strip()]

    def run(self, input_path: Path, output_path: Path, code_field_priority: tuple[str, ...] = ("line_slice", "refined_code", "llm_slice", "func")) -> dict[str, int]:
        rows = [row for row in iter_jsonl(input_path) if row.get("target") == 1]

        def pick_code(row: dict[str, Any]) -> tuple[str, str]:
            for field in code_field_priority:
                value = row.get(field, "")
                if isinstance(value, str) and value.strip():
                    return field, value
            return "", ""

        prompt_rows = []
        for row in rows:
            source_field, code = pick_code(row)
            if code:
                seed_code = str(row.get("func", "") or "")
                anchor_signature, anchor_constraints = _build_anchor_constraints(self.config, code, seed_code)
                prompt_rows.append(
                    (
                        row,
                        source_field,
                        code,
                        seed_code,
                        anchor_signature,
                        self._build_prompt(row, source_field, code, seed_code, anchor_signature, anchor_constraints),
                    )
                )

        async def _generate_for_row(
            row: dict[str, Any],
            source_field: str,
            source_code: str,
            seed_code: str,
            anchor_signature: dict[str, list[str]],
            prompt: str,
            semaphore: asyncio.Semaphore,
        ) -> tuple[dict[str, Any], str, str, str, dict[str, list[str]], list[str]]:
            return row, source_field, source_code, seed_code, anchor_signature, await self._generate(prompt, semaphore)

        async def _run_all() -> tuple[list[list[dict[str, Any]]], int, int]:
            semaphore = asyncio.Semaphore(self.config.llm.concurrency_limit)
            tasks = [
                asyncio.create_task(_generate_for_row(row, source_field, source_code, seed_code, anchor_signature, prompt, semaphore))
                for row, source_field, source_code, seed_code, anchor_signature, prompt in prompt_rows
            ]
            results: list[list[dict[str, Any]]] = []
            anchor_rejected = 0
            copy_rejected = 0
            for task in tqdm(asyncio.as_completed(tasks), total=len(tasks), desc="CWE Augment", unit="sample"):
                row, source_field, source_code, seed_code, anchor_signature, generated = await task
                generated_rows: list[dict[str, Any]] = []
                seed_fingerprint = fingerprint_code(seed_code)
                for i, gen_code in enumerate(generated):
                    cleaned_code = sanitize_generated_function(gen_code)
                    if not cleaned_code:
                        continue
                    if seed_fingerprint and fingerprint_code(cleaned_code) == seed_fingerprint:
                        copy_rejected += 1
                        continue
                    passes_anchor_gate, anchor_metrics = _passes_anchor_gate(self.config, anchor_signature, cleaned_code)
                    if not passes_anchor_gate:
                        anchor_rejected += 1
                        continue
                    new_row = copy.deepcopy(row)
                    new_row["func"] = cleaned_code
                    new_row["seed_func"] = seed_code
                    new_row["original_idx"] = row.get("idx")
                    new_row["augmentation_seed_field"] = source_field
                    new_row["augmentation_seed_code"] = source_code
                    new_row["augmentation_anchor_calls"] = anchor_signature["calls"]
                    new_row["augmentation_anchor_identifiers"] = anchor_signature["identifiers"]
                    new_row["augmentation_anchor_call_hits"] = anchor_metrics["call_hits"]
                    new_row["augmentation_anchor_identifier_hits"] = anchor_metrics["identifier_hits"]
                    new_row["idx"] = f"{row.get('idx')}_cwe_{i}"
                    new_row["is_cwe_enhanced"] = True
                    generated_rows.append(new_row)
                results.append(generated_rows)
            return results, anchor_rejected, copy_rejected

        grouped_rows, anchor_rejected, copy_rejected = asyncio.run(_run_all())
        flat_rows = [row for group in grouped_rows for row in group]
        write_jsonl(output_path, flat_rows)
        return {
            "total": len(rows),
            "generated": len(flat_rows),
            "anchor_rejected": anchor_rejected,
            "copy_rejected": copy_rejected,
        }
