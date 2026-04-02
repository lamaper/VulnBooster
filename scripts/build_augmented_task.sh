#!/usr/bin/env bash
set -euo pipefail

REPO_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
PYTHON_BIN="${VULNBOOSTER_PYTHON:-/home/lamaper/miniconda3/envs/vulnbooster/bin/python}"
SOURCE_ROOT="${SOURCE_ROOT:-$REPO_ROOT/gvi_causalcode/data}"
OUTPUT_ROOT="${OUTPUT_ROOT:-$REPO_ROOT/gvi_causalcode/data}"
SOURCE_TASK="${SOURCE_TASK:-reveal}"
NEW_TASK="${NEW_TASK:?please set NEW_TASK}"
AUG_JSON="${AUG_JSON:-$REPO_ROOT/gvi_causalcode/data/reveal/pattern_generate_repair_deepseek-chat_result/final_augmented_vul.json}"
LIMIT_GENERATED="${LIMIT_GENERATED:-0}"
MAX_ORIGIN_TRAIN="${MAX_ORIGIN_TRAIN:-0}"
MAX_ORIGIN_TEST="${MAX_ORIGIN_TEST:-0}"

cd "$REPO_ROOT/gvi_causalcode/generation"

"$PYTHON_BIN" build_augmented_task.py \
  --source-root "$SOURCE_ROOT" \
  --output-root "$OUTPUT_ROOT" \
  --source-task "$SOURCE_TASK" \
  --new-task "$NEW_TASK" \
  --aug-json "$AUG_JSON" \
  --limit-generated "$LIMIT_GENERATED" \
  --max-origin-train "$MAX_ORIGIN_TRAIN" \
  --max-origin-test "$MAX_ORIGIN_TEST"
