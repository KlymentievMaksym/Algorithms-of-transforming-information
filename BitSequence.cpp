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
        int FINISHED_BITS_READ = 0;
        int FINISHED_BITS_WRITE = 0;

        unsigned char reverse_table[256] = {
            0x00, 0x80, 0x40, 0xc0, 0x20, 0xa0, 0x60, 0xe0,
            0x10, 0x90, 0x50, 0xd0, 0x30, 0xb0, 0x70, 0xf0,
            0x08, 0x88, 0x48, 0xc8, 0x28, 0xa8, 0x68, 0xe8,
            0x18, 0x98, 0x58, 0xd8, 0x38, 0xb8, 0x78, 0xf8,
            0x04, 0x84, 0x44, 0xc4, 0x24, 0xa4, 0x64, 0xe4,
            0x14, 0x94, 0x54, 0xd4, 0x34, 0xb4, 0x74, 0xf4,
            0x0c, 0x8c, 0x4c, 0xcc, 0x2c, 0xac, 0x6c, 0xec,
            0x1c, 0x9c, 0x5c, 0xdc, 0x3c, 0xbc, 0x7c, 0xfc,
            0x02, 0x82, 0x42, 0xc2, 0x22, 0xa2, 0x62, 0xe2,
            0x12, 0x92, 0x52, 0xd2, 0x32, 0xb2, 0x72, 0xf2,
            0x0a, 0x8a, 0x4a, 0xca, 0x2a, 0xaa, 0x6a, 0xea,
            0x1a, 0x9a, 0x5a, 0xda, 0x3a, 0xba, 0x7a, 0xfa,
            0x06, 0x86, 0x46, 0xc6, 0x26, 0xa6, 0x66, 0xe6,
            0x16, 0x96, 0x56, 0xd6, 0x36, 0xb6, 0x76, 0xf6,
            0x0e, 0x8e, 0x4e, 0xce, 0x2e, 0xae, 0x6e, 0xee,
            0x1e, 0x9e, 0x5e, 0xde, 0x3e, 0xbe, 0x7e, 0xfe,
            0x01, 0x81, 0x41, 0xc1, 0x21, 0xa1, 0x61, 0xe1,
            0x11, 0x91, 0x51, 0xd1, 0x31, 0xb1, 0x71, 0xf1,
            0x09, 0x89, 0x49, 0xc9, 0x29, 0xa9, 0x69, 0xe9,
            0x19, 0x99, 0x59, 0xd9, 0x39, 0xb9, 0x79, 0xf9,
            0x05, 0x85, 0x45, 0xc5, 0x25, 0xa5, 0x65, 0xe5,
            0x15, 0x95, 0x55, 0xd5, 0x35, 0xb5, 0x75, 0xf5,
            0x0d, 0x8d, 0x4d, 0xcd, 0x2d, 0xad, 0x6d, 0xed,
            0x1d, 0x9d, 0x5d, 0xdd, 0x3d, 0xbd, 0x7d, 0xfd,
            0x03, 0x83, 0x43, 0xc3, 0x23, 0xa3, 0x63, 0xe3,
            0x13, 0x93, 0x53, 0xd3, 0x33, 0xb3, 0x73, 0xf3,
            0x0b, 0x8b, 0x4b, 0xcb, 0x2b, 0xab, 0x6b, 0xeb,
            0x1b, 0x9b, 0x5b, 0xdb, 0x3b, 0xbb, 0x7b, 0xfb,
            0x07, 0x87, 0x47, 0xc7, 0x27, 0xa7, 0x67, 0xe7,
            0x17, 0x97, 0x57, 0xd7, 0x37, 0xb7, 0x77, 0xf7,
            0x0f, 0x8f, 0x4f, 0xcf, 0x2f, 0xaf, 0x6f, 0xef,
            0x1f, 0x9f, 0x5f, 0xdf, 0x3f, 0xbf, 0x7f, 0xff,
        };

        int Read(fstream &bitstream, vector<uint8_t> &Arr, int BitLength)
        {
            uint8_t value;
            int BITS_READ = 0;
            // bitset<8> val;
            bitstream.seekg(FINISHED_BITS_READ/8);
            cout << "[?] Cursor in file on " << FINISHED_BITS_READ << " bits (" << bitstream.tellg() << " byte)\n";
            int BitLength_Left, BITS_LEFT, BITS_FREE;
            while (!bitstream.eof( ) and BITS_READ + 8 < BitLength)
            {
                // bitstream.seekg(FINISHED_BITS_READ/8);
                cout << "Entered NORMAL\n";
                bitstream.read(reinterpret_cast<char*>(&value), sizeof(value));
                cout << "[?] Value received: " << bitset<8>(value) << "\n";
                BITS_READ += 8;
                FINISHED_BITS_READ += 8;
            
                //     int bits_left = bitstream.tellg()*8 - FINISHED_BITS_READ - BitLength;
                //     int bits_to_use = 8 - bits_left;
                    
                //     // string str = bitset<8>(value).to_string();
                //     // reverse(str.begin(), str.end());

                //     int res = 0;
                //     for (int i = 0; i < bits_to_use; i++)
                //     {
                //         // cout << res << ", " << i << ", " << (2^i) << " | ";
                //         res += pow(2, i);
                //     }
                //     val = bitset<8>(value);
                //     // Reverse(val);
                //     // cout << "\n" << bits_to_use << " | " << bits_left << "\n";
                //     // cout << res << " | " << bitset<8>(res) << " | " << (bitset<8>(res) << bits_left) << " | " << ((bitset<8>(res) << bits_left) & val) << " | " << '\n';
                //     bitset<8> result = (bitset<8>(res) << bits_left) & val;

                //     // cout << bitstream.tellg()*8 << " | " << value << " | " << bitset<8>(value) << " | " << val << " | " << result << '\n';
                // }
                // else
                // {
                //     val = bitset<8>(value);
                //     // Reverse(val);
                // }
                // cout << bitset<8>(value) << ' ';
                Arr.push_back(value);
                // Arr.push_back(static_cast<uint8_t>(val.to_ulong()));
                // cout << static_cast<char>(value);
            }
            if (!bitstream.eof( ))
            {
                cout << "Entered END\n";
                bitstream.read(reinterpret_cast<char*>(&value), sizeof(value));
                
                BITS_LEFT = BitLength - BITS_READ;
                BITS_FREE = 8 - BITS_LEFT;
                cout << "[?] Value received: " << bitset<8>(value) << "\n";
                cout << "[?] BITS LEFT: " << BITS_LEFT << "\n";
                cout << "[?] BITS FREE: " << BITS_FREE << "\n";
                value = value & (CreateByte(BITS_LEFT) << BITS_FREE);
                value = Reverse(value);
                cout << "[?] Value will use: " << bitset<8>(value) << "\n";
                FINISHED_BITS_READ += BITS_LEFT;
                Arr.push_back(value);
            }
            // FINISHED_BITS_READ += BitLength;
            return 0;
        }
        // WriteBitSequence(BitStream, a1, 9),
        int Write(fstream &bitstream, vector<uint8_t> &Arr, int BitLength, bool NeedInfo=false)
        {
            uint8_t value;
            int BITS_WRITE = 0;
            // bitset<8> val;
            // bitstream.seekg(FINISHED_BITS_READ/8);
            // cout << "Cursor in file on " << FINISHED_BITS_READ << " bits (" << bitstream.tellg() << " byte)\n";
            for (uint8_t it : Arr)
            {
                // if (bitstream.tellg()*8 <= BitLength - (BitLength % 8))
                // cout << '\n' << FINISHED_BITS_WRITE << '\n';
                
                if ((FINISHED_BITS_WRITE + 8) % 8 == 0 and BITS_WRITE + 8 < BitLength)
                {
                    if (NeedInfo)
                    {
                        cout << "ENTERED NORMAL\n";
                        cout << "[?] Cursor on: " << bitstream.tellg()<< " byte | " << bitstream.tellg()*8 << " bit\n";
                    }
                    
                    bitstream.write(reinterpret_cast<char*>(&it), sizeof(it));
                    BITS_WRITE += sizeof(it)*8;
                    FINISHED_BITS_WRITE += sizeof(it)*8;
                }
                else
                {
                    int BitLength_Left, BITS_LEFT, BITS_FREE;
                    BitLength_Left = BitLength - BITS_WRITE;
                    
                    if (NeedInfo)
                    {
                        cout << "ENTERED END\n";
                        cout << "[?] BitLength Left: " << BitLength_Left << "\n";
                        cout << "[?] FINISHED_BITS_WRITE: " << FINISHED_BITS_WRITE << " | " << BITS_WRITE << "\n";
                    }
                    // BitLength_Left - 
                    if (BitLength_Left <= 8)
                    {
                        BITS_LEFT = BitLength_Left;
                    }
                    else
                    {
                        BITS_LEFT = (bitstream.tellg()*8 - FINISHED_BITS_WRITE);
                        // BitLength_Left -= BITS_LEFT;
                        if (NeedInfo)
                        {
                            cout << "[?] Bits left: " << BITS_LEFT << " | " << bitstream.tellg()*8 - FINISHED_BITS_WRITE << "\n";
                        }
                        bitstream.seekg(FINISHED_BITS_WRITE/8);
                        bitstream.read(reinterpret_cast<char*>(&value), sizeof(value));
                        value = Reverse(value);
                        // it = Reverse(it);
                    }
                    bitstream.seekg(FINISHED_BITS_WRITE/8);
                    
                    BITS_FREE = 8 - BITS_LEFT;
                    int byte_left = 0, byte_free = 0;
                    byte_left = CreateByte(BITS_LEFT);
                    byte_free = CreateByte(BITS_FREE) << BITS_LEFT;

                    if (NeedInfo)
                    {
                        cout << "[?] Cursor on: " << bitstream.tellg()<< " byte | " << bitstream.tellg()*8 << " bit\n";
                        cout << "[?] Value received: " << bitset<8>(value) << "\n";
                        cout << "[?] Byte received: " << bitset<8>(it) << "\n";
                        cout << "[?] Byte to access left bits: " << bitset<8>(byte_left) << "\n";
                        cout << "[?] Byte to access free bits: " << bitset<8>(byte_free) << "\n";
                        cout << "[?] Byte received: " << bitset<8>(Reverse((it & byte_left) << BITS_FREE)) << "\n";
                    }

                    value = (value) | Reverse((it & byte_left) << BITS_FREE);

                    if (NeedInfo)
                    {
                        cout << "[?] Value will use: " << bitset<8>(value) << "\n";
                    }

                    bitstream.write(reinterpret_cast<char*>(&value), sizeof(value));
                    // BITS_WRITE += BITS_LEFT;
                    FINISHED_BITS_WRITE += BITS_LEFT;
                    if (BitLength_Left-BITS_LEFT > 0)
                    {
                        value = (it & byte_free);

                        if (NeedInfo)
                        {
                            cout << "[?] Cursor on: " << bitstream.tellg()<< " byte | " << bitstream.tellg()*8 << " bit\n";
                            cout << "[?] Value for next will use: " << bitset<8>(value) << "\n";
                        }
                        bitstream.write(reinterpret_cast<char*>(&value), sizeof(value));
                        BITS_WRITE += 8;
                        FINISHED_BITS_WRITE += BITS_FREE;
                    }
                }
                

                // if (FINISHED_BITS_WRITE <= BitLength - (BitLength % 8))
                // {
                //     bitstream.write(reinterpret_cast<char*>(&it), sizeof(it));
                //     FINISHED_BITS_WRITE += sizeof(it)*8;
                // }
                // else
                // {
                //     // cout << bitset<8>(it & (BitLength % 8 << (8 - BitLength % 8))) << "\n\n\n";
                //     value = it & (BitLength % 8 << (8 - BitLength % 8));
                //     bitstream.write(reinterpret_cast<char*>(&value), sizeof(value));
                //     // val = 
                // }
                // bitstream.write(reinterpret_cast<char*>(&it), sizeof(it));
            }
            return 0;
        }
    private:
        unsigned char Reverse(unsigned char x)
        {
            return reverse_table[x];
        }
        int CreateByte(int BitCount)
        {
            int byt = 0;
            for (int i = 0; i < BitCount; i++)
            {
                byt += pow(2, i);
            }
            return byt;
        }
        
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
};


int main(int argc, char* argv[])
{
    BitSequence bs;
    string str = "test.txt";
    // int BitLength = 0;

    // try
    // {
    //     BitLength = stoi(argv[1]);
    // }
    // catch(const std::exception& e)
    // {
    //     cerr << e.what() << '\n';
    //     try
    //     {
    //         str = argv[1];
    //     }
    //     catch(const std::exception& e)
    //     {
    //         cerr << e.what() << '\n';
    //     }
    //     try
    //     {
    //         BitLength = stoi(argv[2]);
    //     }
    //     catch(const std::exception& e)
    //     {
    //         cerr << e.what() << '\n';
    //     }
    // }
    // cout << "\n[T] DONE TRY\n";

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
    // arr.push_back(0b11100001);
    vector<uint8_t> a1 = {0b11100001, 0b00000001};
    vector<uint8_t> a2 = {0b11101110, 0b00000000};
    // bs.Write(fr, a1, 9, true);
    // bs.Write(fr, a2, 9, true);
    bs.Write(fr, a1, 9);
    bs.Write(fr, a2, 9);
    vector<uint8_t> b1, b2;
    bs.Read(fr, b1, 11);
    // bs.Read(fr, b1, 18);
    bs.Read(fr, b2, 7);
    fr.close();

    for (uint8_t byte : b1)
    {
        // cout << hex << static_cast<int>(byte) << " ";
        cout << bitset<8>(byte) << " ";
    }
    cout << dec << endl;
    for (uint8_t byte : b2)
    {
        // cout << hex << static_cast<int>(byte) << " ";
        cout << bitset<8>(byte) << " ";
    }
    cout << dec << endl;
    cout << "\n" << bitset<8>(0b11100001) << " " << bitset<8>(0b00000101) << "\n";
    cout << bitset<8>(0b00111011) << "\n";

    // cout << bitset<8>(1) << " | " << bitset<8>(bs.reverse(1));

    // cout << std::bitset<4>(11)[1] << "\n";
    // for (auto it : arr)
    // {
    //     cout << bitset<8>(it) << ' ';
    // }
    
    // string s;
    // cin >> s;
    // cout << "\n[T] DONE Main\n";
    return 0;
}