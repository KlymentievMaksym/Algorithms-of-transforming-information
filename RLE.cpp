#include <iostream>
#include <fstream>
#include <bitset>
#include <vector>

#include <cstdint>
// #include <windows.h>

using namespace std;

class RLE 
{
    public:
        // 1. Кодер повинен приймати на вхід ім'я файла для кодування та (опціонально) ім'я файла для зберігання закодованого результату.
        // 2. Якщо користувач не надав ім'я файла для зберігання закодованого результату, кодер повинен створити такий файл сам, додавши до імені оригінального файлу розширення ".rle"
        // 3. Вхідний файл повинен трактуватись як файл двійкових даних (потік байтів).
        // 4. Стиснені дані повинні занисуватись у вихідний файл як у файл двійкових даних (потік байтів)
        // 5. Кодер може вставляли у вихідний файл довільні необхідні йому метадані (наприклад, заголовки чи якісь службові команди, які ви передбачаєте своєю реалізацією)

        // 1. Кодер повинен приймати на вхід ім'я файла для кодування та (опціонально) ім'я файла для зберігання закодованого результату.
        int Encoder(string filename_read, string filename_write = "")
        {
            // 2. Якщо користувач не надав ім'я файла для зберігання закодованого результату, кодер повинен створити такий файл сам, додавши до імені оригінального файлу розширення ".rle"
            if (filename_write == "")
            {
                filename_write = filename_read;
                size_t lastindex_dot = filename_write.find_last_of(".");
                filename_write = filename_write.substr(0, lastindex_dot)  + ".rle";
            }
            cout << "[I] Input: '" << filename_read << "'\n";
            cout << "[O] Output: '" << filename_write << "'\n";

            // 3. Вхідний файл повинен трактуватись як файл двійкових даних (потік байтів).
            // streampos size;
            // char * memblock;

            ifstream fr(filename_read, ios::binary); //  | ios::ate
            if (!fr.is_open())
            {
                cerr << "[!] Error opening the file!\n";
                return 1;
            }
            // size = fr.tellg();
            // memblock = new char [size];
            // fr.seekg(0, ios::beg);
            // fr.read(memblock, size);
            // fr.close();

            // cout << "the entire file content is in memory\n";
            // cout << memblock;

            // vector<char> buffer(istreambuf_iterator<char>(fr), {});

            // 4. Стиснені дані повинні занисуватись у вихідний файл як у файл двійкових даних (потік байтів)        
            ofstream fw(filename_write, ios::binary);
            if (!fw.is_open())
            {
                cerr << "Error opening the file!\n";
                return 1;
            }

            // int char_count = 1;
            // char buffer[1];
            // // char buffer_i[1];

            // float data[8] = {0.00001, 0.00002, 0.00003, 0.00004, 0.00005, 0.00006, 0.00007, 0.00008};

            // for (int i=0; i < size; i++)
            // {
            //     buffer[0] = memblock[i];
            //     while (memblock[i] == memblock[i+1])
            //     {
            //         i++;
            //         char_count++;
            //     }
            //     // buffer_i[0] = char(char_count);
            //     // cout << char_count;
            //     char_count = 1;
            //     // fw.write((char *) bitset<8>(char_count), 1);
            //     if (i < 8)
            //         fw.write((char*) &data[i], sizeof(float));
            //     fw.write(buffer, 1);
            //     cout << memblock[i];
            // }
            // cout << "\n";

            // int char_count = 1;
            
            // for (int it = 0; it < size(buffer); it++)
            // {
            //     while (buffer[it] == buffer[it+1])
            //         it++;
            //         char_count++;
            //     cout << buffer[it];
            // }
            // int a[4] = {100023, 23, 42, 13};
            // fw.write((char*) &a, sizeof(a));


            // uint8_t value = 255;  // 255 in one byte (0xFF)
            // uint8_t value1 = 254;  // 255 in one byte (0xFF)
            // uint8_t value2 = 253;  // 255 in one byte (0xFF)
            // fw.write(reinterpret_cast<char*>(&value), sizeof(value));
            // fw.write(reinterpret_cast<char*>(&value1), sizeof(value1));
            // fw.write(reinterpret_cast<char*>(&value2), sizeof(value2));
            // Encode
            string s;
            while (getline(fr, s))
            {
                // cout << "\nLine\n";
                int count = 1;
                for (int i = 0; i < size(s); i++)
                {
                    while (i < size(s) - 1 and s[i] == s[i+1])
                    {
                        count++;
                        i++;
                        // if (count >= 2^7-1)
                        //     break;
                    }
                    uint8_t cont = (1 << 7) | count;
                    uint8_t si = s[i];
                    fw.write(reinterpret_cast<char*>(&cont), sizeof(cont));
                    fw.write(reinterpret_cast<char*>(&si), sizeof(si));
                    // cout << count;
                    // cout << count << "\n";
                    // cout << bitset<1>(1) << bitset<7>(count) << "\n";
                    // cout << s[i];
                    // cout << s[i] << "\n";
                    // cout << bitset<8>(s[i]) << "\n" << "\n";
                    // fw << bitset<1>(1) << bitset<7>(count);
                    // fw << bitset<8>(s[i]);
                    count = 1;
                }
                // cout << "\n";
                uint8_t cont = (1 << 7) | count;
                uint8_t si = '\n';
                fw.write(reinterpret_cast<char*>(&cont), sizeof(cont));
                fw.write(reinterpret_cast<char*>(&si), sizeof(si));
                // fw << bitset<1>(1) << bitset<7>(count);
                // fw << bitset<8>('\n');
            }   

            // 5. Кодер може вставляли у вихідний файл довільні необхідні йому метадані (наприклад, заголовки чи якісь службові команди, які ви передбачаєте своєю реалізацією)
            // delete[] memblock;
            fr.close();
            fw.close();
            return 0;
        };

        // 1. Декодер повинен приймати на вхід ім'я стисненого файлу та ім'я файла для зберігання розпакованого результату.
        // 2. (Опціонально) Декодер може запропонувати користувачу варіант імені для декодованого файлу: наприклад, якщо закодований файл має розширення 
        // ".rle" -- відкинувши таке розширення; або, якщо закодований файл у метаданих зберігає ім'я оригінального файлу, -- запропонувати збережене ім'я. 
        // Але, в будь-якому випадку, користувач повинен або сам зафіксувати ім'я файлу виходу, або свідомо погодитись із пропозицією такого імені.
        // 3. Файли входу та виходу повинні трактуватись як файли двійкових даних (потоки байтів)
        // 4. Якщо ваша реалізація передбачає якісь метадані у стиснутому файлі, декодер повинен перевірити їх коректність та, у разі їх некоректності, вивести відповідне повідомлення про помилку.
        // 5. Якшо декодер виявив неправильну команду алгоритму стиснення у вхідному файлі (команда каже зчитати послідовність байтів, яка виходить за кінець файлу), декодер повинен вивести відповідне повідомлення про помилку.
        // 6. У випадку виникнення помилки декодування декодер може як повністю зупинити свою роботу, так і спробувати декодувати те, що зможе. Вибір поведінки залишається на ваш розсуд.

        // 1. Декодер повинен приймати на вхід ім'я стисненого файлу та ім'я файла для зберігання розпакованого результату.
        int Decoder(string filename_read, string filename_write = "")
        {
            // 2. (Опціонально) Декодер може запропонувати користувачу варіант імені для декодованого файлу: наприклад, якщо закодований файл має розширення 
            // ".rle" -- відкинувши таке розширення; або, якщо закодований файл у метаданих зберігає ім'я оригінального файлу, -- запропонувати збережене ім'я. 
            // Але, в будь-якому випадку, користувач повинен або сам зафіксувати ім'я файлу виходу, або свідомо погодитись із пропозицією такого імені.
            if (filename_write == "")
            {
                filename_write = filename_read;
                size_t lastindex_dot = filename_write.find_last_of(".");
                filename_write = filename_write.substr(0, lastindex_dot)  + ".txt";
                cout << "[I] Input: '" << filename_read << "'\n";
                cout << "[O] Output: '" << filename_write << "'\n";
            }

            // 3. Файли входу та виходу повинні трактуватись як файли двійкових даних (потоки байтів)
            ifstream fr(filename_read, ios::binary);
            if (!fr.is_open())
            {
                cerr << "Error opening the file!\n";
                return 1;
            }

            // Decode
            string text = "";
            while (!fr.eof( ))
            {
                uint8_t value;
                fr.read(reinterpret_cast<char*>(&value), sizeof(value));
                if (bitset<8>(value)[7] == 1)
                {
                    int count = static_cast<int>(value) - 128;
                    fr.read(reinterpret_cast<char*>(&value), sizeof(value));
                    if (bitset<8>(value)[7] == 0)
                    {
                        for (int cnt = 0; cnt < count; cnt++)
                        {
                            text = text + static_cast<char>(value);
                        }
                    }
                }
            }
            fr.close();

            // cout << text;
            if (text != "")
            {
                // 3. Файли входу та виходу повинні трактуватись як файли двійкових даних (потоки байтів)
                ofstream fw(filename_write, ios::binary);
                if (!fw.is_open())
                {
                    cerr << "Error opening the file!\n";
                    return 1;
                }

                fw << text;
                fw.close();
            }
            // cout << fr.tellg() << "\n";
            // cout << value << "\n";
            // cout << static_cast<int>(value)  << "\n";
            // fr.read(reinterpret_cast<char*>(&value), sizeof(value));
            // cout << static_cast<int>(value)  << "\n";
            // fr.read(reinterpret_cast<char*>(&value), sizeof(value));
            // cout << static_cast<int>(value)  << "\n";
            // fr.read(reinterpret_cast<char*>(&value), sizeof(value));
            // cout << static_cast<int>(value)  << "\n";
            // vector<unsigned char> buffer(istreambuf_iterator<char>(fr), {});

            // unsigned char character;
            // unsigned long integer = 0;
            // string main_text = "";
            // string text = "";
            // int j;
            // for (j = 0; j < size(buffer)-7; j = j + 8)
            // {
            //     vector<unsigned char> slice(buffer.begin() + j, buffer.begin() + j + 8);
            //     string s = "";
            //     if (slice[0] == '1')
            //     {
            //         for (unsigned long k = 0; k < integer; k++)
            //         {
            //             cout << text;
            //             main_text = main_text + text;
            //         }
            //         integer = 0;
            //         text = "";
            //         for (int i = 1; i < size(slice); i++)
            //         {
            //             s = s + static_cast<char>(slice[i]);
            //         }
            //         bitset<7> byt;
            //         byt = static_cast<bitset<7>>(s);
            //         integer = byt.to_ulong();
            //     }
            //     else
            //     {
            //         if (slice[0] == '0')
            //         {
            //             for (auto it : slice)
            //             {
            //                 s = s + static_cast<char>(it);
            //             }
            //             bitset<8> byt;
            //             byt = static_cast<bitset<8>>(s);
            //             unsigned long i = byt.to_ulong(); 
            //             character = static_cast<unsigned char>( i );
            //             text = text + static_cast<char>(character);
            //         }
            //     }
            // }
            // cout << "\n" << j << " " << size(buffer) << "\n";
            // if (j != size(buffer))
            // {
            //     cout << "[!] Something wrong after col (Seems like not full byte) " << j << "\n[?] Change with skipping it? [N(/Y))]\n>>> ";
            //     string ask;
            //     cin >> ask;
            //     if (ask != "Y")
            //     {
            //         main_text = "";
            //     }
            // }
            // else
            // {
            //     if (integer != 0)
            //     {
            //         for (unsigned long k = 0; k < integer; k++)
            //         {
            //             cout << text;
            //             main_text = main_text + text;
            //         }
            //         integer = 0;
            //         text = "";
            //     }
            // }

            // if (main_text != "")
            // {
            //     // 3. Файли входу та виходу повинні трактуватись як файли двійкових даних (потоки байтів)
            //     ofstream fw(filename_write, ios::binary);
            //     if (!fw.is_open())
            //     {
            //         cerr << "Error opening the file!\n";
            //         return 1;
            //     }

            //     fw << main_text;
            //     fw.close();
            // }

            // 4. Якщо ваша реалізація передбачає якісь метадані у стиснутому файлі, декодер повинен перевірити їх коректність та, у разі їх некоректності, вивести відповідне повідомлення про помилку.
            // 5. Якшо декодер виявив неправильну команду алгоритму стиснення у вхідному файлі (команда каже зчитати послідовність байтів, яка виходить за кінець файлу), декодер повинен вивести відповідне повідомлення про помилку.
            // 6. У випадку виникнення помилки декодування декодер може як повністю зупинити свою роботу, так і спробувати декодувати те, що зможе. Вибір поведінки залишається на ваш розсуд.
            return 0;
        };

};


int main(int argc, char* argv[])
{
    RLE rle;

    // cout << "You have entered " << argc
    //      << " arguments:" << endl;

    for (int i = 1; i < argc; i++)
    {
        cout << "File " << i << ": " << argv[i]
             << endl;
    }

    while (true)
    {
        cout << "\n[?] What to do with it?\n1: Encode, 2: Decode, 0: Exit\n>>> ";
        string ask;
        cin >> ask;
        // cout << ask << "\n";

        if (ask == "0")
        {
            return 0;
        }
        else if (ask == "1")
        {
            for (int i = 1; i < argc; i++)
            {
                rle.Encoder(argv[i]);
            }
        }
        else if (ask == "2")
        {
            for (int i = 1; i < argc; i++)
            {
                rle.Decoder(argv[i]);
            }
        }
        else
        {
            cout << "[!] There is no " << ask << " command\n";
        }
    }
}
