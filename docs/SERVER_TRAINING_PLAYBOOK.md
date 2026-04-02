# 服务器训练部署手册

最后更新：2026-04-02

## 1. 文档目的

本文档说明如何把当前项目从本地 WSL 环境快速迁移到租赁 GPU 服务器，并尽量减少部署中的不确定性。

核心原则只有一句话：

- 不要在服务器上临场试错，尽量把环境、路径、命令和数据都提前标准化

## 2. 最推荐的部署思路

最快也最稳的方案是：

1. 租一台 Linux GPU 服务器
2. 把仓库放到 Linux 原生路径
3. 只同步必要的处理后数据和文档
4. 用脚本初始化 conda 环境
5. 先验证 CUDA、PyTorch、模型加载
6. 再在 `tmux` 中启动训练

这个方案明显优于：

- 继续在 `/mnt/d/...` 这类挂载路径上长期训练
- 到服务器后再临时一个个装包
- 依赖当前本地 shell 的隐式环境状态

## 3. 建议租什么服务器

最低实用建议：

- Ubuntu 22.04 或 24.04
- NVIDIA 驱动已配置好
- CUDA 可用
- 至少 16 GB 内存
- 至少 100 GB 空闲磁盘

比较舒服的 GPU 选择：

- RTX 4090 级别
- A5000 / A6000
- A10 / A40
- 其他现代 CUDA 显卡，只要显存足够即可

如果预算有限：

- 24 GB VRAM 的服务器卡已经会比本地 4060 Laptop 好用很多

## 4. 服务器上需要同步什么

你不需要把本地所有东西都搬过去。

建议同步这些：

- 仓库代码
- `docs/notes/PROJECT_MEMORY.md`
- `docs/notes/PROJECT_RESUME_GUIDE.md`
- `docs/WSL_GPU_ENV.md`
- 处理后的训练数据目录：
  - `gvi_causalcode/data/reveal/dataset/`
  - `gvi_causalcode/data/devign/dataset/`
- 你明确要训练的生成后数据集

通常不建议同步这些：

- `.git/`
- `.smoke_data/`
- `wandb/`
- 本地日志
- 不参与训练的大体积临时产物

## 5. 服务器推荐目录布局

建议在服务器上使用 Linux 原生路径，例如：

```bash
~/projects/VulnBooster
~/datasets/VulnBooster
~/logs/VulnBooster
```

不要把正式训练长期放在 Windows 挂载路径上。

## 6. 服务器快速部署步骤

### A. 克隆仓库

```bash
mkdir -p ~/projects
cd ~/projects
git clone <你的仓库地址> VulnBooster
cd VulnBooster
```

### B. 从本地同步处理后的数据

建议从本地机器执行：

```bash
rsync -avP /mnt/d/Scientific/VulnBooster/gvi_causalcode/data/reveal/dataset/ user@server:~/projects/VulnBooster/gvi_causalcode/data/reveal/
rsync -avP /mnt/d/Scientific/VulnBooster/gvi_causalcode/data/devign/dataset/ user@server:~/projects/VulnBooster/gvi_causalcode/data/devign/
```

如果你已有自己要训练的生成后数据集，也一起同步过去。

### C. 初始化环境

直接在服务器仓库根目录执行：

```bash
bash scripts/bootstrap_vulnbooster_env.sh
```

### D. 验证 GPU 和 PyTorch

```bash
nvidia-smi
/home/$USER/miniconda3/envs/vulnbooster/bin/python - <<'PY'
import torch
print(torch.__version__)
print(torch.cuda.is_available())
print(torch.cuda.get_device_name(0))
PY
```

期望结果：

- `torch.cuda.is_available()` 为 `True`

## 7. 服务器上怎么启动训练

建议在 `tmux` 中运行：

```bash
tmux new -s vulntrain
cd ~/projects/VulnBooster
GPU_ID=0 EPOCHS=5 BATCH_SIZE=8 ROOT_DIR=$PWD/gvi_causalcode/data/ RUN_TAG=server_reveal_to_devign_e5 bash scripts/train_short_gpu.sh
```

然后按：

```bash
Ctrl+b d
```

即可后台保留会话。

重新进入：

```bash
tmux attach -t vulntrain
```

## 8. 怎么看训练状态

查看日志：

```bash
tail -f ~/projects/VulnBooster/logs/server_reveal_to_devign_e5.log
```

查看 GPU：

```bash
watch -n 2 nvidia-smi
```

## 9. 为什么这种方式部署最快

真正让部署变快的，不只是“下载速度快”，而是：

- 环境提前定好
- 路径提前定好
- 启动命令提前定好
- 只同步必要数据
- 尽量避免服务器上的交互式调试

所以当前最关键的准备文件是：

- `requirements/vulnbooster-gpu.txt`
- `scripts/bootstrap_vulnbooster_env.sh`
- `scripts/train_short_gpu.sh`

## 10. 常见坑

### 坑 1：Python 用错了

一定要检查：

```bash
which python
```

更稳的方式是直接写绝对路径：

```bash
~/miniconda3/envs/vulnbooster/bin/python
```

### 坑 2：路径还沿用本地 `/mnt/d/...`

迁移到服务器后，不要再保留本地 Windows 挂载路径。

### 坑 3：只传了代码，没有传处理后的数据

当前训练代码依赖现成的 `data.pkl.gz` 等处理结果。

### 坑 4：误以为短训练一定会保存模型

当前代码只有在后续 epoch 进入验证后，才会开始保存 `best.pt`。

所以：

- `1 epoch` 更像是 sanity check
- 真正要产出模型的实验要更长

## 11. 推荐的服务器实验顺序

最稳妥的顺序是：

1. 先在服务器上跑通当前基线训练
2. 保存这套基线日志和指标
3. 再同步或生成新的增强数据集
4. 如有需要，再生成配对的 `CausalCode` 干预域
5. 用固定配置跑正式实验
6. 把日志和 checkpoint 同步回本地

## 12. 最终建议

如果你准备租服务器，最省时间的实际方案是：

- 继续使用当前仓库作为代码基座
- 服务器上全部改成 Linux 原生路径
- 用 `scripts/bootstrap_vulnbooster_env.sh` 初始化环境
- 先跑一轮已经验证过的 `reveal -> devign` 短训练
- 确认没问题后，再开始更长、更正式的训练实验
