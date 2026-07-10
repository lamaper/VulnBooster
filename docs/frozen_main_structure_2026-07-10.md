# 冻结版主结构与当前成果快照

## 1. 当前主结构的定位

截至 `2026-07-10`，项目主结构先冻结为：

`PrimeVul 数据清洗 -> Joern 静态切片 -> LLM 预筛 -> LLM 融合精炼 -> 教师切片对齐回原函数 -> 行级切片监督集 -> 行级小模型切片 -> 漏报样本增强生成 -> 数据质量过滤 -> 增强训练集回灌 -> 漏洞检测器重训与评估`

这里的“主结构冻结”含义是：

1. 不推翻现有增强主链路。
2. 当前增强生成器与质量门控作为稳定 baseline 保留。
3. 后续新工作优先以“并行新增后端”的方式接入，避免把已有增益混到一起。

## 2. 当前各模块实际使用的技术

### 2.1 数据与清洗

1. 数据集：`PrimeVul`
2. 清洗入口：`src/vulnbooster/cleaning.py`
3. 实验编排脚本：`scripts/run_small_model_aug_experiment.py`

### 2.2 教师切片构造

当前教师切片不是单一来源，而是三段式组合：

1. `Joern` 静态切片
   - 代码：`src/vulnbooster/static_slice.py`
2. `DeepSeek-Coder` 预筛切片
   - 代码：`src/vulnbooster/llm.py`
3. `LLMFusionRefiner` 融合精炼
   - 代码：`src/vulnbooster/llm.py`

最终教师切片主监督字段是：

1. `refined_code`
2. 回退时也可能使用 `line_slice / llm_slice / static_slice`

### 2.3 行级切片监督构造

1. 对齐逻辑：`src/vulnbooster/line_slicer.py::align_teacher_slice_to_function`
2. 数据集构造：`src/vulnbooster/line_slicer.py::build_line_slice_alignment_dataset`

产物核心字段：

1. `line_labels`
2. `matched_teacher_line_numbers`
3. `static_line_numbers`
4. `teacher_slice`

### 2.4 当前切片小模型 baseline

当前用于替代部分语义切片能力的小模型 baseline 不是 CodeT5，而是：

1. 模型：`microsoft/codebert-base`
2. 任务：行级二分类
3. 代码：`src/vulnbooster/line_slicer.py`

这一步的作用是：

1. 从原函数中预测漏洞相关行。
2. 给验证集漏报样本构造 `line_slice`。
3. 将 `line_slice` 作为增强生成提示的高密度语义上下文。

### 2.5 当前漏洞检测 baseline

当前下游漏洞检测器 baseline 为：

1. 模型：`microsoft/codebert-base`
2. 训练代码：`src/vulnbooster/training.py`
3. 目标字段：原函数 `func`

这意味着当前研究重点仍然放在“增强数据是否有效”，而不是直接换最终检测器。

### 2.6 当前增强生成器

代码：`src/vulnbooster/augmentation.py`

当前已接入两层关键改进：

1. 数据质量层
   - 锚点约束
   - 非平凡变异过滤
   - 语法修复
   - 结构相似度过滤
2. 漏洞机理感知层
   - `memory_bounds`
   - `null_deref`
   - `integer_size`
   - `resource_lifecycle`
   - `input_validation`
   - `generic_contextual`

## 3. 当前冻结版实验结论

### 3.1 基线检测器

测试集默认阈值结果：

1. Precision: `0.6875`
2. Recall: `0.8250`
3. F1: `0.7500`
4. MCC: `0.4593`

### 3.2 `v3` 生成器当前最强结果

实验目录：`stage_best_det055_top1_q035`

1. Precision: `0.7556`
2. Recall: `0.8500`
3. F1: `0.8000`
4. MCC: `0.5795`

相对基线默认阈值：

1. Precision `+0.0681`
2. Recall `+0.0250`
3. F1 `+0.0500`
4. MCC `+0.1203`

### 3.3 `v4` 机理感知生成器当前最稳结果

默认阈值下：

1. Precision: `0.7333`
2. Recall: `0.8250`
3. F1: `0.7765`
4. MCC: `0.5292`

相对基线默认阈值：

1. Precision `+0.0458`
2. Recall `+0.0000`
3. F1 `+0.0265`
4. MCC `+0.0699`

## 4. 当前冻结版的研究边界

截至当前，项目还没有做下面两件事：

1. 还没有把 `CodeT5 / CodeT5+` 作为主切片器接入正式实验链路。
2. 还没有训练“由大模型蒸馏得到的小模型切片器”。

因此，接下来新阶段的创新重点应该明确写成：

1. 设计并接入 `CodeT5` 行级切片器。
2. 对比 `CodeBERT` 行级分类切片器与 `CodeT5` 行级序列切片器。
3. 分析新切片器对增强数据质量和下游漏洞检测效果的影响。

## 5. 接下来冻结后允许改动的方向

为了不破坏当前主结构，后续改动优先遵循三条原则：

1. 保留当前 `line_slicer` 作为稳定 baseline。
2. 新增 `codet5_slicer` 并行后端，而不是重写旧模块。
3. 所有实验结果都必须明确区分：
   - `生成器版本`
   - `切片器后端`
   - `是否阈值校准`
