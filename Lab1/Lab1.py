from os import getcwd
from sys import path

MAIN_DIRNAME = "Algorithms-of-transforming-information"
PATH = getcwd()

IMPORT_PATH = PATH[:PATH.find(MAIN_DIRNAME) + len(MAIN_DIRNAME)]
IMPORT_PATH_LAB = IMPORT_PATH + "\\Lab1\\"
path.append(IMPORT_PATH)

from RLE import Encoder as Ecd, Decoder as Dcd

print(Ecd)
Ecd(IMPORT_PATH_LAB + "Lab1.txt")
print(Dcd)
Dcd(IMPORT_PATH_LAB + "Lab1.txt.rle", IMPORT_PATH_LAB + "Lab1_result.txt")
# Dcd(IMPORT_PATH_LAB + "Lab1.txt.rle")
