#include "memory_map.h"


MemoryMap::MemoryMap() {
    // 32 kB Cartridge ROM Bank #0
    m_address_space[0] = 0x0000;
    // 32 kB Cartridge Switchable ROM Bank
    m_address_space[1] = 0x4000;
    // Video RAM
    m_address_space[2] = 0x8000;
    // Switchable RAM Bank
    m_address_space[3] = 0xA000;
    // Internal RAM
    m_address_space[4] = 0xC000;
    // Unusable
    m_address_space[5] = 0xE000;
    // Sprite Attributes
    m_address_space[6] = 0xFE00;
    // Unusable
    m_address_space[7] = 0xFEA0;
    // I/O Ports
    m_address_space[8] = 0xFF00;
    // Unusable
    m_address_space[9] = 0xFF4C;
    // High RAM
    m_address_space[10] = 0xFF80;
    // Interrupt Enable Register
    m_address_space[11] = 0xFFFF;
}

MemoryMap::~MemoryMap() {
    delete (Memory *)m_memory_map.find(3)->second;
    delete (Memory *)m_memory_map.find(4)->second;
}

bool MemoryMap::init_memory_map(void *file_parser_buffer) {
    m_memory_map.insert(std::pair<int, void *>(0, file_parser_buffer));

    Memory *switchable_ram = new Memory(0x2000);
    switchable_ram->init_memory();
    m_memory_map.insert(std::pair<int, Memory *>(3, switchable_ram));

    Memory *internal_ram  = new Memory(0x2000);
    internal_ram->init_memory();
    m_memory_map.insert(std::pair<int, Memory *>(4, internal_ram));

    return true;
}

uint16_t MemoryMap::write(uint16_t address, uint8_t data) {
    int index = this->get_index(address);

    switch (index) {
        case 0:
            std::cerr << "Cannot write to ROM" << std::endl;
            throw new std::exception;

        case 3:
        case 4: {
                Memory *mem = (Memory*)m_memory_map.find(index)->second;
                return mem->write_memory(address - m_address_space[index], data);
            }
        
        default:
            std::cerr << "MemoryMap index not implemented: " << index << std::endl;
            throw new std::exception;
    }
}

uint8_t MemoryMap::read(uint16_t address) {
    int index = this->get_index(address);

    switch (index) {
        case 0: {
                uint8_t *rom = (uint8_t *)m_memory_map.find(index)->second;
                return rom[address];
            }

        case 3:
        case 4: {
                Memory *mem = (Memory*)m_memory_map.find(index)->second;
                return mem->read_memory(address - m_address_space[index]);
            }
        
        default:
            std::cerr << "MemoryMap index not implemented: " << index << std::endl;
            throw new std::exception;
    }
}

int MemoryMap::get_index(uint16_t address) const {
    for (int i=0; i<12; i++) {
        if (address < m_address_space[i]) {
            return i-1;
        }
    }

    if (address == 0xFFFF) {
        return 11;
    }

    return -1;
}