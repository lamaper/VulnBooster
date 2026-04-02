#!/usr/bin/env bash
set -euo pipefail

REPO_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
PYTHON_BIN="${VULNBOOSTER_PYTHON:-/home/lamaper/miniconda3/envs/vulnbooster/bin/python}"
ROOT_DIR="${ROOT_DIR:-$REPO_ROOT/gvi_causalcode/data/}"
TASK_NAME="${TASK_NAME:?please set TASK_NAME}"
GPU_ID="${GPU_ID:-0}"
ATTACK_TYPE="${ATTACK_TYPE:-token}"
TRAINED_MODEL_PATH="${TRAINED_MODEL_PATH:-}"

cd "$REPO_ROOT/gvi_causalcode/train_bert"

CMD=(
  "$PYTHON_BIN" attacker4simple.py
  --task "$TASK_NAME"
  --enhance_method CausalCode
  --attack_type "$ATTACK_TYPE"
  --gpu "$GPU_ID"
  --root_dir "$ROOT_DIR"
)

if [ -n "$TRAINED_MODEL_PATH" ]; then
  CMD+=(--trained_model_path "$TRAINED_MODEL_PATH")
fi

"${CMD[@]}"
