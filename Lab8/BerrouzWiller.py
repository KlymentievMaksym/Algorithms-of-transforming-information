import numpy as np

class Node:
    def __init__(self, key=None, name=None, name_end=None, next=None, prev=None):
        self.key = key
        self.name = name
        self.name_end = name_end
        self.next = next
        self.prev = prev

    def __repr__(self):
        return f"{self.key}|{self.name}|{self.name_end}"

class BerrouzWiller:
    def __init__(self, word, pattern=None, reverse=False):
        self.word = word
        self.pattern = pattern
        self.reverse = reverse
        self.matrix = []
        self.run

    def _find_count(self, i, top=0, bottom=None):
        if i == len(self.pattern):
            raise NotImplementedError
            return 1
        count = 0
        top = top
        if bottom is None:
            bottom = len(self.matrix) - 1
        while top <= bottom:
            mid = (top + bottom) // 2
            if self.matrix[mid].name > self.pattern[i]:
                bottom = mid
            elif self.matrix[mid].name < self.pattern[i]:
                top = mid
            else:
                if self.matrix[bottom].name != self.pattern[i]:
                   bottom -= 1
                elif self.matrix[top].name != self.pattern[i]:
                    top += 1
                else:
                    investigate_top = float("inf")
                    investigate_bottom = float("-inf")
                    for char in self.matrix[top:bottom + 1]:
                        if char.name == self.pattern[i+1]:
                            investigate_top = min(investigate_top, char.key)
                            investigate_bottom = max(investigate_bottom, char.key)
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
            
            # n = len(matrix)-1
            # self.matrix = [Node(n, matrix[0][0], matrix[0][-1])]
            # for i in range(1, len(matrix)):
            #     self.matrix.append(Node(n - i, matrix[i][0], matrix[i][-1]))
            #     self.matrix[-2].next = self.matrix[-1]
            #     self.matrix[-1].prev = self.matrix[-2]
            # return self.matrix
        else:
            matrix = [self.word]
            for i in range(1, len(self.word)):
                matrix.append(self.word[i:] + self.word[:i])
            matrix = sorted(matrix)
            self.matrix = [Node(0, matrix[0][0], matrix[0][-1])]
            for i in range(1, len(matrix)):
                self.matrix.append(Node(i, matrix[i][0], matrix[i][-1]))
                self.matrix[-2].next = self.matrix[-1]
                self.matrix[-1].prev = self.matrix[-2]
            if self.pattern:
                print(self.matrix)
                self._find_count(0)
                
                raise NotImplementedError
            # return self.matrix

    def __repr__(self):
        if self.reverse:
            return self.word_needed
        return "".join([node.name_end for node in self.matrix])
