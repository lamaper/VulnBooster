# -*- coding: utf-8 -*-

import torch
import random
import copy
import numpy
from copy import deepcopy
import sys
import os
import pattern
from tqdm import tqdm

# 【修复 2】：彻底删除 from pycparser import c_parser，不再使用 AST 验证


def raw2x(raws, txt2idx):
    "here we dont convert raw to ids in fact, but replace OoVs as '<unk>'"
    xs = []
    for raw in raws:
        xs.append([])
        for token in raw:
            if token in txt2idx.keys():
                xs[-1].append(token)
            else:
                xs[-1].append("<unk>")
    return xs

def get_batched_data(raws, ys, txt2idx, ids=None):
    xs = raw2x(raws, txt2idx)
    batch = {"x": [], "y": [], "raw":[], "id": [], "new_epoch": False}
    batch['x'] =[" ".join(x) for x in xs]
    batch['y'] = ys
    batch['id'] = ids
    batch['raw'] = deepcopy(raws)
    return batch


class TokenModifier(object):

    def __init__(self, classifier, loss, uids, txt2idx, idx2txt):

        self.cl = classifier
        self.loss = loss
        self.txt2idx = txt2idx
        self.idx2txt = idx2txt

        self.__key_words__ =["auto", "break", "case", "char", "const", "continue",
                              "default", "do", "double", "else", "enum", "extern",
                              "float", "for", "goto", "if", "inline", "int", "long",
                              "register", "restrict", "return", "short", "signed",
                              "sizeof", "static", "struct", "switch", "typedef",
                              "union", "unsigned", "void", "volatile", "while",
                              "_Alignas", "_Alignof", "_Atomic", "_Bool", "_Complex",
                              "_Generic", "_Imaginary", "_Noreturn", "_Static_assert",
                              "_Thread_local", "__func__"]
        self.__ops__ =["...", ">>=", "<<=", "+=", "-=", "*=", "/=", "%=", "&=", "^=", "|=",
                        ">>", "<<", "++", "--", "->", "&&", "||", "<=", ">=", "==", "!=", ";",
                        "{", "<%", "}", "%>", ",", ":", "=", "(", ")", "[", "<:", "]", ":>",
                        ".", "&", "!", "~", "-", "+", "*", "/", "%", "<", ">", "^", "|", "?"]
        self.__macros__ =["NULL", "_IOFBF", "_IOLBF", "BUFSIZ", "EOF", "FOPEN_MAX", "TMP_MAX", 
                           "FILENAME_MAX", "L_tmpnam", "SEEK_CUR", "SEEK_END", "SEEK_SET",
                           "NULL", "EXIT_FAILURE", "EXIT_SUCCESS", "RAND_MAX", "MB_CUR_MAX"] 
        self.__special_ids__ =["main", 
                                "stdio", "cstdio", "stdio.h",  
                                "size_t", "FILE", "fpos_t", "stdin", "stdout", "stderr", 
                                "remove", "rename", "tmpfile", "tmpnam", "fclose", "fflush", 
                                "fopen", "freopen", "setbuf", "setvbuf", "fprintf", "fscanf",
                                "printf", "scanf", "snprintf", "sprintf", "sscanf", "vprintf",
                                "vscanf", "vsnprintf", "vsprintf", "vsscanf", "fgetc", "fgets",
                                "fputc", "getc", "getchar", "putc", "putchar", "puts", "ungetc",
                                "fread", "fwrite", "fgetpos", "fseek", "fsetpos", "ftell",
                                "rewind", "clearerr", "feof", "ferror", "perror", "getline"
                                "stdlib", "cstdlib", "stdlib.h",
                                "size_t", "div_t", "ldiv_t", "lldiv_t", 
                                "atof", "atoi", "atol", "atoll", "strtod", "strtof", "strtold", 
                                "strtol", "strtoll", "strtoul", "strtoull", "rand", "srand",
                                "aligned_alloc", "calloc", "malloc", "realloc", "free", "abort",
                                "atexit", "exit", "at_quick_exit", "_Exit", "getenv",
                                "quick_exit", "system", "bsearch", "qsort", "abs", "labs",
                                "llabs", "div", "ldiv", "lldiv", "mblen", "mbtowc", "wctomb",
                                "mbstowcs", "wcstombs",
                                "string", "cstring", "string.h", 
                                "memcpy", "memmove", "memchr", "memcmp", "memset", "strcat", 
                                "strncat", "strchr", "strrchr", "strcmp", "strncmp", "strcoll",
                                "strcpy", "strncpy", "strerror", "strlen", "strspn", "strcspn",
                                "strpbrk", "strstr", "strtok", "strxfrm",
                                "memccpy", "mempcpy", "strcat_s", "strcpy_s", "strdup",
                                "strerror_r", "strlcat", "strlcpy", "strsignal", "strtok_r",
                                "iostream", "istream", "ostream", "fstream", "sstream", 
                                "iomanip", "iosfwd",
                                "ios", "wios", "streamoff", "streampos", "wstreampos", 
                                "streamsize", "cout", "cerr", "clog", "cin",
                                "boolalpha", "noboolalpha", "skipws", "noskipws", "showbase", 
                                "noshowbase", "showpoint", "noshowpoint", "showpos",
                                "noshowpos", "unitbuf", "nounitbuf", "uppercase", "nouppercase",
                                "left", "right", "internal", "dec", "oct", "hex", "fixed",
                                "scientific", "hexfloat", "defaultfloat", "width", "fill",
                                "precision", "endl", "ends", "flush", "ws", "showpoint",
                                "sin", "cos", "tan", "asin", "acos", "atan", "atan2", "sinh", 
                                "cosh", "tanh", "exp", "sqrt", "log", "log10", "pow", "powf",
                                "ceil", "floor", "abs", "fabs", "cabs", "frexp", "ldexp",
                                "modf", "fmod", "hypot", "ldexp", "poly", "matherr"]
        self.forbidden_uid = self.__key_words__ + self.__ops__ + self.__macros__ + self.__special_ids__

        # ================= 开始优化后的词表映射 =================
        print("⏳ 正在进行 BERT 词表与代码变量名的交叉映射计算 (该过程涉及数亿次匹配，请耐心等待)...")
        _uids =[]
        
        # 【优化】：预先过滤合法的 uid，极大地减少内层循环的计算量
        valid_uids = set([u for u in uids if u in self.txt2idx and u not in self.forbidden_uid])
        
        # 【增加进度条】：套上 tqdm 让你能看到进度
        for subtoken_idx in tqdm(range(self.cl.vocab_size), desc="构建干预词典"):
            subtoken = self.cl.tokenizer.convert_ids_to_tokens(subtoken_idx)
            assert isinstance(subtoken, str)
            
            if subtoken in[self.cl.tokenizer.bos_token, self.cl.tokenizer.eos_token,
                            self.cl.tokenizer.sep_token, self.cl.tokenizer.pad_token,
                            self.cl.tokenizer.unk_token, self.cl.tokenizer.cls_token,
                            self.cl.tokenizer.mask_token]:
                continue
            if not subtoken.startswith('Ġ'):
                continue
                
            clear_subtoken = subtoken[1:]
            
            # 【优化】：将重复判断移到外层
            if clear_subtoken == "" or clear_subtoken[0] in '0987654321' or clear_subtoken in self.forbidden_uid:
                continue

            # 内层循环匹配
            for uid in valid_uids:
                if clear_subtoken in uid:
                    _uids.append(subtoken_idx)
                    break

        self._uids = _uids
        self.uids = self.__gen_uid_mask_on_vocab(_uids)
        print(f"✅ 干预词典构建完成！共找到 {len(self._uids)} 个合法替换词。")
        # =========================================================

    def __gen_uid_mask_on_vocab(self, uids):
        _uids = torch.zeros(self.cl.vocab_size)
        _uids.index_put_([torch.LongTensor(uids)], torch.Tensor([1 for _ in uids]))
        _uids = _uids.reshape([self.cl.vocab_size, 1]).to(self.cl.device)
        return _uids

    def rename_uid(self, x_raw, y, ori_uid_raw, n_candidate=5):
        Gori_uid_raw = 'Ġ' + ori_uid_raw
        Gori_uid_idx = self.cl.tokenizer.convert_tokens_to_ids(Gori_uid_raw)
        if not self.uids[Gori_uid_idx]:
            return None, None
        batch = get_batched_data([x_raw], [y], self.txt2idx)
        grad = self.cl.grad(batch['x'], batch['y'])
        grad = grad[Gori_uid_idx].reshape([1, self.cl.x_size])
        ori_embed = self.cl.embed.weight[Gori_uid_idx].reshape([1, self.cl.x_size]).expand([self.cl.vocab_size, self.cl.x_size])
        delta_embed = self.uids * (self.cl.embed.weight - ori_embed)
        delta_embed_len = torch.sqrt(torch.sum(delta_embed * delta_embed, dim=1)) + 1e-5
        inner_prod = torch.sum(grad * delta_embed, dim=1) / delta_embed_len
        _, Gnew_uid_cand = torch.topk(inner_prod, n_candidate)
        Gnew_uid_cand = Gnew_uid_cand.cpu().numpy()
        
        new_x_raw, new_x_uid = [],[]
        for Gnew_uid_idx in Gnew_uid_cand:
            if not self.uids[Gnew_uid_idx]:
                continue
            Gnew_uid_raw = self.cl.tokenizer.convert_ids_to_tokens(int(Gnew_uid_idx))
            new_uid_raw = Gnew_uid_raw[1:]
            if new_uid_raw in x_raw:
                continue
                
            new_x_uid.append(new_uid_raw)
            new_x_raw.append(copy.deepcopy(x_raw))
            for i in range(len(new_x_raw[-1])):
                if new_x_raw[-1][i] == ori_uid_raw:
                    new_x_raw[-1][i] = new_uid_raw
                    
            # 【修复 3】：直接信任生成的变体，删除会引发灾难的 pycparser.parse 校验
            
        if len(new_x_uid) == 0:
            return None, None
        while len(new_x_uid) < n_candidate:
            new_x_uid.append(new_x_uid[-1])
            new_x_raw.append(new_x_raw[-1])
        return new_x_raw, new_x_uid

    def rename_uid_random(self, x_raw, ori_uid_raw):
        Gori_uid_raw = 'Ġ' + ori_uid_raw
        Gori_uid_idx = self.cl.tokenizer.convert_tokens_to_ids(Gori_uid_raw)
        
        if not self.uids[Gori_uid_idx]:
            return None, None

        fail_cnt = 0
        Guid_cand_idx = random.sample(self._uids, 1)[0]
        Guid_cand_raw = self.cl.tokenizer.convert_ids_to_tokens(Guid_cand_idx)
        uid_cand_raw = Guid_cand_raw[1:]
        
        while Guid_cand_idx == Gori_uid_idx or uid_cand_raw in x_raw:
            fail_cnt += 1
            Guid_cand_idx = random.sample(self._uids, 1)[0]
            Guid_cand_raw = self.cl.tokenizer.convert_ids_to_tokens(Guid_cand_idx)
            uid_cand_raw = Guid_cand_raw[1:]
            if fail_cnt >= 10:  
                Guid_cand_idx = Gori_uid_idx  
                Guid_cand_raw = Gori_uid_raw
                uid_cand_raw = ori_uid_raw
                break
                
        new_x_uid = [uid_cand_raw]
        new_x_raw =[copy.deepcopy(x_raw)]
        for i in range(len(new_x_raw[-1])):
            if new_x_raw[-1][i] == ori_uid_raw:
                new_x_raw[-1][i] = uid_cand_raw
                
        # 【修复 4】：删除 pycparser 校验
        
        if new_x_uid ==[]:
            return None, None
        else:
            return new_x_raw, new_x_uid


class InsModifier(object):

    def __init__(self, classifier, txt2idx, idx2txt, poses=None):
        self.cl = classifier
        self.txt2idx = txt2idx
        self.idx2txt = idx2txt
        if poses is not None:  
            self.initInsertDict(poses)
        inserts =[";", "{ }", "printf ( \"\" ) ;", "if ( false ) ;",
                   "if ( true ) { }", "if ( false ) ; else { }", "if ( 0 ) ;",
                   "if ( false ) { int cnt = 0 ; for ( int i = 0 ; i < 123 ; i ++ ) cnt += 1 ; }",
                   "for ( int i = 0 ; i < 100 ; i ++ ) break ;",
                   "for ( int i = 0 ; i < 0 ; i ++ ) { }",
                   "while ( false ) ;", "while ( 0 ) ;", "while ( true ) break ;",
                   "for ( int i = 0 ; i < 10 ; i ++ ) { for ( int j = 0 ; j < 10 ; j ++ ) break ; break ; }",
                   "do { } while ( false ) ;"]
        self.inserts =[insert.split(" ") for insert in inserts]

    def initInsertDict(self, poses):
        self.insertDict = dict([(pos, []) for pos in poses])
        self.insertDict["count"] = 0

    def insert(self, x_raw, n_candidate=5):
        pos_candidates = pattern.InsAddCandidates(self.insertDict)  
        n = len(pos_candidates)
        if n_candidate < n:
            candisIdx = random.sample(range(n), n_candidate)
        else:
            candisIdx = random.sample(range(n), n)
        pos_candidates = [pos_candidates[candiIds] for candiIds in candisIdx] 

        new_x_raw, new_insertDict = [],[]
        for pos in pos_candidates:
            inst = random.sample(self.inserts, 1)[0]
            _insertDict = deepcopy(self.insertDict)
            pattern.InsAdd(_insertDict, pos, inst)
            _x_raw = pattern.InsResult(x_raw, _insertDict)
            
            # 【修复 5】：删除 pycparser 校验
            
            new_x_raw.append(_x_raw)
            new_insertDict.append(_insertDict)

        return new_x_raw, new_insertDict

    def remove(self, x_raw, n_candidate=5):
        pos_candidates = pattern.InsDeleteCandidates(self.insertDict) 
        n = len(pos_candidates)
        if n_candidate < n:
            candisIdx = random.sample(range(n), n_candidate)
        else:
            candisIdx = random.sample(range(n), n)
        pos_candidates =[pos_candidates[candiIds] for candiIds in candisIdx]

        new_x_raw, new_insertDict = [],[]
        for pos, listIdx in pos_candidates:
            _insertDict = deepcopy(self.insertDict)
            pattern.InsDelete(_insertDict, pos, listIdx)
            _x_raw = pattern.InsResult(x_raw, _insertDict)
            
            # 【修复 6】：删除 pycparser 校验
            
            new_x_raw.append(_x_raw)
            new_insertDict.append(_insertDict)

        return new_x_raw, new_insertDict

    def insert_remove_random(self, x_raw):
        new_x_raw, new_insertDict = [],[]
        fail_cnt = 0
        while True:
            if fail_cnt >= 15:  
                break
            if random.random() > 0.5:  
                pos_candidates = pattern.InsAddCandidates(self.insertDict)
                if pos_candidates ==[]:
                    fail_cnt += 1
                    continue
                pos_cand = random.sample(pos_candidates, 1)[0]
                inst = random.sample(self.inserts, 1)[0]
                _insertDict = deepcopy(self.insertDict)
                pattern.InsAdd(_insertDict, pos_cand, inst)
            else:
                pos_candidates = pattern.InsDeleteCandidates(self.insertDict)
                if pos_candidates ==[]:
                    fail_cnt += 1
                    continue
                pos_cand, inPosIdx = random.sample(pos_candidates, 1)[0]
                _insertDict = deepcopy(self.insertDict)
                pattern.InsDelete(_insertDict, pos_cand, inPosIdx)
                
            _x_raw = pattern.InsResult(x_raw, _insertDict)
            
            # 【修复 7】：删除 pycparser 校验
            
            new_x_raw.append(_x_raw)
            new_insertDict.append(_insertDict)
            break
        return new_x_raw, new_insertDict