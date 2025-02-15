#include <iostream>
#include <fstream>
#include <bitset>
#include <vector>

// #include <windows.h>

using namespace std;

class RLE 
{
    public:
        int Encoder(string filename_read, string filename_write = "")
        {
            if (filename_write == "")
            {
                filename_write = filename_read + ".rle";
            }

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

            ofstream fw(filename_write);
            if (!fw.is_open())
            {
                cerr << "Error opening the file!\n";
                return 1;
            }

            vector<unsigned char> buffer(istreambuf_iterator<char>(fr), {});

            unsigned char character;
            unsigned long integer = 0;
            string text = "";
            for (int j = 0; j < size(buffer); j = j + 8)
            {
                vector<unsigned char> slice(buffer.begin() + j, buffer.begin() + j + 8);
                string s = "";
                if (slice[0] == '1')
                {
                    for (unsigned long k = 0; k < integer; k++)
                    {
                        // cout << text;
                        fw << text;
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
            if (integer != 0)
            {
                for (unsigned long k = 0; k < integer; k++)
                {
                    // cout << text;
                    fw << text;
                }
                integer = 0;
                text = "";
            }
            

            fr.close();
            fw.close();
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
