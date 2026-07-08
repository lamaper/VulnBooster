# VulnBooster

`VulnBooster` is a research-oriented pipeline for source code vulnerability detection with:

- feature extraction and slicing,
- targeted data augmentation,
- iterative fine-tuning,
- false-negative feedback loops.

The repo contains:

- legacy scripts in `code/`,
- the original Joern slice program in `slice/slice.sc`,
- a refactored package in `src/vulnbooster/`,
- research notes in `docs/`.

## Environment

Use `uv`:

```bash
uv venv .venv
uv pip install --python .venv/bin/python -e .
```

Install LLM dependencies when you need pre-filtering, fusion, or augmentation:

```bash
uv pip install --python .venv/bin/python -e ".[llm]"
```

Install training dependencies when you need fine-tuning:

```bash
uv pip install --python .venv/bin/python -e ".[train]"
```

Install both when you need the full line-slicer and augmentation workflow:

```bash
uv pip install --python .venv/bin/python -e ".[llm,train]"
```

## Quick Start

Inspect the research/task understanding:

```bash
sed -n '1,240p' docs/project_analysis.md
```

Show the new CLI:

```bash
uv run vulnbooster --help
```

Build a local smoke dataset and inspect environment health:

```bash
PYTHONPATH=src .venv/bin/python -m vulnbooster.cli build-smoke --config configs/smoke.toml
PYTHONPATH=src .venv/bin/python -m vulnbooster.cli doctor --config configs/smoke.toml
```
