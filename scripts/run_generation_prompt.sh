#!/usr/bin/env bash
set -euo pipefail

REPO_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
PYTHON_BIN="${VULNBOOSTER_PYTHON:-/home/lamaper/miniconda3/envs/vulnbooster/bin/python}"
PROMPT_MODE="${PROMPT_MODE:-pattern_generate_repair}"
LIMIT="${LIMIT:-10}"
NUM_VARIANTS="${NUM_VARIANTS:-4}"
RUN_POST_PROCESS="${RUN_POST_PROCESS:-1}"
RUN_POST_ANALYSIS="${RUN_POST_ANALYSIS:-0}"

echo "仓库根目录=$REPO_ROOT"
echo "Python 解释器=$PYTHON_BIN"
echo "提示词模式=$PROMPT_MODE"
echo "样本上限=$LIMIT"
echo "每条变体数=$NUM_VARIANTS"
echo "生成后处理=$RUN_POST_PROCESS"
echo "相似度分析=$RUN_POST_ANALYSIS"

cd "$REPO_ROOT/gvi_causalcode/generation"

CMD=(
  "$PYTHON_BIN" chain_gen.py
  --prompt-mode "$PROMPT_MODE"
  --num-variants "$NUM_VARIANTS"
)

if [ "${LIMIT}" -gt 0 ]; then
  CMD+=(--limit "$LIMIT")
fi

"${CMD[@]}"

if [ "$RUN_POST_PROCESS" = "1" ]; then
  "$PYTHON_BIN" post_process.py
fi

if [ "$RUN_POST_ANALYSIS" = "1" ]; then
  "$PYTHON_BIN" post_analysis.py
fi
