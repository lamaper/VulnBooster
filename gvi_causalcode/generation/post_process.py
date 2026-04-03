import json
import os
import re
import shutil
import subprocess
import sys
import tempfile

import config
from tqdm import tqdm

# ================= 1. 读取配置路径 =================
gen_output_root = config.gen_output_root
gen_output_result_root = config.gen_output_result_root
rm_comments_output = config.rm_comments_output
static_check_report = config.static_check_report


def _resolve_syntax_checker():
    if not config.SYNTAX_CHECK_ENABLED:
        return None

    if config.SYNTAX_CHECKER != "auto":
        return shutil.which(config.SYNTAX_CHECKER)

    for candidate in ("clang", "gcc"):
        checker = shutil.which(candidate)
        if checker:
            return checker
    return None


def _run_syntax_check(code):
    checker = _resolve_syntax_checker()
    if not checker:
        return {
            "status": "skipped",
            "tool": None,
            "passed": True,
            "reason": "syntax checker unavailable",
        }

    wrapped_code = (
        "#include <stddef.h>\n"
        "#include <stdint.h>\n"
        "#include <stdbool.h>\n"
        "#include <stdio.h>\n"
        "#include <stdlib.h>\n"
        "#include <string.h>\n\n"
        f"{code.strip()}\n"
    )

    with tempfile.NamedTemporaryFile("w", suffix=".c", delete=False, encoding="utf-8") as tmp:
        tmp.write(wrapped_code)
        tmp_path = tmp.name

    try:
        proc = subprocess.run(
            [checker, "-fsyntax-only", "-std=c11", "-w", "-x", "c", tmp_path],
            capture_output=True,
            text=True,
            timeout=config.SYNTAX_TIMEOUT_SEC,
            check=False,
        )
        stderr = (proc.stderr or "").strip()
        if proc.returncode != 0 and stderr and not _looks_like_parse_failure(stderr):
            return {
                "status": "passed_with_context_errors",
                "tool": os.path.basename(checker),
                "passed": True,
                "returncode": proc.returncode,
                "message": stderr[:1000],
            }
        return {
            "status": "passed" if proc.returncode == 0 else "failed",
            "tool": os.path.basename(checker),
            "passed": proc.returncode == 0,
            "returncode": proc.returncode,
            "message": stderr[:1000],
        }
    except subprocess.TimeoutExpired:
        return {
            "status": "failed",
            "tool": os.path.basename(checker),
            "passed": False,
            "returncode": None,
            "message": "syntax check timeout",
        }
    finally:
        try:
            os.remove(tmp_path)
        except OSError:
            pass


def _looks_like_parse_failure(stderr: str) -> bool:
    hard_parse_markers = (
        "stray",
        "missing terminating",
        "parse error",
        "invalid preprocessing directive",
        "unterminated",
    )
    semantic_markers = (
        "unknown type name",
        "invalid use of undefined type",
        "has no member named",
        "incomplete type",
        "undeclared",
        "implicit declaration",
        "conflicting types",
    )
    lowered = stderr.lower()
    if any(marker in lowered for marker in semantic_markers):
        return False
    return any(marker in lowered for marker in hard_parse_markers)


def _run_semgrep_check(code):
    if not config.SEMGREP_ENABLED:
        return {
            "status": "skipped",
            "tool": None,
            "passed": True,
            "reason": "semgrep disabled",
        }

    semgrep_bin = shutil.which(config.SEMGREP_BIN)
    if not semgrep_bin:
        candidate = os.path.join(os.path.dirname(sys.executable), config.SEMGREP_BIN)
        if os.path.exists(candidate):
            semgrep_bin = candidate
    if not semgrep_bin:
        return {
            "status": "skipped",
            "tool": config.SEMGREP_BIN,
            "passed": True,
            "reason": "semgrep unavailable",
        }

    if not os.path.exists(config.SEMGREP_RULES):
        return {
            "status": "skipped",
            "tool": os.path.basename(semgrep_bin),
            "passed": True,
            "reason": f"rules not found: {config.SEMGREP_RULES}",
        }

    with tempfile.NamedTemporaryFile("w", suffix=".c", delete=False, encoding="utf-8") as tmp:
        tmp.write(code.strip() + "\n")
        tmp_path = tmp.name

    try:
        proc = subprocess.run(
            [
                semgrep_bin,
                "--config",
                config.SEMGREP_RULES,
                "--json",
                "--quiet",
                tmp_path,
            ],
            capture_output=True,
            text=True,
            timeout=config.SEMGREP_TIMEOUT_SEC,
            check=False,
        )
        if proc.returncode not in (0, 1):
            return {
                "status": "failed",
                "tool": os.path.basename(semgrep_bin),
                "passed": False,
                "returncode": proc.returncode,
                "message": (proc.stderr or proc.stdout or "").strip()[:1000],
            }

        payload = json.loads(proc.stdout or "{}")
        results = payload.get("results", [])
        has_findings = len(results) > 0
        passed = has_findings if config.SEMGREP_REQUIRE_MATCH else True
        return {
            "status": "passed" if passed else "failed",
            "tool": os.path.basename(semgrep_bin),
            "passed": passed,
            "returncode": proc.returncode,
            "finding_count": len(results),
            "rule_ids": [item.get("check_id", "unknown_rule") for item in results[:20]],
            "message": "" if passed else "no semgrep findings matched required rules",
        }
    except subprocess.TimeoutExpired:
        return {
            "status": "failed",
            "tool": os.path.basename(semgrep_bin),
            "passed": False,
            "returncode": None,
            "message": "semgrep timeout",
        }
    except json.JSONDecodeError:
        return {
            "status": "failed",
            "tool": os.path.basename(semgrep_bin),
            "passed": False,
            "returncode": None,
            "message": "invalid semgrep json output",
        }
    finally:
        try:
            os.remove(tmp_path)
        except OSError:
            pass


# ================= 2. 清洗函数 =================
def remove_comments(code):
    """去除 C 代码中的单行和多行注释，同时保留字符串里的内容"""
    pattern = r"(\".*?\"|\'.*?\')|(/\*.*?\*/|//[^\r\n]*$)"
    regex = re.compile(pattern, re.MULTILINE | re.DOTALL)

    def _replacer(match):
        if match.group(2) is not None:
            return ""
        return match.group(1)

    return regex.sub(_replacer, code)


def remove_selected_structs(code):
    """去除头文件和某些结构体定义，防止大模型自由发挥的外部依赖导致编译失败"""
    code = re.sub(r"#include[^\n]*", "", code)
    code = re.sub(r"#define[^\n]*", "", code)
    code = re.sub(r"typedef\s+struct\s+\w*\s*\{[^}]*\}\s*\w+;", "", code, flags=re.DOTALL)
    code = re.sub(r"typedef\s+struct\s*\{[^}]*\}\s*\w+;", "", code, flags=re.DOTALL)
    code = re.sub(r"typedef\s+struct\s+\w*\s*\{[^}]*\}\s*\w+,\s*\*?\w+;", "", code, flags=re.DOTALL)
    code = re.sub(r"typedef\s+enum\s*\{([^\}]*)\}\s*(\w+);", "", code, flags=re.DOTALL)
    return code


def collect_comment_stats(raw_code, cleaned_code):
    comment_pattern = re.compile(r"/\*.*?\*/|//[^\r\n]*$", re.MULTILINE | re.DOTALL)
    comment_matches = comment_pattern.findall(raw_code)
    removed_comment_chars = sum(len(item) for item in comment_matches)
    raw_len = len(raw_code)
    cleaned_len = len(cleaned_code)
    return {
        "comment_block_count": len(comment_matches),
        "removed_comment_chars": removed_comment_chars,
        "raw_char_len": raw_len,
        "cleaned_char_len": cleaned_len,
        "removed_comment_ratio": 0.0 if raw_len == 0 else removed_comment_chars / raw_len,
    }


def extract_code_blocks(context):
    """优先从 Assistant 回答里提取代码块，兼容旧版 Step 4 输出。"""
    assistant_sections = re.findall(
        r"=== Assistant Turn \d+ ===\n(.*?)(?=\n=== (?:User|Assistant) Turn \d+ ===|\Z)",
        context,
        re.DOTALL,
    )

    if assistant_sections:
        target_text = "\n".join(assistant_sections)
    else:
        parts = context.split("Step 4:")
        target_text = parts[-1] if len(parts) >= 2 else context

    pattern = r"```(?:c|cpp)?\s*\n(.*?)\n```"
    matches = re.findall(pattern, target_text, re.DOTALL | re.IGNORECASE)

    unique_matches = []
    seen = set()
    for match in matches:
        normalized = match.strip()
        if not normalized or normalized in seen:
            continue
        seen.add(normalized)
        unique_matches.append(normalized)
    return unique_matches


# ================= 3. 主处理流程 =================
def process_generated_files():
    if not os.path.exists(gen_output_result_root):
        os.makedirs(gen_output_result_root, exist_ok=True)

    print(f"🔍 正在扫描生成目录: {gen_output_root}")

    extracted_data = []
    check_report = {
        "summary": {
            "accepted": 0,
            "rejected": 0,
            "no_code_block_files": 0,
            "samples_with_comments_removed": 0,
            "total_removed_comment_chars": 0,
        },
        "items": [],
    }
    global_id = 0
    error_count = 0

    if not os.path.exists(gen_output_root):
        print("❌ 找不到生成目录，请先运行 chain_gen.py！")
        return

    subdirs = sorted(d for d in os.listdir(gen_output_root) if os.path.isdir(os.path.join(gen_output_root, d)))

    for subdir in tqdm(subdirs, desc="处理生成结果"):
        dir_path = os.path.join(gen_output_root, subdir)

        for file in sorted(os.listdir(dir_path)):
            if not file.endswith(".txt"):
                continue

            file_path = os.path.join(dir_path, file)
            with open(file_path, "r", encoding="utf-8", errors="ignore") as f:
                context = f.read()

            matches = extract_code_blocks(context)

            if not matches:
                error_count += 1
                continue

            for num, match in enumerate(matches):
                cleaned_code = remove_selected_structs(remove_comments(match))
                if not cleaned_code.strip():
                    continue
                comment_stats = collect_comment_stats(match, cleaned_code)
                if comment_stats["comment_block_count"] > 0:
                    check_report["summary"]["samples_with_comments_removed"] += 1
                    check_report["summary"]["total_removed_comment_chars"] += comment_stats["removed_comment_chars"]

                syntax_result = _run_syntax_check(cleaned_code)
                semgrep_result = _run_semgrep_check(cleaned_code)
                passed = syntax_result["passed"] and semgrep_result["passed"]
                generated_name = f"{subdir}_{num}_1.c"
                check_report["items"].append(
                    {
                        "source_txt": file_path,
                        "generated_variant": generated_name,
                        "accepted": passed,
                        "comment_stats": comment_stats,
                        "syntax_check": syntax_result,
                        "semgrep_check": semgrep_result,
                    }
                )

                if not passed:
                    check_report["summary"]["rejected"] += 1
                    continue

                ex = {
                    "id": global_id,
                    "file_name": generated_name,
                    "file_path": file_path,
                    "func": cleaned_code,
                    "target": 1,
                }
                global_id += 1
                extracted_data.append(ex)
                check_report["summary"]["accepted"] += 1

    print(f"\n✅ 提取完成！共提取出 {len(extracted_data)} 条有效漏洞变体。")
    print(f"⚠️ 未找到代码块的失败文件数: {error_count}")
    check_report["summary"]["no_code_block_files"] = error_count

    with open(rm_comments_output, "w", encoding="utf-8") as f:
        json.dump(extracted_data, f, indent=4)
    print(f"📁 已保存清洗后的纯净漏洞数据至: {rm_comments_output}")

    with open(static_check_report, "w", encoding="utf-8") as f:
        json.dump(check_report, f, indent=2)
    print(f"📁 已保存静态检查报告至: {static_check_report}")


if __name__ == "__main__":
    process_generated_files()
