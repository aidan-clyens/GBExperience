#include "memory.h"


Memory::Memory(int mem_size):
m_memory_size(mem_size)
{

}

Memory::~Memory() {
    delete m_memory;
}

bool Memory::init_memory() {
    m_memory = new uint8_t[m_memory_size];

    return m_memory != nullptr;
}

void Memory::write_memory(uint16_t address, uint8_t data) {
    if (address > m_memory_size) {
        throw new std::exception;
    }
    
    m_memory[address] = data;
}

uint8_t Memory::read_memory(uint16_t address) {
    if (address > m_memory_size) {
        throw new std::exception;
    }
    
    return m_memory[address];
}

int Memory::get_size() const {
    return m_memory_size;
}