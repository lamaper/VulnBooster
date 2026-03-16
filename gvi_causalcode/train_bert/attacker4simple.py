# -*- coding: utf-8 -*-

import copy
import os, sys, time
import pickle, gzip
import argparse
import random
import numpy
import torch
import torch.nn as nn

from dataset import OJ104, CodeChef
from modifier import TokenModifier, InsModifier, get_batched_data
import build_dataset as bd

# =================================================================================
# 本文核心：CausalCode 框架数据增强生成器 (变量名替换)
# =================================================================================
class CausalCodeToken(object):
    def __init__(self, dataset, symtab, classifier):
        self.txt2idx = dataset.get_txt2idx()
        self.idx2txt = dataset.get_idx2txt()
        self.tokenM = TokenModifier(classifier=classifier,
                                    loss=torch.nn.CrossEntropyLoss(),
                                    uids=symtab['all'],
                                    txt2idx=self.txt2idx,
                                    idx2txt=self.idx2txt)
        self.cl = classifier
        self.d = dataset
        self.syms = symtab

    def gen_one(self, x_raw, y, uids, n_candidate=5, n_iter=20):
        # 【极其关键的修复 1】：防空转保护
        if not uids or len(uids) == 0:
            return [x_raw], 0

        iter_cnt = 0
        n_stop = 0
        stop_iter = random.randint(3, n_iter)
        
        while iter_cnt < n_iter:
            keys = list(uids.keys())
            modified_in_pass = False # 【修复 2】：死循环防抱死锁
            
            for k in keys:
                if iter_cnt >= n_iter: break
                if n_stop >= len(uids): break
                
                if k in self.tokenM.forbidden_uid:
                    n_stop += 1
                    continue
                    
                assert not k.startswith('Ġ')
                Gk = 'Ġ' + k
                Gk_idx = self.cl.tokenizer.convert_tokens_to_ids(Gk)
                if Gk_idx == self.cl.tokenizer.unk_token_id:
                    n_stop += 1 # 【修复 3】：填补作者遗漏的计数器
                    continue
                    
                iter_cnt += 1
                new_x_raw, new_x_uid = self.tokenM.rename_uid(x_raw, y, k, n_candidate)
                if new_x_raw is None:
                    n_stop += 1
                    continue
                    
                modified_in_pass = True # 标记为：本轮确实干了活
                
                if iter_cnt == stop_iter:
                    new_prob_idx = random.randint(0, len(new_x_raw) - 1)
                    x_raw = new_x_raw[new_prob_idx]
                    return [x_raw], 1

                new_prob_idx = random.randint(0, len(new_x_raw) - 1)
                x_raw = new_x_raw[new_prob_idx]
                uids[new_x_uid[new_prob_idx]] = uids.pop(k)
                n_stop = 0 # 成功替换，重置错误计数
                
            # 【极其关键的修复 4】：如果一整圈遍历下来，全部命中 continue 没有任何实质修改
            # 直接打破外层的 while，阻止无限循环发生！
            if not modified_in_pass:
                break
                
        return [x_raw], 0

    def gen_all(self, n_candidate=5, n_iter=40, res_save=None):
        n_succ = 0
        st_time = time.time()
        total_time = 0
        
        base_dir = os.path.dirname(os.path.dirname(res_save))
        origin_path = os.path.join(base_dir, "origin_s", "data.pkl.gz")
        with gzip.open(origin_path, "rb") as f:
            dd = pickle.load(f)
            
        print("🚀 开始生成基于梯度对抗的干预样本...")
        total_samples = self.d.train.get_size()
        
        from tqdm import tqdm
        for i in tqdm(range(total_samples), desc="生成变异数据"):
            b = self.d.train.next_batch(1)
            x_raw, typ = self.gen_one(b['raw'][0], b['y'][0], self.syms['tr'][b['id'][0]], n_candidate, n_iter)
            
            while len(x_raw) == 1:
                x_raw = x_raw[0]
            dd['x_tr'][b['id'][0]] = bd.text2index([x_raw], self.txt2idx)[0]
            dd['raw_tr'][b['id'][0]] = x_raw
            
        os.makedirs(os.path.dirname(res_save), exist_ok=True)
        if res_save is not None:
            print(f"💾 正在保存生成数据至: {res_save}")
            with gzip.open(res_save, "wb") as f:
                pickle.dump(dd, f)
        print(f"🎉 [Task Done] 总耗时: {time.time() - st_time:.1f} 秒")


class CausalCodeDeadCode(object):
    # 这个类的逻辑是基于插桩点插入的，天生带有 n_stop += 1 和 break 机制，不会死循环。
    # 为了防止篇幅超限，我省略这里的覆写。你之前修改后的版本是安全的。
    def __init__(self, dataset, instab, classifier):
        self.txt2idx = dataset.get_txt2idx()
        self.idx2txt = dataset.get_idx2txt()
        self.insM = InsModifier(classifier=classifier, txt2idx=self.txt2idx, idx2txt=self.idx2txt)
        self.d = dataset
        self.inss = instab

    def attack(self, x_raw, y, poses, n_candidate=5, n_iter=40):
        self.insM.initInsertDict(poses)
        iter_cnt = 0
        n_stop = 0
        stop_iter = random.randint(3, n_iter)
        while iter_cnt < n_iter:
            iter_cnt += 1
            n_could_del = self.insM.insertDict["count"]
            new_x_raw_del, new_insertDict_del = self.insM.remove(x_raw, n_could_del)
            new_x_raw_add, new_insertDict_add = self.insM.insert(x_raw, n_candidate - n_could_del)
            new_x_raw = new_x_raw_del + new_x_raw_add
            new_insertDict = new_insertDict_del + new_insertDict_add
            
            if not new_x_raw:
                n_stop += 1
                if n_stop > 10: break # 加入防死循环保护
                continue
                
            if iter_cnt == stop_iter:
                return True, [random.choice(new_x_raw)], 1
            new_idx = random.randint(0, len(new_x_raw) - 1)
            self.insM.insertDict = new_insertDict[new_idx]
        return False,[x_raw], 2

    def gen_all(self, n_candidate=5, n_iter=40, res_save=None):
        base_dir = os.path.dirname(os.path.dirname(res_save))
        origin_path = os.path.join(base_dir, "origin_s", "data.pkl.gz")
        with gzip.open(origin_path, "rb") as f:
            dd = pickle.load(f)
        total_samples = self.d.train.get_size()
        
        from tqdm import tqdm
        for i in tqdm(range(total_samples), desc="生成死代码变异"):
            b = self.d.train.next_batch(1)
            _, x_raw, _ = self.attack(b['raw'][0], b['y'][0], self.inss['stmt_tr'][b['id'][0]], n_candidate, n_iter)
            while len(x_raw) == 1:
                x_raw = x_raw[0]
            dd['x_tr'][b['id'][0]] = bd.text2index([x_raw], self.txt2idx)[0]
            dd['raw_tr'][b['id'][0]] = x_raw
            
        os.makedirs(os.path.dirname(res_save), exist_ok=True)
        with gzip.open(res_save, "wb") as f:
            pickle.dump(dd, f)


# =================================================================================
# 控制台：参数解析与统一执行总入口
# =================================================================================
if __name__ == "__main__":

    parser = argparse.ArgumentParser()
    parser.add_argument('--gpu', default="0")
    parser.add_argument('--enhance_method', default='CausalCode')
    parser.add_argument('--model_name', type=str, default="linevul") 
    parser.add_argument('--task', default='reveal') 
    parser.add_argument('--attack_type', default='token')
    
    # 无关参数保留防止报错
    parser.add_argument('--data', type=str, default=None)
    parser.add_argument('--iter_select', type=int, default=30)
    parser.add_argument('--index', type=int, default=0)
    parser.add_argument('--wandb_name', type=str, default='default')
    parser.add_argument('--data_name', type=str, default='')
    parser.add_argument('--begin_epoch', type=int, default=15)
    opt = parser.parse_args()

    root = '../data/'
    os.environ["CUDA_VISIBLE_DEVICES"] = opt.gpu
    device = torch.device("cuda:" + opt.gpu if torch.cuda.is_available() else "cpu")

    origin_data_path = os.path.join(root, opt.task, 'dataset', 'origin_s', 'data.pkl.gz')
    
    if opt.task == 'reveal':
        n_class = 2
        original_dataset = CodeChef(path=origin_data_path)
    else:
        raise ValueError("仅支持 reveal 测试！")
        
    rand_seed = 1726
    torch.manual_seed(rand_seed)
    random.seed(rand_seed)
    numpy.random.seed(rand_seed)

    opt.data_name = f"{opt.model_name}-{opt.enhance_method}-{opt.attack_type}"
    save_path = os.path.join(root, opt.task, "dataset", opt.data_name)
    os.makedirs(save_path, exist_ok=True)

    from linevul_wrapper import LineVulClassifier
    class DummyArgs:
        def __init__(self):
            self.model_name_or_path = "microsoft/codebert-base"
            self.block_size = 512
            self.use_word_level_tokenizer = False
            self.use_non_pretrained_model = False
            self.device = device
    linevul_args = DummyArgs()

    origin_dir = os.path.join(root, opt.task, 'dataset', 'origin_s')
    with gzip.open(os.path.join(origin_dir, "oj_uid.pkl.gz"), "rb") as f:
        symtab = pickle.load(f)
    with gzip.open(os.path.join(origin_dir, "oj_inspos.pkl.gz"), "rb") as f:
        instab = pickle.load(f)

    if opt.enhance_method == 'CausalCode':
        # 加载初训模型
        trained_model_path = "../evaluation/linevul/code/linevul/saved_models/reveal_model/checkpoint-best-f1/microsoft/codebert-base"
        
        if not os.path.exists(trained_model_path):
            print(f"❌ 严重错误: 找不到预训练模型 {trained_model_path}")
            sys.exit(1)

        print(f"✅ 成功加载用于提供梯度的向导模型: {trained_model_path}")
        classifier = LineVulClassifier(model_path="microsoft/codebert-base",
                                    num_labels=n_class,
                                    device=device,
                                    args=linevul_args).to(device)
        classifier.model.load_state_dict(torch.load(trained_model_path, map_location=device))
        classifier.eval() 

        if opt.attack_type == 'dead_code':
            print(">>> 开始生成 CausalCode 死代码干预数据...")
            atk = CausalCodeDeadCode(original_dataset, instab, classifier)
            atk.gen_all(5, 30, res_save=os.path.join(save_path, "data.pkl.gz"))
            
        elif opt.attack_type == 'token':
            print(">>> 开始生成 CausalCode 变量名干预数据...")
            gen = CausalCodeToken(original_dataset, symtab, classifier)
            gen.gen_all(5, 30, res_save=os.path.join(save_path, "data.pkl.gz"))