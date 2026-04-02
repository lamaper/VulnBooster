import argparse
import gzip
import json
import os
import pickle
from typing import List, Tuple

import config
import sys

CURRENT_DIR = os.path.dirname(__file__)
TRAIN_BERT_DIR = os.path.normpath(os.path.join(CURRENT_DIR, "..", "train_bert"))
PREPROCESS_DIR = os.path.normpath(os.path.join(CURRENT_DIR, "..", "preprocess-lstm"))
if TRAIN_BERT_DIR not in sys.path:
    sys.path.insert(0, TRAIN_BERT_DIR)
if PREPROCESS_DIR not in sys.path:
    sys.path.insert(0, PREPROCESS_DIR)

import build_dataset as bd
from mytoken import remove_comment, safe_tokenize, extract_uids_regex
from pattern import StmtInsPos, DeclInsPos


def parse_args():
    parser = argparse.ArgumentParser(description="将生成的漏洞样本合并为新的增强训练任务。")
    parser.add_argument("--source-root", default="../data", help="原始任务数据根目录。")
    parser.add_argument("--output-root", default="../data", help="增强任务输出根目录。")
    parser.add_argument("--source-task", default="reveal", help="原始训练任务名。")
    parser.add_argument("--new-task", required=True, help="新增强任务名。")
    parser.add_argument("--aug-json", default=os.path.join(config.gen_output_result_root, "final_augmented_vul.json"))
    parser.add_argument("--limit-generated", type=int, default=0, help="只取前 N 条增强样本。0 表示全部。")
    parser.add_argument("--max-origin-train", type=int, default=0, help="仅保留前 N 条原始训练样本，便于 smoke test。")
    parser.add_argument("--max-origin-test", type=int, default=0, help="仅保留前 N 条原始测试样本，便于 smoke test。")
    return parser.parse_args()


def _load_pickle(path):
    with gzip.open(path, "rb") as f:
        return pickle.load(f)


def _save_pickle(path, obj):
    os.makedirs(os.path.dirname(path), exist_ok=True)
    with gzip.open(path, "wb") as f:
        pickle.dump(obj, f)


def _normalize_code(code: str) -> str:
    return "\n".join(line.rstrip() for line in code.strip().splitlines()).strip()


def _tokenize_code(code: str) -> List[str]:
    stripped = remove_comment(code)
    return safe_tokenize(stripped)


def _uid_positions(tokens: List[str]):
    uid_set = extract_uids_regex(" ".join(tokens))
    positions = {}
    for idx, token in enumerate(tokens):
        if token in uid_set:
            positions.setdefault(token, []).append(idx)
    return positions


def _prepare_generated_samples(aug_items, existing_raw_tr, limit_generated=0) -> Tuple[list, list, list]:
    existing_texts = {" ".join(tokens) for tokens in existing_raw_tr}
    seen_new = set()
    raws, labels, meta = [], [], []

    for item in aug_items:
        code = item.get("func", item.get("code", ""))
        label = int(item.get("target", item.get("label", 1)))
        if not code.strip():
            continue
        tokens = _tokenize_code(code)
        if len(tokens) < 5:
            continue
        key = " ".join(tokens)
        if key in existing_texts or key in seen_new:
            continue
        seen_new.add(key)
        raws.append(tokens)
        labels.append(label)
        meta.append(
            {
                "source_id": item.get("id"),
                "source_file_name": item.get("file_name"),
                "token_count": len(tokens),
                "label": label,
            }
        )
        if limit_generated > 0 and len(raws) >= limit_generated:
            break

    return raws, labels, meta


def _extend_vocab(idx2txt, txt2idx, raws):
    new_idx2txt = list(idx2txt)
    new_txt2idx = dict(txt2idx)
    for tokens in raws:
        for token in tokens:
            if token not in new_txt2idx:
                new_txt2idx[token] = len(new_idx2txt)
                new_idx2txt.append(token)
    return new_idx2txt, new_txt2idx


def main():
    args = parse_args()
    source_dir = os.path.join(args.source_root, args.source_task, "dataset", "origin_s")
    output_dir = os.path.join(args.output_root, args.new_task, "dataset", "origin_s")
    os.makedirs(output_dir, exist_ok=True)

    data = _load_pickle(os.path.join(source_dir, "data.pkl.gz"))
    uid = _load_pickle(os.path.join(source_dir, "oj_uid.pkl.gz"))
    inspos = _load_pickle(os.path.join(source_dir, "oj_inspos.pkl.gz"))

    if args.max_origin_train > 0:
        data["raw_tr"] = data["raw_tr"][: args.max_origin_train]
        data["y_tr"] = data["y_tr"][: args.max_origin_train]
        data["x_tr"] = data["x_tr"][: args.max_origin_train]
        uid["tr"] = uid["tr"][: args.max_origin_train]
        inspos["stmt_tr"] = inspos["stmt_tr"][: args.max_origin_train]
        inspos["decl_tr"] = inspos["decl_tr"][: args.max_origin_train]

    if args.max_origin_test > 0:
        data["raw_te"] = data["raw_te"][: args.max_origin_test]
        data["y_te"] = data["y_te"][: args.max_origin_test]
        data["x_te"] = data["x_te"][: args.max_origin_test]
        uid["te"] = uid["te"][: args.max_origin_test]
        inspos["stmt_te"] = inspos["stmt_te"][: args.max_origin_test]
        inspos["decl_te"] = inspos["decl_te"][: args.max_origin_test]

    with open(args.aug_json, "r", encoding="utf-8") as f:
        aug_items = json.load(f)

    new_raws, new_labels, metadata = _prepare_generated_samples(
        aug_items=aug_items,
        existing_raw_tr=data["raw_tr"],
        limit_generated=args.limit_generated,
    )

    if not new_raws:
        raise RuntimeError("没有可用的增强样本可合并。请检查 final_augmented_vul.json 或过滤阈值。")

    idx2txt, txt2idx = _extend_vocab(data["idx2txt"], data["txt2idx"], new_raws)
    new_x = bd.text2index(new_raws, txt2idx)
    new_uid_entries = [_uid_positions(tokens) for tokens in new_raws]
    new_stmt_pos = [StmtInsPos(tokens) for tokens in new_raws]
    new_decl_pos = [DeclInsPos(tokens) for tokens in new_raws]

    data["raw_tr"] = data["raw_tr"] + new_raws
    data["y_tr"] = data["y_tr"] + new_labels
    data["x_tr"] = data["x_tr"] + new_x
    data["idx2txt"] = idx2txt
    data["txt2idx"] = txt2idx

    uid["tr"] = uid["tr"] + new_uid_entries
    uid["all"] = sorted(set(uid["all"]).union(*(set(item.keys()) for item in new_uid_entries)))
    inspos["stmt_tr"] = inspos["stmt_tr"] + new_stmt_pos
    inspos["decl_tr"] = inspos["decl_tr"] + new_decl_pos

    _save_pickle(os.path.join(output_dir, "data.pkl.gz"), data)
    _save_pickle(os.path.join(output_dir, "oj_uid.pkl.gz"), uid)
    _save_pickle(os.path.join(output_dir, "oj_inspos.pkl.gz"), inspos)
    with open(os.path.join(output_dir, "dataset.done"), "w", encoding="utf-8") as f:
        f.write("generated\n")

    manifest = {
        "source_task": args.source_task,
        "new_task": args.new_task,
        "source_root": args.source_root,
        "output_root": args.output_root,
        "aug_json": args.aug_json,
        "origin_train_size": len(data["raw_tr"]) - len(new_raws),
        "origin_test_size": len(data["raw_te"]),
        "added_generated_size": len(new_raws),
        "final_train_size": len(data["raw_tr"]),
        "final_test_size": len(data["raw_te"]),
        "generated_samples": metadata,
    }
    with open(os.path.join(output_dir, "augmentation_manifest.json"), "w", encoding="utf-8") as f:
        json.dump(manifest, f, ensure_ascii=False, indent=2)

    print(f"✅ 增强任务已构建完成: {output_dir}")
    print(f"   原始训练样本: {manifest['origin_train_size']}")
    print(f"   新增增强样本: {manifest['added_generated_size']}")
    print(f"   最终训练样本: {manifest['final_train_size']}")


if __name__ == "__main__":
    main()
