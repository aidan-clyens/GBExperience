#include "cpu.h"


CPU::CPU(MemoryMap &mem_map):
m_memory_map(mem_map)
{
    m_registers.insert(std::pair<std::string, uint16_t>("AF", 0x0));
    m_registers.insert(std::pair<std::string, uint16_t>("BC", 0x0));
    m_registers.insert(std::pair<std::string, uint16_t>("DE", 0x0));
    m_registers.insert(std::pair<std::string, uint16_t>("HL", 0x0));
    m_registers.insert(std::pair<std::string, uint16_t>("SP", 0x0));
    m_registers.insert(std::pair<std::string, uint16_t>("PC", 0x100));
}

CPU::~CPU() {

}

void CPU::write_register(const std::string &reg, uint16_t data) {
    if (m_registers.count(reg) > 0) {
        m_registers.find(reg)->second = data;
    }
    else {
        std::cerr << "Register: " << reg << " does not exist" << std::endl;
        throw new std::exception;
    }
}

uint16_t CPU::read_register(const std::string &reg) {
    if (m_registers.count(reg) > 0) {
        return m_registers.find(reg)->second;
    }
    else {
        std::cerr << "Register: " << reg << " does not exist" << std::endl;
        throw new std::exception;
    }
}