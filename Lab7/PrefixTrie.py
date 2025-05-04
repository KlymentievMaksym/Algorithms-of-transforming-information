
if __name__ == "__main__":  # pragma: no cover
    from TimerMemory import TimerMemory


class TrieNode:
    def __init__(self, value="", key=0, key_add=0):
        self.children = {}
        self.value = value
        self.key = key
        self.key_add = key_add
        self.isEndOfWord = False

    def __repr__(self):  # pragma: no cover
        return f"{self.value}, {self.isEndOfWord}"


class PrefixTrie:
    def __init__(self, patterns, repr="connections"):
        if repr == "connections":
            self.repr = True
        else:
            self.repr = False
        self.root = TrieNode()
        self.patterns = patterns
        for pattern in patterns:
            self.insert(pattern)

    def insert(self, word):
        node = self.root
        for ch in word:
            if ch not in node.children:
                new_key = node.key_add + 1
                node.children[ch] = TrieNode(ch, new_key, new_key)
                node.key_add += 1
            node = node.children[ch]
        node.isEndOfWord = True

    def searchPattern(self, word):
        node = self.root
        for ch in word:
            if ch not in node.children:
                return False
            node = node.children[ch]
        return node.isEndOfWord

    def search(self, word):
        # patterns = {pattern: 0 for pattern in self.patterns}
        text = ""
        for ch_index in range(len(word)):
            node = self.root
            # wrd = node.value
            for index in range(ch_index, len(word)):
                char = word[index]
                inside = char in node.children
                if inside:
                    # wrd += word[index]
                    node = node.children[char]
                    if node.isEndOfWord:
                        text += str(ch_index) + " "
                        # patterns[wrd] += 1
                else:
                    break
        # return patterns
        return text.strip()

    def startsWith(self, prefix):
        node = self.root
        for ch in prefix:
            if ch not in node.children:
                return False
            node = node.children[ch]
        return True

    def __repr__(self):
        result = []
        if self.repr:
            stack = [self.root]
            while stack:
                node = stack.pop()  # From Last to First
                for char, child in node.children.items():
                    result.append(f"{node.key}->{child.key}:{char}")
                    stack.append(child)
            return "\n".join(result)
        else:
            stack = [[self.root, self.root.value]]
            while stack:
                node, prefix = stack.pop()  # Not sure which will be next... ^_^
                for char, child in node.children.items():
                    if child.isEndOfWord:
                        result.append(f"{prefix}{char}")
                    stack.append([child, prefix + char])
            return "\n".join(result)


if __name__ == "__main__":  # pragma: no cover
    with TimerMemory(True):
        tree = PrefixTrie(["banana", "pan", "nab", "antenna", "bandana", "ananas", "nana"], None)
        print(tree.search("panamabananas"))
        print(tree)
