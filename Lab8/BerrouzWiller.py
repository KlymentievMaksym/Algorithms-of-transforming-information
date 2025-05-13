import numpy as np


class Node:
    def __init__(self, key: int, name: str = None, name_end: str = None, next: "Node" = None, prev: "Node" = None):
        self.key = key
        self.name = name
        self.name_end = name_end
        self.next = next
        self.prev = prev

    def __repr__(self):
        return f"{self.key}|{self.name}|{self.name_end}"


class BerrouzWiller:
    def __init__(self, word: str, pattern: str = None, reverse: bool = False):
        self.word = word
        self.pattern = pattern
        self.reverse = reverse
        self.matrix = []
        self.count = 0
        if self.word != "":
            self.run

    def _find_count(self, i, top=0, bottom=None):
        count = 0
        top = top
        if bottom is None:
            bottom = len(self.matrix) - 1
        last_char = self.pattern[len(self.pattern) - 1 - i]
        while (self.matrix[bottom].name != last_char or self.matrix[top].name != last_char) and top <= bottom:
            if self.matrix[bottom].name != last_char:
                bottom -= 1
            if self.matrix[top].name != last_char:
                top += 1
        investigate_top = float("inf")
        investigate_bottom = float("-inf")
        for char in self.matrix[top:bottom + 1]:
            if len(self.pattern) - 2 - i < 0:
                if char.name == last_char:
                    count += 1

            elif char.name == last_char and char.name_end == self.pattern[len(self.pattern) - 2 - i]:
                investigate_top = min(investigate_top, char.prev.key)
                investigate_bottom = max(investigate_bottom, char.prev.key)
        # print(self.matrix[top:bottom + 1])
        if len(self.pattern) - 2 - i < 0:
            return count
        count += self._find_count(i+1, investigate_top, investigate_bottom)
        return count

    @property
    def run(self):
        if self.reverse:
            n = len(self.word)
            word_to_add = np.array([list(char for char in self.word)]).T

            matrix = sorted(word_to_add, key=lambda x: x[0])
            matrix = np.array(matrix)

            while matrix.shape[1] < n:
                matrix = np.concatenate((word_to_add, matrix), axis=1)
                matrix = sorted(matrix, key=lambda x: x[0])
                matrix = np.array(matrix)

            # print(matrix)
            word_needed = None
            for word in matrix:
                if word[-1] == "$":
                    word_needed = "".join(word)
                    break
            self.word_needed = word_needed
        else:
            matrix = [self.word]
            for i in range(1, len(self.word)):
                matrix.append(self.word[i:] + self.word[:i])

            indexes = np.argsort(matrix)

            self.matrix = [Node(0, matrix[0][0], matrix[0][-1])]
            for i in range(1, len(matrix)):
                self.matrix.append(Node(i, matrix[i][0], matrix[i][-1]))
                self.matrix[-2].next = self.matrix[-1]
                self.matrix[-1].prev = self.matrix[-2]
            self.matrix[0].prev = self.matrix[-1]
            self.matrix[-1].next = self.matrix[0]

            self.matrix = np.array(self.matrix)
            self.matrix = list(self.matrix[indexes])

            for i in range(0, len(self.matrix)):
                self.matrix[i].key = i

            if self.pattern and self.word >= self.pattern:
                self.count = self._find_count(0)

    def __repr__(self):
        if self.pattern:
            return str(self.count)
        if self.reverse:
            return self.word_needed
        return "".join([node.name_end for node in self.matrix])
