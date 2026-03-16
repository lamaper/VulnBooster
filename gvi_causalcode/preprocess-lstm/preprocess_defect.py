import json
import os
import re
from pycparser import c_parser, preprocess_file
import ast

# 初始化 C 语言抽象语法树(AST)解析器
parser = c_parser.CParser()

def remove_comment(text):
    """
    功能：通过正则表达式安全地移除 C 源代码中的单行和多行注释。
    说明：逻辑与 mytoken.py 中的完全一致，通过把字符串字面量一起加入匹配来防止误删。
    """
    def replacer(match):
        s = match.group(0)
        # 如果匹配到的是以 '/' 开头的（即注释），将其替换为一个空格
        if s.startswith('/'):
            return " "  # note: a space and not an empty string (注意：必须替换为空格，防止相邻词元粘连)
        else:
            return s    # 匹配到的是字符串字面量，原样返回

    pattern = re.compile(
        r'//.*?$|/\*.*?\*/|\'(?:\\.|[^\\\'])*\'|"(?:\\.|[^\\"])*"',
        re.DOTALL | re.MULTILINE
    )
    return re.sub(pattern, replacer, text)


def check_syntax(code, parser):
    """
    功能：检查代码语法的正确性。
    说明：使用 pycparser 自带的 preprocess_file 函数，模拟 C 语言编译前的预处理阶段（宏展开等，cpp_args='-E'），
          然后再进行解析，如果能顺利生成 AST 则说明语法没有问题。
    """
    try:
        # 调用 C 语言的预处理器 gcc -E 处理代码
        preprocessed_code = preprocess_file(code, cpp_args='-E')
        # 解析预处理后的代码
        ast = parser.parse(preprocessed_code)
    except Exception as e:
        # 如果抛出异常，说明有语法错误
        print(e)
        print(preprocessed_code)
        return False
    return True


if __name__ == '__main__':
    """
    主程序逻辑：
    读取包含缺陷检测代码的 JSON 文件，将其清洗（去除注释）后，
    按照分类标签（缺陷类型）提取并保存成标准的文件夹树形结构（如 origin/0/1.c, origin/1/2.c）。
    这种树形结构是为了适配前面的 tokenize() 函数的读取习惯。
    """
    
    # 缺陷检测任务的数据集路径
    root = '../code_defect/data_raw/'
    
    # 加载包含所有源代码及标签的 JSON 文件 (这通常是 CodeChef 数据集转换过来的中间格式)
    with open(root + 'function.json', 'r') as f:
        data = json.load(f)

    import shutil

    # 如果已经存在 origin 文件夹，则将其递归删除，确保每次运行都是全新的数据集
    if os.path.exists(os.path.join(root, 'origin')):
        shutil.rmtree(os.path.join(root, 'origin'))
        
    # 重新创建存放原始分层代码的 origin 文件夹
    os.makedirs(os.path.join(root, 'origin'), exist_ok=True)

    # 遍历 JSON 文件中的每一条代码记录
    for index, item in enumerate(data):
        target = item['target'] # 获取代码的类别标签 (比如 0代表无缺陷OK，1代表运行时错误RE等)
        func = item['func']     # 获取具体的源代码字符串
        
        # 清理代码：移除多行注释 /* ... */
        func = re.sub(r'/\*.*?\*/', '', func, flags=re.DOTALL)
        # 清理代码：移除单行注释 // ...
        func = re.sub(r'//.*?\n', '\n', func)
        
        # 将标签转化为字符串，作为文件夹的名字
        directory = str(target)
        # 根据当前代码的类别，创建对应的子文件夹 (如果尚未创建的话)
        os.makedirs(os.path.join(root, 'origin', directory), exist_ok=True)
        
        # 为每段代码分配一个简单的递增数字文件名，例如 1.c, 2.c, 3.c...
        filename = f'{index + 1}.c'
        
        # 将清理干净的源代码写入对应的标签文件夹下
        with open(os.path.join(root, 'origin', directory, filename), 'w') as f:
            f.write(func)
            
    print('done')