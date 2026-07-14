# 近几天项目进展汇报

汇报日期：2026-07-14

项目：基于数据增强的源代码漏洞检测

## 1. 总体进展概览

这几天的工作重点，是在已有 `V3/V4` 增强链路已经有效的基础上，把后续主攻方向切换到 `CodeT5` 行级切片器和筛选器优化。

我们没有推翻原来的增强生成器，而是先冻结当前表现较好的 `V3/V4`，再把实验重心放到下面三件事：

1. 将教师切片链路系统化整理为 `Joern 静态切片 -> LLM 初筛 -> LLM 融合精炼 -> refined_code`。
2. 将小模型切片器从 `CodeBERT 行级二分类` 迁移到 `CodeT5 行号序列生成`。
3. 基于 `CodeT5` 切片结果继续改进增强样本筛选器，尝试把最终漏洞检测 precision 往 `0.78 ~ 0.80` 推进。

截至目前，主结论是：

1. `V3/V4` 增强生成器已具备稳定正收益，可以作为冻结基线。
2. `CodeT5` 已经成功接入增强闭环，并在首轮复用实验中带来最终检测收益。
3. 后续 precision 未继续上冲的主要瓶颈，不是 `CodeT5` 完全不能切，而是增强样本筛选门控过严或过窄，导致样本保留数量不足。
4. 单纯提高 detector 置信度和质量分数阈值，不能稳定提升 precision，反而容易把增强样本压到 `0 ~ 1` 条。

## 2. 当前完整技术路线

当前项目主链路已经固定为：

```text
PrimeVul 数据清洗
  -> Joern 静态切片
  -> LLM 语义初筛
  -> LLM 融合精炼得到教师切片 refined_code
  -> 将 refined_code 对齐回原函数，构造成行级标签
  -> 训练小模型行级切片器
  -> 用切片器对 baseline 漏报样本预测 line_slice
  -> 基于 line_slice、CWE 知识和漏洞机理生成增强样本
  -> 语法 / 对齐 / 锚点 / 非平凡性 / detector 置信度过滤
  -> 合并增强训练集
  -> 重训漏洞检测器
  -> 阈值校准与最终评估
```

这条路线的核心思想是：

1. 用 `Joern + LLM` 构造高质量教师切片。
2. 用教师切片训练低成本小模型切片器。
3. 让小模型切片器服务于漏报样本增强。
4. 通过增强数据改善下游漏洞检测器。

## 3. 教师切片三阶段总结

这几天我们专门整理了教师切片三阶段，并形成文档：

- `docs/teacher_slice_stage_summary.md`

### 3.1 Joern 静态切片

对应字段：`static_slice`

作用：

- 提供结构先验。
- 利用 CPG、数据依赖、控制依赖找出和漏洞相关变量、调用、条件分支存在结构关系的代码行。
- 后续作为 `hint / anchor / fallback` 使用。

优点：

- 确定性强，可复现。
- 能提供行号锚点。
- 对变量传播、控制条件、危险调用上下文比较敏感。

问题：

- 语义理解弱。
- 容易包含结构相关但漏洞机理无关的噪声。
- 不适合作为硬过滤标准。

### 3.2 LLM 初次切片

对应字段：`llm_slice`

作用：

- 从完整函数中筛出语义上更可能与漏洞有关的代码区域。
- 弥补静态切片只看结构依赖、不理解漏洞机理的问题。

具体做法：

- 使用 `LLMPreFilter` 对原函数做漏洞相关区域初筛。
- LLM 输出后，不直接信任生成文本，而是用 `project_slice_onto_original()` 投影回原函数，降低改写和幻觉。

优点：

- 能关注漏洞机理、危险 API、缺失检查、边界条件、资源释放等语义因素。
- 通常比纯静态切片噪声更少。

问题：

- 输出不稳定，可能漏行、改写、格式漂移。
- 不适合直接作为最终教师标签。

### 3.3 LLM 融合精炼

对应字段：`refined_code`

作用：

- 融合 `static_slice` 的结构召回和 `llm_slice` 的语义精度。
- 作为训练小模型切片器的主监督信号。

具体做法：

- 使用 `LLMFusionRefiner` 同时读取静态切片和 LLM 初筛结果。
- 如果两者都有，则让 LLM 融合精炼。
- 如果其中一个缺失，则回退到另一个。
- 如果都缺失，则回退到原始函数。
- 最终再投影回原函数，用于行级标签构造。

当前判断：

```text
static_slice 是结构候选
llm_slice 是语义候选
refined_code 是最终教师目标
```

## 4. 冻结 V3/V4 基线

我们将 `V3/V4` 增强生成器作为当前冻结基线，记录在：

- `docs/frozen_v3_v4_baselines_2026-07-10.md`

冻结原因：

1. V3/V4 已经证明增强样本能够提升最终漏洞检测器。
2. 当前不再优先大改生成器 prompt 主结构。
3. 后续主要优化切片器和筛选器。

### 4.1 原始 baseline 结果

| 方法 | Precision | Recall | F1 | MCC |
|---|---:|---:|---:|---:|
| Baseline detector | `0.6875` | `0.8250` | `0.7500` | `0.4593` |

### 4.2 V3 当前最强结果

| 方法 | Precision | Recall | F1 | MCC |
|---|---:|---:|---:|---:|
| V3 增强 | `0.7556` | `0.8500` | `0.8000` | `0.5795` |

结论：

- V3 证明少量高质量增强样本可以带来明显收益。
- 相比 baseline，precision、F1、MCC 均有提升。

### 4.3 V4 当前最稳结果

| 方法 | Precision | Recall | F1 | MCC |
|---|---:|---:|---:|---:|
| V4 机理感知增强 | `0.7333` | `0.8250` | `0.7765` | `0.5292` |

结论：

- V4 在默认阈值下更稳。
- V4 保持 recall 不下降，同时提升 precision 和 MCC。
- 因此后续 `CodeT5` 实验主要挂接在冻结后的 V4/CWE 生成器上。

## 5. CodeT5 行级切片器迁移

迁移文档与首轮报告：

- `docs/codet5_line_slicer_migration_plan.md`
- `docs/codet5_first_run_report_2026-07-10.md`

### 5.1 为什么迁移到 CodeT5

原来的 `CodeBERT line_slicer` 是行级二分类：

```text
输入：函数中的某一行 + 上下文
输出：该行是否属于漏洞相关切片
```

这类方式的问题是：

- 行之间的组合关系建模较弱。
- 容易把切片看成独立行集合，而不是一个有结构的代码片段。

我们迁移到 `CodeT5` 后，改为行号序列生成：

```text
输入：带行号的完整函数 + 静态切片提示
输出：L003 L004 L007 ...
```

这样做有两个好处：

1. 不让模型自由生成代码，减少幻觉。
2. 让模型学习“哪些行共同组成漏洞相关切片”。

### 5.2 具体实现内容

新增和修改的关键模块：

- `src/vulnbooster/codet5_slicer.py`
- `src/vulnbooster/config.py`
- `src/vulnbooster/cli.py`
- `scripts/run_small_model_aug_experiment.py`

关键机制：

1. 将原函数转换为带行号输入，例如 `L001: int foo(...)`。
2. 将静态切片行号作为提示输入模型。
3. 模型输出行号序列。
4. 后处理阶段只保留合法行号。
5. 对行号去重、排序、裁剪。
6. 回拼得到 `line_slice`。
7. 对 baseline 漏报样本生成切片，再进入增强生成器。

### 5.3 工程兼容修复

为了让远端训练稳定跑通，我们做了几类工程修复：

1. 固定训练依赖版本：
   - `transformers==4.44.2`
   - `tokenizers==0.19.1`
2. 修复 `Seq2SeqTrainer` 参数兼容问题：
   - 将不兼容的 `processing_class=` 适配为 `tokenizer=`。
3. 修复 tokenizer 加载问题：
   - 检测器打分时使用基础模型 tokenizer，模型权重仍从实验目录加载。
4. 修复 checkpoint 磁盘占用过大：
   - 在 `training.py`、`line_slicer.py`、`codet5_slicer.py` 中启用 `save_only_model=True`。
   - 避免反复保存 optimizer state 导致远端根分区写满。
5. 增加实验续跑脚本：
   - `scripts/resume_experiment_from_step6.py`
   - 用于复用前面已经完成的 teacher / slicer 资产，从 detector 阶段继续跑。

相关提交：

- `43990702 Freeze v3 v4 baselines and tighten CodeT5 slicing`
- `962e4f9d Pin CodeT5 training deps to compatible versions`
- `58d947ae Reduce checkpoint disk usage during training`
- `0d63ae27 Add experiment resume helper from detector stage`
- `fe3c0d82 Load local env in experiment resume helper`

## 6. CodeT5 首轮结果

首轮复用实验中，CodeT5 已经成功带来下游收益。

### 6.1 CodeT5 切片器自身指标

| Split | Precision | Recall | F1 | Exact Match |
|---|---:|---:|---:|---:|
| Valid | `0.6732` | `0.4672` | `0.5516` | `0.3000` |
| Test | `0.7111` | `0.5386` | `0.6130` | `0.2625` |

观察：

- CodeT5 能稳定输出非空切片。
- 初版 CodeT5 比较保守，precision 尚可，但 recall 偏低。

### 6.2 对最终漏洞检测器的影响

| 方法 | Precision | Recall | F1 | MCC |
|---|---:|---:|---:|---:|
| Baseline detector | `0.6875` | `0.8250` | `0.7500` | `0.4593` |
| CodeT5 切片增强 | `0.7143` | `0.8750` | `0.7865` | `0.5388` |
| 增益 | `+0.0268` | `+0.0500` | `+0.0365` | `+0.0795` |

结论：

- CodeT5 不只是中间切片指标有效，而是能把收益传导到最终漏洞检测器。
- 这证明“用低成本小模型接管 LLM 语义切片职责”是可行的。

## 7. Precision 定向优化：我们具体怎么改

为了冲击 precision `0.78 ~ 0.80`，这几天主要从两个方向改：

### 7.1 CodeT5 候选生成与重排

原始做法：

```text
CodeT5 beam search 输出第一条候选
  -> 直接作为 line_slice
```

改进后：

```text
CodeT5 生成多条候选
  -> 过滤非法行号
  -> 过预测裁剪
  -> 计算与静态切片的重合度
  -> 计算切片紧凑性、连续性、密度
  -> 选择综合得分最高的候选
```

新增或调优的参数包括：

- `codet5_slicer.candidate_count`
- `codet5_slicer.static_hint_window`
- `codet5_slicer.overpredict_function_ratio`
- `codet5_slicer.overpredict_static_ratio`
- `codet5_slicer.overpredict_static_margin`

设计意图：

- 防止 CodeT5 输出过宽切片。
- 尽量选择更靠近静态结构先验的候选。
- 在不牺牲太多 recall 的情况下提升增强样本质量。

### 7.2 validation.py 增加切片质量门控

原始验证流程主要包括：

- Tree-sitter 语法检查
- 与 seed 的对齐度
- 锚点命中
- 非平凡性
- detector 置信度
- composite quality score

这几天新增了 prompt-slice 质量门：

- `--prompt-slice-min-static-precision`
- `--prompt-slice-min-static-recall`
- `--prompt-slice-max-ratio`

它们分别控制：

1. `line_slice` 与静态切片的 precision。
2. `line_slice` 与静态切片的 recall。
3. `line_slice` 相对原函数是否过宽。

最初设想是：

```text
如果 CodeT5 预测切片太宽，或者和静态切片几乎不重合，
则认为该增强 seed 不可靠，拒绝它生成的增强样本。
```

后续实验发现，这个方向有价值，但不能作为过硬门槛，否则会误杀。

## 8. 远端实验与环境处理

远端服务器：

- `lmpr@10.2.16.53`

主要实验目录：

- `~/VulnBooster_runs/43990702`
- `~/VulnBooster_runs/43990702/artifacts/experiments`

这几天处理过的远端问题：

1. 使用 `uv` 管理依赖。
2. 修复 `transformers/tokenizers` 版本不兼容。
3. 清理远端磁盘：
   - 清理 `~/.cache/uv`
   - 清理失败实验目录
   - 释放约 `17G`
4. 训练器启用 `save_only_model=True`，避免 optimizer checkpoint 写爆磁盘。
5. 使用本地 git 作为主版本，先本地提交，再同步到服务器运行，保证本地不落后于服务器。

## 9. rerun2 到 rerun7 实验结果

### 9.1 汇总表

| 实验 | 目的 | Generated | Kept | Aug Precision | Aug Recall | Aug F1 | Aug MCC | 结论 |
|---|---|---:|---:|---:|---:|---:|---:|---|
| rerun2 relaxed | 放松 prompt-slice 门后完整跑 | `12` | `0` | `0.6379` | `0.9250` | `0.7551` | `0.4479` | 仍被 `low_prompt_slice_quality` 全杀 |
| rerun3 no_slice_gate | 移除 prompt-slice 门 | `11` | `4` | `0.6604` | `0.8750` | `0.7527` | `0.4494` | 证明门控过严是主因 |
| rerun3 open_slice_gate | 打开 prompt-slice 门但保留流程 | `8` | `3` | `0.6800` | `0.8500` | `0.7556` | `0.4648` | 当前 CodeT5+V4 最高 absolute precision |
| rerun4 strict_quality | 提高 detector 与 quality 阈值 | `21` | `0` | `0.6379` | `0.9250` | `0.7551` | `0.4479` | 过严，`low_detector_confidence=19` |
| rerun5 mid_quality | 中等质量门，`detector=0.50, quality=0.75` | `8` | `3` | `0.6379` | `0.9250` | `0.7551` | `0.4479` | 有正收益，但 precision 不如 rerun3 open |
| rerun6 mid_quality_077 | `detector=0.50, quality=0.77` | `9` | `3` | `0.6491` | `0.9250` | `0.7629` | `0.4695` | F1/MCC 较好，但 precision 仍低于 rerun3 open |
| rerun7 precision_052_q077_g4 | `detector=0.52, quality=0.77, generate_k=4` | `18` | `1` | `0.6429` | `0.9000` | `0.7500` | `0.4364` | 门控太窄，样本只剩 1 条 |

### 9.2 关键实验解释

#### rerun2

做法：

- 在 rerun1 后放松 prompt-slice 质量门。
- 继续完整跑 CodeT5 切片、增强生成、验证、合并、重训。

结果：

- CodeT5 本身评估明显提升：
  - Precision `0.6982`
  - Recall `0.7445`
  - F1 `0.7206`
  - Exact Match `0.3625`
- 但增强阶段 `12/12` 仍被 `low_prompt_slice_quality` 拒绝。

结论：

- 模型能切，但验证门仍然太硬。
- 静态切片和 CodeT5 切片不能直接用高重合度当硬标准。

#### rerun3

做法：

- 跑两组：
  - `no_slice_gate`：去掉 prompt-slice 质量门。
  - `open_slice_gate`：打开 prompt-slice 门，阈值放到很宽。

结果：

- `no_slice_gate`：
  - 保留 `4` 条增强样本。
  - precision 从 baseline `0.6066` 提到 `0.6604`。
  - F1 从 `0.7327` 提到 `0.7527`。
  - MCC 从 `0.3819` 提到 `0.4494`。
- `open_slice_gate`：
  - 保留 `3` 条增强样本。
  - augmented precision 达到 `0.6800`。
  - 当前是 CodeT5 + V4 这批实验中的最高 absolute precision。

结论：

- prompt-slice 质量门确实是之前 0 样本保留的主因。
- CodeT5 不是完全不行，而是样本被过滤器杀掉了。

#### rerun4

做法：

- 尝试强行冲 precision：
  - `detector_min_prob=0.55`
  - `quality_score=0.79`

结果：

- 生成 `21` 条。
- 保留 `0` 条。
- 主要拒绝原因：
  - `low_detector_confidence=19`
  - `low_quality_score=2`

结论：

- detector 与 quality 双门控不能直接拉太高。
- 这种做法会导致增强训练集实际没有新增样本。

#### rerun5

做法：

- 回到中等质量门：
  - `detector_min_prob=0.50`
  - `quality_score=0.75`

结果：

- 生成 `8` 条。
- 保留 `3` 条。
- augmented:
  - Precision `0.6379`
  - Recall `0.9250`
  - F1 `0.7551`
  - MCC `0.4479`

结论：

- 中等门控能恢复样本保留和正收益。
- 但 precision 不够高。

#### rerun6

做法：

- 小幅提高质量门：
  - `detector_min_prob=0.50`
  - `quality_score=0.77`

结果：

- 生成 `9` 条。
- 保留 `3` 条。
- augmented:
  - Precision `0.6491`
  - Recall `0.9250`
  - F1 `0.7629`
  - MCC `0.4695`
- 相对该轮 baseline：
  - Precision `+0.0459`
  - F1 `+0.0250`
  - MCC `+0.0723`

结论：

- `quality_score=0.77` 比 `0.75` 在 F1/MCC 上更好。
- 但 precision 仍没超过 rerun3 open 的 `0.6800`。

#### rerun7

做法：

- 继续偏 precision：
  - `detector_min_prob=0.52`
  - `quality_score=0.77`
  - `generate_k=4`
  - `max_per_seed=1`

设计意图：

- 让每个 FN seed 多生成候选。
- 再由 detector 和 quality rerank 选最高质量样本。

结果：

- 生成 `18` 条。
- 只保留 `1` 条。
- augmented precision `0.6429`，低于 baseline `0.6604`。
- 主要拒绝原因：
  - `low_detector_confidence=11`
  - `low_quality_score=3`
  - `over_seed_budget=3`

结论：

- 单纯增加 `generate_k` 没有解决问题。
- 当 detector/quality 门控过窄时，候选再多也会被杀掉。
- 下一步不应继续简单提高阈值。

## 10. 目前取得的成果

### 10.1 科研结论层面

1. 已证明增强数据对漏洞检测器有效：
   - V3 最强结果 precision `0.7556`、F1 `0.8000`、MCC `0.5795`。
   - V4 稳态结果 precision `0.7333`、F1 `0.7765`、MCC `0.5292`。
2. 已证明 `CodeT5` 切片器能接入增强链路：
   - 首轮 CodeT5 增强后 precision 从 `0.6875` 到 `0.7143`。
   - F1 从 `0.7500` 到 `0.7865`。
   - MCC 从 `0.4593` 到 `0.5388`。
3. 已明确当前 CodeT5 + V4 的主要瓶颈：
   - 不是模型完全不能切。
   - 不是增强器完全不能生成。
   - 而是筛选策略对样本保留数量和样本质量之间的平衡还不够好。
4. 已验证“静态切片重合度”更适合做软信号：
   - 不能作为过硬门槛。
   - 过硬会导致 `low_prompt_slice_quality` 大量误杀。

### 10.2 工程实现层面

1. 完成 CodeT5 行级切片器模块。
2. 完成 CodeT5 与 CLI / 配置 / 一键实验脚本集成。
3. 完成多候选生成、候选裁剪、候选重排。
4. 完成 prompt-slice 质量门控。
5. 完成实验续跑脚本，节省重复跑 teacher / slicer 的成本。
6. 修复远端依赖版本、Trainer 兼容、tokenizer 加载、checkpoint 写盘等问题。
7. 建立 `docs/working_memory.md` 长期记忆，避免上下文丢失。
8. 补充教师切片三阶段总结文档。

### 10.3 实验管理层面

1. 本地使用 git 管理，保证本地版本不落后于服务器。
2. 远端复用已有数据集和切片资产，减少重复计算。
3. 每轮实验保留 summary、日志、参数和结论。
4. 对失败实验也记录原因，例如：
   - `low_prompt_slice_quality`
   - `low_detector_confidence`
   - `low_quality_score`
   - 磁盘写满
   - 依赖不兼容

## 11. 当前问题与下一步计划

### 11.1 当前问题

1. CodeT5 首轮切片 recall 仍偏保守。
2. prompt-slice 静态重合度不能作为强硬过滤条件。
3. detector/quality 阈值过高会导致增强样本保留数过低。
4. 当前 CodeT5 + V4 的 best absolute precision 仍为 `0.6800`，没有超过冻结 V3/V4。

### 11.2 下一步建议

下一轮不建议继续简单提高阈值，而建议改筛选和训练策略。

建议方向一：离线分桶选择增强样本

- 先生成更多候选。
- 不立即用单一阈值过滤。
- 按 detector 概率、quality score、seed 覆盖、CWE 类型分桶。
- 每个桶中选少量高质量样本，避免只留下 0 或 1 条。

建议方向二：增强样本加权训练

- 不只控制“保留 / 丢弃”。
- 对高质量增强样本赋予更高训练权重。
- 对边界样本赋予较低权重。
- 避免少量增强样本对 detector 训练造成随机扰动。

建议方向三：优化 CodeT5 切片 recall

- 扩大静态 hint window。
- 对预测行加入邻接行扩展。
- 对低 recall 样本引入静态 fallback。
- 让 CodeT5 学到更完整的漏洞上下文，而不是只抓最核心几行。

建议方向四：筛选器从硬规则转为排序器

当前硬阈值容易出现两种极端：

```text
太松 -> 保留样本质量不稳
太严 -> 保留样本过少
```

更稳的方向是：

```text
先尽量生成候选
  -> 计算 detector_prob / quality_score / anchor_hit / novelty / slice_quality
  -> 排序
  -> 按 seed 或 CWE 做配额选择
```

## 12. 今天汇报可以强调的结论

可以重点讲四句话：

1. 我们已经把项目从“增强样本能不能生成”推进到“增强样本如何稳定提升检测器”的阶段。
2. V3/V4 已经冻结为有效基线，其中 V3 precision 达到 `0.7556`、F1 达到 `0.8000`。
3. CodeT5 行级切片器已经接入完整增强闭环，首轮带来 precision、recall、F1、MCC 全面提升。
4. 最近几轮 rerun 证明，当前瓶颈主要在增强样本筛选策略，不是模型完全无效；下一步要从硬阈值过滤转向排序选择和加权训练。

## 13. 文件与实验索引

关键文档：

- `docs/working_memory.md`
- `docs/teacher_slice_stage_summary.md`
- `docs/frozen_v3_v4_baselines_2026-07-10.md`
- `docs/codet5_line_slicer_migration_plan.md`
- `docs/codet5_first_run_report_2026-07-10.md`

关键代码：

- `src/vulnbooster/static_slice.py`
- `src/vulnbooster/llm.py`
- `src/vulnbooster/line_slicer.py`
- `src/vulnbooster/codet5_slicer.py`
- `src/vulnbooster/augmentation.py`
- `src/vulnbooster/validation.py`
- `src/vulnbooster/training.py`
- `scripts/run_small_model_aug_experiment.py`
- `scripts/resume_experiment_from_step6.py`

关键远端实验：

- `~/VulnBooster_runs/43990702/artifacts/experiments/codet5_v4_pre_no_slice_gate_43990702_rerun3`
- `~/VulnBooster_runs/43990702/artifacts/experiments/codet5_v4_pre_open_slice_gate_43990702_rerun3`
- `~/VulnBooster_runs/43990702/artifacts/experiments/codet5_v4_pre_mid_quality_43990702_rerun5`
- `~/VulnBooster_runs/43990702/artifacts/experiments/codet5_v4_pre_mid_quality_077_43990702_rerun6`
- `~/VulnBooster_runs/43990702/artifacts/experiments/codet5_v4_pre_precision_052_q077_g4_43990702_rerun7`

