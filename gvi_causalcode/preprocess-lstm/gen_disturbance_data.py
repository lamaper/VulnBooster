"""
description：生成用于破坏虚假相关性的代码扰动数据（干预样本）。
包含插入死代码（结构干预）和标识符替换（命名干预）两种策略。
这部分代码主要是离线预生成数据，用于形成对比基线或基础增强数据。
"""
import os
import random
import re
import shutil
from pycparser import c_parser
import random
import string


def find_insert_locations(code: str) -> list:
    """
    功能：通过正则表达式扫描 C 代码文本，寻找可以安全插入“死代码”的行列坐标。
    """
    dead_code_locations =[]

    # 策略 1：在大括号 `{` 后面紧跟换行符的地方寻找插入点
    for match in re.finditer(r'(\{[ \t\n]*\n)', code):
        # 计算当前位置所在行号和列号
        line_number = code.count('\n', 0, match.start())
        column_number = match.start() - code.rfind('\n', 0, match.start())
        # struct 过滤：如果在结构体 (struct) 内部插入普通语句会报语法错误，需要避开
        if not re.search(r'struct\s+\w+\s*\{[^}]*' + re.escape(code[match.start():match.end()]) + r'[^}]*\}\s*\w',
                         code):
            dead_code_locations.append((line_number, column_number))

    # 策略 2：在分号加右大括号 `;\n}` 或者 `; }` 的结构中寻找插入点
    for match in re.finditer(r'(\;[ \t]*\})', code):
        line_number = code.count('\n', 0, match.start())
        column_number = match.start() - code.rfind('\n', 0, match.start())
        dead_code_locations.append((line_number, column_number))

    # 策略 3：在特定 C 语言关键字紧跟左大括号 `{` 的地方寻找插入点
    keywords =['int', 'for', 'char', 'double', 'float', 'long', 'short', 'unsigned', 'signed', 'void', 'struct',
                'enum', 'if']
    for keyword in keywords:
        for match in re.finditer(r'(\{[ \t\n]*' + keyword + ')', code):
            line_number = code.count('\n', 0, match.start())
            column_number = match.start() - code.rfind('\n', 0, match.start())
            dead_code_locations.append((line_number, column_number))
            
    # struct 二次过滤：彻底剔除掉落在结构体定义 `struct {...};` 范围内的所有候选插入点
    # 注意：原代码此处使用了 c_code 变量，可能依赖外部同名变量。我们原样保留作者代码。
    for match in re.finditer(r'struct\s+\w+\s*\{[^}]*\}\s*;', c_code):
        start_line_number = c_code.count('\n', 0, match.start()) + 1
        end_line_number = c_code.count('\n', 0, match.end()) + 1
        dead_code_locations =[location for location in dead_code_locations if
                               not (start_line_number <= location[0] <= end_line_number)]
    return dead_code_locations

# 预先定义好的“死代码”片段集合（语义等价转换的载体）。
# 这些片段执行后不会改变程序任何状态，对应论文中控制“风格特征 F”且“语义特征 S”不变。
dead_code =[
    ";",
    "{ }",
    "printf ( \"\" ) ;",
    "if ( false ) ;",
    "if ( true ) { }",
    "if ( false ) ; else { }",
    "if ( 0 ) ;",
    "if ( false ) { int cnt = 0 ; for ( int i = 0 ; i < 123 ; i ++ ) cnt += 1 ; }"
    "for ( int i = 0 ; i < 100 ; i ++ ) break ;",
    "for ( int i = 0 ; i < 0 ; i ++ ) { }"
    "while ( false ) ;",
    "while ( 0 ) ;",
    "while ( true ) break ;",
    "for ( int i = 0 ; i < 10 ; i ++ ) { for ( int j = 0 ; j < 10 ; j ++ ) break ; break ; }",
    "do { } while ( false ) ;"]


def ins_dead_code(code_path, save_path):
    """
    功能：遍历给定目录下的所有C代码文件，随机插入死代码，并使用编译器级验证语法后保存。
    """
    count = 0
    parser = c_parser.CParser() # 使用 pycparser 进行抽象语法树验证，确保语法严格正确
    for root, dirs, files in os.walk(code_path):
        for file in files:
            relative_path = os.path.relpath(root, code_path)
            os.makedirs(os.path.join(save_path, relative_path), exist_ok=True)
            if os.path.exists(os.path.join(save_path, relative_path, file)):
                continue # 如果文件已处理过则跳过
            with open(os.path.join(root, file), 'r', encoding='utf-8') as f:
                c_code = f.read()
                
            insertion_points = find_insert_locations(c_code)
            c_code_lines = c_code.split('\n')

            if len(insertion_points) > 0:
                insertion_point = random.choice(insertion_points)
                dead_code_str = random.choice(dead_code)
                loop_count = 0
                # 再次规避在带有 struct 声明的相邻行插入死代码
                while 'struct' in c_code_lines[insertion_point[0] - 1] or 'struct' in c_code_lines[
                    insertion_point[0]]:
                    insertion_point = random.choice(insertion_points)
                    loop_count += 1
                    if loop_count > 15: # 如果尝试15次依然是死胡同，就放弃插入
                        break
                # 将代码根据确定的行号和列号切断，在中间嵌入挑好的死代码字符串
                line_number, column_number = insertion_point
                c_code_lines[line_number] = c_code_lines[line_number][
                                            :column_number] + '\n' + dead_code_str + '\n' + \
                                            c_code_lines[line_number][column_number:]

                c_code_with_dead_code = '\n'.join(c_code_lines)
                try:
                    # 关键防御：调用 C 语言解析器。如果插入破坏了原始语法，将抛出异常，就不会执行写入
                    parser.parse(c_code_with_dead_code)
                    with open(os.path.join(save_path, relative_path, file), 'w', encoding='utf-8') as f:
                        f.write(c_code_with_dead_code)

                except Exception as e:
                    # 被原作者注释掉的调试信息
                    # print(os.path.join(data_root, file))
                    # print(c_code)
                    # print(c_code_with_dead_code)
                    print(e)
            else:
                print(os.path.join(root, file)) # 找不到插入点就打印路径
                
            # 如果上面因为种种原因(没插入点或语法报错)没生成新文件，就直接把原文件复制过去
            if not os.path.exists(os.path.join(save_path, relative_path, file)):
                shutil.copy(os.path.join(root, file), os.path.join(save_path, relative_path, file))
                print(os.path.join(root, file))
                count += 1
    print(count)

# ================= 禁忌词表定义区 (不可用于替换) =================
# C 语言保留字/关键字
__key_words__ =["auto", "break", "case", "char", "const", "continue",
                 "default", "do", "double", "else", "enum", "extern",
                 "float", "for", "goto", "if", "inline", "int", "long",
                 "register", "restrict", "return", "short", "signed",
                 "sizeof", "static", "struct", "switch", "typedef",
                 "union", "unsigned", "void", "volatile", "while",
                 "_Alignas", "_Alignof", "_Atomic", "_Bool", "_Complex",
                 "_Generic", "_Imaginary", "_Noreturn", "_Static_assert",
                 "_Thread_local", "__func__"]
                 
# C 语言操作符
__ops__ =["...", ">>=", "<<=", "+=", "-=", "*=", "/=", "%=", "&=", "^=", "|=",
           ">>", "<<", "++", "--", "->", "&&", "||", "<=", ">=", "==", "!=", ";",
           "{", "<%", "}", "%>", ",", ":", "=", "(", ")", "[", "<:", "]", ":>",
           ".", "&", "!", "~", "-", "+", "*", "/", "%", "<", ">", "^", "|", "?"]
           
# C 语言常见标准库宏定义
__macros__ =["NULL", "_IOFBF", "_IOLBF", "BUFSIZ", "EOF", "FOPEN_MAX", "TMP_MAX",  # <stdio.h> macro
              "FILENAME_MAX", "L_tmpnam", "SEEK_CUR", "SEEK_END", "SEEK_SET",
              "NULL", "EXIT_FAILURE", "EXIT_SUCCESS", "RAND_MAX", "MB_CUR_MAX"]  # <stdlib.h> macro
              
# C 语言标准库函数名、库对象、以及某些数学和流标识符
__special_ids__ =["main",
                   "stdio", "cstdio", "stdio.h",  # <stdio.h> & <cstdio>
                   "size_t", "FILE", "fpos_t", "stdin", "stdout", "stderr",  # <stdio.h> types & streams
                   "remove", "rename", "tmpfile", "tmpnam", "fclose", "fflush",  # <stdio.h> functions
                   "fopen", "freopen", "setbuf", "setvbuf", "fprintf", "fscanf",
                   "printf", "scanf", "snprintf", "sprintf", "sscanf", "vprintf",
                   "vscanf", "vsnprintf", "vsprintf", "vsscanf", "fgetc", "fgets",
                   "fputc", "getc", "getchar", "putc", "putchar", "puts", "ungetc",
                   "fread", "fwrite", "fgetpos", "fseek", "fsetpos", "ftell",
                   "rewind", "clearerr", "feof", "ferror", "perror", "getline"
                                                                     "stdlib", "cstdlib", "stdlib.h",

                   "size_t", "div_t", "ldiv_t", "lldiv_t",  # <stdlib.h> types
                   "atof", "atoi", "atol", "atoll", "strtod", "strtof", "strtold",  # <stdlib.h> functions
                   "strtol", "strtoll", "strtoul", "strtoull", "rand", "srand",
                   "aligned_alloc", "calloc", "malloc", "realloc", "free", "abort",
                   "atexit", "exit", "at_quick_exit", "_Exit", "getenv",
                   "quick_exit", "system", "bsearch", "qsort", "abs", "labs",
                   "llabs", "div", "ldiv", "lldiv", "mblen", "mbtowc", "wctomb",
                   "mbstowcs", "wcstombs",
                   "string", "cstring", "string.h",  # <string.h> & <cstring>
                   "memcpy", "memmove", "memchr", "memcmp", "memset", "strcat",  # <string.h> functions
                   "strncat", "strchr", "strrchr", "strcmp", "strncmp", "strcoll",
                   "strcpy", "strncpy", "strerror", "strlen", "strspn", "strcspn",
                   "strpbrk", "strstr", "strtok", "strxfrm",
                   "memccpy", "mempcpy", "strcat_s", "strcpy_s", "strdup",
                   # <string.h> extension functions
                   "strerror_r", "strlcat", "strlcpy", "strsignal", "strtok_r",
                   "iostream", "istream", "ostream", "fstream", "sstream",  # <iostream> family
                   "iomanip", "iosfwd",
                   "ios", "wios", "streamoff", "streampos", "wstreampos",  # <iostream> types
                   "streamsize", "cout", "cerr", "clog", "cin",
                   "boolalpha", "noboolalpha", "skipws", "noskipws", "showbase",  # <iostream> manipulators
                   "noshowbase", "showpoint", "noshowpoint", "showpos",
                   "noshowpos", "unitbuf", "nounitbuf", "uppercase", "nouppercase",
                   "left", "right", "internal", "dec", "oct", "hex", "fixed",
                   "scientific", "hexfloat", "defaultfloat", "width", "fill",
                   "precision", "endl", "ends", "flush", "ws", "showpoint",
                   "sin", "cos", "tan", "asin", "acos", "atan", "atan2", "sinh",  # <math.h> functions
                   "cosh", "tanh", "exp", "sqrt", "log", "log10", "pow", "powf",
                   "ceil", "floor", "abs", "fabs", "cabs", "frexp", "ldexp",
                   "modf", "fmod", "hypot", "ldexp", "poly", "matherr", 'u', 'U', 'UU', 'uU', 'Uu']
# 最终的禁忌词汇总
forbidden_uid = __key_words__ + __ops__ + __macros__ + __special_ids__
# ================= 禁忌词表定义区结束 =================

import re

def find_replaceable_names(code: str) -> list:
    """
    功能：提取所有的开发者自定义变量/函数标识符。
    """
    # 剔除代码中出现的所有双引号包裹的字符串字面量
    code = re.sub(r'"[^"\\]*(?:\\.[^"\\]*)*"', '', code)
    # 剔除代码中出现的所有单引号包裹的字符字面量
    code = re.sub(r"'[^'\\]*(?:\\.[^'\\]*)*'", '', code)
    
    # 使用正则表达式匹配合法的 C 语言标识符
    pattern = r'(?<![\w\\%])[_a-zA-Z][_a-zA-Z0-9]*(?![\w\\%])'
    # 提取代码中匹配的所有文本片段 findall 
    names = re.findall(pattern, code)
    
    # 利用预先定义好的禁忌词表过滤，避免错误替换语言内置结构、关键字、库函数
    names =[name for name in names if name not in forbidden_uid]
    
    # 转化为集合以去重，随后变回列表
    names = list(set(names))
    return names


def change_token(old_name, new_name, code):
    """
    功能：进行精准的单词替换
    """
    # 必须使用 \b 单词边界，防止将例如 id 替换成了 token0，导致原有的 width 被错误替换成 wtoken0th
    pattern = r'\b{}\b'.format(old_name)
    new_code = re.sub(pattern, new_name, code)
    return new_code


def generate_random_tokens(names: list) -> dict:
    """
    功能：生成等长度乱码变量名，模拟混淆代码时的对抗样本风格。
    """
    tokens = {}
    used_tokens = set()
    for name in names:
        # 长度上下浮动 1 个字符，最小为 1
        min_len = max(1, len(name) - 1)
        max_len = len(name) + 1
        
        while True:
            token_len = random.randint(min_len, max_len)
            # 保证合法的变量首字母只能是字母或下划线
            first_char = random.choice(string.ascii_letters + '_')
            # 剩下的字符还可以包含数字
            other_chars = ''.join(random.choices(string.ascii_letters + string.digits + '_', k=token_len - 1))
            token = first_char + other_chars
            # 如果没撞禁忌词、没撞原名、也没有被别人占用过，就算合法
            if token not in forbidden_uid and token not in names and token not in used_tokens:
                break
        
        # 映射保存新 token
        tokens[name] = token
        used_tokens.add(token)
    return tokens


def generate_format_token(names: list) -> dict:
    """
    功能：格式化命名，统一把变量抹平为 token0, token1...
    说明：在构建 CausalCode 基线对比（去除虚假风格 F）时非常有效。
    """
    tokens = {}
    for i, name in enumerate(names):
        tokens[name] = 'token' + str(i)
    return tokens


if __name__ == '__main__':
    """
    主程序执行逻辑：读取一批代码，扫描所有自定义标识符，进行 `tokenX` 替换后，写出新文件。
    """
    code_path = r'../data_raw/origin'           # 原始代码所在目录
    save_path = r'../data_raw/token_format'  # 替换后代码保存目录 token_dis
    os.makedirs(save_path, exist_ok=True)
    parser = c_parser.CParser()
    error_count = 0
    
    for root, dirs, files in os.walk(code_path):
        for file in files:
            relative_path = os.path.relpath(root, code_path)
            os.makedirs(os.path.join(save_path, relative_path), exist_ok=True)
            with open(os.path.join(root, file), 'r') as f:
                c_code = f.read()
                
            # 找到可以替换的变量名
            or_names = find_replaceable_names(c_code)
            # 生成格式化的字典
            chang_tokens = generate_format_token(or_names)
            
            # 针对找出来的词汇，逐个替换
            for or_name in or_names:
                changed_code = change_token(or_name, chang_tokens[or_name], c_code)
                try:
                    # 每次替换都过一次抽象语法树（AST）验证，如果报错进 except
                    parser.parse(changed_code)
                    c_code = changed_code # 验证通过，生效
                except Exception as e:
                    error_count += 1
                    print(os.path.join(root, file))
                    print(c_code)
                    print(changed_code)
                    print(e)
                    
            # 覆盖或新建文件写入最后成果
            with open(os.path.join(save_path, relative_path, file), 'w') as f:
                f.write(c_code)
    print('error_count:', error_count)