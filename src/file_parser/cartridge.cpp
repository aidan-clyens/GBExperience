#include "cartridge.h"


Cartridge::Cartridge(std::vector<char> file_buffer, int num_rom_banks):
m_cartridge_type(ROM_ONLY),
m_cartridge_size(0),
m_num_rom_banks(num_rom_banks)
{
    int buffer_index = 0;
    for (int i = 0; i < m_num_rom_banks; i++) {
        Memory *mem = new Memory(ROM_BANK_SIZE);
        mem->init_memory();

        int j = 0;
        while (buffer_index < file_buffer.size() && j < ROM_BANK_SIZE) {
            mem->write_memory(j, file_buffer[buffer_index]);

            buffer_index++;
            j++;
        }

        m_rom_banks.push_back(mem);
    }
}

Cartridge::~Cartridge() {
    for (int i = 0; i < m_rom_banks.size(); i++) {
        delete m_rom_banks[i];
    }
}

void Cartridge::set_cartridge_type(cartridge_type_t type) {
    m_cartridge_type = type;
}

cartridge_type_t Cartridge::get_cartridge_type() const {
    return m_cartridge_type;
}

void Cartridge::set_num_rom_banks(int size) {
    m_num_rom_banks = size;
}

int Cartridge::get_num_rom_banks() const {
    return m_num_rom_banks;
}


ROMOnly::ROMOnly(std::vector<char> file_buffer, int num_rom_banks):
Cartridge(file_buffer, num_rom_banks)
{
    Cartridge::set_cartridge_type(ROM_ONLY);
}

ROMOnly::~ROMOnly() {

}

uint8_t ROMOnly::read(uint16_t address) {
    if (address > 2 * ROM_BANK_SIZE) {
        std::cerr << "ROMOnly read: Address out of range" << std::endl;
        throw new std::exception;
    }

    unsigned int index = (unsigned int)address / ROM_BANK_SIZE;
    address = address % ROM_BANK_SIZE;
    return m_rom_banks[index]->read_memory(address);
}

uint16_t ROMOnly::write(uint16_t address, uint8_t data) {
    std::cerr << "ROMOnly: Cannot write to ROM" << std::endl;

    return 0;
}
