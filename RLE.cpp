#include <iostream>
#include <fstream>
#include <bitset>
#include <vector>

#include <cstdint> // uint8_t
#include <sstream> // stringstream

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
            ifstream fr(filename_read, ios::binary);
            if (!fr.is_open())
            {
                cerr << "[!] Error opening the file '" << filename_read << "'!\n";
                return 1;
            }

            // 4. Стиснені дані повинні занисуватись у вихідний файл як у файл двійкових даних (потік байтів)        
            ofstream fw(filename_write, ios::binary);
            if (!fw.is_open())
            {
                cerr << "[!] Error opening the file '" << filename_write << "'!\n";
                return 1;
            }

            // Encode
            string s;
            while (getline(fr, s))
            {
                int count = 1;
                for (int i = 0; i < size(s); i++)
                {
                    while (i < size(s) - 1 and s[i] == s[i+1])
                    {
                        count++;
                        i++;
                        if (count >= 127)
                        {
                            break;
                        }
                    }
                    uint8_t cont = (1 << 7) | count;
                    uint8_t si = s[i];
                    fw.write(reinterpret_cast<char*>(&cont), sizeof(cont));
                    fw.write(reinterpret_cast<char*>(&si), sizeof(si));
                    count = 1;
                }
                uint8_t cont = (1 << 7) | count;
                uint8_t si = '\n';
                fw.write(reinterpret_cast<char*>(&cont), sizeof(cont));
                fw.write(reinterpret_cast<char*>(&si), sizeof(si));
            }   

            // 5. Кодер може вставляли у вихідний файл довільні необхідні йому метадані (наприклад, заголовки чи якісь службові команди, які ви передбачаєте своєю реалізацією)
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
                // filename_write = filename_write.substr(0, lastindex_dot)  + ".txt";
                filename_write = filename_write.substr(0, lastindex_dot);
                cout << "[I] Input: '" << filename_read << "'\n";
                cout << "[O] Output: '" << filename_write << "'\n";
            }

            // 3. Файли входу та виходу повинні трактуватись як файли двійкових даних (потоки байтів)
            ifstream fr(filename_read, ios::binary);
            if (!fr.is_open())
            {
                cerr << "[!] Error opening the file '" << filename_read << "'!\n";
                return 1;
            }

            // Decode
            string text = "";
            string text_not_decoded = "";
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
                else if (bitset<8>(value)[7] == 0)
                {
                    text_not_decoded = text_not_decoded + static_cast<char>(value);
                }
            }
            fr.close();

            // cout << text << "\n";
            // cout << text_not_decoded << "\n";
            if (text != "")
            {
                // 3. Файли входу та виходу повинні трактуватись як файли двійкових даних (потоки байтів)
                ofstream fw(filename_write, ios::binary);
                if (!fw.is_open())
                {
                    cerr << "[!] Error opening the file '" << filename_write << "'!\n";
                    return 1;
                }

                fw << text;
                fw.close();
            }
            else
            {
                cerr << "[!] There is no text which can be decoded\n";
                return 2;
            }

            // 4. Якщо ваша реалізація передбачає якісь метадані у стиснутому файлі, декодер повинен перевірити їх коректність та, у разі їх некоректності, вивести відповідне повідомлення про помилку.
            // 5. Якшо декодер виявив неправильну команду алгоритму стиснення у вхідному файлі (команда каже зчитати послідовність байтів, яка виходить за кінець файлу), декодер повинен вивести відповідне повідомлення про помилку.
            // 6. У випадку виникнення помилки декодування декодер може як повністю зупинити свою роботу, так і спробувати декодувати те, що зможе. Вибір поведінки залишається на ваш розсуд.
            return 0;
        };

};


int main(int argc, char* argv[])
{
    RLE rle;

    for (int i = 1; i < argc; i++)
    {
        cout << "[ ] Argument " << i << ": " << argv[i]
             << endl;
    }

    while (true)
    {
        cout << "\n[?] What to do with it?\n1: Encode, 2: Decode, 0: Exit\n>>> ";
        string ask, subask;

        getline(cin, ask);
        if (size(ask) == 0)
            continue;
        stringstream ss(ask);
        vector<string> v;
        while (getline(ss, ask, ' '))
        {
            v.push_back(ask);
        }

        if(size(v[0]) > 1)
        {
            cout << "[!] There is no " << v[0] << " command\n";
        }

        if (v[0] == "0")
        {
            return 0;
        }
        else if (v[0] == "1")
        {
            if (argc > 1)
            {
                cout << "[?] There is " << argc - 1 << " arguments\nWant to use them? (N(/Y))\n>>> ";
                getline(cin, subask);
                if (subask == "Y")
                {
                    for (int i = 1; i < argc; i++)
                    {
                        rle.Encoder(argv[i]);
                    }
                }
            }
            else
            {
                if (size(v) > 3)
                    cerr << "[!] There is too many arguments! Omitting... \n";
                if (size(v) > 1)
                {
                    string read, write;
                    read = v[1];
                    if (size(v) < 3)
                    {
                        cout << "[?] There is no file name to write, use " << read.substr(0, read.find_first_of(".")) << ".rle?(Y(/FILENAME))\n>>> ";
                        getline(cin, subask);
                        if (subask == "Y" or subask == "")
                        {    
                            write = "";
                        }
                        else
                        {
                            write = subask;
                        }
                    }
                    else
                    {
                        write = v[2];
                    }
                    rle.Encoder(read, write);
                }
                else
                {
                    cerr << "[!] There is no arguments\n";
                }
            }
        }
        else if (v[0] == "2")
        {
            if (argc > 1)
            {
                cout << "[?] There is " << argc - 1 << " arguments\nWant to use them? (N(/Y))\n>>> ";
                getline(cin, subask);
                if (subask == "Y")
                {
                    for (int i = 1; i < argc; i++)
                    {
                        rle.Decoder(argv[i]);
                    }
                }
            }
            else
            {
                if (size(v) > 3)
                    cerr << "[!] There is too many arguments! Omitting... \n";
                if (size(v) > 1)
                {
                    string read, write;
                    read = v[1];
                    if (size(v) < 3)
                    {
                        cout << "[?] There is no file name to write, use " << read.substr(0, read.find_first_of(".")) << "?(Y(/FILENAME))\n>>> ";
                        getline(cin, subask);
                        if (subask == "Y")
                        {    
                            write = "";
                        }
                        else
                        {
                            write = subask;
                        }
                    }
                    else
                    {
                        write = v[2];
                    }
                    rle.Decoder(read, write);
                }
                else
                {
                    cerr << "[!] There is no arguments\n";
                }
            }
        }
        else
        {
            cout << "[!] There is no " << v[0] << " command\n";
        }
    }
}
