# 更偏跨域对齐的增强筛选方案

更新时间：2026-04-03

## 1. 设计动机

`reveal_aug_v2` 的结果说明：

- 大规模增强可以显著提升训练内验证表现
- 但不能保证跨域 `devign` 泛化变好
- 仅依赖“与源域不过分偏离”的过滤策略，会让增强样本继续围绕 `reveal` 分布打转

因此，下一版筛选的核心目标应从：

- “像不像源域漏洞代码”

调整为：

- “既不要脱离源域漏洞机制，又要更接近目标域风格分布”

## 2. 新筛选原则

下一版建议使用三段式筛选，而不是只看 source similarity。

### 2.1 第一层：漏洞机制保真

目的：

- 防止生成样本完全跑偏
- 保留与原漏洞机制仍然相关的样本

做法：

- 延续当前 `post_process.py + post_analysis.py`
- 保留和源域漏洞种子距离不超过上界的样本

建议：

- `source_distance <= 0.92`

### 2.2 第二层：去重与去近邻

目的：

- 防止增强样本只是 seed 的轻微改写
- 减少“越扩越像 reveal 原文”的问题

做法：

- 在 source similarity 的基础上再加一个下界
- 过近样本直接丢弃

建议：

- `source_distance >= 0.10`

### 2.3 第三层：目标域对齐重打分

目的：

- 让保留下来的增强样本更接近 `devign` 风格
- 提升跨域而不是只提升训练内指标

做法：

- 只使用 `devign` 的 `train split` 作为无标签目标域参考，避免测试泄漏
- 为每个生成样本计算：
  - 与目标域训练集的字符级 TF-IDF 余弦相似度
  - 与目标域长度分布的一致性
  - 在 source band 内的“新颖度”
- 最后做一个加权总分排序

当前实现的打分形式为：

- `0.55 * target_cosine`
- `0.25 * length_alignment`
- `0.20 * source_novelty`

## 3. 为何这样设计

这套方案的直觉是：

1. source gate 保证漏洞模式不要漂移太远
2. source min distance 防止只是对 seed 做极小改写
3. target cosine 让样本更像目标域代码写作风格
4. length alignment 避免增强样本长度分布长期偏离目标域
5. per-seed cap 避免少数 seed 生成大量相似样本主导训练集

## 4. 注释作弊防护

当前需要特别警惕的风险是：

- 模型可能学到“注释文本提示漏洞”的捷径
- 尤其当生成样本里出现解释性注释、审计性注释或自然语言提示时

因此，下一版实验必须坚持：

1. 所有生成样本在入库前统一去注释
2. source / target / augmented 三端尽量使用一致的 comment stripping 逻辑
3. 每轮实验输出 comment audit，记录：
   - 有多少样本移除了注释
   - 移除了多少注释字符
   - 哪些样本存在较重注释依赖

目前工程上已经补充了：

- `post_process.py` 中的 comment audit 统计
- 生成后处理报告里会显式记录 comment removal 信息

## 5. 已落地的脚本

当前已新增跨域对齐筛选脚本：

- `/root/VulnBooster/gvi_causalcode/generation/filter_cross_domain_alignment.py`

它会在 `post_analysis.py` 之后进一步重打分，并输出：

- 跨域对齐后的 `final_augmented_vul.json`
- `target_alignment_report.json`

## 6. 推荐默认参数

建议先从这组参数开始：

- `FILTER_MODE=source_target_align`
- `TARGET_ALIGN_TASK=devign`
- `TARGET_ALIGN_SOURCE_MIN_DISTANCE=0.10`
- `TARGET_ALIGN_SOURCE_MAX_DISTANCE=0.92`
- `TARGET_ALIGN_MIN_COSINE=0.08`
- `TARGET_ALIGN_KEEP_RATIO=0.35`
- `TARGET_ALIGN_MAX_PER_SEED=2`

这组参数的意图是：

- 不让样本离 source 太远
- 也不让它离 source 太近
- 更偏向保留与 `devign` 写作风格更接近的前 `35%` 样本
- 且每个 seed 至多贡献 `2` 条

## 7. 推荐执行方式

下一轮实验建议直接这样跑：

```bash
FILTER_MODE=source_target_align \
TARGET_ALIGN_TASK=devign \
TARGET_ALIGN_SOURCE_MIN_DISTANCE=0.10 \
TARGET_ALIGN_SOURCE_MAX_DISTANCE=0.92 \
TARGET_ALIGN_MIN_COSINE=0.08 \
TARGET_ALIGN_KEEP_RATIO=0.35 \
TARGET_ALIGN_MAX_PER_SEED=2 \
bash scripts/run_augmented_formal_pipeline.sh
```

## 8. 阶段性预期

这套方案的目标不是单纯让训练集更大，而是：

- 降低训练域过拟合
- 抑制“source 内部自我强化”
- 提高增强样本对目标域分布的贴近程度

如果方向正确，下一轮更理想的现象应该是：

- 训练内验证 F1 可能略低于 `reveal_aug_v2`
- 但 `devign` 上的 Recall 与 F1 应该回升
