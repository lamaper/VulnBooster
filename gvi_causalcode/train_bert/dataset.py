# -*- coding: utf-8 -*-

import os
import pickle, gzip
import random
import numpy
import copy

class Dataset(object):
    """通用的批处理数据集封装"""
    def __init__(self, xs=[], ys=[], raws=None, ids=None, idx2txt=[], txt2idx={},
                 vocab_size=5000, dtype=None):

        self.__dtype = dtype
        self.__vocab_size = vocab_size
        self.__idx2txt = idx2txt
        self.__txt2idx = txt2idx
        assert len(self.__idx2txt) == self.__vocab_size \
               and len(self.__txt2idx) == self.__vocab_size + 1
        self.__xs = []
        self.__raws = []
        self.__ys =[]
        self.__ids =[]
        
        if raws is None:
            assert len(xs) == len(ys)
            raws = [None for _ in ys]
        else:
            assert len(xs) == len(ys) and len(ys) == len(raws)
            
        if ids is None:
            ids = list(range(len(xs)))
        else:
            assert len(xs) == len(ids)
            
        for x, y, r, i in zip(xs, ys, raws, ids):
            self.__raws.append(r)
            self.__ys.append(y)
            self.__ids.append(i)
            self.__xs.append([])
            for t in x:
                if t >= self.__vocab_size:
                    self.__xs[-1].append('<unk>')
                else:
                    self.__xs[-1].append(self.__idx2txt[t])
                    
        self.__ys = numpy.asarray(self.__ys, dtype=self.__dtype['int'])
        self.__ids = numpy.asarray(self.__ids, dtype=self.__dtype['int'])
        self.__size = len(self.__raws)

        assert self.__size == len(self.__raws) \
               and len(self.__raws) == len(self.__xs) \
               and len(self.__xs) == len(self.__ys) \
               and len(self.__ys) == len(self.__ids)

        self.__epoch = None
        self.reset_epoch()

    def reset_epoch(self):
        self.__epoch = random.sample(range(self.__size), self.__size)

    def next_batch(self, batch_size=32):
        batch = {"x": [], "y": [], "raw":[], "id":[], "new_epoch": False}
        assert batch_size <= self.__size
        
        if len(self.__epoch) < batch_size:
            batch['new_epoch'] = True
            self.reset_epoch()
            
        idxs = self.__epoch[:batch_size]
        self.__epoch = self.__epoch[batch_size:]
        
        # 将 token list 拼接成字符串，供 transformer 分词器使用
        batch['x'] = copy.deepcopy([" ".join(self.__xs[i]) for i in idxs])
        batch['y'] = numpy.take(self.__ys, indices=idxs, axis=0)
        batch['id'] = numpy.take(self.__ids, indices=idxs, axis=0)
        batch['raw'] = copy.deepcopy([self.__raws[i] for i in idxs])
        return batch

    def get_size(self):
        return self.__size

    def get_rest_epoch_size(self):
        return len(self.__epoch)

def remove_tail_padding(token_idx_ndarray, pad_idx):
    """
    【已修复】：移除末尾的 pad_idx。修复了原代码中没有保留原序列顺序的 bug。
    """
    token_idx_list = list(token_idx_ndarray)
    # 从后往前找，找到第一个不是 pad_idx 的位置
    last_valid_idx = len(token_idx_list) - 1
    while last_valid_idx >= 0 and token_idx_list[last_valid_idx] == pad_idx:
        last_valid_idx -= 1
    
    # 截取有效部分，保持原顺序
    return token_idx_list[:last_valid_idx + 1]


class VulnDataset(object):
    """
    统一的漏洞数据集加载器，合并了原来重复的 OJ104 和 CodeChef 类。
    """
    def __init__(self, path='../dataset/data.pkl.gz', vocab_size=-1,
                 valid_ratio=0.1, dtype='32', adv_train_path=None, adv_train_size=None):
        # 默认将 valid_ratio 改为 0.1，保留更多数据用于训练

        self.__dtypes = self.__dtype(dtype)

        with gzip.open(path, "rb") as f:
            d = pickle.load(f)

        if vocab_size > 0:
            self.__idx2txt = d['idx2txt'][:vocab_size]
            self.__vocab_size = vocab_size
        else:
            self.__idx2txt = d['idx2txt']
            self.__vocab_size = len(self.__idx2txt)
            
        self.__txt2idx = {"<pad>": 0}
        for i, t in zip(range(self.__vocab_size), self.__idx2txt):
            self.__txt2idx[t] = i
            
        random.seed(666)
        
        # 安全处理：如果当前 pkl 中包含训练数据，才进行划分
        if 'x_tr' in d and len(d['x_tr']) > 0:
            idxs = random.sample(range(len(d['x_tr'])), len(d['x_tr']))
            n_valid = int(len(d['x_tr']) * valid_ratio)
            
            raw_dev, x_dev, y_dev, ids_dev = [], [], [], []
            for i in idxs[:n_valid]:
                raw_dev.append(d['raw_tr'][i])
                x_dev.append(d['x_tr'][i])
                y_dev.append(d['y_tr'][i])
                ids_dev.append(i)
                
            self.dev = Dataset(xs=x_dev, ys=y_dev, raws=raw_dev, ids=ids_dev,
                               idx2txt=self.__idx2txt,
                               txt2idx=self.__txt2idx,
                               vocab_size=self.__vocab_size,
                               dtype=self.__dtypes)
                               
            raw_tr, x_tr, y_tr, ids_tr = [], [], [],[]
            for i in idxs[n_valid:]:
                raw_tr.append(d['raw_tr'][i])
                x_tr.append(d['x_tr'][i])
                y_tr.append(d['y_tr'][i])
                ids_tr.append(i)
                
            # 支持对抗训练数据加载
            if adv_train_path is not None:
                raw_tr = None # 对抗样本没有原始文本
                with gzip.open(adv_train_path, "rb") as f:
                    tmp_d = pickle.load(f)
                    adv_x = tmp_d["adv_x"]
                    adv_y = tmp_d["adv_label"]
                if adv_train_size is not None:
                    print("adv_train_size:", adv_train_size)
                    tmp_idxs = random.sample(range(len(adv_x)), adv_train_size)
                    adv_x = [adv_x[i] for i in tmp_idxs]
                    adv_y = [adv_y[i] for i in tmp_idxs]
                    
                for _x, _y in zip(adv_x, adv_y):
                    # 如果是第一个添加的对抗样本且之前没数据，做个保护
                    new_id = ids_tr[-1] + 1 if ids_tr else 0
                    ids_tr.append(new_id)
                    x_tr.append(remove_tail_padding(_x, 0))
                    y_tr.append(_y)
                print("[Adversarial Training] adversarial sample number: %d" % len(adv_x), flush=True)
                
            self.train = Dataset(xs=x_tr, ys=y_tr, raws=raw_tr, ids=ids_tr,
                                 idx2txt=self.__idx2txt,
                                 txt2idx=self.__txt2idx,
                                 vocab_size=self.__vocab_size,
                                 dtype=self.__dtypes)
        else:
            # 如果仅仅用作测试集（比如 devign），不包含训练数据
            self.train = None
            self.dev = None

        # 加载测试集
        if 'x_te' in d and len(d['x_te']) > 0:
            self.test = Dataset(xs=d['x_te'],
                                ys=d['y_te'],
                                raws=d['raw_te'],
                                idx2txt=self.__idx2txt,
                                txt2idx=self.__txt2idx,
                                vocab_size=self.__vocab_size,
                                dtype=self.__dtypes)
        else:
             self.test = None

    def __dtype(self, dtype='32'):
        assert dtype in['16', '32', '64']
        if dtype == '16':
            return {'fp': numpy.float16, 'int': numpy.int16}
        elif dtype == '32':
            return {'fp': numpy.float32, 'int': numpy.int32}
        elif dtype == '64':
            return {'fp': numpy.float64, 'int': numpy.int64}

    def get_dtype(self): return self.__dtypes
    def get_vocab_size(self): return self.__vocab_size
    def get_idx2txt(self): return copy.deepcopy(self.__idx2txt)
    def get_txt2idx(self): return copy.deepcopy(self.__txt2idx)

    def vocab2idx(self, vocab):
        if vocab in self.__txt2idx.keys(): return self.__txt2idx[vocab]
        else: return self.__txt2idx['<unk>']

    def idx2vocab(self, idx):
        if 0 <= idx < len(self.__idx2txt): return self.__idx2txt[idx]
        else: return '<unk>'

# 为了兼容 run.py 等已有代码中的调用，提供别名映射
OJ104 = VulnDataset
CodeChef = VulnDataset

if __name__ == "__main__":
    pass