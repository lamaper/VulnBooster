#!/usr/bin/env bash
set -euo pipefail

REPO_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
PYTHON_BIN="${VULNBOOSTER_PYTHON:-/home/lamaper/miniconda3/envs/vulnbooster/bin/python}"
PROMPT_MODE="${PROMPT_MODE:-direct_generate}"
LIMIT="${LIMIT:-10}"
NUM_VARIANTS="${NUM_VARIANTS:-4}"

echo "仓库根目录=$REPO_ROOT"
echo "Python 解释器=$PYTHON_BIN"
echo "提示词模式=$PROMPT_MODE"
echo "样本上限=$LIMIT"
echo "每条变体数=$NUM_VARIANTS"

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
