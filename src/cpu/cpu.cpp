#include "cpu.h"


CPU::CPU(MemoryMap &mem_map):
m_memory_map(mem_map)
{

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
        case 0x87:
            this->alu_add("A", false);
            break;
        case 0x80:
            this->alu_add("B", false);
            break;
        case 0x81:
            this->alu_add("C", false);
            break;
        case 0x82:
            this->alu_add("D", false);
            break;
        case 0x83:
            this->alu_add("E", false);
            break;
        case 0x84:
            this->alu_add("H", false);
            break;
        case 0x85:
            this->alu_add("L", false);
            break;
        case 0x86:
            this->alu_add("HL", false);
            break;
        case 0xC6:
            // TODO
            break;
        // ADC A, n
        case 0x8F:
            this->alu_add("A", true);
            break;
        case 0x88:
            this->alu_add("B", true);
            break;
        case 0x89:
            this->alu_add("C", true);
            break;
        case 0x8A:
            this->alu_add("D", true);
            break;
        case 0x8B:
            this->alu_add("E", true);
            break;
        case 0x8C:
            this->alu_add("H", true);
            break;
        case 0x8D:
            this->alu_add("L", true);
            break;
        case 0x8E:
            this->alu_add("HL", true);
            break;
        case 0xCE:
            // TODO
            break;
        // SUB n
        case 0x97:
            this->alu_sub("A", false);
            break;
        case 0x90:
            this->alu_sub("B", false);
            break;
        case 0x91:
            this->alu_sub("C", false);
            break;
        case 0x92:
            this->alu_sub("D", false);
            break;
        case 0x93:
            this->alu_sub("E", false);
            break;
        case 0x94:
            this->alu_sub("H", false);
            break;
        case 0x95:
            this->alu_sub("L", false);
            break;
        case 0x96:
            this->alu_sub("HL", false);
            break;
        case 0xD6:
            // TODO
            break;
        // SBC n
        case 0x9F:
            this->alu_sub("A", true);
            break;
        case 0x98:
            this->alu_sub("B", true);
            break;
        case 0x99:
            this->alu_sub("C", true);
            break;
        case 0x9A:
            this->alu_sub("D", true);
            break;
        case 0x9B:
            this->alu_sub("E", true);
            break;
        case 0x9C:
            this->alu_sub("H", true);
            break;
        case 0x9D:
            this->alu_sub("L", true);
            break;
        case 0x9E:
            this->alu_sub("HL", true);
            break;
        // AND n
        case 0xA7:
            this->alu_and("A");
            break;
        case 0xA0:
            this->alu_and("B");
            break;
        case 0xA1:
            this->alu_and("C");
            break;
        case 0xA2:
            this->alu_and("D");
            break;
        case 0xA3:
            this->alu_and("E");
            break;
        case 0xA4:
            this->alu_and("H");
            break;
        case 0xA5:
            this->alu_and("L");
            break;
        case 0xA6:
            this->alu_and("HL");
            break;
        case 0xE6:
            // TODO
            break;
        // OR n
        case 0xB7:
            this->alu_or("A");
            break;
        case 0xB0:
            this->alu_or("B");
            break;
        case 0xB1:
            this->alu_or("C");
            break;
        case 0xB2:
            this->alu_or("D");
            break;
        case 0xB3:
            this->alu_or("E");
            break;
        case 0xB4:
            this->alu_or("H");
            break;
        case 0xB5:
            this->alu_or("L");
            break;
        case 0xB6:
            this->alu_or("HL");
            break;
        case 0xF6:
            // TODO
            break;
        // XOR n
        case 0xAF:
            this->alu_xor("A");
            break;
        case 0xA8:
            this->alu_xor("B");
            break;
        case 0xA9:
            this->alu_xor("C");
            break;
        case 0xAA:
            this->alu_xor("D");
            break;
        case 0xAB:
            this->alu_xor("E");
            break;
        case 0xAC:
            this->alu_xor("H");
            break;
        case 0xAD:
            this->alu_xor("L");
            break;
        case 0xAE:
            this->alu_xor("HL");
            break;
        case 0xEE:
            // TODO
            break;
        // CP n
        case 0xBF: case 0xB8: case 0xB9: case 0xBA: case 0xBB: case 0xBC: case 0xBD: case 0xBE:
        case 0xFE:
            std::cout << "CP n" << std::endl;
            break;
        // INC n
        case 0x3C:
            this->alu_inc("A");
            break;
        case 0x04:
            this->alu_inc("B");
            break;
        case 0x0C:
            this->alu_inc("C");
            break;
        case 0x14:
            this->alu_inc("D");
            break;
        case 0x1C:
            this->alu_inc("E");
            break;
        case 0x24:
            this->alu_inc("H");
            break;
        case 0x2C:
            this->alu_inc("L");
            break;
        case 0x34:
            this->alu_inc("HL");
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
    m_registers.write_register(reg, data);
}

uint16_t CPU::read_register(const std::string &reg) {
    return m_registers.read_register(reg);
}