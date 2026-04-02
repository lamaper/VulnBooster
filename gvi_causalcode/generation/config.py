import os
import re

# ================= 1. LLM 接口配置 =================
# 默认优先走 Gemini 官方 REST 接口，不再依赖 langchain。
LLM_PROVIDER = os.getenv("LLM_PROVIDER", "gemini")
GEMINI_API_KEY = os.getenv("GEMINI_API_KEY", "")
OPENAI_API_KEY = os.getenv("OPENAI_API_KEY", "")
LLM_API_KEY = os.getenv("LLM_API_KEY", "") or GEMINI_API_KEY or OPENAI_API_KEY

LLM_BASE_URL = os.getenv("LLM_BASE_URL", "https://generativelanguage.googleapis.com/v1beta")
MODEL = os.getenv("LLM_MODEL", os.getenv("GEMINI_MODEL", "gemini-2.0-flash"))
TEMPERATURE = float(os.getenv("GEN_TEMPERATURE", "0.9"))
TOP_P = float(os.getenv("GEN_TOP_P", "0.95"))
MAX_OUTPUT_TOKENS = int(os.getenv("GEN_MAX_OUTPUT_TOKENS", "4096"))
REQUEST_INTERVAL_SEC = float(os.getenv("GEN_REQUEST_INTERVAL_SEC", "0"))

# ================= 2. 生成策略配置 =================
# 这里把原本偏论文复现的链式提示词，整理成“多种可切换的生成策略”。
PROMPT_MODE = os.getenv("PROMPT_MODE", "direct_generate")
NUM_VARIANTS = int(os.getenv("NUM_VARIANTS", "4"))
MAX_SAMPLES = int(os.getenv("MAX_SAMPLES", "0"))

SYSTEM_PROMPT = (
    "You are a senior vulnerability researcher. "
    "Your task is to generate realistic vulnerable C functions for data augmentation. "
    "Preserve plausible software context and vulnerability mechanisms. "
    "Do not explain unless explicitly asked. When asked to generate code, output only the requested content."
)

# ================= 3. 路径配置 (适配 ReVeal) =================
# 注意：这里只读取漏洞样本作为种子。
origin_vul_data = os.getenv("ORIGIN_VUL_DATA", "../data/reveal/reveal_vul_only.json")


def _slugify(value: str) -> str:
    return re.sub(r"[^a-zA-Z0-9._-]+", "_", value).strip("_") or "run"


_default_run_tag = f"{PROMPT_MODE}_{_slugify(MODEL)}"
GEN_RUN_TAG = os.getenv("GEN_RUN_TAG", _default_run_tag)

gen_output_root = os.getenv("GEN_OUTPUT_ROOT", f"../data/reveal/{GEN_RUN_TAG}")
gen_output_result_root = os.getenv("GEN_OUTPUT_RESULT_ROOT", gen_output_root + "_result")
gen_combine_output = os.path.join(gen_output_result_root, "chain_combine.json")
rm_comments_output = os.path.join(gen_output_result_root, "chain_rm_comments.json")
similarity_database_root = os.path.join(gen_output_result_root, "db")
similarity_output = os.path.join(gen_output_result_root, "similarity.json")
similarity_output_graph = os.path.join(gen_output_result_root, "similarity_hist.png")

# ================= 4. 后处理与过滤配置 =================
SIMILARITY_THRESHOLD = float(os.getenv("SIMILARITY_THRESHOLD", "0.4"))
