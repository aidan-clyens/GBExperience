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

bool CPU::decode_op(uint8_t opcode) {
    uint8_t arg_1;
    uint8_t arg_2;
    uint16_t arg16bit;

    switch (opcode) {
        /****    Misc    ****/
        // NOP
        case 0x00:
            std::cout << "NOP" << std::endl;
            break;
        // HALT
        case 0x76:
            std::cout << "HALT" << std::endl;
            break;
        // STOP
        case 0x10:
            std::cout << "STOP" << std::endl;
            break;
        // DAA
        case 0x27:
            std::cout << "DAA" << std::endl;
            break;
        // CPL
        case 0x2F:
            std::cout << "CPL" << std::endl;
            break;
        // CCF
        case 0x3F:
            std::cout << "CCF" << std::endl;
            break;
        // SCF
        case 0x37:
            std::cout << "SCF" << std::endl;
            break;
        // DI
        case 0xF3:
            std::cout << "DI" << std::endl;
            break;
        // EI
        case 0xFB:
            std::cout << "EI" << std::endl;
            break;
        /****    8-Bit Loads    ****/
        // LD nn, n
        case 0x06: case 0x0E: case 0x16: case 0x1E: case 0x26: case 0x2E:
            arg_1 = this->fetch_op();
            std::cout << "LD nn, " << static_cast<int>(arg_1) << std::endl;
            break;
        // LD r1, r2
        case 0x7F: case 0x78: case 0x79: case 0x7A: case 0x7B: case 0x7C: case 0x7D: case 0x7E:
        case 0x40: case 0x41: case 0x42: case 0x43: case 0x44: case 0x45: case 0x46:
        case 0x48: case 0x49: case 0x4A: case 0x4B: case 0x4C: case 0x4D: case 0x4E:
        case 0x50: case 0x51: case 0x52: case 0x53: case 0x54: case 0x55: case 0x56:
        case 0x58: case 0x59: case 0x5A: case 0x5B: case 0x5C: case 0x5D: case 0x5E:
        case 0x60: case 0x61: case 0x62: case 0x63: case 0x64: case 0x65: case 0x66:
        case 0x68: case 0x69: case 0x6A: case 0x6B: case 0x6C: case 0x6D: case 0x6E:
        case 0x70: case 0x71: case 0x72: case 0x73: case 0x74: case 0x75:
        case 0x36:
            std::cout << "LD r1, r2" << std::endl;
            break;
        // LD A, n
        case 0x0A: case 0x1A: case 0xFA: case 0x3E:
            arg_1 = this->fetch_op();
            arg_2 = this->fetch_op();
            std::cout << "LD A, " << static_cast<int>(arg_1) << static_cast<int>(arg_2) << std::endl;
            break;
        // LD n, A
        case 0x47: case 0x4F: case 0x57: case 0x5F: case 0x67: case 0x6F: case 0x02: case 0x12: case 0x77: case 0xEA:
            arg_1 = this->fetch_op();
            arg_2 = this->fetch_op();
            std::cout << "LD n, A" << std::endl;
            break;
        // LD A, (C)
        case 0xF2:
            std::cout << "LD A, (C)" << std::endl;
            break;
        // LD (C), A
        case 0xE2:
            std::cout << "LD (C), A" << std::endl;
            break;
        // LDD A, (HL)
        case 0x3A:
            std::cout << "LDD A, (HL)" << std::endl;
            break;
        // LDD (HL), A
        case 0x32:
            std::cout << "LDD (HL), A" << std::endl;
            break;
        // LDI A, (HL)
        case 0x2A:
            std::cout << "LDI A, (HL)" << std::endl;
            break;
        // LDI (HL), A
        case 0x22:
            std::cout << "LDI (HL), A" << std::endl;
            break;
        // LDH (n), A
        case 0xE0:
            arg_1 = this->fetch_op();
            std::cout << "LDH (" << static_cast<int>(arg_1) << "), A" << std::endl;
            break;
        // LDH A, (n)
        case 0xF0:
            arg_1 = this->fetch_op();
            std::cout << "LDH A, (" << static_cast<int>(arg_1) << ")" << std::endl;
            break;
        /****    16-Bit Loads    ****/
        // LD n, nn
        case 0x01: case 0x11: case 0x21: case 0x31:
            arg_1 = this->fetch_op();
            arg_2 = this->fetch_op();
            std::cout << "LD n, " << static_cast<int>(arg_1) << static_cast<int>(arg_2) << std::endl;
            break;
        // LD SP, HL
        case 0xF9:
            std::cout << "LD SP, HL" << std::endl;
            break;
        // LDHL SP, n
        case 0xF8:
            arg_1 = this->fetch_op();
            std::cout << "LDHL SP, " << static_cast<int>(arg_1) << std::endl;
            break;
        // LD (nn), SP
        case 0x08:
            arg_1 = this->fetch_op();
            std::cout << "LD " << static_cast<int>(arg_1) << ", SP" << std::endl;
            break;
        // PUSH nn
        case 0xF5: case 0xC5: case 0xD5: case 0xE5:
            std::cout << "PUSH nn" << std::endl;
            break;
        // POP nn
        case 0xF1: case 0xC1: case 0xD1: case 0xE1:
            std::cout << "POP nn" << std::endl;
            break;
        /****    8-Bit ALU    ****/
        // ADD A, n
        case 0x87: case 0x80: case 0x81: case 0x82: case 0x83: case 0x84: case 0x85: case 0x86:
        case 0xC6:
            std::cout << "ADD A, " << static_cast<int>(arg_1) << std::endl;
            break;
        // ADC A, n
        case 0x8F: case 0x88: case 0x89: case 0x8A: case 0x8B: case 0x8C: case 0x8D: case 0x8E:
        case 0xCE:
            std::cout << "ADC A, n" << std::endl;
            break;
        // SUB n
        case 0x97: case 0x90: case 0x91: case 0x92: case 0x93: case 0x94: case 0x95: case 0x96:
        case 0xD6:
            std::cout << "SUB n" << std::endl;
            break;
        // SBC n
        case 0x9F: case 0x98: case 0x99: case 0x9A: case 0x9B: case 0x9C: case 0x9D: case 0x9E:
            std::cout << "SBC n" << std::endl;
            break;
        // AND n
        case 0xA7: case 0xA0: case 0xA1: case 0xA2: case 0xA3: case 0xA4: case 0xA5: case 0xA6:
        case 0xE6:
            std::cout << "AND n" << std::endl;
            break;
        // OR n
        case 0xB7: case 0xB0: case 0xB1: case 0xB2: case 0xB3: case 0xB4: case 0xB5: case 0xB6:
        case 0xF6:
            std::cout << "OR n" << std::endl;
            break;
        // XOR n
        case 0xAF: case 0xA8: case 0xA9: case 0xAA: case 0xAB: case 0xAC: case 0xAD: case 0xAE:
        case 0xEE:
            std::cout << "XOR n" << std::endl;
            break;
        // CP n
        case 0xBF: case 0xB8: case 0xB9: case 0xBA: case 0xBB: case 0xBC: case 0xBD: case 0xBE:
        case 0xFE:
            std::cout << "CP n" << std::endl;
            break;
        // INC n
        case 0x3C: case 0x04: case 0x0C: case 0x14: case 0x1C: case 0x24: case 0x2C: case 0x34:
            std::cout << "INC n" << std::endl;
            break;
        // DEC n
        case 0x3D: case 0x05: case 0x0D: case 0x15: case 0x1D: case 0x25: case 0x2D: case 0x35:
            std::cout << "DEC n" << std::endl;
            break;
        /****    16-Bit Arithmetic    ****/
        // ADD HL, n
        case 0x09: case 0x19: case 0x29: case 0x39:
            std::cout << "ADD HL, n" << std::endl;
            break;
        // ADD SP, n
        case 0xE8:
            std::cout << "ADD SP, n" << std::endl;
            break;
        // INC nn
        case 0x03: case 0x13: case 0x23: case 0x33:
            std::cout << "INC nn" << std::endl;
            break;
        // DEC nn
        case 0x0B: case 0x1B: case 0x2B: case 0x3B:
            std::cout << "DEC nn" << std::endl;
            break;
        /****    Rotates and Shifts    ****/
        // RLCA
        case 0x07:
            std::cout << "RLCA" << std::endl;
            break;
        // RLA
        case 0x17:
            std::cout << "RLA" << std::endl;
            break;
        // RRCA
        case 0x0F:
            std::cout << "RRCA" << std::endl;
            break;
        // RRA
        case 0x1F:
            std::cout << "RRA" << std::endl;
            break;
        /****    Jumps    ****/
        // JP nn
        case 0xC3:
            arg_1 = this->fetch_op();
            arg_2 = this->fetch_op();
            std::cout << "JP " << static_cast<int>(arg_1) << static_cast<int>(arg_2) << std::endl;
            break;
        // JP cc, nn
        case 0xC2: case 0xCA: case 0xD2: case 0xDA:
            arg_1 = this->fetch_op();
            arg_2 = this->fetch_op();
            std::cout << "JP cc, " << static_cast<int>(arg_1) << static_cast<int>(arg_2) << std::endl;
            break;
        // JP HL
        case 0xE9:
            std::cout << "JP HL" << std::endl;
            break;
        // JP n
        case 0x18:
            arg_1 = this->fetch_op();
            std::cout << "JP " << static_cast<int>(arg_1) << std::endl;
            break;
        // JR cc, n
        case 0x20: case 0x28: case 0x30: case 0x38:
            arg_1 = this->fetch_op();
            std::cout << "JR cc, " << static_cast<int>(arg_1) << std::endl;
            break;
        /****    Calls    ****/
        // CALL nn
        case 0xCD:
            arg_1 = this->fetch_op();
            arg_2 = this->fetch_op();
            std::cout << "CALL " << static_cast<int>(arg_1) << static_cast<int>(arg_2) << std::endl;
            break;
        // CALL cc, nn
        case 0xC4: case 0xCC: case 0xD4: case 0xDC:
            arg_1 = this->fetch_op();
            arg_2 = this->fetch_op();
            std::cout << "CALL cc, " << static_cast<int>(arg_1) << static_cast<int>(arg_2) << std::endl;
            break;
        /****    Restarts    ****/
        // RST n
        case 0xC7: case 0xCF: case 0xD7: case 0xDF: case 0xE7: case 0xEF: case 0xF7: case 0xFF:
            std::cout << "RST n" << std::endl;
            break;
        /****    Returns    ****/
        // RET
        case 0xC9:
            std::cout << "RET" << std::endl;
            break;
        // RET cc
        case 0xC0: case 0xC8: case 0xD0: case 0xD8:
            std::cout << "RET cc" << std::endl;
            break;
        // RETI
        case 0xD9:
            std::cout << "RETI" << std::endl;
            break;
        
        // CB
        case 0xCB:
            opcode = this->fetch_op();

            switch (opcode) {
                /****    Misc    ****/
                // SWAP n
                case 0x37: case 0x30: case 0x31: case 0x32: case 0x33: case 0x34: case 0x35: case 0x36:
                    std::cout << "SWAP n" << std::endl;
                    break;
                /****    Rotates and Shifts    ****/
                // RLC n
                case 0x07: case 0x00: case 0x01: case 0x02: case 0x03: case 0x04: case 0x05: case 0x06:
                    std::cout << "RLC n" << std::endl;
                    break;
                // RL n
                case 0x17: case 0x10: case 0x11: case 0x12: case 0x13: case 0x14: case 0x15: case 0x16:
                    std::cout << "RL n" << std::endl;
                    break;
                // RRC n
                case 0x0F: case 0x08: case 0x09: case 0x0A: case 0x0B: case 0x0C: case 0x0D: case 0x0E:
                    std::cout << "RRC n" << std::endl;
                    break;
                // RR n
                case 0x1F: case 0x18: case 0x19: case 0x1A: case 0x1B: case 0x1C: case 0x1D: case 0x1E:
                    std::cout << "RR n" << std::endl;
                    break;
                // SLA n
                case 0x27: case 0x20: case 0x21: case 0x22: case 0x23: case 0x24: case 0x25: case 0x26:
                    std::cout << "SLA n" << std::endl;
                    break;
                // SRA n
                case 0x2F: case 0x28: case 0x29: case 0x2A: case 0x2B: case 0x2C: case 0x2D: case 0x2E:
                    std::cout << "SRA n" << std::endl;
                    break;
                // SRL n
                case 0x3F: case 0x38: case 0x39: case 0x3A: case 0x3B: case 0x3C: case 0x3D: case 0x3E:
                    std::cout << "SRL n" << std::endl;
                    break;
                /****    Bit Opcodes    ****/
                // BIT b, r
                case 0x47: case 0x40: case 0x41: case 0x42: case 0x43: case 0x44: case 0x45: case 0x46:
                    std::cout << "BIT b, r" << std::endl;
                    break;
                // SET b, r
                case 0xC7: case 0xC0: case 0xC1: case 0xC2: case 0xC3: case 0xC4: case 0xC5: case 0xC6:
                    std::cout << "SET b, r" << std::endl;
                    break;
                // RES b, r
                case 0x87: case 0x80: case 0x81: case 0x82: case 0x83: case 0x84: case 0x85: case 0x86:
                    std::cout << "RES b, r" << std::endl;
                    break;

                // Default, opcode not implemented
                default:
                    std::cerr << "CB opcode " << static_cast<int>(opcode) << " not implemented" << std::endl;
                    return false;
            }

            break;

        // Default, opcode not implemented
        default:
            std::cerr << "Opcode " << static_cast<int>(opcode) << " not implemented" << std::endl;
            return false;
    }

    return true;
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