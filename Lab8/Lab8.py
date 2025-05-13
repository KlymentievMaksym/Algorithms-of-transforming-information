if __name__ == "__main__":  # pragma: no cover
    from TimerMemory import TimerMemory
    from BerrouzWiller import BerrouzWiller
else:
    from .TimerMemory import TimerMemory
    from .BerrouzWiller import BerrouzWiller

from os import listdir

path = "."
data = "Lab8Data"
inputs = listdir(path)
if data in inputs:
    path += f"/{data}"
    inputs = listdir(path)
else:
    if "Lab8" in inputs:
        path += "/Lab8"
        inputs = listdir(path)
        if data in inputs:
            path += f"/{data}"
            inputs = listdir(path)

# print(inputs)

# with TimerMemory(True):
for input in inputs[:]:
    if input.startswith("input") and input.endswith(".dat"):
        output = input.replace("in", "out")
        print("[I]", input)
        with TimerMemory(True) as TM:
            with open(path + "/" + input, "r") as f:
                text = f.read().split("\n")
                if len(text) == 2:
                    word = text[0]
                    pattern = text[1]
                elif len(text) == 1:
                    word = text[0]
                    pattern = None
                print(word, pattern)
                bw = BerrouzWiller(word, pattern, reverse=False if word[-1] == "$" or "$" not in word else True)
                print(bw)
                with open(path + "/" + output, "w") as f:
                    f.write(str(bw))
        print("[O]", output)
        print()
