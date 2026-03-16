import json

# 读取原始数据集
with open("reveal_original.json", "r", encoding="utf-8") as f:
    original_data = json.load(f)

# 读取 Gemini 生成的新漏洞数据
with open("chain_reveal_gemini_result/chain_rm_comments.json", "r", encoding="utf-8") as f:
    generated_vul_data = json.load(f)

# 直接将新生成的漏洞拼接到原数据后面
augmented_data = original_data + generated_vul_data

# 保存为最终用于喂给分类器训练的数据集
with open("reveal_augmented.json", "w", encoding="utf-8") as f:
    json.dump(augmented_data, f, indent=2)

print(f"合并完成！原始数据 {len(original_data)} 条，增强数据 {len(generated_vul_data)} 条。")
print(f"最终增强版训练集总数：{len(augmented_data)} 条。")