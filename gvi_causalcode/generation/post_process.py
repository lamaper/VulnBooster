import json
import os
import re
import config
from tqdm import tqdm

# ================= 1. 读取配置路径 =================
gen_output_root = config.gen_output_root
gen_output_result_root = config.gen_output_result_root
rm_comments_output = config.rm_comments_output

# ================= 2. 清洗函数 =================
def remove_comments(code):
    """去除 C 代码中的单行和多行注释，同时保留字符串里的内容"""
    pattern = r"(\".*?\"|\'.*?\')|(/\*.*?\*/|//[^\r\n]*$)"
    regex = re.compile(pattern, re.MULTILINE | re.DOTALL)

    def _replacer(match):
        if match.group(2) is not None:
            return ""  # 匹配到注释，替换为空
        else:  
            return match.group(1) # 匹配到字符串，原样保留

    return regex.sub(_replacer, code)

def remove_selected_structs(code):
    """去除头文件和某些结构体定义，防止大模型自由发挥的外部依赖导致编译失败"""
    code = re.sub(r'#include[^\n]*', '', code)
    code = re.sub(r'#define[^\n]*', '', code)
    code = re.sub(r'typedef\s+struct\s+\w*\s*\{[^}]*\}\s*\w+;', '', code, flags=re.DOTALL)
    code = re.sub(r'typedef\s+struct\s*\{[^}]*\}\s*\w+;', '', code, flags=re.DOTALL)
    code = re.sub(r'typedef\s+struct\s+\w*\s*\{[^}]*\}\s*\w+,\s*\*?\w+;', '', code, flags=re.DOTALL)
    code = re.sub(r'typedef\s+enum\s*\{([^\}]*)\}\s*(\w+);', '', code, flags=re.DOTALL)
    return code

def extract_code_blocks(context):
    """优先从 Assistant 回答里提取代码块，兼容旧版 Step 4 输出。"""
    assistant_sections = re.findall(
        r"=== Assistant Turn \d+ ===\n(.*?)(?=\n=== (?:User|Assistant) Turn \d+ ===|\Z)",
        context,
        re.DOTALL,
    )

    if assistant_sections:
        target_text = "\n".join(assistant_sections)
    else:
        parts = context.split("Step 4:")
        target_text = parts[-1] if len(parts) >= 2 else context

    pattern = r"```(?:c|cpp)?\s*\n(.*?)\n```"
    matches = re.findall(pattern, target_text, re.DOTALL | re.IGNORECASE)

    # 保序去重，避免同一轮自我改写把相同代码块重复保留下来。
    unique_matches = []
    seen = set()
    for match in matches:
        normalized = match.strip()
        if not normalized or normalized in seen:
            continue
        seen.add(normalized)
        unique_matches.append(normalized)
    return unique_matches

# ================= 3. 主处理流程 =================
def process_generated_files():
    if not os.path.exists(gen_output_result_root):
        os.makedirs(gen_output_result_root, exist_ok=True)

    print(f"🔍 正在扫描生成目录: {gen_output_root}")
    
    extracted_data =[]
    global_id = 0
    error_count = 0

    # 遍历基于种子文件生成的子文件夹 (例如 0, 1, 2...)
    if not os.path.exists(gen_output_root):
        print("❌ 找不到生成目录，请先运行 chain_gen.py！")
        return

    subdirs =[d for d in os.listdir(gen_output_root) if os.path.isdir(os.path.join(gen_output_root, d))]
    
    for subdir in tqdm(subdirs, desc="处理生成结果"):
        dir_path = os.path.join(gen_output_root, subdir)
        
        # 遍历子文件夹下的所有 .txt 文件
        for file in os.listdir(dir_path):
            if not file.endswith('.txt'):
                continue
                
            file_path = os.path.join(dir_path, file)
            with open(file_path, 'r', encoding='utf-8', errors='ignore') as f:
                context = f.read()
                
            # 提取代码块
            matches = extract_code_blocks(context)
            
            if not matches:
                error_count += 1
                continue
                
            # 处理提取出来的每一个代码变体
            for num, match in enumerate(matches):
                # 1. 深度清洗
                cleaned_code = remove_selected_structs(remove_comments(match))
                # 如果清洗后代码空了，跳过
                if not cleaned_code.strip():
                    continue
                    
                # 2. 组装为标准训练格式
                new_file_name = f"{subdir}_{num}_1.c"
                ex = {
                    'id': global_id,
                    'file_name': new_file_name,
                    'file_path': file_path,
                    'func': cleaned_code, # 注意：我改成了 'func' 以适配你之前的 reveal_original.json
                    'target': 1            # 1 代表这是漏洞代码
                }
                global_id += 1
                extracted_data.append(ex)

    # 写入最终的清洗后 JSON 文件
    print(f"\n✅ 提取完成！共提取出 {len(extracted_data)} 条有效漏洞变体。")
    print(f"⚠️ 未找到代码块的失败文件数: {error_count}")
    
    with open(rm_comments_output, 'w', encoding='utf-8') as f:
        json.dump(extracted_data, f, indent=4)
    print(f"📁 已保存清洗后的纯净漏洞数据至: {rm_comments_output}")


if __name__ == "__main__":
    process_generated_files()
