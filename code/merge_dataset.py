"""
数据集增量合并与去重模块 (Dataset Merge Module)

主要功能：
将大语言模型 (LLM) 生成的定向增强数据（CoT / CWE）与基准训练集进行合并。
采用增量扩充机制，并基于样本主键 (idx) 提供严格的全局去重，输出供下一轮微调使用的高质量训练集。
"""
import os
import json
import sys
from pathlib import Path
from tqdm import tqdm

def robust_merge_jsonl(input_files: list, output_file: str, task_desc: str) -> bool:
    """
    具备幂等性与主键去重机制的数据合并函数。
    采用文件流逐行读取机制，防止在处理全量大规模数据集时发生内存溢出 (OOM)。
    """
    valid_files = [f for f in input_files if os.path.exists(f)]
    
    if not valid_files:
        print(f"[Error] 合并队列为空或输入文件均不存在，当前合并任务终止。", file=sys.stderr)
        return False

    output_path = Path(output_file)
    output_path.parent.mkdir(parents=True, exist_ok=True)

    print(f"\n{'='*60}")
    print(f"[Task] 开始执行数据集合并作业: {task_desc}")
    print(f"  - 输入数据分片数: {len(valid_files)}")
    print(f"  - 目标输出路径: {output_path.resolve()}")
    print(f"{'='*60}")
    
    seen_idxs = set()
    total_written = 0
    duplicate_count = 0

    with open(output_path, 'w', encoding='utf-8') as fout:
        for file_path in valid_files:
            file_size_mb = os.path.getsize(file_path) / (1024 * 1024)
            print(f"\n[Info] 正在加载数据分片: {os.path.basename(file_path)} ({file_size_mb:.2f} MB)")
            
            with open(file_path, 'r', encoding='utf-8') as fin:
                for line in tqdm(fin, desc=f"[Process] 合并写入", leave=False, unit=" samples"):
                    line = line.strip()
                    if not line: 
                        continue
                    
                    try:
                        data = json.loads(line)
                        raw_idx = data.get("idx")
                        
                        # 完整性校验：拦截缺少主键的异常样本
                        if raw_idx is None:
                            continue
                        
                        # 将主键转换为字符串，防范跨文件 JSON 类型推断不一致导致的去重失效
                        idx_str = str(raw_idx)
                        
                        # 基于全局唯一标识符进行严格去重
                        if idx_str in seen_idxs:
                            duplicate_count += 1
                            continue
                            
                        seen_idxs.add(idx_str)
                        fout.write(line + '\n')
                        total_written += 1
                        
                    except json.JSONDecodeError:
                        continue

    print(f"\n[Task Report] 数据集重组与合并作业完成。")
    print(f"  - 有效写入样本总数: {total_written} 项")
    if duplicate_count > 0:
        print(f"  - [Clean] 成功拦截并剔除重复样本: {duplicate_count} 项")
    print(f"{'='*60}\n")
    return True


def build_iterative_dataset(dataset_type: str, iteration_num: int):
    """
    构建包含历史基线特征与本轮增量变体特征的闭环微调数据集。
    支持在标准增强与各消融实验配置之间灵活切换。
    """
    iter_name = f"iteration{iteration_num}"
    
    # ============================================================
    # 消融实验配置 3：移除漏洞特征提取方案
    # 挂载原始基线数据与未经过滤精炼的语法验证增强数据
    # ============================================================
    base_dir = f"../slice/{dataset_type}/ablation_3_no_feature_extract"
    
    # 1. 确定基准训练集输入路径
    if iteration_num == 1:
        if dataset_type == "smoke":
            base_train = "../smoke/primevul_train_cleaned.jsonl"
        else:
            base_train = "../dataset/primevul_train_cleaned.jsonl"
        print(f"[Info] 识别为 Iteration 1，加载 [原始长函数清洗训练集] 作为基础数据源。")
    else:
        prev_iter_name = f"iteration{iteration_num - 1}"
        base_train = os.path.join(base_dir, prev_iter_name, "raw_aug_train.jsonl")
        print(f"[Info] 识别为 Iteration {iteration_num}，加载前序 ({prev_iter_name}) [增量增强原始集] 作为基础数据源。")
        
    if not os.path.exists(base_train):
        print(f"[Error] 无法定位基础数据源，合并流程被迫中断: {base_train}", file=sys.stderr)
        return
    
    # 2. 挂载本轮仅经过 Tree-sitter 校验的增强数据 (无特征提取)
    enhanced_cot = os.path.join(base_dir, iter_name, "val_cot_validated.jsonl")
    enhanced_cwe = os.path.join(base_dir, iter_name, "val_cwe_validated.jsonl")

    input_files = [base_train, enhanced_cot, enhanced_cwe]
    
    # 3. 设定合并输出路径，存入当前迭代专属目录，命名为 raw_aug_train.jsonl
    output_file = os.path.join(base_dir, iter_name, "raw_aug_train.jsonl")

    robust_merge_jsonl(
        input_files=input_files,
        output_file=output_file,
        task_desc=f"增量微调数据集装配 - 消融配置 3 ({dataset_type} - {iter_name})"
    )

    # ============================================================
    # 准流水线配置（完整系统方案）
    # 支持自适应切换 full (deepseek) 与 smoke 模式
    # ============================================================
    # base_dir = f"../slice/{dataset_type}"
    # 
    # if iteration_num == 1:
    #     base_train = os.path.join(base_dir, "refined_train.jsonl")
    #     print(f"[Info] 识别为 Iteration 1，加载初始精炼训练集作为基础数据源。")
    # else:
    #     prev_iter_name = f"iteration{iteration_num - 1}"
    #     base_train = os.path.join(base_dir, prev_iter_name, "refined_train.jsonl")
    #     print(f"[Info] 识别为 Iteration {iteration_num}，加载前序 ({prev_iter_name}) 增量训练集作为基础数据源。")
    #     
    # if not os.path.exists(base_train):
    #     print(f"[Error] 无法定位基础数据源，合并流程被迫中断: {base_train}", file=sys.stderr)
    #     return
    # 
    # enhanced_cot = os.path.join(base_dir, iter_name, "val_cot_validated_refined.jsonl")
    # enhanced_cwe = os.path.join(base_dir, iter_name, "val_cwe_validated_refined.jsonl")
    # 
    # input_files = [base_train, enhanced_cot, enhanced_cwe]
    # output_file = os.path.join(base_dir, iter_name, "refined_train.jsonl")
    #
    # robust_merge_jsonl(
    #     input_files=input_files,
    #     output_file=output_file,
    #     task_desc=f"增量微调数据集装配 ({dataset_type} - {iter_name})"
    # )


if __name__ == "__main__":
    
    # ==================== [运行环境变量配置] ====================
    # 支持在全量生产环境 (deepseek) 与开发沙盒环境 (smoke) 间切换
    DATASET_TYPE = "smoke"   
    TARGET_ITERATION = 1  
    
    # ============================================================
    # 消融实验配置 3：移除漏洞特征提取方案
    # ============================================================
    print(f"\n{'='*60}")
    print(f"启动数据集增量合并模块 - 消融配置 3 (Dataset: {DATASET_TYPE} | Target Iteration: {TARGET_ITERATION})")
    print(f"{'='*60}")
    
    build_iterative_dataset(dataset_type=DATASET_TYPE, iteration_num=TARGET_ITERATION)

    # ============================================================
    # 标准流水线配置（完整系统方案）
    # ============================================================
    # print(f"\n{'='*60}")
    # print(f"启动数据集增量合并模块 (Dataset: {DATASET_TYPE} | Target Iteration: {TARGET_ITERATION})")
    # print(f"{'='*60}")
    #
    # build_iterative_dataset(dataset_type=DATASET_TYPE, iteration_num=TARGET_ITERATION)