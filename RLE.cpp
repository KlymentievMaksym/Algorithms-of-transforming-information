#include <iostream>
#include <fstream>
#include <bitset>
#include <vector>

// #include <windows.h>

using namespace std;

class RLE 
{
    public:
        // 1. Кодер повинен приймати на вхід ім'я файла для кодування та (опціонально) ім'я файла для зберігання закодованого результату.
        int Encoder(string filename_read, string filename_write = "")
        {
            if (filename_write == "")
            {
                filename_write = filename_read;
                size_t lastindex_dot = filename_write.find_last_of(".");
                filename_write = filename_write.substr(0, lastindex_dot)  + ".rle";
            }
            cout << filename_read << "\n";
            cout << filename_write << "\n";

            ifstream fr(filename_read);
            if (!fr.is_open())
            {
                cerr << "Error opening the file!\n";
                return 1;
            }

            ofstream fw(filename_write, ios::binary);
            if (!fw.is_open())
            {
                cerr << "Error opening the file!\n";
                return 1;
            }

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
                        // if (count >= 2^7-1)
                        //     break;
                    }
                    // cout << count << "\n";
                    // cout << bitset<1>(1) << bitset<7>(count) << "\n";
                    // cout << s[i] << "\n";
                    // cout << bitset<8>(s[i]) << "\n" << "\n";
                    fw << bitset<1>(1) << bitset<7>(count);
                    fw << bitset<8>(s[i]);
                    count = 1;
                }
                fw << bitset<1>(1) << bitset<7>(count);
                fw << bitset<8>('\n');
            }   
            fr.close();
            fw.close();
            return 0;
        };

        int Decoder(string filename_read, string filename_write = "")
        {
            if (filename_write == "")
            {
                filename_write = filename_read;
                if (filename_write.find(".rle") != string::npos)
                {
                    filename_write.pop_back();
                    filename_write.pop_back();
                    filename_write.pop_back();
                    filename_write.pop_back();
                }
                else
                {
                    filename_write = filename_write + "_copy.txt";
                }
                // cout << filename_write << '\n';
                // cout << filename_read << '\n';
            }

            ifstream fr(filename_read, ios::binary);
            if (!fr.is_open())
            {
                cerr << "Error opening the file!\n";
                return 1;
            }

            vector<unsigned char> buffer(istreambuf_iterator<char>(fr), {});
            fr.close();

            unsigned char character;
            unsigned long integer = 0;
            string main_text = "";
            string text = "";
            int j;
            for (j = 0; j < size(buffer)-7; j = j + 8)
            {
                vector<unsigned char> slice(buffer.begin() + j, buffer.begin() + j + 8);
                string s = "";
                if (slice[0] == '1')
                {
                    for (unsigned long k = 0; k < integer; k++)
                    {
                        cout << text;
                        main_text = main_text + text;
                    }
                    integer = 0;
                    text = "";
                    for (int i = 1; i < size(slice); i++)
                    {
                        s = s + static_cast<char>(slice[i]);
                    }
                    bitset<7> byt;
                    byt = static_cast<bitset<7>>(s);
                    integer = byt.to_ulong();
                }
                else
                {
                    if (slice[0] == '0')
                    {
                        for (auto it : slice)
                        {
                            s = s + static_cast<char>(it);
                        }
                        bitset<8> byt;
                        byt = static_cast<bitset<8>>(s);
                        unsigned long i = byt.to_ulong(); 
                        character = static_cast<unsigned char>( i );
                        text = text + static_cast<char>(character);
                    }
                }
            }
            cout << "\n" << j << " " << size(buffer) << "\n";
            if (j != size(buffer))
            {
                cout << "[!] Something wrong after col (Seems like not full byte) " << j << "\n[?] Change with skipping it? [N(/Y))]\n>>> ";
                string ask;
                cin >> ask;
                if (ask != "Y")
                {
                    main_text = "";
                }
            }
            else
            {
                if (integer != 0)
                {
                    for (unsigned long k = 0; k < integer; k++)
                    {
                        cout << text;
                        main_text = main_text + text;
                    }
                    integer = 0;
                    text = "";
                }
            }

            if (main_text != "")
            {
                ofstream fw(filename_write, ios::binary);
                if (!fw.is_open())
                {
                    cerr << "Error opening the file!\n";
                    return 1;
                }

                fw << main_text;
                fw.close();
            }

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
