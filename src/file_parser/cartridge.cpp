#include "cartridge.h"


Cartridge::Cartridge():
m_cartridge_type(ROM_ONLY),
m_cartridge_size(0)
{

}

Cartridge::~Cartridge() {

}

uint8_t Cartridge::read(uint16_t address) {
    return 0;
}

uint16_t Cartridge::write(uint16_t address, uint8_t data) {
    return 0;
}

void Cartridge::set_cartridge_type(cartridge_type_t type) {
    m_cartridge_type = type;
}

cartridge_type_t Cartridge::get_cartridge_type() const {
    return m_cartridge_type;
}

void Cartridge::set_size(int size) {
    m_cartridge_size = size;
}

int Cartridge::get_size() const {
    return m_cartridge_size;
}


ROMOnly::ROMOnly(std::vector<char> file_buffer) {
    m_rom_buffer = std::vector<uint8_t>(file_buffer.begin(), file_buffer.end());
}

ROMOnly::~ROMOnly() {
    
}