# 项目记忆

最后更新：2026-04-02

## 项目目标

项目名称：

- 基于数据增强的源代码漏洞检测技术研究

当前总体思路：

- 结合 `CausalCode` 和 `VulScribeR`
- 用 `VulScribeR` 风格的方法提升漏洞样本数量、质量和多样性
- 用 `CausalCode` 降低源代码模型学到伪相关特征的风险，提高鲁棒性和跨数据集泛化能力
- 当前工程实现上，优先采用“提示词 + 大语言模型 + 后过滤”的轻量增强路线，把检索增强视作后续可选升级

## 参考论文

### 1. CausalCode

论文：

- `A Causal Learning Framework for Enhancing Robustness of Source Code Models`
- DOI：`10.1145/3729387`

核心思想：

- 代码模型容易学到伪相关特征，而不是真正和漏洞有关的因果特征
- 通过构造干预样本打破伪相关
- 在经验风险最小化之外增加表示对齐或因果约束
- 提升模型对扰动和跨域测试的稳定性

和当前仓库最相关的点：

- 干预方式主要是变量名替换、死代码插入
- 训练时会同时加载原始域和干预域
- 训练损失中加入因果对齐项

### 2. VulScribeR

论文：

- `VulScribeR: Exploring RAG-based Vulnerability Augmentation with LLMs`
- DOI：`10.1145/3760775`

核心思想：

- 通过检索增强生成，为大模型提供更可靠的漏洞模式和相似案例
- 目标是提高生成漏洞样本的质量、可控性和多样性

对本项目的意义：

- 它更适合放在“数据扩充”阶段
- 不应该直接替代当前 `CausalCode` 的配对干预训练

## 当前仓库的真实状态

这个仓库目前并不是完整的 `VulScribeR + CausalCode` 实现。

当前真实拥有的部分：

- 一套 `CausalCode + LineVul` 的训练管线
- 一套基于大模型的漏洞代码生成管线
- 一套生成后清洗、相似度过滤、静态分析过滤相关脚本

当前还没有真正实现的部分：

- 生成前检索注入 prompt 的完整 RAG 设计
- 从生成样本到正式因果训练的统一闭环

重要结论：

- 当前 `generation/` 更接近“通用漏洞样本生成 + 过滤”
- 还不能算论文意义上的完整 `VulScribeR`

## 关键代码位置

### 因果训练主入口

- `gvi_causalcode/train_bert/run.py`

它负责：

- 同时加载原始域和干预域
- 进行因果对齐训练
- 按跨数据集方式组织训练与测试

### 干预样本生成

- `gvi_causalcode/train_bert/attacker4simple.py`

当前已实现干预方式：

- token rename
- dead-code insertion

### 数据集封装

- `gvi_causalcode/train_bert/dataset.py`

这里非常关键，因为：

- 多域 batch 是否按 `id` 对齐，直接决定当前 `CausalCode` 训练是否成立

### 当前 LLM 生成流程

主要文件：

- `gvi_causalcode/generation/config.py`
- `gvi_causalcode/generation/chain_gen.py`
- `gvi_causalcode/generation/post_process.py`
- `gvi_causalcode/generation/post_analysis.py`

当前流程大致是：

1. 读取漏洞种子函数
2. 执行多步 prompt chain
3. 生成候选漏洞函数
4. 提取和清洗代码
5. 用相似度和静态分析做后置过滤

重要判断：

- 当前检索更多是“生成后过滤”
- 而不是“生成前把检索结果放进提示词”
- 所以这还不是严格意义上的 RAG 生成
- 从工程实用性看，现阶段更适合先把“轻量提示词生成”跑稳，再考虑是否引入真正的检索增强

## 当前最重要的限制

当前 `CausalCode` 训练要求多域样本一一对应。

代码层面的证据：

- `run.py` 中明确断言两个域的 batch `id` 必须一致

这意味着：

- 直接自由生成出来的新漏洞样本，不能直接拿来充当当前因果训练里的第二域
- 如果新样本不保留原始样本的配对关系，当前训练代码就会失败，或者在理论上不成立

这是整个项目当前最重要的整合约束。

## 推荐的整合路线

建议顺序：

1. 先做 `VulScribeR` 风格的数据增强，获得更高质量的漏洞样本
2. 将筛选后的漏洞样本合并进训练池
3. 再对这个新训练池生成 `CausalCode` 配对干预样本
4. 最后用“原始域 + 干预域”做因果训练
5. 在 `ReVeal -> Devign` 这类跨数据集设置上评估

简化理解：

- `VulScribeR` 解决样本数量和质量
- `CausalCode` 解决鲁棒性和伪相关
- 工程第一阶段可以先用“提示词生成”承担 `VulScribeR` 的大部分数据增强角色

## 明确不要直接做的事

不要直接这样做：

- 把自由生成的新漏洞函数直接作为当前 `CausalCode` 的第二域

原因：

- 当前代码需要按 `id` 严格配对
- 当前损失设计默认多域样本一一对应

如果以后真的想把“非配对生成样本”直接并入因果训练，需要至少做其中之一：

- 改训练损失
- 增加样本匹配逻辑
- 把生成样本转成每个原样本的一对一增强形式

## 项目推进路线

### 阶段 1：记忆、结构、仓库整理

- 保存关键结论到 markdown
- 规整目录
- 清理 git 跟踪范围
- 区分代码、数据、日志、生成物、checkpoint、笔记

### 阶段 2：环境与复现

- 建立干净的 Ubuntu / Linux 训练环境
- 固定依赖版本
- 去掉硬编码路径和密钥
- 增加一键训练、生成、过滤、评估脚本

### 阶段 3：真正的 VulScribeR 风格增强

应构建的能力：

- 建立漏洞检索语料库
- 在生成前检索相似漏洞模式
- 将检索内容注入 prompt
- 生成候选漏洞函数
- 用相似度、静态分析和去重做筛选

### 阶段 4：CausalCode 整合

- 将高质量生成数据并入训练集
- 生成成对的因果干预域
- 保持当前多域因果训练方式

### 阶段 5：实验

建议的实验组：

1. 基线 `LineVul`
2. `LineVul + 当前 CausalCode`
3. `LineVul + VulScribeR 风格生成增强`
4. `LineVul + VulScribeR 风格增强 + CausalCode`

建议的指标：

- Accuracy
- Precision
- Recall
- F1
- 跨数据集泛化
- 扰动鲁棒性

## 当前数据状态

从本地处理后数据来看：

- `ReVeal`：`18188` 训练，`4546` 测试
- `Devign`：`21855` 训练，`5463` 测试

因此：

- 现有数据已经足够支撑真实训练实验

## WSL 与 Ubuntu 建议

当前习惯：

- 你通常在 WSL 中运行

长期目标：

- 最终训练希望放到物理 Ubuntu 机器或服务器上

建议：

- 真正长时间训练时，尽量用 Linux 原生路径，不要长期依赖 `/mnt/d/...`
- 在 Ubuntu 或服务器上最好把项目放到类似 `~/projects/VulnBooster`
- 数据、日志、checkpoint、生成结果不要进入 Git

针对你的本机硬件：

- RTX 4060 Laptop 可以跑这个项目
- 但显存比较紧，参数应偏保守

## 当前仓库中已经发现过的问题

### 1. 早期环境依赖不齐

在前期分析时，当前 shell 里曾缺少过这些关键包：

- `torch`
- `transformers`
- `wandb`
- `pandas`
- `langchain_openai`
- `langchain_classic`
- `langchain_community`
- `chromadb`

这说明：

- 环境管理必须单独规范化

### 2. 生成配置中曾有硬编码 API key

后续已经修复：

- 现在生成配置改为读环境变量

### 3. 一些脚本里存在硬编码绝对路径

这些路径在从 WSL 迁移到 Ubuntu 或服务器时会出问题。

已经开始修正：

- 将明显写死的 `/root/...` 路径改为相对路径或可传参形式

### 4. 一些旧脚本兼容性一般

例如：

- 部分脚本的参数设计不够统一
- 部分训练流程中的命名和注释容易让人误解

这些暂时不一定阻断运行，但后面最好逐步清理。

## 2026-04-02 WSL 训练验证

这一天完成了第一轮真正意义上的本地端到端训练验证。

### 已验证环境

- conda 环境：`vulnbooster`
- 可靠解释器路径：
  - `/home/lamaper/miniconda3/envs/vulnbooster/bin/python`
- WSL 中 `nvidia-smi` 可用
- 可见 GPU：`NVIDIA GeForce RTX 4060 Laptop GPU`
- 安装成功的 CUDA 版 PyTorch：
  - `torch 2.6.0+cu124`
- `transformers 5.4.0` 可导入
- `wandb 0.25.1` 可导入
- 本地 Hugging Face 缓存已包含 `microsoft/codebert-base`

### 重要经验

- 当前 shell 若已激活别的虚拟环境，`conda run` 可能解析到错误的 Python
- 因此现在更推荐显式调用 conda 环境解释器

### Smoke test 结果

创建了一个极小数据子集目录：

- `.smoke_data/`

验证结果：

- CPU smoke test 可以进入真实训练循环
- GPU smoke test 也可以成功跑完

验证的训练配置：

- task：`reveal -> devign`
- model：`linevul`
- enhance method：`CausalCode`
- attack type：`token`

GPU smoke test 使用过的命令形式：

```bash
cd gvi_causalcode/train_bert
WANDB_MODE=offline TRANSFORMERS_OFFLINE=1 HF_HUB_OFFLINE=1 \
/home/lamaper/miniconda3/envs/vulnbooster/bin/python run.py \
  --do_train \
  --train_task reveal \
  --test_task devign \
  --model_name linevul \
  --enhance_method CausalCode \
  --attack_type token \
  --domain_list origin_s,linevul-CausalCode-token \
  --epochs 1 \
  --batch_size 2 \
  --gpu 0 \
  --root_dir /mnt/d/Scientific/VulnBooster/.smoke_data/
```

### 验证结论

- 当前 WSL 本地环境已经可以支撑短训练
- 下一步应从 smoke test 进入真实短训练和正式实验

## 真实短训练已启动

在 `2026-04-02`，已经启动了一次真实数据短训练。

配置：

- 启动脚本：`scripts/train_short_gpu.sh`
- train task：`reveal`
- test task：`devign`
- enhance method：`CausalCode`
- attack type：`token`
- epochs：`1`
- batch size：`8`
- gpu：`0`
- root dir：`/mnt/d/Scientific/VulnBooster/gvi_causalcode/data/`

本地日志位置：

- 主日志：`logs/formal_short_realdata_gpu_debug.log`
- wandb 离线日志：`gvi_causalcode/train_bert/wandb/`

启动后观察到：

- 训练成功进入真实 epoch 循环
- 速度大约 `1.0 ~ 1.2 batch/s`
- GPU 显存占用约 `7755 / 8188 MiB`
- GPU 利用率可到 `100%`

这说明：

- 当前真实训练链路已经可用
- `batch_size=8` 在本机 4060 Laptop 上是可跑的，但显存已接近上限

## 如果未来上下文丢失，先记住这几件事

1. 当前仓库本质上是 `CausalCode + LineVul`，还不是完整 `VulScribeR`
2. 当前生成流程更像“生成 + 后过滤”，不是真正的 RAG prompt 注入
3. 当前 `CausalCode` 训练要求多域样本按 `id` 对齐
4. 正确整合顺序是“先扩充数据，再生成配对干预域，再做因果训练”
5. 环境、路径、依赖和启动脚本已经基本验证过，可以开始正式实验
