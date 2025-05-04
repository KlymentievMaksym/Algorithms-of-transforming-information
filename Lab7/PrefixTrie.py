
if __name__ == "__main__":  # pragma: no cover
    from TimerMemory import TimerMemory


class TrieNode:
    def __init__(self):
        self.children = {}
        self.value = None
        self.isEndOfWord = False


class PrefixTrie:
    def __init__(self, patterns):
        self.root = TrieNode()
        for pattern in patterns:
            self.insert(pattern)

    def insert(self, word):
        node = self.root
        for ch in word:
            if ch not in node.children:
                node.children[ch] = TrieNode()
            node = node.children[ch]
        node.isEndOfWord = True

    def search(self, word):
        node = self.root
        for ch in word:
            if ch not in node.children:
                return False
            node = node.children[ch]
        return node.isEndOfWord

    def startsWith(self, prefix):
        node = self.root
        for ch in prefix:
            if ch not in node.children:
                return False
            node = node.children[ch]
        return True


if __name__ == "__main__":  # pragma: no cover
    with TimerMemory():
        tree = PrefixTrie(["apple", "app", "ape", "apples"])
        print(tree.search("apple"))

""" Задача 1
Побудуйте префiксне дерево для заданої множини шаблонiв.

– Формат вхiдних даних
Текстовий файл input.dat (ASCII), який мiстить цiле число n та множину
шаблонiв P atterns = {p1, . . . , pn} (цiле число та кожен шаблон заданi в окремомих рядках).

– Обмеження на вхiднi данi
1 <= n <= 100; 1 <= | pi | <= 100 для всiх 1 <= i <= n;
кожен шаблон є словом над алфавiтом { A, C, G, T };
жоден шаблон не є префiксом iншого шаблону.

– Обмеження на реалiзацiю
Програма повинна завершувати роботу за час, що не перевищує 2 секунд на кожен тестовий приклад.
Тести, на яких програма не завершила роботу за цей час, вважаються невдалими.
Програма повинна використовувати не бiльше 512 Мб пам’ятi.

– Формат вихiдних даних
Текстовий файл output.dat (ASCII), який мiстить список сумiжностi, що вiдповiдає префiксному
дереву шаблонiв в такому форматi. Якщо префiксне дерево має n вершин, спочатку позначаємо
корiнь як 0, а потiм позначаємо решту вершин цiлими числами вiд 1 до n - 1 у довiльному порядку.
Кожне ребро списку сумiжностi дерева буде закодовано трiйкою: першi два елементи трiйки повиннi
бути цiлими числами i, j, якi позначають початкову та кiнцеву вершини ребра вiдповiдно; третiй
елемент трiйки повинен бути символом c \in { A, C, G, T } , який позначає саме ребро. Необхiдно
вивести кожну таку трiйку у форматi i \rightarrow j : c (без пропускiв) в окремому рядку. Порядок виведення
трiйок не має значення.

– Приклад 1.
Вхiднi данi (input.dat):
1
CGT
Вихiднi данi (output.dat):
0->1:C
1->2:G
2->3:T

Приклад 2.
Вхiднi данi (input.dat):
3
CG
CC
CT

Вихiднi данi (output.dat):
0->1:C
1->2:G
1->3:C
1->4:T
"""


"""
– Задача 2.
Знайдiть всi входження множини шаблонiв в текстi (за допомогою префiксного дерева).
– Формат вхiдних даних
Текстовий файл input.dat (ASCII), який у першому рядку мiстить текст T ext, у другому рядку
мiстить цiле число n та множину шаблонiв P atterns = { p1, . . . , pn } (цiле число та кожен шаблон
також заданi в окремих рядках).
– Обмеження на вхiднi данi
1 <= | T ext| <= 10000; 1 <= n <= 5000; 1 <= | pi

| <= 100 для всiх 1 <= i <= n; кожен шаблон є словом над

алфавiтом { A, C, G, T } ; жоден шаблон не є префiксом iншого шаблону.
– Обмеження на реалiзацiю
Програма повинна завершувати роботу за час, що не перевищує 7 секунд на кожен тестовий приклад.
Тести, на яких програма не завершила роботу за цей час, вважаються невдалими.
Програма повинна використовувати не бiльше 512 Мб пам’ятi.
– Формат вихiдних даних
Текстовий файл output.dat (ASCII), який мiстить всi iндекси (iндексацiя починається з 0) входжень
шаблонiв у текстi в порядку зростання в одному рядку, роздiленi пробiлами.
– Приклад 1.
Вхiднi данi (input.dat):
СССС
1
CС

Вихiднi данi (output.dat):
0 1 2

Приклад 2.
Вхiднi данi (input.dat):
СССС
2
CG
CT

Вихiднi данi (output.dat):

Що є порожнiм файлом.
Приклад 3.
Вхiднi данi (input.dat):

ATTCCGATA
3
AT
C

Вихiднi данi (output.dat):
0 3 4 6
"""

"""
4. Бонуснi бали
За пiдготовку тестових прикладiв (з правильними вiдповiдями), якi покривають усi крайнi
випадки i якi можна вважати достатньо повними, можна отримати до 4 бонусних балiв (до 2 бонусних
балiв для кожної задачi).
"""
