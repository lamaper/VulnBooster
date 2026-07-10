from __future__ import annotations

import tempfile
import unittest
from pathlib import Path
import os

from vulnbooster.augmentation import build_mechanism_guidance, infer_mechanism_family
from vulnbooster.cleaning import clean_c_code
from vulnbooster.code_utils import (
    build_anchor_signature,
    close_unbalanced_blocks,
    compute_anchor_hit_metrics,
    compute_code_length_similarity,
    compute_seed_alignment_metrics,
    compute_variant_novelty_metrics,
    ensure_block_balance,
    stitch_function_header,
)
from vulnbooster.config import load_experiment_config
from vulnbooster.env import apply_java_home, configure_hf_endpoint, load_local_env
from vulnbooster.line_slicer import (
    align_teacher_slice_to_function,
    build_line_slice_alignment_dataset,
    reconstruct_line_slice,
    resolve_model_artifact_dir,
)
from vulnbooster.merge import merge_jsonl
from vulnbooster.sampling import build_balanced_smoke_set
from vulnbooster.code_utils import project_slice_onto_original, sanitize_generated_function
from vulnbooster.validation import filter_valid_samples

try:
    import numpy as np
    from vulnbooster.calibration import compute_binary_metrics, select_best_threshold

    HAS_CALIBRATION_DEPS = True
except ModuleNotFoundError:
    HAS_CALIBRATION_DEPS = False


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

    def test_configure_hf_endpoint_sets_both_env_vars(self) -> None:
        os.environ.pop("HF_ENDPOINT", None)
        os.environ.pop("HUGGINGFACE_HUB_ENDPOINT", None)
        endpoint = configure_hf_endpoint("https://hf-mirror.example")
        self.assertEqual(endpoint, "https://hf-mirror.example")
        self.assertEqual(os.environ["HF_ENDPOINT"], "https://hf-mirror.example")
        self.assertEqual(os.environ["HUGGINGFACE_HUB_ENDPOINT"], "https://hf-mirror.example")

    def test_apply_java_home_updates_java_home_and_path(self) -> None:
        original_path = os.environ.get("PATH", "")
        original_java_home = os.environ.get("JAVA_HOME")
        try:
            java_home = "/tmp/demo-jdk"
            os.environ["PATH"] = "/usr/bin"
            applied = apply_java_home(java_home)
            self.assertEqual(applied, java_home)
            self.assertEqual(os.environ["JAVA_HOME"], java_home)
            self.assertTrue(os.environ["PATH"].startswith(f"{java_home}/bin"))
        finally:
            os.environ["PATH"] = original_path
            if original_java_home is None:
                os.environ.pop("JAVA_HOME", None)
            else:
                os.environ["JAVA_HOME"] = original_java_home


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

    def test_resolve_model_artifact_dir_prefers_best_checkpoint(self) -> None:
        with tempfile.TemporaryDirectory() as tmpdir:
            base = Path(tmpdir)
            checkpoint = base / "checkpoint-10"
            checkpoint.mkdir()
            (checkpoint / "config.json").write_text("{}", encoding="utf-8")
            trainer_state = {
                "best_model_checkpoint": str(checkpoint),
            }
            (checkpoint / "trainer_state.json").write_text(__import__("json").dumps(trainer_state), encoding="utf-8")
            resolved = resolve_model_artifact_dir(base)
            self.assertEqual(resolved, checkpoint)

    def test_sanitize_generated_function_removes_duplicate_leading_header_blocks(self) -> None:
        raw = (
            "int demo(int x)\n"
            "{\n"
            "int demo(int x)\n"
            "{\n"
            "return x;\n"
            "}\n"
            "}\n"
        )
        cleaned = sanitize_generated_function(raw)
        self.assertEqual(cleaned, "int demo(int x)\n{\nreturn x;\n}")

    def test_project_slice_onto_original_reuses_original_lines(self) -> None:
        original = (
            "int demo(int x)\n"
            "{\n"
            "int y = x + 1;\n"
            "if (y > 0) {\n"
            "return y;\n"
            "}\n"
            "return 0;\n"
            "}\n"
        )
        extracted = (
            "int demo(int x)\n"
            "{\n"
            "int demo(int x)\n"
            "{\n"
            "if (y > 0) {\n"
            "return y;\n"
            "}\n"
            "}\n"
        )
        projected = project_slice_onto_original(extracted, original)
        self.assertEqual(projected, "int demo(int x)\n{\nif (y > 0) {\nreturn y;\n}\nreturn 0;\n}")

    def test_compute_seed_alignment_metrics_prefers_shared_calls(self) -> None:
        seed = (
            "GF_Err url_box_read(GF_Box *s, GF_BitStream *bs)\n"
            "{\n"
            "ptr->location = (char*)gf_malloc((u32) ptr->size);\n"
            "gf_bs_read_data(bs, ptr->location, (u32)ptr->size);\n"
            "}\n"
        )
        close_variant = (
            "GF_Err sample_box_read(GF_Box *s, GF_BitStream *bs)\n"
            "{\n"
            "ptr->sample = (char*)gf_malloc(ptr->size);\n"
            "gf_bs_read_data(bs, ptr->sample, ptr->size + 1);\n"
            "}\n"
        )
        far_variant = "int process_data(const int *data, int len) {\nint buffer[4];\nreturn buffer[0];\n}"

        close_metrics = compute_seed_alignment_metrics(seed, close_variant)
        far_metrics = compute_seed_alignment_metrics(seed, far_variant)

        self.assertGreater(close_metrics["alignment_score"], far_metrics["alignment_score"])
        self.assertGreater(close_metrics["call_overlap"], 0.0)

    def test_compute_code_length_similarity_prefers_similar_size(self) -> None:
        reference = "int demo() {\nint a = 0;\nint b = a + 1;\nreturn b;\n}"
        close = "int sample() {\nint x = 0;\nreturn x + 1;\n}"
        far = "int tiny() {\nreturn 0;\n}"

        self.assertGreater(compute_code_length_similarity(reference, close), compute_code_length_similarity(reference, far))

    def test_build_anchor_signature_prefers_shared_calls(self) -> None:
        prompt_code = (
            "GF_Err url_box_read(GF_Box *s, GF_BitStream *bs)\n"
            "{\n"
            "ptr->location = (char*)gf_malloc((u32) ptr->size);\n"
            "gf_bs_read_data(bs, ptr->location, (u32)ptr->size);\n"
            "return GF_OK;\n"
            "}\n"
        )
        seed_code = (
            "GF_Err url_box_read(GF_Box *s, GF_BitStream *bs)\n"
            "{\n"
            "ptr->location = (char*)gf_malloc((u32) ptr->size);\n"
            "gf_bs_read_data(bs, ptr->location, (u32)ptr->size);\n"
            "}\n"
        )
        anchors = build_anchor_signature(prompt_code, seed_code, max_identifier_anchors=4, max_call_anchors=2)

        self.assertIn("gf_bs_read_data", anchors["calls"])
        self.assertIn("ptr", anchors["identifiers"])

    def test_compute_anchor_hit_metrics_detects_anchor_matches(self) -> None:
        candidate = (
            "GF_Err sample_box_read(GF_Box *s, GF_BitStream *bs)\n"
            "{\n"
            "ptr->sample = (char*)gf_malloc(ptr->size);\n"
            "gf_bs_read_data(bs, ptr->sample, ptr->size + 1);\n"
            "return GF_OK;\n"
            "}\n"
        )
        metrics = compute_anchor_hit_metrics(
            candidate,
            anchor_calls=["gf_bs_read_data", "other_call"],
            anchor_identifiers=["ptr", "size", "missing"],
        )

        self.assertEqual(metrics["call_hits"], 1)
        self.assertEqual(metrics["identifier_hits"], 2)
        self.assertTrue(metrics["has_anchor_signal"])

    def test_compute_variant_novelty_metrics_penalizes_rename_only_variants(self) -> None:
        seed = (
            "int changedline(char *src) {\n"
            "char buf[8];\n"
            "strcpy(buf, src);\n"
            "return buf[0];\n"
            "}\n"
        )
        rename_only = (
            "int changedline_copy(char *input) {\n"
            "char tmp[8];\n"
            "strcpy(tmp, input);\n"
            "return tmp[0];\n"
            "}\n"
        )
        structural = (
            "int changedline_copy(char *src) {\n"
            "char buf[8];\n"
            "size_t n = strlen(src);\n"
            "if (n > 0) {\n"
            "strcpy(buf, src);\n"
            "}\n"
            "return buf[0];\n"
            "}\n"
        )

        rename_metrics = compute_variant_novelty_metrics(seed, rename_only)
        structural_metrics = compute_variant_novelty_metrics(seed, structural)

        self.assertEqual(rename_metrics["structural_novel_line_count"], 0)
        self.assertGreater(rename_metrics["abstract_token_similarity"], 0.95)
        self.assertGreater(structural_metrics["structural_novel_line_count"], 0)
        self.assertLess(structural_metrics["abstract_token_similarity"], rename_metrics["abstract_token_similarity"])

    def test_close_unbalanced_blocks_appends_missing_braces(self) -> None:
        raw = (
            "int demo(int x) {\n"
            "if (x > 0) {\n"
            "return x;\n"
            "}\n"
        )
        balanced = close_unbalanced_blocks(raw)
        self.assertEqual(balanced, "int demo(int x) {\nif (x > 0) {\nreturn x;\n}\n}")

    def test_infer_mechanism_family_detects_memory_bounds(self) -> None:
        family = infer_mechanism_family(
            "CWE-119: Buffer Overflow",
            "int demo(char *src) {\nchar buf[8];\nstrcpy(buf, src);\nreturn buf[0];\n}",
        )
        self.assertEqual(family, "memory_bounds")

    def test_infer_mechanism_family_detects_resource_lifecycle(self) -> None:
        family = infer_mechanism_family(
            "CWE-416: Use After Free",
            "void demo(Node *n) {\nfree(n);\nreturn n->value;\n}",
        )
        self.assertEqual(family, "resource_lifecycle")

    def test_build_mechanism_guidance_assigns_candidate_specific_plan(self) -> None:
        family, guidance = build_mechanism_guidance(
            "CWE-476: NULL Pointer Dereference",
            "int demo(struct Obj *obj) {\nif (obj)\nreturn obj->field;\nreturn 0;\n}",
            kb_info={"def": "The product dereferences a pointer that might be null."},
            generate_k=3,
        )
        self.assertEqual(family, "null_deref")
        self.assertIn("[Mechanism Profile]", guidance)
        self.assertIn("Candidate 1", guidance)
        self.assertIn("Candidate 3", guidance)
        self.assertIn("Null Pointer Dereference", guidance)


class ValidationTests(unittest.TestCase):
    def test_filter_valid_samples_deduplicates_and_skips_seed_copies(self) -> None:
        with tempfile.TemporaryDirectory() as tmpdir:
            base = Path(tmpdir)
            input_path = base / "generated.jsonl"
            output_path = base / "validated.jsonl"
            seed = "int demo(int x) {\nreturn x;\n}"
            generated = [
                {
                    "idx": "a",
                    "func": "int demo(int x) {\nreturn x + 1;\n}",
                    "seed_func": seed,
                },
                {
                    "idx": "b",
                    "func": "int demo(int x) {\nreturn x + 1;\n}",
                    "seed_func": seed,
                },
                {
                    "idx": "c",
                    "func": "int demo(int x) {\nreturn x;\n}",
                    "seed_func": seed,
                },
            ]
            input_path.write_text("\n".join(__import__("json").dumps(row) for row in generated) + "\n", encoding="utf-8")

            stats = filter_valid_samples(input_path, output_path)
            kept = output_path.read_text(encoding="utf-8").strip().splitlines()

            self.assertEqual(stats["kept"], 1)
            self.assertEqual(stats["duplicate_generated"], 1)
            self.assertEqual(stats["same_as_seed"], 1)
            self.assertEqual(len(kept), 1)

    def test_filter_valid_samples_respects_seed_alignment_threshold(self) -> None:
        with tempfile.TemporaryDirectory() as tmpdir:
            base = Path(tmpdir)
            input_path = base / "generated.jsonl"
            output_path = base / "validated.jsonl"
            seed = (
                "GF_Err url_box_read(GF_Box *s, GF_BitStream *bs)\n"
                "{\n"
                "ptr->location = (char*)gf_malloc((u32) ptr->size);\n"
                "gf_bs_read_data(bs, ptr->location, (u32)ptr->size);\n"
                "return GF_OK;\n"
                "}\n"
            )
            generated = [
                {
                    "idx": "close",
                    "func": (
                        "GF_Err sample_box_read(GF_Box *s, GF_BitStream *bs)\n"
                        "{\n"
                        "ptr->sample = (char*)gf_malloc(ptr->size);\n"
                        "gf_bs_read_data(bs, ptr->sample, ptr->size + 1);\n"
                        "return GF_OK;\n"
                        "}\n"
                    ),
                    "seed_func": seed,
                },
                {
                    "idx": "far",
                    "func": "int process_data(const int *data, int len) {\nint buffer[4];\nreturn buffer[0];\n}",
                    "seed_func": seed,
                },
            ]
            input_path.write_text("\n".join(__import__("json").dumps(row) for row in generated) + "\n", encoding="utf-8")

            stats = filter_valid_samples(input_path, output_path, min_seed_alignment=0.2)
            kept = output_path.read_text(encoding="utf-8").strip().splitlines()

            self.assertEqual(stats["kept"], 1)
            self.assertEqual(stats["low_seed_alignment"], 1)
            self.assertEqual(len(kept), 1)

    def test_filter_valid_samples_reranks_per_seed(self) -> None:
        with tempfile.TemporaryDirectory() as tmpdir:
            base = Path(tmpdir)
            input_path = base / "generated.jsonl"
            output_path = base / "validated.jsonl"
            seed_func = (
                "int changedline(char *src) {\n"
                "char buf[8];\n"
                "strcpy(buf, src);\n"
                "return buf[0];\n"
                "}\n"
            )
            line_slice = (
                "int changedline(char *src) {\n"
                "strcpy(buf, src);\n"
                "}\n"
            )
            generated = [
                {
                    "idx": "best",
                    "original_idx": "seed-1",
                    "func": (
                        "int changedline_copy(char *src) {\n"
                        "char buf[8];\n"
                        "strcpy(buf, src);\n"
                        "return buf[0];\n"
                        "}\n"
                    ),
                    "seed_func": seed_func,
                    "augmentation_seed_code": line_slice,
                },
                {
                    "idx": "runner_up",
                    "original_idx": "seed-1",
                    "func": (
                        "int changedline_alt(char *src) {\n"
                        "char buf[8];\n"
                        "strcpy(buf, src);\n"
                        "buf[7] = '\\0';\n"
                        "return buf[0];\n"
                        "}\n"
                    ),
                    "seed_func": seed_func,
                    "augmentation_seed_code": line_slice,
                },
                {
                    "idx": "far",
                    "original_idx": "seed-1",
                    "func": "int process_data(const int *data, int len) {\nint buffer[4];\nreturn buffer[0];\n}",
                    "seed_func": seed_func,
                    "augmentation_seed_code": line_slice,
                },
            ]
            input_path.write_text("\n".join(__import__("json").dumps(row) for row in generated) + "\n", encoding="utf-8")

            stats = filter_valid_samples(
                input_path,
                output_path,
                min_prompt_alignment=0.1,
                min_quality_score=0.3,
                max_per_seed=1,
            )
            kept_rows = [__import__("json").loads(line) for line in output_path.read_text(encoding="utf-8").splitlines() if line.strip()]

            self.assertEqual(stats["kept"], 1)
            self.assertEqual(stats["low_prompt_alignment"], 1)
            self.assertEqual(stats["over_seed_budget"], 1)
            self.assertEqual(kept_rows[0]["idx"], "best")
            self.assertEqual(kept_rows[0]["quality_rank_within_seed"], 1)

    def test_filter_valid_samples_requires_anchor_hits(self) -> None:
        with tempfile.TemporaryDirectory() as tmpdir:
            base = Path(tmpdir)
            input_path = base / "generated.jsonl"
            output_path = base / "validated.jsonl"
            seed = (
                "GF_Err url_box_read(GF_Box *s, GF_BitStream *bs)\n"
                "{\n"
                "ptr->location = (char*)gf_malloc((u32) ptr->size);\n"
                "gf_bs_read_data(bs, ptr->location, (u32)ptr->size);\n"
                "return GF_OK;\n"
                "}\n"
            )
            generated = [
                {
                    "idx": "close",
                    "func": (
                        "GF_Err sample_box_read(GF_Box *s, GF_BitStream *bs)\n"
                        "{\n"
                        "ptr->sample = (char*)gf_malloc(ptr->size);\n"
                        "gf_bs_read_data(bs, ptr->sample, ptr->size + 1);\n"
                        "return GF_OK;\n"
                        "}\n"
                    ),
                    "seed_func": seed,
                    "augmentation_seed_code": seed,
                    "augmentation_anchor_calls": ["gf_bs_read_data"],
                    "augmentation_anchor_identifiers": ["ptr", "size"],
                },
                {
                    "idx": "far",
                    "func": "int process_data(const int *data, int len) {\nint buffer[4];\nreturn buffer[0];\n}",
                    "seed_func": seed,
                    "augmentation_seed_code": seed,
                    "augmentation_anchor_calls": ["gf_bs_read_data"],
                    "augmentation_anchor_identifiers": ["ptr", "size"],
                },
            ]
            input_path.write_text("\n".join(__import__("json").dumps(row) for row in generated) + "\n", encoding="utf-8")

            stats = filter_valid_samples(
                input_path,
                output_path,
                min_anchor_identifier_hits=1,
                min_anchor_call_hits=1,
                require_anchor_signal=True,
            )
            kept_rows = [__import__("json").loads(line) for line in output_path.read_text(encoding="utf-8").splitlines() if line.strip()]

            self.assertEqual(stats["kept"], 1)
            self.assertEqual(stats["low_anchor_signal"], 1)
            self.assertEqual(kept_rows[0]["idx"], "close")

    def test_filter_valid_samples_rejects_trivial_variants(self) -> None:
        with tempfile.TemporaryDirectory() as tmpdir:
            base = Path(tmpdir)
            input_path = base / "generated.jsonl"
            output_path = base / "validated.jsonl"
            seed = (
                "int changedline(char *src) {\n"
                "char buf[8];\n"
                "strcpy(buf, src);\n"
                "return buf[0];\n"
                "}\n"
            )
            generated = [
                {
                    "idx": "rename_only",
                    "func": (
                        "int changedline_copy(char *input) {\n"
                        "char tmp[8];\n"
                        "strcpy(tmp, input);\n"
                        "return tmp[0];\n"
                        "}\n"
                    ),
                    "seed_func": seed,
                    "augmentation_seed_code": seed,
                },
                {
                    "idx": "structural",
                    "func": (
                        "int changedline_guard(char *src) {\n"
                        "char buf[8];\n"
                        "size_t n = strlen(src);\n"
                        "if (n > 0) {\n"
                        "strcpy(buf, src);\n"
                        "}\n"
                        "return buf[0];\n"
                        "}\n"
                    ),
                    "seed_func": seed,
                    "augmentation_seed_code": seed,
                },
            ]
            input_path.write_text("\n".join(__import__("json").dumps(row) for row in generated) + "\n", encoding="utf-8")

            stats = filter_valid_samples(
                input_path,
                output_path,
                min_novel_line_count=2,
                min_novel_line_ratio=0.2,
                min_structural_novel_line_count=1,
                max_abstract_token_similarity=0.92,
                reject_trivial_variants=True,
            )
            kept_rows = [__import__("json").loads(line) for line in output_path.read_text(encoding="utf-8").splitlines() if line.strip()]

            self.assertEqual(stats["kept"], 1)
            self.assertEqual(stats["trivial_variant"], 1)
            self.assertEqual(kept_rows[0]["idx"], "structural")


@unittest.skipUnless(HAS_CALIBRATION_DEPS, "calibration dependencies are not installed")
class CalibrationTests(unittest.TestCase):
    def test_select_best_threshold_can_raise_precision(self) -> None:
        labels = np.array([0, 0, 1, 1], dtype=np.int64)
        probs = np.array([0.2, 0.55, 0.58, 0.95], dtype=np.float32)

        best_precision = select_best_threshold(
            labels,
            probs,
            objective="precision",
            threshold_min=0.5,
            threshold_max=0.8,
            num_thresholds=7,
        )
        default_metrics = compute_binary_metrics(labels, probs, 0.5)

        self.assertGreaterEqual(best_precision["precision"], default_metrics["precision"])
        self.assertGreater(best_precision["threshold"], 0.5)


if __name__ == "__main__":
    unittest.main()
