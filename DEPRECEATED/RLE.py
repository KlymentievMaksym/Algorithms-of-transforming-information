

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
        text_encoded = ""
        with open(self.filename_read, 'r') as rd:
            text_to_encode = rd.read()
            print(text_to_encode)
        for char in text_to_encode:
            encoded_char = format(ord(char), "08b")
            if len(encoded_char) != 8:
                print(f"Wrong character: '{char}', omitting...")
            else:
                text_encoded += encoded_char
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
                ask = input("[!] There is '.rle' in file name, remove it? (N(/Y/RENAME)):\n>>> ")
                if ask.upper() == "Y":
                    self.filename_write = self.filename_write[:-3]
                elif ask.upper() == "RENAME":
                    self.rename
            else:
                ask = input(f"[!] There is no file name to write, use {self.filename_write}? (Y(/RENAME))")
                if ask.upper() == "RENAME":
                    self.rename
        else:
            self.filename_write = filename_write
        self.start

    @property
    def rename(self):
        ask = input("[ ] Write new file name:\n>>> ")
        confirm = input(f"You typed: {ask}\nConfrim? (Y/N)\n>>> ")
        while confirm.upper() != "Y":
            ask = input("[ ] Write new file name:\n>>> ")
            confirm = input(f"You typed: {ask}\nConfrim? (Y/N)\n>>> ")
        self.filename_write = ask

    @property
    def start(self):
        with open(self.filename_read, 'r') as rd:
            text_to_decode = rd.read()
        for i in range(0, len(text_to_decode), 8):
            char = text_to_decode[i:i+8]
            list_of_chars = [char]
        text_decoded = "".join(chr(int(i, 2)) for i in list_of_chars)
        print(text_decoded)
        with open(self.filename_write, 'w') as wt:
            wt.write(text_decoded)

    def __str__(self):
        return f"Decoder from {self.filename_read} to {self.filename_write}"

