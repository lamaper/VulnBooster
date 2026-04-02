# VulnBooster

这是当前“基于数据增强的源代码漏洞检测技术研究”项目的工作仓库。

## 仓库结构

- `gvi_causalcode/`：当前主要代码，包括生成、预处理、训练、评估
- `docs/`：长期文档、项目记忆、部署说明、参考资料说明
- `scripts/`：环境初始化和训练启动脚本
- `requirements/`：当前已验证可用的依赖版本

## 哪些内容应该进 Git

- 源代码
- 轻量级脚本
- 项目说明文档
- 对后续推进有帮助的长期笔记

## 哪些内容应该只保留在本地

- 原始数据
- 处理后的大体积训练产物
- 生成样本和静态分析结果
- tokenizer、checkpoint、日志、缓存
- 本地论文 PDF
- API Key 等敏感信息

## 当前主线

目前项目最重要的三条线是：

1. `gvi_causalcode/generation/`
2. `gvi_causalcode/train_bert/`
3. `gvi_causalcode/evaluation/linevul/`

## 建议阅读顺序

如果你隔了很久再回来，建议按这个顺序看：

1. `docs/notes/PROJECT_RESUME_GUIDE.md`
2. `docs/notes/PROJECT_MEMORY.md`
3. `docs/WSL_GPU_ENV.md`
4. `docs/SERVER_TRAINING_PLAYBOOK.md`
5. `gvi_causalcode/README.md`

## 当前补充说明

- 项目长期记忆保存在 `docs/notes/PROJECT_MEMORY.md`
- 项目恢复指南保存在 `docs/notes/PROJECT_RESUME_GUIDE.md`
- 已验证的 WSL GPU 环境说明保存在 `docs/WSL_GPU_ENV.md`
- 服务器快速部署说明保存在 `docs/SERVER_TRAINING_PLAYBOOK.md`
- 可复用的短训练脚本在 `scripts/train_short_gpu.sh`
- 可复用的轻量漏洞生成脚本在 `scripts/run_generation_prompt.sh`
