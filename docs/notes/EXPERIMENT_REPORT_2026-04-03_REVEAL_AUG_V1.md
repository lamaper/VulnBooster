# reveal_aug_v1 实验结论

更新时间：2026-04-03

## 1. 实验目的

本轮实验的目标是验证一条完整闭环是否成立：

1. 使用 LLM 生成漏洞增强样本
2. 将增强样本并入 `reveal`，构建增强任务 `reveal_aug_v1`
3. 先训练正式的 `LineVul` 引导模型
4. 基于引导模型为增强任务重生成 `CausalCode` 配对域
5. 在 `origin_s + linevul-CausalCode-token` 双域设置下重新训练
6. 在 `devign` 上进行跨数据集测试

## 2. 数据与配置

### 2.1 训练任务

- 基础任务：`reveal`
- 增强任务：`reveal_aug_v1`
- 跨域测试集：`devign`
- 模型：`LineVul`
- 因果增强方式：`CausalCode`
- 干预类型：`token`

### 2.2 增强数据规模

`reveal_aug_v1` 由原始 `reveal` 加入少量 LLM 生成样本构成：

- 原始训练样本：`18188`
- 原始测试样本：`4546`
- 新增生成样本：`4`
- 最终训练样本：`18192`

说明：

- 当前 `reveal_aug_v1` 仍然更接近“闭环验证版”而不是“正式大规模增强版”
- 这会直接限制增强收益的上限

## 3. 实验流程与产物

### 3.1 正式引导模型训练

先在 `reveal_aug_v1` 的 `origin_s` 上训练正式 guide 模型。

模型产物：

- `gvi_causalcode/data/reveal_aug_v1/model/linevul/CausalCode/token/origin_s/best.pt`

### 3.2 配对域重生成

随后使用上一步的 guide 模型为 `reveal_aug_v1` 重建 `linevul-CausalCode-token` 配对域。

配对域产物：

- `gvi_causalcode/data/reveal_aug_v1/dataset/linevul-CausalCode-token/data.pkl.gz`

### 3.3 双域正式训练与测试

最终在以下双域设置下训练并测试：

- 域组合：`origin_s,linevul-CausalCode-token`
- 训练任务：`reveal_aug_v1`
- 测试任务：`devign`

模型产物：

- `gvi_causalcode/data/reveal_aug_v1/model/linevul/CausalCode/token/origin_s+linevul-CausalCode-token/best.pt`

## 4. 结果

### 4.1 guide-only 模型在 devign 上的结果

这里的 guide-only 指仅使用 `origin_s` 训练得到的模型，在 `devign` 上直接测试。

- Accuracy：`54.73%`
- Precision：`51.00%`
- Recall：`4.12%`
- F1：`7.63%`

### 4.2 双域 CausalCode 模型的训练内验证结果

- Epoch 3：`Acc 90.86% | P 57.97% | R 22.60% | F1 32.52%`
- Epoch 4：`Acc 90.65% | P 64.00% | R 9.09% | F1 15.92%`
- Epoch 5：`Acc 88.50% | P 38.73% | R 31.25% | F1 34.59%`

最佳验证 F1 为：

- `34.59%`

### 4.3 双域 CausalCode 模型在 devign 上的最终结果

- Accuracy：`54.69%`
- Precision：`50.25%`
- Recall：`8.12%`
- F1：`13.99%`

## 5. 结果分析

### 5.1 正向结论

本轮实验最重要的正向结论有三点：

1. 已经成功跑通“LLM 增强数据 -> 增强任务构建 -> guide 模型训练 -> 配对域重生成 -> 双域训练 -> 跨域测试”的完整闭环。
2. `CausalCode` 双域训练相较于 guide-only 基线，确实带来了跨域 F1 提升。
3. 提升主要体现在召回率上升，说明因果配对域对缓解跨域漏检有一定帮助。

具体表现为：

- F1：`7.63% -> 13.99%`
- Recall：`4.12% -> 8.12%`

这说明当前方案不是完全无效，而是已经表现出“方向正确但力度不足”的特征。

### 5.2 当前主要问题

当前结果仍然偏弱，核心问题是：

- 最终 `devign` F1 仍然只有 `13.99%`
- 模型在 `devign` 上依然高度保守
- `Accuracy` 维持在 `54%` 左右，但 `Recall` 很低，说明漏检严重

换句话说：

- 现在的模型不是“抓错太多”
- 而是“抓出来的太少”

### 5.3 为什么效果有限

当前最可能的限制因素如下：

1. 增强规模过小。`reveal_aug_v1` 只新增了 `4` 条 LLM 漏洞样本，难以显著改变训练分布。
2. `reveal -> devign` 本身属于较难的跨数据集迁移，分布差异较大。
3. 当前仍然只测试了 `token` 型干预，还没有比较 `dead_code` 或更大规模增强版本。

## 6. 可写进论文或周报的表述

可以直接使用下面这段较正式的总结：

> We completed an end-to-end experimental pipeline that integrates LLM-based vulnerability augmentation with CausalCode-style paired intervention training. Starting from the original ReVeal dataset, we constructed an augmented training task (`reveal_aug_v1`), trained a formal LineVul guide model, regenerated the paired CausalCode intervention domain, and finally conducted cross-dataset evaluation on Devign. The dual-domain CausalCode setting improved cross-dataset F1 from 7.63% to 13.99%, mainly by increasing recall from 4.12% to 8.12%. These results indicate that the proposed integration is feasible and can improve cross-domain robustness, although the current gain is still limited due to the very small scale of generated augmentation data.

也可以用更偏中文周报/论文草稿的表述：

> 本轮实验成功完成了从 LLM 漏洞生成增强、增强任务构建、正式引导模型训练、配对干预域重生成到双域因果训练与跨数据集测试的完整闭环。实验结果表明，在 `reveal_aug_v1 -> devign` 设置下，引入 `origin_s + linevul-CausalCode-token` 双域训练后，模型的跨域 F1 从 `7.63%` 提升至 `13.99%`，召回率从 `4.12%` 提升至 `8.12%`。这说明基于增强数据的 CausalCode 配对训练具有一定的跨域增益潜力，但由于当前增强样本规模过小，整体提升仍然有限。

## 7. 阶段性结论

当前最合理的阶段判断是：

- 工程闭环已经验证成功
- 因果双域训练已经表现出正增益
- 当前瓶颈不在“流程能否运行”，而在“增强数据规模是否足够”

因此，下一阶段最重要的工作不是继续重复当前 `reveal_aug_v1` 小规模版本，而是：

- 使用更大规模的 LLM 增强数据构建新的增强任务
- 再重复相同的闭环流程
- 观察更大增强规模下对跨域 F1 和 Recall 的提升幅度
