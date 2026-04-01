# -*- coding: utf-8 -*-

import os, sys
import pickle, gzip
import random
import tqdm

def split(data, test_ratio=0.1, seed=1726): # 改为更合理的 10% 划分，并统一随机种子
    """
    功能：将数据集划分为训练集和测试集/验证集。
    增强：增加了对无效数据（空代码、None）的过滤机制，防止后续处理崩溃。
    """
    random.seed(seed)
    
    # 【修复】：过滤掉处理失败产生的 None 数据或空代码
    valid_indices = []
    for i, (raw_code, label) in enumerate(zip(data['raw'], data['labels'])):
        if raw_code is not None and len(raw_code) > 0 and label is not None:
            valid_indices.append(i)
            
    n_valid = len(valid_indices)
    print(f"数据清洗完毕：共保留 {n_valid} 条有效代码记录。")
    
    n_test = int(test_ratio * n_valid)
    # 对有效索引进行洗牌
    rand_idx = random.sample(valid_indices, n_valid)
    
    test = {"raw": [], "labels": [], "uids": [], "index": []}
    train = {"raw":[], "labels": [], "uids": [], "index":[]}
    
    # 构建测试集/验证集
    for i in rand_idx[:n_test]:
        test['raw'].append(data['raw'][i])
        test['labels'].append(data['labels'][i])
        # 增加容错：如果 uids 是 None，给个空字典
        test['uids'].append(data['uids'][i] if data['uids'][i] is not None else {})
        test['index'].append(data['index'][i])
        
    # 构建训练集
    for i in rand_idx[n_test:]:
        train['raw'].append(data['raw'][i])
        train['labels'].append(data['labels'][i])
        train['uids'].append(data['uids'][i] if data['uids'][i] is not None else {})
        train['index'].append(data['index'][i])
        
    return train, test


def build_vocab(codes):
    """
    功能：统计词频，将特定字面量泛化，构建词汇表。
    """
    vocab_cnt = {"<str>": 0, "<char>": 0, "<int>": 0, "<fp>": 0}
    for c in tqdm.tqdm(codes, desc="Building Vocabulary"):
        for t in c:
            if t[0] == '"' and t[-1] == '"':
                vocab_cnt["<str>"] += 1
            elif t[0] == "'" and t[-1] == "'":
                vocab_cnt["<char>"] += 1
            elif t[0] in "0123456789.":
                if 'e' in t.lower():
                    vocab_cnt["<fp>"] += 1
                elif '.' in t:
                    if t == '.':
                        if t not in vocab_cnt.keys():
                            vocab_cnt[t] = 0
                        vocab_cnt[t] += 1
                    else:
                        vocab_cnt["<fp>"] += 1
                else:
                    vocab_cnt["<int>"] += 1
            elif t in vocab_cnt.keys():
                vocab_cnt[t] += 1
            else:
                vocab_cnt[t] = 1
                
    vocab_cnt = sorted(vocab_cnt.items(), key=lambda x: x[1], reverse=True)
    idx2txt = ["<unk>"] +[it[0] for it in vocab_cnt]
    
    txt2idx = {}
    for idx in range(len(idx2txt)):
        txt2idx[idx2txt[idx]] = idx
    return idx2txt, txt2idx


def text2index(codes, txt2idx):
    """
    功能：将代码字符串序列转换为模型可读的整数 ID 序列。
    修复：删除了原作者诡异的 continue 语句，保证索引和原序列 1:1 绝对对齐。
    """
    codes_idx =[]
    for c in codes:
        codes_idx.append([])
        for t in c:
            if t[0] == '"' and t[-1] == '"':
                codes_idx[-1].append(txt2idx["<str>"])
            elif t[0] == "'" and t[-1] == "'":
                codes_idx[-1].append(txt2idx["<char>"])
            elif t[0] in "0123456789.":
                if 'e' in t.lower():
                    codes_idx[-1].append(txt2idx["<fp>"])
                elif '.' in t:
                    if t == '.':
                        # 【修复核心】：去掉了 continue，老老实实把 '.' 的 ID 存进去
                        codes_idx[-1].append(txt2idx.get(t, txt2idx["<unk>"]))
                    else:
                        codes_idx[-1].append(txt2idx["<fp>"])
                else:
                    codes_idx[-1].append(txt2idx["<int>"])
            elif t in txt2idx.keys():
                codes_idx[-1].append(txt2idx[t])
            else:
                codes_idx[-1].append(txt2idx["<unk>"])
    return codes_idx


if __name__ == "__main__":
    # 因为我们现在通过 run.py 来统筹整个预处理流程，这里的代码仅作占位。
    # 实际的调用请运行 run.py
    print("Please run run.py to start the dataset building pipeline.")
    pass