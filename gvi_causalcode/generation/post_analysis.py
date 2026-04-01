import json
import os
from typing import Dict

from langchain_community.document_loaders import JSONLoader
from langchain_community.embeddings import HuggingFaceEmbeddings
from langchain_community.vectorstores.chroma import Chroma
from matplotlib import pyplot as plt

import config

# 从 config 读取核心路径
origin_data = config.origin_vul_data # 这里必须和生成时的原始种子数据一致！
rm_comments_output = config.rm_comments_output
similarity_database_root = config.similarity_database_root
similarity_output = config.similarity_output
similarity_output_graph = config.similarity_output_graph
gen_output_result_root = config.gen_output_result_root

def metadata_func(json_obj: Dict, default_metadata: Dict) -> Dict:
    """
    提取 JSON 中的元数据。
    注意：适配了我们之前处理的 'func' 和 'target' 键名。
    """
    # 兼容原作者的字段和我们处理后的字段
    code_val = json_obj.get('func', json_obj.get('code', None))
    label_val = json_obj.get('target', json_obj.get('label', None))
    
    default_metadata['id'] = json_obj.get('id', 'unknown_id')
    default_metadata['file_name'] = json_obj.get('file_name', 'unknown_file')
    default_metadata['code'] = code_val
    default_metadata['label'] = label_val
    return default_metadata

def check_output():
    """
    核心：构建向量数据库，计算生成代码与原始代码的相似度
    """
    print(f"📦 正在加载原始种子数据: {origin_data}")
    source_loader = JSONLoader(
        file_path=origin_data,
        jq_schema='.[]',
        content_key='func', # 我们的原始数据代码键名叫 func
        metadata_func=metadata_func,
    )
    
    print(f"📦 正在加载生成的变异数据: {rm_comments_output}")
    target_loader = JSONLoader(
        file_path=rm_comments_output,
        jq_schema='.[]',
        content_key='func', # 变异数据的代码键名也是 func
        metadata_func=metadata_func,
    )
    
    source_documents = source_loader.load()
    target_documents = target_loader.load()

    persist_directory = similarity_database_root

    print("🧠 正在初始化 HuggingFace Embedding 模型 (第一次运行会自动下载模型)...")
    embeddings = HuggingFaceEmbeddings()
    
    print("🗄️ 正在构建原始代码的 Chroma 向量数据库...")
    db = Chroma.from_documents(
        source_documents,
        embeddings,
        persist_directory=persist_directory,
        collection_metadata={"hnsw:space": "cosine"}, # 使用余弦相似度
    )
    db.persist()
    
    # 重新加载以确保持久化成功
    db = Chroma(
        persist_directory=persist_directory,
        embedding_function=embeddings,
        collection_metadata={"hnsw:space": "cosine"},
    )

    similarity =[]
    print(f"🔍 开始为 {len(target_documents)} 条变异数据寻找最相似的原始代码...")
    for target in target_documents:
        # 对每一个生成的变异代码，在向量库中寻找最相似的 1 个原始代码
        result = db.similarity_search_with_score(
            target.page_content,
            k=1,
        )
        for src_doc, score in result:
            res = {
                'id': target.metadata['id'],
                'query_file_name': target.metadata['file_name'],
                'query_code': target.metadata['code'],
                'query_label': target.metadata['label'],
                'result_code': src_doc.metadata['code'],
                'similarity_score': float(score) # 强制转为 float 方便 JSON 序列化
            }
            similarity.append(res)

    # 将相似度计算结果保存下来
    os.makedirs(os.path.dirname(similarity_output), exist_ok=True)
    with open(similarity_output, 'w', encoding='utf-8') as f:
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
        
    print(f"⚖️ 开始根据相似度阈值 (<= 0.4) 过滤数据...")
    for item in data:
        # 这里的 score 是 Chroma 返回的 distance，通常 0 代表完全一样，最大为 2
        # 保留距离小于等于 0.4 的（既有变异，又没跑偏太远）
        if item['similarity_score'] <= 0.4:
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