"""
基础数据集静态特征纯净化模块 (Dataset Sanitization Module)

主要功能：
1. 冗余注释剥离：利用正则状态机安全剔除 C/C++ 源码中的块注释 (/*...*/) 与行注释 (//...)，同时保证字符串常量的完整性。
2. 冗余空白符清理：将连续的空格或制表符收敛为单一空格，并剔除行首尾空白。
3. 冗余空行折叠：消除代码中的无意义空行，提高代码的语义密度，为下游模型 (如 CodeBERT) 提供高信噪比的输入特征。
"""
import os
import sys
import json
import re
from pathlib import Path
from tqdm import tqdm

def clean_c_code(code: str) -> str:
    """
    静态代码清洗引擎：
    执行去注释、去冗余空格与去空行操作。
    """
    if not code:
        return ""

    # ==========================================
    # 1. 安全移除注释 (规避字符串内部的干扰)
    # ==========================================
    # 匹配规则：双引号字符串 | 单引号字符 | 块注释 | 行注释
    pattern = re.compile(
        r'(?P<string>"(?:\\.|[^\\"])*")|'
        r"(?P<char>'(?:\\.|[^\\'])*')|"
        r'(?P<block_comment>/\*.*?\*/)|'
        r'(?P<line_comment>//.*?$)',
        re.DOTALL | re.MULTILINE
    )

    def replacer(match):
        # 若命中注释组，则替换为空
        if match.group('block_comment') or match.group('line_comment'):
            return ""  
        # 若命中字符串/字符常量，则原样保留
        else:
            return match.group(0)  

    code_no_comments = pattern.sub(replacer, code)
    
    # ==========================================
    # 2. 清理冗余空格与空行
    # ==========================================
    cleaned_lines = []
    for line in code_no_comments.splitlines():
        # 将连续的空格或制表符收敛为单一空格，并剔除首尾空白
        line_stripped = re.sub(r'[ \t]+', ' ', line).strip()
        
        # 抛弃纯空行
        if line_stripped:
            cleaned_lines.append(line_stripped)
            
    return '\n'.join(cleaned_lines)


def process_clean_pipeline(input_file: str, output_file: str):
    """
    数据集单文件清洗流水线：
    支持大文件的流式 I/O，并保留除 func 以外的所有原始元数据。
    """
    if not os.path.exists(input_file):
        print(f"[Error] 数据源不存在，跳过清洗任务: {input_file}", file=sys.stderr)
        return

    output_path = Path(output_file)
    output_path.parent.mkdir(parents=True, exist_ok=True)

    print(f"\n[Info] 开始清洗特征集: {os.path.basename(input_file)}")
    
    # 快速统计总行数以驱动进度条
    with open(input_file, 'r', encoding='utf-8') as fin:
        total_samples = sum(1 for _ in fin if _.strip())

    if total_samples == 0:
        print("[Warning] 输入文件内容为空。")
        return

    success_count = 0
    error_count = 0

    with open(input_file, 'r', encoding='utf-8') as fin, \
         open(output_file, 'w', encoding='utf-8') as fout:
             
        for line in tqdm(fin, total=total_samples, desc="[Process] Code Sanitization", unit=" samples"):
            line = line.strip()
            if not line:
                continue
                
            try:
                data = json.loads(line)
                original_code = data.get("func", "")
                
                # 执行代码提纯
                cleaned_code = clean_c_code(original_code)
                
                # 覆写原始代码，其他元数据（idx, target, cwe 等）均安全保留
                data["func"] = cleaned_code
                
                fout.write(json.dumps(data, ensure_ascii=False) + '\n')
                success_count += 1
                
            except json.JSONDecodeError:
                error_count += 1
                continue

    print(f"[Task Report] {os.path.basename(output_file)} 清洗作业完成。")
    print(f"  - 参与清洗总样本数: {total_samples} 项")
    print(f"  - 成功清洗并落盘: {success_count} 项")
    if error_count > 0:
        print(f"  - [Warning] 剔除畸形 JSON 结构: {error_count} 项")
    print(f"  - 数据归档路径: {output_path.resolve()}")


if __name__ == "__main__":
    print(f"\n{'='*60}")
    print(f"启动基础数据集代码纯净化模块 (Dataset Sanitization)")
    print(f"{'='*60}")

    # =================================================================
    # 1. 全量生产环境作业池 
    # =================================================================
    """
    DATA_DIR_FULL = "../dataset"
    print(f"\n[Task] 启动全量生产环境数据清洗作业...")
    
    process_clean_pipeline(
        input_file=f"{DATA_DIR_FULL}/primevul_train.jsonl",
        output_file=f"{DATA_DIR_FULL}/primevul_train_cleaned.jsonl"
    )
    process_clean_pipeline(
        input_file=f"{DATA_DIR_FULL}/primevul_valid.jsonl",
        output_file=f"{DATA_DIR_FULL}/primevul_valid_cleaned.jsonl"
    )
    process_clean_pipeline(
        input_file=f"{DATA_DIR_FULL}/primevul_test.jsonl",
        output_file=f"{DATA_DIR_FULL}/primevul_test_cleaned.jsonl"
    )
    print("\n[Info] 全量生产环境清洗作业执行完毕。")
    """

    # =================================================================
    # 2. 冒烟测试环境 (Smoke Test) 作业池
    # =================================================================
    DATA_DIR_SMOKE = "../smoke"
    print(f"\n[Task] 启动 Smoke 测试沙盒环境数据清洗作业...")
    
    process_clean_pipeline(
        input_file=f"{DATA_DIR_SMOKE}/primevul_train.jsonl",
        output_file=f"{DATA_DIR_SMOKE}/primevul_train_cleaned.jsonl"
    )
    process_clean_pipeline(
        input_file=f"{DATA_DIR_SMOKE}/primevul_valid.jsonl",
        output_file=f"{DATA_DIR_SMOKE}/primevul_valid_cleaned.jsonl"
    )
    process_clean_pipeline(
        input_file=f"{DATA_DIR_SMOKE}/primevul_test.jsonl",
        output_file=f"{DATA_DIR_SMOKE}/primevul_test_cleaned.jsonl"
    )
    
    print(f"\n{'='*60}")
    print(f"[Info] 所有数据集静态代码提纯任务执行完毕。请核对输出文件。")
    print(f"{'='*60}")