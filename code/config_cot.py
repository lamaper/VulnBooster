# =====================================================================
# CoT 提示模板 
# =====================================================================

GENERATE_K = 3

chain_sys = "I need your help to generate some vulnerable C functions to train our ML model. Please using all your knowledge to follow the steps below.\n"

chain_inputs = [
    "\n```c\n{code}\n```\nStep 1: Application Scenario. Perform a general analysis of the application scenario of the given C language function example. Do not output any <think> tags, reasoning, or explanations. Only the final answer.  \n",

    "Step 2: Identify Vulnerability Type. Base on step 1, identify the type of security vulnerability present in the example function code. Do not output any <think> tags, reasoning, or explanations. Only the final answer.  \n",

    "Step 3: Extract Vulnerability Pattern. Base on step 2, extract the vulnerability pattern. Do not output any <think> tags, reasoning, or explanations. Only the final answer. \n",

    '''
    Step 4: Generate Similar Examples. Based on step 1 and step 3, create {K} independent and high-quality vulnerable functions similar to the example function's application scenario and vulnerability pattern. 
    Each generated function must not exceed 512 tokens when tokenized by a standard code tokenizer (e.g., CodeBERT tokenizer).
    Wrap EACH generated function in the following format, and ensure there is NO additional text between or inside the code blocks:
    ```c
    
    ```
    Generate exactly {K} such code blocks. Do not output any <think> tags, reasoning, or explanations. Only the final answer.
    ''',
]