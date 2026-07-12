# 教师切片三阶段结果总结

更新时间：2026-07-12

## 1. Joern 静态切片结果

对应实现：`src/vulnbooster/static_slice.py`

典型输出：`teacher/{split}/{split}_static.jsonl`

核心字段：

- `code_lines` / `raw_lines`：Joern 静态切片得到的候选代码行。
- `static_slice`：后续融合阶段规范化后的静态切片文本。
- `fromIdx`、`target` 等：Joern 切片过程中的结构定位信息。

定位：

静态切片是第一层结构先验。它主要依赖 Joern 的 CPG、数据依赖和控制依赖关系，从原函数中抽出和目标变量、敏感调用、漏洞相关语句存在结构关联的代码区域。

优点：

- 确定性强，可复现，不依赖 LLM 输出稳定性。
- 能提供较好的结构锚点，尤其适合作为后续对齐、提示词和行号弱监督的依据。
- 对变量传播、控制条件、调用上下文等结构关系比较敏感，召回潜在相关语句时有价值。

局限：

- 语义判断弱，容易把只是结构相关但漏洞机制无关的上下文也带进来。
- 对 Joern 解析质量、语言特性、切片脚本规则较敏感。
- 结果可能偏噪声或偏碎片化，不能直接当作最终训练目标。

当前结论：

静态切片更适合作为结构提示和弱监督，而不是硬过滤标准。近期 CodeT5 增强实验里，过度依赖 prompt-slice / static overlap 作为硬门槛会杀掉大量样本，因此它应该用于提供 hint、anchor、fallback，而不是单独决定样本是否保留。

## 2. LLM 初次切片结果

对应实现：`src/vulnbooster/llm.py::LLMPreFilter`

典型输出：`teacher/{split}/{split}_llm.jsonl`

核心字段：

- `llm_slice`：LLM 从原始函数中初步筛出的漏洞相关代码片段。

定位：

LLM 初筛是第二层语义先验。它从完整函数出发，根据漏洞语义、CWE 机制、危险调用、边界检查、资源释放、权限/状态检查等语义线索，判断哪些代码行最可能与漏洞形成有关。

实现上，LLM 原始输出不会被直接信任，而是通过 `project_slice_onto_original()` 尽量投影回原始函数，以降低改写、幻觉和格式漂移带来的影响。

优点：

- 语义密度通常高于静态切片，能主动过滤一些结构相关但漏洞无关的噪声。
- 对漏洞机理、危险模式、检查缺失、上下文前后因果关系有更强理解能力。
- 能补足纯静态分析不容易表达的语义关系。

局限：

- 输出可能不稳定，存在漏行、改写、补全、幻觉或格式不一致。
- 如果函数较长或漏洞上下文隐蔽，初筛可能漏掉关键条件或依赖行。
- 成本和速度受 LLM API 影响。

当前结论：

`llm_slice` 是有用的语义候选，但还不够稳定，不适合直接作为最终教师标签。它适合作为融合阶段的语义输入，并可在 `refined_code` 缺失时作为回退教师。

## 3. LLM 融合精炼结果

对应实现：`src/vulnbooster/llm.py::LLMFusionRefiner`

典型输出：`teacher/{split}/{split}_refined.jsonl`

核心字段：

- `refined_code`：融合静态切片和 LLM 初筛后的最终教师切片。
- `static_slice`：融合输入之一，提供结构召回。
- `llm_slice`：融合输入之一，提供语义筛选。

定位：

LLM 融合精炼是当前教师生成链路的最终阶段。它把 `[Static Slice]` 和 `[Initial Screening]` 一起交给 LLM，让模型在结构召回和语义判断之间做平衡，生成更适合训练小切片器的教师切片。

回退逻辑：

- 有 `static_slice` 且有 `llm_slice`：LLM 执行融合精炼，再投影回原函数。
- 无 `static_slice` 但有 `llm_slice`：使用 `llm_slice` 投影结果作为 `refined_code`。
- 有 `static_slice` 但无 `llm_slice`：使用 `static_slice` 投影结果作为 `refined_code`。
- 两者都缺失：回退为原始函数 `func`。

优点：

- 综合了静态切片的结构召回和 LLM 初筛的语义精度。
- 比单独 `static_slice` 更少噪声，比单独 `llm_slice` 更不容易漏掉结构依赖。
- 是当前最适合作为小模型行级切片器监督信号的字段。

局限：

- 仍然会继承静态切片和 LLM 初筛的错误。
- 如果 LLM 精炼输出和原函数不完全一致，对齐阶段可能只能部分匹配。
- 教师质量强依赖投影、清洗、fallback 和后续行级对齐逻辑。

当前结论：

`refined_code` 是当前教师切片主目标。后续 `line_slicer.py` 会优先读取 `refined_code`，将其对齐回原始函数，得到 `matched_teacher_line_numbers` 和 `line_labels`，再训练小模型行级切片器。

## 4. 三者关系

整体关系可以概括为：

```text
原始函数 func
  -> Joern 静态切片
  -> static_slice：结构相关候选区域
  -> LLM 初次切片
  -> llm_slice：语义相关候选区域
  -> LLM 融合精炼
  -> refined_code：最终教师切片
  -> line_slicer.py 对齐原函数
  -> line_labels / teacher_slice
  -> 训练 CodeT5 行级切片器
```

字段优先级：

```text
refined_code > line_slice > llm_slice > static_slice > func
```

工程判断：

- `static_slice`：更像结构先验，适合做 hint、anchor、fallback。
- `llm_slice`：更像语义先验，适合做候选教师和融合输入。
- `refined_code`：当前主教师目标，最适合训练小模型切片器。

## 5. 对当前 CodeT5 实验的意义

当前 CodeT5 切片迁移不是让小模型直接学习 Joern 的静态结果，也不是只模仿 LLM 初筛，而是学习 `refined_code` 对齐回原函数后的行级标签。

近期实验表明：

- CodeT5 已能学习到一定的漏洞相关行选择能力。
- 过严的 prompt-slice / static overlap 质量门控会导致增强样本被大量过滤。
- 静态切片适合作为辅助信号，但不适合作为硬保留条件。
- 较合理的方向是保留 `refined_code` 作为教师主监督，同时让静态切片参与提示、fallback 和软质量评估。

