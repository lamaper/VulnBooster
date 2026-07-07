from __future__ import annotations

import json
import re
from pathlib import Path

import requests
from bs4 import BeautifulSoup


class CWEKnowledgeBase:
    def __init__(self, cache_file: Path):
        self.cache_file = cache_file
        self.cache_file.parent.mkdir(parents=True, exist_ok=True)

    def load_cache(self) -> dict[str, dict[str, str]]:
        if not self.cache_file.exists():
            return {}
        try:
            return json.loads(self.cache_file.read_text(encoding="utf-8"))
        except json.JSONDecodeError:
            return {}

    def save_cache(self, cache: dict[str, dict[str, str]]) -> None:
        self.cache_file.write_text(json.dumps(cache, ensure_ascii=False, indent=2), encoding="utf-8")

    def fetch(self, cwe_id: str) -> dict[str, str] | None:
        match = re.search(r"\d+", cwe_id)
        if not match:
            return None

        cwe_num = match.group(0)
        url = f"https://cwe.mitre.org/data/definitions/{cwe_num}.html"
        headers = {
            "User-Agent": "Mozilla/5.0",
        }
        response = requests.get(url, headers=headers, timeout=15)
        if response.status_code != 200:
            return None

        soup = BeautifulSoup(response.text, "html.parser")
        result = {
            "def": "Definition not found on MITRE.",
            "manifest": "Manifestation examples not found on MITRE.",
        }

        desc_div = soup.find(id="oc_Description") or soup.find(id="Description")
        if desc_div:
            detail = desc_div.find(class_="detail") or desc_div
            text = detail.get_text(separator=" ", strip=True)
            if text:
                result["def"] = text

        example_div = soup.find(id="oc_Demonstrative_Examples") or soup.find(id="Demonstrative_Examples")
        if not example_div:
            example_div = soup.find(id="oc_Observed_Examples") or soup.find(id="Observed_Examples")
        if example_div:
            detail = example_div.find(class_="detail") or example_div
            text = detail.get_text(separator=" ", strip=True)
            text = re.sub(r"Example Language:\s*\w+", "", text)
            text = re.sub(r"\(bad code\)|\(good code\)", "", text)
            text = re.sub(r"\s+", " ", text).strip()
            if text:
                result["manifest"] = re.split(r"\s*Example\s*[2-9]\s*", text, maxsplit=1, flags=re.IGNORECASE)[0].strip()
        return result

    def get(self, cwe_id: str) -> dict[str, str] | None:
        cache = self.load_cache()
        if cwe_id in cache:
            return cache[cwe_id]
        fetched = self.fetch(cwe_id)
        if fetched:
            cache[cwe_id] = fetched
            self.save_cache(cache)
        return fetched
