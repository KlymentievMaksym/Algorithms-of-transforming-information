import numpy as np


class NodeR:
    def __init__(self, name: str = None, next: "Node" = None):
        self.name = name
        self.next = next

    def __repr__(self):
        return f"{self.name}"


class Node:
    def __init__(self, key: int, name: str = None, name_end: str = None, next: "Node" = None, prev: "Node" = None):
        self.key = key
        self.name = name
        self.name_end = name_end
        self.prev = prev

    def __repr__(self):
        return f"{self.key}|{self.name}|{self.name_end}"


class BerrouzWiller:
    def __init__(self, word: str, pattern: str = None, reverse: bool = False):
        self.word = word
        self.pattern = pattern
        self.reverse = reverse

    @property
    def run(self):
        if self.reverse:
            return self._reverse
        elif self.pattern:
            return self._count
        else:
            return self._straight

    @property
    def _straight(self) -> str:
        double_word = self.word * 2
        matrix = [double_word[i:i+len(self.word)] for i in range(len(self.word))]
        matrix = sorted(matrix)
        return "".join(word[-1] for word in matrix)

    @property
    def _reverse(self) -> str:
        n = len(self.word)
        word_needed = ""
        if n >= 1:
            # create connections beetween first and last cols
            word_rec = [NodeR(char) for char in self.word]  # Slow
            # print("First")
            word_start = sorted(word_rec, key=lambda x: x.name)
            # print("Second")
            for first, second in zip(word_start, word_rec):
                first.next = second
            # print("Connected")

            # recreate word  # Slow
            start_node = word_start[0]
            word_needed += start_node.name
            node = start_node.next
            while node != start_node:
                word_needed += node.name
                node = node.next
                # print(len(word_needed))
            # print("Created")
            word_needed = word_needed[::-1]
            # print("Inverted")
        return word_needed

    @property
    def _count(self) -> int:
        double_word = self.word * 2
        matrix = [double_word[i:i+len(self.word)] for i in range(len(self.word))]
        # matrix = [self.word[:i] + self.word[i:] for i in range(len(self.word))]
        matrix_2 = [Node(i, rotation[0], rotation[-1]) for i, rotation in enumerate(matrix)]
        for node_index in range(len(matrix)):
            matrix_2[node_index].prev = matrix_2[(node_index - 1) % len(matrix)]
        matrix = sorted(matrix_2, key=lambda x: matrix[matrix_2.index(x)])
        for node_index in range(len(matrix)):
            matrix[node_index].key = node_index

        count = 0
        new_top = 0
        new_bottom = len(matrix) - 1

        if new_top < new_bottom:
            for pattern_last_char_index in range(len(self.pattern) - 1, -1, -1):
                top = new_top
                bottom = new_bottom
                new_top, new_bottom = float("inf"), float("-inf")

                last_char = self.pattern[pattern_last_char_index]
                while (matrix[bottom].name != last_char or matrix[top].name != last_char) and top <= bottom:
                    if matrix[bottom].name != last_char:
                        bottom -= 1
                    if matrix[top].name != last_char:
                        top += 1
                if top > bottom:
                    break
                if pattern_last_char_index - 1 < 0:
                    for char in matrix[top:bottom + 1]:
                        if char.name == last_char:
                            count += 1
                else:
                    for char in matrix[top:bottom + 1]:
                        if char.name == last_char and char.name_end == self.pattern[pattern_last_char_index - 1]:
                            new_top = min(new_top, char.prev.key)
                            new_bottom = max(new_bottom, char.prev.key)
        return count
