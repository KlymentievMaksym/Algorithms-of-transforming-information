import unittest

if __name__ == "__main__":  # pragma: no cover
    suite = unittest.TestLoader().discover('.', pattern="*test*")
    unittest.TextTestRunner(verbosity=2).run(suite)
