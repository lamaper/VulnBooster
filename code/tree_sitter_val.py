"""
基于 Tree-sitter 的代码语法质量控制模块 (Syntax Quality Control)

主要功能：
1. 代码纯净化处理：自动剥离 C/C++ 注释（行/块注释）及空行，消除冗余噪音。
2. 静态语法校验：基于清洗后的纯净代码构建 AST (Abstract Syntax Tree)，
   识别并剔除缺失函数体、括号不匹配、语句截断等结构性缺陷样本，确保训练特征池的绝对纯净。
"""

import os
import sys
import json
import re
from collections import deque
from tree_sitter import Parser, Language
import tree_sitter_c
import tree_sitter_cpp
from tqdm import tqdm

# 初始化跨语言解析环境配置 
C_LANGUAGE = Language(tree_sitter_c.language())
CPP_LANGUAGE = Language(tree_sitter_cpp.language())

# 实例化全局语法解析器
C_PARSER = Parser(C_LANGUAGE)
CPP_PARSER = Parser(CPP_LANGUAGE)


def remove_comments_and_blank_lines(code: str) -> str:
    """
    代码清洗函数：安全移除 C/C++ 源码中的注释及空行。
    利用正则匹配，跳过字符串与字符常量内部的 '//' 或 '/* */'，防止误删有效载荷。
    """
    if not code:
        return ""
        
    # 匹配规则：双引号字符串 | 单引号字符 | 块注释 | 行注释
    pattern = re.compile(
        r'(?P<string>"(?:\\.|[^\\"])*")|'
        r"(?P<char>'(?:\\.|[^\\'])*')|"
        r'(?P<block_comment>/\*.*?\*/)|'
        r'(?P<line_comment>//.*?$)',
        re.DOTALL | re.MULTILINE
    )

    def replacer(match):
        # 命中注释则替换为空字符串
        if match.group('block_comment') or match.group('line_comment'):
            return ""  
        # 命中字符串或字符常量则保留原样
        else:
            return match.group(0)  

    # 1. 移除注释
    code_no_comments = pattern.sub(replacer, code)
    
    # 2. 移除空行与纯空白行
    lines = [line for line in code_no_comments.splitlines() if line.strip()]
    
    return '\n'.join(lines)


def validate_ast_structure(root_node) -> bool:
    """
    单趟广度优先搜索 (BFS) 遍历 AST 树。
    替代原生递归，防范超深代码嵌套导致的 RecursionError。
    同时完成“函数定义域检查”与“严重语法错误拦截”。
    
    返回: bool (是否为合规的 C/C++ 函数代码)
    """
    has_func_def = False
    queue = deque([root_node])
    
    while queue:
        current = queue.popleft()
        
        # 一旦发现解析错误 (非法标识符) 或 Token 截断 (is_missing)，立刻判定非法
        if current.type == 'ERROR' or getattr(current, 'is_missing', False):
            return False
            
        # 探测是否存在完整的函数定义域
        if current.type == "function_definition":
            has_func_def = True
            
        for child in current.children:
            queue.append(child)
            
    return has_func_def


def is_valid_syntax(code: str) -> bool:
    """
    综合静态语法校验代理。
    利用 C 与 C++ 解析器的双重冗余机制，验证代码文本的句法合法性。
    """
    if not code or not code.strip():
        return False

    for parser in [C_PARSER, CPP_PARSER]:
        try:
            # 构建字节流并映射为抽象语法树 (AST)
            tree = parser.parse(bytes(code, "utf8"))
            root = tree.root_node

            # 根节点级错误筛查
            if root.has_error:
                continue
                
            # AST 深度遍历与合规性研判
            if validate_ast_structure(root):
                return True
                
        except Exception:
            # 捕获不可预见的底层 C 解析器异常，转交下一解析器
            continue
            
    return False


def filter_and_clean_jsonl(input_path: str, output_path: str):
    """
    标准化数据集清洗与过滤流水线。
    执行流式 I/O，先进行代码清洗（去注释/空行），再进行 AST 语法校验，最终安全落盘。
    """
    if not os.path.exists(input_path):
        print(f"[Error] 目标数据源不存在: {input_path}", file=sys.stderr)
        return

    os.makedirs(os.path.dirname(os.path.abspath(output_path)), exist_ok=True)

    print(f"\n[Info] 开始分析与清洗特征集: {os.path.basename(input_path)}")
    
    # 获取总行数以支持进度条 (避免 readlines 导致全量数据 OOM)
    with open(input_path, "r", encoding="utf-8") as f:
        total_samples = sum(1 for _ in f if _.strip())
        
    kept_samples = 0
    
    with open(input_path, "r", encoding="utf-8") as fin, \
         open(output_path, "w", encoding="utf-8") as fout:
             
        for line in tqdm(fin, total=total_samples, desc="[Process] AST Validation", unit="samples"):
            line = line.strip()
            if not line: 
                continue
            
            try:
                item = json.loads(line)
                original_code = item.get("func", "")
                
                # 先清洗代码，剥离注释与冗余空行
                cleaned_code = remove_comments_and_blank_lines(original_code)
                
                # 再对清洗后的纯净代码进行 AST 严苛校验
                if is_valid_syntax(cleaned_code):
                    item["func"] = cleaned_code
                    fout.write(json.dumps(item, ensure_ascii=False) + '\n')
                    kept_samples += 1
                    
            except json.JSONDecodeError:
                tqdm.write(f"[Warning] 检测到畸形 JSON 行数据，已触发静默隔离。")
                continue
                
    drop_rate = ((total_samples - kept_samples) / total_samples * 100) if total_samples > 0 else 0
    print(f"[Task Report] {os.path.basename(input_path)} 语法质量管控作业完成。")
    print(f"  - 输入总样本数: {total_samples} 项")
    print(f"  - 校验通过并保留: {kept_samples} 项")
    print(f"  - 非法样本拦截率: {drop_rate:.2f}%")
    print(f"  - 数据归档路径: {output_path}\n")


# =====================================================================
# 全局运行态与路径配置
# =====================================================================
RUN_MODE = "smoke" 
CURRENT_ITERATION = 1 

def main():
    # ==================== [命令行调用模式] ====================
    if len(sys.argv) == 3:
        filter_and_clean_jsonl(sys.argv[1], sys.argv[2])
        sys.exit(0)
        
    # ============================================================
    # 消融实验配置 3：移除漏洞特征提取方案
    # 校验无特征提取模型产生的增强样本
    # ============================================================
    if RUN_MODE == "smoke":
        base_path = f"../slice/smoke/ablation_3_no_feature_extract/iteration{CURRENT_ITERATION}"
    else:
        base_path = f"../slice/deepseek/ablation_3_no_feature_extract/iteration{CURRENT_ITERATION}"

    # ============================================================
    # 标准流水线配置（完整系统方案）
    # ============================================================
    # if RUN_MODE == "smoke":
    #     base_path = f"../slice/smoke/iteration{CURRENT_ITERATION}"
    # else:
    #     base_path = f"../slice/deepseek/iteration{CURRENT_ITERATION}"

    print(f"\n{'='*60}")
    print(f"[Task] 启动代码语法质量控制与清洗模块 (消融配置 3)")
    print(f"       运行环境: {RUN_MODE.upper()} | 迭代层级: Iteration {CURRENT_ITERATION}")
    print(f"{'='*60}")
    
    # ---------------------------------------------------------
    # 1. 验证 CWE 知识增强特征集
    # ---------------------------------------------------------
    cwe_input = os.path.join(base_path, "val_cwe.jsonl")
    cwe_output = os.path.join(base_path, "val_cwe_validated.jsonl")
    
    if os.path.exists(cwe_input):
        print(f"\n[Task] 启动 CWE 拓展特征集语法校验流水线...")
        filter_and_clean_jsonl(cwe_input, cwe_output)
    else:
        print(f"\n[Skip] 依赖寻址跳过：未定位到 CWE 增强产物 ({cwe_input})")

    # ---------------------------------------------------------
    # 2. 验证 CoT 逻辑繁衍特征集
    # ---------------------------------------------------------
    cot_input = os.path.join(base_path, "val_cot.jsonl")
    cot_output = os.path.join(base_path, "val_cot_validated.jsonl")
    
    if os.path.exists(cot_input):
        print(f"\n[Task] 启动 CoT 繁衍特征集语法校验流水线...")
        filter_and_clean_jsonl(cot_input, cot_output)
    else:
        print(f"\n[Skip] 依赖寻址跳过：未定位到 CoT 增强产物 ({cot_input})")


if __name__ == "__main__":
    main()