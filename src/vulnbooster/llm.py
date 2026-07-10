from __future__ import annotations

import asyncio
import os
import re
from pathlib import Path
from typing import Any

from openai import AsyncOpenAI
from tqdm.asyncio import tqdm

from .code_utils import project_slice_onto_original, sanitize_generated_function
from .config import ExperimentConfig
from .jsonl import iter_jsonl, write_jsonl


TICK3 = "```"


def extract_code_block(response_text: str, min_length: int = 10) -> tuple[str, bool]:
    if not response_text:
        return "", False

    text_no_think = re.sub(r"<think>.*?</think>", "", response_text, flags=re.DOTALL | re.IGNORECASE).strip()
    pattern = re.compile(TICK3 + r"(?:cpp|c|c\+\+)?\s*\n?(.*?)\n?\s*" + TICK3, re.DOTALL | re.IGNORECASE)
    matches = pattern.findall(text_no_think)

    if matches:
        extracted = matches[0].strip()
    elif "{" in text_no_think and ";" in text_no_think:
        extracted = text_no_think.strip()
    else:
        return "", False

    lowered = extracted.lower()
    if "no vulnerability" in lowered or "cannot identify" in lowered:
        return "", False
    if len(extracted) < min_length:
        return "", False
    return extracted, True

class DeepSeekChatClient:
    def __init__(self, config: ExperimentConfig):
        self.config = config
        api_key = os.environ.get(config.llm.api_key_env, "")
        self.client = AsyncOpenAI(api_key=api_key, base_url=config.llm.base_url)

    async def complete(self, messages: list[dict[str, str]], temperature: float | None = None, timeout: float = 60.0) -> str:
        last_error: Exception | None = None
        for attempt in range(self.config.llm.max_retries):
            try:
                response = await self.client.chat.completions.create(
                    model=self.config.llm.model_name,
                    messages=messages,
                    temperature=self.config.llm.temperature if temperature is None else temperature,
                    max_tokens=self.config.llm.max_tokens,
                    timeout=timeout,
                )
                content = response.choices[0].message.content
                if not content or not content.strip():
                    raise ValueError("empty llm response")
                return content
            except Exception as exc:
                last_error = exc
                if attempt == self.config.llm.max_retries - 1:
                    break
                await asyncio.sleep(self.config.llm.retry_delay_seconds * (2 ** attempt))
        raise RuntimeError(f"LLM request failed: {last_error}")


class LLMPreFilter:
    SYSTEM_PROMPT = (
        "You are an expert C/C++ security analyst. Your task is to extract a semantically complete, "
        "concise Vulnerability-Relevant Region from the provided function. Strictly follow the extraction "
        "rules provided in the user message and output only the final code block."
    )

    USER_PROMPT_TEMPLATE = f"""Please analyze the following C/C++ function and Extract the Vulnerability-Relevant Region by strictly adhering to the rules below:

[Extraction Rules]
1. Identify the Vulnerability Seed: Locate the exact vulnerable lines.
2. Expand via Data Dependency: Include definitions and sources of variables used in the vulnerable line.
3. Expand via Control Dependency: Include conditional statements that guard or trigger the vulnerable line.
4. Basic Block Closure: Ensure the snippet contains the complete basic block.
5. Length & Density Control: Target 5-20 lines demonstrating a 'Context + Action' pattern.

[Output Constraints]
- Return ONLY the extracted code within a single {TICK3}cpp block.
- Preserve original indentation, variable names, and line structure.

[Function to Analyze]
{TICK3}cpp
{{code}}
{TICK3}"""

    def __init__(self, config: ExperimentConfig):
        self.config = config
        self.client = DeepSeekChatClient(config)

    async def _process_row(self, row: dict[str, Any], semaphore: asyncio.Semaphore) -> dict[str, Any]:
        cleaned = {
            "idx": row.get("idx"),
            "func": row.get("func", ""),
            "target": row.get("target"),
            "cwe": row.get("cwe", []),
            "cve": row.get("cve", []),
        }
        func_code = cleaned["func"]
        if not func_code:
            cleaned["llm_slice"] = ""
            return cleaned

        user_prompt = self.USER_PROMPT_TEMPLATE.replace("{code}", func_code)
        async with semaphore:
            try:
                response = await self.client.complete(
                    [
                        {"role": "system", "content": self.SYSTEM_PROMPT},
                        {"role": "user", "content": user_prompt},
                    ],
                    timeout=40.0,
                )
                pure_slice, ok = extract_code_block(response)
                cleaned["llm_slice"] = project_slice_onto_original(pure_slice, func_code) if ok else ""
            except Exception:
                cleaned["llm_slice"] = ""
        return cleaned

    def run(self, input_path: Path, output_path: Path) -> dict[str, int]:
        rows = list(iter_jsonl(input_path))

        async def _run_all() -> list[dict[str, Any]]:
            semaphore = asyncio.Semaphore(self.config.llm.concurrency_limit)
            tasks = [self._process_row(row, semaphore) for row in rows]
            results: list[dict[str, Any]] = []
            for coro in tqdm(asyncio.as_completed(tasks), total=len(tasks), desc="LLM Pre-filter", unit="sample"):
                results.append(await coro)
            return results

        results = asyncio.run(_run_all())
        write_jsonl(output_path, results)
        success = sum(1 for row in results if row.get("llm_slice"))
        return {"total": len(results), "success": success}


class LLMFusionRefiner:
    SYSTEM_PROMPT = (
        "You are an expert C/C++ security analyst. Your task is to fuse and refine two code snippets into a "
        "semantically complete, concise vulnerability-relevant region. Strictly follow the refinement rules "
        "and output only the final code block."
    )

    USER_PROMPT_TEMPLATE = f"""Refine the following two code snippets into one high-quality vulnerability-relevant region:

[Static Slice]
{TICK3}cpp
{{static_slice}}
{TICK3}

[Initial Screening]
{TICK3}cpp
{{initial_screening}}
{TICK3}

[Refinement Rules]
1. Align both snippets and preserve missing variable definitions and control conditions.
2. Remove redundant declarations and unrelated code.
3. Preserve complete basic blocks.
4. Target 5-20 lines with high semantic density.

[Output Constraints]
- Return only one {TICK3}cpp block.
- Preserve original indentation and variable names.
"""

    def __init__(self, config: ExperimentConfig):
        self.config = config
        self.client = DeepSeekChatClient(config)

    async def _process_row(self, row: dict[str, Any], semaphore: asyncio.Semaphore) -> dict[str, Any]:
        original_code = row.get("func", "")
        static_slice = row.get("static_slice", "")
        llm_slice = row.get("llm_slice", "")

        if not static_slice and llm_slice:
            row["refined_code"] = project_slice_onto_original(llm_slice, original_code)
            return row
        if static_slice and not llm_slice:
            row["refined_code"] = project_slice_onto_original(static_slice, original_code)
            return row
        if not static_slice and not llm_slice:
            row["refined_code"] = original_code
            return row

        prompt = self.USER_PROMPT_TEMPLATE.format(
            static_slice=static_slice,
            initial_screening=llm_slice,
        )
        async with semaphore:
            try:
                response = await self.client.complete(
                    [
                        {"role": "system", "content": self.SYSTEM_PROMPT},
                        {"role": "user", "content": prompt},
                    ],
                    timeout=60.0,
                )
                refined, ok = extract_code_block(response)
                fallback = llm_slice or static_slice
                candidate = refined if ok else fallback
                row["refined_code"] = project_slice_onto_original(candidate, original_code)
            except Exception:
                fallback = llm_slice or static_slice or original_code
                row["refined_code"] = project_slice_onto_original(fallback, original_code)
        return row

    def run(self, static_path: Path, llm_path: Path, output_path: Path) -> dict[str, int]:
        static_rows = {str(row.get("fromIdx", row.get("idx"))): row for row in iter_jsonl(static_path)}
        llm_rows = {str(row.get("idx")): row for row in iter_jsonl(llm_path)}
        merged_rows: list[dict[str, Any]] = []

        for idx in sorted(set(static_rows) | set(llm_rows)):
            static_row = static_rows.get(idx, {})
            llm_row = llm_rows.get(idx, {})
            merged = dict(llm_row) if llm_row else dict(static_row)
            merged["idx"] = idx

            code_lines = static_row.get("code_lines", "")
            if isinstance(code_lines, list):
                merged["static_slice"] = "\n".join(code_lines)
            else:
                merged["static_slice"] = static_row.get("static_slice", "")

            llm_slice = llm_row.get("llm_slice", "")
            if isinstance(llm_slice, list):
                llm_slice = "\n".join(llm_slice)
            merged["llm_slice"] = sanitize_generated_function(llm_slice)
            merged_rows.append(merged)

        async def _run_all() -> list[dict[str, Any]]:
            semaphore = asyncio.Semaphore(self.config.llm.concurrency_limit)
            tasks = [self._process_row(row, semaphore) for row in merged_rows]
            results: list[dict[str, Any]] = []
            for coro in tqdm(asyncio.as_completed(tasks), total=len(tasks), desc="LLM Fusion", unit="sample"):
                results.append(await coro)
            return results

        results = asyncio.run(_run_all())
        write_jsonl(output_path, results)
        success = sum(1 for row in results if row.get("refined_code"))
        return {"total": len(results), "success": success}
