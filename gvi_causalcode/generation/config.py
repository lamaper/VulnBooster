import os
import re


def _env_flag(name: str, default: str = "1") -> bool:
    return os.getenv(name, default).strip().lower() not in {"0", "false", "no", "off"}


# ================= 1. LLM 接口配置 =================
# 统一切换到 OpenAI-compatible API，默认兼容 DeepSeek。
OPENAI_API_KEY = os.getenv("OPENAI_API_KEY", "")
LLM_API_KEY = os.getenv("LLM_API_KEY", "") or OPENAI_API_KEY
LLM_BASE_URL = os.getenv("LLM_BASE_URL", os.getenv("OPENAI_BASE_URL", "https://api.deepseek.com/v1"))
MODEL = os.getenv("LLM_MODEL", os.getenv("OPENAI_MODEL", "deepseek-chat"))
TEMPERATURE = float(os.getenv("GEN_TEMPERATURE", "0.9"))
TOP_P = float(os.getenv("GEN_TOP_P", "0.95"))
MAX_OUTPUT_TOKENS = int(os.getenv("GEN_MAX_OUTPUT_TOKENS", "4096"))
REQUEST_INTERVAL_SEC = float(os.getenv("GEN_REQUEST_INTERVAL_SEC", "0"))
REQUEST_TIMEOUT_SEC = int(os.getenv("GEN_REQUEST_TIMEOUT_SEC", "180"))

# ================= 2. 生成策略配置 =================
# 这里把原本偏论文复现的链式提示词，整理成“多种可切换的生成策略”。
PROMPT_MODE = os.getenv("PROMPT_MODE", "pattern_generate_repair")
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
static_check_report = os.path.join(gen_output_result_root, "static_check_report.json")

# ================= 4. 后处理与过滤配置 =================
SIMILARITY_BACKEND = os.getenv("SIMILARITY_BACKEND", "tfidf")
_default_similarity_threshold = "0.92" if SIMILARITY_BACKEND == "tfidf" else "0.4"
SIMILARITY_THRESHOLD = float(os.getenv("SIMILARITY_THRESHOLD", _default_similarity_threshold))
SYNTAX_CHECK_ENABLED = _env_flag("SYNTAX_CHECK_ENABLED", "1")
SYNTAX_CHECKER = os.getenv("SYNTAX_CHECKER", "auto")
SYNTAX_TIMEOUT_SEC = int(os.getenv("SYNTAX_TIMEOUT_SEC", "15"))
SEMGREP_ENABLED = _env_flag("SEMGREP_ENABLED", "1")
SEMGREP_BIN = os.getenv("SEMGREP_BIN", "semgrep")
SEMGREP_RULES = os.getenv(
    "SEMGREP_RULES",
    os.path.join(os.path.dirname(__file__), "static_check", "semgrep_vuln_rules.yml"),
)
SEMGREP_TIMEOUT_SEC = int(os.getenv("SEMGREP_TIMEOUT_SEC", "20"))
SEMGREP_REQUIRE_MATCH = _env_flag("SEMGREP_REQUIRE_MATCH", "0")
