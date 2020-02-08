#include <fstream>
#include <iostream>
#include <SFML/Graphics.hpp>

int main(int argc, char** argv) {
    std::ifstream file_buffer("roms/Pokemon_Blue_Version.gb", std::ios::in|std::ios::binary);

    uint8_t input[1024];

    if (file_buffer.is_open()) {
        file_buffer.seekg(0, std::ios::beg);
        file_buffer.getline((char*)input, 1024);
    }

    file_buffer.close();

    char name[0x143-0x134];
    for (int i=0x134; i<0x143; i++) {    
        name[i-0x134] = static_cast<char>(static_cast<int>(input[i]));
    }

    std::cout << name << std::endl;

    std::cout << static_cast<int>(input[0x146]) << std::endl;
    std::cout << static_cast<int>(input[0x147]) << std::endl;
    std::cout << static_cast<int>(input[0x148]) << std::endl;
    std::cout << static_cast<int>(input[0x149]) << std::endl;
    

    return 0;
}
