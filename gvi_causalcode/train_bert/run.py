# -*- coding: utf-8 -*-

import argparse
import gzip
import os
import pickle
import time
from math import inf

import torch
from torch import optim
import random
import numpy
import wandb
from tqdm import tqdm

# 引入我们统一处理过的数据集类和评估模块
from dataset import VulnDataset
from bert_eval import evaluate

# 引入我们的秘密武器：适配了 CausalCode 接口的 LineVul 包装器
from linevul_wrapper import LineVulClassifier
# 保留基础大模型生成器（如果你在 run.py 也要生成数据的话）
from attacker4simple import CausalCodeToken, CausalCodeDeadCode

import logging

# 屏蔽分词器长度警告，防止刷屏干扰进度条
logging.getLogger("transformers.tokenization_utils_base").setLevel(logging.ERROR)


def adjust_learning_rate(optimizer, decay_rate=0.8):
    for param_group in optimizer.param_groups:
        param_group['lr'] = param_group['lr'] * decay_rate


def get_train_batch(renew_num, opt, root):
    """
    多域数据加载器。用于在训练时同时加载【原数据】和【干预数据】
    """
    training_set = {}
    batch = {}
    
    # 固定种子，保证不同域的数据在切分 Batch 时严格对齐
    rand_seed = 666
    torch.manual_seed(rand_seed)
    random.seed(rand_seed)
    numpy.random.seed(rand_seed)
    
    # opt.domain_list 是一个列表，比如['origin_s', 'linevul-CausalCode-token']
    for d in opt.domain_list:
        domain_name = d
        # 如果不是原数据且开启了刷新，则自动找不同后缀的干预数据集
        if d != 'origin_s' and opt.do_renew:  
            domain_name = f"{d}-index-{renew_num * opt.aug_num + opt.begin_num - 1}"
            
        data_path = os.path.join(root, opt.train_task, 'dataset', domain_name, "data.pkl.gz")
        print(f'📦 正在加载训练域数据: {data_path}')
        
        if not os.path.exists(data_path):
            raise FileNotFoundError(f"找不到训练域文件: {data_path}，请确保你已经生成了干预数据！")
            
        domain_dataset = VulnDataset(path=data_path)
        training_set[domain_name] = domain_dataset.train
        batch[domain_name] = training_set[domain_name].next_batch(opt.batch_size)
        
    return training_set, opt.domain_list, batch


def ws_loss_function(domain_list, batch_size, outputs, labels, device):
    """
    CausalCode 论文核心公式：因果对齐损失 (特征空间的 L2 距离)
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

    # 掩码：只惩罚标签相同的样本之间的距离
    mask = (all_labels.unsqueeze(1) == all_labels.unsqueeze(0)).float().to(device)
    masked_diffs = diff_matrix * mask
    total_diff = torch.sum(masked_diffs)
    
    return total_diff / (len(domain_list) * batch_size)


def train_CausalCode(classifier, optimizer, opt, valid_set, device, wandb, root):
    """
    因果联合训练主循环 - 严格还原 Algorithm 2 动态权重逻辑
    """
    classifier.train()
    epoch = 0
    renew_num = 0
    penalty_ws = 1.0               # λ 的上限
    ws_proportion = 0.0             # λ 初始为 0 (对应论文第3行)
    begin_wasserstein = 2           # 预热 epoch 数 N_s

    best_f1 = 0.0
    early_stop_counter = 0

    # 【新增】：用于记录历史最低的因果损失和总损失，避免 lambda 震荡
    best_w_loss = inf
    best_total_loss = inf

    # 1. 初始化数据加载
    training_set, current_domain_list, _ = get_train_batch(renew_num, opt, root)
    main_domain = current_domain_list[0]

    total_samples = training_set[main_domain].get_size()
    n_batch = total_samples // opt.batch_size

    print(f'\n🚀 CausalCode 强化训练启动 | 任务: {opt.train_task} -> {opt.test_task}')

    pbar = tqdm(total=n_batch, desc=f"Epoch {epoch + 1}/{opt.epochs}", unit="batch", leave=True)

    erm_loss_accum = 0.0
    w_loss_accum = 0.0
    loss_total_accum = 0.0
    step_count = 0

    while True:
        input_batch = {}
        rand_seed = random.randint(1, 1000)
        for d in current_domain_list:
            torch.manual_seed(rand_seed)
            random.seed(rand_seed)
            numpy.random.seed(rand_seed)
            input_batch[d] = training_set[d].next_batch(opt.batch_size)

        if len(current_domain_list) > 1:
            assert numpy.array_equal(input_batch[current_domain_list[0]]['id'],
                                     input_batch[current_domain_list[1]]['id']), "致命错误：多域数据未对齐！"

        # ----------------- 2. 每个 Epoch 结束时的逻辑 -----------------
        if input_batch[main_domain]['new_epoch']:
            pbar.close()
            epoch += 1

            # 计算该 epoch 的平均损失
            avg_erm = erm_loss_accum / max(1, step_count)
            avg_w = w_loss_accum / max(1, step_count)
            avg_total = loss_total_accum / max(1, step_count)

            wandb.log({
                "train/epoch": epoch,
                "train/erm_loss_avg": avg_erm,
                "train/wasserstein_loss_avg": avg_w,
                "train/total_loss_avg": avg_total
            })

            # ---------- 严格按照 Algorithm 2 更新 λ (ws_proportion) ----------
            if epoch > begin_wasserstein:
                # 只要因果距离(w_loss)缩小了，或者总Loss下降了，说明模型在进步
                if avg_w < best_w_loss or avg_total < best_total_loss:
                    if ws_proportion < penalty_ws:
                        ws_proportion = min(penalty_ws, ws_proportion + 0.1)
                    
                    # 更新历史最低记录
                    best_w_loss = min(best_w_loss, avg_w)
                    best_total_loss = min(best_total_loss, avg_total)
                else:
                    # 否则 λ -= 0.1 (但不小于 0)
                    ws_proportion = max(0.0, ws_proportion - 0.1)

            # 模型评估与早停
            if epoch > 2:
                with torch.no_grad():
                    print(f"\n[Epoch {epoch}] 正在验证集上执行性能评估...")
                    current_acc = evaluate(classifier, valid_set, device, batch_size=opt.batch_size)
                    wandb.log({"eval/acc": current_acc})

                classifier.train()

                # 这里为了变量名不混淆，我们知道现在的 current_acc 其实是 F1 的值
                if current_acc > best_f1:
                    best_f1 = current_acc
                    early_stop_counter = 0
                    save_path = os.path.join(opt.model_save_dir, "best.pt")
                    torch.save(classifier.model.state_dict(), save_path)
                    print(f"🔥 性能提升! 最佳 F1-score 更新为: {best_f1:.2f}% | 模型已保存")
                else:
                    early_stop_counter += 1
                    print(f"⚠️ 性能未提升 | 早停计数: {early_stop_counter}/{opt.early_stop}")
                    if early_stop_counter >= opt.early_stop:
                        print("🚫 达到早停阈值，停止训练。")
                        break

            if opt.lr_decay:
                adjust_learning_rate(optimizer)

            if epoch >= opt.epochs:
                print("🏁 已达到最大训练 Epoch。")
                break

            # 数据刷新逻辑
            if epoch % 7 == 0 and opt.do_renew:
                renew_num = (renew_num + 1) % 4
                print(f"🔄 刷新干预数据池，进入周期 {renew_num}")
                training_set, current_domain_list, _ = get_train_batch(renew_num, opt, root)

            # 重置累加器并开启新进度条
            erm_loss_accum = 0.0
            w_loss_accum = 0.0
            loss_total_accum = 0.0
            step_count = 0
            pbar = tqdm(total=n_batch, desc=f"Epoch {epoch + 1}/{opt.epochs}", unit="batch", leave=True)

        # ----------------- 3. 前向与反向传播 -----------------
        optimizer.zero_grad()
        outputs = {}
        current_erm_loss = torch.tensor(0.0).to(device)
        current_w_loss = torch.tensor(0.0).to(device)
        labels = {d: input_batch[d]['y'] for d in current_domain_list}

        for d in current_domain_list:
            out_logits, e_loss = classifier(input_batch[d]['x'], input_batch[d]['y'])
            outputs[d] = out_logits
            current_erm_loss += e_loss

        loss_e = current_erm_loss.clone()

        # 因果约束计算 (仅在预热期后且有多域数据时)
        if epoch > begin_wasserstein and opt.enhance_method == 'CausalCode' and len(current_domain_list) > 1:
            current_w_loss = ws_loss_function(current_domain_list, opt.batch_size, outputs, labels, device)
            loss_e += ws_proportion * current_w_loss

        loss_e.backward()
        optimizer.step()

        # 统计数据
        step_count += 1
        erm_loss_accum += current_erm_loss.item()
        w_loss_accum += current_w_loss.item()
        loss_total_accum += loss_e.item()

        # 更新进度条
        pbar.update(1)
        pbar.set_postfix({
            "Loss": f"{loss_e.item():.3f}",
            "λ": f"{ws_proportion:.2f}"      # 显示当前 λ 值
        })

if __name__ == "__main__":
    
    parser = argparse.ArgumentParser()
    parser.add_argument('--root_dir', type=str, default='../data/')
    parser.add_argument('--gpu', type=str, default='0')
    parser.add_argument('--lr', type=float, default=2e-5)
    parser.add_argument('--l2p', type=float, default=0)
    parser.add_argument('--lr_decay', action='store_true')
    
    # 核心任务定义（跨域魔法的核心）
    parser.add_argument('--train_task', type=str, default='reveal', help='训练数据集，通常是 reveal')
    parser.add_argument('--test_task', type=str, default='devign', help='跨域测试数据集，通常是 devign')
    
    parser.add_argument('--model_name', type=str, default="linevul", help="强制使用 linevul")
    parser.add_argument('--enhance_method', type=str, default='CausalCode')
    parser.add_argument('--attack_type', type=str, default='token', help='token 或 dead_code')
    
    # 要加载的数据域，用逗号分隔
    parser.add_argument('--domain_list', type=str, default='origin_s,linevul-CausalCode-token')
    
    parser.add_argument('--batch_size', type=int, default=8)
    parser.add_argument('--epochs', type=int, default=15)
    parser.add_argument('--early_stop', default=5, type=int)
    
    # 执行开关
    parser.add_argument('--do_train', action='store_true', default=False)
    parser.add_argument('--do_eval', action='store_true', default=False)
    parser.add_argument('--do_test', action='store_true', default=False)
    parser.add_argument('--do_renew', action='store_true', default=False)
    
    # CausalCode 参数
    parser.add_argument('--aug_num', type=int, default=1)
    parser.add_argument('--begin_num', type=int, default=1)
    parser.add_argument('--begin_proportion', type=float, default=0.1)

    opt = parser.parse_args()

    # 初始化配置
    root = opt.root_dir
    opt.domain_list = opt.domain_list.split(',')
    wandb_name = f"{opt.model_name}-{opt.enhance_method}-{opt.train_task}2{opt.test_task}-{opt.attack_type}-{time.strftime('%Y%m%d', time.localtime())}"
    
    print(f'📊 实验名称: {wandb_name}')
    wandb.init(project='CausalCode-CrossDataset', name=wandb_name)
    os.environ["WANDB_MODE"] = "offline"
    
    os.environ["CUDA_VISIBLE_DEVICES"] = opt.gpu
    device = torch.device("cpu" if int(opt.gpu) < 0 else f"cuda:{opt.gpu}")
    
    # 固定全局随机种子
    rand_seed = 1726
    torch.manual_seed(rand_seed)
    random.seed(rand_seed)
    numpy.random.seed(rand_seed)
    
    # 建立模型保存路径
    model_param_str = '+'.join(opt.domain_list)
    opt.model_save_dir = os.path.join(root, opt.train_task, 'model', opt.model_name, opt.enhance_method, opt.attack_type, model_param_str)
    os.makedirs(opt.model_save_dir, exist_ok=True)

    # 1. ================== 数据加载 (分离训练集与跨域测试集) ==================
    n_class = 2 # 漏洞二分类
    
    print(f"📦 正在加载【训练/验证集】 ({opt.train_task})...")
    train_data_path = os.path.join(root, opt.train_task, 'dataset', 'origin_s', 'data.pkl.gz')
    train_dataset_wrapper = VulnDataset(path=train_data_path)
    valid_s = train_dataset_wrapper.dev
    
    print(f"📦 正在加载【跨域测试集】 ({opt.test_task})...")
    test_data_path = os.path.join(root, opt.test_task, 'dataset', 'origin_s', 'data.pkl.gz')
    test_dataset_wrapper = VulnDataset(path=test_data_path)
    cross_test_s = test_dataset_wrapper.test # 我们只取它的 test 切片

    # 2. ================== 模型初始化 (LineVul) ==================
    class DummyArgs:
        def __init__(self, device):
            self.model_name_or_path = "microsoft/codebert-base"
            self.device = device  # 【修复核心】：把当前的 device 存进去
            self.n_gpu = 1       # 顺便补上这个参数，防止后面报错
    linevul_args = DummyArgs(device)
    
    # 3. ================== 核心阶段: 训练 ==================
    if opt.do_train:
        print("\n🛠️ 初始化 LineVul 模型准备训练...")
        classifier = LineVulClassifier(model_path="microsoft/codebert-base",
                                       num_labels=n_class,
                                       device=device,
                                       args=linevul_args).to(device)
                                       
        optimizer = optim.AdamW(classifier.parameters(), lr=opt.lr, weight_decay=opt.l2p)
        train_CausalCode(classifier, optimizer, opt, valid_s, device, wandb, root)
       
    # 4. ================== 核心阶段: 跨域评估 ==================
    if opt.do_eval or opt.do_test:
        model_attack = os.path.join(opt.model_save_dir, 'best.pt')
        print(f'\n🎯 正在加载最佳模型权重进行测试: {model_attack}')
        
        classifier = LineVulClassifier(model_path="microsoft/codebert-base",
                                       num_labels=n_class,
                                       device=device,
                                       args=linevul_args).to(device)
        classifier.model.load_state_dict(torch.load(model_attack, map_location=device))
        classifier.eval()
        
        print(f"🚀 开始在 【{opt.test_task.upper()} 跨域测试集】上执行评估...")
        test_acc = evaluate(classifier, cross_test_s, device, batch_size=opt.batch_size)
        wandb.log({f"test_on_{opt.test_task}/acc": test_acc})

    wandb.finish()
    print("\n🎉 实验全部完成！" + time.strftime("%Y-%m-%d %H:%M:%S", time.localtime()))