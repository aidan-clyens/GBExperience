#include "cartridge.h"


ROMOnly::ROMOnly(std::vector<char> file_buffer) {
    m_rom_buffer = std::vector<uint8_t>(file_buffer.begin(), file_buffer.end());
}

ROMOnly::~ROMOnly() {
    
}