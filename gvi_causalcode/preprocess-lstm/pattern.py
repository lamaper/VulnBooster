# -*- coding: utf-8 -*-

import re
import pickle, gzip

INDENT = "  " # 定义可视化输出时的标准缩进空格


def extractStr(tokens):
    """
    功能：提取并隐藏代码序列中的字符串/字符字面量。
    机制：遍历 Token 序列，把带有单双引号的词替换为临时占位符（如 <_str0_>, <_str1_>）。
    目的：防止字符串内部的伪代码（如包含 "{" 或 "if" 的字符串）干扰后续 AST 状态机的括号匹配。
    返回：替换后的 tokens 列表，以及占位符与原字符串的双向映射字典。
    """
    mask2token, token2mask = {}, {}
    result =[]
    cnt = 0
    for token in tokens:
        # 如果 token 中包含单引号或双引号（说明是字符或字符串）
        if "'" in token or '"' in token:
            # 如果这个字符串还没被映射过
            if token2mask.get(token) == None:
                mask = "<_str%d_>" % cnt   # 生成一个独特的掩码，例如 <_str0_>
                token2mask[token] = mask   # 记录正向映射：字符串 -> 掩码
                mask2token[mask] = token   # 记录反向映射：掩码 -> 字符串
                cnt += 1
            # 将生成的或已有的掩码加入结果列表
            result.append(token2mask[token])
        else:
            # 不是字符串，原样保留
            result.append(token)
    return result, token2mask, mask2token


def recoverStr(tokens, mask2token):
    """
    功能：结构分析完毕后，将之前替换的占位符（<_str0_> 等）安全地还原为原始的字符串字面量。
    """
    result =[]
    for token in tokens:
        # 如果遇到以 "<_str" 开头的 token，说明是掩码
        if token.startswith("<_str"):
            result.append(mask2token[token]) # 查表还原回原始字符串
        else:
            result.append(token)
    return result


def _go4next(tokens, token, curIdx):
    """
    功能：向后探测。从当前索引 curIdx 开始，向后寻找指定的 token（例如寻找下一个分号 ";"）。
    返回：目标 token 所在的索引位置。如果一直找到底都没找到，则返回 -1。
    """
    n = len(tokens)
    while curIdx < n and tokens[curIdx] != token:
        curIdx += 1
    if curIdx == n:
        return -1
    else:
        return curIdx


def _go4match(tokens, startToken, curIdx):
    endToken = ""
    if startToken == "(":
        endToken = ")"
    elif startToken == "[":
        endToken = "]"
    elif startToken == "{":
        endToken = "}"
    else:
        assert False

    indent = 0
    n = len(tokens)
    
    # 记录初始位置防死循环
    start_idx = curIdx 
    
    while curIdx < n:
        if tokens[curIdx] == startToken:
            indent += 1
        elif tokens[curIdx] == endToken:
            indent -= 1
            if indent == 0:
                break
        curIdx += 1
        
    # 【修复】：如果一直找到结尾也没找到匹配的括号，
    # 不要返回 -1，而是强行返回当前索引的下一个位置，逼迫解析器继续前进，防止卡死
    if curIdx == n:
        return min(start_idx + 1, n)
    else:
        return curIdx

def _tokens2stmts(tokens, level=0):
    le_paren = 0
    idx = 0
    n = len(tokens)
    res = ""
    res += INDENT * level
    inAssign = False
    
    # 增加一个最大迭代保护，防止任何意外的死循环
    max_iters = n * 5 
    iters = 0

    while idx < n and iters < max_iters:
        iters += 1
        t = tokens[idx]
        res += t + " "
        
        if t == "(":
            le_paren += 1
        elif t == ")":
            le_paren -= 1
            if le_paren <= 0:  # 修复：防止残缺右括号导致负数
                le_paren = 0
                inAssign = False
        elif t == ";" and le_paren == 0:
            res += "\n"
            if idx != n - 1:
                res += INDENT * level
            inAssign = False
        elif t in [";", ",", ":", "?"]:
            inAssign = False
        elif t == "{" and not inAssign:
            startIdx = idx + 1
            endIdx = _go4match(tokens, "{", idx)
            
            # 【修复】：如果 _go4match 失败或者返回的原地踏步，强制推进
            if endIdx <= idx:
                endIdx = idx + 1
                
            res += "\n"
            res += _tokens2stmts(tokens[startIdx: endIdx], level + 1)
            res += "\n"
            if endIdx < n: # 修复边界
                res += INDENT * level
            idx = endIdx - 1 # 外面有 idx+=1，这里要减一
            
        elif t == "{" and inAssign:
            idx += 1
            found_semi = False
            while idx < n:
                res += tokens[idx] + " "
                if tokens[idx] == ";":
                    res += "\n"
                    if idx != n - 1:
                        res += INDENT * level
                    inAssign = False
                    found_semi = True
                    break
                idx += 1
            
            # 【修复】：如果在赋值的大括号里走到结尾都没找到分号，
            # 必须强制解除赋值状态，否则外层会卡死
            if not found_semi:
                inAssign = False
                continue # 不要执行下面的 idx+=1 了，因为已经到尽头了
                
        elif t in ["=", "enum"]:
            inAssign = True
            
        idx += 1
        
    return res


def _getIndent(str_):
    """
    功能：获取某行字符串前面的缩进（提取开头连续的空格或 Tab）。
    用于后续推断这行代码属于哪一层级。
    """
    res = ""
    for ch in str_:
        if ch in["\t", " "]:
            res += ch
        else:
            break
    return res


# return: (stmts, StmtInsPos)
#   stmts: a list of statements, where variable declaration can be inserted following
#   StmtInsPos: a list of indices, indicating which statments can be seen as statement insertion positions
def tokens2stmts(tokens):
    """
    功能：这是一个上层封装接口，统筹调用前面写的工具，最终产出“干净的语句列表”和“合法的插入点”。
    """
    # 1. 隐藏代码中的字符串字面量（用掩码代替，防止字符串里的分号和大括号捣乱）
    tokens, token2mask, mask2token = extractStr(tokens)
    
    # 2. 调用核心状态机，将一维 tokens 转化为带有 `\n` 分隔、带有正确缩进的长文本
    tokens = _tokens2stmts(tokens)
    
    # 3. 按 `\n` 切分为语句列表，并过滤掉空行
    stmts = tokens.split("\n")
    stmts =["" if stmt.strip() == "" else stmt for stmt in stmts]

    # 4. 修复机制：Add temporary omitted "}" with corresponding indentation
    # 有时候因为递归和解析的边界问题，某些代码块的右大括号 `}` 会被漏掉，这里利用栈（Stack）来补齐。
    statStack = []
    newStmts =[]
    for stmt in stmts:
        if stmt != "":
            newStmts.append(stmt)
            # 如果某行以 `{` 结尾，说明开启了新区块，入栈
            if stmt.rstrip().endswith("{"):
                statStack.append(stmt)
        # 如果遇到空行，且栈里有未闭合的块，强制补齐一个带着正确缩进的 `}`
        elif len(statStack) != 0:
            matchStmt = statStack.pop()
            newStmts.append(_getIndent(matchStmt) + "}")
        else:
            pass
            # newStmts.append("}")

    '''
    5. 结构体定义修复机制：
    C 语言允许这样定义结构体并紧接着声明变量：
    struct a {              struct a {
        int i;                  int i;
        double j;   ==>         double j;
    }                       } c, d, e;
    c, d, e;
    状态机会把 `c, d, e;` 拆成新的一行，但这在逻辑上其实和上面的 `}` 是连在一起的一条语句。这里将它们强行合并。
    '''
    # 正则表达式：匹配类似 `a, b[10];` 这样的变量声明模式
    pattern_uid = r"[A-Za-z_][A-Za-z0-9_]*(\[[0-9]*\])*"
    pattern = r"^({},\s*)*{};".format(pattern_uid, pattern_uid)
    stmts =[]
    blockStack =[]
    endStruct = False  # 标记是否刚刚闭合了一个 struct 或 union
    
    for stmt in newStmts:
        if stmt.rstrip().endswith("{"):
            stmts.append(stmt)
            blockStack.append(stmt)
            
        elif stmt.strip() == "}":
            stmts.append(stmt)
            # 【修复】：增加栈非空校验，防止遇到残缺的右大括号导致崩溃
            if len(blockStack) > 0:
                if blockStack[-1].lstrip().startswith("struct") or \
                        blockStack[-1].lstrip().startswith("union") or \
                        blockStack[-1].lstrip().startswith("typedef"):
                    endStruct = True
                blockStack.pop()
            
        elif endStruct:
            # 如果结构体刚结束，且紧跟的这行只包含分号，或者是变量名声明，则把它合并到上一行末尾
            if stmt.strip() == ";" or re.match(pattern, stmt.replace(" ", "")):
                stmts[-1] = stmts[-1] + " " + stmt
            else:
                stmts.append(stmt)
            endStruct = False # 重置标记
        else:
            stmts.append(stmt)

    # ================= 极其关键：寻找死代码合法插入点 =================
    paren_n = 0
    StmtInsPos =[]
    structStack =[]
    
    for i, stmt in enumerate(stmts):
        # 跟踪当前所在的代码块深度和类型
        if stmt.rstrip().endswith("{"):
            paren_n += 1
            # 记录是否进入了结构体/联合体内部
            if stmt.lstrip().startswith("struct") or stmt.lstrip().startswith("union"):
                structStack.append((stmt, paren_n))
                
        elif stmt.lstrip().startswith("}"):
            # 如果离开了对应的层级，将结构体标记出栈
            if structStack != [] and paren_n == structStack[-1][1]:
                structStack.pop()
            paren_n -= 1
            
        # 【核心判断】：如果当前所在区域不是空列表，即 *当前没有处在任何 struct 或 union 定义的内部*
        # 那么，这一条语句的末尾，就是一个合法的死代码插入点！
        # （因为在结构体内部插入普通的执行语句如 `a=1;` 会导致编译报错，必须避开）
        if structStack ==[]:
            StmtInsPos.append(i)

    # 6. 收尾工作：记录下每一行的缩进值，并把被掩码遮盖的字符串还原回来
    indents =[_getIndent(stmt) for stmt in stmts]
    stmts =[recoverStr(stmt.strip().split(), mask2token) for stmt in stmts]

    # 返回最终结果：
    # stmts: [['int', 'main', '(', ')', '{'], ['int', 'a', ';'], ... ] (切分好的语句列表)
    # StmtInsPos: [0, 1, 3, ...] (可以插死代码的 stmts 数组索引集合)
    # indents: ["", "  ", "    ", ...] (方便可视化的缩进)
    return stmts, StmtInsPos, indents

def StmtInsPos(tokens, strict=True):
    '''
    Find all possible positions to insert any statements
    功能：计算出所有的“普通语句”插入点。返回的是在一维 Token 列表中的绝对索引坐标。
    参数：
      tokens: 一维的 token 字符串列表
      strict: 是否开启严格模式。严格模式下会过滤掉一些虽然不报错但位置尴尬（比如 if 刚开头）的插入点。
    返回：
      res: [int] 插入点的绝对 Token 下标列表
    '''
    # 调用第二部分的核心函数，拿到语句列表和语句级别的插入索引
    statements, StmtInsPos, _ = tokens2stmts(tokens)
    res =[]
    cnt, indent = 0, 0
    
    # -1 代表在所有代码的最开头插入（如果是宽松模式允许开头插入）
    if not strict:
        res.append(-1)
        
    # 遍历每一行语句
    for i, stmt in enumerate(statements):
        # 累加当前行包含的 Token 数量，用于计算绝对一维下标
        cnt += len(stmt)
        
        # 维护一个简单的当前缩进/括号深度
        if stmt[-1] == "}":
            indent -= 1
        elif stmt[-1] == "{" and stmt[0] not in["struct", "union", "enum", "typedef"]:
            indent += 1
            
        # 如果当前这行 i 被前面的核心函数判定为“安全” (在 StmtInsPos 中)
        if i in StmtInsPos:
            if not strict:
                # 宽松模式下，只要安全就在这行的最后一个 Token 后面插入
                res.append(cnt - 1)
            # 严格模式下的额外防御：
            # 1. 当前行不能是右括号 `}` (防破坏结构闭合)
            # 2. 必须处于至少一层代码块内部 (indent != 0)
            # 3. 当前行不能是 if 或 else 的单行开头 (如果在 else 后面马上插死代码，会把后面的原代码顶出控制流)
            # 4. 不能是只有 if 没有括号的 for 循环特例
            elif stmt[-1] != "}" and \
                    indent != 0 and \
                    stmt[0] not in ['else', 'if'] and \
                    not (stmt[0] == 'for' and 'if' in stmt):
                res.append(cnt - 1)
    return res


def DeclInsPos(tokens):
    '''
    Find all possible positions to insert variable declarations
    功能：寻找可以插入变量声明（Declarations，如 int xxx;）的位置坐标。
    说明：变量声明的限制比执行语句要宽泛得多。一般只要是个完整的语句结束，就可以声明变量。
    '''
    statements, _, _ = tokens2stmts(tokens)
    res =[]
    cnt = 0
    # 永远允许在代码文件的最开头 (-1) 声明全局变量
    res.append(-1)
    
    # 遍历每一句话，直接把每句话结束的位置作为可插入点
    for stmt in statements:
        cnt += len(stmt)
        res.append(cnt - 1)
    return res


# =========================================================================
# 以下三个函数只是 StmtInsPos 的别名封装，便于在顶层按语义分类调用。
# 它们其实找的安全位置都是一样的（普通语句能插的地方，分支/循环也能插）
# =========================================================================

def BrchInsPos(tokens):
    '''寻找可以插入死分支 (如 if(false) {...}) 的位置'''
    return StmtInsPos(tokens)

def LoopInsPos(tokens):
    '''寻找可以插入无副作用循环代码的位置'''
    return StmtInsPos(tokens)

def FuncInsPos(tokens):
    '''寻找可以插入空函数的位置'''
    return StmtInsPos(tokens)


def _InsVis(tokens, pos):
    """
    功能：终端可视化工具。打印出带缩进格式的代码，
          并在所有传进来的可插入位置 `pos` 的后面打上 "[____]" 的标记，方便肉眼 debug。
    """
    statements, _, indents = tokens2stmts(tokens)
    lens =[len(line) for line in statements]

    for pidx in pos:
        # 如果是在开头插入
        if pidx == -1:
            statements[0] = ["[____]"] + statements[0]
            continue
            
        # 根据绝对索引坐标 pidx，找到对应是哪一行
        cnt = 0
        for i, n in enumerate(lens):
            cnt += n
            if cnt > pidx:
                # 在对应行的末尾追加标记
                statements[i].append("[____]")
                break

    # 打印结果
    for indent, line in zip(indents, statements):
        print(indent, end="")
        print(" ".join(line))


# =========================================================================
# 以下四个函数是提供给 modifier.py 里的 `InsModifier` 类操作状态的底层 API。
# 为了在张量操作时实现“随时插入”和“随时撤销”，系统维护了一个 insertDict 字典：
# 格式为：{ 绝对位置索引: [[插入的Token序列1], [插入序列2]], "count": 总插入次数 }
# =========================================================================

# return [pos1, pos2, ...]
def InsAddCandidates(insertDict, maxLen=None):
    """
    功能：获取当前允许插入的“候选坐标”。
    说明：过滤掉专门记录数量的 "count" 字段，如果指定了最大长度 maxLen，则过滤掉越界的坐标。
    """
    res =[]
    for pos in insertDict.keys():
        if pos == "count":
            continue
        if maxLen is None:
            res.append(pos)
        elif int(pos) < maxLen:
            res.append(pos)
    return res


# only able to insert into legal poses, and can't insert same inserted content into same pos (return False)
def InsAdd(insertDict, pos, insertedTokenList):
    """
    功能：在字典中记录一次插入动作。
    说明：防止在同一个位置连续插入两段一模一样的死代码。
    """
    suc = True
    assert insertDict.get(pos) is not None  # 确保这个位置在字典键里（是合法的可插入点）
    
    # 去重判定
    if insertedTokenList in insertDict[pos]:  # can't insert same statement
        suc = False
    else:
        # 在该位置的列表中挂上这段新死代码的 Token 流
        insertDict[pos].append(insertedTokenList)

    # 成功插入则全局计数器 +1
    if suc:
        if insertDict.get("count") is not None:
            insertDict["count"] += 1
        else:
            insertDict["count"] = 1
    return suc


# return[(pos1, 0), (pos1, 1), (pos2, 0), ...]
def InsDeleteCandidates(insertDict):
    """
    功能：获取当前所有【已经被插入过死代码】的具体位置及其在列表中的次序，作为可撤销的候选。
    返回：元组列表，例如在位置 10 插入了 2 段代码，会返回 [(10, 0), (10, 1)]。
    """
    res =[]
    for key in insertDict.keys():
        if key == "count":
            continue
        # 如果该位置的插入列表不为空
        if insertDict[key] !=[]:
            # 遍历挂在这个位置上的所有死代码片段
            for i, _ in enumerate(insertDict[key]):
                res.append((key, i))
    return res


# what is passed in must is legal (pos, listIdx)
def InsDelete(insertDict, pos, listIdx=0):
    """
    功能：撤销某次指定的插入动作（删除记录）。
    """
    assert insertDict.get(pos) is not None
    assert insertDict[pos] !=[]
    if len(insertDict[pos]) <= listIdx:
        assert False
        
    # 从列表中删除那段死代码序列
    del insertDict[pos][listIdx]
    assert insertDict.get("count") is not None
    
    # 计数器 -1
    insertDict["count"] -= 1


# return complete tokenlist by inserting corresponding token list (insertions)
def InsResult(tokens, insertDict):
    """
    功能：这是 CausalCode 【极速生成对抗/干预序列】的秘密武器！
    说明：它不再去修改真实的 C 语言字符串文本，而是直接对一维的 Token 张量/列表进行快速穿插重组。
          将原本的代码 Token 序列和 insertDict 中记录好的死代码 Token 序列拼成一条全新的一维数组。
    返回：包含了原始代码和死代码的全新一维 Token 列表。
    """
    result =[]
    
    # 优先处理插在最开头位置 (-1) 的死代码
    if insertDict.get(-1) is not None:
        for tokenList in insertDict[-1]:
            result += tokenList
            
    # 遍历原代码的每一个 Token
    for i, t in enumerate(tokens):
        # 先把原代码的这个 Token 加进来
        result.append(t)
        
        # 检查当前位置之后，是不是挂着一段或多段死代码
        if insertDict.get(i) is not None:  # so it's a legal insertion position
            for tokenList in insertDict[i]:
                # 如果有，顺势将死代码 Token 紧跟其后拼进去
                result += tokenList
                
    return result

# =================== 高级语义等价转换：语句块重构 (Refactoring) ===================

# Usage: for each token in <tokens>, find "end token" that indicating where the corresponding statement ends.
#   tokens: token list
#   optimize: optimize level
#       0 => Label index of statement end token within single line.                         E.g. "for(...) sum++;" => index of ";"
#       1 => Label index of recurrent statement block end token (including "switch").       E.g. "while() {}"、"do {} while ();"、"for() {}"
#       2 => Label index of if-else statement block end token.                              E.g. "if() {} else if() {} else xxx;" => ";"
#       3 => Label index of other open statement "block" end token.                         E.g. "int() {}" => "}"       "enum { 1, 5, a }" => "}"
# Return: <list<int>> of index of end tokens
def getStmtEnd(tokens, optimize=3):
    """
    功能：为代码中的【每一个 token】打上标签，指出这个 token 所属的控制流/语句块的“结尾 Token 索引”在哪里。
    目的：这是进行 if-else、for-while 等复杂块级替换的基础。因为你要替换一个块，必须先精确知道这个块管辖的代码到哪里结束。
    """
    statements, _, indents = tokens2stmts(tokens)
    heads = [stmt[0] for stmt in statements] # 每一行的开头 Token (如 if, for, while)
    ends = [stmt[-1] for stmt in statements] # 每一行的结尾 Token (如 ;, {, })
    lens = [len(stmt) for stmt in statements]# 每一行的长度
    n = len(ends)
    endIndices =[]

    # 第 0 级解析 (optimize=0): 寻找单行语句的结尾位置 (主要找分号)
    totalCnt = 0
    for i, (head, end, cnt, indent) in enumerate(zip(heads, ends, lens, indents)):
        totalCnt += cnt
        if end == ";":
            if i == n - 1:
                endIndices.append(totalCnt - 1)
            elif head not in["for", "while", "do", "if", "else", "switch"]:
                endIndices.append(totalCnt - 1)
            elif head in ["for", "while", "switch", "do"]:
                endIndices.append(totalCnt - 1)
            elif heads[i + 1] != "else":
                endIndices.append(totalCnt - 1)
            else:
                endIndices.append(None)
        elif end == "}":
            if i == n - 1:
                endIndices.append(totalCnt - 1)
            elif len(indents[i + 1]) < len(indent):
                endIndices.append(totalCnt - 1)
            elif heads[i + 1] != "else" and heads[i + 1] != "while":
                endIndices.append(totalCnt - 1)
            else:
                endIndices.append(None)
        else:
            endIndices.append(None)
    if optimize <= 0:
        return endIndices

    # 第 1 级解析 (optimize=1): 查找 for / while / switch 等循环/分支块的结尾
    totalCnt = 0
    for i, (head, end, cnt, indent) in enumerate(zip(heads, ends, lens, indents)):
        totalCnt += cnt
        if endIndices[i] != None:
            continue
        if head not in ["for", "while", "switch"]:
            continue
        if end == "{":
            curIdx = i + 1
            # 利用缩进判断代码块的范围，跳过所有比当前缩进深的行
            while curIdx < n and len(indents[curIdx]) > len(indent):
                curIdx += 1
            assert curIdx < n and heads[curIdx] == "}", "[%d]%s" % (curIdx, heads[curIdx])
            endIndices[i] = endIndices[curIdx] # 找到了块的结尾
            
    # 单独处理 do-while 循环
    for i, (head, end, cnt, indent) in enumerate(zip(heads, ends, lens, indents)):
        totalCnt += cnt
        if endIndices[i] != None:
            continue
        if head not in ["do"]:
            continue
        if end == "{":
            curIdx = i + 1
            while curIdx < n and len(indents[curIdx]) > len(indent):
                curIdx += 1
            assert curIdx < n and heads[curIdx] == "}", "[%d]%s" % (curIdx, heads[curIdx])
            curIdx += 1
            # do-while 结尾是大括号后跟 while 和分号
            while curIdx < n and not (indents[curIdx] == indent and heads[curIdx] == "while" and ends[curIdx] == ";"):
                curIdx += 1
            assert curIdx < n and heads[curIdx] == "while", "[%d]%s" % (curIdx, heads[curIdx])
            endIndices[i] = endIndices[curIdx]
    if optimize <= 1:
        return endIndices

    # 第 2 级解析 (optimize=2): 查找 if-else 块的结尾
    totalCnt = 0
    for i, (head, end, cnt, indent) in enumerate(zip(heads, ends, lens, indents)):
        totalCnt += cnt
        if endIndices[i] != None:
            continue
        if head not in["if", "else"]:
            continue
        curTotalCnt = totalCnt
        curIdx = i
        while True:
            curIdx += 1
            while curIdx < n and len(indents[curIdx]) > len(indent):
                curTotalCnt += lens[curIdx]
                curIdx += 1
            assert curIdx < n  # 所有的单行 if/else 已经在第 0 级被处理完了
            if endIndices[curIdx] != None:
                endIndices[i] = endIndices[curIdx]
                break
                
    for i, (head, end, cnt, indent) in enumerate(zip(heads, ends, lens, indents)):
        totalCnt += cnt
        if endIndices[i] != None:
            continue
        # 处理 "} else" 连写的情况
        if not (head == "}" and i + 1 < n and heads[i + 1] == "else"):
            continue
        endIndices[i] = endIndices[i + 1]
    if optimize <= 2:
        return endIndices

    # 第 3 级解析 (optimize=3): 查找其他的开放语句块 (如函数定义 int main() {} 或枚举 enum {})
    totalCnt = 0
    for i, (head, end, cnt, indent) in enumerate(zip(heads, ends, lens, indents)):
        totalCnt += cnt
        if endIndices[i] != None:
            continue
        if end == "{":
            curIdx = i + 1
            while curIdx < n and len(indents[curIdx]) > len(indent):
                curIdx += 1
            assert curIdx < n and heads[curIdx] == "}", "[%d]%s" % (curIdx, heads[curIdx])
            endIndices[i] = endIndices[curIdx]

    # 最后，将每一行算出的结尾索引，展开并赋给这一行里面的每一个 Token
    res =[]
    for cnt, endIdx in zip(lens, endIndices):
        res += [endIdx] * cnt
    return res


# =======================================================================
# 干预组 1：对 if-else 控制流进行翻转干预 (保持语义等价)
# =======================================================================

def IfElseReplacePos(tokens, endPoses):
    """寻找可以执行 `if-else` 反转替换的合法位置。"""
    pos =[]
    n = len(tokens)
    for i, t in enumerate(tokens):
        if t == "if":  # 只处理单纯的 "if {} else {}" ，不处理 "else if {}" 这种链式结构
            ifIdx = i
            conditionEndIdx = _go4match(tokens, "(", ifIdx)
            if tokens[conditionEndIdx + 1] == "{":
                ifBlockEndIdx = _go4match(tokens, "{", conditionEndIdx + 1)
            else:
                ifBlockEndIdx = _go4next(tokens, ";", conditionEndIdx + 1)
            if not (ifBlockEndIdx + 1 < n and tokens[ifBlockEndIdx + 1] == "else"):
                continue
            if tokens[ifBlockEndIdx + 2] == "if":  # in case of "else if {}"
                continue
            elseBlockEndIdx = endPoses[ifBlockEndIdx + 1]
            pos.append([ifIdx, conditionEndIdx, ifBlockEndIdx, elseBlockEndIdx])
    return pos

def IfElseReplace(tokens, pos):
    """
    【干预操作】：执行 if-else 反转（语义保留变换）
    将：if (a) { A } else { B }  ====> 变成：if (! (a) ) { B } else { A }
    """
    beforeIf = tokens[:pos[0]]
    codition = tokens[pos[0] + 2:pos[1]]
    
    # 提取 if 里面的代码块 A
    if tokens[pos[1] + 1] == "{":
        blockIf = tokens[pos[1] + 2:pos[2]]
    else:
        blockIf = tokens[pos[1] + 1:pos[2] + 1]
        
    # 提取 else 里面的代码块 B
    if tokens[pos[2] + 2] == "{":
        blockElse = tokens[pos[2] + 3:pos[3]]
    else:
        blockElse = tokens[pos[2] + 2:pos[3] + 1]
    afterElse = tokens[pos[3] + 1:]
    
    # 重新组装！在条件前面加逻辑非 "!"，并且互换 blockElse 和 blockIf 的位置
    res = beforeIf + ["if", "(", "!", "("] + codition +[")", ")", "{"] + blockElse + ["}", "else", "{"] + blockIf + ["}"] + afterElse
    return res


def IfReplacePos(tokens, endPoses):
    """寻找独立的单 `if` 语句（后面不带 else 的）的位置"""
    pos =[]
    n = len(tokens)
    for i, t in enumerate(tokens):
        if t == "if":
            ifIdx = i
            conditionEndIdx = _go4match(tokens, "(", ifIdx)
            if tokens[conditionEndIdx + 1] == "{":
                ifBlockEndIdx = _go4match(tokens, "{", conditionEndIdx + 1)
            else:
                ifBlockEndIdx = _go4next(tokens, ";", conditionEndIdx + 1)
            if ifBlockEndIdx + 1 < n and tokens[ifBlockEndIdx + 1] == "else":  # in case of "if {} else {}", only process "if {} xxx"
                continue
            pos.append([ifIdx, conditionEndIdx, ifBlockEndIdx])
    return pos

def IfReplace(tokens, pos):
    """
    【干预操作】：将独立的 if 变成 if-else 结构（语义保留变换）
    将：if (a) { A }  ====> 变成：if (! (a) ) ; else { A }
    """
    beforeIf = tokens[:pos[0]]
    condition = tokens[pos[0] + 2:pos[1]]
    if tokens[pos[1] + 1] == "{":
        body = tokens[pos[1] + 2:pos[2]]
    else:
        body = tokens[pos[1] + 1:pos[2] + 1]
    afterIf = tokens[pos[2] + 1:]
    
    # 组装：加入空语句分号 ";"，把原来的执行体丢进 else 里
    res = beforeIf +["if", "(", "!", "("] + condition + [")", ")", ";", "else", "{"] + body +["}"] + afterIf
    return res

# =======================================================================
# 干预组 2：对 for/while 循环控制流进行翻转干预 (保持语义等价)
# =======================================================================

def For2WhileReplacePos(tokens, endPoses):
    """寻找 `for` 循环语句的位置及其关键组件的边界索引"""
    pos =[]
    for i, t in enumerate(tokens):
        if t == "for":
            forIdx = i
            # 找到 for 循环条件部分的右括号 `)` 位置
            conditionEndIdx = _go4match(tokens, "(", forIdx)
            
            # 确定 for 循环体的结尾位置
            if tokens[conditionEndIdx + 1] == "{":
                blockForEndIdx = _go4match(tokens, "{", conditionEndIdx)
            else:
                # 如果没有大括号（单行循环），利用之前算好的 endPoses 找到这句单行代码在哪结束
                blockForEndIdx = endPoses[conditionEndIdx + 1]
                
            # 在 for(A; B; C) 中找到两处分号的位置，用来切分条件 A、B、C
            condition1EndIdx = _go4next(tokens, ";", forIdx)
            condition2EndIdx = _go4next(tokens, ";", condition1EndIdx + 1)
            
            pos.append([forIdx, condition1EndIdx, condition2EndIdx, conditionEndIdx, blockForEndIdx])
    return pos

def For2WhileRepalce(tokens, pos):
    """
    【干预操作】：将 for 循环转换为等价的 while 循环（语义保留变换）
    将：for (A; B; C) { body } ====> 变成：A; while(B) { body; C; }
    """
    beforeFor = tokens[:pos[0]]
    condition1 = tokens[pos[0] + 2:pos[1] + 1] # 提取初始化部分 A (包含分号)
    condition2 = tokens[pos[1] + 1:pos[2]]     # 提取判断条件部分 B (不包含分号)
    condition3 = tokens[pos[2] + 1:pos[3]] + [";"] # 提取自增部分 C，并补上分号
    
    # 提取循环体 body
    if tokens[pos[3] + 1] == "{":
        body = tokens[pos[3] + 2:pos[4]]
    else:
        body = tokens[pos[3] + 1:pos[4] + 1]
    afterFor = tokens[pos[4] + 1:]
    
    # 组装：根据 for 循环所处的上下文，决定是否要在外层再包一个大括号 {}，
    # 这是为了限制原 for(int i=0) 中声明的变量 i 的作用域，防止污染后面的代码
    if beforeFor != [] and beforeFor[-1] in [";", "{", "}"]:
        res = beforeFor + condition1 + ["while", "("] + condition2 + [")", "{"] + body + condition3 + ["}"] + afterFor
    else:
        res = beforeFor + ["{"] + condition1 + ["while", "("] + condition2 + [")", "{"] + body + condition3 +["}", "}"] + afterFor
    return res


def While2ForReplacePos(tokens, endPoses):
    """寻找 `while` 循环的位置"""
    pos =[]
    n = len(tokens)
    for i, t in enumerate(tokens):
        if t == "while":
            whileIdx = i
            conditionEndIdx = _go4match(tokens, "(", whileIdx)
            # 跳过 do-while 循环中的 while，因为 do-while 转 for 比较复杂且不常见
            if conditionEndIdx + 1 < n and tokens[conditionEndIdx + 1] == ";":  
                continue
            # 确定 while 循环体的结尾位置
            if tokens[conditionEndIdx + 1] == "{":
                blockWhileEndIdx = _go4match(tokens, "{", conditionEndIdx)
            else:
                blockWhileEndIdx = endPoses[conditionEndIdx + 1]
            pos.append([whileIdx, conditionEndIdx, blockWhileEndIdx])
    return pos

def While2ForRepalce(tokens, pos):
    """
    【干预操作】：将 while 循环转换为等价的 for 循环（语义保留变换）
    将：while (B) { body } ====> 变成：for(; B; ) { body }
    """
    beforeWhile = tokens[:pos[0]]
    condition = tokens[pos[0] + 2:pos[1]]
    if tokens[pos[1] + 1] == "{":
        body = tokens[pos[1] + 2:pos[2]]
    else:
        body = tokens[pos[1] + 1:pos[2] + 1]
    afterWhile = tokens[pos[2] + 1:]
    
    # 组装：直接把 while 换成 for，并在条件前后加上必需的分号
    res = beforeWhile + ["for", "(", ";"] + condition + [";", ")", "{"] + body + ["}"] + afterWhile
    return res


# =======================================================================
# 单元测试模块：当直接运行 `python pattern.py` 时执行。
# 用于测试所有的坐标计算、插入/删除操作、控制流反转是否能通过 parser 编译。
# =======================================================================
if __name__ == "__main__":
    import random
    import pycparser

    # 读取之前预处理好的序列化数据
    with gzip.open('../dataset/data.pkl.gz', "rb") as f:
        d = pickle.load(f)
        raw = d['raw_tr'] + d['raw_te']

    ''' 
    # [测试 1] 测试代码语句切分器
    for i, code in enumerate(raw):
        if "struct" in code:
            print("%d-----------------------------------------"%i)
            pos = StmtInsPos(code) #pos = StmtInsPos(code)
            _InsVis(code, pos)
            print("%d~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"%i)
            stmts, _, indents = tokens2stmts(code)
            endTokenIndices = getStmtEnd(code, 3)
            for stmt, endIdx, indent in zip(stmts, endTokenIndices, indents):
                if endIdx != None:
                    print("{:30}".format(" ".join(code[endIdx-3:endIdx+1])), end="")
                else:
                    print("{:30}".format(" "), end="")
                print(indent + " ".join(stmt))
    '''

    # [测试 2] TEST INSERT & DELETE (测试死代码的插入与删除)
    parser = pycparser.c_parser.CParser()
    inserts =[
        ";",
        "if ( false ) ;",
        "if ( true ) ;",
        "if ( false ) ; else ;"]
    inserts =[insert.split(" ") for insert in inserts]
    
    # 随机抽 1000 个代码文件进行插入和删除压力测试
    for _ in range(1000):
        code = random.sample(raw, 1)[0]
        # 获取严格模式下的安全插入点
        poses = StmtInsPos(code, strict=True)
        insertDict = dict([(pos, []) for pos in poses])
        _InsVis(code, poses) # 打印插入前的样子
        print("-----------------------------------")
        
        suc_cnt = 0
        # 尝试插入 10 次死代码
        for _ in range(10):
            candis = InsAddCandidates(insertDict)
            insIdx = random.randint(0, len(candis) - 1)
            pos = candis[insIdx]
            instIdx = random.randint(0, len(inserts) - 1)
            inst = inserts[instIdx]
            
            if InsAdd(insertDict, pos, inst):
                suc_cnt += 1
            _InsVis(InsResult(code, insertDict),[])
            
            # 【关键】：使用真正的 C 语言解析器 pycparser 验证我们通过纯 Token 操作拼出来的代码是否符合 C 语法
            parser.parse(" ".join(InsResult(code, insertDict)))
            print("------------- INSERT ---------------", insertDict["count"])
            
        # 尝试将刚才插入的死代码逐一撤销 (恢复原状)
        for _ in range(suc_cnt):
            candis = InsDeleteCandidates(insertDict)
            delIdx = random.randint(0, len(candis) - 1)
            pos, listIdx = candis[delIdx]
            InsDelete(insertDict, pos, listIdx)
            _InsVis(InsResult(code, insertDict),[])
            
            # 撤销后再编译一次，确保没搞坏原代码
            parser.parse(" ".join(InsResult(code, insertDict)))
            print("------------- REMOVE --------------", insertDict["count"])
        print()

    # 以下是原作者注释掉的控制流反转单元测试代码，逻辑同上，都是调用对应的替换函数后使用 _InsVis 可视化
    
    # [测试 3] TEST FOR => WHILE (测试 for 转 while)
    '''code = raw[2333]
    _InsVis(code,[])
    endPoses = getStmtEnd(code, 3)
    poses = For2WhileReplacePos(code, endPoses)
    for pos in poses:
        res = For2WhileRepalce(code, pos)
        print("-----------------------------------")
        _InsVis(res, [])'''

    # [测试 4] TEST WHILE => FOR (测试 while 转 for)
    '''code = raw[233]
    _InsVis(code,[])
    endPoses = getStmtEnd(code, 3)
    poses = While2ForReplacePos(code, endPoses)
    for pos in poses:
        res = While2ForRepalce(code, pos)
        print("-----------------------------------")
        _InsVis(res, [])'''

    #[测试 5] TEST FINAL IF ELSE (测试 if-else 倒转)
    '''code = raw[233]
    _InsVis(code,[])
    endPoses = getStmtEnd(code, 3)
    poses = IfElseReplacePos(code, endPoses)
    for pos in poses:
        res = IfElseReplace(code, pos)
        print("-----------------------------------")
        _InsVis(res, [])'''

    # [测试 6] TEST SINGLE IF (测试单 if 变双分支)
    '''code = raw[233]
    _InsVis(code,[])
    endPoses = getStmtEnd(code, 3)
    poses = IfReplacePos(code, endPoses)
    for pos in poses:
        res = IfReplace(code, pos)
        print("-----------------------------------")
        _InsVis(res,[])'''