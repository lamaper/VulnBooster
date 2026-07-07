# =====================================================================
# 模板定义及 CWE 知识库配置
# =====================================================================

# 动态反引号防止截断
TICK3 = chr(96) * 3

# 系统提示词 (System)
SYSTEM_PROMPT = (
    "You are an expert C/C++ security analyst. Your task is to generate precise, "
    "semantically complete vulnerable functions strictly adhering to the provided rules."
)

# ---------------------------------------------------------------------
# [定制化提示词模板] (适用于 Top 8 知识完备的 CWE)
# ---------------------------------------------------------------------
CUSTOMIZED_TEMPLATE = (
    "You are working on a software security task that requires generating semantically equivalent vulnerable C functions.\n\n"
    "[Seed Code]\n"
    "{seedfunc}\n\n"
    "[Vulnerability Definition]\n"
    "{vulDef}\n\n"
    "[Vulnerability Manifestation]\n"
    "{vulManifest}\n\n"
    "[Your Task]\n"
    "Referring to the [Vulnerability Definition] and [Vulnerability Manifestation] above to ensure the correct vulnerability "
    "semantics, and using the Seed Code above only as a stylistic and structural reference, generate {k} new C functions.\n\n"
    "[Output Format]\n"
    "Wrap EACH generated function in the following format:\n"
    f"{TICK3}c\n"
    "resultCode\n"
    f"{TICK3}"
)

# ---------------------------------------------------------------------
# [通用提示词模板] (适用于长尾/知识缺失的 CWE)
# ---------------------------------------------------------------------
GENERAL_TEMPLATE = (
    "You are working on a software security task that requires generating semantically equivalent vulnerable C functions.\n\n"
    "[Seed Code]\n"
    "{seedfunc}\n\n"
    "[CWE Type]\n"
    "{cweType}\n\n"
    "[Your Task]\n"
    "Referring to the [Vulnerability Definition] and [Vulnerability Manifestation] above to ensure the correct vulnerability "
    "semantics, and using the Seed Code above only as a stylistic and structural reference, generate {k} new C functions.\n\n"
    "[Output Format]\n"
    "Wrap EACH generated function in the following format:\n"
    f"{TICK3}c\n"
    "resultCode\n"
    f"{TICK3}"
)