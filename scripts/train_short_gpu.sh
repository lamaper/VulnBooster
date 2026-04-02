#!/usr/bin/env bash
set -euo pipefail

REPO_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
PYTHON_BIN="${VULNBOOSTER_PYTHON:-/home/lamaper/miniconda3/envs/vulnbooster/bin/python}"
GPU_ID="${GPU_ID:-0}"
EPOCHS="${EPOCHS:-1}"
BATCH_SIZE="${BATCH_SIZE:-8}"
TRAIN_TASK="${TRAIN_TASK:-reveal}"
TEST_TASK="${TEST_TASK:-devign}"
DOMAIN_LIST="${DOMAIN_LIST:-origin_s,linevul-CausalCode-token}"
ROOT_DIR="${ROOT_DIR:-$REPO_ROOT/gvi_causalcode/data/}"
LOG_DIR="${LOG_DIR:-$REPO_ROOT/logs}"
RUN_TAG="${RUN_TAG:-short_gpu_${TRAIN_TASK}_to_${TEST_TASK}_$(date +%Y%m%d_%H%M%S)}"

mkdir -p "$LOG_DIR"
LOG_PATH="$LOG_DIR/${RUN_TAG}.log"

echo "仓库根目录=$REPO_ROOT"
echo "Python 解释器=$PYTHON_BIN"
echo "GPU 编号=$GPU_ID"
echo "训练轮数=$EPOCHS"
echo "批大小=$BATCH_SIZE"
echo "数据根目录=$ROOT_DIR"
echo "日志路径=$LOG_PATH"

cd "$REPO_ROOT/gvi_causalcode/train_bert"

WANDB_MODE=offline \
TRANSFORMERS_OFFLINE=1 \
HF_HUB_OFFLINE=1 \
"$PYTHON_BIN" run.py \
  --do_train \
  --train_task "$TRAIN_TASK" \
  --test_task "$TEST_TASK" \
  --model_name linevul \
  --enhance_method CausalCode \
  --attack_type token \
  --domain_list "$DOMAIN_LIST" \
  --epochs "$EPOCHS" \
  --batch_size "$BATCH_SIZE" \
  --gpu "$GPU_ID" \
  --root_dir "$ROOT_DIR" | tee "$LOG_PATH"
