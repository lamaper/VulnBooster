from __future__ import annotations

from collections import deque
import re
from pathlib import Path

from tqdm import tqdm
from tree_sitter import Language, Parser
import tree_sitter_c
import tree_sitter_cpp

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


def filter_valid_samples(input_path: Path, output_path: Path) -> dict[str, int]:
    rows = list(iter_jsonl(input_path))
    kept_rows: list[dict] = []
    for row in tqdm(rows, desc="AST Validation", unit="sample"):
        cleaned_code = remove_comments_and_blank_lines(row.get("func", ""))
        if is_valid_syntax(cleaned_code):
            new_row = dict(row)
            new_row["func"] = cleaned_code
            kept_rows.append(new_row)

    write_jsonl(output_path, kept_rows)
    return {"total": len(rows), "kept": len(kept_rows)}
