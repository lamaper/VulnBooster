from __future__ import annotations

import tempfile
import unittest
from pathlib import Path
import os

from vulnbooster.cleaning import clean_c_code
from vulnbooster.code_utils import ensure_block_balance, stitch_function_header
from vulnbooster.config import load_experiment_config
from vulnbooster.env import load_local_env
from vulnbooster.line_slicer import (
    align_teacher_slice_to_function,
    build_line_slice_alignment_dataset,
    reconstruct_line_slice,
)
from vulnbooster.merge import merge_jsonl
from vulnbooster.sampling import build_balanced_smoke_set


class ConfigTests(unittest.TestCase):
    def test_load_smoke_config(self) -> None:
        cfg = load_experiment_config("configs/smoke.toml")
        self.assertEqual(cfg.project.dataset_variant, "smoke")
        self.assertTrue(cfg.root_dir.exists())
        self.assertEqual(cfg.dataset_split_path("train", cleaned=False).name, "primevul_train.jsonl")


class CleaningTests(unittest.TestCase):
    def test_clean_c_code_removes_comments_and_blank_lines(self) -> None:
        source = """
        // line comment
        int main() {
            char *s = "http://example";
            /* block
               comment */
            return 0;
        }
        """
        cleaned = clean_c_code(source)
        self.assertIn('char *s = "http://example";', cleaned)
        self.assertNotIn("// line comment", cleaned)
        self.assertNotIn("block", cleaned)


class MergeTests(unittest.TestCase):
    def test_merge_jsonl_deduplicates_idx(self) -> None:
        with tempfile.TemporaryDirectory() as tmpdir:
            base = Path(tmpdir)
            input_a = base / "a.jsonl"
            input_b = base / "b.jsonl"
            output = base / "out.jsonl"

            input_a.write_text('{"idx": 1, "func": "a"}\n{"idx": 2, "func": "b"}\n', encoding="utf-8")
            input_b.write_text('{"idx": 2, "func": "dup"}\n{"idx": 3, "func": "c"}\n', encoding="utf-8")

            stats = merge_jsonl([input_a, input_b], output)
            self.assertEqual(stats["written"], 3)
            self.assertEqual(stats["duplicates"], 1)


class SamplingTests(unittest.TestCase):
    def test_build_balanced_smoke_set(self) -> None:
        with tempfile.TemporaryDirectory() as tmpdir:
            base = Path(tmpdir)
            input_path = base / "full.jsonl"
            output_path = base / "smoke.jsonl"

            rows = [
                '{"idx": 1, "target": 0}',
                '{"idx": 2, "target": 0}',
                '{"idx": 3, "target": 1}',
                '{"idx": 4, "target": 1}',
            ]
            input_path.write_text("\n".join(rows) + "\n", encoding="utf-8")

            stats = build_balanced_smoke_set(input_path, output_path, seed=1, num_per_class=1)
            self.assertEqual(stats["written"], 2)
            self.assertTrue(output_path.exists())


class EnvTests(unittest.TestCase):
    def test_load_local_env(self) -> None:
        with tempfile.TemporaryDirectory() as tmpdir:
            env_path = Path(tmpdir) / ".env.local"
            env_path.write_text("DEMO_KEY=demo-value\n", encoding="utf-8")
            if "DEMO_KEY" in os.environ:
                del os.environ["DEMO_KEY"]
            loaded = load_local_env(env_path)
            self.assertEqual(loaded, env_path)
            self.assertEqual(os.environ["DEMO_KEY"], "demo-value")


class LineSlicerTests(unittest.TestCase):
    def test_align_teacher_slice_to_function_marks_expected_lines(self) -> None:
        func = "int f() {\nint a = source();\nif (a > 0) {\nreturn a;\n}\nreturn 0;\n}"
        teacher = "if (a > 0) {\nreturn a;\n}"
        result = align_teacher_slice_to_function(func, teacher)
        self.assertEqual(result.matched_line_numbers, [3, 4, 5])
        self.assertEqual(sum(result.labels), 3)
        self.assertEqual(result.unmatched_teacher_lines, [])

    def test_reconstruct_line_slice_stitches_header(self) -> None:
        func = "int f() {\nint a = source();\nif (a > 0) {\nreturn a;\n}\nreturn 0;\n}"
        reconstructed, lines = reconstruct_line_slice(func, [0.1, 0.2, 0.9, 0.95, 0.8, 0.1, 0.0], 0.5)
        self.assertEqual(lines, [3, 4, 5])
        self.assertTrue(reconstructed.startswith("int f() {"))
        self.assertIn("return a;", reconstructed)

    def test_ensure_block_balance_adds_closing_brace(self) -> None:
        function_lines = [
            "int f() {",
            "int a = source();",
            "if (a > 0) {",
            "return a;",
            "}",
            "return 0;",
            "}",
        ]
        balanced = ensure_block_balance(function_lines, [3, 4])
        self.assertEqual(balanced, [3, 4, 5])

    def test_build_line_slice_alignment_dataset(self) -> None:
        with tempfile.TemporaryDirectory() as tmpdir:
            base = Path(tmpdir)
            input_path = base / "input.jsonl"
            output_path = base / "aligned.jsonl"
            row = {
                "idx": "demo",
                "target": 1,
                "func": "int f() {\nint a = source();\nif (a > 0) {\nreturn a;\n}\nreturn 0;\n}",
                "refined_code": "if (a > 0) {\nreturn a;\n}",
                "raw_lines": [3, 4, 5],
            }
            input_path.write_text(__import__("json").dumps(row) + "\n", encoding="utf-8")
            stats = build_line_slice_alignment_dataset(input_path, output_path)
            self.assertEqual(stats["written"], 1)
            payload = output_path.read_text(encoding="utf-8")
            self.assertIn("\"teacher_source\": \"refined_code\"", payload)
            self.assertIn("\"line_labels\": [0, 0, 1, 1, 1, 0, 0]", payload)


if __name__ == "__main__":
    unittest.main()
