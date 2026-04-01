# -*- coding: utf-8 -*-

import argparse
import os
import time
from math import inf

import torch
import torch.nn as nn
from torch import optim
import random
import numpy
import pickle
import gzip

# 引入我们统一的数据集类和评估函数
from dataset import CodeChef 
from bert_eval import evaluate

# 引入我们写好的 LineVul 包装器（如果你想跑普通的 CodeBERT/GraphCodeBERT，也可以换回原来的类）
from linevul_wrapper import LineVulClassifier


def adjust_learning_rate(optimizer, decay_rate=0.8):
    for param_group in optimizer.param_groups:
        param_group['lr'] = param_group['lr'] * decay_rate

def ws_loss_function(domain_list, batch_size, outputs, labels, device):
    """
    【核心因果损失】：计算多个域（原数据 vs 变体数据）在特征空间的 L2 距离
    """
    all_outputs = torch.stack([outputs[d] for d in domain_list])
    all_labels = torch.stack([torch.from_numpy(labels[d]) for d in domain_list])

    diff_matrix = torch.zeros(len(domain_list), len(domain_list), batch_size, device=device)

    for i in range(len(domain_list)):
        for j in range(i + 1, len(domain_list)):
            diff = all_outputs[i] - all_outputs[j]
            diff = torch.sum(diff ** 2, dim=-1)
            diff_matrix[i, j] = diff
            diff_matrix[j, i] = diff  

    # 掩码：只有真实标签相同的样本才拉近距离
    mask = (all_labels.unsqueeze(1) == all_labels.unsqueeze(0)).float().to(device)
    masked_diffs = diff_matrix * mask
    total_diff = torch.sum(masked_diffs)
    
    return total_diff / (len(domain_list) * batch_size)


def trainEpochs(epochs, training_set, valid_set, device, opt, batch_size=32, print_each=100):
    classifier.train()
    epoch = 0
    i = 0
    penalty_s = -1
    penalty_ws = 1.0  # 因果损失的权重
    
    print_loss_total = 0
    w_loss_total = 0
    
    # 以第一个域的数据量为准计算 batch 数量
    main_domain = opt.domain_list[0]
    n_batch = int(training_set[main_domain].get_size() / batch_size)
    print(f"[{main_domain}] Total samples: {training_set[main_domain].get_size()}, Total batches: {n_batch}")
    
    erm_loss_total = 0
    loss_total = 0
    early_stop = 0
    best_f1 = 0.0 # 【修复】：以验证集的 F1 score 为准，而不是看训练 loss
    
    print('start training epoch ' + str(epoch + 1) + '....')
    while True:
        input_batch = {}
        for d in opt.domain_list:
            # 固定种子以保证多域数据在 next_batch 时顺序完全对齐！
            rand_seed = 666
            torch.manual_seed(rand_seed)
            random.seed(rand_seed)
            numpy.random.seed(rand_seed)
            input_batch[d] = training_set[d].next_batch(batch_size)

        if len(opt.domain_list) > 1:
            assert numpy.array_equal(input_batch[opt.domain_list[0]]['id'],
                                     input_batch[opt.domain_list[1]]['id']), "数据未对齐！"

        if input_batch[main_domain]['new_epoch']:
            epoch += 1
            print(f"\n--- Epoch {epoch} 结束，开始在验证集上评估 ---")
            
            with torch.no_grad():
                os.makedirs(opt.save_dir, exist_ok=True)
                # 【修复】：去掉了作者原先传的错误参数，标准调用 evaluate
                acc_f1 = evaluate(classifier, valid_set, device, batch_size=batch_size)
            
            classifier.train()
            
            # 【修复】：保存最佳模型逻辑 (使用 torch.save 兼容自定义的 LineVul 模型)
            if acc_f1 > best_f1:
                best_f1 = acc_f1
                early_stop = 0
                print(f"🔥 发现更好模型，当前验证表现: {best_f1:.4f}，正在保存...")
                torch.save(classifier.model.state_dict(), os.path.join(opt.save_dir, "best.pt"))
            else:
                early_stop += 1
                print(f"模型未提升，早停计数: {early_stop}/4")
                if early_stop >= 4:
                    print(f"触发早停，结束训练！最佳表现: {best_f1:.4f}")
                    break

            if opt.lrdecay:
                adjust_learning_rate(optimizer)
                
            if epoch >= epochs:
                break
                
            i = 0
            print_loss_total = 0
            erm_loss_total = 0
            w_loss_total = 0
            loss_total = 0
            print('start training epoch ' + str(epoch + 1) + '....')

        optimizer.zero_grad()
        outputs = {}
        erm_loss = torch.tensor(0.0).to(device)
        wasserstein_loss = torch.tensor(0.0).to(device)
        labels = {d: input_batch[d]['y'] for d in opt.domain_list}
        
        # 多域前向传播
        for d in opt.domain_list:
            out_logits, e_loss = classifier(input_batch[d]['x'], input_batch[d]['y'])
            outputs[d] = out_logits
            erm_loss += e_loss
        
        loss_e = erm_loss.clone()
        
        # 只有存在多个域且启用了 CausalCode 才计算因果对齐损失
        if opt.enhance_method == 'CausalCode' and len(opt.domain_list) > 1:
            wasserstein_loss = ws_loss_function(opt.domain_list, batch_size, outputs, labels, device)
            loss_e += (penalty_ws * (epoch - penalty_s) / (epochs - penalty_s)) * wasserstein_loss

        loss_e.backward()
        optimizer.step()
        
        erm_loss_total += erm_loss.item()
        print_loss_total += loss_e.item()
        w_loss_total += wasserstein_loss.item()
        loss_total += loss_e.item()

        if (i + 1) % print_each == 0:
            print_loss_avg = print_loss_total / print_each
            print_loss_total = 0
            progress = (i + 1) / n_batch * 100 if n_batch > 0 else 0
            print(f'({epoch + 1} {progress:.0f}%) Total Loss: {print_loss_avg:.4f} | ERM: {erm_loss_total/print_each:.4f} | Causal: {w_loss_total/print_each:.4f}')
        i += 1


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    # 【修复】：加入了缺失的 task, root_dir, domain_list 参数
    parser.add_argument('--root_dir', type=str, default='../data/')
    parser.add_argument('--task', type=str, default='reveal', help='reveal, devign, or code_function')
    parser.add_argument('--domain_list', type=str, default='origin_s', help='例如: origin_s,graphcodebert-CausalCode-token')
    
    parser.add_argument('--gpu', type=str, default="0")
    parser.add_argument('--lr', type=float, default=2e-5)
    parser.add_argument('--l2p', type=float, default=0)
    parser.add_argument('--lrdecay', action='store_true')
    parser.add_argument('--model', type=str, default="linevul", help="linevul, codebert, graphcodebert")
    parser.add_argument('--enhance_method', type=str, default='origin', help='origin, CausalCode, ALERT')
    parser.add_argument('--save_dir', type=str, default=None)
    parser.add_argument('--bs', type=int, default=8) # 二分类建议 batch_size 不要太大，防止 OOM
    parser.add_argument('--epochs', type=int, default=10)

    opt = parser.parse_args()

    os.environ["CUDA_VISIBLE_DEVICES"] = opt.gpu
    device = torch.device("cpu" if int(opt.gpu) < 0 else f"cuda:{opt.gpu}")

    opt.domain_list = opt.domain_list.split(',')

    # 【修复】：动态判定类别数，漏洞检测是二分类
    n_class = 2 if opt.task in ['reveal', 'devign', 'code_defect'] else 104

    # 动态设定保存路径
    if opt.save_dir is None:
        model_parameter = '+'.join(opt.domain_list)
        opt.save_dir = os.path.join(opt.root_dir, opt.task, 'model', opt.model, opt.enhance_method, model_parameter)
    print(f"💾 模型将保存在: {opt.save_dir}")

    # 加载数据集
    training_set = {}
    valid_set = None
    
    print("📦 正在加载数据集...")
    for domain in opt.domain_list:
        path = os.path.join(opt.root_dir, opt.task, 'dataset', domain, 'data.pkl.gz')
        print(f" -> 加载: {path}")
        if not os.path.exists(path):
            raise FileNotFoundError(f"找不到数据集文件，请检查预处理: {path}")
            
        dataset_wrapper = CodeChef(path=path)
        training_set[domain] = dataset_wrapper.train
        if valid_set is None:
            valid_set = dataset_wrapper.dev # 统一使用第一个域(origin_s)的验证集

    # 初始化模型 (LineVul)
    print(f"🤖 正在初始化 {opt.model} 模型...")
    class DummyArgs:
        def __init__(self):
            self.model_name_or_path = "microsoft/codebert-base"
    linevul_args = DummyArgs()
    
    classifier = LineVulClassifier(model_path="microsoft/codebert-base",
                                   num_labels=n_class,
                                   device=device,
                                   args=linevul_args).to(device)

    optimizer = optim.Adam(classifier.parameters(), lr=opt.lr, weight_decay=opt.l2p)

    trainEpochs(opt.epochs, training_set, valid_set, device, opt,
                saving_path=opt.save_dir, batch_size=opt.bs, print_each=50)