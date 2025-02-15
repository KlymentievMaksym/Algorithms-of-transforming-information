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
                cerr << "Error opening the file!";
                return 1;
            }

            ofstream fw(filename_write, ios::binary);
            if (!fw.is_open())
            {
                cerr << "Error opening the file!";
                return 1;
            }

            string s;
            while (getline(fr, s))
            {
                // cout << s << s[1] << size(s) << bitset<8>(s[1]).to_string() << "\n";
                for (int i = 0; i < size(s); i++)
                {
                    fw << bitset<8>(s[i]);
                    // cout << i << "\n";
                    // cout << bitset<8>(s[i]) << "\n";
                }
                fw << "\n";
            }   
            fr.close();
            fw.close();
            return 0;
        };

        int Decoder(string filename_read, string filename_write = "")
        {
            // if (filename_write == "")
            // {
            //     auto it = next(filename_read.begin(), filename_read.find(".rle")); 
            //     filename_write = filename_read;
            //     filename_write.erase(it, next(it, 2));
            //     filename_write = filename_write + "_COPY.txt";
            // }

            ifstream fr(filename_read, ios::binary);
            if (!fr.is_open())
            {
                cerr << "Error opening the file!";
                return 1;
            }

            // ofstream fw(filename_write);
            // if (!fw.is_open())
            // {
            //     cerr << "Error opening the file!";
            //     return 1;
            // }

            // char* s;
            // fr.read(s, 8);
            vector<unsigned char> buffer(std::istreambuf_iterator<char>(fr), {});

            vector<unsigned char> slice(buffer.begin(), buffer.begin() + 8);
            for (auto it : slice)
            {
                cout << it;
            }
            // unsigned long i = slice.to_ulong(); 
            // unsigned char c = static_cast<unsigned char>( i ); 

            cout << "\n";

            for (auto it : buffer)
            {
                cout << it;
            }
            // cout << s << "\n";
            fr.close();
            // fw.close();
            return 0;
        };

};


int main(int argc, char* argv[])
{
    RLE rle;

    cout << "You have entered " << argc
         << " arguments:" << endl;

    for (int i = 0; i < argc; i++)
    {
        cout << "Argument " << i + 1 << ": " << argv[i]
             << endl;
    }
    while (true)
    {
        cout << "[?] What to do with it?\n1: Encode, 2: Decode, 0: Exit\n>>> ";
        string ask;
        cin >> ask;
        cout << ask << "\n";

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
