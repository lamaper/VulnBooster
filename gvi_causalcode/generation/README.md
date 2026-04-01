# Generation Notes

This directory contains the LLM-based vulnerable sample generation pipeline and its post-processing utilities.

## Files

- `config.py`: tracked defaults and prompt configuration, reads secrets from environment variables
- `chain_gen.py`: main multi-step generation entry
- `post_process.py`: extracts generated code and removes comments
- `post_analysis.py`: similarity analysis on generated outputs
- `static_check/`: helper scripts for static-analysis based filtering

## Environment

Set the Gemini key before running generation:

```bash
export GEMINI_API_KEY="your_key_here"
```

You can also override the model:

```bash
export GEMINI_MODEL="gemini-3-flash-preview"
```

## Output Policy

Generated samples, filtering results, similarity outputs, and static-analysis artifacts are local experiment outputs and should stay out of git.
