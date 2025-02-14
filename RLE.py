

class Encoder:
    def __init__(self, filename_read: str, filename_write: str = None):
        self.filename_read = filename_read
        if filename_write is None:
            self.filename_write = filename_read + ".rle"
        else:
            self.filename_write = filename_write
        self.start

    @property
    def start(self):
        with open(self.filename_read, 'r') as rd:
            text_to_encode = rd.read()
            print(text_to_encode)
        text_encoded = "".join(format(ord(char), "08b") for char in text_to_encode)
        with open(self.filename_write, 'w') as wt:
            wt.write(text_encoded)

    def __str__(self):
        return f"Encoder from {self.filename_read} to {self.filename_write}"


class Decoder:
    def __init__(self, filename_read: str, filename_write: str = None):
        self.filename_read = filename_read
        if filename_write is None:
            self.filename_write = filename_read
            if ".rle" in filename_read:
                ask = input("There is '.rle' in file name, remove it? (Y/N):\n>>> ")
                if ask == "Y":
                    self.filename_write = self.filename_write[:-3]
        else:
            self.filename_write = filename_write
        self.start

    @property
    def start(self):
        with open(self.filename_read, 'r') as rd:
            text_to_decode = rd.read()
            # print(text_to_decode)
        list_of_chars = [text_to_decode[i:i+8] for i in range(0, len(text_to_decode), 8)]
        text_decoded = "".join(chr(int(i, 2)) for i in list_of_chars)
        print(text_decoded)
        with open(self.filename_write, 'w') as wt:
            wt.write(text_decoded)

    def __str__(self):
        return f"Decoder from {self.filename_read} to {self.filename_write}"
