# WSL GPU 环境说明

本文档记录当前已经验证可用的 WSL 本地训练环境。

## 当前已验证环境

- 系统：WSL2 Ubuntu 22.04
- 显卡：NVIDIA GeForce RTX 4060 Laptop GPU
- 驱动检查：`nvidia-smi` 已可在 WSL 中正常运行
- Conda 环境名：`vulnbooster`
- Python：`3.10.20`
- PyTorch：`2.6.0+cu124`
- Transformers：`5.4.0`
- wandb：`0.25.1`
- 已固定依赖文件：`requirements/vulnbooster-gpu.txt`

## 重要经验

当前 shell 如果已经激活了别的虚拟环境，`conda run` 有时会错误地解析到别的 Python 或 pip。

因此目前最稳妥的解释器写法是：

```bash
/home/lamaper/miniconda3/envs/vulnbooster/bin/python
```

## 已验证命令

下面这个检查命令已经通过：

```bash
/home/lamaper/miniconda3/envs/vulnbooster/bin/python - <<'PY'
import torch
print(torch.__version__)
print(torch.cuda.is_available())
print(torch.cuda.get_device_name(0))
PY
```

期望输出：

- `torch` 显示 `2.6.0+cu124`
- `torch.cuda.is_available()` 为 `True`
- 设备名能看到本机 `RTX 4060 Laptop GPU`

## 本机训练建议

- 建议先用 `batch_size=8`
- 建议先使用 `WANDB_MODE=offline`
- 如果本地 Hugging Face 缓存已经存在，建议同时设置离线模式
- 真正的大规模正式训练，仍建议最终迁移到物理 Ubuntu 机器或租赁服务器

## 已观测到的显存情况

在真实数据短训练中观察到：

- `batch_size=8` 可以在 4060 Laptop GPU 上运行
- 显存占用大约 `7755 / 8188 MiB`
- GPU 利用率最高达到 `100%`

这意味着：

- `batch_size=8` 是目前本机比较实用的默认值
- 但显存余量已经不多，继续加大 batch 风险较高

## 本地模型缓存

本地 Hugging Face 缓存中已经存在 `microsoft/codebert-base`，因此当前环境支持离线加载该模型。
