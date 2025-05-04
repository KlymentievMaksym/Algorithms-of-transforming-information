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
    trie_standart = PrefixTrie(["CC", "CG", "C", "CT", "AT"])
    trie_big = PrefixTrie(["ATTC", "GATA", "TCCGA", "CT", "TTCCGA", "ATTCCGATA", "ATTCCGATA"*100])
    trie_not_standart = PrefixTrie(["CC", "CG", "C", "CT", "AT"], "Nonsense")
    word_standart = "ATTCCGATA"  # 9
    word_big = "ATTCCGATA"*100  # 900
    word_large = "ATTCCGATA"*10000  # 90000

    def check_time_memory(self, TM):
        self.assertLess(TM.time, 2.0)
        self.assertLess(TM.peak, 512.0)

    def test_search(self):
        with TimerMemory(False) as TM:
            self.assertEqual(self.trie_standart.search(self.word_standart), "0 3 3 4 4 6")
        self.check_time_memory(TM)

    def test_search_big(self):
        text = "0 3 3 4 4 6"
        arr = np.array(list(map(int, text.split(" "))))
        for i in range(1, 100):
            text += " " + " ".join(map(str, arr + (i * 9)))
        with TimerMemory(False) as TM:
            self.assertEqual(self.trie_standart.search(self.word_big), text)
        self.check_time_memory(TM)

    def test_search_large(self):
        text = "0 3 3 4 4 6"
        arr = np.array(list(map(int, text.split(" "))))
        for i in range(1, 10000):
            text += " " + " ".join(map(str, arr + (i * 9)))
        with TimerMemory(False) as TM:
            self.assertEqual(self.trie_standart.search(self.word_large), text)
        self.check_time_memory(TM)

    def test_search_trie_big(self):
        with TimerMemory(False) as TM:
            self.assertEqual(self.trie_big.search(self.word_standart), "0 0 1 2 5")
        self.check_time_memory(TM)

    def test_search_big_trie_big(self):
        text = "0 0 1 2 5"
        arr = np.array(list(map(int, text.split(" "))))
        for i in range(1, 100):
            text += " " + " ".join(map(str, arr + (i * 9)))
        with TimerMemory(False) as TM:
            self.assertEqual(self.trie_big.search(self.word_big), "0 " + text)
        self.check_time_memory(TM)

    def test_search_large_trie_big(self):
        text = "0 0 0 1 2 5"
        arr = np.array(list(map(int, text.split(" "))))
        for i in range(1, 10000):
            # if i % 100 == 0:
            #     text += f" {i * 9}"
            if i >= 9901:
                text += " " + " ".join(map(str, arr[1:] + (i * 9)))
            else:
                text += " " + " ".join(map(str, arr + (i * 9)))
        with TimerMemory(False) as TM:
            self.assertEqual(self.trie_big.search(self.word_large), text)
        self.check_time_memory(TM)

    def test_search_pattern_True(self):
        with TimerMemory(False) as TM:
            self.assertTrue(self.trie_standart.searchPattern(self.word_standart[:2]))
        self.check_time_memory(TM)

    def test_search_pattern_False(self):
        with TimerMemory(False) as TM:
            self.assertFalse(self.trie_standart.searchPattern(self.word_standart[:3]))
        self.check_time_memory(TM)

    def test_startsWith_True(self):
        with TimerMemory(False) as TM:
            self.assertTrue(self.trie_standart.startsWith(self.word_standart[:2]))
        self.check_time_memory(TM)

    def test_startsWith_False(self):
        with TimerMemory(False) as TM:
            self.assertFalse(self.trie_standart.startsWith(self.word_standart))
        self.check_time_memory(TM)

    def test_str1(self):
        with TimerMemory(False) as TM:
            text = "0->1:C\n0->2:A\n2->3:T\n1->2:C\n1->3:G\n1->4:T"
            self.assertEqual(str(self.trie_standart), text)
        self.assertLess(TM.time, 2.0)
        self.assertLess(TM.peak, 512.0)

    def test_str2(self):
        with TimerMemory(False) as TM:
            text = "C\nAT\nCC\nCG\nCT"
            self.assertEqual(str(self.trie_not_standart), text)
        self.check_time_memory(TM)


if __name__ == "__main__":  # pragma: no cover
    unittest.main()
