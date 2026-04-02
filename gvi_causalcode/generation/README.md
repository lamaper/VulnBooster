# 生成模块说明

这个目录存放基于大模型的漏洞代码生成流程，以及相关后处理和过滤脚本。

## 主要文件

- `config.py`：生成策略、模型参数、路径和过滤阈值配置
- `prompt_templates.py`：多种提示词模板，支持轻量纯提示词生成
- `chain_gen.py`：轻量生成主入口，直接通过 HTTP 调用 LLM API，不依赖 `langchain`
- `post_process.py`：提取生成代码、去注释、做基础清洗
- `post_analysis.py`：相似度分析和结果筛选
- `static_check/`：静态分析辅助脚本

## 运行前环境变量

运行前至少需要设置 API Key。默认推荐 Gemini：

```bash
export GEMINI_API_KEY="你的密钥"
```

也可以统一使用通用变量：

```bash
export LLM_API_KEY="你的密钥"
```

如果需要，可以覆盖模型名和模式：

```bash
export LLM_MODEL="gemini-2.0-flash"
export PROMPT_MODE="direct_generate"
```

## 当前推荐路线

如果你现在希望比原始 `VulScribeR` 更轻、更灵活，推荐优先使用：

- `direct_generate`：单轮直接生成，最快
- `pattern_then_generate`：先总结模式再生成，通常更稳

`cot_chain` 仍然保留，适合延续原本“多步分析再生成”的思路。

## 快速运行

在 `gvi_causalcode/generation/` 目录下执行：

```bash
/home/lamaper/miniconda3/envs/vulnbooster/bin/python chain_gen.py --prompt-mode direct_generate --limit 10
```

处理完成后继续执行：

```bash
/home/lamaper/miniconda3/envs/vulnbooster/bin/python post_process.py
/home/lamaper/miniconda3/envs/vulnbooster/bin/python post_analysis.py
```

## 结果管理原则

以下内容属于本地实验产物，原则上不进入 Git：

- 生成样本
- 过滤结果
- 相似度分析输出
- 静态分析过程产物
