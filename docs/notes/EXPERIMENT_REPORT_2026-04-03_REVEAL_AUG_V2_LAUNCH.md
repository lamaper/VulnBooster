# reveal_aug_v2 大规模增强实验启动记录

更新时间：2026-04-03

## 1. 上轮实验结论回顾

上轮 `reveal_aug_v1` 实验已经验证了完整闭环可运行：

1. LLM 生成漏洞增强样本
2. 构建增强任务
3. 训练正式 `LineVul` guide 模型
4. 基于 guide 模型重生成 `CausalCode` 配对域
5. 在 `origin_s + linevul-CausalCode-token` 双域上重新训练
6. 在 `devign` 上进行跨数据集测试

核心结果如下：

- guide-only on `devign`：`Acc 54.73% | P 51.00% | R 4.12% | F1 7.63%`
- dual-domain on `devign`：`Acc 54.69% | P 50.25% | R 8.12% | F1 13.99%`

阶段性判断如下：

- 闭环本身已经成立
- `CausalCode` 双域训练对跨域 F1 和 Recall 有正增益
- 当前瓶颈主要不是流程，而是增强数据规模过小

## 2. 本轮实验目标

本轮实验不再停留在小样本闭环验证，而是尝试构建一个真正更大规模的 LLM 增强版本，再重复完整正式流程，观察跨域效果是否继续提升。

目标分为两部分：

1. 用 DeepSeek API 生成更大规模的漏洞增强数据
2. 基于新增强任务重新执行“guide 训练 + 配对域重生成 + 双域训练/测试”

## 3. 大规模增强配置

本轮使用的增强配置如下：

- 基础任务：`reveal`
- 新增强任务：`reveal_aug_v2`
- 生成模式：`pattern_generate_repair`
- 生成种子数：`200`
- 每个种子生成变体数：`4`
- 理论最大原始生成规模：`800`
- 生成模型：`deepseek-chat`
- 推理接口：`https://api.deepseek.com/v1`

正式训练配置如下：

- guide 训练轮数：`5`
- 最终双域训练轮数：`5`
- early stop：`5`
- batch size：`8`
- GPU：`0`
- 测试任务：`devign`
- 干预类型：`token`

## 4. 本轮核心假设

本轮实验的核心研究假设是：

- 如果增强样本规模从 `reveal_aug_v1` 的极小规模提升到更大规模，
- 且样本仍然能够保持漏洞机制的一致性与基本语法可行性，
- 那么基于增强数据训练出来的 guide 模型及其重生成的 `CausalCode` 配对域，
- 有望进一步提高 `reveal -> devign` 的跨域 Recall 与 F1。

换句话说，本轮实验主要检验的是：

- 之前的正增益是否具有可放大性
- 生成规模扩大后是否能真正改善跨域迁移效果

## 5. 启动状态

本轮正式大规模实验已经在 `tmux` 中启动，当前以不阻塞终端的方式持续运行。

- tmux 会话：`vb_reveal_aug_v2_full_0403_111250`
- 主日志：`/root/VulnBooster/logs/reveal_aug_v2_master_20260403_111250.log`
- 生成输出目录：`/root/VulnBooster/gvi_causalcode/data/reveal/deepseek_reveal_aug_v2_pgr_l200_n4`
- 过滤结果目录：`/root/VulnBooster/gvi_causalcode/data/reveal/deepseek_reveal_aug_v2_pgr_l200_n4_result`

当前执行顺序为：

1. LLM 漏洞增强生成
2. `post_process.py`
3. `post_analysis.py`
4. 构建增强任务 `reveal_aug_v2`
5. 训练正式 guide 模型
6. 重生成 `linevul-CausalCode-token` 配对域
7. 进行最终双域训练与 `devign` 测试

## 6. 论文或周报可直接使用的表述

可写成如下较正式的实验推进描述：

> Based on the positive but limited results of `reveal_aug_v1`, we launched a larger-scale augmentation experiment on ReVeal using DeepSeek-based vulnerable code generation. The new setting, denoted as `reveal_aug_v2`, increases the augmentation scale from a smoke-test level to a substantially larger candidate pool and re-runs the full pipeline of formal LineVul guide training, paired CausalCode domain regeneration, and dual-domain cross-dataset evaluation on Devign. This experiment is intended to verify whether the previously observed gains in recall and F1 can be amplified when the augmentation scale is increased.

也可以用中文周报风格表述：

> 在上一轮 `reveal_aug_v1` 小规模闭环实验取得正向结果后，本周进一步启动了 `reveal_aug_v2` 大规模增强实验。该实验基于 DeepSeek 接口对 `reveal` 漏洞函数进行更大规模生成，并在此基础上重新执行正式 guide 模型训练、CausalCode 配对域重生成以及双域跨数据集评测。该阶段的主要目标是验证：随着增强样本规模扩大，前一轮实验中观察到的 Recall 和 F1 增益是否能够进一步放大。

## 7. 待最终补充的结果项

本记录当前主要用于保存实验目的与启动配置。待实验完成后，需要补充以下结果：

- 最终保留下来的增强样本数量
- `reveal_aug_v2` 的训练集规模
- guide-only 在 `devign` 上的结果
- 双域模型在 `devign` 上的最终 `Acc / P / R / F1`
- 与 `reveal_aug_v1` 的对比分析
