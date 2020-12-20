#include "cpu_registers.h"


CPURegisters::CPURegisters():
m_A(0x01),
m_F(0xB0),
m_B(0x00),
m_C(0x13),
m_D(0x00),
m_E(0xD8),
m_H(0x01),
m_L(0x4D),
m_PC(0x0100),
m_SP(0xFFFE)
{

}

CPURegisters::~CPURegisters() {

}

void CPURegisters::write_register(Registers_t reg, uint16_t data) {
    switch (reg) {
        case REG_AF:
            m_A = data >> 8;
            m_F = data & 0xF0;
            break;
        case REG_BC:
            m_B = data >> 8;
            m_C = data & 0xFF;
            break;
        case REG_DE:
            m_D = data >> 8;
            m_E = data & 0xFF;
            break;
        case REG_HL:
            m_H = data >> 8;
            m_L = data & 0xFF;
            break;
        case REG_PC:
            m_PC = data;
            break;
        case REG_SP:
            m_SP = data;
            break;
        case REG_A:
            m_A = data;
            break;
        case REG_F:
            m_F = (data & 0xF0);
            break;
        case REG_B:
            m_B = data;
            break;
        case REG_C:
            m_C = data;
            break;
        case REG_D:
            m_D = data;
            break;
        case REG_E:
            m_E = data;
            break;
        case REG_H:
            m_H = data;
            break;
        case REG_L:
            m_L = data;
            break;
        default:
            std::cerr << "Error: Register does not exist" << std::endl;
            throw new std::exception;
    }
}

uint16_t CPURegisters::read_register(Registers_t reg) {
    switch (reg) {
        case REG_AF:
            return (m_A << 8) | (m_F);
        case REG_BC:
            return (m_B << 8) | (m_C);
        case REG_DE:
            return (m_D << 8) | (m_E);
        case REG_HL:
            return (m_H << 8) | (m_L);
        case REG_PC:
            return m_PC;
        case REG_SP:
            return m_SP;
        case REG_A:
            return m_A;
        case REG_F:
            return m_F;
        case REG_B:
            return m_B;
        case REG_C:
            return m_C;
        case REG_D:
            return m_D;
        case REG_E:
            return m_E;
        case REG_H:
            return m_H;
        case REG_L:
            return m_L;
        default:
            std::cerr << "Error: Register does not exist" << std::endl;
            throw new std::exception;
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
