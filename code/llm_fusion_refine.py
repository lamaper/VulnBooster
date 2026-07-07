"""
基于大语言模型 (LLM) 的双路特征深度对齐与融合精炼模块 (Fusion Refine)

主要功能：
1. 数据映射：基于样本主键 (idx) 将静态分析切片 (Static Slice) 与大模型初筛特征 (Initial Screening) 进行对齐。
2. 深度融合：驱动 LLM 依据严谨的提取规则 (Refinement Rules)，对两路特征进行去噪、缝合与语义补全。
3. 函数头修补 (Header Stitching)：自动检测并补全缺失的函数签名，防止特征降维与 AST 解析失败。
4. 动态降级：若任一切片链路失败，则直接沿用另一条有效链路的切片结果，避免无效的 API 调用。
5. 容错控制：内置信号量并发管理、指数退避重试机制以及异常输出的代码提纯与降级机制。
"""
import json
import os
import re
import asyncio
from pathlib import Path
from openai import AsyncOpenAI
from tqdm.asyncio import tqdm

# =====================================================================
# 异步接口与并发控制配置
# =====================================================================
API_KEY = "sk-xxxxxxxxxxxxxxxxxxx"
BASE_URL = "https://api.deepseek.com"  
MODEL_NAME = "deepseek-coder"  

# 并发安全阈值与重试策略设定
CONCURRENCY_LIMIT = 500
MAX_RETRIES = 2
BASE_RETRY_DELAY = 3.0

aclient = AsyncOpenAI(api_key=API_KEY, base_url=BASE_URL)

# 动态定义反引号，防止破坏 Markdown 渲染器或导致语法高亮错乱
TICK3 = "```"

# =====================================================================
# 提示词模板 (Prompt Template)
# =====================================================================
FUSION_SYSTEM_PROMPT = (
    "You are an expert C/C++ security analyst. Your task is to fuse and refine two code snippets into a "
    "semantically complete, concise vulnerability-relevant region. Strictly follow the refinement rules "
    "and output ONLY the final code block."
)

# 使用双大括号 {{}} 来保留 format 的占位符
FUSION_USER_PROMPT_TEMPLATE = f"""Refine the following two code snippets into one high-quality vulnerability-relevant region:

[Static Slice]
{TICK3}cpp
{{static_slice}}
{TICK3}

[Initial Screening]
{TICK3}cpp
{{initial_screening}}
{TICK3}

[Refinement Rules]
1. Consistency & Completion: Align both snippets. Ensure all variable definitions, data sources, and control conditions are complete.
2. Noise Filtering: Remove redundant declarations, unrelated code, comments, and debug logs.
3. Boundary Validation: Preserve complete basic blocks (include opening/closing braces). Do not truncate mid-logic.
4. Length Control: Target 5–20 lines with high semantic density. Focus on 'Context + Vulnerable Action' pattern.

[Output Constraints]
- Return ONLY the refined code in a single {TICK3}cpp block.
- Preserve original indentation and variable names.
- Ensure syntactic completeness."""

# =====================================================================
# 代码提纯与语义缝合机制
# =====================================================================
def extract_pure_code_slice(response_text: str, fallback_code: str) -> tuple[str, bool]:
    """
    合规性校验与正则提纯：剥离 LLM 输出的 Markdown 包装层及内在推理过程。
    返回: (提取出的纯净代码字符串, 提取状态布尔值)
    """
    if not response_text:
        return fallback_code, False
        
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
            return fallback_code, False
            
    # 长度阈值拦截：防范无意义的极短切片或格式不合规的响应
    if len(extracted) < 10:
        return fallback_code, False
        
    return extracted, is_success

def stitch_function_header(refined_code: str, original_code: str) -> str:
    """
    函数头自动修补机制 (Header Stitching)：
    检测提取出的切片是否缺失函数签名。若缺失，则从原始长代码中截取函数头进行缝合，
    并在代码末尾补齐闭合大括号，以保证 AST 树的完整性与数据流追踪的连续性。
    """
    if not refined_code or not original_code:
        return refined_code
        
    first_line = refined_code.strip().split('\n')[0].strip()
    
    # 状态推断：若第一行以控制流关键字开头，或缺乏典型的函数声明特征 (无括号)，则判定为缺失函数头
    is_missing_header = False
    if re.match(r'^(if|while|for|return|switch|else|do|try|catch)\b', first_line, re.IGNORECASE):
        is_missing_header = True
    elif not re.search(r'\w+\s*\(.*?\)', first_line):
        is_missing_header = True
        
    if is_missing_header:
        # 提取原始代码的函数头（匹配直到遇到第一个 '{'）
        header_match = re.search(r'^(.*?\{)', original_code, re.DOTALL)
        if header_match:
            header = header_match.group(1).strip()
            # 修补函数头，并在末尾追加闭合大括号以保证语法域闭环
            return f"{header}\n{refined_code}\n}}"
            
    return refined_code

# =====================================================================
# 异步请求与数据融合引擎
# =====================================================================
async def request_fusion_async(static_code: str, llm_code: str, semaphore: asyncio.Semaphore) -> str:
    """
    发起融合精炼请求，集成指数退避重试机制以应对网络波动和流控限制。
    """
    user_content = FUSION_USER_PROMPT_TEMPLATE.format(
        static_slice=static_code, 
        initial_screening=llm_code
    )

    for attempt in range(MAX_RETRIES):
        try:
            async with semaphore:
                response = await aclient.chat.completions.create(
                    model=MODEL_NAME,
                    messages=[
                        {"role": "system", "content": FUSION_SYSTEM_PROMPT},
                        {"role": "user", "content": user_content}
                    ],
                    temperature=0.1,
                    max_tokens=2048,
                    timeout=60.0
                )
                content = response.choices[0].message.content
                
                if not content or not content.strip():
                    raise ValueError("大语言模型返回内容为空。")
                    
                return content
                
        except Exception as e:
            error_msg = str(e).lower()
            # 错误拦截：API Key 无效、欠费等异常
            if "401" in error_msg or "authentication" in error_msg or "insufficient_quota" in error_msg:
                raise RuntimeError(f"[Error] API 拒绝访问，请检查密钥或资源额度。详细日志: {e}")
            
            # 若达到最大重试次数仍失败，则打印异常日志供分析
            if attempt == MAX_RETRIES - 1:
                tqdm.write(f"\n[Warning] 样本融合请求失败 (已达最大重试次数)。异常详情: {str(e)}")
                return ""
            
            await asyncio.sleep(BASE_RETRY_DELAY * (2 ** attempt))
            
    return ""

async def process_single_fusion(item: dict, semaphore: asyncio.Semaphore) -> dict:
    """
    单条数据的融合处理协程。
    包含：特征映射、旁路降级、大模型融合调用、代码提纯与函数头修补。
    """
    cleaned_item = {
        "idx": item.get("idx"),
        "func": item.get("func", ""),
        "target": item.get("target"),
        "cwe": item.get("cwe", []),
        "cve": item.get("cve", [])
    }

    original_code = cleaned_item['func']
    static_slice = item.get('static_slice', '').strip()
    llm_slice = item.get('llm_slice', '').strip()
    
    # ================= 旁路降级逻辑 (Fallback) =================
    # 若任一链路缺失，则避免触发 LLM 融合，直接沿用有效特征
    if not static_slice and llm_slice:
        stitched_llm = stitch_function_header(llm_slice, original_code)
        cleaned_item['refined_code'] = stitched_llm
        cleaned_item['fusion_status'] = 'fallback_llm'
        return cleaned_item
    
    if static_slice and not llm_slice:
        stitched_static = stitch_function_header(static_slice, original_code)
        cleaned_item['refined_code'] = stitched_static
        cleaned_item['fusion_status'] = 'fallback_static'
        return cleaned_item
        
    if not static_slice and not llm_slice:
        cleaned_item['refined_code'] = original_code
        cleaned_item['fusion_status'] = 'fallback_original'
        return cleaned_item

    # ================= 深度融合逻辑 =================
    refined_result = await request_fusion_async(static_slice, llm_slice, semaphore)
    fallback = llm_slice or static_slice
    
    if refined_result:
        extracted_code, is_success = extract_pure_code_slice(refined_result, fallback_code=fallback)
        if is_success:
            # 提取成功，执行函数头自动修补以保证 AST 完整性
            stitched_code = stitch_function_header(extracted_code, original_code)
            cleaned_item['refined_code'] = stitched_code
            cleaned_item['fusion_status'] = 'fused_by_llm'
        else:
            # 格式解析失败导致的提纯降级
            cleaned_item['refined_code'] = stitch_function_header(fallback, original_code)
            cleaned_item['fusion_status'] = 'fallback_refusal_or_invalid'
    else:
        # API 彻底超时的容错降级
        cleaned_item['refined_code'] = stitch_function_header(fallback, original_code)
        cleaned_item['fusion_status'] = 'fusion_api_error'
        
    return cleaned_item

async def run_batch_fusion(merged_data_list: list) -> list:
    """
    批量调度器：管理并发任务池并收集融合结果。
    """
    semaphore = asyncio.Semaphore(CONCURRENCY_LIMIT)
    tasks = [process_single_fusion(data, semaphore) for data in merged_data_list]
    
    results = []
    for coro in tqdm(asyncio.as_completed(tasks), total=len(tasks), desc="[Process] LLM Fusion Refine", unit="samples"):
        res = await coro
        results.append(res)
        
    return results

# =====================================================================
# 数据流对齐与调度封装
# =====================================================================
def load_jsonl_to_dict(file_path: str) -> dict:
    """加载 JSONL 数据字典，兼容 Joern 的 fromIdx 与普通特征的 idx"""
    data_dict = {}
    if not os.path.exists(file_path):
        return data_dict
        
    with open(file_path, 'r', encoding='utf-8') as f:
        for line in f:
            line = line.strip()
            if not line: continue
            try:
                obj = json.loads(line)
                idx = obj.get('idx')
                if idx is None:
                    idx = obj.get('fromIdx')
                    
                if idx is not None:
                    data_dict[idx] = obj
            except json.JSONDecodeError:
                continue
    return data_dict

def process_fusion_pipeline(static_jsonl: str, llm_jsonl: str, output_jsonl: str):
    """
    双路融合流水线主控函数：执行数据对齐、异步处理、状态统计与结果落盘。
    """
    print(f"\n[Info] 挂载静态分析特征源 (Joern): {os.path.basename(static_jsonl)}")
    print(f"[Info] 挂载大语言模型初筛特征源 (LLM): {os.path.basename(llm_jsonl)}")
    
    static_data = load_jsonl_to_dict(static_jsonl)
    llm_data = load_jsonl_to_dict(llm_jsonl)
    
    if not static_data and not llm_data:
        print("[Warning] 输入流缺失，当前特征融合任务已终止。\n")
        return

    all_indices = set(static_data.keys()).union(set(llm_data.keys()))
    merged_list = []
    
    for idx in all_indices:
        llm_item = llm_data.get(idx, {})
        static_item = static_data.get(idx, {})
        
        merged_item = dict(llm_item) if llm_item else dict(static_item)
        merged_item['idx'] = idx  
        
        # 将列表格式的特征合并为长字符串
        llm_slice_val = llm_item.get('llm_slice', '')
        if isinstance(llm_slice_val, list):
            llm_slice_val = "\n".join(llm_slice_val)
            
        static_slice_val = static_item.get('code_lines', '')
        if isinstance(static_slice_val, list):
            static_slice_val = "\n".join(static_slice_val)
            
        merged_item['static_slice'] = static_slice_val
        merged_item['llm_slice'] = llm_slice_val
        
        merged_list.append(merged_item)

    print(f"[Task] 映射对齐完成，共计 {len(merged_list)} 条样本记录。启动异步融合引擎...")
    
    if os.name == 'nt':
        asyncio.set_event_loop_policy(asyncio.WindowsSelectorEventLoopPolicy())
    processed_data = asyncio.run(run_batch_fusion(merged_list))

    output_path = Path(output_jsonl)
    output_path.parent.mkdir(parents=True, exist_ok=True)
    
    # 细化统计状态
    stats = {
        'total_aligned': len(merged_list),
        'fused_by_llm': 0,
        'fallback_llm': 0,
        'fallback_static': 0,
        'fallback_original': 0,
        'fusion_api_error': 0,
        'fallback_refusal_or_invalid': 0
    }
    
    success_count = 0
    with open(output_jsonl, 'w', encoding='utf-8') as f_out:
        for item in processed_data:
            status = item.pop('fusion_status', 'unknown')
            if status in stats:
                stats[status] += 1
                
            f_out.write(json.dumps(item, ensure_ascii=False) + '\n')
            success_count += 1
            
    print(f"\n[Task Report] {os.path.basename(output_jsonl)} 融合精炼作业统计摘要:")
    print(f"  - 成功映射对齐总样本: {stats['total_aligned']} 项")
    print(f"  - [双路齐备] 成功执行 LLM 深度融合: {stats['fused_by_llm']} 项")
    print(f"  - [单路回退] 仅沿用 LLM 初筛切片: {stats['fallback_llm']} 项")
    print(f"  - [单路回退] 仅沿用 Joern 静态切片: {stats['fallback_static']} 项")
    print(f"  - [双路缺失] 彻底回退至原始全量代码: {stats['fallback_original']} 项")
    if stats['fallback_refusal_or_invalid'] > 0:
        print(f"  - [Warning] 因输出格式不合规导致回退: {stats['fallback_refusal_or_invalid']} 项")
    if stats['fusion_api_error'] > 0:
        print(f"  - [Warning] 因 API 网络异常导致回退: {stats['fusion_api_error']} 项")
    print(f"  - 最终成功落盘样本数: {success_count} 项\n")


# =====================================================================
# 自动化执行总线
# =====================================================================
if __name__ == "__main__":
    
    # =================================================================
    # 1. 全量生产环境作业池
    # =================================================================
    # [A] 全量 - 初始数据集融合精炼 
    """
    print(f"\n{'='*60}\n[任务调度] 启动全量生产环境 - 初始数据集双路融合精炼作业\n{'='*60}")
    process_fusion_pipeline(
        static_jsonl="../slice/deepseek/joern_sliced_train.jsonl",
        llm_jsonl="../slice/deepseek/llm_pre_filtered_train.jsonl",
        output_jsonl="../slice/deepseek/refined_train.jsonl"
    )
    process_fusion_pipeline(
        static_jsonl="../slice/deepseek/joern_sliced_valid.jsonl",
        llm_jsonl="../slice/deepseek/llm_pre_filtered_valid.jsonl",
        output_jsonl="../slice/deepseek/refined_valid.jsonl"
    )
    process_fusion_pipeline(
        static_jsonl="../slice/deepseek/joern_sliced_test.jsonl",
        llm_jsonl="../slice/deepseek/llm_pre_filtered_test.jsonl",
        output_jsonl="../slice/deepseek/refined_test.jsonl"
    )
    print("\n[系统通知] 全量初始数据集融合精炼作业执行完毕。")
    """
    
    # [B] 全量 - 迭代漏报样本融合精炼 
    """
    ITERATION = "iteration1"
    print(f"\n{'='*60}\n[任务调度] 启动全量生产环境 - 迭代漏报样本融合精炼作业 ({ITERATION})\n{'='*60}")
    process_fusion_pipeline(
        static_jsonl=f"../slice/deepseek/{ITERATION}/val_cot_validated_joern_sliced.jsonl",
        llm_jsonl=f"../slice/deepseek/{ITERATION}/val_cot_validated_llm_pre_filtered.jsonl",
        output_jsonl=f"../slice/deepseek/{ITERATION}/val_cot_validated_refined.jsonl"
    )
    process_fusion_pipeline(
        static_jsonl=f"../slice/deepseek/{ITERATION}/val_cwe_validated_joern_sliced.jsonl",
        llm_jsonl=f"../slice/deepseek/{ITERATION}/val_cwe_validated_llm_pre_filtered.jsonl",
        output_jsonl=f"../slice/deepseek/{ITERATION}/val_cwe_validated_refined.jsonl"
    )
    print("\n[系统通知] 全量迭代漏报样本融合精炼作业执行完毕。")
    """

    # =================================================================
    # 2. 冒烟测试环境 (Smoke Test) 作业池
    # =================================================================
    DATASET_TYPE = "smoke"
    
    print(f"\n{'='*60}")
    print(f"启动双路特征对齐与融合精炼模块 (Dataset: {DATASET_TYPE})")
    print(f"{'='*60}")
    """
    # [A] Smoke - 初始数据集融合精炼
    print(f"\n[Task] 开始执行初始数据集双路融合精炼作业...")
    
    process_fusion_pipeline(
        static_jsonl=f"../slice/{DATASET_TYPE}/joern_sliced_train.jsonl",
        llm_jsonl=f"../slice/{DATASET_TYPE}/llm_pre_filtered_train.jsonl",
        output_jsonl=f"../slice/{DATASET_TYPE}/refined_train.jsonl"
    )
    process_fusion_pipeline(
        static_jsonl=f"../slice/{DATASET_TYPE}/joern_sliced_valid.jsonl",
        llm_jsonl=f"../slice/{DATASET_TYPE}/llm_pre_filtered_valid.jsonl",
        output_jsonl=f"../slice/{DATASET_TYPE}/refined_valid.jsonl"
    )
    process_fusion_pipeline(
        static_jsonl=f"../slice/{DATASET_TYPE}/joern_sliced_test.jsonl",
        llm_jsonl=f"../slice/{DATASET_TYPE}/llm_pre_filtered_test.jsonl",
        output_jsonl=f"../slice/{DATASET_TYPE}/refined_test.jsonl"
    )
    print("\n[Info] Smoke 测试环境初始数据集融合精炼作业执行完毕。")
    """
    # [B] Smoke - 迭代漏报样本融合精炼
    
    ITERATION = "iteration1"
    print(f"\n[Task] 开始执行迭代漏报样本融合精炼作业 ({ITERATION})...")
    
    process_fusion_pipeline(
        static_jsonl=f"../slice/{DATASET_TYPE}/{ITERATION}/val_cot_validated_joern_sliced.jsonl",
        llm_jsonl=f"../slice/{DATASET_TYPE}/{ITERATION}/val_cot_validated_llm_pre_filtered.jsonl",
        output_jsonl=f"../slice/{DATASET_TYPE}/{ITERATION}/val_cot_validated_refined.jsonl"
    )
    process_fusion_pipeline(
        static_jsonl=f"../slice/{DATASET_TYPE}/{ITERATION}/val_cwe_validated_joern_sliced.jsonl",
        llm_jsonl=f"../slice/{DATASET_TYPE}/{ITERATION}/val_cwe_validated_llm_pre_filtered.jsonl",
        output_jsonl=f"../slice/{DATASET_TYPE}/{ITERATION}/val_cwe_validated_refined.jsonl"
    )
    print("\n[Info] 迭代漏报样本融合精炼作业执行完毕。")
    
    
    print(f"\n{'='*60}")
    print(f"[Info] 所有双路特征融合精炼任务执行完毕。请核对输出文件。")
    print(f"{'='*60}")