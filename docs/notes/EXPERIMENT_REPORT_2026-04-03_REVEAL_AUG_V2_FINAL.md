# reveal_aug_v2 最终评估

更新时间：2026-04-03

## 1. 实验状态

`reveal_aug_v2` 这一轮完整闭环已经全部完成，包括：

1. DeepSeek 并发生成
2. `post_process.py`
3. `post_analysis.py`
4. 增强任务构建
5. formal guide 模型训练
6. `linevul-CausalCode-token` 配对域重生成
7. 双域训练与 `devign` 跨域测试

## 2. 增强数据规模

本轮增强数据结果如下：

- 处理种子数：`200`
- 每个种子目标变体数：`4`
- 生成成功 seed 数：`195`
- resume 跳过 seed 数：`5`
- 提取出的有效漏洞变体：`1324`
- 相似度过滤后保留：`1321`
- 实际并入训练集的增强样本：`1307`

增强任务规模如下：

- 原始训练样本：`18188`
- 原始测试样本：`4546`
- 新增增强样本：`1307`
- 最终训练样本：`19495`
- 最终测试样本：`4546`

## 3. guide 阶段结果

guide 模型在训练内验证集上的最佳结果为：

- Accuracy：`91.63%`
- Precision：`81.91%`
- Recall：`56.40%`
- F1：`66.80%`

这说明在增强后的 `reveal_aug_v2` 任务内部，模型能够较好地拟合训练分布。

## 4. 最终双域跨域测试结果

最终使用：

- 训练任务：`reveal_aug_v2`
- 域组合：`origin_s + linevul-CausalCode-token`
- 测试任务：`devign`

最终 `devign` 测试结果为：

- Accuracy：`54.89%`
- Precision：`53.76%`
- Recall：`3.76%`
- F1：`7.03%`

## 5. 与上一轮 reveal_aug_v1 对比

上一轮 `reveal_aug_v1` 最终双域跨域结果为：

- Accuracy：`54.69%`
- Precision：`50.25%`
- Recall：`8.12%`
- F1：`13.99%`

本轮 `reveal_aug_v2` 最终双域跨域结果为：

- Accuracy：`54.89%`
- Precision：`53.76%`
- Recall：`3.76%`
- F1：`7.03%`

对比变化如下：

- Accuracy：`54.69% -> 54.89%`
- Precision：`50.25% -> 53.76%`
- Recall：`8.12% -> 3.76%`
- F1：`13.99% -> 7.03%`

## 6. 最终分析

本轮最重要的发现是：

- 大规模增强显著提升了训练内表现
- 但没有带来更好的跨域泛化
- 最终反而让模型在 `devign` 上更保守，导致 Recall 和 F1 明显下降

这说明当前问题不在“增强规模不够”，而更可能在“增强样本分布与目标跨域分布之间的偏差”。

更具体地说，当前结果更支持以下判断：

1. `reveal_aug_v2` 的增强样本成功强化了模型对 `reveal` 风格漏洞模式的拟合能力。
2. 这些增强样本未能有效覆盖 `devign` 的跨域分布差异。
3. 配对域训练在更大规模增强数据上可能进一步放大了训练域偏置，而不是缓解域偏移。
4. 因此，训练内高 F1 并不等价于跨数据集泛化更强。

换句话说：

- `reveal_aug_v1` 呈现的是“小规模但有跨域正增益”
- `reveal_aug_v2` 呈现的是“大规模但更偏训练域、更弱跨域泛化”

## 7. 当前最合理的阶段结论

当前最合理的结论不是“LLM 增强无效”，而是：

- 朴素扩大增强规模并不能保证跨域收益
- 增强数据的质量、分布控制和目标域对齐，比单纯扩大数量更关键
- 当前方法需要进一步加入更强的筛选、去偏或目标域对齐策略

## 8. 可写进论文或周报的表述

可以直接写成如下英文表述：

> We further scaled up the augmentation pipeline from a smoke-test setting (`reveal_aug_v1`) to a substantially larger version (`reveal_aug_v2`), adding 1,307 generated vulnerable samples into the ReVeal training set. Although the enlarged dataset significantly improved in-domain validation performance of the guide model, the final cross-dataset evaluation on Devign did not improve accordingly. In fact, the dual-domain model achieved only 7.03 F1 on Devign, lower than the 13.99 F1 observed in the smaller `reveal_aug_v1` setting. This result suggests that simply increasing augmentation scale is insufficient for cross-domain robustness; distribution alignment and augmentation quality control are more critical than augmentation quantity alone.

也可以直接写成中文周报/论文草稿表述：

> 本轮实验将增强规模从 `reveal_aug_v1` 的小规模闭环验证扩展到 `reveal_aug_v2` 的大规模版本，最终向训练集加入了 `1307` 条 LLM 生成漏洞样本。结果表明，大规模增强确实显著提升了训练域内部的验证表现，但并未转化为更好的跨数据集泛化能力。最终在 `devign` 上的双域测试 F1 仅为 `7.03%`，低于上一轮 `reveal_aug_v1` 的 `13.99%`。这说明当前阶段的主要瓶颈已经不再是增强规模，而是增强样本与目标跨域分布之间的偏差控制问题。仅靠扩大生成数量并不能保证跨域鲁棒性提升，后续更需要关注增强样本筛选、分布对齐和生成质量约束。
