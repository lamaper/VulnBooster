# CodeT5 行级切片器首轮迁移报告

## 1. 本轮完成内容

本轮围绕“冻结现有主结构后，引入 CodeT5 行级切片器并跑第一轮验证”完成了以下工作：

1. 冻结当前主结构与已有成绩
   - `docs/frozen_main_structure_2026-07-10.md`
2. 补充 CodeT5 行级切片器迁移方案
   - `docs/codet5_line_slicer_migration_plan.md`
3. 新增 `CodeT5` 切片模块
   - `src/vulnbooster/codet5_slicer.py`
4. 接入配置、CLI 与总实验脚本
   - `src/vulnbooster/config.py`
   - `src/vulnbooster/cli.py`
   - `scripts/run_small_model_aug_experiment.py`
5. 补充测试并完成本地、远端语法/单测验证
6. 在远端 `4090D` 环境上跑出第一版可用结果

## 2. 本轮采用的 CodeT5 方案

本次不是让 `CodeT5` 自由生成切片代码，而是采用“行号序列预测”方案：

1. 输入：带行号的完整函数 + 静态切片提示
2. 输出：漏洞相关行号序列，例如 `L003 L004 L005`
3. 后处理：
   - 只保留合法行号
   - 去重排序
   - 自动补齐代码块平衡
   - 回拼为 `line_slice`

这样做的目的，是把 `SLICEFORMER` 中“减少幻觉、加强约束”的思想，以更低改造成本落到当前工程中。

## 3. 关键工程兼容修复

为了让远端实验真正跑通，本轮顺手修掉了几类环境兼容问题：

1. `transformers 5.13.0` 与 `CodeT5` tokenizer 兼容不稳
   - 解决：远端与本地训练环境回落到 `transformers==4.44.2`、`tokenizers==0.19.1`
2. `Trainer/Seq2SeqTrainer` 参数差异
   - 解决：将 `processing_class=` 适配为 `tokenizer=`
3. 历史 `CodeBERT` 模型目录 tokenizer 兼容问题
   - 解决：检测器打分时使用基础模型名的 tokenizer，权重仍从实验模型目录加载
4. `CodeT5` 模型/Tokenizer 本地缓存不完整时的回退逻辑
   - 解决：新增更稳的 local/online fallback

## 4. 首轮结果

### 4.1 远端快速复用实验

为了先验证 `CodeT5` 切片器是否能带来真实下游增益，先复用了历史资产：

1. 基础实验：`~/VulnBooster/artifacts/experiments/medium_line_slice_v1`
2. 新实验输出：`~/VulnBooster/artifacts/experiments/codet5_line_slice_v1_reuse`

复用内容：

1. 现有教师切片监督 `train/valid/test_line_labels.jsonl`
2. 现有 baseline detector 漏报样本
3. 现有 clean train/valid/test 数据

### 4.2 CodeT5 切片器本身结果

文件：

1. `~/VulnBooster/artifacts/experiments/codet5_line_slice_v1_reuse/codet5_slicer_eval.json`

结果：

1. Valid
   - Precision: `0.6732`
   - Recall: `0.4672`
   - F1: `0.5516`
   - ExactMatch: `0.3000`
2. Test
   - Precision: `0.7111`
   - Recall: `0.5386`
   - F1: `0.6130`
   - ExactMatch: `0.2625`
3. 对 baseline 漏报样本的切片覆盖
   - `fn_slice_rows = 7`
   - `fn_slice_non_empty = 7`
   - `fn_pred_non_empty = 7`

说明：

1. 这一版 `CodeT5` 已经能稳定输出非空切片。
2. 但切片层 Recall 还不高，说明它倾向于更保守地抓关键行。

### 4.3 下游漏洞检测结果

文件：

1. `~/VulnBooster/artifacts/experiments/codet5_line_slice_v1_reuse/summary_resume.json`

基线：

1. Precision: `0.6875`
2. Recall: `0.8250`
3. F1: `0.7500`
4. MCC: `0.4593`

CodeT5 切片增强后：

1. Precision: `0.7143`
2. Recall: `0.8750`
3. F1: `0.7865`
4. MCC: `0.5388`

相对基线增益：

1. Precision `+0.0268`
2. Recall `+0.0500`
3. F1 `+0.0365`
4. MCC `+0.0795`

### 4.4 数据质量层表现

1. 生成候选共 `20` 条
2. 验证保留 `14` 条
3. `invalid_syntax = 0`
4. `trivial_variant = 0`
5. 因 `max_per_seed=2` 被截断 `6` 条

说明：

1. `CodeT5` 切片输出已经能够支撑当前增强生成器稳定工作。
2. 在现有质量门控下，增强样本没有明显塌成垃圾样本。

## 5. 当前结论

可以先得出一个明确的阶段性结论：

**CodeT5 行级切片器已经成功接入当前增强主链路，并在首轮复用实验中带来了可观的下游增益。**

尤其是：

1. F1 从 `0.7500` 提升到 `0.7865`
2. MCC 从 `0.4593` 提升到 `0.5388`

这说明：

1. “小模型切片替代部分 LLM 辅助切片职责”这条线是可行的
2. `CodeT5` 不是只在切片指标上好看，而是已经把收益传导到漏洞检测结果

## 6. 尚未结束的任务

为了拿到更干净的结论，还同步启动了一条“从教师切片开始完整重跑”的后台任务：

1. 远端目录：`~/VulnBooster/artifacts/experiments/codet5_line_slice_v1_full`
2. 日志：`~/VulnBooster/artifacts/experiments/codet5_line_slice_v1_full/run.log`
3. 当前状态：仍在后台运行

这条任务的意义是：

1. 不再依赖历史中间产物
2. 直接验证 `CodeT5` 接入后的完整实验链路
3. 便于后续与现有 `line_slicer`、`v3`、`v4` 结果做更严格对比

## 7. 下一步建议

基于本轮结果，下一步建议继续做三件事：

1. 把 `CodeT5` 切片结果接入“按漏洞机理分流”的 prompt 生成
2. 提高 `CodeT5` 切片 Recall
   - 增加静态切片 hint
   - 加入邻接行扩展策略
   - 加入数据流感知训练增强
3. 等完整重跑结束后，对比：
   - `CodeBERT line_slicer + v4 generator`
   - `CodeT5 slicer + v4 generator`
