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
    // Echo RAM
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

    this->init_memory_map();
}

MemoryMap::~MemoryMap() {
    for (int i = 0; i < m_memory_map.size() - 1; i++) {
        if (i != 5 || i != 7 || i != 8 || i != 9) {
            delete (Memory *)m_memory_map.find(i)->second;
        }
    }
}

bool MemoryMap::init_memory_map() {
    for (int i = 0; i < 11; i++) {
        if (i != 5 || i != 7 || i != 8 || i != 9) {
            Memory *ram = new Memory(m_address_space[i+1] - m_address_space[i]);
            ram->init_memory();
            m_memory_map.insert(std::pair<int, Memory*>(i, ram));
        }
    }

    return true;
}

void MemoryMap::load_rom(std::vector<uint8_t> file_parser_buffer) {
    for (int i = 0; i < file_parser_buffer.size() / 2; i++) {
        Memory *mem = (Memory *)m_memory_map.find(0)->second;
        mem->write_memory(i - m_address_space[0], file_parser_buffer[i]);
    }
    
    for (int i = file_parser_buffer.size() / 2; i < file_parser_buffer.size(); i++) {
        Memory *mem = (Memory *)m_memory_map.find(1)->second;
        mem->write_memory(i - m_address_space[1], file_parser_buffer[i]);
    }
}

uint16_t MemoryMap::write(uint16_t address, uint8_t data) {
    int index = this->get_index(address);

    switch (index) {
        case 0:
        case 1:
            std::cerr << "Cannot write to ROM" << std::endl;
            break;
        case 2:
            return this->write_vram(address, data);
        case 3:
        case 4:
        case 6:
        case 10: {
            Memory *mem = (Memory *)m_memory_map.find(index)->second;
            return mem->write_memory(address - m_address_space[index], data);
        }
        case 5: {
            Memory *mem = (Memory *)m_memory_map.find(index - 1)->second;
            return mem->write_memory(address - m_address_space[index], data);
        }
        case 7:
        case 9:
            std::cerr << "Address space unusable: " << index << ". Address: " << static_cast<int>(address) << std::endl;
            break;
        case 8:
        case 11:
            return this->m_io.write((IORegisters_t)address, data);
        default: {
            std::cerr << "Invalid address: " << static_cast<int>(address) << std::endl;
            throw new std::exception;
        }
    }
}

uint8_t MemoryMap::read(uint16_t address) {
    int index = this->get_index(address);

    switch (index) {
        case 0:
        case 1: {
            Memory *mem = (Memory *)m_memory_map.find(index)->second;
            return mem->read_memory(address - m_address_space[index]);
        }
        case 2:
            return this->read_vram(address);
        case 3:
        case 4:
        case 6:
        case 10: {
            Memory *mem = (Memory *)m_memory_map.find(index)->second;
            return mem->read_memory(address - m_address_space[index]);
        }
        case 5: {
            Memory *mem = (Memory *)m_memory_map.find(index - 1)->second;
            return mem->read_memory(address - m_address_space[index]);
        }
        case 7:
        case 9:
            std::cerr << "Address space unusable: " << index << ". Address: " << static_cast<int>(address) << std::endl;
            break;
        
        case 8:
        case 11:
            return this->m_io.read((IORegisters_t)address);
        
        default: {
            std::cerr << "Invalid address: " << static_cast<int>(address) << std::endl;
            throw new std::exception;
        }
    }
}

uint16_t MemoryMap::write_vram(uint16_t address, uint8_t data) {
    
    if (address >= TILE_DATA_UNSIGNED && address < TILE_MAP_0) {
        log_memory("MemoryMap: Writing %X to Tile Data Table at address %X", data, address);
    }
    else if (address >= TILE_MAP_0 && address < TILE_MAP_1) {
        log_memory("MemoryMap: Writing %X to Background Map 0 at address %X", data, address);
    }
    else if (address >= TILE_MAP_1) {
        log_memory("MemoryMap: Writing %X to Background Map 1 at address %X", data, address);
    }
    

    Memory *mem = (Memory *)m_memory_map.find(2)->second;
    return mem->write_memory(address - m_address_space[2], data);
}

uint8_t MemoryMap::read_vram(uint16_t address) {
    Memory *mem = (Memory *)m_memory_map.find(2)->second;
    uint8_t data = mem->read_memory(address - m_address_space[2]);
    
    
    if (address >= TILE_DATA_UNSIGNED && address < TILE_MAP_0) {
        log_memory("MemoryMap: Reading %X from Tile Data Table at address %X", data, address);
    }
    else if (address >= TILE_MAP_0 && address < TILE_MAP_1) {
        log_memory("MemoryMap: Reading %X from Background Map 0 at address %X", data, address);
    }
    else if (address >= TILE_MAP_1) {
        log_memory("MemoryMap: Reading %X from Background Map 1 at address %X", data, address);
    }
    

    return data;
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

void MemoryMap::increment_io_counter(IORegisters_t reg) {
    m_io.increment_counter(reg);
}
