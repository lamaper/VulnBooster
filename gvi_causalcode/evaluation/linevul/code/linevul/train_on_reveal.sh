#!/bin/bash
python linevul_main.py \
  --model_name=microsoft/codebert-base \
  --output_dir=./saved_models/reveal_model \
  --model_type=roberta \
  --tokenizer_name=microsoft/codebert-base \
  --model_name_or_path=microsoft/codebert-base \
  --do_train \
  --train_data_file=reveal_train.csv \
  --eval_data_file=reveal_valid.csv \
  --epochs=10 \
  --block_size=512 \
  --train_batch_size=4 \
  --eval_batch_size=4 \
  --learning_rate=2e-5 \
  --max_grad_norm=1.0 \
  --evaluate_during_training \
  --seed=123456