"""
基于大语言模型 (LLM) 的特征初筛与语义切片提取模块 (LLM Pre-filter)

主要功能：
严格遵循预设的单轨提示词模板，通过异步高并发网络请求，
从原始 C/C++ 源码中提取具有高语义密度的代码切片 (Vulnerability-Relevant Region)。

容错与数据流机制：
1. 字段清洗：执行严格的白名单策略，仅保留模型训练所需的核心字段。
2. 异常降级：若大模型提取失败或触发模型安全限制，严格输出空字符串 ("")，将降级决策权交由下游融合模块处理。
3. 函数头修补 (Header Stitching)：自动检测并补全有效切片缺失的函数签名，保证语法树 (AST) 解析完整性。
4. 状态追踪：精准记录每个样本的提取状态，输出结构化的任务执行报告。
"""
import json
import os
import re
import asyncio
import sys
from pathlib import Path
from openai import AsyncOpenAI
from tqdm.asyncio import tqdm

# =====================================================================
# 大语言模型 (LLM) 异步接口与并发控制配置
# =====================================================================
API_KEY = "sk-xxxxxxxxxxxxxxxxxxx"
BASE_URL = "https://api.deepseek.com"  
MODEL_NAME = "deepseek-coder"            

CONCURRENCY_LIMIT = 500
MAX_RETRIES = 3
BASE_RETRY_DELAY = 2.0

aclient = AsyncOpenAI(api_key=API_KEY, base_url=BASE_URL)

TICK3 = "```"

# =====================================================================
# 提示词模板 (Prompt Template)
# =====================================================================
SYSTEM_PROMPT = (
    "You are an expert C/C++ security analyst. Your task is to extract a semantically complete, "
    "concise Vulnerability-Relevant Region from the provided function. Strictly follow the extraction "
    "rules provided in the user message and output only the final code block."
)

USER_PROMPT_TEMPLATE = f"""Please analyze the following C/C++ function and Extract the Vulnerability-Relevant Region by strictly adhering to the rules below:

[Extraction Rules]

1. Identify the Vulnerability Seed: Locate the exact vulnerable lines. Prioritize modified lines if diff context is implied.

2. Expand via Data Dependency: Include definitions and sources of variables used in the vulnerable line. Trace back to untrusted inputs.

3. Expand via Control Dependency: Include conditional statements that guard or trigger the vulnerable line. If the vulnerability stems from a MISSING check, include the surrounding logic demonstrating the absence of validation.

4. Basic Block Closure: Ensure the snippet contains the complete basic block. Do not truncate mid-logic.

5. Length & Density Control: Target 5-20 lines demonstrating a 'Context + Action' pattern. Avoid single-line extractions without context. Exclude unrelated utility code, comments, or distant functions.

[Output Constraints]

- Return ONLY the extracted code within a single {TICK3}cpp block.

- Preserve original indentation, variable names, and line structure.

- Ensure the snippet is syntactically self-contained and independently understandable.

[Function to Analyze]

{TICK3}cpp
{{code}}
{TICK3}"""

# =====================================================================
# 代码提纯与合规性校验机制
# =====================================================================
def extract_pure_code_slice(response_text: str) -> tuple[str, bool]:
    """
    合规性校验与正则提纯：剥离 LLM 输出的 Markdown 包装层及内在推理过程。
    提取失败时严格返回空字符串，真实暴露模型能力边界。
    返回: (提取出的纯净代码字符串, 提取状态布尔值)
    """
    if not response_text:
        return "", False
        
    text_no_think = re.sub(r'<think>.*?</think>', '', response_text, flags=re.DOTALL | re.IGNORECASE).strip()
    
    # 尝试宽容正则匹配提取代码块
    pattern = re.compile(TICK3 + r'(?:cpp|c|c\+\+)?\s*\n?(.*?)\n?\s*' + TICK3, re.DOTALL | re.IGNORECASE)
    matches = pattern.findall(text_no_think)
    
    is_success = False
    if matches:
        extracted = matches[0].strip()
        is_success = True
    else:
        # 若模型未提供 Markdown 标记，但内容包含 C 语言基本闭合特征，判定为有效提取
        if "{" in text_no_think and ";" in text_no_think:
            extracted = text_no_think.strip()
            is_success = True
        else:
            return "", False

    # 语义合规拦截：若模型明确表示无法识别漏洞特征，则判定为提取失败
    lower_text = extracted.lower()
    if "no vulnerability" in lower_text or "cannot identify" in lower_text:
        return "", False
            
    # 长度阈值拦截：防范无意义的极短异常字符组合
    if len(extracted) < 10:
        return "", False
        
    return extracted, is_success

def stitch_function_header(refined_code: str, original_code: str) -> str:
    """
    函数头自动修补机制 (Header Stitching)：
    检测提取出的初筛切片是否缺失函数签名。若缺失，则从原始长代码中截取函数头进行缝合。
    """
    if not refined_code or not original_code:
        return refined_code
        
    first_line = refined_code.strip().split('\n')[0].strip()
    
    is_missing_header = False
    if re.match(r'^(if|while|for|return|switch|else|do|try|catch)\b', first_line, re.IGNORECASE):
        is_missing_header = True
    elif not re.search(r'\w+\s*\(.*?\)', first_line):
        is_missing_header = True
        
    if is_missing_header:
        header_match = re.search(r'^(.*?\{)', original_code, re.DOTALL)
        if header_match:
            header = header_match.group(1).strip()
            return f"{header}\n{refined_code}\n}}"
            
    return refined_code

# =====================================================================
# 异步请求与调度引擎
# =====================================================================
async def analyze_code_async(func_code: str, semaphore: asyncio.Semaphore) -> str:
    """
    发起大语言模型异步分析请求，执行提示词装配及异常捕获重试。
    """
    user_content = USER_PROMPT_TEMPLATE.replace("{code}", func_code)
    
    for attempt in range(MAX_RETRIES):
        try:
            async with semaphore:
                response = await aclient.chat.completions.create(
                    model=MODEL_NAME,
                    messages=[
                        {"role": "system", "content": SYSTEM_PROMPT},
                        {"role": "user", "content": user_content}
                    ],
                    temperature=0.1,  
                    max_tokens=2048,
                    timeout=40.0  
                )
                content = response.choices[0].message.content
                if not content or not content.strip():
                    raise ValueError("API 返回内容为空。")
                return content
                
        except Exception as e:
            error_msg = str(e).lower()
            if "401" in error_msg or "authentication" in error_msg or "insufficient_quota" in error_msg:
                raise RuntimeError(f"[Error] API 鉴权失败或额度不足。详细日志: {e}")
            
            if attempt == MAX_RETRIES - 1:
                tqdm.write(f"\n[Warning] API 请求超时或失败 (已达最大重试次数): {str(e)}")
                return ""  
            
            await asyncio.sleep(BASE_RETRY_DELAY * (2 ** attempt))
    return ""

async def process_single_item(data: dict, semaphore: asyncio.Semaphore) -> dict:
    """
    单样本特征处理协程：执行白名单字段过滤、提取请求调用及状态追踪打标。
    """
    cleaned_data = {
        "idx": data.get("idx"),
        "func": data.get("func", ""),
        "target": data.get("target"),
        "cwe": data.get("cwe", []),
        "cve": data.get("cve", [])
    }
    
    func_code = cleaned_data['func']
    if not func_code:
        cleaned_data['llm_slice'] = ""
        cleaned_data['filter_status'] = 'empty_input'
        return cleaned_data

    llm_result = await analyze_code_async(func_code, semaphore)
    
    if llm_result:
        pure_slice, is_success = extract_pure_code_slice(llm_result)
        
        if is_success:
            # 成功提取有效代码块，执行函数头修补以保障 AST 完整性
            stitched_slice = stitch_function_header(pure_slice, func_code)
            cleaned_data['llm_slice'] = stitched_slice
            
            if stitched_slice.strip() == func_code.strip():
                cleaned_data['filter_status'] = 'filtered_but_unmodified'
            else:
                cleaned_data['filter_status'] = 'filtered_by_llm'
        else:
            # 提取失败或模型未返回有效代码特征，强制清空以供下游决策
            cleaned_data['llm_slice'] = ""
            cleaned_data['filter_status'] = 'format_invalid_or_refusal'
    else:
        # 网络请求异常或持续无响应，强制清空
        cleaned_data['llm_slice'] = ""
        cleaned_data['filter_status'] = 'api_error'
        
    return cleaned_data

async def run_batch_processing(lines: list) -> list:
    """
    批量任务调度器：初始化异步任务池并聚合协程执行结果。
    """
    semaphore = asyncio.Semaphore(CONCURRENCY_LIMIT)
    tasks = []
    
    for line in lines:
        line = line.strip()
        if not line: continue
        try:
            data = json.loads(line)
            tasks.append(process_single_item(data, semaphore))
        except json.JSONDecodeError:
            continue
    
    results = []
    for coro in tqdm(asyncio.as_completed(tasks), total=len(tasks), desc="[Process] LLM Pre-filtering", unit="samples"):
        res = await coro
        results.append(res)
    return results

# =====================================================================
# 流水线数据流读写封装
# =====================================================================
def process_dataset_pre_filter(input_jsonl_path: str, output_jsonl_path: str):
    """
    数据初筛核心主控函数：执行文件 I/O 读取、状态统计分析与结果安全落盘。
    """
    if not os.path.exists(input_jsonl_path):
        print(f"[Error] 数据源路径不存在: {input_jsonl_path}", file=sys.stderr)
        return

    output_path = Path(output_jsonl_path)
    output_path.parent.mkdir(parents=True, exist_ok=True)

    print(f"\n[Info] 挂载数据特征源: {os.path.basename(input_jsonl_path)}")
    with open(input_jsonl_path, 'r', encoding='utf-8') as f:
        lines = f.readlines()

    if not lines:
        print("[Warning] 输入文件内容为空，跳过处理任务。")
        return

    print(f"[Task] 数据流加载完成，共计 {len(lines)} 条记录。正在激活异步分析引擎...")
    
    if os.name == 'nt':
        asyncio.set_event_loop_policy(asyncio.WindowsSelectorEventLoopPolicy())
    processed_data = asyncio.run(run_batch_processing(lines))

    # 初始化处理状态统计枚举
    stats = {
        'total_processed': len(processed_data),
        'filtered_by_llm': 0,
        'filtered_but_unmodified': 0,
        'format_invalid_or_refusal': 0,
        'api_error': 0,
        'empty_input': 0
    }

    print(f"[Info] 正在执行结果序列化落盘至: {output_jsonl_path}")
    success_count = 0
    with open(output_jsonl_path, 'w', encoding='utf-8') as f_out:
        for item in processed_data:
            # 提取状态标识并从数据集记录中移除，以保证输出集的纯净
            status = item.pop('filter_status', 'unknown')
            if status in stats:
                stats[status] += 1
                
            f_out.write(json.dumps(item, ensure_ascii=False) + '\n')
            success_count += 1
            
    # 输出结构化的任务执行报告
    print(f"\n[Task Report] {os.path.basename(output_jsonl_path)} 特征初筛作业执行摘要:")
    print(f"  - 参与分析总样本数: {stats['total_processed']} 项")
    print(f"  - [Success] 成功提取语义切片: {stats['filtered_by_llm']} 项")
    print(f"  - [Success] 成功提取 (保留原函数代码): {stats['filtered_but_unmodified']} 项")
    print(f"  - [Rejected] 模型未输出有效特征代码 (已清空切片): {stats['format_invalid_or_refusal']} 项")
    if stats['api_error'] > 0:
        print(f"  - [Warning] API 网络请求异常 (已清空切片): {stats['api_error']} 项")
    if stats['empty_input'] > 0:
        print(f"  - [Skip] 原始输入代码为空，系统自动跳过: {stats['empty_input']} 项")
    print(f"  - 最终成功落盘样本总数: {success_count} 项\n")

# =====================================================================
# 自动化执行调度总线
# =====================================================================
if __name__ == "__main__":
    
    # =================================================================
    # 1. 全量生产环境作业池
    # =================================================================
    # [A] 全量 - 初始数据集初筛流水线
    """
    DATASET_TYPE = "deepseek"
    print(f"\n{'='*60}\n[Task] 启动全量生产环境初始数据集初筛作业\n{'='*60}")
    process_dataset_pre_filter(
        input_jsonl_path=f"../dataset/primevul_train_cleaned.jsonl", 
        output_jsonl_path=f"../slice/{DATASET_TYPE}/llm_pre_filtered_train.jsonl"
    )
    process_dataset_pre_filter(
        input_jsonl_path=f"../dataset/primevul_valid_cleaned.jsonl", 
        output_jsonl_path=f"../slice/{DATASET_TYPE}/llm_pre_filtered_valid.jsonl"
    )
    process_dataset_pre_filter(
        input_jsonl_path=f"../dataset/primevul_test_cleaned.jsonl",  
        output_jsonl_path=f"../slice/{DATASET_TYPE}/llm_pre_filtered_test.jsonl"
    )
    print("\n[Info] 全量初始数据集大模型初筛作业执行完毕。")
    """
    
    # [B] 全量 - 迭代训练中漏洞漏报阶段初筛
    """
    ITERATION = "iteration1"
    print(f"\n{'='*60}\n[Task] 启动全量生产环境迭代漏报样本初筛作业 ({ITERATION})\n{'='*60}")
    process_dataset_pre_filter(
        input_jsonl_path=f"../slice/{DATASET_TYPE}/{ITERATION}/val_cot_validated.jsonl", 
        output_jsonl_path=f"../slice/{DATASET_TYPE}/{ITERATION}/val_cot_validated_llm_pre_filtered.jsonl"
    )
    process_dataset_pre_filter(
        input_jsonl_path=f"../slice/{DATASET_TYPE}/{ITERATION}/val_cwe_validated.jsonl", 
        output_jsonl_path=f"../slice/{DATASET_TYPE}/{ITERATION}/val_cwe_validated_llm_pre_filtered.jsonl"
    )
    print("\n[Info] 全量迭代漏报样本大模型初筛作业执行完毕。")
    """

    # =================================================================
    # 2. 冒烟测试环境 (Smoke Test) 作业池
    # =================================================================
    DATASET_TYPE = "smoke"
    
    print(f"\n{'='*60}")
    print(f"启动 LLM 代码特征初筛模块 (Dataset: {DATASET_TYPE})")
    print(f"{'='*60}")
    """
    # [A] Smoke - 初始数据集初筛流水线
    print(f"\n[Task] 开始处理初始数据集...")
    process_dataset_pre_filter(
        input_jsonl_path=f"../{DATASET_TYPE}/primevul_train_cleaned.jsonl", 
        output_jsonl_path=f"../slice/{DATASET_TYPE}/llm_pre_filtered_train.jsonl"
    )
    process_dataset_pre_filter(
        input_jsonl_path=f"../{DATASET_TYPE}/primevul_valid_cleaned.jsonl", 
        output_jsonl_path=f"../slice/{DATASET_TYPE}/llm_pre_filtered_valid.jsonl"
    )
    process_dataset_pre_filter(
        input_jsonl_path=f"../{DATASET_TYPE}/primevul_test_cleaned.jsonl",  
        output_jsonl_path=f"../slice/{DATASET_TYPE}/llm_pre_filtered_test.jsonl"
    )
    print("\n[Info] 初始数据集初筛作业执行完毕。")
    """
    # [B] Smoke - 迭代训练中漏洞漏报阶段初筛
    
    ITERATION = "iteration1"
    print(f"\n[Task] 开始处理迭代漏报增强样本 ({ITERATION})...")
    process_dataset_pre_filter(
        input_jsonl_path=f"../slice/{DATASET_TYPE}/{ITERATION}/val_cot_validated.jsonl", 
        output_jsonl_path=f"../slice/{DATASET_TYPE}/{ITERATION}/val_cot_validated_llm_pre_filtered.jsonl"
    )
    process_dataset_pre_filter(
        input_jsonl_path=f"../slice/{DATASET_TYPE}/{ITERATION}/val_cwe_validated.jsonl", 
        output_jsonl_path=f"../slice/{DATASET_TYPE}/{ITERATION}/val_cwe_validated_llm_pre_filtered.jsonl"
    )
    print("\n[Info] 迭代漏报样本初筛作业执行完毕。")