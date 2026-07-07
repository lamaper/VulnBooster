# 迁移映射

这份映射用于帮助后续阅读者理解：

- `code/` 里的旧脚本现在在新结构里对应哪里；
- 后续如果替换方法，应该优先改哪个模块。

## 旧脚本到新结构

| 旧脚本 | 新模块 | 说明 |
| --- | --- | --- |
| `code/clean_dataset.py` | `src/vulnbooster/cleaning.py` | 数据清洗 |
| `code/generate_cpg.py` | `src/vulnbooster/static_slice.py` | Joern 切片调度 |
| `slice/slice.sc` | `slice/slice.sc` | Joern Scala 切片脚本，原样保留 |
| `code/llm_pre_filter.py` | `src/vulnbooster/llm.py` 中 `LLMPreFilter` | LLM 初筛 |
| `code/llm_fusion_refine.py` | `src/vulnbooster/llm.py` 中 `LLMFusionRefiner` | 双路融合 |
| `code/cwe_spider.py` | `src/vulnbooster/knowledge.py` | CWE 知识抓取与缓存 |
| `code/cot_enhance.py` | `src/vulnbooster/augmentation.py` 中 `CoTAugmenter` | CoT 增强 |
| `code/cwe_enhance.py` | `src/vulnbooster/augmentation.py` 中 `CWEAugmenter` | CWE 增强 |
| `code/tree_sitter_val.py` | `src/vulnbooster/validation.py` | 语法过滤 |
| `code/merge_dataset.py` | `src/vulnbooster/merge.py` | 数据集合并 |
| `code/finetune_lambda_miu.py` | `src/vulnbooster/training.py` | 训练与 FN 提取 |

## 后续扩展优先改哪里

### 1. 想把 LLM 切片替换成小模型切片

优先改：

- `src/vulnbooster/llm.py`
- 或新增 `src/vulnbooster/small_model_slice.py`

建议做法：

- 先保留 `JoernSlicer`
- 将当前 `LLMPreFilter` 抽象替换为 `SmallModelSlicer`
- 保持下游输出字段仍然叫 `llm_slice` 或升级为统一的 `semantic_slice`

### 2. 想换下游检测模型

优先改：

- `src/vulnbooster/training.py`
- `configs/*.toml` 中的 `training.model_name`

### 3. 想换增强策略

优先改：

- `src/vulnbooster/augmentation.py`
- `src/vulnbooster/knowledge.py`

### 4. 想增加实验配置

优先改：

- `configs/*.toml`
- `src/vulnbooster/config.py`
- `src/vulnbooster/cli.py`
