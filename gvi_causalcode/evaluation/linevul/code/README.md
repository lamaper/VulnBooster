# LineVul 评估代码说明

这个目录保留的是 `LineVul` 相关评估代码和部分复现实验资源，主要用于当前项目中的基线对比与结果参考。

## 这个目录在当前项目里的作用

- 提供 `LineVul` 相关代码结构参考
- 保留原始评估逻辑，便于和当前 `CausalCode + LineVul` 训练路线对照
- 为后续基线实验、结果复查和论文写作提供依据

## 使用时需要注意

- 这里更多是“参考与评估资源区”，不是当前项目的主训练入口
- 当前真正已经跑通的训练入口仍然是：
  - `gvi_causalcode/train_bert/run.py`
- 如果你要复现实验，优先看：
  - `docs/notes/PROJECT_RESUME_GUIDE.md`
  - `docs/notes/PROJECT_MEMORY.md`
  - `docs/WSL_GPU_ENV.md`
  - `scripts/train_short_gpu.sh`

## 与当前仓库的关系

当前仓库并不是原始 `LineVul` 仓库的完整复刻，而是围绕“漏洞检测 + 数据增强 + 因果训练”整理过的一套研究工作区。

因此这里的 `LineVul` 代码更适合这样理解：

- 它是当前项目中的一个重要基础模型来源
- 它为 `CausalCode` 路线提供基线能力和评估参照
- 它不是你后续主要修改和扩展的唯一核心目录

## 如果你之后要继续推进

建议优先关注这些位置：

1. `gvi_causalcode/train_bert/`
2. `gvi_causalcode/generation/`
3. `docs/notes/PROJECT_MEMORY.md`
4. `docs/notes/PROJECT_RESUME_GUIDE.md`

## 说明

原始 `LineVul` 项目包含更完整的论文复现说明、数据下载方式和模型细节。当前文件改为中文摘要版，目的是让本仓库的文档风格保持统一、便于后续快速恢复项目上下文。
