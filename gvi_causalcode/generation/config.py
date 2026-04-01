import os

# ================= 1. Gemini API 配置 =================
# 使用环境变量提供密钥，避免把敏感信息提交到仓库里
GEMINI_API_KEY = os.getenv("GEMINI_API_KEY", "")
OPENAI_API_KEY = os.getenv("OPENAI_API_KEY", "")
# 推荐使用 gemini-1.5-pro 或 gemini-2.0-flash
MODEL = os.getenv("GEMINI_MODEL", "gemini-3-flash-preview")

# ================= 2. 路径配置 (适配 ReVeal) =================
# ⚠️注意：大模型进行“漏洞想象”时，只需要“漏洞代码”作为种子！
# 你需要将之前处理好的漏洞数据提取为一个单独的文件
origin_vul_data = '../data/reveal/reveal_vul_only.json' 

gen_output_root = '../data/reveal/chain_reveal_gemini'
gen_output_result_root = gen_output_root + '_result'                                    
gen_combine_output = os.path.join(gen_output_result_root, 'chain_combine.json')         
rm_comments_output = os.path.join(gen_output_result_root, 'chain_rm_comments.json')     
similarity_database_root = os.path.join(gen_output_result_root, 'db')                   
similarity_output = os.path.join(gen_output_result_root, 'similarity.json')             
similarity_output_graph = os.path.join(gen_output_result_root, 'similarity_hist.png')   

# ================= 3. GVI 核心：受 CoT 启发的思维链提示词 =================
# 系统提示词：赋予大模型安全专家的角色
chain_sys = "I need your help to generate some vulnerable C functions to train our ML model. Please using all your knowledge to follow the steps below.\n"

# 启用论文中 GVI 方法的核心：4 步完整思维链 (场景分析 -> 类型识别 -> 模式提取 -> 生成)
chain_inputs =[
    "\n```c\n{code}\n```\nStep 1: Application Scenario. Perform a general analysis of the application scenario of the given C language function example. Please limit your response to no more than 100 tokens. \n",
    "Step 2: Identify Vulnerability Type. Base on step 1, identify the type of security vulnerability present in the example function code. Please limit your response to no more than 100 tokens. \n",
    "Step 3: Extract Vulnerability Pattern. Base on step 2, extract the vulnerability pattern. Please limit your response to no more than 100 tokens.\n",
    "Step 4: Generate Similar Examples. Base on step 1 and step 3, create 4 independent and high-quality vulnerable functions similar to the example function's application scenario and vulnerability pattern. Please limit the response examples to no less than 800 tokens. \n",
]
