#!/usr/bin/env bash
set -euo pipefail

REPO_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
PYTHON_BIN="${VULNBOOSTER_PYTHON:-/home/lamaper/miniconda3/envs/vulnbooster/bin/python}"

GEN_LIMIT="${GEN_LIMIT:-1}"
NUM_VARIANTS="${NUM_VARIANTS:-2}"
PROMPT_MODE="${PROMPT_MODE:-pattern_generate_repair}"
GEN_OUTPUT_ROOT="${GEN_OUTPUT_ROOT:-$REPO_ROOT/gvi_causalcode/data/reveal/deepseek_smoke_gen}"
GEN_OUTPUT_RESULT_ROOT="${GEN_OUTPUT_RESULT_ROOT:-$REPO_ROOT/gvi_causalcode/data/reveal/deepseek_smoke_gen_result}"

AUG_TASK_NAME="${AUG_TASK_NAME:-reveal_aug_smoke}"
LIMIT_GENERATED="${LIMIT_GENERATED:-2}"
MAX_ORIGIN_TRAIN="${MAX_ORIGIN_TRAIN:-64}"
MAX_ORIGIN_TEST="${MAX_ORIGIN_TEST:-16}"

GPU_ID="${GPU_ID:-0}"
BATCH_SIZE="${BATCH_SIZE:-4}"
EPOCHS="${EPOCHS:-1}"
RUN_TAG="${RUN_TAG:-aug_smoke_pipeline_$(date +%Y%m%d_%H%M%S)}"


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
    echo "缺少 OPENAI_API_KEY。请先 export，或把它写进可被交互 bash 读取的配置。" >&2
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
  echo "NUM_VARIANTS=$NUM_VARIANTS"
  echo "GEN_OUTPUT_ROOT=$GEN_OUTPUT_ROOT"
  echo "GEN_OUTPUT_RESULT_ROOT=$GEN_OUTPUT_RESULT_ROOT"
  echo "AUG_TASK_NAME=$AUG_TASK_NAME"
  echo "LIMIT_GENERATED=$LIMIT_GENERATED"
  echo "MAX_ORIGIN_TRAIN=$MAX_ORIGIN_TRAIN"
  echo "MAX_ORIGIN_TEST=$MAX_ORIGIN_TEST"
  echo "GPU_ID=$GPU_ID"
  echo "BATCH_SIZE=$BATCH_SIZE"
  echo "EPOCHS=$EPOCHS"
  echo "RUN_TAG=$RUN_TAG"
}


run_generation() {
  cd "$REPO_ROOT/gvi_causalcode/generation"
  GEN_OUTPUT_ROOT="$GEN_OUTPUT_ROOT" \
  LLM_BASE_URL="$LLM_BASE_URL" \
  LLM_MODEL="$LLM_MODEL" \
  OPENAI_API_KEY="$OPENAI_API_KEY" \
  "$PYTHON_BIN" chain_gen.py \
    --prompt-mode "$PROMPT_MODE" \
    --limit "$GEN_LIMIT" \
    --num-variants "$NUM_VARIANTS" \
    --output-root "$GEN_OUTPUT_ROOT"
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


build_augmented_task() {
  cd "$REPO_ROOT/gvi_causalcode/generation"
  "$PYTHON_BIN" build_augmented_task.py \
    --source-root "$REPO_ROOT/gvi_causalcode/data" \
    --output-root "$REPO_ROOT/.smoke_data" \
    --source-task reveal \
    --new-task "$AUG_TASK_NAME" \
    --aug-json "$GEN_OUTPUT_RESULT_ROOT/final_augmented_vul.json" \
    --limit-generated "$LIMIT_GENERATED" \
    --max-origin-train "$MAX_ORIGIN_TRAIN" \
    --max-origin-test "$MAX_ORIGIN_TEST"
}


generate_causal_domain() {
  cd "$REPO_ROOT/gvi_causalcode/train_bert"
  PYTHONUNBUFFERED=1 \
  TRANSFORMERS_OFFLINE=1 \
  HF_HUB_OFFLINE=1 \
  "$PYTHON_BIN" attacker4simple.py \
    --task "$AUG_TASK_NAME" \
    --enhance_method CausalCode \
    --attack_type token \
    --gpu "$GPU_ID" \
    --root_dir "$REPO_ROOT/.smoke_data/"
}


train_smoke_model() {
  cd "$REPO_ROOT"
  VULNBOOSTER_PYTHON="$PYTHON_BIN" \
  ROOT_DIR="$REPO_ROOT/.smoke_data/" \
  TRAIN_TASK="$AUG_TASK_NAME" \
  TEST_TASK="devign" \
  BATCH_SIZE="$BATCH_SIZE" \
  EPOCHS="$EPOCHS" \
  GPU_ID="$GPU_ID" \
  RUN_TAG="$RUN_TAG" \
  bash scripts/train_short_gpu.sh
}


main() {
  ensure_llm_env
  print_config

  run_generation
  run_post_process
  run_post_analysis
  build_augmented_task
  generate_causal_domain
  train_smoke_model

  echo
  echo "Smoke pipeline 完成。"
  echo "生成结果目录: $GEN_OUTPUT_ROOT"
  echo "过滤结果目录: $GEN_OUTPUT_RESULT_ROOT"
  echo "增强任务目录: $REPO_ROOT/.smoke_data/$AUG_TASK_NAME"
  echo "训练日志: $REPO_ROOT/logs/${RUN_TAG}.log"
}


main "$@"
