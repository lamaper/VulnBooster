import json
import os

from sklearn.feature_extraction.text import TfidfVectorizer
from sklearn.metrics.pairwise import linear_kernel

import config

# 从 config 读取核心路径
origin_data = config.origin_vul_data
rm_comments_output = config.rm_comments_output
similarity_output = config.similarity_output
gen_output_result_root = config.gen_output_result_root
similarity_threshold = config.SIMILARITY_THRESHOLD


def _load_items(path):
    with open(path, "r", encoding="utf-8") as f:
        data = json.load(f)

    items = []
    for item in data:
        items.append(
            {
                "id": item.get("id", "unknown_id"),
                "file_name": item.get("file_name", "unknown_file"),
                "code": item.get("func", item.get("code", "")),
                "label": item.get("target", item.get("label", 0)),
            }
        )
    return items


def check_output():
    """
    轻量相似度后端：使用 TF-IDF + cosine similarity，避免依赖 Chroma/LangChain。
    """
    print(f"📦 正在加载原始种子数据: {origin_data}")
    source_items = _load_items(origin_data)

    print(f"📦 正在加载生成的变异数据: {rm_comments_output}")
    target_items = _load_items(rm_comments_output)

    if not source_items or not target_items:
        raise RuntimeError("原始数据或生成数据为空，无法执行相似度分析。")

    print(f"🧠 使用轻量后端 `{config.SIMILARITY_BACKEND}` 计算代码相似度...")
    source_codes = [item["code"] for item in source_items]
    target_codes = [item["code"] for item in target_items]
    vectorizer = TfidfVectorizer(analyzer="char_wb", ngram_range=(3, 5))
    matrix = vectorizer.fit_transform(source_codes + target_codes)
    source_matrix = matrix[: len(source_codes)]
    target_matrix = matrix[len(source_codes) :]

    similarity = []
    print(f"🔍 开始为 {len(target_items)} 条变异数据寻找最相似的原始代码...")
    for idx, target in enumerate(target_items):
        scores = linear_kernel(target_matrix[idx], source_matrix).ravel()
        best_idx = int(scores.argmax())
        cosine_score = float(scores[best_idx])
        distance = 1.0 - cosine_score
        matched = source_items[best_idx]
        similarity.append(
            {
                "id": target["id"],
                "query_file_name": target["file_name"],
                "query_code": target["code"],
                "query_label": target["label"],
                "result_code": matched["code"],
                "similarity_score": distance,
                "cosine_similarity": cosine_score,
            }
        )

    os.makedirs(os.path.dirname(similarity_output), exist_ok=True)
    with open(similarity_output, "w", encoding="utf-8") as f:
        json.dump(similarity, f, indent=4)
    print(f"✅ 相似度计算完成！结果已保存至: {similarity_output}")

def get_similar():
    """
    核心过滤逻辑：如果生成的代码和原始代码距离太近（得分过低），说明没啥变化，直接扔掉。
    原作者设定的阈值是 0.4（距离 <= 0.4 视为过于相似）。
    但是！如果是计算距离（Cosine Distance），值越小表示越相似。
    所以原代码 `if item['similarity_score'] <= 0.4:` 其实是保留了**相似度高**的代码，剔除了变化太大的代码（防止大模型瞎写）。
    """
    out =[]
    index = 0
    with open(similarity_output, 'r', encoding='utf-8') as f:
        data = json.load(f)
        
    print(f"⚖️ 开始根据相似度阈值 (distance <= {similarity_threshold}) 过滤数据...")
    for item in data:
        # 这里的 score 是 Chroma 返回的 distance，通常 0 代表完全一样，最大为 2
        # 保留距离小于等于 0.4 的（既有变异，又没跑偏太远）
        if item['similarity_score'] <= similarity_threshold:
            frame = {
                'id': index,
                'file_name': item['query_file_name'],
                'func': item['query_code'], # 组装回后续训练需要的 func 键
                'target': item['query_label'],
                'similarity_score': item['similarity_score']
            }
            out.append(frame)
            index += 1
            
    final_path = os.path.join(gen_output_result_root, 'final_augmented_vul.json')
    with open(final_path, 'w', encoding='utf-8') as f:
        json.dump(out, f, indent=4)
    print(f"🎉 最终过滤完成！共保留 {len(out)} 条高质量漏洞变体。")
    print(f"📁 最终训练可用数据已保存至: {final_path}")

if __name__ == "__main__":
    # 依次执行计算相似度和过滤
    check_output()
    get_similar()
