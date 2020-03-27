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

int CPU::decode_op(uint8_t opcode) {
    uint8_t arg_1;
    uint8_t arg_2;
    uint16_t arg16bit;

    int cycle_count = 1;

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
        case 0x06:
            arg_1 = this->fetch_op();
            this->load("B", arg_1);
            cycle_count = 4;
            break;
        case 0x0E:
            arg_1 = this->fetch_op();
            this->load("C", arg_1);
            cycle_count = 4;
            break;
        case 0x16:
            arg_1 = this->fetch_op();
            this->load("D", arg_1);
            cycle_count = 4;
            break;
        case 0x1E:
            arg_1 = this->fetch_op();
            this->load("E", arg_1);
            cycle_count = 4;
            break;
        case 0x26:
            arg_1 = this->fetch_op();
            this->load("H", arg_1);
            cycle_count = 4;
            break;
        case 0x2E:
            arg_1 = this->fetch_op();
            this->load("L", arg_1);
            cycle_count = 4;
            break;
        // LD r1, r2
        case 0x7F:
            this->load("A", "A");
            cycle_count = 4;
            break;
        case 0x78:
            this->load("A", "B");
            cycle_count = 4;
            break;
        case 0x79:
            this->load("A", "C");
            cycle_count = 4;
            break;
        case 0x7A:
            this->load("A", "D");
            cycle_count = 4;
            break;
        case 0x7B:
            this->load("A", "E");
            cycle_count = 4;
            break;
        case 0x7C:
            this->load("A", "H");
            cycle_count = 4;
            break;
        case 0x7D:
            this->load("A", "L");
            cycle_count = 4;
            break;
        case 0x7E:
            this->load_from_mem("A", "HL");
            cycle_count = 8;
            break;
        case 0x40:
            this->load("B", "B");
            cycle_count = 4;
            break;
        case 0x41:
            this->load("B", "C");
            cycle_count = 4;
            break;
        case 0x42:
            this->load("B", "D");
            cycle_count = 4;
            break;
        case 0x43:
            this->load("B", "E");
            cycle_count = 4;
            break;
        case 0x44:
            this->load("B", "H");
            cycle_count = 4;
            break;
        case 0x45:
            this->load("B", "L");
            cycle_count = 4;
            break;
        case 0x46:
            this->load_from_mem("B", "HL");
            cycle_count = 8;
            break;
        case 0x48:
            this->load("C", "B");
            cycle_count = 4;
            break;
        case 0x49:
            this->load("C", "C");
            cycle_count = 4;
            break;
        case 0x4A:
            this->load("C", "D");
            cycle_count = 4;
            break;
        case 0x4B:
            this->load("C", "E");
            cycle_count = 4;
            break;
        case 0x4C:
            this->load("C", "H");
            cycle_count = 4;
            break;
        case 0x4D:
            this->load("C", "L");
            cycle_count = 4;
            break;
        case 0x4E:
            this->load_from_mem("C", "HL");
            cycle_count = 8;
            break;
        case 0x50:
            this->load("D", "B");
            cycle_count = 4;
            break;
        case 0x51:
            this->load("D", "C");
            cycle_count = 4;
            break;
        case 0x52:
            this->load("D", "D");
            cycle_count = 4;
            break;
        case 0x53:
            this->load("D", "E");
            cycle_count = 4;
            break;
        case 0x54:
            this->load("D", "H");
            cycle_count = 4;
            break;
        case 0x55:
            this->load("D", "L");
            cycle_count = 4;
            break;
        case 0x56:
            this->load_from_mem("D", "HL");
            cycle_count = 8;
            break;
        case 0x58:
            this->load("E", "B");
            cycle_count = 4;
            break;
        case 0x59:
            this->load("E", "C");
            cycle_count = 4;
            break;
        case 0x5A:
            this->load("E", "D");
            cycle_count = 4;
            break;
        case 0x5B:
            this->load("E", "E");
            cycle_count = 4;
            break;
        case 0x5C:
            this->load("E", "H");
            cycle_count = 4;
            break;
        case 0x5D:
            this->load("E", "L");
            cycle_count = 4;
            break;
        case 0x5E:
            this->load_from_mem("E", "HL");
            cycle_count = 8;
            break;
        case 0x60:
            this->load("H", "B");
            cycle_count = 4;
            break;
        case 0x61:
            this->load("H", "C");
            cycle_count = 4;
            break;
        case 0x62:
            this->load("H", "D");
            cycle_count = 4;
            break;
        case 0x63:
            this->load("H", "E");
            cycle_count = 4;
            break;
        case 0x64:
            this->load("H", "H");
            cycle_count = 4;
            break;
        case 0x65:
            this->load("H", "L");
            cycle_count = 4;
            break;
        case 0x66:
            this->load_from_mem("H", "HL");
            cycle_count = 8;
            break;
        case 0x68:
            this->load("L", "B");
            cycle_count = 4;
            break;
        case 0x69:
            this->load("L", "C");
            cycle_count = 4;
            break;
        case 0x6A:
            this->load("L", "D");
            cycle_count = 4;
            break;
        case 0x6B:
            this->load("L", "E");
            cycle_count = 4;
            break;
        case 0x6C:
            this->load("L", "H");
            cycle_count = 4;
            break;
        case 0x6D:
            this->load("L", "L");
            cycle_count = 4;
            break;
        case 0x6E:
            this->load_from_mem("L", "HL");
            cycle_count = 8;
            break;
        case 0x70:
            this->load_to_mem("HL", "B");
            cycle_count = 8;
            break;
        case 0x71:
            this->load_to_mem("HL", "C");
            cycle_count = 8;
            break;
        case 0x72:
            this->load_to_mem("HL", "D");
            cycle_count = 8;
            break;
        case 0x73:
            this->load_to_mem("HL", "E");
            cycle_count = 8;
            break;
        case 0x74:
            this->load_to_mem("HL", "H");
            cycle_count = 8;
            break;
        case 0x75:
            this->load_to_mem("HL", "L");
            cycle_count = 8;
            break;
        case 0x36:
            arg_1 = this->fetch_op();
            this->load_to_mem("HL", arg_1);
            cycle_count = 12;
            break;
        // LD A, n
        case 0x0A:
            this->load_from_mem("A", "BC");
            cycle_count = 8;
            break;
        case 0x1A:
            this->load_from_mem("A", "DE");
            cycle_count = 8;
            break;
        case 0xFA:
            arg_1 = this->fetch_op();
            arg_2 = this->fetch_op();
            arg16bit = (arg_2 << 8) | arg_1;

            this->load_from_mem("A", arg16bit);
            cycle_count = 16;
            break;
        case 0x3E:
            arg_1 = this->fetch_op();
            this->load("A", arg_1);
            cycle_count = 8;
            break;
        // LD n, A
        case 0x47:
            this->load("B", "A");
            cycle_count = 4;
            break;
        case 0x4F:
            this->load("C", "A");
            cycle_count = 4;
            break;
        case 0x57:
            this->load("D", "A");
            cycle_count = 4;
            break;
        case 0x5F:
            this->load("E", "A");
            cycle_count = 4;
            break;
        case 0x67:
            this->load("H", "A");
            cycle_count = 4;
            break;
        case 0x6F:
            this->load("L", "A");
            cycle_count = 4;
            break;
        case 0x02:
            this->load_to_mem("BC", "A");
            cycle_count = 8;
            break;
        case 0x12:
            this->load_to_mem("DE", "A");
            cycle_count = 8;
            break;
        case 0x77:
            this->load_to_mem("HL", "A");
            cycle_count = 8;
            break;
        case 0xEA:
            arg_1 = this->fetch_op();
            arg_2 = this->fetch_op();
            arg16bit = (arg_2 << 8) | arg_1;

            this->load_to_mem(arg16bit, "A");
            cycle_count = 16;
            break;
        // LD A, (C)
        case 0xF2:
            arg16bit = 0xFF00 + this->read_register("C");
            this->load_from_mem("A", arg16bit);
            cycle_count = 8;
            break;
        // LD (C), A
        case 0xE2:
            arg16bit = 0xFF00 + this->read_register("C");
            this->load_to_mem(arg16bit, "A");
            cycle_count = 8;
            break;
        // LDD A, (HL)
        case 0x3A:
            this->load_from_mem("A", "HL");
            this->alu_dec_16bit("HL");
            cycle_count = 8;
            break;
        // LDD (HL), A
        case 0x32:
            this->load_to_mem("HL", "A");
            this->alu_dec_16bit("HL");
            cycle_count = 8;
            break;
        // LDI A, (HL)
        case 0x2A:
            this->load_from_mem("A", "HL");
            this->alu_inc_16bit("HL");
            cycle_count = 8;
            break;
        // LDI (HL), A
        case 0x22:
            this->load_to_mem("HL", "A");
            this->alu_inc_16bit("HL");
            cycle_count = 8;
            break;
        // LDH (n), A
        case 0xE0:
            arg16bit = 0xFF00 + this->fetch_op();
            this->load_to_mem(arg16bit, "A");
            cycle_count = 12;
            break;
        // LDH A, (n)
        case 0xF0:
            arg16bit = 0xFF00 + this->fetch_op();
            this->load_from_mem("A", arg16bit);
            cycle_count = 12;
            break;
        /****    16-Bit Loads    ****/
        // LD n, nn
        case 0x01:
            arg_1 = this->fetch_op();
            arg_2 = this->fetch_op();
            arg16bit = (arg_2 << 8) | arg_1;
            std::cout << arg16bit << std::endl;

            this->load("BC", arg16bit);
            break;
        case 0x11:
            arg_1 = this->fetch_op();
            arg_2 = this->fetch_op();
            arg16bit = (arg_2 << 8) | arg_1;

            this->load("DE", arg16bit);
            break;
        case 0x21:
            arg_1 = this->fetch_op();
            arg_2 = this->fetch_op();
            arg16bit = (arg_2 << 8) | arg_1;

            this->load("HL", arg16bit);
            break;
        case 0x31:
            arg_1 = this->fetch_op();
            arg_2 = this->fetch_op();
            arg16bit = (arg_2 << 8) | arg_1;

            this->load("SP", arg16bit);
            break;
        // LD SP, HL
        case 0xF9:
            this->load("SP", "HL");
            break;
        // LDHL SP, n
        case 0xF8:
            arg_1 = this->fetch_op();

            this->load_HL(arg_1);
            break;
        // LD (nn), SP
        case 0x08:
            // TODO Learn how to implement this instruction
            std::cout << "LD " << static_cast<int>(arg_1) << ", SP" << std::endl;
            break;
        // PUSH nn
        case 0xF5:
            this->push_stack("AF");
            break;
        case 0xC5:
            this->push_stack("BC");
            break;
        case 0xD5:
            this->push_stack("DE");
            break;
        case 0xE5:
            this->push_stack("HL");
            break;
        // POP nn
        case 0xF1:
            this->pop_stack("AF");
            break;
        case 0xC1:
            this->pop_stack("BC");
            break;
        case 0xD1:
            this->pop_stack("DE");
            break;
        case 0xE1:
            this->pop_stack("HL");
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
            arg_1 = this->fetch_op();
            this->alu_add(arg_1, false);
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
            arg_1 = this->fetch_op();
            this->alu_add(arg_1, true);
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
            arg_1 = this->fetch_op();
            this->alu_sub(arg_1, false);
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
            arg_1 = this->fetch_op();
            this->alu_sub(arg_1, true);
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
            arg_1 = this->fetch_op();
            this->alu_or(arg_1);
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
            arg_1 = this->fetch_op();
            this->alu_xor(arg_1);
            break;
        // CP n
        case 0xBF:
            this->alu_cp("A");
            break;
        case 0xB8:
            this->alu_cp("B");
            break;
        case 0xB9:
            this->alu_cp("C");
            break;
        case 0xBA:
            this->alu_cp("D");
            break;
        case 0xBB:
            this->alu_cp("E");
            break;
        case 0xBC:
            this->alu_cp("H");
            break;
        case 0xBD:
            this->alu_cp("L");
            break;
        case 0xBE:
            this->alu_cp("HL");
            break;
        case 0xFE:
            arg_1 = this->fetch_op();
            this->alu_cp(arg_1);
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
        case 0x3D:
            this->alu_dec("A");
            break;
        case 0x05:
            this->alu_dec("B");
            break;
        case 0x0D:
            this->alu_dec("C");
            break;
        case 0x15:
            this->alu_dec("D");
            break;
        case 0x1D:
            this->alu_dec("E");
            break;
        case 0x25:
            this->alu_dec("H");
            break;
        case 0x2D:
            this->alu_dec("L");
            break;
        case 0x35:
            this->alu_dec("HL");
            break;
        /****    16-Bit Arithmetic    ****/
        // ADD HL, n
        case 0x09:
            this->alu_add_HL("BC");
            break;
        case 0x19:
            this->alu_add_HL("DE");
            break;
        case 0x29:
            this->alu_add_HL("HL");
            break;
        case 0x39:
            this->alu_add_HL("SP");
            break;
        // ADD SP, n
        case 0xE8:
            arg_1 = this->fetch_op();
            this->alu_add_SP(arg_1);
            break;
        // INC nn
        case 0x03:
            this->alu_inc_16bit("BC");
            break;
        case 0x13:
            this->alu_inc_16bit("DE");
            break;
        case 0x23:
            this->alu_inc_16bit("HL");
            break;
        case 0x33:
            this->alu_inc_16bit("SP");
            break;
        // DEC nn
        case 0x0B:
            this->alu_dec_16bit("BC");
            break;
        case 0x1B:
            this->alu_dec_16bit("DE");
            break;
        case 0x2B:
            this->alu_dec_16bit("HL");
            break;
        case 0x3B:
            this->alu_dec_16bit("SP");
            break;
        /****    Rotates and Shifts    ****/
        // RLCA
        case 0x07:
            this->rotate_left(false);
            break;
        // RLA
        case 0x17:
            this->rotate_left(true);
            break;
        // RRCA
        case 0x0F:
            this->rotate_right(false);
            break;
        // RRA
        case 0x1F:
            this->rotate_right(true);
            break;
        /****    Jumps    ****/
        // JP nn
        case 0xC3:
            // LSB
            arg_1 = this->fetch_op();
            // MSB
            arg_2 = this->fetch_op();
            arg16bit = (arg_2 << 8) | arg_1;

            this->jump(arg16bit);
            break;
        // JP cc, nn
        case 0xC2:
            // LSB
            arg_1 = this->fetch_op();
            // MSB
            arg_2 = this->fetch_op();
            arg16bit = (arg_2 << 8) | arg_1;

            this->jump_conditional(arg16bit, ZERO_FLAG, false);
            break;
        case 0xCA:
            // LSB
            arg_1 = this->fetch_op();
            // MSB
            arg_2 = this->fetch_op();
            arg16bit = (arg_2 << 8) | arg_1;

            this->jump_conditional(arg16bit, ZERO_FLAG, true);
            break;
        case 0xD2:
            // LSB
            arg_1 = this->fetch_op();
            // MSB
            arg_2 = this->fetch_op();
            arg16bit = (arg_2 << 8) | arg_1;

            this->jump_conditional(arg16bit, CARRY_FLAG, false);
            break;
        case 0xDA:
            // LSB
            arg_1 = this->fetch_op();
            // MSB
            arg_2 = this->fetch_op();
            arg16bit = (arg_2 << 8) | arg_1;

            this->jump_conditional(arg16bit, CARRY_FLAG, true);
            break;
        // JP HL
        case 0xE9:
            this->jump_hl();
            break;
        // JP n
        case 0x18:
            arg_1 = this->fetch_op();
            this->jump_add(arg_1);
            break;
        // JR cc, n
        case 0x20:
            arg_1 = this->fetch_op();
            this->jump_add_conditional(arg_1, ZERO_FLAG, false);
            break;
        case 0x28:
            arg_1 = this->fetch_op();
            this->jump_add_conditional(arg_1, ZERO_FLAG, true);
            break;
        case 0x30:
            arg_1 = this->fetch_op();
            this->jump_add_conditional(arg_1, CARRY_FLAG, false);
            break;
        case 0x38:
            arg_1 = this->fetch_op();
            this->jump_add_conditional(arg_1, CARRY_FLAG, true);
            break;
        /****    Calls    ****/
        // CALL nn
        case 0xCD:
            arg_1 = this->fetch_op();
            arg_2 = this->fetch_op();
            arg16bit = (arg_2 << 8) | arg_1;

            this->call(arg16bit);
            break;
        // CALL cc, nn
        case 0xC4:
            arg_1 = this->fetch_op();
            arg_2 = this->fetch_op();
            arg16bit = (arg_2 << 8) | arg_1;

            this->call(arg16bit, ZERO_FLAG, false);
            break;
        case 0xCC:
            arg_1 = this->fetch_op();
            arg_2 = this->fetch_op();
            arg16bit = (arg_2 << 8) | arg_1;

            this->call(arg16bit, ZERO_FLAG, true);
            break;
        case 0xD4:
            arg_1 = this->fetch_op();
            arg_2 = this->fetch_op();
            arg16bit = (arg_2 << 8) | arg_1;

            this->call(arg16bit, CARRY_FLAG, false);
            break;
        case 0xDC:
            arg_1 = this->fetch_op();
            arg_2 = this->fetch_op();
            arg16bit = (arg_2 << 8) | arg_1;

            this->call(arg16bit, CARRY_FLAG, true);
            break;
        /****    Restarts    ****/
        // RST n
        case 0xC7:
            this->restart(0x00);
            break;
        case 0xCF:
            this->restart(0x08);
            break;
        case 0xD7:
            this->restart(0x10);
            break;
        case 0xDF:
            this->restart(0x18);
            break;
        case 0xE7:
            this->restart(0x20);
            break;
        case 0xEF:
            this->restart(0x28);
            break;
        case 0xF7:
            this->restart(0x30);
            break;
        case 0xFF:
            this->restart(0x38);
            break;
        /****    Returns    ****/
        // RET
        case 0xC9:
            this->ret();
            break;
        // RET cc
        case 0xC0:
            this->ret(ZERO_FLAG, false);
            break;
        case 0xC8:
            this->ret(ZERO_FLAG, true);
            break;
        case 0xD0:
            this->ret(CARRY_FLAG, false);
            break;
        case 0xD8:
            this->ret(CARRY_FLAG, true);
            break;
        // RETI
        case 0xD9:
            this->ret_enable_interrupts();
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
                case 0x07:
                    this->rotate_left("A", false);
                    break;
                case 0x00:
                    this->rotate_left("B", false);
                    break;
                case 0x01:
                    this->rotate_left("C", false);
                    break;
                case 0x02:
                    this->rotate_left("D", false);
                    break;
                case 0x03:
                    this->rotate_left("E", false);
                    break;
                case 0x04:
                    this->rotate_left("H", false);
                    break;
                case 0x05:
                    this->rotate_left("L", false);
                    break;
                case 0x06:
                    this->rotate_left("HL", false);
                    break;
                // RL n
                case 0x17:
                    this->rotate_left("A", true);
                    break;
                case 0x10:
                    this->rotate_left("B", true);
                    break;
                case 0x11:
                    this->rotate_left("C", true);
                    break;
                case 0x12:
                    this->rotate_left("D", true);
                    break;
                case 0x13:
                    this->rotate_left("E", true);
                    break;
                case 0x14:
                    this->rotate_left("H", true);
                    break;
                case 0x15:
                    this->rotate_left("L", true);
                    break;
                case 0x16:
                    this->rotate_left("HL", true);
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
            }

            break;

        // Default, opcode not implemented
        default:
            std::cerr << "Opcode " << static_cast<int>(opcode) << " not implemented" << std::endl;
    }

    return cycle_count;
}

void CPU::write_register(const std::string &reg, uint16_t data) {
    m_registers.write_register(reg, data);
}

uint16_t CPU::read_register(const std::string &reg) {
    return m_registers.read_register(reg);
}

void CPU::write_memory(uint8_t data) {
    this->write_memory("HL", data);
}

void CPU::write_memory(const std::string &reg, uint8_t data) {
    uint16_t address = this->read_register(reg);
    this->m_memory_map.write(address, data);
}

uint8_t CPU::read_memory() {
    return this->read_memory("HL");
}

uint8_t CPU::read_memory(const std::string &reg) {
    uint16_t address = this->read_register(reg);
    return this->m_memory_map.read(address);
}

void CPU::set_flag_register(CPUFlag_t flag, bool value) {
    uint8_t flag_register_val = this->read_register("F");
    uint8_t val = (value) ? flag : 0;

    // Reset flag value to 0
    flag_register_val &= ~flag;
    this->write_register("F", flag_register_val);
    // Set new flag value
    flag_register_val |= val;
    this->write_register("F", flag_register_val);
}

bool CPU::read_flag_register(CPUFlag_t flag) {
    return (this->read_register("F") & flag) == flag;
}

void CPU::reset_flag_register() {
    this->write_register("F", 0);
}