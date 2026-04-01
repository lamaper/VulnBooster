import json
import pandas as pd
from sklearn.model_selection import train_test_split

def json_to_dataframe(json_path):
    """读取 JSON 或 JSONL 并转换为 DataFrame"""
    try:
        with open(json_path, 'r', encoding='utf-8') as f:
            data = json.load(f)
    except json.JSONDecodeError:
        # 如果是 JSONL (每行一个 JSON)
        data =[]
        with open(json_path, 'r', encoding='utf-8') as f:
            for line in f:
                if line.strip():
                    data.append(json.loads(line))
                    
    df = pd.DataFrame(data)
    return df

print("1. 正在处理训练集 (ReVeal)...")
# 读取你之前准备好的 ReVeal 数据
reveal_df = json_to_dataframe("../../../../data/reveal/reveal_original.json")

# 因为需要训练，我们将 ReVeal 划分为 训练集 (90%) 和 验证集 (10%，用于 Early Stop)
train_df, valid_df = train_test_split(reveal_df, test_size=0.1, random_state=42, stratify=reveal_df['target'])

train_df.to_csv("reveal_train.csv", index=False, encoding='utf-8')
valid_df.to_csv("reveal_valid.csv", index=False, encoding='utf-8')
print(f"ReVeal 训练集: {len(train_df)} 条, 验证集: {len(valid_df)} 条")

print("2. 正在处理测试集 (Devign)...")
# 读取你刚下载的 Devign 数据 (假设路径如下，请根据实际情况修改)
devign_df = json_to_dataframe("../../../../data/devign/function.json")
devign_df.to_csv("devign_test.csv", index=False, encoding='utf-8')
print(f"Devign 测试集: {len(devign_df)} 条")

print("✅ 数据准备完成！")