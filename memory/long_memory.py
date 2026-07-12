import re

from memory.conversation import load_memory, save_memory


def remember(text):

    memory = load_memory()

    lower = text.lower()


    patterns = [

        r"my name is (.+)",

        r"i am (.+)",

        r"my favourite color is (.+)",

        r"my favorite color is (.+)",

        r"i like (.+)",

        r"i love (.+)",

        r"i am building (.+)",

        r"i'm building (.+)"
    ]


    for pattern in patterns:

        match = re.search(pattern, lower)

        if match:

            fact = match.group(0)

            if fact not in memory["facts"]:

                memory["facts"].append(fact)

                save_memory(memory)


def get_facts():

    return load_memory()["facts"]