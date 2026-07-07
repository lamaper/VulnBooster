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

## Quick Start

Inspect the research/task understanding:

```bash
sed -n '1,240p' docs/project_analysis.md
```

Show the new CLI:

```bash
uv run vulnbooster --help
```
