if __name__ == "__main__":  # pragma: no cover
    from TimerMemory import TimerMemory
    from PrefixTrie import PrefixTrie
else:
    from .TimerMemory import TimerMemory
    from .PrefixTrie import PrefixTrie

from os import listdir

path = "."
inputs = listdir(path)
if "Lab7Data" in inputs:
    path += "/Lab7Data"
    inputs = listdir(path)
else:
    if "Lab7" in inputs:
        path += "/Lab7"
        inputs = listdir(path)
        if "Lab7Data" in inputs:
            path += "/Lab7Data"
            inputs = listdir(path)

# print(inputs)

# with TimerMemory(True):
for input in inputs:
    if input.endswith(".dat") and input.startswith("input"):
        output = input.replace("in", "out")
        print("[I]", input)
        with TimerMemory(True) as TM:
            with open(path + "/" + input, "r") as f:
                text = f.read().split("\n")
                word = None
                try:
                    n = int(text[0])
                    patterns = text[1:]
                except Exception as e1:
                    try:
                        word = text[0]
                        n = int(text[1])
                        patterns = text[2:]
                    except Exception as e2:
                        print("[ERROR]", e1, e2)
                trie = PrefixTrie(patterns)
                with open(path + "/" + output, "w") as f:
                    if word is not None:
                        f.write(str(trie.search(word)))
                    else:
                        f.write(str(trie))
        print("[O]", output)
        print()
