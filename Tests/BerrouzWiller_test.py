import unittest
import numpy as np

from Lab8.BerrouzWiller import BerrouzWiller
from Lab8.TimerMemory import TimerMemory
"""
4. Бонуснi бали
За пiдготовку тестових прикладiв (з правильними вiдповiдями), якi покривають усi крайнi
випадки i якi можна вважати достатньо повними, можна отримати до 4 бонусних балiв (до 2 бонусних
балiв для кожної задачi).
"""


class TestBerrouzWiller(unittest.TestCase):
    # ----------------------
    # 1 <= | Text | <= 1000;
    # Завершувати роботу за час, що не перевищує 2 секунд на кожен тестовий приклад.
    # Програма повинна використовувати не бiльше 512 Мб пам’ятi.

    # 1 <= | Transform | <= 1000000;
    # Завершувати роботу за час, що не перевищує 15 секунд на кожен тестовий приклад.
    # Програма повинна використовувати не бiльше 512 Мб пам’ятi.

    # 1 <= | Text | <= 1e6;
    # 1 <= | p | <= 1000;
    # Завершувати роботу за час, що не перевищує 25 секунд на кожен тестовий приклад.
    # Програма повинна використовувати не бiльше 512 Мб пам’ятi.
    # ----------------------
    # TODO
    # | Text | >= 1e6
    # | p | >= 1000
    # | Text | <= 1
    # | p | <= 1
    # ----------------------
    word_empty = ""  # 0
    word_small = "A"  # 1
    word_standart = "ATTCCGATA"  # 9
    word_large = word_standart * (int(1e6)//9)  # 9e6

    pattern = "CG"  # 2
    pattern_big = pattern * int(1e3)  # 2e3

    bw_empty_main = BerrouzWiller(word_empty)
    bw_empty_count = BerrouzWiller(word_empty, pattern)

    bw_small_main = BerrouzWiller(word_small)
    bw_small_count = BerrouzWiller(word_small, pattern)

    bw_standart_main = BerrouzWiller(word_standart)
    bw_standart_count = BerrouzWiller(word_standart, pattern)

    # bw_large_main = BerrouzWiller(word_large)
    # bw_large_count = BerrouzWiller(word_large, pattern)

    def check_time_memory(self, TM, time=2.0, peak=512.0):
        self.assertLess(TM.time, time)
        self.assertLess(TM.peak, peak)

    def test_empty_main(self):  # Expectation: Empty word
        with TimerMemory(False) as TM:
            self.assertEqual(str(self.bw_empty_main), "")
        self.check_time_memory(TM, 2.0)

    def test_empty_count(self):  # Expectation: 0
        with TimerMemory(False) as TM:
            self.assertEqual(str(self.bw_empty_count), '0')
        self.check_time_memory(TM, 25.0)

    def test_small_main(self):  # Expectation: Word
        with TimerMemory(False) as TM:
            self.assertEqual(str(self.bw_small_main), "")
        self.check_time_memory(TM, 2.0)

    def test_small_count(self):  # Expectation: 0
        with TimerMemory(False) as TM:
            self.assertEqual(str(self.bw_small_count), '0')
        self.check_time_memory(TM, 25.0)

    def test_standart_main(self):  # Expectation: Word
        with TimerMemory(False) as TM:
            self.assertEqual(str(self.bw_standart_main), "")
        self.check_time_memory(TM, 2.0)

    def test_standart_count(self):  # Expectation: 1
        with TimerMemory(False) as TM:
            self.assertEqual(str(self.bw_standart_count), '1')
        self.check_time_memory(TM, 25.0)

    # def test_large_main(self):  # Expectation: Word
    #     with TimerMemory(False) as TM:
    #         self.assertEqual(str(self.bw_large_main), "")
    #     self.check_time_memory(TM, 2.0)

    # def test_large_count(self):  # Expectation: 1e6
    #     with TimerMemory(False) as TM:
    #         self.assertEqual(str(self.bw_large_count), str(int(1e6)))
    #     self.check_time_memory(TM, 25.0)


if __name__ == "__main__":  # pragma: no cover
    unittest.main()
