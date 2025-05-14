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
    # | Text | >= 1e3 (straight)
    # | Text | >= 1e6 (reverse)
    # | p | >= 1000
    # | Text | <= 1
    # | p | <= 1
    # ----------------------

    task_1_1_word = "AAAA$"
    task_1_1_result = "AAAA$"

    task_1_2_word = "AGGTCAACC$"
    task_1_2_result = "CCA$CTAAGG"

    task_2_1_word = "AC$A"
    task_2_1_result = "ACA$"

    task_2_2_word = "AC$GATCTG"
    task_2_2_result = "ACGTTGCA$"

    task_3_1_word = "AGCCACA"
    task_3_1_pattern = "CA"
    task_3_1_result = "2"

    task_3_2_word = "AAGGGCGTCGGTGC"
    task_3_2_pattern = "GG"
    task_3_2_result = "3"

    word_empty = ""  # 0
    word_small = "A$"  # 1
    word_small_reverse = "A$"
    word_standart = "ATTCCGATA$"  # 9
    word_standart_reverse = "ATG$TCCATA"

    coeff = int(1e3)
    word_large = word_standart[:-1] * coeff + "$"  # 8e3 + 1
    word_large_reverse = "A" + "T" * coeff + "G" * coeff + "A" * (coeff - 1) + "$" + "T" * coeff + "C" * coeff + "C" * coeff + "A" * coeff + "T" * coeff + "A" * coeff

    coeff = int(.25e6)
    word_large_2 = word_standart[:-1] * coeff + "$"  # 2e6 + 1
    word_large_2_reverse = "A" + "T" * coeff + "G" * coeff + "A" * (coeff - 1) + "$" + "T" * coeff + "C" * coeff + "C" * coeff + "A" * coeff + "T" * coeff + "A" * coeff

    coeff = int(2e3)
    word_large_3 = word_standart[:-1] * coeff + "$"  # 1.8e4 + 1

    pattern = "CG"  # 2

    def check_time_memory(self, TM, time=2.0, peak=512.0):
        self.assertLess(TM.time, time)
        self.assertLess(TM.peak, peak)

    def test_task_1_1(self):  # Expectation: "AAAA$"
        with TimerMemory(False) as TM:
            bw_task_1_1 = BerrouzWiller(self.task_1_1_word).run
            self.assertEqual(str(bw_task_1_1), self.task_1_1_result)
        self.check_time_memory(TM, 2.0)

    def test_task_1_2(self):  # Expectation: "CCA$CTAAGG"
        with TimerMemory(False) as TM:
            bw_task_1_2 = BerrouzWiller(self.task_1_2_word).run
            self.assertEqual(str(bw_task_1_2), self.task_1_2_result)
        self.check_time_memory(TM, 2.0)

    def test_task_2_1(self):  # Expectation: "ACA$"
        with TimerMemory(False) as TM:
            bw_task_2_1 = BerrouzWiller(self.task_2_1_word, reverse=True).run
            self.assertEqual(str(bw_task_2_1), self.task_2_1_result)
        self.check_time_memory(TM, 15.0)

    def test_task_2_2(self):  # Expectation: "ACGTTGCA$"
        with TimerMemory(False) as TM:
            bw_task_2_2 = BerrouzWiller(self.task_2_2_word, reverse=True).run
            self.assertEqual(str(bw_task_2_2), self.task_2_2_result)
        self.check_time_memory(TM, 15.0)

    def test_task_3_1(self):  # Expectation: "2"
        with TimerMemory(False) as TM:
            bw_task_3_1 = BerrouzWiller(self.task_3_1_word, self.task_3_1_pattern).run
            self.assertEqual(str(bw_task_3_1), self.task_3_1_result)
        self.check_time_memory(TM, 25.0)

    def test_task_3_2(self):  # Expectation: "3"
        with TimerMemory(False) as TM:
            bw_task_3_2 = BerrouzWiller(self.task_3_2_word, self.task_3_2_pattern).run
            self.assertEqual(str(bw_task_3_2), self.task_3_2_result)
        self.check_time_memory(TM, 25.0)

    def test_empty_main(self):  # Expectation: Empty word
        with TimerMemory(False) as TM:
            bw_empty_main = BerrouzWiller(self.word_empty).run
            self.assertEqual(str(bw_empty_main), "")
        self.check_time_memory(TM, 2.0)

    def test_empty_reverse(self):  # Expectation: ""
        with TimerMemory(False) as TM:
            bw_empty_reverse = BerrouzWiller(self.word_empty, reverse=True).run
            self.assertEqual(str(bw_empty_reverse), "")
        self.check_time_memory(TM, 15.0)

    def test_empty_count(self):  # Expectation: 0
        with TimerMemory(False) as TM:
            bw_empty_count = BerrouzWiller(self.word_empty, self.pattern).run
            self.assertEqual(str(bw_empty_count), '0')
        self.check_time_memory(TM, 25.0)

    def test_small_main(self):  # Expectation: Word "A"
        with TimerMemory(False) as TM:
            bw_small_main = BerrouzWiller(self.word_small).run
            self.assertEqual(str(bw_small_main), self.word_small_reverse)
        self.check_time_memory(TM, 2.0)

    def test_small_reverse(self):  # Expectation: ""
        with TimerMemory(False) as TM:
            bw_small_reverse = BerrouzWiller(self.word_small_reverse, reverse=True).run
            self.assertEqual(str(bw_small_reverse), self.word_small)
        self.check_time_memory(TM, 15.0)

    def test_small_count(self):  # Expectation: 0
        with TimerMemory(False) as TM:
            bw_small_count = BerrouzWiller(self.word_small, self.pattern).run
            self.assertEqual(str(bw_small_count), '0')
        self.check_time_memory(TM, 25.0)

    def test_standart_main(self):  # Expectation: Word "TGATCCATA"
        with TimerMemory(False) as TM:
            bw_standart_main = BerrouzWiller(self.word_standart).run
            self.assertEqual(str(bw_standart_main), self.word_standart_reverse)
        self.check_time_memory(TM, 2.0)

    def test_standart_reverse(self):  # Expectation: ""
        with TimerMemory(False) as TM:
            bw_standart_reverse = BerrouzWiller(self.word_standart_reverse, reverse=True).run
            self.assertEqual(str(bw_standart_reverse), self.word_standart)
        self.check_time_memory(TM, 15.0)

    def test_standart_count(self):  # Expectation: 1
        with TimerMemory(False) as TM:
            bw_standart_count = BerrouzWiller(self.word_standart, self.pattern).run
            self.assertEqual(str(bw_standart_count), '1')
        self.check_time_memory(TM, 25.0)

    def test_large_main(self):  # Expectation: Word
        with TimerMemory(False) as TM:
            bw_large_main = BerrouzWiller(self.word_large).run
            self.assertEqual(str(bw_large_main), self.word_large_reverse)
        self.check_time_memory(TM, 2.0)

    def test_large_reverse(self):  # Expectation: Word
        with TimerMemory(False) as TM:
            bw_large_reverse = BerrouzWiller(self.word_large_2_reverse, reverse=True).run

            self.assertEqual(str(bw_large_reverse), self.word_large_2)
        self.check_time_memory(TM, 15.0)

    def test_large_count(self):  # Expectation: 2e3
        with TimerMemory(False) as TM:
            bw_large_count = BerrouzWiller(self.word_large_3, self.pattern).run
            self.assertEqual(str(bw_large_count), str(int(2e3)))
        self.check_time_memory(TM, 25.0)


if __name__ == "__main__":  # pragma: no cover
    unittest.main()
