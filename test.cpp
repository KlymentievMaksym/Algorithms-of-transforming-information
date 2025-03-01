#include <iostream>
#include <fstream>
#include <vector>

#include <cstdint> // uint8_t


void Write(std::fstream& BitStream, const std::vector<uint8_t>& data, size_t bitCount) {
    size_t byteCount = (bitCount + 7) / 8; // Кількість повних байтів для запису
    for (size_t i = 0; i < byteCount; ++i) {
        BitStream.put(static_cast<char>(data[i]));
    }
    BitStream.flush();
}

void Read(std::fstream& BitStream, std::vector<uint8_t>& data, size_t bitCount) {
    size_t byteCount = (bitCount + 7) / 8;
    data.resize(byteCount);
    for (size_t i = 0; i < byteCount; ++i) {
        char byte;
        BitStream.get(byte);
        data[i] = static_cast<uint8_t>(byte);
    }
}

int main() {
    std::fstream file("bitstream.bin", std::ios::in | std::ios::out | std::ios::binary | std::ios::trunc);
    if (!file) {
        std::cerr << "Не вдалося відкрити файл!" << std::endl;
        return 1;
    }
    
    // std::vector<uint8_t> writeData = {0b10101010, 0b11001100};
    std::vector<uint8_t> writeData = {0b11100001, 0b00000001};
    std::vector<uint8_t> writeData1 = {0b11101110, 0b00000000};
    size_t bitCount = 9; // Записуємо 12 біт (1.5 байта)
    Write(file, writeData, bitCount);
    Write(file, writeData1, bitCount);
    
    file.seekg(0);
    std::vector<uint8_t> readData;
    std::vector<uint8_t> readData1;
    Read(file, readData, 11);
    Read(file, readData1, 7);
    
    std::cout << "Readed bytes: ";
    for (uint8_t byte : readData) {
        std::cout << std::hex << static_cast<int>(byte) << " ";
    }
    std::cout << std::dec << std::endl;
    for (uint8_t byte : readData1) {
        std::cout << std::hex << static_cast<int>(byte) << " ";
    }
    std::cout << std::dec << std::endl;
    
    file.close();
    return 0;
}
