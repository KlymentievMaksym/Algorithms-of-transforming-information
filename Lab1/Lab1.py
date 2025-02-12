from os import getcwd
from sys import path

MAIN_DIRNAME = "Algorithms-of-transforming-information"
PATH = getcwd()

IMPORT_PATH = PATH[:PATH.find(MAIN_DIRNAME) + len(MAIN_DIRNAME)]
path.append(IMPORT_PATH)

from RLE.Encoder import Encoder as Ecd
from RLE.Decoder import Decoder as Dcd

print(Ecd)
print(Dcd)
