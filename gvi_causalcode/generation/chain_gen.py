import json
import os
import warnings
import random
from tqdm import tqdm

from langchain_classic.chains import ConversationChain
from langchain_classic.memory import ConversationBufferMemory
from langchain_core.prompts import ChatPromptTemplate, MessagesPlaceholder, HumanMessagePromptTemplate, SystemMessagePromptTemplate
from langchain_openai import ChatOpenAI

import config

warnings.filterwarnings('ignore')

# ----------------- 1. 获取配置信息 -----------------
# 优先读取 GEMINI_API_KEY，如果没有则回退读取 OPENAI_API_KEY
API_KEY = getattr(config, 'GEMINI_API_KEY', getattr(config, 'OPENAI_API_KEY', os.getenv("OPENAI_API_KEY")))
# 强制使用你指定的 Gemini 3.1 Pro 模型
MODEL = "gemini-3-flash-preview"

# 注意：生成干预样本必须使用“纯漏洞数据”作为种子！
origin_vul_data = config.origin_vul_data
chain_sys = config.chain_sys
chain_inputs = config.chain_inputs
gen_output_root = config.gen_output_root
gen_output_result_root = config.gen_output_result_root


def get_output_path(index, file_name):
    """安全地创建多级目录并返回输出路径"""
    if not os.path.exists(gen_output_root):
        os.makedirs(gen_output_root, exist_ok=True)
    output_dir = os.path.join(gen_output_root, str(index))
    if not os.path.exists(output_dir):
        os.makedirs(output_dir, exist_ok=True)
    output_path = os.path.join(output_dir, file_name)
    return output_path


def gen():
    print(f"🚀 正在加载种子漏洞数据: {origin_vul_data}")
    with open(origin_vul_data, 'r', encoding='utf-8') as f:
        data = json.load(f)
    print(f"✅ 共加载 {len(data)} 条漏洞种子代码。")

    # ----------------- 2. 初始化 Gemini 客户端 -----------------
    # 使用 langchain_openai 库结合 Google 官方兼容接口调用 Gemini
    chat = ChatOpenAI(
        model_name=MODEL,
        api_key=API_KEY,
        base_url="https://generativelanguage.googleapis.com/v1beta/openai/",
        streaming=False,  # 关闭流式输出，提高稳定性
        temperature=0.9   # 保持较高的温度以增加生成漏洞的多样性
    )
    
    prompt = ChatPromptTemplate.from_messages([
        SystemMessagePromptTemplate.from_template(chain_sys),
        MessagesPlaceholder(variable_name="history"),
        HumanMessagePromptTemplate.from_template("{input}")
    ])

    # ----------------- 3. 执行 GVI 思维链生成 -----------------
    print(f"🧠 开始使用 {MODEL} 引擎执行 GVI 思维链想象...")
    for index, item in enumerate(tqdm(data)):
        idx = index
        
        # 兼容不同的数据格式，提取源代码
        code_text = item.get('func', item.get('code', ''))
        if not code_text.strip():
            continue

        # 【修复 BUG】：在循环内部实例化 Memory，确保每个漏洞种子的上下文绝对纯净，防止污染
        memory = ConversationBufferMemory(memory_key="history", return_messages=True)
        conversation = ConversationChain(memory=memory, prompt=prompt, llm=chat, verbose=False)

        try:
            # 严格执行 config.py 中配置的 4 步思维链
            for chain_input in chain_inputs:
                # 【修复 BUG】：填入真正的源代码，而不是原本的 index 数字
                c_input = chain_input.format(code=code_text)
                conversation.predict(input=c_input)

            # 【修复 BUG】：处理文件名缺失的情况，自动回退生成唯一标识名
            file_name = item.get('file_name', f"vul_variant_{idx}.txt")
            output_path = get_output_path(idx, file_name)
            
            # 将大模型一步步思考的完整过程写入文件
            with open(output_path, 'w', encoding='utf-8') as f:
                f.write(f'System: {chain_sys}\n')
                f.write(memory.buffer_as_str)
                
        except Exception as e:
            print(f"\n❌ 处理第 {index} 条样本时遭遇错误: {e}")
        finally:
            memory.clear()

def few_shot():
    dataset = 'bigvul'
    train_path = f'./{dataset}_revision_left_2.json'
    test_path = f'./{dataset}_revision_2.json'
    with open(train_path, 'r') as f:
        train_data = json.load(f)
    vul = [item for item in train_data if item['label'] == 1]
    saf = [item for item in train_data if item['label'] == 0]
    train_vul_data = [item for item in vul if 0 < len(item['code']) <= 300]
    train_saf_data = [item for item in saf if 0 < len(item['code']) <= 300]
    print(len(train_vul_data), len(train_saf_data))

    with open(test_path, 'r') as f:
        test_data = json.load(f)

    chat = ChatOpenAI(
        # model_name='gpt-4-1106-preview',
        model_name=MODEL,
        streaming=True,
        # callbacks=[StreamingStdOutCallbackHandler()],
        temperature=.9
    )

    prompt = ChatPromptTemplate.from_messages([
        SystemMessagePromptTemplate.from_template(chain_sys),
        MessagesPlaceholder(variable_name="history"),
        HumanMessagePromptTemplate.from_template("{input}")
    ])

    memory = ConversationBufferMemory(memory_key="history", return_messages=True)
    conversation = ConversationChain(memory=memory, prompt=prompt, llm=chat, verbose=False)

    for index, item in enumerate(tqdm(test_data)):
        # index: data中的索引
        # idx: 生成文件的索引
        idx = index
        vul_examples = random.sample(train_vul_data, 10)
        saf_examples = random.sample(train_saf_data, 10)

        for chain_input in chain_inputs:
            # pdb.set_trace()
            # cot-shot
            # c_input = chain_input.format(code=item['code'])
            # 5-shot
            # c_input = chain_input.format(
            #     example0=vul_examples[0]['code'], label0='yes',
            #     example1=saf_examples[0]['code'], label1='no',
            #     example2=saf_examples[1]['code'], label2='no',
            #     example3=saf_examples[2]['code'], label3='no',
            #     example4=saf_examples[3]['code'], label4='no',
            #     code=item['code'])
            # 10-shot
            # c_input = chain_input.format(
            #     example0=saf_examples[0]['code'], label0='no',
            #     example1=saf_examples[1]['code'], label1='no',
            #     example2=saf_examples[2]['code'], label2='no',
            #     example3=saf_examples[3]['code'], label3='no',
            #     example4=saf_examples[4]['code'], label4='no',
            #     example5=vul_examples[0]['code'], label5='yes',
            #     example6=vul_examples[1]['code'], label6='yes',
            #     example7=vul_examples[2]['code'], label7='yes',
            #     example8=vul_examples[3]['code'], label8='yes',
            #     example9=vul_examples[4]['code'], label9='yes',
            #     code=item['code'])

            c_input = chain_input.format(
                example0=vul_examples[0]['code'], label0='yes',
                example1=vul_examples[1]['code'], label1='yes',
                example2=vul_examples[2]['code'], label2='yes',
                example3=vul_examples[3]['code'], label3='yes',
                example4=vul_examples[4]['code'], label4='yes',
                example5=vul_examples[5]['code'], label5='yes',
                example6=vul_examples[6]['code'], label6='yes',
                example7=vul_examples[7]['code'], label7='yes',
                example8=vul_examples[8]['code'], label8='yes',
                example9=vul_examples[9]['code'], label9='yes',
                example10=saf_examples[0]['code'], label10='no',
                example11=saf_examples[1]['code'], label11='no',
                example12=saf_examples[2]['code'], label12='no',
                example13=saf_examples[3]['code'], label13='no',
                example14=saf_examples[4]['code'], label14='no',
                example15=saf_examples[5]['code'], label15='no',
                example16=saf_examples[6]['code'], label16='no',
                example17=saf_examples[7]['code'], label17='no',
                example18=saf_examples[8]['code'], label18='no',
                example19=saf_examples[9]['code'], label19='no',
                code=item['code'])
            # pdb.set_trace()
            conversation.predict(input=c_input)
        # pdb.set_trace()
        output_path = get_output_path(idx, item['file_name'])
        # print(memory.buffer_as_str)
        # assert 0
        with open(output_path, 'w') as f:
            f.write(f'System: {chain_sys}\n')
            f.write(memory.buffer_as_str)
        memory.clear()


if __name__ == "__main__":
    gen()
    # few_shot()
