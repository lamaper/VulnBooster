import argparse
import json
import os
import time
import urllib.error
import urllib.parse
import urllib.request
from typing import Dict, List

from tqdm import tqdm

import config
from prompt_templates import PROMPT_MODE_DESCRIPTIONS, build_turns


def parse_args():
    parser = argparse.ArgumentParser(description="轻量漏洞生成入口，支持纯提示词与链式提示词模式。")
    parser.add_argument(
        "--prompt-mode",
        default=config.PROMPT_MODE,
        choices=sorted(PROMPT_MODE_DESCRIPTIONS.keys()),
        help="生成策略。",
    )
    parser.add_argument("--limit", type=int, default=config.MAX_SAMPLES, help="最多处理多少条种子。0 表示全部处理。")
    parser.add_argument("--start-index", type=int, default=0, help="从第几条种子开始。")
    parser.add_argument("--num-variants", type=int, default=config.NUM_VARIANTS, help="每条种子希望生成多少个漏洞变体。")
    parser.add_argument("--temperature", type=float, default=config.TEMPERATURE, help="采样温度。")
    parser.add_argument("--top-p", type=float, default=config.TOP_P, help="Top-p。")
    parser.add_argument("--max-output-tokens", type=int, default=config.MAX_OUTPUT_TOKENS, help="最大输出 token。")
    parser.add_argument("--request-interval", type=float, default=config.REQUEST_INTERVAL_SEC, help="每次请求之间的等待秒数。")
    parser.add_argument("--output-root", default=config.gen_output_root, help="生成文本输出目录。")
    parser.add_argument("--seed-path", default=config.origin_vul_data, help="漏洞种子 JSON 路径。")
    parser.add_argument("--resume", action="store_true", help="如果输出文件已存在则跳过，便于断点续跑。")
    return parser.parse_args()


def ensure_dir(path: str):
    os.makedirs(path, exist_ok=True)


def get_output_path(output_root: str, index: int, file_name: str) -> str:
    ensure_dir(output_root)
    output_dir = os.path.join(output_root, str(index))
    ensure_dir(output_dir)
    return os.path.join(output_dir, file_name)


def load_seed_data(seed_path: str) -> List[Dict]:
    with open(seed_path, "r", encoding="utf-8") as f:
        return json.load(f)


def request_llm(messages: List[Dict[str, str]], temperature: float, top_p: float, max_output_tokens: int) -> str:
    if not config.LLM_API_KEY:
        raise RuntimeError("缺少 API Key。请设置 GEMINI_API_KEY、OPENAI_API_KEY 或 LLM_API_KEY。")

    if config.LLM_PROVIDER == "gemini":
        return request_gemini(messages, temperature, top_p, max_output_tokens)

    if config.LLM_PROVIDER == "openai_compatible":
        return request_openai_compatible(messages, temperature, top_p, max_output_tokens)

    raise ValueError(f"不支持的 LLM_PROVIDER: {config.LLM_PROVIDER}")


def request_gemini(messages: List[Dict[str, str]], temperature: float, top_p: float, max_output_tokens: int) -> str:
    base_url = config.LLM_BASE_URL.rstrip("/")
    model = config.MODEL
    encoded_key = urllib.parse.quote(config.LLM_API_KEY, safe="")
    url = f"{base_url}/models/{model}:generateContent?key={encoded_key}"

    contents = []
    for message in messages:
        role = "model" if message["role"] == "assistant" else "user"
        contents.append({"role": role, "parts": [{"text": message["content"]}]})

    payload = {
        "systemInstruction": {"parts": [{"text": config.SYSTEM_PROMPT}]},
        "contents": contents,
        "generationConfig": {
            "temperature": temperature,
            "topP": top_p,
            "maxOutputTokens": max_output_tokens,
        },
    }
    data = json.dumps(payload).encode("utf-8")
    request = urllib.request.Request(
        url,
        data=data,
        headers={"Content-Type": "application/json"},
        method="POST",
    )

    try:
        with urllib.request.urlopen(request, timeout=180) as response:
            resp_json = json.loads(response.read().decode("utf-8"))
    except urllib.error.HTTPError as exc:
        detail = exc.read().decode("utf-8", errors="ignore")
        raise RuntimeError(f"Gemini 请求失败: {exc.code} {detail}") from exc

    candidates = resp_json.get("candidates") or []
    if not candidates:
        raise RuntimeError(f"Gemini 未返回候选结果: {resp_json}")

    parts = candidates[0].get("content", {}).get("parts", [])
    text = "".join(part.get("text", "") for part in parts).strip()
    if not text:
        raise RuntimeError(f"Gemini 返回内容为空: {resp_json}")
    return text


def request_openai_compatible(messages: List[Dict[str, str]], temperature: float, top_p: float, max_output_tokens: int) -> str:
    base_url = config.LLM_BASE_URL.rstrip("/")
    url = f"{base_url}/chat/completions"
    payload = {
        "model": config.MODEL,
        "messages": [{"role": "system", "content": config.SYSTEM_PROMPT}, *messages],
        "temperature": temperature,
        "top_p": top_p,
        "max_tokens": max_output_tokens,
    }
    data = json.dumps(payload).encode("utf-8")
    request = urllib.request.Request(
        url,
        data=data,
        headers={
            "Content-Type": "application/json",
            "Authorization": f"Bearer {config.LLM_API_KEY}",
        },
        method="POST",
    )

    try:
        with urllib.request.urlopen(request, timeout=180) as response:
            resp_json = json.loads(response.read().decode("utf-8"))
    except urllib.error.HTTPError as exc:
        detail = exc.read().decode("utf-8", errors="ignore")
        raise RuntimeError(f"OpenAI-compatible 请求失败: {exc.code} {detail}") from exc

    choices = resp_json.get("choices") or []
    if not choices:
        raise RuntimeError(f"接口未返回 choices: {resp_json}")

    message = choices[0].get("message", {})
    text = (message.get("content") or "").strip()
    if not text:
        raise RuntimeError(f"接口返回内容为空: {resp_json}")
    return text


def write_run_manifest(args, total_seeds: int):
    ensure_dir(args.output_root)
    manifest_path = os.path.join(args.output_root, "_run_meta.json")
    manifest = {
        "llm_provider": config.LLM_PROVIDER,
        "model": config.MODEL,
        "prompt_mode": args.prompt_mode,
        "prompt_mode_desc": PROMPT_MODE_DESCRIPTIONS[args.prompt_mode],
        "seed_path": args.seed_path,
        "seed_count": total_seeds,
        "limit": args.limit,
        "start_index": args.start_index,
        "num_variants": args.num_variants,
        "temperature": args.temperature,
        "top_p": args.top_p,
        "max_output_tokens": args.max_output_tokens,
        "output_root": args.output_root,
    }
    with open(manifest_path, "w", encoding="utf-8") as f:
        json.dump(manifest, f, ensure_ascii=False, indent=2)


def write_transcript(output_path: str, item: Dict, sample_index: int, prompt_mode: str, turns: List[Dict[str, str]]):
    with open(output_path, "w", encoding="utf-8") as f:
        f.write(f"System: {config.SYSTEM_PROMPT}\n")
        f.write(f"PromptMode: {prompt_mode}\n")
        f.write(f"SeedIndex: {sample_index}\n")
        f.write(f"SeedId: {item.get('id', 'unknown')}\n")
        f.write(f"SeedFile: {item.get('file_name', f'vul_variant_{sample_index}.txt')}\n")
        f.write(f"Model: {config.MODEL}\n\n")

        user_turn = 0
        assistant_turn = 0
        for message in turns:
            if message["role"] == "user":
                user_turn += 1
                f.write(f"=== User Turn {user_turn} ===\n")
                f.write(message["content"].strip() + "\n\n")
            elif message["role"] == "assistant":
                assistant_turn += 1
                f.write(f"=== Assistant Turn {assistant_turn} ===\n")
                f.write(message["content"].strip() + "\n\n")


def run_generation(args):
    print(f"正在加载漏洞种子数据: {args.seed_path}")
    data = load_seed_data(args.seed_path)
    print(f"共加载 {len(data)} 条漏洞种子。")

    write_run_manifest(args, len(data))

    start = max(args.start_index, 0)
    end = len(data) if args.limit <= 0 else min(len(data), start + args.limit)
    selected = data[start:end]
    print(f"当前生成模式: {args.prompt_mode} -> {PROMPT_MODE_DESCRIPTIONS[args.prompt_mode]}")
    print(f"计划处理区间: [{start}, {end})，共 {len(selected)} 条。")

    for local_index, item in enumerate(tqdm(selected, desc="生成漏洞变体")):
        sample_index = start + local_index
        code_text = item.get("func", item.get("code", ""))
        if not code_text or not code_text.strip():
            continue

        file_name = item.get("file_name", f"vul_variant_{sample_index}.txt")
        output_path = get_output_path(args.output_root, sample_index, file_name)
        if args.resume and os.path.exists(output_path):
            continue

        messages: List[Dict[str, str]] = []
        turns = build_turns(args.prompt_mode, code_text, args.num_variants)

        try:
            for turn in turns:
                messages.append({"role": "user", "content": turn})
                reply = request_llm(
                    messages=messages,
                    temperature=args.temperature,
                    top_p=args.top_p,
                    max_output_tokens=args.max_output_tokens,
                )
                messages.append({"role": "assistant", "content": reply})
                if args.request_interval > 0:
                    time.sleep(args.request_interval)

            write_transcript(output_path, item, sample_index, args.prompt_mode, messages)
        except Exception as exc:
            print(f"\n处理第 {sample_index} 条样本失败: {exc}")


if __name__ == "__main__":
    run_generation(parse_args())
