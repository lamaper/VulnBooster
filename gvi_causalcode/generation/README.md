# 生成模块说明

这个目录存放基于大模型的漏洞代码生成流程，以及相关后处理和过滤脚本。

## 主要文件

- `config.py`：生成策略、模型参数、路径和过滤阈值配置
- `prompt_templates.py`：多种提示词模板，支持轻量纯提示词生成
- `chain_gen.py`：轻量生成主入口，直接通过 HTTP 调用 OpenAI-compatible API，不依赖 `langchain`
- `post_process.py`：提取生成代码、去注释、做基础清洗，并接入语法检查和 `semgrep` 风格过滤
- `post_analysis.py`：相似度分析和结果筛选
- `static_check/`：静态分析辅助脚本

## 运行前环境变量

运行前至少需要设置 API Key。当前默认按 OpenAI-compatible 接口组织，推荐直接兼容 `DeepSeek`：

```bash
export OPENAI_API_KEY="你的密钥"
```

也可以统一使用通用变量：

```bash
export LLM_API_KEY="你的密钥"
```

如果需要，可以覆盖模型名和模式：

```bash
export LLM_BASE_URL="https://api.deepseek.com/v1"
export LLM_MODEL="deepseek-chat"
export PROMPT_MODE="pattern_generate_repair"
```

## 当前推荐路线

如果你现在希望比原始 `VulScribeR` 更轻、更灵活，推荐优先使用：

- `pattern_generate_repair`：先抽模式，再生成，再自检重写，最符合当前项目主线
- `pattern_then_generate`：先总结模式再生成，通常更稳
- `direct_generate`：单轮直接生成，最快，适合做对照实验

`cot_chain` 仍然保留，适合延续原本“多步分析再生成”的思路。

## 当前默认轻量过滤链

生成后建议按这个顺序走：

1. `post_process.py` 提取代码块和基础清洗
2. `gcc/clang -fsyntax-only` 做语法检查
3. `semgrep` 风格规则做漏洞模式过滤
4. `post_analysis.py` 做 embedding 相似度过滤

说明：

- 当前语法检查默认自动优先找 `clang`，找不到时回退到 `gcc`
- `semgrep` 如果本机没有安装，会自动跳过，不会阻塞流程
- 静态检查报告会输出到 `*_result/static_check_report.json`

## 快速运行

在 `gvi_causalcode/generation/` 目录下执行：

```bash
/home/lamaper/miniconda3/envs/vulnbooster/bin/python chain_gen.py --prompt-mode pattern_generate_repair --limit 10
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
