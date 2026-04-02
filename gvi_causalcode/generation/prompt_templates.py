PROMPT_MODE_DESCRIPTIONS = {
    "cot_chain": "四步链式分析，先分析场景与漏洞模式，再生成多个漏洞变体。",
    "direct_generate": "单轮直接生成，最轻量，适合先快速扩充数据。",
    "pattern_then_generate": "先总结漏洞模式，再按模式生成，稳定性通常比直接生成更好。",
    "self_refine_generate": "先生成，再自我筛选与重写，质量更高但耗时更多。",
}


def _code_block(code: str) -> str:
    return f"```c\n{code.strip()}\n```"


def build_turns(prompt_mode: str, code: str, num_variants: int) -> list[str]:
    seed_code = _code_block(code)

    if prompt_mode == "cot_chain":
        return [
            (
                f"{seed_code}\n"
                "Step 1: Application Scenario. Analyze the software context and the functional purpose of the seed C function. "
                "Keep the answer within 100 tokens."
            ),
            (
                "Step 2: Identify Vulnerability Type. Based on Step 1, identify the likely vulnerability category or weakness pattern. "
                "Keep the answer within 100 tokens."
            ),
            (
                "Step 3: Extract Vulnerability Pattern. Summarize the exploitable coding pattern, preconditions, and failure mechanism. "
                "Keep the answer within 120 tokens."
            ),
            (
                f"Step 4: Generate Similar Examples. Based on the previous analysis, create exactly {num_variants} independent vulnerable C functions. "
                "Each example must preserve the general application scenario and vulnerability pattern, but should vary variable names, control flow, "
                "data flow, and surrounding context. Output only fenced ```c``` code blocks."
            ),
        ]

    if prompt_mode == "direct_generate":
        return [
            (
                "You are given one vulnerable seed function.\n"
                f"{seed_code}\n"
                f"Generate exactly {num_variants} new vulnerable C functions inspired by this seed.\n"
                "Requirements:\n"
                "1. Keep the vulnerability real and compilable in spirit.\n"
                "2. Do not copy the seed verbatim.\n"
                "3. Vary identifiers, branch structure, and local logic.\n"
                "4. Keep each sample self-contained.\n"
                "5. Output only fenced ```c``` code blocks, one function per block."
            )
        ]

    if prompt_mode == "pattern_then_generate":
        return [
            (
                "You are given one vulnerable seed function.\n"
                f"{seed_code}\n"
                "First summarize the vulnerable behavior using the following headings only:\n"
                "- Scenario\n"
                "- Vulnerability Type\n"
                "- Vulnerability Pattern\n"
                "- Mutation Suggestions"
            ),
            (
                f"Now generate exactly {num_variants} new vulnerable C functions that follow the summarized vulnerability pattern. "
                "Make them diverse but still realistic. Output only fenced ```c``` code blocks."
            ),
        ]

    if prompt_mode == "self_refine_generate":
        return [
            (
                "You are given one vulnerable seed function.\n"
                f"{seed_code}\n"
                f"Generate {num_variants + 2} candidate vulnerable C functions. "
                "Keep them realistic and output only fenced ```c``` code blocks."
            ),
            (
                f"From your previous candidates, keep the best {num_variants} functions only. "
                "Improve weak ones if needed so that the final set is diverse, realistic, and still vulnerable. "
                "Output only fenced ```c``` code blocks."
            ),
        ]

    raise ValueError(
        f"未知的 PROMPT_MODE: {prompt_mode}。可选值: {', '.join(PROMPT_MODE_DESCRIPTIONS)}"
    )
