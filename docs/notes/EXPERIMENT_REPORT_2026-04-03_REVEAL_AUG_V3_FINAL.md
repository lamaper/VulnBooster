# reveal_aug_v3 最终评估

更新时间：2026-04-03

## 1. 实验状态

`reveal_aug_v3` 这一轮完整闭环已经全部完成，包括：

1. 基于 `reveal_aug_v2` 生成池执行目标域对齐筛选
2. 构建增强任务 `reveal_aug_v3`
3. 训练正式 `LineVul` guide 模型
4. 重生成 `linevul-CausalCode-token` 配对域
5. 在 `origin_s + linevul-CausalCode-token` 双域设置下重新训练
6. 在 `devign` 上执行最终跨域测试

## 2. 数据与筛选配置

### 2.1 目标域对齐筛选结果

本轮没有重新调用 LLM 生成，而是复用 `reveal_aug_v2` 的变体池，并加入“更偏跨域对齐”的筛选：

- 候选变体总数：`1324`
- 通过源域/目标域双门控：`1296`
- 对齐筛选选中：`392`
- 与原训练集去重后实际加入训练集：`389`

筛选报告位于：

- `gvi_causalcode/data/reveal/deepseek_reveal_aug_v2_pgr_l200_n4_result/target_alignment_report_devign.json`

### 2.2 reveal_aug_v3 训练集规模

- 原始训练样本：`18188`
- 原始测试样本：`4546`
- 新增增强样本：`389`
- 最终训练样本：`18577`
- 最终测试样本：`4546`

## 3. guide 阶段结果

在 `reveal_aug_v3` 的 `origin_s` 上训练 guide 模型，其验证集最佳结果为：

- Accuracy：`90.85%`
- Precision：`61.15%`
- Recall：`42.50%`
- F1：`50.15%`

对应最佳模型：

- `gvi_causalcode/data/reveal_aug_v3/model/linevul/CausalCode/token/origin_s/best.pt`

## 4. 双域训练结果

最终使用如下配置进行训练与测试：

- 训练任务：`reveal_aug_v3`
- 域组合：`origin_s + linevul-CausalCode-token`
- 测试任务：`devign`
- 模型：`LineVul`
- 干预方式：`CausalCode`
- 干预类型：`token`

双域训练过程中的最佳验证结果为：

- Accuracy：`89.23%`
- Precision：`50.27%`
- Recall：`46.00%`
- F1：`48.04%`

最终 `devign` 跨域测试结果为：

- Accuracy：`55.22%`
- Precision：`59.06%`
- Recall：`4.08%`
- F1：`7.64%`

对应最终模型：

- `gvi_causalcode/data/reveal_aug_v3/model/linevul/CausalCode/token/origin_s+linevul-CausalCode-token/best.pt`

## 5. 与 v1 / v2 对比

### 5.1 最终跨域结果对比

`reveal_aug_v1`：

- Accuracy：`54.69%`
- Precision：`50.25%`
- Recall：`8.12%`
- F1：`13.99%`

`reveal_aug_v2`：

- Accuracy：`54.89%`
- Precision：`53.76%`
- Recall：`3.76%`
- F1：`7.03%`

`reveal_aug_v3`：

- Accuracy：`55.22%`
- Precision：`59.06%`
- Recall：`4.08%`
- F1：`7.64%`

### 5.2 对比变化

相对 `v2`，`v3` 的变化为：

- Accuracy：`54.89% -> 55.22%`
- Precision：`53.76% -> 59.06%`
- Recall：`3.76% -> 4.08%`
- F1：`7.03% -> 7.64%`

相对 `v1`，`v3` 的变化为：

- Accuracy：`54.69% -> 55.22%`
- Precision：`50.25% -> 59.06%`
- Recall：`8.12% -> 4.08%`
- F1：`13.99% -> 7.64%`

## 6. 最终分析

### 6.1 正向结论

`v3` 至少说明一件事：

- “目标域对齐筛选”比 `v2` 的朴素大规模并入更合理

因为在增强样本数量从 `1307` 显著收缩到 `389` 之后，`devign` 上的最终结果出现了小幅恢复：

- F1：`7.03% -> 7.64%`
- Recall：`3.76% -> 4.08%`
- Precision：`53.76% -> 59.06%`

这说明：

- `v2` 中确实存在一部分会放大训练域偏置的增强样本
- 对齐筛选在一定程度上缓解了这一问题

### 6.2 但 v3 仍未恢复到 v1

尽管 `v3` 比 `v2` 略好，但它仍明显落后于 `v1`：

- `v1` F1：`13.99%`
- `v3` F1：`7.64%`

最关键的问题仍然是：

- 模型在 `devign` 上依然非常保守
- 最终 Recall 只有 `4.08%`
- 也就是说，模型不是“乱报太多”，而是“报得太少”

### 6.3 当前结果说明了什么

当前三轮实验联合起来，更支持下面这个判断：

1. 朴素扩大增强规模会明显强化训练域拟合，但不一定提升跨域泛化。
2. 引入目标域对齐筛选后，跨域结果确实比 `v2` 有恢复，说明“对齐方向”是对的。
3. 但当前筛选仍然主要基于相似度/距离启发式，无法充分保证语义级跨域迁移价值。
4. 因此，`v3` 证明了“对齐筛选有必要”，但还没有证明“当前对齐策略已经足够”。

### 6.4 一个很重要的现象

`v2` 的 guide 验证 F1 很高，为 `66.80%`；`v3` 的 guide 验证 F1 降到了 `50.15%`。

但跨域结果却是：

- `v2`：`7.03%`
- `v3`：`7.64%`

这进一步说明：

- 训练内验证指标并不能直接代表跨数据集泛化能力
- 更高的 in-domain F1，可能只是更强地拟合了 `reveal` 风格
- 对于当前课题，增强数据与目标域的分布匹配度，比单纯提高训练内分数更关键

## 7. 可写进论文或周报的表述

英文版本：

> We further evaluated a target-aligned augmentation setting (`reveal_aug_v3`) by reusing the previously generated augmentation pool and filtering it with a cross-domain alignment strategy toward Devign. This reduced the effective augmentation size from 1,307 samples in `reveal_aug_v2` to 389 selected samples. Compared with the naive large-scale augmentation setting, the target-aligned version slightly improved cross-dataset performance on Devign, raising F1 from 7.03% to 7.64% and recall from 3.76% to 4.08%. However, the result was still well below the 13.99% F1 observed in the earlier small-scale `reveal_aug_v1` setting. These findings suggest that target-domain-aware filtering is necessary and directionally beneficial, but similarity-based alignment alone is still insufficient to fully recover cross-domain generalization.

中文版本：

> 本轮实验在 `reveal_aug_v2` 已生成增强池的基础上，引入了面向 `devign` 的目标域对齐筛选策略，最终将实际并入训练集的增强样本从 `1307` 条压缩为 `389` 条。结果表明，与 `v2` 的朴素大规模增强相比，目标域对齐版本在跨数据集测试上出现了小幅恢复，`devign` 上的 F1 从 `7.03%` 提升到 `7.64%`，Recall 从 `3.76%` 提升到 `4.08%`。但这一结果仍明显低于 `reveal_aug_v1` 的 `13.99%`。这说明目标域对齐筛选是必要且方向正确的，但仅靠当前基于相似度的筛选策略，还不足以充分恢复跨域泛化能力。

## 8. 阶段性结论

`v3` 的最合理结论不是“方案失败”，而是：

- `v2` 暴露了大规模增强会放大源域偏置的问题
- `v3` 证明了目标域对齐筛选能部分缓解这一问题
- 但现有对齐强度仍不够，下一步需要更强的跨域约束

下一阶段更值得推进的方向包括：

1. 引入更严格的跨域对齐打分，而不是仅依赖 token/embedding 相似度。
2. 在增强筛选中加入结构约束、漏洞语义约束和注释清洗一致性检查。
3. 降低“只增强正样本”带来的判别边界偏移，考虑更平衡的训练策略或阈值分析。
