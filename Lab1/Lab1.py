from os import getcwd
from sys import path

MAIN_DIRNAME = "Algorithms-of-transforming-information"
PATH = getcwd()

IMPORT_PATH = PATH[:PATH.find(MAIN_DIRNAME) + len(MAIN_DIRNAME)]
path.append(IMPORT_PATH)

from RLE import Encoder as Ecd, Decoder as Dcd

print(Ecd)
Ecd(IMPORT_PATH + "\\Lab1\\Lab1.txt")
print(Dcd)
Dcd(IMPORT_PATH + "\\Lab1\\Lab1.txt.rle", IMPORT_PATH + "\\Lab1\\Lab1_result.txt")
