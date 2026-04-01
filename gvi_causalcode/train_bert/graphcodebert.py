# -*- coding: utf-8 -*-

from __future__ import absolute_import, division, print_function

import logging
import torch
import torch.nn as nn
from transformers import RobertaForSequenceClassification, RobertaTokenizer

logger = logging.getLogger(__name__)

class GraphCodeBERTClassifier(nn.Module):
    """
    通用 CodeBERT/GraphCodeBERT 分类器包装类。
    适配二分类漏洞检测任务，并提供提取底层梯度的能力。
    """
    def __init__(self, model_path, num_labels=2, device=None):
        super(GraphCodeBERTClassifier, self).__init__()
        
        self.device = device
        self.block_size = 512
        
        # 加载分词器
        self.tokenizer = RobertaTokenizer.from_pretrained(model_path)
        
        # 加载模型。
        # 【修复】：增加 ignore_mismatched_sizes=True，防止加载微调过的模型时分类头维度不匹配导致崩溃
        self.model = RobertaForSequenceClassification.from_pretrained(
            model_path, 
            num_labels=num_labels,
            ignore_mismatched_sizes=True 
        )
        
        # 获取底层词嵌入层，用于后续的梯度计算和对抗干预
        # CodeBERT/GraphCodeBERT 底层都是 Roberta
        self.embed = self.model.roberta.embeddings.word_embeddings
        self.vocab_size = self.embed.weight.size()[0]
        self.x_size = self.embed.weight.size()[-1]

    def tokenize(self, inputs, cut_and_pad=False, ret_id=False):
        """将代码字符串转化为模型可接受的 token 序列或 ID"""
        rets = []
        if isinstance(inputs, str):
            inputs = [inputs]
            
        for sent in inputs:
            if cut_and_pad:
                # 截断并填充至 block_size
                tokens = self.tokenizer.tokenize(sent)[:self.block_size - 2]
                tokens = [self.tokenizer.cls_token] + tokens + [self.tokenizer.sep_token]
                padding_length = self.block_size - len(tokens)
                tokens +=[self.tokenizer.pad_token] * padding_length
            else:
                # 仅分词并添加首尾特殊符
                tokens = self.tokenizer.tokenize(sent)
                tokens =[self.tokenizer.cls_token] + tokens + [self.tokenizer.sep_token]
                
            if ret_id:
                ids = self.tokenizer.convert_tokens_to_ids(tokens)
                rets.append(ids)
            else:
                rets.append(tokens)
        return rets

    def run_batch(self, inputs_src, labels=None):
        """执行一个 batch 的前向传播"""
        inputs = self.tokenize(inputs_src, cut_and_pad=True, ret_id=True)
        inputs = torch.tensor(inputs, dtype=torch.long).to(self.device)
        
        if labels is not None:
            # 漏洞检测是分类任务，标签应该是 long (整数索引型)
            labels = torch.tensor(labels, dtype=torch.long).to(self.device)
            
        # 注意：这里传递了 labels，模型内部会自动计算 CrossEntropyLoss
        outputs = self.model(
            input_ids=inputs, 
            attention_mask=inputs.ne(self.tokenizer.pad_token_id), 
            labels=labels
        )

        if labels is not None:
            return outputs.logits, outputs.loss
        else:
            return outputs.logits  # Transformers 返回的对象属性最好用明确的 .logits

    def forward(self, inputs, labels=None):
        return self.run_batch(inputs, labels)

    def prob(self, inputs):
        """返回预测的概率分布 (形状: batch_size, num_labels)"""
        logits = self.forward(inputs)
        # 对于 num_labels >= 2 的情况，使用 Softmax 将 logits 转化为概率
        prob = nn.Softmax(dim=-1)(logits)
        return prob

    def grad(self, inputs, labels):
        """
        【核心功能】：提取对抗梯度。
        对应论文公式 (4)，计算 Loss 对底层词嵌入权重的偏导数。
        """
        self.zero_grad()
        
        # 强制保留对不可导叶子节点的梯度
        self.embed.weight.retain_grad()

        # 前向传播拿到 loss
        logits, loss = self.forward(inputs, labels)
        
        # 反向传播
        loss.backward()

        # 拿到并返回整个词表的梯度矩阵 (vocab_size, hidden_size)
        return self.embed.weight.grad


if __name__ == "__main__":
    # 【修复】：替换为适用于你的二分类漏洞检测的测试代码
    from dataset import VulnDataset # 使用我们之前重构过的统称
    from torch import optim
    import os

    # 这里需要指向你实际生成的 pkl 文件路径
    data_path = '../data/reveal/dataset/origin_s/data.pkl.gz'
    
    if not os.path.exists(data_path):
        print(f"⚠️ 测试数据不存在: {data_path}")
        print("请先运行预处理脚本生成数据。")
    else:
        print("🚀 开始本地测试 GraphCodeBERTClassifier...")
        device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
        
        # 初始化二分类的数据集
        dataset = VulnDataset(path=data_path)
        
        # 初始化模型，注意这里 num_labels 改为 2
        model = GraphCodeBERTClassifier('microsoft/codebert-base', num_labels=2, device=device).train()
        model.to(device)
        
        opt = optim.Adam(model.parameters(), lr=1e-5)
        opt.zero_grad()

        # 取出一个小 batch 测试
        b = dataset.train.next_batch(2)
        print("测试输入前向传播...")
        logits, loss = model.run_batch(b['x'], b['y'])
        print(f"Logits shape: {logits.shape}, Loss: {loss.item():.4f}")

        print("测试反向传播与梯度提取...")
        grad = model.grad(b['x'], b['y'])
        print(f"Embedding 梯度提取成功! 形状为: {grad.shape}")
        print("✅ GraphCodeBERTClassifier 模块测试通过！")