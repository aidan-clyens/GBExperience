#include "cpu_registers.h"


CPURegisters::CPURegisters():
m_PC(0x0100),
m_SP(0xFFFE)
{
    m_registers.insert(std::pair<Registers_t, uint8_t>(REG_A, 0x0));
    m_registers.insert(std::pair<Registers_t, uint8_t>(REG_F, 0x0));
    m_registers.insert(std::pair<Registers_t, uint8_t>(REG_B, 0x0));
    m_registers.insert(std::pair<Registers_t, uint8_t>(REG_C, 0x0));
    m_registers.insert(std::pair<Registers_t, uint8_t>(REG_D, 0x0));
    m_registers.insert(std::pair<Registers_t, uint8_t>(REG_E, 0x0));
    m_registers.insert(std::pair<Registers_t, uint8_t>(REG_H, 0x0));
    m_registers.insert(std::pair<Registers_t, uint8_t>(REG_L, 0x0));

    this->write_register(REG_AF, 0x01B0);
    this->write_register(REG_BC, 0x0013);
    this->write_register(REG_DE, 0x00D8);
    this->write_register(REG_HL, 0x014D);
}

CPURegisters::~CPURegisters() {

}

void CPURegisters::write_register(Registers_t reg, uint16_t data) {
    if (reg == REG_AF) {
        uint8_t upper_byte = data >> 8;
        uint8_t lower_byte = data & 0xFF;

        this->write_register(REG_A, upper_byte);
        this->write_register(REG_F, lower_byte);
    }
    else if (reg == REG_BC) {
        uint8_t upper_byte = data >> 8;
        uint8_t lower_byte = data & 0xFF;

        this->write_register(REG_B, upper_byte);
        this->write_register(REG_C, lower_byte);
    }
    else if (reg == REG_DE) {
        uint8_t upper_byte = data >> 8;
        uint8_t lower_byte = data & 0xFF;

        this->write_register(REG_D, upper_byte);
        this->write_register(REG_E, lower_byte);
    }
    else if (reg == REG_HL) {
        uint8_t upper_byte = data >> 8;
        uint8_t lower_byte = data & 0xFF;

        this->write_register(REG_H, upper_byte);
        this->write_register(REG_L, lower_byte);
    }
    else if (reg == REG_PC) {
        m_PC = data;
    }
    else if (reg == REG_SP) {
        m_SP = data;
    }
    else {
        if (m_registers.count(reg) > 0) {
            if (reg == REG_F) {
                data = (data & 0xF0) | (m_registers.find(reg)->second & 0x0F);
            }

            m_registers.find(reg)->second = data;
        }
        else {
            std::cerr << "Error: Register does not exist!" << std::endl;
            throw new std::exception;
        }
    }
}

uint16_t CPURegisters::read_register(Registers_t reg) {
    if (reg == REG_AF) {
        return (this->read_register(REG_A) << 8) | (this->read_register(REG_F));
    }
    else if (reg == REG_BC) {
        return (this->read_register(REG_B) << 8) | (this->read_register(REG_C));
    }
    else if (reg == REG_DE) {
        return (this->read_register(REG_D) << 8) | (this->read_register(REG_E));
    }
    else if (reg == REG_HL) {
        return (this->read_register(REG_H) << 8) | (this->read_register(REG_L));
    }
    else if (reg == REG_PC) {
        return m_PC;
    }
    else if (reg == REG_SP) {
        return m_SP;
    }
    else {
        if (m_registers.count(reg) > 0) {
            return m_registers.find(reg)->second;
        }
        else {
            std::cerr << "Error: Register does not exist!" << std::endl;
            throw new std::exception;
        }
    }
}

const char *CPURegisters::to_string(Registers_t reg) {
    switch (reg) {
        case REG_A: return "A";
        case REG_F: return "F";
        case REG_B: return "B";
        case REG_C: return "C";
        case REG_D: return "D";
        case REG_E: return "E";
        case REG_H: return "H";
        case REG_L: return "L";
        case REG_AF: return "AF";
        case REG_BC: return "BC";
        case REG_DE: return "DE";
        case REG_HL: return "HL";
        case REG_PC: return "PC";
        case REG_SP: return "SP";
    }

    return "";
}
