# -*- coding: utf-8 -*-

import argparse
import os
import torch
import numpy as np
from sklearn.metrics import accuracy_score, precision_score, recall_score, f1_score

# 导入我们为 LineVul 专门写的包装器
from linevul_wrapper import LineVulClassifier

def adjust_learning_rate(optimizer, decay_rate=0.8):
    for param_group in optimizer.param_groups:
        param_group['lr'] = param_group['lr'] * decay_rate

def evaluate(classifier, dataset, device, batch_size=16):
    """
    核心评估函数：不仅计算 Accuracy，还计算 P, R, F1 (应对不平衡的漏洞数据)。
    返回值：Accuracy (为了兼容 run.py 的早期停止逻辑，返回 Acc 的百分比格式)
    """
    classifier = classifier.to(device)
    classifier.eval()
    
    all_preds = []
    all_trues =[]
    
    while True:
        batch = dataset.next_batch(batch_size)
        if batch['new_epoch']:
            break
            
        with torch.no_grad():
            # LineVulClassifier.run_batch() 会返回拼接好的 [1-p, p] logits
            outputs = classifier.run_batch(batch['x'])
            
            labels = batch['y']
            # 取概率较大的一维作为预测结果
            p_labels = torch.argmax(outputs, dim=1).cpu().numpy()
            
            all_preds.extend(p_labels)
            all_trues.extend(labels)

    all_preds = np.array(all_preds)
    all_trues = np.array(all_trues)
    
    # 【修复核心】：强制扁平化，并转为标准的整型数组
    all_preds = np.array(all_preds).flatten().astype(int)
    all_trues = np.array(all_trues).flatten().astype(int)
    
    # 计算各项指标 (显式指定 average='binary' 防患于未然)
    acc = accuracy_score(all_trues, all_preds)
    precision = precision_score(all_trues, all_preds, average='binary', zero_division=0)
    recall = recall_score(all_trues, all_preds, average='binary', zero_division=0)
    f1 = f1_score(all_trues, all_preds, average='binary', zero_division=0)
    
    print(f"    [Eval Results] Acc: {acc*100:.2f}% | P: {precision*100:.2f}% | R: {recall*100:.2f}% | F1: {f1*100:.2f}%")
    
    # 按照原作者在 run.py 里的习惯，evaluate 返回的是 0~100 格式的准确率
    return float(f1) * 100.0

if __name__ == "__main__":
    from dataset import CodeChef
    import random
    
    root = '../data/'
    parser = argparse.ArgumentParser()
    parser.add_argument('--gpu', type=str, default="0")
    # 这里默认测试从 ReVeal 练出来，要在 Devign 上测的模型
    parser.add_argument('--model_path', type=str, required=True, help="要测试的模型权重绝对路径")
    parser.add_argument('--task', type=str, default="reveal", help="主要用来区分路径结构，这里选 reveal 或 devign")
    parser.add_argument('--test_data_path', type=str, required=True, help="指向你要测试的 data.pkl.gz 的路径")
    parser.add_argument('--bs', type=int, default=16)

    opt = parser.parse_args()

    os.environ["CUDA_VISIBLE_DEVICES"] = opt.gpu
    device = torch.device("cuda:" + opt.gpu if torch.cuda.is_available() else "cpu")
    
    n_class = 2 # 漏洞检测一定是二分类！

    batch_size = opt.bs
    rand_seed = 1726
    torch.manual_seed(rand_seed)
    random.seed(rand_seed)
    np.random.seed(rand_seed)

    print(f"📦 正在加载测试数据集: {opt.test_data_path}")
    dataset_wrapper = CodeChef(path=opt.test_data_path)
    test_s = dataset_wrapper.test

    print(f"🧠 正在加载模型权重: {opt.model_path}")
    class DummyArgs:
        def __init__(self):
            self.model_name_or_path = "microsoft/codebert-base"
    linevul_args = DummyArgs()
    
    classifier = LineVulClassifier(model_path="microsoft/codebert-base", 
                                   num_labels=n_class,
                                   device=device,
                                   args=linevul_args).to(device)
                                   
    classifier.model.load_state_dict(torch.load(opt.model_path, map_location=device))
    classifier.eval()
    
    print("🚀 开始执行评估...")
    evaluate(classifier, test_s, device, batch_size=batch_size)