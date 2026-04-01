# -*- coding: utf-8 -*-

import os, sys
import pickle, gzip
import random
import tqdm

def split(data, test_ratio=0.2, seed=666):
    random.seed(seed)
    
    # 【修复】：过滤掉处理失败产生的 None 数据
    valid_indices =[i for i, x in enumerate(data['raw']) if x is not None]
    n_valid = len(valid_indices)
    
    n_test = int(test_ratio * n_valid)
    rand_idx = random.sample(valid_indices, n_valid)
    
    test = {"raw":[], "labels": [], "uids": [], "index":[]}
    train = {"raw": [], "labels":[], "uids": [], "index":[]}
    
    for i in rand_idx[:n_test]:
        test['raw'].append(data['raw'][i])
        test['labels'].append(data['labels'][i])
        test['uids'].append(data['uids'][i])  
        test['index'].append(data['index'][i])
        
    for i in rand_idx[n_test:]:
        train['raw'].append(data['raw'][i])
        train['labels'].append(data['labels'][i])
        train['uids'].append(data['uids'][i])
        train['index'].append(data['index'][i])
        
    return train, test

def build_vocab(codes):
    vocab_cnt = {"<str>": 0, "<char>": 0, "<int>": 0, "<fp>": 0}
    for c in tqdm.tqdm(codes, desc="Building Vocab"):
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
    idx2txt = ["<unk>"] + [it[0] for it in vocab_cnt]
    txt2idx = {}
    for idx in range(len(idx2txt)):
        txt2idx[idx2txt[idx]] = idx
    return idx2txt, txt2idx

def text2index(codes, txt2idx):
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
                        codes_idx[-1].append(txt2idx[t])
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
    pass # 预留入口，实际主要通过 main.py 调用