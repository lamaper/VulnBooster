import torch
import torch.nn as nn
from transformers import RobertaTokenizer, RobertaForSequenceClassification, RobertaConfig
# 导入刚刚复制过来的 LineVul 核心模型
from linevul_model import Model as LineVulCoreModel

class LineVulClassifier(nn.Module):
    """
    为了适配 CausalCode 框架，对 LineVul 进行的一层包装。
    提供分词、前向传播、计算梯度(用于干预生成)等 CausalCode 必需的接口。
    """
    def __init__(self, model_path, num_labels=2, device=None, args=None):
        super(LineVulClassifier, self).__init__()
        self.device = device
        self.block_size = 512
        
        # 1. 加载 CodeBERT 分词器
        self.tokenizer = RobertaTokenizer.from_pretrained(model_path)
        
        # 2. 加载基础配置并初始化 Roberta (这是 LineVul 的基座)
        config = RobertaConfig.from_pretrained(model_path)
        config.num_labels = 1 # LineVul 内部是用 1 个输出节点做 Sigmoid 二分类
        
        base_model = RobertaForSequenceClassification.from_pretrained(model_path, config=config, ignore_mismatched_sizes=True)
        
        # 3. 实例化真正的 LineVul 模型
        self.model = LineVulCoreModel(base_model, config, self.tokenizer, args)
        
        # 4. 获取底层词嵌入层 (为了 CausalCode 算梯度用)
        self.embed = self.model.encoder.roberta.embeddings.word_embeddings
        self.vocab_size = self.embed.weight.size()[0]
        self.x_size = self.embed.weight.size()[-1]

    def tokenize(self, inputs, cut_and_pad=False, ret_id=False):
        """和 GraphCodeBERT 一模一样的文本分词逻辑"""
        rets = []
        if isinstance(inputs, str): inputs = [inputs]
        for sent in inputs:
            if cut_and_pad:
                tokens = self.tokenizer.tokenize(sent)[:self.block_size - 2]
                tokens = [self.tokenizer.cls_token] + tokens + [self.tokenizer.sep_token]
                padding_length = self.block_size - len(tokens)
                tokens +=[self.tokenizer.pad_token] * padding_length
            else:
                tokens = self.tokenizer.tokenize(sent)
                tokens = [self.tokenizer.cls_token] + tokens + [self.tokenizer.sep_token]
            
            if ret_id:
                rets.append(self.tokenizer.convert_tokens_to_ids(tokens))
            else:
                rets.append(tokens)
        return rets

    def run_batch(self, inputs_src, labels=None):
        """前向传播，输出 logits 和 loss"""
        inputs = self.tokenize(inputs_src, cut_and_pad=True, ret_id=True)
        inputs = torch.tensor(inputs, dtype=torch.long).to(self.device)
        
        if labels is not None:
            # 训练阶段：有标签，强转为 long 类型满足交叉熵需求
            labels = torch.tensor(labels, dtype=torch.long).to(self.device)
            # 模型直接返回 (loss, logits)，logits 已经是 (batch, 2) 形状
            loss, logits = self.model(input_ids=inputs, labels=labels)
            return logits, loss
        else:
            # 评估阶段：无标签，直接拿输出
            out = self.model(input_ids=inputs)
            # 兼容处理：确保拿到的纯 logits
            if isinstance(out, tuple):
                logits = out[1] if len(out) > 1 else out[0]
            else:
                logits = out
            return logits

    def forward(self, inputs, labels=None):
        return self.run_batch(inputs, labels)

    def prob(self, inputs):
        """预测概率"""
        logits = self.forward(inputs)
        # 因为在 run_batch 里已经转成概率拼起来了，所以直接返回
        return logits

    def grad(self, inputs, labels):
        """提取特征对抗梯度，CausalCode 核心依赖"""
        self.zero_grad()
        self.embed.weight.retain_grad()
        logits, loss = self.forward(inputs, labels)
        loss.backward()
        return self.embed.weight.grad