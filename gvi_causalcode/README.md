# Code Layout

This directory contains the working codebase for the vulnerability detection project.

## Main Areas

- `train_bert/`: main training, evaluation wrappers, intervention generation, LineVul integration
- `generation/`: LLM-based vulnerable sample generation and post-processing
- `evaluation/`: original LineVul-related evaluation code and helper assets
- `preprocess-lstm/`: older preprocessing and disturbance-generation utilities
- `data/`: lightweight scripts and local dataset metadata
- `data_raw/`: raw extracted source samples, kept locally and ignored by git
- `utils/`: shared utilities from the original project

## Current Working Focus

The active path for this project is mainly:

1. `generation/`
2. `train_bert/`
3. `evaluation/linevul/`

## Repository Policy

- Keep code and lightweight metadata in git
- Keep datasets, generated artifacts, caches, logs, checkpoints, and experiment outputs out of git
- Keep secrets in environment variables instead of tracked config files
- Prefer relative paths or environment variables over machine-specific absolute paths
