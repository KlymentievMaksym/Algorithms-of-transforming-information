import unittest
from Lab7.PrefixTrie import PrefixTrie


class TestPrefixTrie(unittest.TestCase):
    trie_standart = PrefixTrie(["apple", "app", "ape", "appl"])

    def test_search(self):
        self.assertTrue(self.trie_standart.search("apple"))
        self.assertFalse(self.trie_standart.search("apples"))

    def test_startsWith(self):
        self.assertTrue(self.trie_standart.startsWith("ap"))
        self.assertFalse(self.trie_standart.startsWith("apes"))


if __name__ == "__main__":  # pragma: no cover
    unittest.main()
