#include <iostream>
#include <fstream>
#include <bitset>
#include <vector>

#include <algorithm> // reverse
#include <cstdint> // uint8_t
#include <sstream> // stringstream
#include <cmath> // pow

using namespace std;

class BitSequence
{
    public:
        // ReadBitSequence(BitStream, b1, 11),
        int FINISHED_BITS = 0;
        template<size_t N>
        void Reverse(bitset<N> &bitst)
        {
            for(std::size_t i = 0; i < N/2; ++i)
            {
                bool t = bitst[i];
                bitst[i] = bitst[N-i-1];
                bitst[N-i-1] = t;
            }
        }
        int Read(fstream &bitsream, vector<char> &Arr, int BitLength)
        {
            uint8_t value;
            bitset<8> val;
            bitsream.seekg(FINISHED_BITS/8);
            cout << "Cursor in file on " << FINISHED_BITS << " bits (" << bitsream.tellg() << " byte)\n";
            while (!bitsream.eof( ) and bitsream.tellg()*8 - FINISHED_BITS < BitLength)
            {
                bitsream.read(reinterpret_cast<char*>(&value), sizeof(value));
                if (bitsream.tellg()*8 - FINISHED_BITS >= BitLength)
                {
                    int bits_left = bitsream.tellg()*8 - FINISHED_BITS - BitLength;
                    int bits_to_use = 8 - bits_left;
                    
                    // string str = bitset<8>(value).to_string();
                    // reverse(str.begin(), str.end());

                    int res = 0;
                    for (int i = 0; i < bits_to_use; i++)
                    {
                        // cout << res << ", " << i << ", " << (2^i) << " | ";
                        res += pow(2, i);
                    }
                    val = bitset<8>(value);
                    // Reverse(val);
                    // cout << "\n" << bits_to_use << " | " << bits_left << "\n";
                    // cout << res << " | " << bitset<8>(res) << " | " << (bitset<8>(res) << bits_left) << " | " << ((bitset<8>(res) << bits_left) & val) << " | " << '\n';
                    bitset<8> result = (bitset<8>(res) << bits_left) & val;

                    // cout << bitsream.tellg()*8 << " | " << value << " | " << bitset<8>(value) << " | " << val << " | " << result << '\n';
                }
                else
                {
                    val = bitset<8>(value);
                    // Reverse(val);
                }
                // cout << bitset<8>(value) << ' ';
                Arr.push_back(static_cast<char>(val.to_ulong()));
                // cout << static_cast<char>(value);
            }
            FINISHED_BITS += BitLength;
            return 0;
        }
        // WriteBitSequence(BitStream, a1, 9),
        int Write(fstream &bitsream, vector<char> &Arr, int BitLength)
        {
            uint8_t value;
            bitset<8> val;
            bitsream.seekg(FINISHED_BITS/8);
            cout << "Cursor in file on " << FINISHED_BITS << " bits (" << bitsream.tellg() << " byte)\n";
            for (auto it : Arr)
            {
                bitsream.write(reinterpret_cast<char*>(&it), sizeof(value));
            }
            return 0;
        }
};


int main(int argc, char* argv[])
{
    BitSequence bs;
    vector<char> arr;
    string str = "test.txt";
    int BitLength = 0;

    try
    {
        BitLength = stoi(argv[1]);
    }
    catch(const std::exception& e)
    {
        cerr << e.what() << '\n';
        try
        {
            str = argv[1];
        }
        catch(const std::exception& e)
        {
            cerr << e.what() << '\n';
        }
        try
        {
            BitLength = stoi(argv[2]);
        }
        catch(const std::exception& e)
        {
            cerr << e.what() << '\n';
        }
    }
    cout << "\n[T] DONE TRY\n";

    fstream fr(str, ios::binary | ios::in | ios::out);
    if (!fr.is_open())
        {
            cerr << "[!] Error opening the file '" << str << "'!\n";
            return 1;
        }
    // bs.Read(fr, arr, BitLength);
    // bs.Read(fr, arr, 11);
    // bs.Read(fr, arr, 7);
    // bs.Read(fr, arr, 0);
    arr.push_back(0b11100001);
    bs.Write(fr, arr, 8);
    bs.Read(fr, arr, 8);
    fr.close();
    // cout << std::bitset<4>(11)[1] << "\n";
    for (auto it : arr)
    {
        cout << bitset<8>(it) << ' ';
    }
    
    // string s;
    // cin >> s;
    cout << "\n[T] DONE Main\n";
    return 0;
}