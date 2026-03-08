# list_models.py
from openai import OpenAI
import os

# 替换成你的 Google API Key
GOOGLE_API_KEY = "AIzaSyA74l3-6A8OWTu8cdHejOoKS___KcJJQdc"

client = OpenAI(
    api_key=GOOGLE_API_KEY,
    base_url="https://generativelanguage.googleapis.com/v1beta/openai/"
)

try:
    models = client.models.list()
    for m in models:
        print(m.id)
except Exception as e:
    print(e)