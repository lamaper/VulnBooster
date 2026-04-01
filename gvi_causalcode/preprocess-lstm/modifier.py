import torch
import copy
import sys

import pattern
import random
from copy import deepcopy


class TokenModifier(object):
    """
    功能：标识符（Token/变量名）修改器。
    作用：用于在模型训练阶段，利用梯度下降方向找到能打破“虚假相关性”的最优替换变量名，
    这正是论文中 CausalCode 框架“步骤1：生成干预样本”针对变量名的具体实现。
    """

    def __init__(self, classifier, loss, uids, txt2idx, idx2txt):
        self.cl = classifier    # 传入要增强的代码分类模型 (如 CodeBERT 或 LSTM)
        self.loss = loss        # 损失函数 (如交叉熵 CrossEntropyLoss)
        self.txt2idx = txt2idx  # 词到索引的映射字典
        self.idx2txt = idx2txt  # 索引到词的映射字典
        
        # ---------------- 禁忌词表定义开始 ----------------
        # C语言关键字，绝对不能被替换
        self.__key_words__ =["auto", "break", "case", "char", "const", "continue",
                              "default", "do", "double", "else", "enum", "extern",
                              "float", "for", "goto", "if", "inline", "int", "long",
                              "register", "restrict", "return", "short", "signed",
                              "sizeof", "static", "struct", "switch", "typedef",
                              "union", "unsigned", "void", "volatile", "while",
                              "_Alignas", "_Alignof", "_Atomic", "_Bool", "_Complex",
                              "_Generic", "_Imaginary", "_Noreturn", "_Static_assert",
                              "_Thread_local", "__func__"]
        # C语言操作符，绝对不能被替换
        self.__ops__ =["...", ">>=", "<<=", "+=", "-=", "*=", "/=", "%=", "&=", "^=", "|=",
                        ">>", "<<", "++", "--", "->", "&&", "||", "<=", ">=", "==", "!=", ";",
                        "{", "<%", "}", "%>", ",", ":", "=", "(", ")", "[", "<:", "]", ":>",
                        ".", "&", "!", "~", "-", "+", "*", "/", "%", "<", ">", "^", "|", "?"]
        # 宏定义，绝对不能被替换
        self.__macros__ =["NULL", "_IOFBF", "_IOLBF", "BUFSIZ", "EOF", "FOPEN_MAX", "TMP_MAX",  # <stdio.h> macro
                           "FILENAME_MAX", "L_tmpnam", "SEEK_CUR", "SEEK_END", "SEEK_SET",
                           "NULL", "EXIT_FAILURE", "EXIT_SUCCESS", "RAND_MAX", "MB_CUR_MAX"]  # <stdlib.h> macro
        # 常见标准库函数、类型名等特殊标识符，绝对不能被替换
        self.__special_ids__ =["main",  # main function
                                "stdio", "cstdio", "stdio.h",  # <stdio.h> & <cstdio>
                                "size_t", "FILE", "fpos_t", "stdin", "stdout", "stderr",  # <stdio.h> types & streams
                                "remove", "rename", "tmpfile", "tmpnam", "fclose", "fflush",  # <stdio.h> functions
                                "fopen", "freopen", "setbuf", "setvbuf", "fprintf", "fscanf",
                                "printf", "scanf", "snprintf", "sprintf", "sscanf", "vprintf",
                                "vscanf", "vsnprintf", "vsprintf", "vsscanf", "fgetc", "fgets",
                                "fputc", "getc", "getchar", "putc", "putchar", "puts", "ungetc",
                                "fread", "fwrite", "fgetpos", "fseek", "fsetpos", "ftell",
                                "rewind", "clearerr", "feof", "ferror", "perror", "getline"
                                                                                  "stdlib", "cstdlib", "stdlib.h",
                                # <stdlib.h> & <cstdlib>
                                "size_t", "div_t", "ldiv_t", "lldiv_t",  # <stdlib.h> types
                                "atof", "atoi", "atol", "atoll", "strtod", "strtof", "strtold",  # <stdlib.h> functions
                                "strtol", "strtoll", "strtoul", "strtoull", "rand", "srand",
                                "aligned_alloc", "calloc", "malloc", "realloc", "free", "abort",
                                "atexit", "exit", "at_quick_exit", "_Exit", "getenv",
                                "quick_exit", "system", "bsearch", "qsort", "abs", "labs",
                                "llabs", "div", "ldiv", "lldiv", "mblen", "mbtowc", "wctomb",
                                "mbstowcs", "wcstombs",
                                "string", "cstring", "string.h",  # <string.h> & <cstring>
                                "memcpy", "memmove", "memchr", "memcmp", "memset", "strcat",  # <string.h> functions
                                "strncat", "strchr", "strrchr", "strcmp", "strncmp", "strcoll",
                                "strcpy", "strncpy", "strerror", "strlen", "strspn", "strcspn",
                                "strpbrk", "strstr", "strtok", "strxfrm",
                                "memccpy", "mempcpy", "strcat_s", "strcpy_s", "strdup",
                                # <string.h> extension functions
                                "strerror_r", "strlcat", "strlcpy", "strsignal", "strtok_r",
                                "iostream", "istream", "ostream", "fstream", "sstream",  # <iostream> family
                                "iomanip", "iosfwd",
                                "ios", "wios", "streamoff", "streampos", "wstreampos",  # <iostream> types
                                "streamsize", "cout", "cerr", "clog", "cin",
                                "boolalpha", "noboolalpha", "skipws", "noskipws", "showbase",  # <iostream> manipulators
                                "noshowbase", "showpoint", "noshowpoint", "showpos",
                                "noshowpos", "unitbuf", "nounitbuf", "uppercase", "nouppercase",
                                "left", "right", "internal", "dec", "oct", "hex", "fixed",
                                "scientific", "hexfloat", "defaultfloat", "width", "fill",
                                "precision", "endl", "ends", "flush", "ws", "showpoint",
                                "sin", "cos", "tan", "asin", "acos", "atan", "atan2", "sinh",  # <math.h> functions
                                "cosh", "tanh", "exp", "sqrt", "log", "log10", "pow", "powf",
                                "ceil", "floor", "abs", "fabs", "cabs", "frexp", "ldexp",
                                "modf", "fmod", "hypot", "ldexp", "poly", "matherr"]
        self.forbidden_uid = self.__key_words__ + self.__ops__ + self.__macros__ + self.__special_ids__
        # ---------------- 禁忌词表定义结束 ----------------
        
        _uids = [txt2idx["<unk>"]]
        # 遍历数据集提取的所有变量 uids，如果不在禁忌表里，说明是用户自定义变量，将其加入合法替换候选词表 _uids
        for uid in uids:
            if uid in txt2idx.keys() and txt2idx[uid] not in _uids and uid not in self.forbidden_uid:
                _uids.append(txt2idx[uid])
        self._uids = _uids
        
        # 调用函数，生成一个针对整个词表的 0/1 掩码
        self.uids = self.__gen_uid_mask_on_vocab(_uids)

    def __gen_uid_mask_on_vocab(self, uids):
        # 创建一个和整个词汇表一样大的全 0 张量
        _uids = torch.zeros(self.cl.vocab_size)
        # 将合法的可替换变量位置设为 1
        _uids.index_put_([torch.LongTensor(uids)], torch.Tensor([1 for _ in uids]))
        _uids = _uids.reshape([self.cl.vocab_size, 1]).cuda()
        return _uids # 返回词表掩码 (GPU Tensor)

    def __gen_uid_mask_on_seq(self, uids):
        # 创建一个和输入序列最大长度一样大的全 0 张量
        _uids = torch.zeros(self.cl.max_len)
        # 将序列中出现的可以被替换的变量位置设为 1
        _uids.index_put_([torch.LongTensor(uids)], torch.Tensor([1 for _ in uids]))
        _uids = _uids.reshape([self.cl.max_len, 1]).cuda()
        return _uids # 返回序列掩码 (GPU Tensor)

    def rename_uid(self, x, y, x_uid, ori_uid, n_candidate=5):
        """
        核心函数：对应论文 公式(4) 的 PGD(投影梯度下降) 干预生成方法。
        根据模型梯度的下降方向，在候选词表中选出破坏力最强（最能影响预测）的词进行替换。
        """
        _x_uid =[]
        # 收集序列中有效范围内的变量索引位置
        for i in x_uid:
            if i < self.cl.max_len:
                _x_uid.append(i)
        
        # 根据变量在序列中的位置生成掩码
        x_uid = self.__gen_uid_mask_on_seq(_x_uid)
        
        # 获取原始变量在词表中的 id
        if ori_uid in self.txt2idx.keys():
            ori_uid = self.txt2idx[ori_uid]
        else:
            ori_uid = self.txt2idx['<unk>']
            
        _x = torch.tensor(x, dtype=torch.long).cuda().permute([1, 0])
        _y = torch.tensor(y, dtype=torch.long).cuda()
        
        # 1. 计算损失对嵌入层的梯度 (即公式4中的 \partial L / \partial v)
        grad = self.cl.grad(_x, _y, self.loss)[0]
        
        # 2. 计算被修改变量在当前序列所有出现位置的平均梯度方向
        mean_grad = torch.sum(grad * x_uid, dim=0) / torch.sum(x_uid)
        mean_grad = mean_grad.reshape([1, self.cl.embedding_size])
        
        # 3. 提取出原变量在模型中的词嵌入向量 (Embedding)
        ori_embed = self.cl.embedding.weight[ori_uid] \
            .reshape([1, self.cl.embedding_size]) \
            .expand([self.cl.vocab_size, self.cl.embedding_size])
            
        # 4. 计算词表里所有“合法候选词”和“原变量”之间的嵌入向量差值
        # 乘以 self.uids 这个掩码矩阵，是为了让那些系统关键字的差值变为 0 (防止选中关键字)
        delta_embed = self.uids * (self.cl.embedding.weight - ori_embed)
        
        # 5. 求出差值向量的长度 (L2范数)，加上 1e-5 防止除以 0
        delta_embed_len = torch.sqrt(torch.sum(delta_embed * delta_embed, dim=1)) + 1e-5
        
        # 6. 【论文核心公式 4 的实现】：求 梯度下降方向 和 词嵌入变化方向 的余弦相似度（内积）
        inner_prod = torch.sum(mean_grad * delta_embed, dim=1) / delta_embed_len
        
        # 7. 挑选出内积排名前 n_candidate(默认为5) 的候选词
        # 这些词就是“换上去以后，模型损失变化最剧烈”的词（即对抗性最强的干预）
        _, new_uid_cand = torch.topk(inner_prod, n_candidate)
        new_uid_cand = new_uid_cand.cpu().numpy()
        
        # 8. 构造包含这些被替换词的新样本序列
        new_x =[]
        for new_uid in new_uid_cand:
            new_x.append(copy.deepcopy(x[0]))
            for i in _x_uid:
                new_x[-1][i] = new_uid  # 逐位置替换旧 id 为新 id
        return new_x, new_uid_cand

    def rename_uid_random(self, x, x_uid, ori_uid):
        """
        基线对比方法：不看梯度，完全随机找一个变量名进行替换。
        对应论文 RQ3 中关于 Intervention Example Generation 使用 'Random examples' 的对比。
        """
        _x_uid =[]
        for i in x_uid:
            if i < self.cl.max_len:
                _x_uid.append(i)
        if ori_uid in self.txt2idx.keys():
            ori_uid = self.txt2idx[ori_uid]
        else:
            ori_uid = self.txt2idx['<unk>']

        fail_cnt = 0
        # 从合法变量名库中随机选一个词
        uid_cand = random.sample(self._uids, 1)[0]
        
        # 防止选到跟原来一样的，或者选到当前代码里已经有的其它变量引起混淆
        while uid_cand == ori_uid or uid_cand in x[0][:self.cl.max_len]:
            fail_cnt += 1
            uid_cand = random.sample(self._uids, 1)[0]
            if fail_cnt >= 10:  # in case of dead loop (防止进入死循环)
                uid_cand = ori_uid  # keep it no changed (如果一直找不到合适的，就不替换了)
                break
                
        new_x = [copy.deepcopy(x[0])]
        for i in _x_uid:
            new_x[-1][i] = uid_cand # 替换
        return new_x, [uid_cand]


class InsModifier(object):
    """
    功能：插入修改器。
    作用：对应论文中的第二种“保留语义的转换”—— 死代码插入。用于扰动程序的结构（也是一种风格F），
    通过改变控制流的外观，测试模型并迫使其学习到不变表示。
    """
    def __init__(self, classifier, txt2idx, poses=None):

        self.cl = classifier
        self.txt2idx = txt2idx
        if poses != None:  # else you need to call initInsertDict later (如果未提供位置，之后需调用 initInsertDict)
            self.initInsertDict(poses)
            
        # 论文中定义的 15 种安全的死代码片段列表 (不改变原程序功能的无用代码)
        inserts =[
            ";",
            "{ }",
            "printf ( \"\" ) ;",
            "if ( false ) ;",
            "if ( true ) { }",
            "if ( false ) ; else { }",
            "if ( 0 ) ;",
            "if ( false ) { int cnt = 0 ; for ( int i = 0 ; i < 123 ; i ++ ) cnt += 1 ; }"
            "for ( int i = 0 ; i < 100 ; i ++ ) break ;",
            "for ( int i = 0 ; i < 0 ; i ++ ) { }"
            "while ( false ) ;",
            "while ( 0 ) ;",
            "while ( true ) break ;",
            "for ( int i = 0 ; i < 10 ; i ++ ) { for ( int j = 0 ; j < 10 ; j ++ ) break ; break ; }",
            "do { } while ( false ) ;"]

        # 按照空格切分，把文本形态的死代码变成 Token 列表
        self.inserts = [insert.split(" ") for insert in inserts]

    def initInsertDict(self, poses):
        # 记录每个位置插入了什么代码，初始化为为空列表。count 记录当前总共插入了几处。
        self.insertDict = dict([(pos, []) for pos in poses])
        self.insertDict["count"] = 0

    def _insert2idxs(self, insert):
        # 辅助函数：将准备插入的 Token 字符串转成对应的整数 Index (词表ID)
        idxs =[]
        for t in insert:
            if self.txt2idx.get(t) is not None:
                idxs.append(self.txt2idx[t])
            else:
                idxs.append(self.txt2idx['<unk>'])
        return idxs

    # only support one piece of data each time: x is idx-list (每次只支持处理一条数据，x是索引列表)
    def insert(self, x, n_candidate=5):
        """在合法的干预位置随机选择插入点，并随机插入死代码片段"""
        
        # 获取允许插入的候选位置（排除掉超长的或者非法的越界位置）
        pos_candidates = pattern.InsAddCandidates(self.insertDict, self.cl.max_len)  # exclude outlier poses
        n = len(pos_candidates)
        
        # 决定对多少个位置进行试探性插入
        if n_candidate < n:
            candisIdx = random.sample(range(n), n_candidate)
        else:
            candisIdx = random.sample(range(n), n)
            
        # 拿到被选中的候选位置坐标
        pos_candidates = [pos_candidates[candiIds] for candiIds in candisIdx]  # sample max(n, n_candidate) poses

        new_x, new_insertDict = [],[]
        for pos in pos_candidates:
            # 随机抽一条死代码
            inst = random.sample(self.inserts, 1)[0]
            # 把死代码转成模型能看懂的 IDs
            inst_idxs = self._insert2idxs(inst)
            
            # 复制一份状态，防止污染
            _insertDict = deepcopy(self.insertDict)
            # 在对应的位置将死代码加入记录
            pattern.InsAdd(_insertDict, pos, inst_idxs)
            # 根据记录，生成真正融合了原代码和死代码的全新序列向量
            _x = pattern.InsResult(x, _insertDict)
            
            new_x.append(_x)
            new_insertDict.append(_insertDict)

        return new_x, new_insertDict

    # only support one piece of data each time: x is idx-list
    def remove(self, x, n_candidate=5):
        """撤销之前某处插入的死代码（配合后续马尔可夫链探索时回退使用）"""
        
        # 找出当前有哪些位置已经插入了死代码
        pos_candidates = pattern.InsDeleteCandidates(self.insertDict)  # e.g.[(pos0, 0), (pos0, 1), (pos1, 0), ...]
        n = len(pos_candidates)
        
        # 随机挑选几个准备删掉
        if n_candidate < n:
            candisIdx = random.sample(range(n), n_candidate)
        else:
            candisIdx = random.sample(range(n), n)
        pos_candidates = [pos_candidates[candiIds] for candiIds in candisIdx]

        new_x, new_insertDict = [],[]
        for pos, inPosIdx in pos_candidates:
            _insertDict = deepcopy(self.insertDict)
            # 调用底层方法，删除记录
            pattern.InsDelete(_insertDict, pos, inPosIdx)
            # 重建张量序列
            _x = pattern.InsResult(x, _insertDict)
            new_x.append(_x)
            new_insertDict.append(_insertDict)

        return new_x, new_insertDict

    def insert_remove_random(self, x):
        """模拟干预探索链条：随机一半概率去插入死代码，一半概率去删掉已有的死代码"""
        new_x, new_insertDict = [],[]
        fail_cnt = 0
        while True:
            if fail_cnt >= 10:  # in case of dead loop (试了10次都没法操作就直接退出)
                break
            
            if random.random() > 0.5:  # insert (50%概率执行插入)
                pos_candidates = pattern.InsAddCandidates(self.insertDict, self.cl.max_len)  # exclude outlier poses
                if pos_candidates ==[]:
                    fail_cnt += 1
                    continue
                pos_cand = random.sample(pos_candidates, 1)[0]
                inst = random.sample(self.inserts, 1)[0]
                inst_idxs = self._insert2idxs(inst)
                _insertDict = deepcopy(self.insertDict)
                pattern.InsAdd(_insertDict, pos_cand, inst_idxs)
            else:                      # 50%概率执行删除
                pos_candidates = pattern.InsDeleteCandidates(self.insertDict)
                if pos_candidates ==[]:
                    fail_cnt += 1
                    continue
                pos_cand, inPosIdx = random.sample(pos_candidates, 1)[0]
                _insertDict = deepcopy(self.insertDict)
                pattern.InsDelete(_insertDict, pos_cand, inPosIdx)
                
            _x = pattern.InsResult(x, _insertDict)
            new_x.append(_x)
            new_insertDict.append(_insertDict)
            break
        return new_x, new_insertDict

# 辅助函数：用于将模型处理完的整数索引序列还原回可读的代码字符串
def idxs2tokens(idxs, idx2word, unk_idx):
    res =[]
    n = len(idx2word)
    for idx in idxs:
        if idx < n:
            res.append(idx2word[idx])
        else:
            res.append(idx2word[unk_idx])
    return res


'''if __name__ == "__main__":
    """
    --------------------------------------------------------------
    以下是作者留下的本地测试与功能验证模块 (当直接运行 modifier.py 时触发)。
    主要是为了验证 TokenModifier 和 InsModifier 能否正常工作并改变分类器的概率。
    --------------------------------------------------------------
    """
    # 尝试加载外部的模块。这里VS Code标黄是因为通常在运行时这些文件位于上层或其它目录。
    from dataset import OJ104
    from lstm_classifier import LSTMClassifier, LSTMEncoder
    import argparse
    import pickle, gzip, os, sys

    # 1. 命令行解析：获取运行在哪个 GPU 上
    parser = argparse.ArgumentParser()
    parser.add_argument('-gpu', required=True)
    parser.add_argument('-attn', action='store_true')
    opt = parser.parse_args()
    os.environ["CUDA_VISIBLE_DEVICES"] = opt.gpu
    device = torch.device("cuda:" + opt.gpu)

    # 模型相关的超参数定义
    vocab_size = 5000
    embedding_size = 512
    hidden_size = 600
    n_layers = 2
    num_classes = 104
    max_len = 300

    # 2. 模拟加载 POJ-104 数据集、符号表 (uids) 和 插入点表 (inspos)
    poj = OJ104(path="../dataset/data.pkl.gz", max_len=max_len, vocab_size=vocab_size)
    training_set, valid_set, test_set = poj.train, poj.dev, poj.test
    with gzip.open('../dataset/oj_uid.pkl.gz', "rb") as f:
        symtab = pickle.load(f)
    with gzip.open('../dataset/oj_inspos.pkl.gz', "rb") as f:
        instab = pickle.load(f)

    # 3. 模拟实例化并加载一个训练好的基线模型 (LSTM)
    enc = LSTMEncoder(embedding_size, hidden_size, n_layers)
    classifier = LSTMClassifier(vocab_size, embedding_size, enc,
                                hidden_size, num_classes, max_len, attn=opt.attn).cuda()
    classifier.load_state_dict(torch.load('../model/lstm/model-14.pt'))

    ''''''
    # ---------- 下方是作者注释掉的 TokenModifier (变量重命名) 测试逻辑 ----------
    # 实例化变量修改器
    m = TokenModifier(classifier, torch.nn.CrossEntropyLoss(), symtab['all'],
                      poj.get_txt2idx(), poj.get_idx2txt())
    
    # 获取一条测试集数据
    b = test_set.next_batch(1)
    uid = symtab['te'][b['id'][0]]
    
    # 打印原始数据的真实标签和模型原始预测的概率
    x = torch.tensor(b['x'], dtype=torch.long).cuda().permute([1, 0])
    y = torch.tensor(b['y'], dtype=torch.long).cuda()
    print (b['y'][0])
    prob = classifier.prob(x)[0]
    print (int(torch.argmax(prob)), float(prob[b['y'][0]]))
    
    # 遍历该数据中的所有合法变量名，使用 rename_uid 寻找对抗性最强的变量替换
    # 并打印替换后，模型预测概率是否发生了大幅下降 (用来验证对抗干预是否有效)
    for k in uid.keys():
        if k in m.forbidden_uid:
            continue
        print (k)
        new_x, new_uid_cand = m.rename_uid(b['x'], b['y'], uid[k], k, 5)
        new_prob = classifier.prob(torch.tensor(new_x, dtype=torch.long).cuda().permute([1, 0]))
        for _p, _uid in zip(new_prob, new_uid_cand):
            print (poj.idx2vocab(_uid), _uid, float(_p[b['y'][0]]), int(torch.argmax(_p).cpu()))
        print ()
    '''
'''
    # ---------- 下方是运行生效的 InsModifier (死代码插入) 测试逻辑 ----------
    # 获取一条测试数据
    b = test_set.next_batch(1)
    # 拿到该条数据中允许插入语句(Statement)的安全位置集合
    stmt_ins_poses = instab['stmt_te'][b['id'][0]]
    
    # 实例化死代码插入器
    m = InsModifier(classifier, poj.get_txt2idx(), stmt_ins_poses)

    # 可视化原始代码结构和能插入的位置
    pattern._InsVis(b['raw'][0], stmt_ins_poses)

    x = torch.tensor(b['x'], dtype=torch.long).cuda().permute([1, 0])
    y = torch.tensor(b['y'], dtype=torch.long).cuda()
    print(b['y'][0])
    prob = classifier.prob(x)[0]
    print(int(torch.argmax(prob)), float(prob[b['y'][0]])) # 打印原版模型的预测自信度

    old_x = b['x'][0]
    
    # 循环2次：测试“插入干预”
    for _ in range(2):
        new_x, new_insertDict = m.insert(old_x, n_candidate=3)
        feed_new_x = [_x[:classifier.max_len] for _x in new_x]  # this step is very important (截断对齐最大序列长度)
        
        # 将插入死代码后的序列丢进模型
        new_prob = classifier.prob(torch.tensor(feed_new_x, dtype=torch.long).cuda().permute([1, 0]))
        
        # 打印置信度的变化（预期插入死代码会引起模型概率混乱，以此证明这是个强有力的干预样本）
        for _p, _dict in zip(new_prob, new_insertDict):
            print(float(_p[b['y'][0]]), int(torch.argmax(_p).cpu()))
            
        # while new_x[-1]=="<unk>": new_x = new_x[:-1]
        # pattern._InsVis(idxs2tokens(new_x[0], poj.get_idx2txt(), poj.get_txt2idx()["<unk>"]), [])
        m.insertDict = new_insertDict[0] # 更新当前的字典状态
        print('------------ INSERT -------------', m.insertDict["count"])
        
    # 循环2次：测试“删除干预” (复原)
    for _ in range(2):
        new_x, new_insertDict = m.remove(old_x, n_candidate=3)
        feed_new_x = [_x[:classifier.max_len] for _x in new_x]  # this step is very important
        new_prob = classifier.prob(torch.tensor(feed_new_x, dtype=torch.long).cuda().permute([1, 0]))
        for _p, _dict in zip(new_prob, new_insertDict):
            print(float(_p[b['y'][0]]), int(torch.argmax(_p).cpu()))
        # while new_x[-1]=="<unk>": new_x = new_x[:-1]
        # pattern._InsVis(idxs2tokens(new_x[0], poj.get_idx2txt(), poj.get_txt2idx()["<unk>"]), [])
        m.insertDict = new_insertDict[0]
        print('------------ REMOVE -------------', m.insertDict["count"])'''