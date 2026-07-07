"""
基于思维链 (Chain of Thought, CoT) 的漏洞数据增强模块

核心机制：
1. 并发调度：基于信号量与指数退避重试机制，控制异步高并发请求。
2. 逻辑推理：基于 config_cot.py 中的 4 步 Prompt 驱动 LLM 进行因果推理与变体生成。
3. 精准提取：兼容多种 Markdown 变体的正则匹配，准确剥离生成的独立代码块。
4. 属性继承与主键重写：采用深拷贝完整保留原样本上下文，并为变体赋予包含溯源信息的唯一主键 (idx)，防范下游合并阶段的数据覆盖。
"""

import json
import os
import re
import asyncio
import sys
import copy
from pathlib import Path
from openai import AsyncOpenAI
from tqdm.asyncio import tqdm

# 获取上级目录以导入配置文件
parent_dir = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.append(parent_dir)

import config_cot

# =====================================================================
# 大语言模型 (LLM) 异步调度配置
# =====================================================================
API_KEY = "sk-xxxxxxxxxxxxxxxx"  
BASE_URL = "https://api.deepseek.com"
MODEL_NAME = "deepseek-coder"

# 系统级并发限制与重试策略
CONCURRENCY_LIMIT = 500
MAX_RETRIES = 3
BASE_RETRY_DELAY = 2.0

aclient = AsyncOpenAI(api_key=API_KEY, base_url=BASE_URL)

# =====================================================================
# 全局运行态与路径配置
# =====================================================================
RUN_MODE = "smoke" 
CURRENT_ITERATION = 1 

# ============================================================
# 消融实验配置 3：移除漏洞特征提取方案
# 针对无特征提取模型产生的漏报样本进行定向增强
# ============================================================
if RUN_MODE == "smoke":
    INPUT_FILE = f"../slice/smoke/ablation_3_no_feature_extract/iteration{CURRENT_ITERATION}/valvul_nofind.jsonl"
    OUTPUT_FILE = f"../slice/smoke/ablation_3_no_feature_extract/iteration{CURRENT_ITERATION}/val_cot.jsonl"
else:
    INPUT_FILE = f"../slice/deepseek/ablation_3_no_feature_extract/iteration{CURRENT_ITERATION}/valvul_nofind.jsonl"
    OUTPUT_FILE = f"../slice/deepseek/ablation_3_no_feature_extract/iteration{CURRENT_ITERATION}/val_cot.jsonl"

# ============================================================
# 标准流水线配置（完整系统方案）
# ============================================================
# if RUN_MODE == "smoke":
#     INPUT_FILE = f"../slice/smoke/iteration{CURRENT_ITERATION}/valvul_nofind.jsonl"
#     OUTPUT_FILE = f"../slice/smoke/iteration{CURRENT_ITERATION}/val_cot.jsonl"
# else:
#     INPUT_FILE = f"../slice/deepseek/iteration{CURRENT_ITERATION}/valvul_nofind.jsonl"
#     OUTPUT_FILE = f"../slice/deepseek/iteration{CURRENT_ITERATION}/val_cot.jsonl"

# =====================================================================
# 核心处理组件
# =====================================================================
def extract_c_code(text: str) -> list:
    """
    基于非贪婪正则匹配，从模型响应中提取 C/C++ 代码块。
    宽容处理多样的 Markdown 语言标识。
    """
    pattern = re.compile(r'```[a-zA-Z]*\s*(.*?)```', re.DOTALL)
    matches = pattern.findall(text)
    return [m.strip() for m in matches if m.strip()]

async def run_cot_chain(code: str, semaphore: asyncio.Semaphore) -> list:
    """
    执行 4 步逻辑推理链，完成上下文分析至代码变体生成的全过程。
    """
    for attempt in range(MAX_RETRIES):
        messages = [{"role": "system", "content": config_cot.chain_sys}]
        
        try:
            async with semaphore:
                for i, step_prompt in enumerate(config_cot.chain_inputs):
                    # 动态注入代码特征及期望的变体生成数量 (K)
                    if i == 0:
                        content = step_prompt.replace("{code}", code)
                    elif i == 3:
                        content = step_prompt.replace("{K}", str(config_cot.GENERATE_K))
                    else:
                        content = step_prompt
                        
                    messages.append({"role": "user", "content": content})
                    
                    response = await aclient.chat.completions.create(
                        model=MODEL_NAME,
                        messages=messages,
                        temperature=0.6 if i == 3 else 0.1, 
                        max_tokens=2048,
                        timeout=60.0
                    )
                    
                    answer = response.choices[0].message.content
                    messages.append({"role": "assistant", "content": answer})
                    
                    # 终止步：执行正则提取
                    if i == 3:
                        return extract_c_code(answer)
                        
            break 
            
        except Exception as e:
            error_msg = str(e).lower()
            if "401" in error_msg or "insufficient_quota" in error_msg:
                raise RuntimeError(f"[Error] API 鉴权失败或资源耗尽: {e}")
                
            if attempt == MAX_RETRIES - 1:
                tqdm.write(f"\n[Warning] 样本推理异常中断 (已达最大重试次数): {str(e)}")
                return []
            await asyncio.sleep(BASE_RETRY_DELAY * (2 ** attempt))
            
    return []

async def process_single_cot_task(item: dict, semaphore: asyncio.Semaphore) -> list:
    """
    独立任务单元：基于输入样本驱动大模型进行逻辑变体繁衍，
    并实施深拷贝与唯一标识符 (idx) 的重分配。
    """
    original_idx = item.get('idx')
    if original_idx is None:
        return []

    # 提取特征序列优先级
    base_code = item.get('refined_code', item.get('llm_slice', item.get('func', '')))
    if not base_code:
        return []

    generated_codes = await run_cot_chain(base_code, semaphore)
    
    enhanced_samples = []
    for i, gen_code in enumerate(generated_codes):
        new_item = copy.deepcopy(item)
        new_item['func'] = gen_code
        
        # 溯源与唯一性保障机制：生成衍生标识并保证合并阶段不被覆盖
        new_item['original_idx'] = original_idx
        new_item['idx'] = f"{original_idx}_cot_{i}"
        new_item['is_cot_enhanced'] = True
        
        enhanced_samples.append(new_item)
        
    return enhanced_samples

# =====================================================================
# 流水线自动化总线
# =====================================================================
def main():
    print(f"\n{'='*60}")
    print(f"[Task] 启动思维链 (CoT) 漏洞数据增强作业 (消融配置 3)")
    print(f"       运行环境: {RUN_MODE.upper()} | 迭代层级: Iteration {CURRENT_ITERATION}")
    print(f"{'='*60}")
    
    if not os.path.exists(INPUT_FILE):
        print(f"[Error] 依赖寻址失败：无法定位漏报验证集 {INPUT_FILE}", file=sys.stderr)
        return

    Path(OUTPUT_FILE).parent.mkdir(parents=True, exist_ok=True)
    
    print(f"\n[Info] 正在装载基线特征源: {os.path.basename(INPUT_FILE)}")
    items = []
    with open(INPUT_FILE, 'r', encoding='utf-8') as f:
        for line in f:
            if not line.strip(): continue
            try:
                items.append(json.loads(line))
            except json.JSONDecodeError:
                continue

    if not items:
        print("[Warning] 输入数据流为空，任务终止。")
        return

    print(f"[Task] 数据流加载完成，有效样本 {len(items)} 条。初始化异步生成队列...")

    if os.name == 'nt':
        asyncio.set_event_loop_policy(asyncio.WindowsSelectorEventLoopPolicy())
        
    semaphore = asyncio.Semaphore(CONCURRENCY_LIMIT)
    
    async def _run_all():
        tasks = [process_single_cot_task(item, semaphore) for item in items]
        results = []
        for coro in tqdm(asyncio.as_completed(tasks), total=len(tasks), desc="[Process] CoT Reasoning", unit="samples"):
            res = await coro
            results.append(res)
        return results

    batch_results = asyncio.run(_run_all())

    # 数据序列化与作业报告生成
    success_count = 0
    total_generated = 0
    
    with open(OUTPUT_FILE, 'w', encoding='utf-8') as fout:
        for enhanced_samples in batch_results:
            if enhanced_samples:
                success_count += 1
                for sample in enhanced_samples:
                    fout.write(json.dumps(sample, ensure_ascii=False) + '\n')
                    total_generated += 1
                    
    print(f"\n[Task Report] {os.path.basename(OUTPUT_FILE)} 数据增强作业执行摘要:")
    print(f"  - 推理目标样本总数: {len(items)} 项")
    print(f"  - 成功衍生变体原样本: {success_count} 项")
    print(f"  - 最终累计合成代码变体: {total_generated} 项")
    print(f"  - 数据安全落盘位置: {OUTPUT_FILE}\n")

if __name__ == "__main__":
    main()