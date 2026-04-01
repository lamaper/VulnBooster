import json
import os

# 把你下载的 vulnerables.json 单独格式化一下
with open("vulnerables.json", "r", encoding="utf-8") as f:
    data = json.load(f)

vul_only_data =[]
for item in data:
    if "code" in item:
        vul_only_data.append({
            "func": item["code"],
            "target": 1
        })

# 存入 config 中指定的路径
os.makedirs("../data/reveal/", exist_ok=True)
with open("../data/reveal/reveal_vul_only.json", "w", encoding="utf-8") as f:
    json.dump(vul_only_data, f, indent=2)

print("种子漏洞数据准备完成！")