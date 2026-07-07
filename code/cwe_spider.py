"""
MITRE CWE 官方知识库自动化爬虫模块
用于动态提取 CWE 的“标准化描述 (Definition)”与“典型表现形式 (Manifestation)”
"""
import os
import re
import json
import requests
from bs4 import BeautifulSoup

# 本地知识库缓存文件路径
CACHE_FILE = "cwe_knowledge_cache.json"

def load_cache():
    if os.path.exists(CACHE_FILE):
        with open(CACHE_FILE, 'r', encoding='utf-8') as f:
            try:
                return json.load(f)
            except json.JSONDecodeError:
                # 如果文件存在但是空的或损坏的，打印警告并返回空字典
                print(f"    [系统警告] 缓存文件 {CACHE_FILE} 损坏或为空，已自动重置。")
                return {}
    return {}

def save_cache(cache_dict):
    with open(CACHE_FILE, 'w', encoding='utf-8') as f:
        json.dump(cache_dict, f, ensure_ascii=False, indent=4)

def fetch_cwe_from_mitre(cwe_id_str):
    """
    核心爬虫逻辑：去 MITRE 官网实时抓取指定 CWE 的信息。
    支持语义级案例清洗，避免生硬截断破坏上下文。
    """
    match = re.search(r'\d+', cwe_id_str)
    if not match:
        return None
    
    cwe_num = match.group(0)
    url = f"https://cwe.mitre.org/data/definitions/{cwe_num}.html"
    
    headers = {
        'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/120.0.0.0 Safari/537.36'
    }
    
    try:
        response = requests.get(url, headers=headers, timeout=15)
        if response.status_code != 200:
            print(f"    [爬虫异常] 无法访问 {cwe_id_str} 官方页面 (HTTP {response.status_code})")
            return None
            
        soup = BeautifulSoup(response.text, 'html.parser')
        
        result = {
            "def": "Definition not found on MITRE.",
            "manifest": "Manifestation examples not found on MITRE."
        }
        
        # 1. 抓取标准化描述 (Description)
        desc_div = soup.find(id="oc_Description") or soup.find(id="Description")
        if desc_div:
            detail = desc_div.find(class_='detail') or desc_div
            text = detail.get_text(separator=" ", strip=True)
            if text:
                result["def"] = text

        # 2. 抓取典型表现形式/案例 (Demonstrative Examples)
        example_div = soup.find(id="oc_Demonstrative_Examples") or soup.find(id="Demonstrative_Examples")
        if not example_div:
            example_div = soup.find(id="oc_Observed_Examples") or soup.find(id="Observed_Examples")
            
        if example_div:
            detail = example_div.find(class_='detail') or example_div
            text = detail.get_text(separator=" ", strip=True)
            
            # 基础文本清洗
            text = re.sub(r'Example Language:\s*\w+', '', text)
            text = re.sub(r'\(bad code\)|\(good code\)', '', text)
            text = re.sub(r'\s+', ' ', text).strip()
            
            if text:
                # 逻辑边界剥离
                # 利用正则匹配 "Example 2" (或 Example2, Example 3等)，将其作为切分点，
                # 确保只拿到纯净且完整的 Example 1。
                split_match = re.split(r'\s*Example\s*[2-9]\s*', text, maxsplit=1, flags=re.IGNORECASE)
                first_example = split_match[0].strip()
                
                # 语义安全截断 (Semantic Safe Cutoff)
                # 限制最大字符数为 1500。如果 Example 1 依然超长，则寻找最安全的语法边界。
                MAX_LEN = 1500
                if len(first_example) > MAX_LEN:
                    # 在 1500 字符内，逆向寻找最后一个合法的代码或语义结束符
                    safe_cut_idx = max(
                        first_example.rfind('. ', 0, MAX_LEN),   # 英文句号结尾
                        first_example.rfind('; ', 0, MAX_LEN),   # C/C++ 语句结尾
                        first_example.rfind('} ', 0, MAX_LEN),   # 作用域闭合
                        first_example.rfind('}', 0, MAX_LEN)     # 紧凑作用域闭合
                    )
                    
                    if safe_cut_idx != -1:
                        # 沿用找到的安全边界（包含该边界符本身）
                        first_example = first_example[:safe_cut_idx + 1].strip()
                    else:
                        # 找不到任何标点，只能硬切
                        first_example = first_example[:MAX_LEN].strip()
                        
                result["manifest"] = first_example

        return result
        
    except Exception as e:
        print(f"    [网络阻断] 抓取 {cwe_id_str} 时发生连接异常: {e}")
        return None

def get_cwe_knowledge(cwe_id_str):
    """
    对外暴露的接口：先查缓存，没有再去爬取
    """
    cache = load_cache()
    
    if cwe_id_str in cache:
        return cache[cwe_id_str]
        
    print(f"    [系统] 本地缓存未命中 {cwe_id_str}，正在启动自动抓取引擎...")
    knowledge = fetch_cwe_from_mitre(cwe_id_str)
    
    if knowledge:
        cache[cwe_id_str] = knowledge
        save_cache(cache)
        print(f"    [系统] {cwe_id_str} 官方知识提取成功并已缓存！")
        return knowledge
    else:
        return None

# 测试爬虫功能
if __name__ == "__main__":
    print("测试抓取 CWE-476 (空指针解引用)...")
    res = get_cwe_knowledge("CWE-476")
    print(json.dumps(res, ensure_ascii=False, indent=2))