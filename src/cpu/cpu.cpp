#include "cpu.h"


CPU::CPU(MemoryMap &mem_map):
m_memory_map(mem_map),
m_PC(0x100),
m_SP(0x0)
{
    m_valid_8bit_registers = {"A", "F", "B", "C", "D", "E", "H", "L"};
    m_valid_16bit_registers = {"AF", "BC", "DE", "HL"};

    for (int i=0; i<m_valid_8bit_registers.size(); i++) {
        std::string reg = m_valid_8bit_registers[i];
        m_registers.insert(std::pair<std::string, uint8_t>(reg, 0x0));
    }
}

CPU::~CPU() {

}

uint8_t CPU::fetch_op() {
    uint16_t address = this->read_register("PC");
    this->write_register("PC", address + 1);

    return m_memory_map.read(address);
}

void CPU::write_register(const std::string &reg, uint16_t data) {
    if (reg == "PC") {
        m_PC = data;
        return;
    }
    else if (reg == "SP") {
        m_SP = data;
        return;
    }

    // 8-bit write
    if (reg.size() == 1) {
        this->_write_8bit_register(reg, data);
    }
    // 16-bit write
    else if (reg.size() == 2) {
        if (!this->_check_register_valid(reg)) {
            throw new std::exception;
        }

        std::string reg_high = std::string(1, reg[0]);
        std::string reg_low = std::string(1, reg[1]);

        this->_write_8bit_register(reg_high, ((data >> 8) & 0xFF));
        this->_write_8bit_register(reg_low, (data & 0xFF));
    }
    else {
        throw new std::exception;
    }
}

uint16_t CPU::read_register(const std::string &reg) {
    if (reg == "PC") {
        return m_PC;
    }
    else if (reg == "SP") {
        return m_SP;
    }

    // 8-bit read
    if (reg.size() == 1) {
        this->_read_8bit_register(reg);
    }
    // 16-bit read
    else if (reg.size() == 2) {
        if (!this->_check_register_valid(reg)) {
            throw new std::exception;
        }

        std::string reg_high = std::string(1, reg[0]);
        std::string reg_low = std::string(1, reg[1]);

        uint16_t value;
        value = (this->_read_8bit_register(reg_high)) << 8 & 0xFF00;
        value |= this->_read_8bit_register(reg_low) & 0xFF;
    
        return value;
    }
    else {
        throw new std::exception;
    }
}

bool CPU::_check_register_valid(const std::string &reg) {
    if (reg.size() == 1) {
        auto it = std::find(m_valid_8bit_registers.begin(), m_valid_8bit_registers.end(), reg);
        return (it != m_valid_8bit_registers.end());
    }
    else if (reg.size() == 2) {
        auto it = std::find(m_valid_16bit_registers.begin(), m_valid_16bit_registers.end(), reg);
        return (it != m_valid_16bit_registers.end());
    }
}

void CPU::_write_8bit_register(const std::string &reg, uint8_t data) {
    if (!this->_check_register_valid(reg)) {
        std::cerr << "Register: " << reg << " does not exist" << std::endl;
        throw new std::exception;
    }

    if (m_registers.count(reg) > 0) {
        m_registers.find(reg)->second = data;
    }
    else {
        std::cerr << "Register: " << reg << " does not exist" << std::endl;
        throw new std::exception;
    }
}

uint8_t CPU::_read_8bit_register(const std::string &reg) {
    if (!this->_check_register_valid(reg)) {
        std::cerr << "Register: " << reg << " does not exist" << std::endl;
        throw new std::exception;
    }

    if (m_registers.count(reg) > 0) {
        return m_registers.find(reg)->second;
    }
    else {
        std::cerr << "Register: " << reg << " does not exist" << std::endl;
        throw new std::exception;
    }
}