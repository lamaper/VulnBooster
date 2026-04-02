# 项目恢复指南

最后更新：2026-04-02

## 1. 这个项目现在到底在做什么

项目主题：

- 基于数据增强的源代码漏洞检测

目前想要实现的总体方向：

- 用 `VulScribeR` 风格的方法扩充和提升漏洞样本质量
- 用 `CausalCode` 提升训练鲁棒性、降低伪相关、增强跨数据集泛化
- 当前工程路径上，优先采用“提示词 + 大模型 + 后过滤”的轻量生成方案

一句话理解：

- `VulScribeR` 偏向“把数据变好”
- `CausalCode` 偏向“把训练变稳”

## 2. 这个仓库目前真实已经做到什么

这个仓库还不是一个完整的 `VulScribeR + CausalCode` 成品实现。

目前已经真实存在的能力：

- 一个 `CausalCode + LineVul` 的训练流程
- 一个基于大模型的漏洞代码生成流程
- 一套生成后过滤与分析脚本
- 一套跨数据集训练与测试框架
- 一个更轻量的“多提示词模式漏洞生成器”方向，适合先代替复杂 RAG 做快速数据增强

目前还没有真正完成的部分：

- 真正意义上的“检索增强生成”提示链
- 从生成、清洗、合并到因果训练的一体化闭环
- 完整标准化、可直接迁移的实验系统

## 3. 现在最关键的限制

当前 `CausalCode` 训练有一个最重要的前提：

- 多域样本必须按 `id` 对齐

实际含义：

- `origin_s` 和 `linevul-CausalCode-token` 这两个域，当前代码默认它们是一一对应的
- 纯自由生成出来的新漏洞函数，不能直接拿来当作当前因果训练中的第二域

所以正确顺序应该是：

1. 先做 `VulScribeR` 风格的数据扩充
2. 把新生成的漏洞样本合并成新的训练集
3. 再对这个新训练集生成配对的 `CausalCode` 干预数据
4. 最后再做因果训练

这件事是整个项目现在最重要的设计约束。

## 4. 关键代码入口

以后回项目时，最该记住这些文件：

- 主训练入口：`gvi_causalcode/train_bert/run.py`
- 干预样本生成：`gvi_causalcode/train_bert/attacker4simple.py`
- 数据集封装：`gvi_causalcode/train_bert/dataset.py`
- 生成配置：`gvi_causalcode/generation/config.py`
- 生成主入口：`gvi_causalcode/generation/chain_gen.py`
- 生成后处理：`gvi_causalcode/generation/post_process.py`
- 相似度与过滤：`gvi_causalcode/generation/post_analysis.py`

## 5. 我们已经验证过什么

### 仓库整理

- Git 仓库已经做过一次瘦身整理
- 大体积数据、生成结果、缓存、日志等已经尽量从仓库跟踪中剥离
- 敏感信息不再直接写死在受 Git 跟踪的生成配置里

### WSL 训练环境

已经验证：

- WSL 中 GPU 可见
- 本机显卡是 `NVIDIA GeForce RTX 4060 Laptop GPU`
- 可用 conda 环境是 `vulnbooster`
- Python 是 `3.10.20`
- PyTorch 是 `2.6.0+cu124`
- `transformers 5.4.0`
- `wandb 0.25.1`

### 训练链路

已经证明：

- 极小子集 smoke test 能跑
- 真实数据训练也能正常启动
- WSL 下 GPU 训练能真实进入 epoch 循环

所以现在真正的瓶颈已经不是“代码能不能运行”，而是：

- 怎么把实验做规范
- 怎么把数据路线走通
- 怎么把环境迁移到更稳定的训练平台

## 6. 当前这类训练实验到底在做什么

当前你正在跑的短训练配置是：

- 训练集：`reveal`
- 跨域测试集：`devign`
- 模型：`linevul`
- 增强方式：`CausalCode`
- 干预类型：`token`
- 域组合：`origin_s,linevul-CausalCode-token`

这类实验的本质是：

- 训练一个漏洞检测模型
- 不是在生成新的数据集

它直接会产出的东西通常是：

- 训练日志
- `wandb` 离线日志
- 如果训练轮数足够并进入验证阶段，可能会产出模型权重如 `best.pt`

但当前代码有一个重要细节：

- 只有在 `epoch > 2` 时才会开始验证并保存最佳模型

所以：

- `1 epoch` 的短训练主要用于验证流程和观察运行行为
- 不能把它当成正式最终模型训练

## 7. 你接下来最应该做什么

如果你是隔了一阵子回来，当前最正确的推进顺序是：

1. 固化环境和启动方式
2. 把当前 `CausalCode + LineVul` 路线先做出一套稳定基线
3. 再做真正的 `VulScribeR` 风格生成流程
4. 合并生成数据形成新版本训练集
5. 再对新训练集生成配对的 `CausalCode` 干预域
6. 最后做成组实验比较

## 8. 后续优化路线

### A. 近期最值得做的优化

- 统一训练命令和日志路径
- 统一 checkpoint 保存目录
- 增加正式 train + eval 启动脚本
- 把环境部署流程写成可直接复用的脚本
- 明确区分 smoke test、短训练、正式实验

### B. 数据流程优化

这是后面论文价值最强的部分：

- 整理生成流程
- 先把轻量提示词生成路线做成稳定基线
- 让 prompt 和参数可复现
- 增加去重和元数据记录
- 记录每个生成样本的来源与筛选过程
- 形成清晰的数据集版本管理方式

建议后续采用类似这样的命名：

- `baseline_reveal`
- `reveal_plus_generated_v1`
- `reveal_plus_generated_v1_causal_token`
- `reveal_plus_generated_v1_causal_deadcode`

### C. 训练优化

目前本机 4060 Laptop GPU 的经验是：

- `batch_size=8` 能跑
- 显存已经接近上限

因此建议：

- 本机先把 `batch_size=8` 当默认起点
- 优先增加训练轮数，而不是继续增大 batch
- 真正要做长实验、多组实验、更多模型比较时，优先上服务器

### D. 研究实验优化

建议实验梯度：

1. 基线 `LineVul`
2. `LineVul + 当前 CausalCode`
3. `LineVul + 漏洞生成数据`
4. `LineVul + 漏洞生成数据 + CausalCode`

建议记录指标：

- Accuracy
- Precision
- Recall
- F1
- 跨数据集泛化
- 扰动鲁棒性

## 9. 目前仍然存在的风险点

- `transformers 5.4.0` 目前可用，但最好长期锁版本并持续关注兼容性
- WSL 路径和 shell 状态仍然可能比原生 Linux 更脆弱
- 当前已有短训练脚本，但还缺一个更完整的正式实验脚本
- 这个仓库目前已经能做研究推进，但还没达到“完全工业化复现”

## 10. 下次回项目时先看什么

建议按这个顺序读：

1. `docs/notes/PROJECT_RESUME_GUIDE.md`
2. `docs/notes/PROJECT_MEMORY.md`
3. `docs/WSL_GPU_ENV.md`
4. `docs/SERVER_TRAINING_PLAYBOOK.md`
5. `gvi_causalcode/README.md`
6. `gvi_causalcode/train_bert/run.py`

## 11. 如果只做一件具体的事

如果你现在只想做一个最正确的下一步，那就是：

- 先把当前 `CausalCode + LineVul` 这条线做出一套清晰、稳定、可重复的正式基线实验

原因：

- 它能给后面所有增强实验提供参照
- 能帮助你分清未来提升到底来自“数据更好”还是“训练更稳”
- 也能减少后面把 `VulScribeR` 接进来时的混乱
