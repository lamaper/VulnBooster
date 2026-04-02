#!/usr/bin/env bash
set -euo pipefail

REPO_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
PYTHON_BIN="${VULNBOOSTER_PYTHON:-/home/lamaper/miniconda3/envs/vulnbooster/bin/python}"

ROOT_DIR="${ROOT_DIR:-$REPO_ROOT/gvi_causalcode/data/}"
TASK_NAME="${TASK_NAME:?please set TASK_NAME}"
TEST_TASK="${TEST_TASK:-devign}"
GPU_ID="${GPU_ID:-0}"
BATCH_SIZE="${BATCH_SIZE:-8}"
EPOCHS="${EPOCHS:-5}"
EARLY_STOP="${EARLY_STOP:-5}"
ATTACK_TYPE="${ATTACK_TYPE:-token}"
MODEL_NAME="${MODEL_NAME:-linevul}"
LOG_DIR="${LOG_DIR:-$REPO_ROOT/logs}"
GUIDE_RUN_TAG="${GUIDE_RUN_TAG:-guide_${TASK_NAME}_${ATTACK_TYPE}_$(date +%Y%m%d_%H%M%S)}"

if [ "$EPOCHS" -lt 3 ]; then
  echo "EPOCHS 必须 >= 3，否则 run.py 不会进入验证与 best.pt 保存阶段。" >&2
  exit 1
fi

mkdir -p "$LOG_DIR"

GUIDE_LOG_PATH="$LOG_DIR/${GUIDE_RUN_TAG}.log"
GUIDE_MODEL_DIR="${ROOT_DIR%/}/${TASK_NAME}/model/${MODEL_NAME}/CausalCode/${ATTACK_TYPE}/origin_s"
GUIDE_MODEL_PATH="$GUIDE_MODEL_DIR/best.pt"

echo "仓库根目录=$REPO_ROOT"
echo "Python 解释器=$PYTHON_BIN"
echo "数据根目录=$ROOT_DIR"
echo "增强任务名=$TASK_NAME"
echo "跨域测试集=$TEST_TASK"
echo "GPU 编号=$GPU_ID"
echo "批大小=$BATCH_SIZE"
echo "训练轮数=$EPOCHS"
echo "早停轮数=$EARLY_STOP"
echo "攻击类型=$ATTACK_TYPE"
echo "Guide 日志=$GUIDE_LOG_PATH"
echo "Guide 模型目录=$GUIDE_MODEL_DIR"

cd "$REPO_ROOT/gvi_causalcode/train_bert"

WANDB_MODE=offline \
TRANSFORMERS_OFFLINE=1 \
HF_HUB_OFFLINE=1 \
"$PYTHON_BIN" run.py \
  --do_train \
  --train_task "$TASK_NAME" \
  --test_task "$TEST_TASK" \
  --model_name "$MODEL_NAME" \
  --enhance_method CausalCode \
  --attack_type "$ATTACK_TYPE" \
  --domain_list origin_s \
  --epochs "$EPOCHS" \
  --early_stop "$EARLY_STOP" \
  --batch_size "$BATCH_SIZE" \
  --gpu "$GPU_ID" \
  --root_dir "$ROOT_DIR" | tee "$GUIDE_LOG_PATH"

if [ ! -f "$GUIDE_MODEL_PATH" ]; then
  echo "未找到引导模型权重: $GUIDE_MODEL_PATH" >&2
  echo "请检查训练日志，确认训练是否至少在 epoch>2 后完成验证并保存 best.pt。" >&2
  exit 1
fi

cd "$REPO_ROOT"

ROOT_DIR="$ROOT_DIR" \
TASK_NAME="$TASK_NAME" \
GPU_ID="$GPU_ID" \
ATTACK_TYPE="$ATTACK_TYPE" \
TRAINED_MODEL_PATH="$GUIDE_MODEL_PATH" \
VULNBOOSTER_PYTHON="$PYTHON_BIN" \
bash "$REPO_ROOT/scripts/generate_causal_domain.sh"

echo
echo "正式引导模型训练 + CausalCode 配对域重建完成。"
echo "引导模型权重: $GUIDE_MODEL_PATH"
echo "配对域目录: ${ROOT_DIR%/}/${TASK_NAME}/dataset/${MODEL_NAME}-CausalCode-${ATTACK_TYPE}"
