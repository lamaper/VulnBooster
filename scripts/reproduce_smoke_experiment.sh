#!/usr/bin/env bash
set -euo pipefail

REPO_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"

export RUN_TAG="${RUN_TAG:-repro_smoke_$(date +%Y%m%d_%H%M%S)}"

echo "启动一键 smoke 复现实验..."
echo "RUN_TAG=$RUN_TAG"

exec bash "$REPO_ROOT/scripts/run_augmented_smoke_pipeline.sh" "$@"
