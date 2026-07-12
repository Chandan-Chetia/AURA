import json
import os

MEMORY_FILE = "memory/memory.json"

MAX_HISTORY = 20


def load_memory():

    if not os.path.exists(MEMORY_FILE):

        return {
            "facts": [],
            "conversation": []
        }

    with open(MEMORY_FILE, "r", encoding="utf-8") as f:
        return json.load(f)


def save_memory(memory):

    with open(MEMORY_FILE, "w", encoding="utf-8") as f:
        json.dump(memory, f, indent=4)


def add_message(role, text):

    memory = load_memory()

    memory["conversation"].append({

        "role": role,

        "content": text

    })

    memory["conversation"] = memory["conversation"][-MAX_HISTORY:]

    save_memory(memory)


def get_history():

    return load_memory()["conversation"]


def clear_history():

    memory = load_memory()

    memory["conversation"] = []

    save_memory(memory)