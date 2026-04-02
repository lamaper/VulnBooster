#!/usr/bin/env bash
set -euo pipefail

ENV_NAME="${ENV_NAME:-vulnbooster}"
PYTHON_VERSION="${PYTHON_VERSION:-3.10}"
REPO_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"

if ! command -v conda >/dev/null 2>&1; then
  echo "未检测到 conda，请先安装 Miniconda 或 Anaconda。"
  exit 1
fi

CONDA_BASE="$(conda info --base)"
source "$CONDA_BASE/etc/profile.d/conda.sh"

if ! conda env list | awk '{print $1}' | grep -qx "$ENV_NAME"; then
  conda create -y -n "$ENV_NAME" "python=$PYTHON_VERSION" pip
fi

ENV_PY="$CONDA_BASE/envs/$ENV_NAME/bin/python"

"$ENV_PY" -m pip install --upgrade pip
"$ENV_PY" -m pip install --index-url https://download.pytorch.org/whl/cu124 "torch==2.6.0+cu124"
"$ENV_PY" -m pip install -r "$REPO_ROOT/requirements/vulnbooster-gpu.txt"

echo
echo "环境初始化完成。"
echo "Python 解释器：$ENV_PY"
echo "建议接下来执行："
echo "  nvidia-smi"
echo "  $ENV_PY - <<'PY'"
echo "import torch"
echo "print(torch.__version__)"
echo "print(torch.cuda.is_available())"
echo "print(torch.cuda.get_device_name(0) if torch.cuda.is_available() else 'NO CUDA')"
echo "PY"
