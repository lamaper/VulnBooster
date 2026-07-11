# 项目工作记忆

最后更新：2026-07-10

## 1. 项目定位

项目主题是“基于数据增强的源代码漏洞检测”。当前主目标不是直接更换最终检测器，而是围绕 `PrimeVul` 构建一条可复现的增强闭环，并证明增强数据能够稳定提升下游漏洞检测性能。

当前冻结主链路为：

`PrimeVul 数据清洗 -> Joern 静态切片 -> LLM 语义初筛 -> LLM 融合精炼得到教师切片 refined_code -> line_slicer.py 对齐回原函数并生成行级标签 -> 训练小模型切片器 -> 用切片器给 baseline 漏报样本预测 line_slice -> augmentation.py 基于切片、CWE 知识和漏洞机理生成增强样本 -> validation.py 做语法/对齐/锚点/非平凡性过滤 -> merge.py 合并增强训练集 -> training.py 重训检测器 -> calibration.py / 报告脚本做阈值校准与评估`

## 2. 当前代码结构

### 2.1 核心包

- `src/vulnbooster/cleaning.py`
  - 清洗 `PrimeVul` 样本中的函数代码，移除注释和空白噪声。
- `src/vulnbooster/static_slice.py`
  - 调度 `joern-parse` 和 `joern`，通过 `slice/slice.sc` 生成静态切片。
- `src/vulnbooster/llm.py`
  - `LLMPreFilter`：对原函数做 LLM 漏洞相关区域初筛。
  - `LLMFusionRefiner`：融合静态切片与 LLM 初筛，生成教师切片 `refined_code`。
- `src/vulnbooster/line_slicer.py`
  - 将教师切片对齐回原函数，构造 `matched_teacher_line_numbers` 和 `line_labels`。
  - 训练 `CodeBERT` 行级二分类切片器。
  - 对漏报样本预测 `line_slice`。
- `src/vulnbooster/codet5_slicer.py`
  - 新增 `CodeT5` 行号序列切片器。
  - 输入是带行号的完整函数和静态提示，输出是 `L003 L004 ...` 形式的行号集合。
  - 支持训练、评估、预测、静态提示回退和过预测裁剪。
- `src/vulnbooster/augmentation.py`
  - `CoTAugmenter` 和 `CWEAugmenter` 两套增强器。
  - 已接入锚点约束、非平凡变异过滤、漏洞机理分流。
- `src/vulnbooster/validation.py`
  - 基于 Tree-sitter 的语法过滤。
  - 对齐度、锚点命中、非平凡性、检测器置信度、质量重排等多重过滤。
- `src/vulnbooster/merge.py`
  - 合并原训练集与增强样本，并按 `idx` 去重。
- `src/vulnbooster/training.py`
  - 训练下游漏洞检测器。
  - 当前检测器 baseline 是 `CodeBERT` 二分类器。
  - 损失是 focal loss + label smoothing 的动态组合。

### 2.2 实验入口

- `src/vulnbooster/cli.py`
  - 已将清洗、静态切片、LLM 初筛、融合、行级标签构造、`line_slicer`/`codet5_slicer` 训练预测、增强、验证、合并、训练统一到 CLI。
- `scripts/run_small_model_aug_experiment.py`
  - 当前最关键的一键实验编排脚本。
  - 能串起采样、清洗、教师切片、行级标签、小模型切片器训练、baseline detector 训练、FN 切片、增强、验证、合并、重训和总结。

## 3. 配置与默认模型

`configs/full.toml` 当前默认配置为：

- 下游检测器：`microsoft/codebert-base`
- baseline 行级切片器：`microsoft/codebert-base`
- CodeT5 切片器：`Salesforce/codet5-small`
- Hugging Face 镜像：`https://hf-mirror.com`
- LLM 服务：`DeepSeek` 接口，代码中由 `VULNBOOSTER_API_KEY` 提供密钥

当前研究重点仍然是：

1. 保留 `CodeBERT` 作为稳定 baseline 检测器。
2. 把切片器作为主要创新位点。
3. 观察切片质量是否能向增强质量和最终检测收益传导。

## 4. 研究状态判断

### 4.1 已跑通并冻结的部分

- 教师切片链路已经稳定：
  - `Joern static slice -> LLM pre-filter -> LLM fusion refine -> refined_code`
- 基于教师切片的行级监督集构造已经落地。
- `CodeBERT` 行级分类切片器已经能作为 baseline 使用。
- 增强生成器已经从“能生成”推进到“能带来下游收益”。
- `v4` 机理感知增强已经接入主链路。

### 4.2 正在推进的新方向

- 迁移到 `CodeT5` 作为新的行级切片后端。
- 目标不是让 `CodeT5` 替换最终检测器，而是让它接管增强链路中的语义切片职责。
- 当前实现采用“行号序列预测”，而不是自由生成代码。
- `2026-07-10` 本轮新增两项 precision 导向机制：
  - `CodeT5` 多候选预测后重排，而不是只吃第一条 beam 结果。
  - `validation.py` 增加基于 prompt slice 质量的附加过滤，能够按切片宽度、与静态切片重合度做 precision 门控。

## 5. 目前可直接引用的阶段性结论

### 5.0 当前冻结口径

截至 `2026-07-10`，`v3` 与 `v4` 增强生成器视为冻结基线，详细结论见：

- `docs/frozen_v3_v4_baselines_2026-07-10.md`

从这个节点开始，后续主要优化对象不再是生成器主结构，而是：

1. `CodeT5` 切片器
2. 切片候选选择
3. 基于切片质量的筛选器

当前下一阶段目标是把 precision 继续推进到 `0.78 ~ 0.80`，同时尽量不破坏现有 recall / F1 / MCC 收益。

### 5.1 冻结版增强结果

基线检测器默认阈值测试结果：

- Precision: `0.6875`
- Recall: `0.8250`
- F1: `0.7500`
- MCC: `0.4593`

`v3` 生成器最强结果：

- Precision: `0.7556`
- Recall: `0.8500`
- F1: `0.8000`
- MCC: `0.5795`

`v4` 机理感知生成器当前最稳结果：

- Precision: `0.7333`
- Recall: `0.8250`
- F1: `0.7765`
- MCC: `0.5292`

### 5.2 CodeT5 首轮迁移结果

根据 `docs/codet5_first_run_report_2026-07-10.md`：

- CodeT5 切片器验证集：
  - Precision: `0.6732`
  - Recall: `0.4672`
  - F1: `0.5516`
- CodeT5 切片器测试集：
  - Precision: `0.7111`
  - Recall: `0.5386`
  - F1: `0.6130`

虽然切片层 recall 还偏保守，但首轮复用实验已经带来下游增益：

- Baseline detector：
  - Precision: `0.6875`
  - Recall: `0.8250`
  - F1: `0.7500`
  - MCC: `0.4593`
- CodeT5 slicer 增强后：
  - Precision: `0.7143`
  - Recall: `0.8750`
  - F1: `0.7865`
  - MCC: `0.5388`

说明当前判断是：

1. `CodeT5` 已成功接入增强主链路。
2. 它不是只改善切片中间指标，而是已对最终检测结果产生正向传导。

### 5.3 CodeT5 + V4 precision 定向实验现状

截至 `2026-07-10`，远端已完成一轮 `CodeT5 + v4(cwe) + 候选重排 + prompt-slice 质量门` 的完整实验重跑：

- 目录：`~/VulnBooster_runs/43990702/artifacts/experiments/codet5_v4_pre_balanced_43990702_rerun1`

这轮的关键现象不是模型训练失败，而是：

1. `CodeT5` 切片链路已经成功跑通。
2. 6 个 FN 样本都产生了非空切片。
3. 增强器共生成 `17` 条候选样本。
4. 但验证阶段 `17/17` 全部被 `low_prompt_slice_quality` 拒绝。

也就是说，当前主要矛盾不是 `CodeT5` 本身没法切，而是：

**prompt-slice 质量门过严，导致增强样本无法进入训练集。**

因此，下一步优先动作不是继续改模型结构，而是：

1. 放松 `min_prompt_slice_static_precision`
2. 放松 `min_prompt_slice_static_recall`
3. 放宽 `max_prompt_slice_ratio`

目标是先恢复“有增强样本可回灌”，再看 precision 能否继续上推。

### 5.4 rerun2 的最新阻塞点

截至 `2026-07-11`，放松 prompt-slice 质量门后的 `rerun2`：

- 目录：`~/VulnBooster_runs/43990702/artifacts/experiments/codet5_v4_pre_relaxed_43990702_rerun2`

已经成功跑过：

1. 教师切片
2. 行级标签构造
3. `CodeT5` 切片器训练与评估

其中 `CodeT5` 评估日志显示：

- Precision: `0.6982`
- Recall: `0.7445`
- F1: `0.7206`
- ExactMatch: `0.3625`
- EmptyRate: `0.0`

但该轮没有在增强阶段中断，而是在后续 `baseline detector` 训练保存 checkpoint 时失败。根因不是模型逻辑，而是：

**远端根分区 `/` 已满，`torch.save(optimizer state)` 写盘失败。**

因此当前新的默认处理原则是：

1. 远端优先清理 `uv` 缓存和失败实验目录。
2. 本地代码中所有训练器统一启用 `save_only_model=True`，减少 checkpoint 写盘压力。

## 6. 当前理解下的论文主线

最合理的论文主线是：

1. 用 `Joern + LLM` 构造高质量教师切片。
2. 将教师切片对齐成行级监督信号。
3. 训练低成本小模型切片器接管高成本语义切片职责。
4. 用该切片器服务于漏报样本增强生成。
5. 通过严格质量控制构造增强训练集。
6. 验证增强数据集对下游漏洞检测器的实际收益。

对应到当前代码，最重要的创新比较对象是：

- `CodeBERT line classifier slicer`
- `CodeT5 line-tag seq2seq slicer`

而不是先急着更换最终检测模型。

## 7. 运行环境记忆

### 7.1 本地

- 仓库根目录：`/mnt/d/Scientific/VulnBooster`
- 包管理与环境：已使用 `uv`
- 当前分支：`main`

### 7.2 远端服务器

- SSH：`lmpr@10.2.16.53`
- 已知信息：
  - 远端已有 `uv`
  - 缺少依赖时可自行安装
  - 需要使用镜像源

注意：

- 不在仓库文档中记录明文密码。
- 后续在服务器训练前，先保证本地仓库状态至少不落后于服务器，再同步代码过去。

## 8. 当前仓库注意事项

截至本次阅读，工作区不是干净状态，已有未提交修改，主要涉及：

- `configs/full.toml`
- `configs/smoke.toml`
- `pyproject.toml`
- `scripts/run_small_model_aug_experiment.py`
- `src/vulnbooster/codet5_slicer.py`
- `src/vulnbooster/config.py`
- `src/vulnbooster/doctor.py`
- `src/vulnbooster/env.py`
- `src/vulnbooster/line_slicer.py`
- `src/vulnbooster/llm.py`
- `src/vulnbooster/static_slice.py`
- `tests/test_core.py`
- 新文件：`scripts/summarize_experiment_outputs.py`
- 新文件：`uv.lock`

后续操作原则：

1. 不覆盖用户已有修改。
2. 任何新改动都先阅读上下文，再基于当前状态继续推进。
3. 与服务器同步时，本地应作为主参考版本，避免服务器代码领先本地。

## 9. 后续默认行动准则

后续如果继续推进本项目，优先顺序默认按下面执行：

1. 先更新本文件，记录新结论和新实验状态。
2. 再做代码修改、实验、服务器同步。
3. 每次新实验都尽量写入 `docs/`，保留输入配置、关键日志位置、核心指标和结论。

## 10. 当前可直接调的 precision 旋钮

这轮代码后，`CodeT5` 和筛选器新增了几组与 precision 直接相关的参数。

### 10.1 CodeT5 切片候选侧

位置：

- `configs/full.toml`
- `configs/smoke.toml`
- `scripts/run_small_model_aug_experiment.py`

关键参数：

- `codet5_slicer.candidate_count`
- `codet5_slicer.static_hint_window`
- `codet5_slicer.overpredict_function_ratio`
- `codet5_slicer.overpredict_static_ratio`
- `codet5_slicer.overpredict_static_margin`

当前逻辑：

1. 生成多条 beam 候选。
2. 对每条候选先做过预测裁剪。
3. 再根据静态提示重合度、切片紧凑性、连续性和密度重排选最优候选。

### 10.2 验证筛选侧

位置：

- `scripts/run_small_model_aug_experiment.py`
- `src/vulnbooster/validation.py`

新增参数：

- `--prompt-slice-min-static-precision`
- `--prompt-slice-min-static-recall`
- `--prompt-slice-max-ratio`

含义：

1. 如果 `line_slice` 相对原函数过宽，可直接拒绝该 seed 派生的增强样本。
2. 如果 `line_slice` 与静态切片重合度太低，可直接拒绝。
3. 这组参数更适合拿来冲 precision，而不是冲 recall。

### 10.3 当前推荐的放松区间

根据 `rerun1` 结果，当前建议下一轮默认从下列区间开始扫：

- `--prompt-slice-min-static-precision 0.15 ~ 0.25`
- `--prompt-slice-min-static-recall 0.20 ~ 0.35`
- `--prompt-slice-max-ratio 0.60 ~ 0.75`

原因：

1. `rerun1` 使用 `0.35 / 0.45 / 0.45` 时，17 条候选全部被拒。
2. 说明当前静态切片与 CodeT5 提示切片之间的偏差，比预想的大。
3. 下一轮应先保证增强样本能保留一批，再判断 precision / recall / F1 / MCC 的真实变化。
