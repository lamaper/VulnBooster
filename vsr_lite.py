import os
import json
import numpy as np
import pandas as pd
from typing import List, Dict
from openai import OpenAI
from sklearn.metrics.pairwise import cosine_similarity

# ================= 论文原版 Prompt 模板库 =================

# 这些是 VulGen/VulScribe 论文中使用的原始 Prompt 策略
TEMPLATES = {
    "base": """
Here are two code snippets specified below, modify code snippet No.2 in a way that it includes the logic of code No.1:
Code Snippet 1: "$MY_UNIQUE_PLACE_HOLDER_1"

Code Snippet 2: "$MY_UNIQUE_PLACE_HOLDER_2"

Put the generated code inside ```C ```
""",
    "extra": """
Here are two code snippets specified below, modify code snippet No.2 in a way that it includes the logic of code No.1:
Code Snippet 1: "$MY_UNIQUE_PLACE_HOLDER_1"

Code Snippet 2: "$MY_UNIQUE_PLACE_HOLDER_2"

Note that the following lines from the first code snippet have a high priority to be in the final modified code:

Lines separated by /~/ : "$MY_UNIQUE_PLACE_HOLDER_3"

Put the generated code inside ```C ```. (Do not include comments)
""",
    "ext_wl": """Here's two code snippets AA and BB, each including a function. Add some parts of the logic of AA to BB in a way that the result would include important lines of BB with some parts from AA. You can add variables to BB to produce a more correct code.
                  
Code Snippet AA: "$MY_UNIQUE_PLACE_HOLDER_1"

Code Snippet BB: "$MY_UNIQUE_PLACE_HOLDER_2"
                  
The following lines from BB are important and should be included in the final result, the rest may be changed or even removed if they have no relation to these lines: (Lines are separated via /~/)

"$MY_UNIQUE_PLACE_HOLDER_3"

Put the generated code inside ```C ``` and note that the final result should a function that takes all the input args of BB and more if required. (Do not include comments)
""",
    "mutation": """Here's a code snippet including a function. Except for the important lines mentioned below, mutate the rest of the code snippet so it is different from the original while keeping the original semantics.
To do so you can use one or more of the following rules:

Rules: 1-> Replace the local variables’ identifiers with new non-repeated identifiers
2-> Replace the for statement with an semantic-equivalent while statement, and vice versa
3-> Change the assignment x++ into x=x+1 or x=x+1 into x+=1
4-> Merge the declaration statements into a single composite declaration statement
5-> Divide the composite declaration statement into separated declaration statements
6-> Switch the two code blocks in the if statement and the corresponding else statement
7-> Change a single if statement into a conditional expression statement.
8-> Change a conditional expression statement into a single if statement
9-> Divide a infix expression into two expressions whose values are stored in temporary variables
10-> Divide a if statement with a compound condition (∧ , ∨, or ¬) into two nested if statements
11-> Switch the places of two adjacent statements in a code block, where the former statement has no shared variable with the latter statement
12-> Replace the if-continue statement in a loop block with if-else statement
13-> Switch the two expressions on both sides of the infix expression whose operator is =
14-> Switch the two string objects on both sides of an equality expression
15-> Divide a pre-fix or post-fix expression into two expressions whose values are stored in temporary variables
16-> Transform the ‘‘Switch-Case’’ statement into the corresponding ‘‘If-Else’’ statement.

Code Snippet: "$MY_UNIQUE_PLACE_HOLDER_1"
                  
The following lines are important and should be included in the final result, but they can still be changed using only the first 5 rules, the rest may be changed using any of the rules or can even be removed if they have no relation to these lines: (Lines are separated via /~/)

"$MY_UNIQUE_PLACE_HOLDER_2"

Put the generated code inside ```C ```. (Do not include comments)
"""
}

# ================= 核心逻辑类 =================

class VulScribeRLite:
    def __init__(self, api_key: str):
        self.client = OpenAI(
            api_key=api_key,
            # Google 的 OpenAI 兼容接口地址
            base_url="https://generativelanguage.googleapis.com/v1beta/openai/"
        )
        self.knowledge_base = [] 
        self.kb_codes = []       
        self.kb_vectors = None   

    def get_embedding(self, text: str):
        """
        [真实 RAG] 调用 Google 模型生成代码向量
        """
        text = text.replace("\n", " ") # Google Embedding 建议去掉换行
        try:
            response = self.client.embeddings.create(
                input=[text],
                # 对应你列表里的 Embedding 模型
                model="models/gemini-embedding-001" 
            )
            return response.data[0].embedding
        except Exception as e:
            print(f"Embedding API Error: {e}")
            # 如果 API 报错，为了不中断流程，暂时返回随机向量
            # 注意：gemini-embedding-001 维度通常是 768
            return np.random.rand(768).tolist()

    def build_knowledge_base(self, clean_samples: List[str]):
        """构建 RAG 索引"""
        print(f"正在构建知识库，共 {len(clean_samples)} 条样本...")
        self.kb_codes = clean_samples
        vectors = []
        for code in clean_samples:
            vectors.append(self.get_embedding(code))
        self.kb_vectors = np.array(vectors)
        print("知识库构建完成。")

    def retrieve(self, target_code: str, top_k: int = 3):
        """检索最相似的代码片段"""
        if self.kb_vectors is None:
            return []
        
        target_vec = np.array([self.get_embedding(target_code)])
        similarities = cosine_similarity(target_vec, self.kb_vectors)[0]
        top_indices = similarities.argsort()[-top_k:][::-1]
        
        return [self.kb_codes[i] for i in top_indices]

    def construct_prompt(self, strategy: str, target_code: str, references: List[str]):
        """
        
        根据策略名称和上下文填充原版模板
        """
        if strategy not in TEMPLATES:
            raise ValueError(f"Unknown strategy: {strategy}")

        template = TEMPLATES[strategy]
        
        # --- 策略 A: Mutation (不需要参考代码，直接变异目标代码) ---
        if strategy == "mutation":
            # 占位符1: 目标代码
            prompt = template.replace("$MY_UNIQUE_PLACE_HOLDER_1", target_code)
            # 占位符2: 关键行 (这里我们简单假设整个函数体都重要，或者留空)
            # 在实际论文中，这里通常填入 'flaw_line'，这里演示留空或填入部分代码
            prompt = prompt.replace("$MY_UNIQUE_PLACE_HOLDER_2", "") 
            return prompt

        # --- 策略 B: Base / Extension (需要参考代码) ---
        # 如果没有检索到参考代码，为了不报错，我们必须给一个默认值
        ref_code = references[0] if references else "// No reference found"

        if strategy == "base":
            # 逻辑: 将参考代码(No.1)的逻辑注入到目标代码(No.2)中
            prompt = template.replace("$MY_UNIQUE_PLACE_HOLDER_1", ref_code)
            prompt = prompt.replace("$MY_UNIQUE_PLACE_HOLDER_2", target_code)
            return prompt

        if strategy == "ext_wl":
            # 逻辑: 将参考代码(AA)的部分逻辑添加到目标代码(BB)
            prompt = template.replace("$MY_UNIQUE_PLACE_HOLDER_1", ref_code)
            prompt = prompt.replace("$MY_UNIQUE_PLACE_HOLDER_2", target_code)
            # 占位符3: BB中的重要行 (这里简单填入 target_code 的第一行作为演示)
            important_lines = target_code.split('\n')[0] if target_code else ""
            prompt = prompt.replace("$MY_UNIQUE_PLACE_HOLDER_3", important_lines)
            return prompt

        # 默认返回基础模板
        return template

    def generate_vulnerability(self, target_code: str, strategy: str = "base"):
        """
        RAG + LLM 生成新漏洞
        :param strategy: 选择使用哪个模板 ('base', 'mutation', 'ext_wl' 等)
        """
        # 1. 检索 (Retrieval)
        # 即使是 mutation 策略，有时候也检索一下作为备用，但主要用于 base/ext
        references = self.retrieve(target_code, top_k=1)
        
        # 2. 构建 Prompt (Construction)
        try:
            prompt = self.construct_prompt(strategy, target_code, references)
        except Exception as e:
            return f"Error constructing prompt: {e}"

        # 3. 调用 LLM (Generation)
        try:
            response = self.client.chat.completions.create(
                model="gemini-2.5-flash", # 这里确保是有效的模型名
                messages=[{"role": "user", "content": prompt}],
                temperature=0.7
            )
            return response.choices[0].message.content
        except Exception as e:
            return f"Error from API: {e}"

# ================= 3. 运行示例 =================

if __name__ == "__main__":
    # 准备数据
    clean_code_database = [
        "void safe_copy(char* src) { char dest[100]; strncpy(dest, src, 100); }",
        "int calculate(int a, int b) { if (b==0) return 0; return a/b; }",
    ]
    
    target_function = "void user_input() { char buffer[10]; gets(buffer); }"
    
    # 初始化
    # 请务必在环境变量或这里填入你的 Google API Key
    api_key = os.getenv("OPENAI_API_KEY", "AIzaSyA74l3-6A8OWTu8cdHejOoKS___KcJJQdc") 
    engine = VulScribeRLite(api_key)
    
    # 构建索引
    engine.build_knowledge_base(clean_code_database)
    
    print("-" * 30)
    print(">>> 策略 1: Base (注入逻辑)")
    result_base = engine.generate_vulnerability(target_function, strategy="base")
    print(result_base)
    
    print("-" * 30)
    print(">>> 策略 2: Mutation (代码变异)")
    result_mut = engine.generate_vulnerability(target_function, strategy="mutation")
    print(result_mut)
    print("-" * 30)