# 代码目录说明

这个目录是当前漏洞检测项目的主要代码区。

## 主要模块

- `train_bert/`：主要训练代码、评估包装、干预数据生成、LineVul 集成
- `generation/`：基于大模型的漏洞代码生成与后处理
- `evaluation/`：原始 LineVul 相关评估代码和辅助资源
- `preprocess-lstm/`：较早期的预处理和扰动生成工具
- `data/`：轻量级脚本和本地数据元信息
- `data_raw/`：原始提取代码样本，只保留本地，不进入 Git
- `utils/`：项目共用工具函数

## 当前重点区域

目前最值得优先关注的是：

1. `generation/`
2. `train_bert/`
3. `evaluation/linevul/`

## 当前推荐入口

- 训练验证：`scripts/train_short_gpu.sh`
- 轻量漏洞生成：`scripts/run_generation_prompt.sh`

## 仓库策略

- 代码和轻量级说明文档保留在 Git 中
- 数据集、生成结果、缓存、日志、checkpoint 和实验产物尽量不进入 Git
- 密钥等敏感信息应通过环境变量提供，不要写死在受跟踪文件里
- 尽量使用相对路径或环境变量，不要依赖机器特定的绝对路径
