#!/bin/bash
python linevul_main.py \
  --model_name=./saved_models/reveal_model/checkpoint-best-f1/microsoft/codebert-base \
  --output_dir=./saved_models/reveal_model \
  --model_type=roberta \
  --tokenizer_name=microsoft/codebert-base \
  --model_name_or_path=microsoft/codebert-base \
  --do_test \
  --test_data_file=devign_test.csv \
  --block_size=512 \
  --eval_batch_size=4 \
  --seed=123456