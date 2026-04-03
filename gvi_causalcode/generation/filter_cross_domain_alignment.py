import argparse
import gzip
import json
import math
import os
import pickle
import re
from collections import defaultdict

from sklearn.feature_extraction.text import TfidfVectorizer
from sklearn.metrics.pairwise import linear_kernel


def parse_args():
    parser = argparse.ArgumentParser(description="按目标域风格对增强样本进行重打分与筛选。")
    parser.add_argument("--similarity-json", required=True, help="post_analysis.py 生成的 similarity.json 路径。")
    parser.add_argument("--target-pkl", required=True, help="目标域 origin_s/data.pkl.gz 路径。")
    parser.add_argument("--output-json", required=True, help="输出筛选后的 augmented json 路径。")
    parser.add_argument("--report-json", required=True, help="输出筛选报告路径。")
    parser.add_argument("--source-max-distance", type=float, default=0.92, help="与源域的最大允许距离。")
    parser.add_argument("--source-min-distance", type=float, default=0.10, help="与源域的最小允许距离，避免近重复。")
    parser.add_argument("--target-min-cosine", type=float, default=0.08, help="与目标域训练集的最小字符级余弦相似度。")
    parser.add_argument("--keep-top-n", type=int, default=0, help="保留前 N 条。0 表示按比例。")
    parser.add_argument("--keep-ratio", type=float, default=0.35, help="保留比例，keep-top-n=0 时生效。")
    parser.add_argument("--max-per-seed", type=int, default=2, help="每个源 seed 最多保留多少条，避免单个 seed 支配增强集。")
    parser.add_argument("--target-use-test", action="store_true", help="是否将目标域 test split 也作为无标签风格参考。默认只用 train split，避免测试泄漏。")
    return parser.parse_args()


def remove_comment(text):
    def replacer(match):
        s = match.group(0)
        if s.startswith("/"):
            return " "
        return s

    pattern = re.compile(
        r"//.*?$|/\*.*?\*/|\'(?:\\.|[^\\\'])*\'|\"(?:\\.|[^\\\"])*\"",
        re.DOTALL | re.MULTILINE,
    )
    return re.sub(pattern, replacer, text)


def safe_tokenize(code):
    token_pattern = re.compile(
        r'(?:"(?:\\.|[^"\\])*")|'
        r"(?:'(?:\\.|[^'\\])*')|"
        r"[a-zA-Z_]\w*|"
        r"\d+(?:\.\d+)?(?:[eE][+-]?\d+)?[fFlLuU]*|"
        r"!=|==|<=|>=|&&|\|\||->|>>|<<|\+\+|--|"
        r"\S"
    )
    return token_pattern.findall(code)


def normalize_code(code):
    return "\n".join(line.rstrip() for line in remove_comment(code).strip().splitlines()).strip()


def load_similarity_items(path):
    with open(path, "r", encoding="utf-8") as f:
        data = json.load(f)
    items = []
    for item in data:
        items.append(
            {
                "id": item.get("id"),
                "file_name": item.get("query_file_name", "unknown_file"),
                "code": normalize_code(item.get("query_code", "")),
                "label": int(item.get("query_label", 1)),
                "source_distance": float(item.get("similarity_score", 1.0)),
            }
        )
    return items


def load_target_codes(path, use_test=False):
    with gzip.open(path, "rb") as f:
        data = pickle.load(f)
    codes = [" ".join(tokens) for tokens in data["raw_tr"]]
    lengths = [len(tokens) for tokens in data["raw_tr"]]
    if use_test:
        codes.extend(" ".join(tokens) for tokens in data["raw_te"])
        lengths.extend(len(tokens) for tokens in data["raw_te"])
    return codes, lengths


def build_target_similarity(codes, target_codes):
    vectorizer = TfidfVectorizer(analyzer="char_wb", ngram_range=(3, 5), min_df=2)
    matrix = vectorizer.fit_transform(target_codes + codes)
    target_matrix = matrix[: len(target_codes)]
    gen_matrix = matrix[len(target_codes) :]
    sims = linear_kernel(gen_matrix, target_matrix)
    return sims.max(axis=1)


def length_alignment_score(length_value, mean_value, std_value):
    if std_value <= 1e-6:
        return 1.0
    z = abs(length_value - mean_value) / std_value
    return math.exp(-z)


def source_novelty_score(distance_value, min_distance, max_distance):
    if max_distance <= min_distance:
        return 0.0
    clamped = min(max(distance_value, min_distance), max_distance)
    return (clamped - min_distance) / (max_distance - min_distance)


def infer_seed_group(file_name):
    base = os.path.basename(file_name)
    head = base.split("_", 1)[0]
    return head


def select_items(items, keep_top_n, keep_ratio, max_per_seed):
    selected = []
    per_seed = defaultdict(int)
    target_n = keep_top_n if keep_top_n > 0 else max(1, int(len(items) * keep_ratio))
    for item in items:
        seed_group = infer_seed_group(item["file_name"])
        if max_per_seed > 0 and per_seed[seed_group] >= max_per_seed:
            continue
        selected.append(item)
        per_seed[seed_group] += 1
        if len(selected) >= target_n:
            break
    return selected


def main():
    args = parse_args()
    candidates = load_similarity_items(args.similarity_json)
    target_codes, target_lengths = load_target_codes(args.target_pkl, use_test=args.target_use_test)

    if not candidates:
        raise RuntimeError("similarity.json 为空，无法执行跨域对齐筛选。")
    if not target_codes:
        raise RuntimeError("目标域参考语料为空，无法执行跨域对齐筛选。")

    candidate_codes = [item["code"] for item in candidates]
    target_similarities = build_target_similarity(candidate_codes, target_codes)
    target_mean_len = sum(target_lengths) / len(target_lengths)
    target_std_len = math.sqrt(sum((x - target_mean_len) ** 2 for x in target_lengths) / len(target_lengths))

    rescored = []
    for item, target_cosine in zip(candidates, target_similarities):
        tokens = safe_tokenize(item["code"])
        token_len = len(tokens)
        source_distance = item["source_distance"]
        source_ok = args.source_min_distance <= source_distance <= args.source_max_distance
        target_ok = float(target_cosine) >= args.target_min_cosine
        length_score = length_alignment_score(token_len, target_mean_len, target_std_len)
        novelty_score = source_novelty_score(source_distance, args.source_min_distance, args.source_max_distance)
        final_score = (
            0.55 * float(target_cosine)
            + 0.25 * length_score
            + 0.20 * novelty_score
        )
        rescored.append(
            {
                "id": item["id"],
                "file_name": item["file_name"],
                "func": item["code"],
                "target": item["label"],
                "source_distance": source_distance,
                "target_cosine": float(target_cosine),
                "token_len": token_len,
                "length_score": length_score,
                "novelty_score": novelty_score,
                "final_score": final_score,
                "source_ok": source_ok,
                "target_ok": target_ok,
            }
        )

    passed = [item for item in rescored if item["source_ok"] and item["target_ok"]]
    passed.sort(key=lambda x: (-x["final_score"], -x["target_cosine"], x["source_distance"]))
    selected = select_items(passed, args.keep_top_n, args.keep_ratio, args.max_per_seed)

    output_items = [
        {
            "id": new_id,
            "file_name": item["file_name"],
            "func": item["func"],
            "target": item["target"],
            "source_distance": item["source_distance"],
            "target_cosine": item["target_cosine"],
            "alignment_score": item["final_score"],
        }
        for new_id, item in enumerate(selected)
    ]

    report = {
        "similarity_json": args.similarity_json,
        "target_pkl": args.target_pkl,
        "target_use_test": args.target_use_test,
        "candidate_count": len(candidates),
        "passed_source_and_target_gate": len(passed),
        "selected_count": len(output_items),
        "source_min_distance": args.source_min_distance,
        "source_max_distance": args.source_max_distance,
        "target_min_cosine": args.target_min_cosine,
        "keep_top_n": args.keep_top_n,
        "keep_ratio": args.keep_ratio,
        "max_per_seed": args.max_per_seed,
        "target_mean_token_len": target_mean_len,
        "target_std_token_len": target_std_len,
        "top_selected_preview": [
            {
                "file_name": item["file_name"],
                "source_distance": item["source_distance"],
                "target_cosine": item["target_cosine"],
                "alignment_score": item["alignment_score"],
            }
            for item in output_items[:20]
        ],
    }

    os.makedirs(os.path.dirname(args.output_json), exist_ok=True)
    with open(args.output_json, "w", encoding="utf-8") as f:
        json.dump(output_items, f, indent=2)
    with open(args.report_json, "w", encoding="utf-8") as f:
        json.dump(report, f, indent=2)

    print(f"✅ 跨域对齐筛选完成，候选数: {len(candidates)}")
    print(f"✅ 通过 source/target 双门控: {len(passed)}")
    print(f"✅ 最终保留样本数: {len(output_items)}")
    print(f"📁 输出增强数据: {args.output_json}")
    print(f"📁 输出筛选报告: {args.report_json}")


if __name__ == "__main__":
    main()
