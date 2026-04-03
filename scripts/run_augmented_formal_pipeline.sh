#!/usr/bin/env bash
set -euo pipefail

REPO_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
PYTHON_BIN="${VULNBOOSTER_PYTHON:-/root/miniconda3/envs/vulnbooster/bin/python}"

PROMPT_MODE="${PROMPT_MODE:-pattern_generate_repair}"
GEN_LIMIT="${GEN_LIMIT:-200}"
GEN_START_INDEX="${GEN_START_INDEX:-0}"
NUM_VARIANTS="${NUM_VARIANTS:-4}"
GEN_WORKERS="${GEN_WORKERS:-8}"
GEN_RUN_TAG="${GEN_RUN_TAG:-formal_${PROMPT_MODE}_deepseek_v2}"
GEN_OUTPUT_ROOT="${GEN_OUTPUT_ROOT:-$REPO_ROOT/gvi_causalcode/data/reveal/${GEN_RUN_TAG}}"
GEN_OUTPUT_RESULT_ROOT="${GEN_OUTPUT_RESULT_ROOT:-${GEN_OUTPUT_ROOT}_result}"
FILTER_MODE="${FILTER_MODE:-source_only}"
TARGET_ALIGN_TASK="${TARGET_ALIGN_TASK:-}"
TARGET_ALIGN_KEEP_TOP_N="${TARGET_ALIGN_KEEP_TOP_N:-0}"
TARGET_ALIGN_KEEP_RATIO="${TARGET_ALIGN_KEEP_RATIO:-0.35}"
TARGET_ALIGN_MAX_PER_SEED="${TARGET_ALIGN_MAX_PER_SEED:-2}"
TARGET_ALIGN_MIN_COSINE="${TARGET_ALIGN_MIN_COSINE:-0.08}"
TARGET_ALIGN_SOURCE_MIN_DISTANCE="${TARGET_ALIGN_SOURCE_MIN_DISTANCE:-0.10}"
TARGET_ALIGN_SOURCE_MAX_DISTANCE="${TARGET_ALIGN_SOURCE_MAX_DISTANCE:-0.92}"

AUG_TASK_NAME="${AUG_TASK_NAME:-reveal_aug_v2}"
LIMIT_GENERATED="${LIMIT_GENERATED:-0}"
MAX_ORIGIN_TRAIN="${MAX_ORIGIN_TRAIN:-0}"
MAX_ORIGIN_TEST="${MAX_ORIGIN_TEST:-0}"

GPU_ID="${GPU_ID:-0}"
BATCH_SIZE="${BATCH_SIZE:-8}"
GUIDE_EPOCHS="${GUIDE_EPOCHS:-5}"
FINAL_EPOCHS="${FINAL_EPOCHS:-5}"
EARLY_STOP="${EARLY_STOP:-5}"
ATTACK_TYPE="${ATTACK_TYPE:-token}"
TEST_TASK="${TEST_TASK:-devign}"
LOG_DIR="${LOG_DIR:-$REPO_ROOT/logs}"
RUN_TAG="${RUN_TAG:-${AUG_TASK_NAME}_formal_$(date +%Y%m%d_%H%M%S)}"

load_env_from_interactive_bash() {
  local var_name="$1"
  TERM=xterm bash -ic "printf '%s' \"\${${var_name}:-}\"" 2>/dev/null
}

ensure_llm_env() {
  if [ -z "${OPENAI_API_KEY:-}" ]; then
    OPENAI_API_KEY="$(load_env_from_interactive_bash OPENAI_API_KEY || true)"
    export OPENAI_API_KEY
  fi

  if [ -z "${LLM_BASE_URL:-}" ]; then
    LLM_BASE_URL="$(load_env_from_interactive_bash LLM_BASE_URL || true)"
    export LLM_BASE_URL
  fi

  if [ -z "${LLM_MODEL:-}" ]; then
    LLM_MODEL="$(load_env_from_interactive_bash LLM_MODEL || true)"
    export LLM_MODEL
  fi

  if [ -z "${OPENAI_API_KEY:-}" ]; then
    echo "缺少 OPENAI_API_KEY。请先在 ~/.bashrc 中配置后重试。" >&2
    exit 1
  fi

  if [ -z "${LLM_BASE_URL:-}" ]; then
    export LLM_BASE_URL="https://api.deepseek.com/v1"
  fi

  if [ -z "${LLM_MODEL:-}" ]; then
    export LLM_MODEL="deepseek-chat"
  fi
}

print_config() {
  echo "仓库根目录=$REPO_ROOT"
  echo "Python 解释器=$PYTHON_BIN"
  echo "OPENAI_API_KEY_SET=${OPENAI_API_KEY:+yes}"
  echo "LLM_BASE_URL=${LLM_BASE_URL:-unset}"
  echo "LLM_MODEL=${LLM_MODEL:-unset}"
  echo "PROMPT_MODE=$PROMPT_MODE"
  echo "GEN_LIMIT=$GEN_LIMIT"
  echo "GEN_START_INDEX=$GEN_START_INDEX"
  echo "NUM_VARIANTS=$NUM_VARIANTS"
  echo "GEN_WORKERS=$GEN_WORKERS"
  echo "GEN_RUN_TAG=$GEN_RUN_TAG"
  echo "GEN_OUTPUT_ROOT=$GEN_OUTPUT_ROOT"
  echo "GEN_OUTPUT_RESULT_ROOT=$GEN_OUTPUT_RESULT_ROOT"
  echo "FILTER_MODE=$FILTER_MODE"
  echo "TARGET_ALIGN_TASK=$TARGET_ALIGN_TASK"
  echo "AUG_TASK_NAME=$AUG_TASK_NAME"
  echo "LIMIT_GENERATED=$LIMIT_GENERATED"
  echo "GPU_ID=$GPU_ID"
  echo "BATCH_SIZE=$BATCH_SIZE"
  echo "GUIDE_EPOCHS=$GUIDE_EPOCHS"
  echo "FINAL_EPOCHS=$FINAL_EPOCHS"
  echo "EARLY_STOP=$EARLY_STOP"
  echo "ATTACK_TYPE=$ATTACK_TYPE"
  echo "TEST_TASK=$TEST_TASK"
  echo "RUN_TAG=$RUN_TAG"
}

run_generation() {
  cd "$REPO_ROOT/gvi_causalcode/generation"
  GEN_RUN_TAG="$GEN_RUN_TAG" \
  GEN_OUTPUT_ROOT="$GEN_OUTPUT_ROOT" \
  GEN_OUTPUT_RESULT_ROOT="$GEN_OUTPUT_RESULT_ROOT" \
  LLM_BASE_URL="$LLM_BASE_URL" \
  LLM_MODEL="$LLM_MODEL" \
  OPENAI_API_KEY="$OPENAI_API_KEY" \
  "$PYTHON_BIN" chain_gen.py \
    --prompt-mode "$PROMPT_MODE" \
    --limit "$GEN_LIMIT" \
    --start-index "$GEN_START_INDEX" \
    --num-variants "$NUM_VARIANTS" \
    --workers "$GEN_WORKERS" \
    --output-root "$GEN_OUTPUT_ROOT" \
    --resume
}

run_post_process() {
  cd "$REPO_ROOT/gvi_causalcode/generation"
  GEN_OUTPUT_ROOT="$GEN_OUTPUT_ROOT" \
  GEN_OUTPUT_RESULT_ROOT="$GEN_OUTPUT_RESULT_ROOT" \
  "$PYTHON_BIN" post_process.py
}

run_post_analysis() {
  cd "$REPO_ROOT/gvi_causalcode/generation"
  GEN_OUTPUT_ROOT="$GEN_OUTPUT_ROOT" \
  GEN_OUTPUT_RESULT_ROOT="$GEN_OUTPUT_RESULT_ROOT" \
  ORIGIN_VUL_DATA="../data/reveal/reveal_vul_only.json" \
  "$PYTHON_BIN" post_analysis.py
}

run_cross_domain_alignment_filter() {
  cd "$REPO_ROOT/gvi_causalcode/generation"
  if [ -z "$TARGET_ALIGN_TASK" ]; then
    echo "FILTER_MODE=source_target_align 需要设置 TARGET_ALIGN_TASK，例如 devign。" >&2
    exit 1
  fi

  "$PYTHON_BIN" filter_cross_domain_alignment.py \
    --similarity-json "$GEN_OUTPUT_RESULT_ROOT/similarity.json" \
    --target-pkl "$REPO_ROOT/gvi_causalcode/data/$TARGET_ALIGN_TASK/dataset/origin_s/data.pkl.gz" \
    --output-json "$GEN_OUTPUT_RESULT_ROOT/final_augmented_vul.json" \
    --report-json "$GEN_OUTPUT_RESULT_ROOT/target_alignment_report.json" \
    --source-min-distance "$TARGET_ALIGN_SOURCE_MIN_DISTANCE" \
    --source-max-distance "$TARGET_ALIGN_SOURCE_MAX_DISTANCE" \
    --target-min-cosine "$TARGET_ALIGN_MIN_COSINE" \
    --keep-top-n "$TARGET_ALIGN_KEEP_TOP_N" \
    --keep-ratio "$TARGET_ALIGN_KEEP_RATIO" \
    --max-per-seed "$TARGET_ALIGN_MAX_PER_SEED"
}

build_augmented_task() {
  cd "$REPO_ROOT"
  VULNBOOSTER_PYTHON="$PYTHON_BIN" \
  SOURCE_TASK="reveal" \
  NEW_TASK="$AUG_TASK_NAME" \
  AUG_JSON="$GEN_OUTPUT_RESULT_ROOT/final_augmented_vul.json" \
  LIMIT_GENERATED="$LIMIT_GENERATED" \
  MAX_ORIGIN_TRAIN="$MAX_ORIGIN_TRAIN" \
  MAX_ORIGIN_TEST="$MAX_ORIGIN_TEST" \
  bash "$REPO_ROOT/scripts/build_augmented_task.sh"
}

train_guide_and_regenerate_domain() {
  cd "$REPO_ROOT"
  VULNBOOSTER_PYTHON="$PYTHON_BIN" \
  TASK_NAME="$AUG_TASK_NAME" \
  ROOT_DIR="$REPO_ROOT/gvi_causalcode/data/" \
  TEST_TASK="$TEST_TASK" \
  GPU_ID="$GPU_ID" \
  BATCH_SIZE="$BATCH_SIZE" \
  EPOCHS="$GUIDE_EPOCHS" \
  EARLY_STOP="$EARLY_STOP" \
  ATTACK_TYPE="$ATTACK_TYPE" \
  GUIDE_RUN_TAG="guide_${RUN_TAG}" \
  bash "$REPO_ROOT/scripts/train_formal_guide_and_regenerate_domain.sh"
}

train_and_test_dual_domain() {
  cd "$REPO_ROOT/gvi_causalcode/train_bert"
  WANDB_MODE=offline \
  TRANSFORMERS_OFFLINE=1 \
  HF_HUB_OFFLINE=1 \
  "$PYTHON_BIN" run.py \
    --do_train \
    --do_test \
    --train_task "$AUG_TASK_NAME" \
    --test_task "$TEST_TASK" \
    --model_name linevul \
    --enhance_method CausalCode \
    --attack_type "$ATTACK_TYPE" \
    --domain_list "origin_s,linevul-CausalCode-token" \
    --epochs "$FINAL_EPOCHS" \
    --early_stop "$EARLY_STOP" \
    --batch_size "$BATCH_SIZE" \
    --gpu "$GPU_ID" \
    --root_dir "$REPO_ROOT/gvi_causalcode/data/"
}

main() {
  mkdir -p "$LOG_DIR"
  ensure_llm_env
  print_config

  run_generation
  run_post_process
  run_post_analysis
  if [ "$FILTER_MODE" = "source_target_align" ]; then
    run_cross_domain_alignment_filter
  fi
  build_augmented_task
  train_guide_and_regenerate_domain
  train_and_test_dual_domain

  echo
  echo "正式增强流水线完成。"
  echo "增强任务目录: $REPO_ROOT/gvi_causalcode/data/$AUG_TASK_NAME"
  echo "生成目录: $GEN_OUTPUT_ROOT"
  echo "过滤结果目录: $GEN_OUTPUT_RESULT_ROOT"
}

main "$@"
