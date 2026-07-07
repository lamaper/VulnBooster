from __future__ import annotations

from dataclasses import dataclass, field
from typing import Any


CORE_FIELDS = {
    "idx",
    "func",
    "target",
    "cwe",
    "cve",
    "llm_slice",
    "static_slice",
    "refined_code",
    "code_lines",
    "raw_lines",
    "fromIdx",
    "original_idx",
    "pred_label",
    "pred_prob_0",
    "pred_prob_1",
    "is_cot_enhanced",
    "is_cwe_enhanced",
}


@dataclass(slots=True)
class CodeSample:
    idx: str
    func: str = ""
    target: int | None = None
    cwe: list[str] = field(default_factory=list)
    cve: list[str] = field(default_factory=list)
    llm_slice: str = ""
    static_slice: str = ""
    refined_code: str = ""
    extras: dict[str, Any] = field(default_factory=dict)

    @classmethod
    def from_dict(cls, obj: dict[str, Any]) -> "CodeSample":
        code_lines = obj.get("code_lines", "")
        if isinstance(code_lines, list):
            static_slice = "\n".join(code_lines)
        else:
            static_slice = obj.get("static_slice", code_lines or "")

        return cls(
            idx=str(obj.get("idx", obj.get("fromIdx", ""))),
            func=obj.get("func", ""),
            target=int(obj["target"]) if obj.get("target") is not None else None,
            cwe=list(obj.get("cwe", [])) if isinstance(obj.get("cwe", []), list) else [str(obj["cwe"])],
            cve=list(obj.get("cve", [])) if isinstance(obj.get("cve", []), list) else [str(obj["cve"])],
            llm_slice=obj.get("llm_slice", ""),
            static_slice=static_slice,
            refined_code=obj.get("refined_code", ""),
            extras={k: v for k, v in obj.items() if k not in CORE_FIELDS},
        )

    def to_dict(self) -> dict[str, Any]:
        payload: dict[str, Any] = {
            "idx": self.idx,
            "func": self.func,
            "target": self.target,
            "cwe": self.cwe,
            "cve": self.cve,
        }
        if self.llm_slice:
            payload["llm_slice"] = self.llm_slice
        if self.static_slice:
            payload["static_slice"] = self.static_slice
        if self.refined_code:
            payload["refined_code"] = self.refined_code
        payload.update(self.extras)
        return payload

    def best_available_code(self, order: tuple[str, ...] = ("refined_code", "llm_slice", "static_slice", "func")) -> str:
        for field_name in order:
            value = getattr(self, field_name, "")
            if isinstance(value, str) and value.strip():
                return value
        return ""
