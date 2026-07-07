"""
系统级代码属性图 (CPG) 构建与静态切片流水线
核心功能：
1. 源码解析：将 JSONL 格式数据集逆向反序列化为独立 C/C++ 物理文件。
2. 拓扑编译：调用 Joern 引擎生成中间态程序属性图 (CPG)。
3. 切片提取：基于底层 Scala 脚本 (slice.sc) 执行图深度遍历，提取漏洞/安全切片。
"""
import json
import os
import subprocess
from pathlib import Path
from tqdm import tqdm

# =====================================================================
# 系统运行环境配置中心 (跨平台适配)
# =====================================================================
# [Windows 环境配置] (当前默认激活，依赖批处理脚本)
JOERN_PARSE_CMD = 'joern-parse.bat'
JOERN_CMD = 'joern.bat'

# [Ubuntu/Linux 环境配置] 
# 部署至远端 Linux 服务器时，请取消下方注释，并注释掉上方的 Windows 配置
# JOERN_PARSE_CMD = 'joern-parse'
# JOERN_CMD = 'joern'

# =====================================================================
# 阶段 1：源代码提取与物理持久化模块 (JSONL -> C)
# =====================================================================
def prepare_dataset(input_path, output_path):
    """
    将原始数据集中的 func 字段提取并落盘为物理文件，以供图引擎编译。
    """
    if not os.path.exists(input_path):
        print(f"[致命错误] 数据集索引文件未命中: {input_path}")
        return 0

    with open(input_path, 'r', encoding='utf-8') as f:
        lines = f.readlines()

    total_processed = 0
    for line in tqdm(lines, desc="[阶段 1] 源码解析与物理持久化", unit="样本"):
        line = line.strip()
        if not line: 
            continue
        try:
            data = json.loads(line)
        except json.JSONDecodeError: 
            continue

        func = data.get('func', '')
        idx  = data.get('idx', 'unknown')
        target = data.get('target', 0)
        
        output_c_path = os.path.join(output_path, f"{idx}_{target}.c")
        with open(output_c_path, 'w', encoding='utf-8') as f_out:
            f_out.write(func + "\n")
        total_processed += 1
            
    return total_processed

# =====================================================================
# 阶段 2：代码属性图 (CPG) 编译流水线模块
# =====================================================================
def parse_single_file(c_path, output_path, timeout=300):
    """
    调用底层 Joern-parse 将单一 C/C++ 源码编译为二进制 CPG 图拓扑。
    """
    try:
        cmd = [JOERN_PARSE_CMD, c_path, '--output', output_path]
        result = subprocess.run(
            cmd, capture_output=True, text=True, encoding='utf-8', 
            errors='ignore', shell=True, timeout=timeout
        )
        if result.returncode == 0:
            return {'status': 'success', 'file': c_path, 'cpg': output_path}
        else:
            return {'status': 'error', 'file': c_path, 'error': result.stderr}
    except subprocess.TimeoutExpired:
        return {'status': 'timeout', 'file': c_path}
    except Exception as e:
        return {'status': 'exception', 'file': c_path, 'error': str(e)}

def generate_cpg(input_path, c_path, cpg_path):
    """
    批量调度器：管理目标目录下所有源码的 CPG 编译生命周期。
    """
    with open(input_path, 'r', encoding='utf-8') as f:
        lines = f.readlines()

    success_count = 0
    fail_count = 0
    
    pbar = tqdm(lines, desc="[阶段 2] CPG 抽象语法图编译", unit="文件")
    for line in pbar:
        line = line.strip()
        if not line: 
            continue
        try:
            data = json.loads(line)
        except json.JSONDecodeError: 
            continue

        idx  = data.get('idx', 'unknown')
        target = data.get('target', 0)

        c_file_path = os.path.join(c_path, f"{idx}_{target}.c")
        cpg_file_path = os.path.join(cpg_path, f"{idx}_{target}.cpg.bin")
        
        res = parse_single_file(c_file_path, cpg_file_path)
        if res.get('status') == 'success':
            success_count += 1
        else:
            fail_count += 1
            err_msg = res.get('error', 'Timeout/Error')
            tqdm.write(f"[编译异常] 文件 {idx}_{target}.c 编译崩溃: {err_msg[:100]}...")

    return success_count

# =====================================================================
# 阶段 3：依赖图拓扑双向切片追踪模块
# =====================================================================
def run_joern_script(cpg_path, output_path, scala_script, source_root, target, sample_id):
    """
    执行 Scala 外部扩展脚本，通过 REACHING_DEF 与 CDG 边进行切片追踪提取。
    """
    env = os.environ.copy()
    if source_root: 
        env["JOERN_SOURCE_ROOT"] = source_root
    env["TARGET_CPG_PATH"] = cpg_path

    cmd = [JOERN_CMD, "--script", scala_script]
    result = subprocess.run(
        cmd, capture_output=True, text=True, encoding='utf-8', 
        errors='ignore', timeout=600, env=env, shell=True
    )
    
    if result.returncode != 0:
        if result.stderr:
            tqdm.write(f"[脚本异常] 样本 {sample_id} 运行时崩溃: {result.stderr[:100]}...")
        return False
    
    output_file = Path(output_path)
    output_file.parent.mkdir(parents=True, exist_ok=True)
    
    jsonl_count = 0
    with open(output_file, 'a', encoding='utf-8') as f:
        for line in result.stdout.strip().split('\n'):
            line = line.strip()
            if not line or line.startswith('[*]') or line.startswith('[!]'): 
                continue
            try:
                data = json.loads(line)
                data['fromIdx'] = sample_id
                data['target'] = target
                f.write(json.dumps(data, ensure_ascii=False) + '\n')
                jsonl_count += 1
            except Exception: 
                pass
    
    return jsonl_count > 0

# =====================================================================
# 核心调度器：将 1-3 阶段打包为标准流水线单元
# =====================================================================
def run_full_pipeline_for_dataset(input_index_file, c_output_dir, cpg_output_dir, final_result_file, task_name):
    """
    封装完整的静态分析生命周期，管理进程间的 I/O 挂载。
    """
    print(f"\n{'='*60}")
    print(f"[任务调度] 启动图谱切片流水线作业: {task_name}")
    print(f"{'='*60}")
    
    if not os.path.exists(input_index_file):
        print(f"[调度终止] 无法挂载输入流，未找到索引文件: {input_index_file}")
        return

    Path(c_output_dir).mkdir(parents=True, exist_ok=True)
    Path(cpg_output_dir).mkdir(parents=True, exist_ok=True)

    prepare_dataset(input_index_file, c_output_dir)
    generate_cpg(input_index_file, c_output_dir, cpg_output_dir)
    
    with open(input_index_file, 'r', encoding='utf-8') as f:
        lines = f.readlines()
        
    success_slices = 0
    for line in tqdm(lines, desc="[阶段 3] 图拓扑遍历与切片生成", unit="次"):
        line = line.strip()
        if not line: 
            continue
        try:
            data = json.loads(line)
        except json.JSONDecodeError: 
            continue
        
        idx    = data.get('idx')
        target = data.get('target')  
        
        safe_cpg_path    = os.path.abspath(f"{cpg_output_dir}/{idx}_{target}.cpg.bin").replace("\\", "/")
        safe_output_path = os.path.abspath(final_result_file).replace("\\", "/")
        safe_script_path = os.path.abspath("../slice/slice.sc").replace("\\", "/")
        safe_source_root = os.path.abspath(c_output_dir).replace("\\", "/")

        status = run_joern_script(
            cpg_path=safe_cpg_path, 
            output_path=safe_output_path, 
            scala_script=safe_script_path, 
            source_root=safe_source_root, 
            target=target, 
            sample_id=idx 
        )
        if status: 
            success_slices += 1
            
    print(f"[流程终止] 任务 {task_name} 执行完毕。成功解析切片数: {success_slices} 项。")
    print(f"           归档目标基址: {final_result_file}")


# =====================================================================
# 自动化执行总线
# =====================================================================
if __name__ == "__main__":
    
    # =================================================================
    # 全量模式 (Full Pipeline)
    # =================================================================
    """
    # 1. 全量 - 初始数据集切片
    run_full_pipeline_for_dataset(
        input_index_file = "../dataset/primevul_train_cleaned.jsonl",
        c_output_dir     = "../slice/deepseek/train_c",
        cpg_output_dir   = "../slice/deepseek/train_cpg",
        final_result_file= "../slice/deepseek/joern_sliced_train.jsonl",
        task_name        = "Full_Train_Set_Pipeline"
    )

    run_full_pipeline_for_dataset(
        input_index_file = "../dataset/primevul_valid_cleaned.jsonl",
        c_output_dir     = "../slice/deepseek/valid_c",
        cpg_output_dir   = "../slice/deepseek/valid_cpg",
        final_result_file= "../slice/deepseek/joern_sliced_valid.jsonl",
        task_name        = "Full_Validation_Set_Pipeline"
    )

    run_full_pipeline_for_dataset(
        input_index_file = "../dataset/primevul_test_cleaned.jsonl",
        c_output_dir     = "../slice/deepseek/test_c",
        cpg_output_dir   = "../slice/deepseek/test_cpg",
        final_result_file= "../slice/deepseek/joern_sliced_test.jsonl",
        task_name        = "Full_Test_Set_Pipeline"
    )

    # 2. 全量 - 迭代训练中漏洞漏报阶段 (以 Iteration 1 为例)
    run_full_pipeline_for_dataset(
        input_index_file = "../slice/deepseek/iteration1/val_cot_validated.jsonl",
        c_output_dir     = "../slice/deepseek/iteration1/val_cot_c",
        cpg_output_dir   = "../slice/deepseek/iteration1/val_cot_cpg",
        final_result_file= "../slice/deepseek/iteration1/val_cot_validated_joern_sliced.jsonl",
        task_name        = "Full_Iteration1_Val_Cot_Pipeline"
    )

    run_full_pipeline_for_dataset(
        input_index_file = "../slice/deepseek/iteration1/val_cwe_validated.jsonl",
        c_output_dir     = "../slice/deepseek/iteration1/val_cwe_c",
        cpg_output_dir   = "../slice/deepseek/iteration1/val_cwe_cpg",
        final_result_file= "../slice/deepseek/iteration1/val_cwe_validated_joern_sliced.jsonl",
        task_name        = "Full_Iteration1_Val_Cwe_Pipeline"
    )
    """

    # =================================================================
    # 冒烟测试模式 (Smoke Pipeline)
    # =================================================================
    # 3. Smoke - 初始数据集切片
    """
    run_full_pipeline_for_dataset(
        input_index_file = "../smoke/primevul_train_cleaned.jsonl",
        c_output_dir     = "../slice/smoke/train_c",
        cpg_output_dir   = "../slice/smoke/train_cpg",
        final_result_file= "../slice/smoke/joern_sliced_train.jsonl",
        task_name        = "Smoke_Train_Set_Pipeline"
    )

    run_full_pipeline_for_dataset(
        input_index_file = "../smoke/primevul_valid_cleaned.jsonl",
        c_output_dir     = "../slice/smoke/valid_c",
        cpg_output_dir   = "../slice/smoke/valid_cpg",
        final_result_file= "../slice/smoke/joern_sliced_valid.jsonl",
        task_name        = "Smoke_Validation_Set_Pipeline"
    )

    run_full_pipeline_for_dataset(
        input_index_file = "../smoke/primevul_test_cleaned.jsonl",
        c_output_dir     = "../slice/smoke/test_c",
        cpg_output_dir   = "../slice/smoke/test_cpg",
        final_result_file= "../slice/smoke/joern_sliced_test.jsonl",
        task_name        = "Smoke_Test_Set_Pipeline"
    )
    """
    
    # 4. Smoke - 迭代训练中漏洞漏报阶段 (以 Iteration 1 为例)
    run_full_pipeline_for_dataset(
        input_index_file = "../slice/smoke/iteration1/val_cot_validated.jsonl",
        c_output_dir     = "../slice/smoke/iteration1/val_cot_c",
        cpg_output_dir   = "../slice/smoke/iteration1/val_cot_cpg",
        final_result_file= "../slice/smoke/iteration1/val_cot_validated_joern_sliced.jsonl",
        task_name        = "Smoke_Iteration1_Val_Cot_Pipeline"
    )

    run_full_pipeline_for_dataset(
        input_index_file = "../slice/smoke/iteration1/val_cwe_validated.jsonl",
        c_output_dir     = "../slice/smoke/iteration1/val_cwe_c",
        cpg_output_dir   = "../slice/smoke/iteration1/val_cwe_cpg",
        final_result_file= "../slice/smoke/iteration1/val_cwe_validated_joern_sliced.jsonl",
        task_name        = "Smoke_Iteration1_Val_Cwe_Pipeline"
    )
    

    print("\n[全局通知] 激活的切片流水线作业已执行完毕。请检查归档产物以验证连通性。")