from __future__ import annotations

import asyncio
import copy
import re
from pathlib import Path
from typing import Any

from tqdm.asyncio import tqdm

from .config import ExperimentConfig
from .jsonl import iter_jsonl, write_jsonl
from .knowledge import CWEKnowledgeBase
from .llm import DeepSeekChatClient, TICK3


class CoTAugmenter:
    def __init__(self, config: ExperimentConfig):
        self.config = config
        self.client = DeepSeekChatClient(config)

    async def _run_chain(self, code: str, semaphore: asyncio.Semaphore) -> list[str]:
        messages = [
            {
                "role": "system",
                "content": "I need your help to generate some vulnerable C functions to train our ML model.",
            }
        ]
        steps = [
            f"\n```c\n{code}\n```\nStep 1: Application Scenario.",
            "Step 2: Identify Vulnerability Type.",
            "Step 3: Extract Vulnerability Pattern.",
            (
                f"Step 4: Generate Similar Examples. Create exactly {self.config.augmentation.generate_k} "
                f"independent vulnerable C functions. Wrap each one in a single {TICK3}c block."
            ),
        ]

        async with semaphore:
            for index, step in enumerate(steps):
                response = await self.client.complete(
                    messages + [{"role": "user", "content": step}],
                    temperature=0.6 if index == 3 else 0.1,
                    timeout=60.0,
                )
                messages.extend(
                    [
                        {"role": "user", "content": step},
                        {"role": "assistant", "content": response},
                    ]
                )
            matches = re.findall(r"```[a-zA-Z]*\s*(.*?)```", response, flags=re.DOTALL)
            return [match.strip() for match in matches if match.strip()]

    def run(self, input_path: Path, output_path: Path, code_field_priority: tuple[str, ...] = ("refined_code", "line_slice", "llm_slice", "func")) -> dict[str, int]:
        rows = list(iter_jsonl(input_path))

        def pick_code(row: dict[str, Any]) -> str:
            for field in code_field_priority:
                value = row.get(field, "")
                if isinstance(value, str) and value.strip():
                    return value
            return ""

        async def _generate_for_row(row: dict[str, Any], semaphore: asyncio.Semaphore) -> tuple[dict[str, Any], list[str]]:
            return row, await self._run_chain(pick_code(row), semaphore)

        async def _run_all() -> list[list[dict[str, Any]]]:
            semaphore = asyncio.Semaphore(self.config.llm.concurrency_limit)
            task_rows = [row for row in rows if pick_code(row)]
            tasks = [asyncio.create_task(_generate_for_row(row, semaphore)) for row in task_rows]
            results: list[list[dict[str, Any]]] = []
            for task in tqdm(asyncio.as_completed(tasks), total=len(tasks), desc="CoT Augment", unit="sample"):
                row, generated_codes = await task
                generated_rows: list[dict[str, Any]] = []
                for i, gen_code in enumerate(generated_codes):
                    new_row = copy.deepcopy(row)
                    new_row["func"] = gen_code
                    new_row["original_idx"] = row.get("idx")
                    new_row["idx"] = f"{row.get('idx')}_cot_{i}"
                    new_row["is_cot_enhanced"] = True
                    generated_rows.append(new_row)
                results.append(generated_rows)
            return results

        grouped_rows = asyncio.run(_run_all())
        flat_rows = [row for group in grouped_rows for row in group]
        write_jsonl(output_path, flat_rows)
        return {"total": len(rows), "generated": len(flat_rows)}


class CWEAugmenter:
    SYSTEM_PROMPT = (
        "You are an expert C/C++ security analyst. Your task is to generate precise, "
        "semantically complete vulnerable functions strictly adhering to the provided rules."
    )

    def __init__(self, config: ExperimentConfig):
        self.config = config
        self.client = DeepSeekChatClient(config)
        self.kb = CWEKnowledgeBase(config.cwe.cache_file)

    def _build_prompt(self, row: dict[str, Any], code: str) -> str:
        cwe_raw = row.get("cwe", ["Unknown"])
        cwe_name = cwe_raw[0] if isinstance(cwe_raw, list) and cwe_raw else str(cwe_raw)
        kb_info = self.kb.get(cwe_name)
        if kb_info:
            return (
                "You are working on a software security task that requires generating semantically equivalent vulnerable C functions.\n\n"
                f"[Seed Code]\n{code}\n\n"
                f"[Vulnerability Definition]\n{kb_info['def']}\n\n"
                f"[Vulnerability Manifestation]\n{kb_info['manifest']}\n\n"
                f"[Your Task]\nGenerate {self.config.augmentation.generate_k} new vulnerable C functions.\n\n"
                f"[Output Format]\nWrap EACH generated function in {TICK3}c blocks."
            )
        return (
            "You are working on a software security task that requires generating semantically equivalent vulnerable C functions.\n\n"
            f"[Seed Code]\n{code}\n\n"
            f"[CWE Type]\n{cwe_name}\n\n"
            f"[Your Task]\nGenerate {self.config.augmentation.generate_k} new vulnerable C functions.\n\n"
            f"[Output Format]\nWrap EACH generated function in {TICK3}c blocks."
        )

    async def _generate(self, prompt: str, semaphore: asyncio.Semaphore) -> list[str]:
        async with semaphore:
            response = await self.client.complete(
                [
                    {"role": "system", "content": self.SYSTEM_PROMPT},
                    {"role": "user", "content": prompt},
                ],
                temperature=0.7,
                timeout=120.0,
            )
        text_no_think = re.sub(r"<think>.*?</think>", "", response, flags=re.DOTALL | re.IGNORECASE).strip()
        matches = re.findall(TICK3 + r"(?:cpp|c|c\+\+)?\s*\n(.*?)\n\s*" + TICK3, text_no_think, flags=re.DOTALL | re.IGNORECASE)
        return [match.strip() for match in matches if match.strip()]

    def run(self, input_path: Path, output_path: Path, code_field_priority: tuple[str, ...] = ("refined_code", "line_slice", "llm_slice", "func")) -> dict[str, int]:
        rows = [row for row in iter_jsonl(input_path) if row.get("target") == 1]

        def pick_code(row: dict[str, Any]) -> str:
            for field in code_field_priority:
                value = row.get(field, "")
                if isinstance(value, str) and value.strip():
                    return value
            return ""

        prompt_rows = []
        for row in rows:
            code = pick_code(row)
            if code:
                prompt_rows.append((row, self._build_prompt(row, code)))

        async def _generate_for_row(row: dict[str, Any], prompt: str, semaphore: asyncio.Semaphore) -> tuple[dict[str, Any], list[str]]:
            return row, await self._generate(prompt, semaphore)

        async def _run_all() -> list[list[dict[str, Any]]]:
            semaphore = asyncio.Semaphore(self.config.llm.concurrency_limit)
            tasks = [asyncio.create_task(_generate_for_row(row, prompt, semaphore)) for row, prompt in prompt_rows]
            results: list[list[dict[str, Any]]] = []
            for task in tqdm(asyncio.as_completed(tasks), total=len(tasks), desc="CWE Augment", unit="sample"):
                row, generated = await task
                generated_rows: list[dict[str, Any]] = []
                for i, gen_code in enumerate(generated):
                    new_row = copy.deepcopy(row)
                    new_row["func"] = gen_code
                    new_row["original_idx"] = row.get("idx")
                    new_row["idx"] = f"{row.get('idx')}_cwe_{i}"
                    new_row["is_cwe_enhanced"] = True
                    generated_rows.append(new_row)
                results.append(generated_rows)
            return results

        grouped_rows = asyncio.run(_run_all())
        flat_rows = [row for group in grouped_rows for row in group]
        write_jsonl(output_path, flat_rows)
        return {"total": len(rows), "generated": len(flat_rows)}
