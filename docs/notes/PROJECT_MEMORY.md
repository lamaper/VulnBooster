# Project Memory

Last updated: 2026-04-01

## Project Goal

Project name:

- Based on data augmentation for source code vulnerability detection

Current high-level idea:

- Combine `CausalCode` and `VulScribeR`
- Use `VulScribeR`-style augmentation to improve vulnerable sample quantity and diversity
- Use `CausalCode` to reduce spurious correlations and improve robustness/generalization

## Papers

### 1. CausalCode

Paper:

- `A Causal Learning Framework for Enhancing Robustness of Source Code Models`
- DOI: `10.1145/3729387`

Core idea:

- Source code models often learn spurious correlations instead of causal features
- Generate intervention examples to break spurious correlations
- Use representation alignment / causal regularization to learn invariant features
- Improve robustness against perturbation and cross-domain generalization

What matters for this repo:

- Token rename and dead-code insertion are used as intervention-style augmentations
- Training uses multi-domain batches: original data plus intervention data
- A causal alignment loss is added on top of ERM loss

### 2. VulScribeR

Paper:

- `VulScribeR: Exploring RAG-based Vulnerability Augmentation with LLMs`
- DOI: `10.1145/3760775`

Core idea:

- Use retrieval-augmented generation to create higher-quality vulnerable samples
- Retrieval provides vulnerability patterns, similar cases, or supporting context to the LLM
- Main value is improving vulnerable sample quality, controllability, and diversity

What matters for this project:

- It is more suitable for "data expansion" than for direct causal alignment
- It should be placed before CausalCode training in the overall pipeline

## Current Repository Reality

This repo is not yet a true `VulScribeR + CausalCode` implementation.

What it currently is:

- A `CausalCode + LineVul` training pipeline
- Plus an LLM-based vulnerable code generation pipeline
- Plus post-generation filtering based on similarity and static analysis

Important conclusion:

- The generation pipeline is closer to generic vulnerable sample generation or GVI-style augmentation
- It is not yet a strict `VulScribeR`-style retrieval-augmented generation pipeline

## Important Code Locations

### CausalCode training

Main cross-dataset training entry:

- `gvi_causalcode/train_bert/run.py`

Important behaviors:

- Loads original and intervention domains together
- Applies causal alignment loss
- Evaluates on cross-dataset test data

Key details:

- Multi-domain data loading: `gvi_causalcode/train_bert/run.py`
- Causal alignment loss: `gvi_causalcode/train_bert/run.py`
- Cross-dataset train/test split logic: `gvi_causalcode/train_bert/run.py`

### Intervention data generation

Main file:

- `gvi_causalcode/train_bert/attacker4simple.py`

Implemented intervention styles:

- Token rename
- Dead-code insertion

Purpose:

- Generate paired intervention samples for CausalCode training

### Dataset wrapper

Main file:

- `gvi_causalcode/train_bert/dataset.py`

Important behavior:

- Batch sampling depends on sample `id`
- This directly affects whether multi-domain alignment works

### Current LLM generation pipeline

Main files:

- `gvi_causalcode/generation/config.py`
- `gvi_causalcode/generation/chain_gen.py`
- `gvi_causalcode/generation/post_process.py`
- `gvi_causalcode/generation/post_analysis.py`

Current behavior:

- Take vulnerable seed functions
- Run a multi-step prompt chain
- Generate new vulnerable functions
- Clean code blocks
- Filter using similarity search
- Optionally use static analysis outputs

Important conclusion:

- Retrieval is used after generation for filtering
- Retrieval is not yet injected into prompting as generation context
- Therefore this is not yet a full RAG generation design

## Most Important Constraint

Current `CausalCode` training requires aligned paired samples across domains.

Evidence in code:

- `gvi_causalcode/train_bert/run.py` asserts that batch `id` values from two domains must match

Practical meaning:

- Freely generated new vulnerable samples from a VulScribeR-like pipeline cannot be directly used as the second domain for current causal alignment training
- If new samples do not preserve original sample ids and one-to-one pairing, current training code will fail or become conceptually invalid

This is the most important integration constraint in the whole project.

## Best Integration Strategy

Recommended order:

1. Use `VulScribeR`-style generation to produce more high-quality vulnerable samples
2. Merge validated generated vulnerable samples into the training pool
3. Run `CausalCode` intervention generation on the resulting dataset
4. Train with original plus paired intervention domains
5. Evaluate on cross-dataset settings such as `ReVeal -> Devign`

Interpretation:

- `VulScribeR` solves sample quantity and diversity
- `CausalCode` solves robustness and spurious correlation

## What Not To Do

Do not do this directly:

- Treat free-form generated vulnerable samples as the second CausalCode domain without pairing

Why:

- Current code requires aligned ids
- Current loss is designed around paired multi-domain examples

If we ever want to directly inject unpaired VulScribeR samples into causal training, we would need one of these:

- Redesign the training loss
- Build sample matching logic
- Convert generated samples into paired augmentations for each original sample

## Recommended Project Roadmap

### Phase 1. Memory and repo stabilization

- Save key findings in markdown
- Standardize repository layout
- Clean git tracking
- Separate code, data, generated artifacts, checkpoints, and notes

### Phase 2. Environment and reproducibility

- Build a clean Ubuntu training environment
- Create dependency manifests
- Replace hard-coded paths and keys with environment variables
- Add one-command scripts for train, generate, filter, and evaluate

### Phase 3. Real VulScribeR-style augmentation

Build a true RAG generation pipeline:

- Build retrieval corpus from vulnerable samples and metadata
- Retrieve similar vulnerability patterns before generation
- Feed retrieved cases into prompts
- Generate candidate vulnerable functions
- Filter with similarity, static analysis, and deduplication

### Phase 4. CausalCode integration

- Merge filtered vulnerable data into the training set
- Generate paired intervention domains
- Keep current multi-domain causal alignment training

### Phase 5. Experiments

Suggested experiment groups:

- Baseline LineVul
- LineVul + current CausalCode
- LineVul + VulScribeR-style augmentation
- LineVul + VulScribeR-style augmentation + CausalCode

Suggested metrics:

- Accuracy
- Precision
- Recall
- F1
- Cross-dataset generalization
- Robustness under perturbation

## Current Problems Found In The Repo

### 1. Environment dependencies are not ready in the current terminal

At the time of analysis, the current environment was missing several important packages:

- `torch`
- `transformers`
- `langchain_openai`
- `langchain_classic`
- `langchain_community`
- `chromadb`
- `wandb`
- `pandas`
- `matplotlib`

Meaning:

- The codebase is not currently runnable in this shell without environment setup
- This is fine for now if your real workflow is in WSL or later on Ubuntu

### 2. Hard-coded API key in repo

Problem file:

- `gvi_causalcode/generation/config.py`

Problem:

- Gemini API key is hard-coded in the repository

Required fix later:

- Move to environment variables
- Remove secrets from git history if needed

### 3. Hard-coded checkpoint path

Problem file:

- `gvi_causalcode/train_bert/attacker4simple.py`

Problem:

- It expects a pre-trained LineVul checkpoint at a fixed path
- That checkpoint does not currently exist in this repo snapshot

Meaning:

- Intervention generation will fail until the model is trained or the path is fixed

### 4. A bug in `graphcodebert_train-dg.py`

Problem file:

- `gvi_causalcode/train_bert/graphcodebert_train-dg.py`

Problem:

- Final call passes `saving_path=...` into `trainEpochs(...)`, but the function signature shown in the file does not accept that argument

Meaning:

- This script likely crashes if run directly

### 5. Confusing metric naming

Problem file:

- `gvi_causalcode/train_bert/bert_eval.py`

Problem:

- The function comment mentions Accuracy, but the function actually returns `F1 * 100`

Meaning:

- The logic can still work
- But naming is confusing and should be cleaned up later

## Current Data Status

From the local processed datasets:

- `ReVeal`: `18188` train, `4546` test
- `Devign`: `21855` train, `5463` test

This is enough to support real experiments after environment cleanup.

## WSL And Ubuntu Advice

Current habit:

- You usually run this code in WSL

Long-term target:

- Final training should run on physical Ubuntu machine

Advice:

- For actual training, prefer native Linux filesystem paths instead of `/mnt/d/...`
- On Ubuntu, keep project under a Linux path like `~/projects/VulnBooster`
- Avoid training directly on Windows-mounted disks when possible
- Keep data, checkpoints, and generated outputs outside git tracking

For your hardware:

- RTX `4060 Laptop` can run this project, but batch sizes and sequence lengths should be conservative
- Start with the existing small batch sizes first

## Immediate Next Steps After This File

Planned next major tasks:

1. Standardize code structure and directories with minimal logic changes
2. Clean the git repository and remove large/generated/unnecessary tracked content
3. Start real project implementation work

When resuming later, start from:

- First read this file
- Then inspect `gvi_causalcode/train_bert/`
- Then inspect `gvi_causalcode/generation/`

## Short Resume Summary

If context is lost, remember these five points first:

1. The repo currently implements `CausalCode + LineVul`, not a full VulScribeR pipeline
2. Current LLM generation is generation-first plus filtering, not retrieval-augmented prompting
3. Current CausalCode training requires paired aligned sample ids across domains
4. Best integration is `VulScribeR-style augmentation first`, `CausalCode paired training second`
5. Before real training, fix environment, secrets, paths, and repo structure
