import json
import random
import os

# ----------------- 配置 -----------------
VULN_FILE = "vulnerables.json"
NON_VULN_FILE = "non-vulnerables.json"
OUTPUT_FILE = "reveal_original.json"

# ----------------- 处理函数 -----------------
def process_data(filepath, label):
    processed =[]
    
    # 检查文件是否存在
    if not os.path.exists(filepath):
        print(f"❌ 找不到文件: {filepath}")
        return processed

    with open(filepath, "r", encoding="utf-8") as f:
        # ReVeal 的这两个文件通常是标准的 JSON 数组（即用[] 包裹所有对象）
        try:
            data = json.load(f)
            for item in data:
                # 检查是否存在 "code" 键
                if "code" in item:
                    # 按照 GVI 的要求，将代码放入 "func" 键，并添加 "target"
                    processed.append({
                        "func": item["code"],
                        "target": label
                    })
        except json.JSONDecodeError:
            # 如果万一是 JSONL 格式（每行一个 JSON 对象），则按行读取
            f.seek(0)
            for line in f:
                if not line.strip(): continue
                item = json.loads(line)
                if "code" in item:
                    processed.append({
                        "func": item["code"],
                        "target": label
                    })
                    
    return processed

# ----------------- 主程序 -----------------
print("开始处理 ReVeal 数据集...")

# 1. 读取并处理漏洞样本 (标签为 1)
print(f"👉 正在提取漏洞样本 (从 {VULN_FILE})...")
vuln_samples = process_data(VULN_FILE, label=1)
print(f"✅ 成功提取 {len(vuln_samples)} 条漏洞样本。")

# 2. 读取并处理正常样本 (标签为 0)
print(f"👉 正在提取正常样本 (从 {NON_VULN_FILE})...")
non_vuln_samples = process_data(NON_VULN_FILE, label=0)
print(f"✅ 成功提取 {len(non_vuln_samples)} 条正常样本。")

# 3. 合并数据
combined_data = vuln_samples + non_vuln_samples

# 4. 随机打乱数据 (打乱顺序对后续划分或截取很重要)
random.seed(42)
random.shuffle(combined_data)

# 5. 保存到新的 JSON 文件
print(f"👉 正在将合并后的数据保存至 {OUTPUT_FILE}...")
with open(OUTPUT_FILE, "w", encoding="utf-8") as f:
    # 使用 indent=2 方便人类阅读，如果不想要那么大的文件体积可以去掉 indent 参数
    json.dump(combined_data, f, indent=2)

print(f"🎉 恭喜！处理完成！总共合并了 {len(combined_data)} 条数据。")
print(f"下一步：请将生成的 {OUTPUT_FILE} 移动到 GVI 项目的 data/reveal/ 目录下。")