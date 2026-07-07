"""
基于 CWE 知识库的漏洞数据定向增强模块 (CWE Enhance)

核心机制：
针对验证集上的漏报样本 (False Negatives)，引入 MITRE 官方 CWE 知识库信息，
通过大语言模型 (LLM) 并发引擎进行代码变体的繁衍与演化，生成具有强漏洞语义的补充训练数据。

容错与安全机制：
1. 深拷贝隔离：采用 deepcopy 完美继承原始样本的全局上下文，防止内存引用污染。
2. 头部过滤：正则剥离大模型在代码首行附加的无关自然语言解释，防止引入捷径特征。
3. 网络退避：基于 Semaphore 与指数退避重试算法，应对高并发下的 API 访问控制。
"""
import os
import json
import re
import asyncio
import copy
import sys
from pathlib import Path
from openai import AsyncOpenAI
from tqdm.asyncio import tqdm

import config_cwe
import cwe_spider

# 显式规避本地网络代理干扰，保障高并发状态下的通讯稳定性
os.environ['NO_PROXY'] = 'localhost,127.0.0.1'

# =====================================================================
# 大语言模型 (LLM) 异步接口与并发控制配置
# =====================================================================
API_KEY = "sk-xxxxxxxxxxxxxxxxxxx" 
BASE_URL = "https://api.deepseek.com" 
MODEL_NAME = "deepseek-coder" 

CONCURRENCY_LIMIT = 500 
MAX_RETRIES = 5
BASE_RETRY_DELAY = 3.0

aclient = AsyncOpenAI(api_key=API_KEY, base_url=BASE_URL)

# =====================================================================
# 运行模式与路径配置
# =====================================================================
RUN_MODE = "smoke" 
CURRENT_ITERATION = 1 

# ============================================================
# 消融实验配置 3：移除漏洞特征提取方案
# 针对无特征提取模型产生的漏报样本进行定向增强
# ============================================================
if RUN_MODE == "smoke":
    INPUT_FILE = f"../slice/smoke/ablation_3_no_feature_extract/iteration{CURRENT_ITERATION}/valvul_nofind.jsonl"
    OUTPUT_FILE = f"../slice/smoke/ablation_3_no_feature_extract/iteration{CURRENT_ITERATION}/val_cwe.jsonl"
else:
    INPUT_FILE = f"../slice/deepseek/ablation_3_no_feature_extract/iteration{CURRENT_ITERATION}/valvul_nofind.jsonl"
    OUTPUT_FILE = f"../slice/deepseek/ablation_3_no_feature_extract/iteration{CURRENT_ITERATION}/val_cwe.jsonl"

# ============================================================
# 标准流水线配置（完整系统方案）
# ============================================================
# if RUN_MODE == "smoke":
#     INPUT_FILE = f"../slice/smoke/iteration{CURRENT_ITERATION}/valvul_nofind.jsonl"
#     OUTPUT_FILE = f"../slice/smoke/iteration{CURRENT_ITERATION}/val_cwe.jsonl"
# else:
#     INPUT_FILE = f"../slice/deepseek/iteration{CURRENT_ITERATION}/valvul_nofind.jsonl"
#     OUTPUT_FILE = f"../slice/deepseek/iteration{CURRENT_ITERATION}/val_cwe.jsonl"

# =====================================================================
# 核心大模型请求与提取引擎
# =====================================================================
async def run_vuln_generation_async(user_prompt: str, semaphore: asyncio.Semaphore) -> str:
    """
    发起大模型异步定向生成请求，内置指数退避重试策略。
    """
    async with semaphore:
        messages = [
            {"role": "system", "content": config_cwe.SYSTEM_PROMPT},
            {"role": "user", "content": user_prompt}
        ]
        
        for attempt in range(MAX_RETRIES):
            try:
                response = await aclient.chat.completions.create(
                    model=MODEL_NAME,
                    messages=messages,
                    temperature=0.7, 
                    timeout=120.0
                )
                content = response.choices[0].message.content
                if not content or not content.strip():
                    raise ValueError("LLM 返回内容为空")
                return content
                
            except Exception as e:
                error_msg = str(e).lower()
                if "401" in error_msg or "insufficient_quota" in error_msg:
                    raise RuntimeError(f"[Error] API 鉴权失败或资源耗尽: {e}")
                    
                if attempt == MAX_RETRIES - 1:
                    tqdm.write(f"\n[Warning] API 请求彻底失败 (已达最大重试次数): {str(e)}")
                    return ""
                    
                await asyncio.sleep(BASE_RETRY_DELAY * (2 ** attempt))
        return ""

def extract_generated_functions(response_text: str) -> list:
    """
    精准剥离 LLM 输出的代码块，并清洗可能被大模型塞入头部的枚举注释。
    """
    if not response_text:
        return []
        
    text_no_think = re.sub(r'<think>.*?</think>', '', response_text, flags=re.DOTALL | re.IGNORECASE).strip()
    pattern = re.compile(config_cwe.TICK3 + r"(?:cpp|c|c\+\+)?\s*\n(.*?)\n\s*" + config_cwe.TICK3, re.DOTALL | re.IGNORECASE)
    matches = pattern.findall(text_no_think)
    
    cleaned_funcs = []
    for match in matches:
        code_lines = match.strip().split('\n')
        
        # 清除首行大模型加入的自然语言注释
        while code_lines:
            first_line = code_lines[0].strip()
            if re.match(r'^//\s*(Function|Example|Scenario|Case|\d+\.?)\b', first_line, re.IGNORECASE):
                code_lines.pop(0)
            else:
                break 
                
        cleaned_code = '\n'.join(code_lines).strip()
        if cleaned_code:
            cleaned_funcs.append(cleaned_code)
            
    return cleaned_funcs

async def process_single_cwe_task(data: dict, user_prompt: str, semaphore: asyncio.Semaphore) -> list:
    """
    单条样本处理协程：执行大模型生成、数据提取及主键溯源分配。
    """
    result_text = await run_vuln_generation_async(user_prompt, semaphore)
    if not result_text:
        return []
        
    functions = extract_generated_functions(result_text)
    if not functions:
        return []
        
    idx = data.get("idx")
    enhanced_list = []
    
    # 遍历大模型生成的所有代码变体
    for i, func in enumerate(functions):
        cwe_data = copy.deepcopy(data)
        
        # 覆写核心代码特征
        cwe_data["func"] = func
        
        # 注入生命周期溯源标记并配置唯一主键
        cwe_data["is_cwe_enhanced"] = True
        cwe_data["original_idx"] = idx
        cwe_data["idx"] = f"{idx}_cwe_{i}"
        
        enhanced_list.append(cwe_data)
        
    return enhanced_list

# =====================================================================
# 流水线生命周期调度入口
# =====================================================================
def main():
    print(f"\n{'='*60}")
    print(f"[Task] 启动 CWE 官方知识定向增强流水线 (消融配置 3)")
    print(f"       运行环境: {RUN_MODE.upper()} | 迭代层级: Iteration {CURRENT_ITERATION}")
    print(f"{'='*60}")
    
    if not os.path.exists(INPUT_FILE):
        print(f"[Error] 数据源未挂载或不存在: {INPUT_FILE}", file=sys.stderr)
        return

    Path(OUTPUT_FILE).parent.mkdir(parents=True, exist_ok=True)
    
    # 1. 读取基础漏报样本池
    print(f"\n[Info] 正在加载待演化漏报样本: {os.path.basename(INPUT_FILE)}")
    preload_items = []
    with open(INPUT_FILE, 'r', encoding='utf-8') as fin:
        for line in fin:
            line = line.strip()
            if not line: 
                continue
            try:
                data = json.loads(line)
                # 由于输入源已是漏报验证集，此处作为防错性校验保留
                if data.get("target") == 1:
                    preload_items.append(data)
            except json.JSONDecodeError:
                pass

    if not preload_items:
        print("[Warning] 未检索到任何可供增强的正样本 (target=1)，任务安全中止。")
        return

    print(f"[Task] 数据挂载完成。进入知识融合阶段，共 {len(preload_items)} 条待处理样本。")
    
    tasks_inputs = []
    custom_count = 0
    general_count = 0
    
    # 2. 爬虫同步检索与双轨提示词装配
    for data in preload_items:
        # 特征提取优先级
        code = data.get('refined_code', data.get('llm_slice', data.get('func', '')))
        
        cwe_raw = data.get("cwe", ["Unknown"])
        cwe = cwe_raw[0] if isinstance(cwe_raw, list) and len(cwe_raw) > 0 else str(cwe_raw)
        
        # 爬取并匹配 CWE 官方漏洞描述与表征代码
        kb_info = cwe_spider.get_cwe_knowledge(cwe)
        
        if kb_info:
            user_prompt = config_cwe.CUSTOMIZED_TEMPLATE.format(
                seedfunc=code,
                vulDef=kb_info["def"],
                vulManifest=kb_info["manifest"],
                k=3
            )
            custom_count += 1
        else:
            user_prompt = config_cwe.GENERAL_TEMPLATE.format(
                seedfunc=code,
                cweType=cwe,
                k=3
            )
            general_count += 1
            
        tasks_inputs.append((data, user_prompt))

    print(f"[Info] 提示词知识矩阵就绪。定制模板: {custom_count} 项 | 通用模板: {general_count} 项")
    
    # 3. 启动异步并发生成引擎
    if os.name == 'nt':
        asyncio.set_event_loop_policy(asyncio.WindowsSelectorEventLoopPolicy())
        
    semaphore = asyncio.Semaphore(CONCURRENCY_LIMIT)
    
    async def _run_all():
        tasks = [process_single_cwe_task(data, prompt, semaphore) for data, prompt in tasks_inputs]
        results = []
        for coro in tqdm(asyncio.as_completed(tasks), total=len(tasks), desc="[Process] CWE 知识定向演化", unit="样本"):
            res = await coro
            results.append(res)
        return results

    batch_results = asyncio.run(_run_all())
    
    # 4. 特征数据序列化与状态报告
    success_count = 0
    total_generated = 0
    
    with open(OUTPUT_FILE, 'w', encoding='utf-8') as fout:
        for enhanced_samples in batch_results:
            if enhanced_samples:
                success_count += 1
                for sample in enhanced_samples:
                    fout.write(json.dumps(sample, ensure_ascii=False) + '\n')
                    total_generated += 1
                    
    print(f"\n[Task Report] {os.path.basename(OUTPUT_FILE)} CWE 增强作业执行摘要:")
    print(f"  - 推理目标漏报样本数: {len(preload_items)} 项")
    print(f"  - 成功衍生变体原样本: {success_count} 项")
    print(f"  - 最终累计合成代码变体: {total_generated} 项")
    print(f"  - 归档路径: {OUTPUT_FILE}\n")

if __name__ == "__main__":
    main()