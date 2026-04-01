# VulnBooster

This repository is the working project space for the vulnerability detection study based on data augmentation.

## Repository Layout

- `gvi_causalcode/`: main codebase used for generation, preprocessing, training, and evaluation
- `docs/`: long-lived notes and local reference material

## What Stays In Git

- source code
- lightweight scripts
- project notes that help the team keep context
- small documentation files

## What Stays Local Only

- raw datasets
- generated samples and static-analysis outputs
- tokenizer files, checkpoints, logs, caches, and experiment artifacts
- local paper PDFs
- secrets such as API keys

## Current Working Path

For the current project plan, the main flow is:

1. `gvi_causalcode/generation/`
2. `gvi_causalcode/train_bert/`
3. `gvi_causalcode/evaluation/linevul/`

## Notes

- The long-term project memory is kept in `docs/notes/PROJECT_MEMORY.md`.
- This repo is being cleaned so it can move more smoothly from WSL development to Ubuntu training.
