"""
Smoke 测试集均衡采样脚本
核心功能：
从指定的原始数据集中，分别提取指定数量的正样本（漏洞）和负样本（安全），
并在打乱顺序后归档至 smoke 独立测试目录。
"""
import json
import random
from pathlib import Path

# =====================================================================
# 采样策略与路径配置中心
# =====================================================================
INPUT_DIR = Path("../dataset")
OUTPUT_DIR = Path("../smoke")

# 随机种子，确保每次采样的结果可复现
SEED = 42 
# 强制类别均衡：正负样本各抽取的数量
NUM_PER_CLASS = 50 

random.seed(SEED)

# =====================================================================
# 核心采样逻辑
# =====================================================================
def build_balanced_smoke_set(split_name: str):
    """
    针对单个数据集执行分离、采样与乱序重组。
    """
    input_path = INPUT_DIR / f"primevul_{split_name}.jsonl"
    output_path = OUTPUT_DIR / f"primevul_{split_name}.jsonl"

    if not input_path.exists():
        print(f"[异常] 数据源缺失: {input_path.resolve()}，已跳过。")
        return

    safe_samples = []
    vul_samples = []

    print(f" -> 正在解析加载 [ {split_name} ] 集合...")
    
    # 1. 数据按目标类别分流
    with open(input_path, 'r', encoding='utf-8') as fin:
        for line in fin:
            line = line.strip()
            if not line: 
                continue
            try:
                data = json.loads(line)
                target = data.get("target", 0)
                if target == 1:
                    vul_samples.append(line)
                else:
                    safe_samples.append(line)
            except json.JSONDecodeError:
                continue

    # 2. 执行绝对数量的随机抽样 
    actual_safe_count = min(NUM_PER_CLASS, len(safe_samples))
    actual_vul_count = min(NUM_PER_CLASS, len(vul_samples))
    
    sampled_safe = random.sample(safe_samples, actual_safe_count)
    sampled_vul = random.sample(vul_samples, actual_vul_count)

    # 3. 乱序重组 
    smoke_samples = sampled_safe + sampled_vul
    random.shuffle(smoke_samples)

    # 4. 物理落盘
    with open(output_path, 'w', encoding='utf-8') as fout:
        for line in smoke_samples:
            fout.write(line + '\n')

    print(f"    [抽取完毕] {split_name:<5} | 负样本(0): {actual_safe_count:02d} 项, 正样本(1): {actual_vul_count:02d} 项")


# =====================================================================
# 主控流入口
# =====================================================================
if __name__ == "__main__":
    
    # 确立目标基址
    OUTPUT_DIR.mkdir(parents=True, exist_ok=True)
    
    print(f"\n{'='*60}")
    print(f"[系统调度] 启动 Smoke 测试集 1:1 均衡采样流水线")
    print(f"           挂载目标: {OUTPUT_DIR.resolve()}")
    print(f"{'='*60}\n")

    # 遍历标准生命周期数据集
    for split in ["train", "valid", "test"]:
        build_balanced_smoke_set(split)

    print(f"\n{'='*60}")
    print(f"[流程终止] 迷你数据集构建成功，可以开始你的流水线测试了！")
    print(f"{'='*60}\n")