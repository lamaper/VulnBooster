# -*- coding: utf-8 -*-

import os, sys
import shutil
import tarfile
import pickle
import tqdm
import re

# ================= 禁忌词表与正则提取 =================
forbidden_uid = set([
    "auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern",
    "float", "for", "goto", "if", "inline", "int", "long", "register", "restrict", "return", "short", "signed",
    "sizeof", "static", "struct", "switch", "typedef", "union", "unsigned", "void", "volatile", "while",
    "main", "stdio", "printf", "malloc", "free", "NULL", "EOF", "size_t", "fprintf", "memset", "av_log", "avctx",
    "__func__", "true", "false", "TRUE", "FALSE"
])

def extract_uids_regex(code_text):
    pattern = r'(?<![\w\\%])[_a-zA-Z][_a-zA-Z0-9]*(?![\w\\%])'
    names = re.findall(pattern, code_text)
    valid_uids = set()
    for name in names:
        if name not in forbidden_uid:
            valid_uids.add(name)
    return valid_uids

# ================= 【终极修复】：正则表达式无敌分词器 =================
def safe_tokenize(code):
    """
    完全无视语法错误和乱码的 C 语言分词器
    """
    token_pattern = re.compile(
        r'(?:"(?:\\.|[^"\\])*")|'               # 匹配双引号字符串 (哪怕内部有转义)
        r"(?:'(?:\\.|[^'\\])*')|"               # 匹配单引号字符
        r'[a-zA-Z_]\w*|'                        # 匹配标识符/关键字
        r'\d+(?:\.\d+)?(?:[eE][+-]?\d+)?[fFlLuU]*|' # 匹配所有数字
        r'!=|==|<=|>=|&&|\|\||->|>>|<<|\+\+|--|'# 匹配双字符操作符
        r'\S'                                   # 兜底：匹配任何其他的非空白单字符
    )
    return token_pattern.findall(code)
# ===================================================================

def unzip(file="../dataset/oj.tar.gz", dir="./tmp", done_file="unzip.done"):
    if os.path.isdir(dir):
        if not os.path.isfile(os.path.join(dir, done_file)):
            shutil.rmtree(dir)
        else:
            return True 
    if not os.path.isdir(dir):
        os.mkdir(dir)
    try:
        with tarfile.open(file) as t:
            t.extractall(dir)
        with open(os.path.join(dir, done_file), "wb"):
            pass
        return True
    except Exception as e:
        print(e)
        return False

def remove_comment(text):
    def replacer(match):
        s = match.group(0)
        if s.startswith('/'):
            return " " 
        else:
            return s
    pattern = re.compile(
        r'//.*?$|/\*.*?\*/|\'(?:\\.|[^\\\'])*\'|"(?:\\.|[^\\"])*"',
        re.DOTALL | re.MULTILINE
    )
    return re.sub(pattern, replacer, text)

def tokenize(dir='./tmp', src='ProgramData', tgt='tokenized.pkl',
             done_file="token.done", min_len=5, save_dir='../data'):
    
    if os.path.isfile(os.path.join(save_dir, src, tgt)):
        if os.path.getsize(os.path.join(save_dir, tgt)) < 1024:
            os.remove(os.path.join(save_dir, src, tgt))
        else:
            with open(os.path.join(save_dir, tgt), "rb") as f:
                return pickle.load(f)
                
    os.makedirs(os.path.join(save_dir), exist_ok=True)
    
    try:
        data = {'raw':[], "labels":[], "uids":[], "index":[]}
        
        for label in tqdm.tqdm(sorted(os.listdir(os.path.join(dir, src)))):
            for file in sorted(os.listdir(os.path.join(dir, src, label))):
                data['index'].append(os.path.join(dir, src, label, file))  
                data['labels'].append(None)  
                data['raw'].append(None)     
                data['uids'].append(None)    
                
                try:
                    uids = {}
                    with open(os.path.join(dir, src, label, file), 'r', encoding='latin1') as _f:
                        text = _f.read()
                        original_text = text 
                        text = remove_comment(text)
                        text = re.sub(r'^\s*#.*$', '', text, flags=re.MULTILINE)
                        
                    with open(os.path.join(dir, src, label, file), 'w', encoding='latin1') as _f:
                        _f.write(text)
                        
                    # ============ 【核心修改】：彻底抛弃 pycparser，使用纯正则分词 ============
                    tokens = safe_tokenize(text)
                    uid_set = extract_uids_regex(text)
                    
                    for i in range(len(tokens)):
                        if tokens[i] in uid_set:
                            if tokens[i] in uids.keys():
                                uids[tokens[i]].append(i)
                            else:
                                uids[tokens[i]] = [i]
                                
                    if len(tokens) >= min_len:
                        data['labels'][-1] = int(label) 
                        data['raw'][-1] = tokens           
                        data['uids'][-1] = uids             
                    else:
                        print(f"Skipped (too short): {os.path.join(dir, src, label, file)}")
                        
                except Exception as e:
                    print(f"Error processing {file}: {e}")

        with open(os.path.join(save_dir, tgt), "wb") as f:
            pickle.dump(data, f)
        
        return data
        
    except Exception as e:
        print(e)
        return None

def convertText2Raw(text):
    return safe_tokenize(text)

if __name__ == "__main__":
    if unzip():
        d = tokenize()