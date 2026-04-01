import json
import os
import shutil
from tqdm import tqdm

def json_to_c_files(json_path, output_root):
    """将 JSON 格式的代码导出为 CausalCode 需要的 0/1 文件夹结构"""
    # 清空并重建输出目录
    if os.path.exists(output_root):
        shutil.rmtree(output_root)
    os.makedirs(os.path.join(output_root, '0'), exist_ok=True)
    os.makedirs(os.path.join(output_root, '1'), exist_ok=True)

    with open(json_path, 'r', encoding='utf-8') as f:
        data = json.load(f)

    for i, item in enumerate(tqdm(data, desc=f"Processing {os.path.basename(json_path)}")):
        code = item.get('func', item.get('code', ''))
        label = str(item.get('target', item.get('label', 0)))
        
        # 将代码写入对应的 0 或 1 文件夹
        file_path = os.path.join(output_root, label, f"{i}.c")
        with open(file_path, 'w', encoding='utf-8') as cf:
            cf.write(code)

print("1. 正在将 ReVeal 数据集转换为文件树...")
# 指向你之前合并好的 reveal_original.json
json_to_c_files("./reveal/reveal_original.json", "../data_raw/reveal/origin_s")

print("2. 正在将 Devign 数据集转换为文件树...")
# 指向你下载好的 devign function.json
json_to_c_files("./devign/function.json", "../data_raw/devign/origin_s")

print("✅ 文件树构建完成！")