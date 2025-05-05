import unittest
import numpy as np

from Lab7.PrefixTrie import PrefixTrie
from Lab7.TimerMemory import TimerMemory
"""
4. Бонуснi бали
За пiдготовку тестових прикладiв (з правильними вiдповiдями), якi покривають усi крайнi
випадки i якi можна вважати достатньо повними, можна отримати до 4 бонусних балiв (до 2 бонусних
балiв для кожної задачi).
"""


class TestPrefixTrie(unittest.TestCase):
    # ----------------------
    # 1 <= n <= 100; 1 <= | pi | <= 100
    # Завершувати роботу за час, що не перевищує 2 секунд на кожен тестовий приклад.
    # Програма повинна використовувати не бiльше 512 Мб пам’ятi. (Вивід 0->1: C, 1->2: G, 2->3: T) Але я не знаю, як це можна зробити і при цьому мати можливість порівняти очікуваний результат з тим, що отримали, тому буде лише перевірка пам'яті та часу

    # 1 <= |Text| <= 10_000; 1 <= n <= 5_000; 1 <= |pi| <= 100
    # Завершувати роботу за час, що не перевищує 7 секунд на кожен тестовий приклад.
    # Програма повинна використовувати не бiльше 512 Мб пам’ятi. (Вивід 0 3 3 4 4 6)
    # ----------------------
    # 1 <= |Text| <= 10_000; 1 <= n <= 5_000; 1 <= |pi| <= 100
    # TODO
    # |word| >= 10_000
    # |pi| >= 100
    # n >= 5000 Але я не знаю, як це взагалі можна зробити і, при цьому, мати можливість порівняти очікуваний результат з тим, що отримали, і, також, не мати префіксів префіксів
    # |word| <= 1
    # |pi| <= 1
    # n <= 1
    # ----------------------
    trie_empty = PrefixTrie([])
    trie_small_1 = PrefixTrie(["C"])
    trie_small_2 = PrefixTrie(["AT"])

    trie_standart = PrefixTrie(["CC", "CG", "C", "CT", "AT"])

    trie_big = PrefixTrie(["ATTC", "GATA", "TCCGA", "CT", "TTCCGA", "ATTCCGATA", "ATTCCGATA"*100])  # 900 > 100
    trie_not_standart = PrefixTrie(["CC", "CG", "C", "CT", "AT"], "Nonsense")

    word_standart = "ATTCCGATA"  # 9

    word_empty = ""  # 0
    word_small11 = "A"  # 1
    word_small12 = "C"  # 1
    word_small21 = "AT"  # 2
    word_small22 = "AA"  # 2

    big = 100  # big * 9
    large = 4000  # large * 9
    word_big = "ATTCCGATA"*big  # 900
    word_large = "ATTCCGATA"*large  # 36_000 > 10_000

    def check_time_memory(self, TM, time=2.0, peak=512.0):
        self.assertLess(TM.time, time)
        self.assertLess(TM.peak, peak)

    def test_search_empty_empty(self):  # Expectation: Not identifies empty word
        with TimerMemory(False) as TM:
            self.assertEqual(self.trie_empty.search(self.word_empty), "")
        self.check_time_memory(TM, 7.0)

    def test_search_standart_empty(self):  # Expectation: Not identifies standart word
        with TimerMemory(False) as TM:
            self.assertEqual(self.trie_empty.search(self.word_standart), "")
        self.check_time_memory(TM, 7.0)

    def test_search_small11(self):  # Expectation: Returns correct indexes ""
        with TimerMemory(False) as TM:
            self.assertEqual(self.trie_small_1.search(self.word_small11), "")
        self.check_time_memory(TM, 7.0)

    def test_search_small12(self):  # Expectation: Returns correct indexes 0
        with TimerMemory(False) as TM:
            self.assertEqual(self.trie_small_1.search(self.word_small12), "0")
        self.check_time_memory(TM, 7.0)

    def test_search_small21(self):  # Expectation: Returns correct indexes 0
        with TimerMemory(False) as TM:
            self.assertEqual(self.trie_small_2.search(self.word_small21), "0")
        self.check_time_memory(TM, 7.0)

    def test_search_small22(self):  # Expectation: Returns correct indexes ""
        with TimerMemory(False) as TM:
            self.assertEqual(self.trie_small_2.search(self.word_small22), "")
        self.check_time_memory(TM, 7.0)

    def test_search(self):  # Expectation: Returns correct indexes 0 3 3 4 4 6
        with TimerMemory(False) as TM:
            self.assertEqual(self.trie_standart.search(self.word_standart), "0 3 3 4 4 6")
        self.check_time_memory(TM, 7.0)

    def test_search_big(self):  # Expectation: Returns correct indexes
        text = "0 3 3 4 4 6"
        arr = np.array(list(map(int, text.split(" "))))
        for i in range(1, self.big):
            text += " " + " ".join(map(str, arr + (i * 9)))
        with TimerMemory(False) as TM:
            self.assertEqual(self.trie_standart.search(self.word_big), text)
        self.check_time_memory(TM, 7.0)

    def test_search_large(self):  # Expectation: Returns correct indexes
        text = "0 3 3 4 4 6"
        arr = np.array(list(map(int, text.split(" "))))
        for i in range(1, self.large):
            text += " " + " ".join(map(str, arr + (i * 9)))
        with TimerMemory(False) as TM:
            self.assertEqual(self.trie_standart.search(self.word_large), text)
        self.check_time_memory(TM, 7.0)

    def test_search_trie_big(self):  # Expectation: Returns correct indexes 0 0 1 2 5
        with TimerMemory(False) as TM:
            self.assertEqual(self.trie_big.search(self.word_standart), "0 0 1 2 5")
        self.check_time_memory(TM, 7.0)

    def test_search_big_trie_big(self):  # Expectation: Returns correct indexes
        text = "0 0 1 2 5"
        arr = np.array(list(map(int, text.split(" "))))
        for i in range(1, self.big):
            text += " " + " ".join(map(str, arr + (i * 9)))
        with TimerMemory(False) as TM:
            self.assertEqual(self.trie_big.search(self.word_big), "0 " + text)
        self.check_time_memory(TM, 7.0)

    def test_search_large_trie_big(self):  # Expectation: Returns correct indexes
        text = "0 0 0 1 2 5"
        arr = np.array(list(map(int, text.split(" "))))
        for i in range(1, self.large):
            # if i % 100 == 0:
            #     text += f" {i * 9}"
            if i >= self.large - 99:  # 10000 = 9901
                text += " " + " ".join(map(str, arr[1:] + (i * 9)))
            else:
                text += " " + " ".join(map(str, arr + (i * 9)))
        with TimerMemory(False) as TM:
            self.assertEqual(self.trie_big.search(self.word_large), text)
        self.check_time_memory(TM, 7.0)

    def test_search_pattern_True(self):  # Expectation: Returns True if word is pattern
        with TimerMemory(False) as TM:
            self.assertTrue(self.trie_standart.searchPattern(self.word_standart[:2]))  # Word = AT, Pattern = AT, Result = True
        self.check_time_memory(TM)

    def test_search_pattern_False(self):  # Expectation: Returns False if word is not pattern
        with TimerMemory(False) as TM:
            self.assertFalse(self.trie_standart.searchPattern(self.word_standart[:3]))  # Word = ATC, Pattern = AT, Result = False
        self.check_time_memory(TM)

    def test_startsWith_True(self):  # Expectation: Returns True if word is at least part of pattern (Only One pattern, not All)
        with TimerMemory(False) as TM:
            self.assertTrue(self.trie_standart.startsWith(self.word_standart[:2]))
        self.check_time_memory(TM)

    def test_startsWith_False(self):  # Expectation: Returns False if word is not even part of pattern (For example, if it is bigger than pattern)
        with TimerMemory(False) as TM:
            self.assertFalse(self.trie_standart.startsWith(self.word_standart))
        self.check_time_memory(TM)

    def test_str1(self):  # Expectation: Returns 0->1:C\n0->2:A\n2->3:T\n1->2:C\n1->3:G\n1->4:T
        with TimerMemory(False) as TM:
            text = "0->1:C\n0->2:A\n2->3:T\n1->2:C\n1->3:G\n1->4:T"
            self.assertEqual(str(self.trie_standart), text)
        self.check_time_memory(TM)

    def test_str2(self):  # Expectation: Returns C\nAT\nCC\nCG\nCT (But I don't know why I made it even possible, maybe just for fun)
        with TimerMemory(False) as TM:
            text = "C\nAT\nCC\nCG\nCT"
            self.assertEqual(str(self.trie_not_standart), text)
        self.check_time_memory(TM)


if __name__ == "__main__":  # pragma: no cover
    unittest.main()
