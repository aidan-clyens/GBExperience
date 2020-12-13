#include "cpu.h"


CPU::CPU(MemoryMap &mem_map):
m_memory_map(mem_map),
m_halted(false),
m_stopped(false),
m_interrupts_enabled(true)
{

}

CPU::~CPU() {

}

int CPU::tick() {
    // Handle interrupts
    this->handle_interrupts();

    // Check if halted
    int cycle_count = 4;
    if (this->is_running()) {
        
        log_cpu_no_new_line("0x%X: ", this->read_register(REG_PC));
        

        // Fetch next opcode and execute
        uint8_t opcode = this->fetch_op();
        cycle_count = this->decode_op(opcode);
    }

    return cycle_count;
}

uint8_t CPU::fetch_op() {
    uint16_t address = this->read_register(REG_PC);
    this->write_register(REG_PC, address + 1);

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
            
            log_cpu("NOP" );
            
            cycle_count = 4;
            break;
        // HALT
        case 0x76:
            this->halt();
            cycle_count = 4;
            break;
        // STOP
        case 0x10:
            this->stop();
            cycle_count = 4;
            break;
        // DAA
        case 0x27:
            this->daa();
            cycle_count = 4;
            break;
        // CPL
        case 0x2F:
            this->complement();
            cycle_count = 4;
            break;
        // CCF
        case 0x3F:
            this->complement_carry();
            cycle_count = 4;
            break;
        // SCF
        case 0x37:
            this->set_carry();
            cycle_count = 4;
            break;
        // DI
        case 0xF3:
            this->disable_interrupts();
            cycle_count = 4;
            break;
        // EI
        case 0xFB:
            this->enable_interrupts();
            cycle_count = 4;
            break;
        /****    8-Bit Loads    ****/
        // LD nn, n
        case 0x06:
            arg_1 = this->fetch_op();
            this->load(REG_B, arg_1);
            cycle_count = 4;
            break;
        case 0x0E:
            arg_1 = this->fetch_op();
            this->load(REG_C, arg_1);
            cycle_count = 4;
            break;
        case 0x16:
            arg_1 = this->fetch_op();
            this->load(REG_D, arg_1);
            cycle_count = 4;
            break;
        case 0x1E:
            arg_1 = this->fetch_op();
            this->load(REG_E, arg_1);
            cycle_count = 4;
            break;
        case 0x26:
            arg_1 = this->fetch_op();
            this->load(REG_H, arg_1);
            cycle_count = 4;
            break;
        case 0x2E:
            arg_1 = this->fetch_op();
            this->load(REG_L, arg_1);
            cycle_count = 4;
            break;
        // LD r1, r2
        case 0x7F:
            this->load(REG_A, REG_A);
            cycle_count = 4;
            break;
        case 0x78:
            this->load(REG_A, REG_B);
            cycle_count = 4;
            break;
        case 0x79:
            this->load(REG_A, REG_C);
            cycle_count = 4;
            break;
        case 0x7A:
            this->load(REG_A, REG_D);
            cycle_count = 4;
            break;
        case 0x7B:
            this->load(REG_A, REG_E);
            cycle_count = 4;
            break;
        case 0x7C:
            this->load(REG_A, REG_H);
            cycle_count = 4;
            break;
        case 0x7D:
            this->load(REG_A, REG_L);
            cycle_count = 4;
            break;
        case 0x7E:
            this->load_from_mem(REG_A, REG_HL);
            cycle_count = 8;
            break;
        case 0x40:
            this->load(REG_B, REG_B);
            cycle_count = 4;
            break;
        case 0x41:
            this->load(REG_B, REG_C);
            cycle_count = 4;
            break;
        case 0x42:
            this->load(REG_B, REG_D);
            cycle_count = 4;
            break;
        case 0x43:
            this->load(REG_B, REG_E);
            cycle_count = 4;
            break;
        case 0x44:
            this->load(REG_B, REG_H);
            cycle_count = 4;
            break;
        case 0x45:
            this->load(REG_B, REG_L);
            cycle_count = 4;
            break;
        case 0x46:
            this->load_from_mem(REG_B, REG_HL);
            cycle_count = 8;
            break;
        case 0x48:
            this->load(REG_C, REG_B);
            cycle_count = 4;
            break;
        case 0x49:
            this->load(REG_C, REG_C);
            cycle_count = 4;
            break;
        case 0x4A:
            this->load(REG_C, REG_D);
            cycle_count = 4;
            break;
        case 0x4B:
            this->load(REG_C, REG_E);
            cycle_count = 4;
            break;
        case 0x4C:
            this->load(REG_C, REG_H);
            cycle_count = 4;
            break;
        case 0x4D:
            this->load(REG_C, REG_L);
            cycle_count = 4;
            break;
        case 0x4E:
            this->load_from_mem(REG_C, REG_HL);
            cycle_count = 8;
            break;
        case 0x50:
            this->load(REG_D, REG_B);
            cycle_count = 4;
            break;
        case 0x51:
            this->load(REG_D, REG_C);
            cycle_count = 4;
            break;
        case 0x52:
            this->load(REG_D, REG_D);
            cycle_count = 4;
            break;
        case 0x53:
            this->load(REG_D, REG_E);
            cycle_count = 4;
            break;
        case 0x54:
            this->load(REG_D, REG_H);
            cycle_count = 4;
            break;
        case 0x55:
            this->load(REG_D, REG_L);
            cycle_count = 4;
            break;
        case 0x56:
            this->load_from_mem(REG_D, REG_HL);
            cycle_count = 8;
            break;
        case 0x58:
            this->load(REG_E, REG_B);
            cycle_count = 4;
            break;
        case 0x59:
            this->load(REG_E, REG_C);
            cycle_count = 4;
            break;
        case 0x5A:
            this->load(REG_E, REG_D);
            cycle_count = 4;
            break;
        case 0x5B:
            this->load(REG_E, REG_E);
            cycle_count = 4;
            break;
        case 0x5C:
            this->load(REG_E, REG_H);
            cycle_count = 4;
            break;
        case 0x5D:
            this->load(REG_E, REG_L);
            cycle_count = 4;
            break;
        case 0x5E:
            this->load_from_mem(REG_E, REG_HL);
            cycle_count = 8;
            break;
        case 0x60:
            this->load(REG_H, REG_B);
            cycle_count = 4;
            break;
        case 0x61:
            this->load(REG_H, REG_C);
            cycle_count = 4;
            break;
        case 0x62:
            this->load(REG_H, REG_D);
            cycle_count = 4;
            break;
        case 0x63:
            this->load(REG_H, REG_E);
            cycle_count = 4;
            break;
        case 0x64:
            this->load(REG_H, REG_H);
            cycle_count = 4;
            break;
        case 0x65:
            this->load(REG_H, REG_L);
            cycle_count = 4;
            break;
        case 0x66:
            this->load_from_mem(REG_H, REG_HL);
            cycle_count = 8;
            break;
        case 0x68:
            this->load(REG_L, REG_B);
            cycle_count = 4;
            break;
        case 0x69:
            this->load(REG_L, REG_C);
            cycle_count = 4;
            break;
        case 0x6A:
            this->load(REG_L, REG_D);
            cycle_count = 4;
            break;
        case 0x6B:
            this->load(REG_L, REG_E);
            cycle_count = 4;
            break;
        case 0x6C:
            this->load(REG_L, REG_H);
            cycle_count = 4;
            break;
        case 0x6D:
            this->load(REG_L, REG_L);
            cycle_count = 4;
            break;
        case 0x6E:
            this->load_from_mem(REG_L, REG_HL);
            cycle_count = 8;
            break;
        case 0x70:
            this->load_to_mem(REG_HL, REG_B);
            cycle_count = 8;
            break;
        case 0x71:
            this->load_to_mem(REG_HL, REG_C);
            cycle_count = 8;
            break;
        case 0x72:
            this->load_to_mem(REG_HL, REG_D);
            cycle_count = 8;
            break;
        case 0x73:
            this->load_to_mem(REG_HL, REG_E);
            cycle_count = 8;
            break;
        case 0x74:
            this->load_to_mem(REG_HL, REG_H);
            cycle_count = 8;
            break;
        case 0x75:
            this->load_to_mem(REG_HL, REG_L);
            cycle_count = 8;
            break;
        case 0x36:
            arg_1 = this->fetch_op();
            this->load_to_mem(REG_HL, arg_1);
            cycle_count = 12;
            break;
        // LD A, n
        case 0x0A:
            this->load_from_mem(REG_A, REG_BC);
            cycle_count = 8;
            break;
        case 0x1A:
            this->load_from_mem(REG_A, REG_DE);
            cycle_count = 8;
            break;
        case 0xFA:
            arg_1 = this->fetch_op();
            arg_2 = this->fetch_op();
            arg16bit = (arg_2 << 8) | arg_1;

            this->load_from_mem(REG_A, arg16bit);
            cycle_count = 16;
            break;
        case 0x3E:
            arg_1 = this->fetch_op();
            this->load(REG_A, arg_1);
            cycle_count = 8;
            break;
        // LD n, A
        case 0x47:
            this->load(REG_B, REG_A);
            cycle_count = 4;
            break;
        case 0x4F:
            this->load(REG_C, REG_A);
            cycle_count = 4;
            break;
        case 0x57:
            this->load(REG_D, REG_A);
            cycle_count = 4;
            break;
        case 0x5F:
            this->load(REG_E, REG_A);
            cycle_count = 4;
            break;
        case 0x67:
            this->load(REG_H, REG_A);
            cycle_count = 4;
            break;
        case 0x6F:
            this->load(REG_L, REG_A);
            cycle_count = 4;
            break;
        case 0x02:
            this->load_to_mem(REG_BC, REG_A);
            cycle_count = 8;
            break;
        case 0x12:
            this->load_to_mem(REG_DE, REG_A);
            cycle_count = 8;
            break;
        case 0x77:
            this->load_to_mem(REG_HL, REG_A);
            cycle_count = 8;
            break;
        case 0xEA:
            arg_1 = this->fetch_op();
            arg_2 = this->fetch_op();
            arg16bit = (arg_2 << 8) | arg_1;

            this->load_to_mem(arg16bit, REG_A);
            cycle_count = 16;
            break;
        // LD A, (C)
        case 0xF2:
            arg16bit = 0xFF00 + this->read_register(REG_C);
            this->load_from_mem(REG_A, arg16bit);
            cycle_count = 8;
            break;
        // LD (C), A
        case 0xE2:
            arg16bit = 0xFF00 + this->read_register(REG_C);
            this->load_to_mem(arg16bit, REG_A);
            cycle_count = 8;
            break;
        // LDD A, (HL)
        case 0x3A:
            this->load_from_mem(REG_A, REG_HL);
            this->alu_dec_16bit(REG_HL);
            cycle_count = 8;
            break;
        // LDD (HL), A
        case 0x32:
            this->load_to_mem(REG_HL, REG_A);
            this->alu_dec_16bit(REG_HL);
            cycle_count = 8;
            break;
        // LDI A, (HL)
        case 0x2A:
            this->load_from_mem(REG_A, REG_HL);
            this->alu_inc_16bit(REG_HL);
            cycle_count = 8;
            break;
        // LDI (HL), A
        case 0x22:
            this->load_to_mem(REG_HL, REG_A);
            this->alu_inc_16bit(REG_HL);
            cycle_count = 8;
            break;
        // LDH (n), A
        case 0xE0:
            arg16bit = 0xFF00 + this->fetch_op();
            this->load_to_mem(arg16bit, REG_A);
            cycle_count = 12;
            break;
        // LDH A, (n)
        case 0xF0:
            arg16bit = 0xFF00 + this->fetch_op();
            this->load_from_mem(REG_A, arg16bit);
            cycle_count = 12;
            break;
        /****    16-Bit Loads    ****/
        // LD n, nn
        case 0x01:
            arg_1 = this->fetch_op();
            arg_2 = this->fetch_op();
            arg16bit = (arg_2 << 8) | arg_1;

            this->load(REG_BC, arg16bit);
            cycle_count = 12;
            break;
        case 0x11:
            arg_1 = this->fetch_op();
            arg_2 = this->fetch_op();
            arg16bit = (arg_2 << 8) | arg_1;

            this->load(REG_DE, arg16bit);
            cycle_count = 12;
            break;
        case 0x21:
            arg_1 = this->fetch_op();
            arg_2 = this->fetch_op();
            arg16bit = (arg_2 << 8) | arg_1;

            this->load(REG_HL, arg16bit);
            cycle_count = 12;
            break;
        case 0x31:
            arg_1 = this->fetch_op();
            arg_2 = this->fetch_op();
            arg16bit = (arg_2 << 8) | arg_1;

            this->load(REG_SP, arg16bit);
            cycle_count = 12;
            break;
        // LD SP, HL
        case 0xF9:
            this->load(REG_SP, REG_HL);
            cycle_count = 8;
            break;
        // LDHL SP, n
        case 0xF8:
            arg_1 = this->fetch_op();

            this->load_HL(arg_1);
            cycle_count = 12;
            break;
        // LD (nn), SP
        case 0x08:
            arg_1 = this->fetch_op();
            arg_2 = this->fetch_op();
            arg16bit = (arg_2 << 8) | arg_1;

            this->load_to_mem16bit(arg16bit, REG_SP);            
            cycle_count = 20;
            break;
        // PUSH nn
        case 0xF5:
            log_cpu("PUSH AF");

            this->push_stack(REG_AF);
            cycle_count = 16;
            break;
        case 0xC5:
            log_cpu("PUSH BC");

            this->push_stack(REG_BC);
            cycle_count = 16;
            break;
        case 0xD5:
            log_cpu("PUSH DE");

            this->push_stack(REG_DE);
            cycle_count = 16;
            break;
        case 0xE5:
            log_cpu("PUSH HL");

            this->push_stack(REG_HL);
            cycle_count = 16;
            break;
        // POP nn
        case 0xF1:
            log_cpu("POP AF");

            this->pop_stack(REG_AF);
            cycle_count = 12;
            break;
        case 0xC1:
            log_cpu("POP BC");

            this->pop_stack(REG_BC);
            cycle_count = 12;
            break;
        case 0xD1:
            log_cpu("POP DE");

            this->pop_stack(REG_DE);
            cycle_count = 12;
            break;
        case 0xE1:
            log_cpu("POP HL");

            this->pop_stack(REG_HL);
            cycle_count = 12;
            break;
        /****    8-Bit ALU    ****/
        // ADD A, n
        case 0x87:
            this->alu_add(REG_A, false);
            cycle_count = 4;
            break;
        case 0x80:
            this->alu_add(REG_B, false);
            cycle_count = 4;
            break;
        case 0x81:
            this->alu_add(REG_C, false);
            cycle_count = 4;
            break;
        case 0x82:
            this->alu_add(REG_D, false);
            cycle_count = 4;
            break;
        case 0x83:
            this->alu_add(REG_E, false);
            cycle_count = 4;
            break;
        case 0x84:
            this->alu_add(REG_H, false);
            cycle_count = 4;
            break;
        case 0x85:
            this->alu_add(REG_L, false);
            cycle_count = 4;
            break;
        case 0x86:
            this->alu_add(REG_HL, false);
            cycle_count = 8;
            break;
        case 0xC6:
            arg_1 = this->fetch_op();
            this->alu_add(arg_1, false);
            cycle_count = 8;
            break;
        // ADC A, n
        case 0x8F:
            this->alu_add(REG_A, true);
            cycle_count = 4;
            break;
        case 0x88:
            this->alu_add(REG_B, true);
            cycle_count = 4;
            break;
        case 0x89:
            this->alu_add(REG_C, true);
            cycle_count = 4;
            break;
        case 0x8A:
            this->alu_add(REG_D, true);
            cycle_count = 4;
            break;
        case 0x8B:
            this->alu_add(REG_E, true);
            cycle_count = 4;
            break;
        case 0x8C:
            this->alu_add(REG_H, true);
            cycle_count = 4;
            break;
        case 0x8D:
            this->alu_add(REG_L, true);
            cycle_count = 4;
            break;
        case 0x8E:
            this->alu_add(REG_HL, true);
            cycle_count = 8;
            break;
        case 0xCE:
            arg_1 = this->fetch_op();
            this->alu_add(arg_1, true);
            cycle_count = 8;
            break;
        // SUB n
        case 0x97:
            this->alu_sub(REG_A, false);
            cycle_count = 4;
            break;
        case 0x90:
            this->alu_sub(REG_B, false);
            cycle_count = 4;
            break;
        case 0x91:
            this->alu_sub(REG_C, false);
            cycle_count = 4;
            break;
        case 0x92:
            this->alu_sub(REG_D, false);
            cycle_count = 4;
            break;
        case 0x93:
            this->alu_sub(REG_E, false);
            cycle_count = 4;
            break;
        case 0x94:
            this->alu_sub(REG_H, false);
            cycle_count = 4;
            break;
        case 0x95:
            this->alu_sub(REG_L, false);
            cycle_count = 4;
            break;
        case 0x96:
            this->alu_sub(REG_HL, false);
            cycle_count = 8;
            break;
        case 0xD6:
            arg_1 = this->fetch_op();
            this->alu_sub(arg_1, false);
            cycle_count = 8;
            break;
        // SBC n
        case 0x9F:
            this->alu_sub(REG_A, true);
            cycle_count = 4;
            break;
        case 0x98:
            this->alu_sub(REG_B, true);
            cycle_count = 4;
            break;
        case 0x99:
            this->alu_sub(REG_C, true);
            cycle_count = 4;
            break;
        case 0x9A:
            this->alu_sub(REG_D, true);
            cycle_count = 4;
            break;
        case 0x9B:
            this->alu_sub(REG_E, true);
            cycle_count = 4;
            break;
        case 0x9C:
            this->alu_sub(REG_H, true);
            cycle_count = 4;
            break;
        case 0x9D:
            this->alu_sub(REG_L, true);
            cycle_count = 4;
            break;
        case 0x9E:
            this->alu_sub(REG_HL, true);
            cycle_count = 8;
            break;
        case 0xDE:
            arg_1 = this->fetch_op();
            this->alu_sub(arg_1, true);
            cycle_count = 8;
            break;
        // AND n
        case 0xA7:
            this->alu_and(REG_A);
            cycle_count = 4;
            break;
        case 0xA0:
            this->alu_and(REG_B);
            cycle_count = 4;
            break;
        case 0xA1:
            this->alu_and(REG_C);
            cycle_count = 4;
            break;
        case 0xA2:
            this->alu_and(REG_D);
            cycle_count = 4;
            break;
        case 0xA3:
            this->alu_and(REG_E);
            cycle_count = 4;
            break;
        case 0xA4:
            this->alu_and(REG_H);
            cycle_count = 4;
            break;
        case 0xA5:
            this->alu_and(REG_L);
            cycle_count = 4;
            break;
        case 0xA6:
            this->alu_and(REG_HL);
            cycle_count = 8;
            break;
        case 0xE6:
            arg_1 = this->fetch_op();
            this->alu_and(arg_1);
            cycle_count = 8;
            break;
        // OR n
        case 0xB7:
            this->alu_or(REG_A);
            cycle_count = 4;
            break;
        case 0xB0:
            this->alu_or(REG_B);
            cycle_count = 4;
            break;
        case 0xB1:
            this->alu_or(REG_C);
            cycle_count = 4;
            break;
        case 0xB2:
            this->alu_or(REG_D);
            cycle_count = 4;
            break;
        case 0xB3:
            this->alu_or(REG_E);
            cycle_count = 4;
            break;
        case 0xB4:
            this->alu_or(REG_H);
            cycle_count = 4;
            break;
        case 0xB5:
            this->alu_or(REG_L);
            cycle_count = 4;
            break;
        case 0xB6:
            this->alu_or(REG_HL);
            cycle_count = 8;
            break;
        case 0xF6:
            arg_1 = this->fetch_op();
            this->alu_or(arg_1);
            cycle_count = 8;
            break;
        // XOR n
        case 0xAF:
            this->alu_xor(REG_A);
            cycle_count = 4;
            break;
        case 0xA8:
            this->alu_xor(REG_B);
            cycle_count = 4;
            break;
        case 0xA9:
            this->alu_xor(REG_C);
            cycle_count = 4;
            break;
        case 0xAA:
            this->alu_xor(REG_D);
            cycle_count = 4;
            break;
        case 0xAB:
            this->alu_xor(REG_E);
            cycle_count = 4;
            break;
        case 0xAC:
            this->alu_xor(REG_H);
            cycle_count = 4;
            break;
        case 0xAD:
            this->alu_xor(REG_L);
            cycle_count = 4;
            break;
        case 0xAE:
            this->alu_xor(REG_HL);
            cycle_count = 8;
            break;
        case 0xEE:
            arg_1 = this->fetch_op();
            this->alu_xor(arg_1);
            cycle_count = 8;
            break;
        // CP n
        case 0xBF:
            this->alu_cp(REG_A);
            cycle_count = 4;
            break;
        case 0xB8:
            this->alu_cp(REG_B);
            cycle_count = 4;
            break;
        case 0xB9:
            this->alu_cp(REG_C);
            cycle_count = 4;
            break;
        case 0xBA:
            this->alu_cp(REG_D);
            cycle_count = 4;
            break;
        case 0xBB:
            this->alu_cp(REG_E);
            cycle_count = 4;
            break;
        case 0xBC:
            this->alu_cp(REG_H);
            cycle_count = 4;
            break;
        case 0xBD:
            this->alu_cp(REG_L);
            cycle_count = 4;
            break;
        case 0xBE:
            this->alu_cp(REG_HL);
            cycle_count = 8;
            break;
        case 0xFE:
            arg_1 = this->fetch_op();
            this->alu_cp(arg_1);
            cycle_count = 8;
            break;
        // INC n
        case 0x3C:
            this->alu_inc(REG_A);
            cycle_count = 4;
            break;
        case 0x04:
            this->alu_inc(REG_B);
            cycle_count = 4;
            break;
        case 0x0C:
            this->alu_inc(REG_C);
            cycle_count = 4;
            break;
        case 0x14:
            this->alu_inc(REG_D);
            cycle_count = 4;
            break;
        case 0x1C:
            this->alu_inc(REG_E);
            cycle_count = 4;
            break;
        case 0x24:
            this->alu_inc(REG_H);
            cycle_count = 4;
            break;
        case 0x2C:
            this->alu_inc(REG_L);
            cycle_count = 4;
            break;
        case 0x34:
            this->alu_inc(REG_HL);
            cycle_count = 12;
            break;
        // DEC n
        case 0x3D:
            this->alu_dec(REG_A);
            cycle_count = 4;
            break;
        case 0x05:
            this->alu_dec(REG_B);
            cycle_count = 4;
            break;
        case 0x0D:
            this->alu_dec(REG_C);
            cycle_count = 4;
            break;
        case 0x15:
            this->alu_dec(REG_D);
            cycle_count = 4;
            break;
        case 0x1D:
            this->alu_dec(REG_E);
            cycle_count = 4;
            break;
        case 0x25:
            this->alu_dec(REG_H);
            cycle_count = 4;
            break;
        case 0x2D:
            this->alu_dec(REG_L);
            cycle_count = 4;
            break;
        case 0x35:
            this->alu_dec(REG_HL);
            cycle_count = 12;
            break;
        /****    16-Bit Arithmetic    ****/
        // ADD HL, n
        case 0x09:
            this->alu_add_HL(REG_BC);
            cycle_count = 8;
            break;
        case 0x19:
            this->alu_add_HL(REG_DE);
            cycle_count = 8;
            break;
        case 0x29:
            this->alu_add_HL(REG_HL);
            cycle_count = 8;
            break;
        case 0x39:
            this->alu_add_HL(REG_SP);
            cycle_count = 8;
            break;
        // ADD SP, n
        case 0xE8:
            arg_1 = this->fetch_op();
            this->alu_add_SP(arg_1);
            cycle_count = 16;
            break;
        // INC nn
        case 0x03:
            this->alu_inc_16bit(REG_BC);
            cycle_count = 8;
            break;
        case 0x13:
            this->alu_inc_16bit(REG_DE);
            cycle_count = 8;
            break;
        case 0x23:
            this->alu_inc_16bit(REG_HL);
            cycle_count = 8;
            break;
        case 0x33:
            this->alu_inc_16bit(REG_SP);
            cycle_count = 8;
            break;
        // DEC nn
        case 0x0B:
            this->alu_dec_16bit(REG_BC);
            cycle_count = 8;
            break;
        case 0x1B:
            this->alu_dec_16bit(REG_DE);
            cycle_count = 8;
            break;
        case 0x2B:
            this->alu_dec_16bit(REG_HL);
            cycle_count = 8;
            break;
        case 0x3B:
            this->alu_dec_16bit(REG_SP);
            cycle_count = 8;
            break;
        /****    Rotates and Shifts    ****/
        // RLCA
        case 0x07:
            this->rotate_left(false);
            cycle_count = 4;
            break;
        // RLA
        case 0x17:
            this->rotate_left(true);
            cycle_count = 4;
            break;
        // RRCA
        case 0x0F:
            this->rotate_right(false);
            cycle_count = 4;
            break;
        // RRA
        case 0x1F:
            this->rotate_right(true);
            cycle_count = 4;
            break;
        /****    Jumps    ****/
        // JP nn
        case 0xC3:
            // LSB
            arg_1 = this->fetch_op();
            // MSB
            arg_2 = this->fetch_op();
            arg16bit = (arg_2 << 8) | arg_1;

            
            log_cpu("JP %X", arg16bit);
            

            this->jump(arg16bit);
            cycle_count = 12;
            break;
        // JP cc, nn
        case 0xC2:
            // LSB
            arg_1 = this->fetch_op();
            // MSB
            arg_2 = this->fetch_op();
            arg16bit = (arg_2 << 8) | arg_1;

            
            log_cpu("JP NZ %X", arg16bit);
            

            this->jump_conditional(arg16bit, ZERO_FLAG, false);
            cycle_count = 12;
            break;
        case 0xCA:
            // LSB
            arg_1 = this->fetch_op();
            // MSB
            arg_2 = this->fetch_op();
            arg16bit = (arg_2 << 8) | arg_1;

            
            log_cpu("JP Z %X", arg16bit);
            

            this->jump_conditional(arg16bit, ZERO_FLAG, true);
            cycle_count = 12;
            break;
        case 0xD2:
            // LSB
            arg_1 = this->fetch_op();
            // MSB
            arg_2 = this->fetch_op();
            arg16bit = (arg_2 << 8) | arg_1;

            
            log_cpu("JP NC %X", arg16bit);
            

            this->jump_conditional(arg16bit, CARRY_FLAG, false);
            cycle_count = 12;
            break;
        case 0xDA:
            // LSB
            arg_1 = this->fetch_op();
            // MSB
            arg_2 = this->fetch_op();
            arg16bit = (arg_2 << 8) | arg_1;

            
            log_cpu("JP C %X", arg16bit);
            

            this->jump_conditional(arg16bit, CARRY_FLAG, true);
            cycle_count = 12;
            break;
        // JP HL
        case 0xE9:
            
            log_cpu("JP (%X)", this->read_register(REG_HL));
            

            this->jump_hl();
            cycle_count = 4;
            break;
        // JR n
        case 0x18:
            arg_1 = this->fetch_op();

            
            log_cpu("JR %d", static_cast<int8_t>(arg_1));
            

            this->jump_add(arg_1);
            cycle_count = 8;
            break;
        // JR cc, n
        case 0x20:
            arg_1 = this->fetch_op();
            
            log_cpu("JR NZ %d", static_cast<int8_t>(arg_1));
            

            this->jump_add_conditional(arg_1, ZERO_FLAG, false);
            cycle_count = 8;
            break;
        case 0x28:
            arg_1 = this->fetch_op();
            
            log_cpu("JR Z %d", static_cast<int8_t>(arg_1));
            

            this->jump_add_conditional(arg_1, ZERO_FLAG, true);
            cycle_count = 8;
            break;
        case 0x30:
            arg_1 = this->fetch_op();
            
            log_cpu("JR NC %d", static_cast<int8_t>(arg_1));
            

            this->jump_add_conditional(arg_1, CARRY_FLAG, false);
            cycle_count = 8;
            break;
        case 0x38:
            arg_1 = this->fetch_op();
            
            log_cpu("JR C %d", static_cast<int8_t>(arg_1));
            

            this->jump_add_conditional(arg_1, CARRY_FLAG, true);
            cycle_count = 8;
            break;
        /****    Calls    ****/
        // CALL nn
        case 0xCD:
            arg_1 = this->fetch_op();
            arg_2 = this->fetch_op();
            arg16bit = (arg_2 << 8) | arg_1;

            
            log_cpu("CALL %X", arg16bit);
            

            this->call(arg16bit);
            cycle_count = 12;
            break;
        // CALL cc, nn
        case 0xC4:
            arg_1 = this->fetch_op();
            arg_2 = this->fetch_op();
            arg16bit = (arg_2 << 8) | arg_1;

            
            log_cpu("CALL NZ %X", arg16bit);
            

            this->call(arg16bit, ZERO_FLAG, false);
            cycle_count = 12;
            break;
        case 0xCC:
            arg_1 = this->fetch_op();
            arg_2 = this->fetch_op();
            arg16bit = (arg_2 << 8) | arg_1;

            
            log_cpu("CALL Z %X", arg16bit);
            

            this->call(arg16bit, ZERO_FLAG, true);
            cycle_count = 12;
            break;
        case 0xD4:
            arg_1 = this->fetch_op();
            arg_2 = this->fetch_op();
            arg16bit = (arg_2 << 8) | arg_1;

            
            log_cpu("CALL NC %X", arg16bit);
            

            this->call(arg16bit, CARRY_FLAG, false);
            cycle_count = 12;
            break;
        case 0xDC:
            arg_1 = this->fetch_op();
            arg_2 = this->fetch_op();
            arg16bit = (arg_2 << 8) | arg_1;

            
            log_cpu("CALL C %X", arg16bit);
            

            this->call(arg16bit, CARRY_FLAG, true);
            cycle_count = 12;
            break;
        /****    Restarts    ****/
        // RST n
        case 0xC7:
            
            log_cpu("RST 00");
            

            this->restart(0x00);
            cycle_count = 32;
            break;
        case 0xCF:
            
            log_cpu("RST 08");
            

            this->restart(0x08);
            cycle_count = 32;
            break;
        case 0xD7:
            
            log_cpu("RST 10");
            

            this->restart(0x10);
            cycle_count = 32;
            break;
        case 0xDF:
            
            log_cpu("RST 18");
            

            this->restart(0x18);
            cycle_count = 32;
            break;
        case 0xE7:
            
            log_cpu("RST 20");
            

            this->restart(0x20);
            cycle_count = 32;
            break;
        case 0xEF:
            
            log_cpu("RST 28");
            

            this->restart(0x28);
            cycle_count = 32;
            break;
        case 0xF7:
            
            log_cpu("RST 30");
            

            this->restart(0x30);
            cycle_count = 32;
            break;
        case 0xFF:
            
            log_cpu("RST 38");
            

            this->restart(0x38);
            cycle_count = 32;
            break;
        /****    Returns    ****/
        // RET
        case 0xC9:
            log_cpu("RET");

            this->ret();
            cycle_count = 8;
            break;
        // RET cc
        case 0xC0:
            log_cpu("RET NZ");

            this->ret(ZERO_FLAG, false);
            cycle_count = 8;
            break;
        case 0xC8:
            log_cpu("RET Z");

            this->ret(ZERO_FLAG, true);
            cycle_count = 8;
            break;
        case 0xD0:
            log_cpu("RET NC");

            this->ret(CARRY_FLAG, false);
            cycle_count = 8;
            break;
        case 0xD8:
            log_cpu("RET C");

            this->ret(CARRY_FLAG, true);
            cycle_count = 8;
            break;
        // RETI
        case 0xD9:
            log_cpu("RETI");

            this->ret_enable_interrupts();
            cycle_count = 8;
            break;
        
        // CB
        case 0xCB:
            opcode = this->fetch_op();

            switch (opcode) {
                /****    Misc    ****/
                // SWAP n
                case 0x37:
                    this->swap(REG_A);
                    cycle_count = 8;
                    break;
                case 0x30:
                    this->swap(REG_B);
                    cycle_count = 8;
                    break;
                case 0x31:
                    this->swap(REG_C);
                    cycle_count = 8;
                    break;
                case 0x32:
                    this->swap(REG_D);
                    cycle_count = 8;
                    break;
                case 0x33:
                    this->swap(REG_E);
                    cycle_count = 8;
                    break;
                case 0x34:
                    this->swap(REG_H);
                    cycle_count = 8;
                    break;
                case 0x35:
                    this->swap(REG_L);
                    cycle_count = 8;
                    break;
                case 0x36:
                    this->swap(REG_HL);
                    cycle_count = 16;
                    break;
                /****    Rotates and Shifts    ****/
                // RLC n
                case 0x07:
                    this->rotate_left(REG_A, false);
                    cycle_count = 8;
                    break;
                case 0x00:
                    this->rotate_left(REG_B, false);
                    cycle_count = 8;
                    break;
                case 0x01:
                    this->rotate_left(REG_C, false);
                    cycle_count = 8;
                    break;
                case 0x02:
                    this->rotate_left(REG_D, false);
                    cycle_count = 8;
                    break;
                case 0x03:
                    this->rotate_left(REG_E, false);
                    cycle_count = 8;
                    break;
                case 0x04:
                    this->rotate_left(REG_H, false);
                    cycle_count = 8;
                    break;
                case 0x05:
                    this->rotate_left(REG_L, false);
                    cycle_count = 8;
                    break;
                case 0x06:
                    this->rotate_left(REG_HL, false);
                    cycle_count = 16;
                    break;
                // RL n
                case 0x17:
                    this->rotate_left(REG_A, true);
                    cycle_count = 8;
                    break;
                case 0x10:
                    this->rotate_left(REG_B, true);
                    cycle_count = 8;
                    break;
                case 0x11:
                    this->rotate_left(REG_C, true);
                    cycle_count = 8;
                    break;
                case 0x12:
                    this->rotate_left(REG_D, true);
                    cycle_count = 8;
                    break;
                case 0x13:
                    this->rotate_left(REG_E, true);
                    cycle_count = 8;
                    break;
                case 0x14:
                    this->rotate_left(REG_H, true);
                    cycle_count = 8;
                    break;
                case 0x15:
                    this->rotate_left(REG_L, true);
                    cycle_count = 8;
                    break;
                case 0x16:
                    this->rotate_left(REG_HL, true);
                    cycle_count = 16;
                    break;
                // RRC n
                case 0x0F:
                    this->rotate_right(REG_A, false);
                    cycle_count = 8;
                    break;
                case 0x08:
                    this->rotate_right(REG_B, false);
                    cycle_count = 8;
                    break;
                case 0x09:
                    this->rotate_right(REG_C, false);
                    cycle_count = 8;
                    break;
                case 0x0A:
                    this->rotate_right(REG_D, false);
                    cycle_count = 8;
                    break;
                case 0x0B:
                    this->rotate_right(REG_E, false);
                    cycle_count = 8;
                    break;
                case 0x0C:
                    this->rotate_right(REG_H, false);
                    cycle_count = 8;
                    break;
                case 0x0D:
                    this->rotate_right(REG_L, false);
                    cycle_count = 8;
                    break;
                case 0x0E:
                    this->rotate_right(REG_HL, false);
                    cycle_count = 16;
                    break;
                // RR n
                case 0x1F:
                    this->rotate_right(REG_A, true);
                    cycle_count = 8;
                    break;
                case 0x18:
                    this->rotate_right(REG_B, true);
                    cycle_count = 8;
                    break;
                case 0x19:
                    this->rotate_right(REG_C, true);
                    cycle_count = 8;
                    break;
                case 0x1A:
                    this->rotate_right(REG_D, true);
                    cycle_count = 8;
                    break;
                case 0x1B:
                    this->rotate_right(REG_E, true);
                    cycle_count = 8;
                    break;
                case 0x1C:
                    this->rotate_right(REG_H, true);
                    cycle_count = 8;
                    break;
                case 0x1D:
                    this->rotate_right(REG_L, true);
                    cycle_count = 8;
                    break;
                case 0x1E:
                    this->rotate_right(REG_HL, true);
                    cycle_count = 16;
                    break;
                // SLA n
                case 0x27:
                    this->shift_left(REG_A);
                    cycle_count = 8;
                    break;
                case 0x20:
                    this->shift_left(REG_B);
                    cycle_count = 8;
                    break;
                case 0x21:
                    this->shift_left(REG_C);
                    cycle_count = 8;
                    break;
                case 0x22:
                    this->shift_left(REG_D);
                    cycle_count = 8;
                    break;
                case 0x23:
                    this->shift_left(REG_E);
                    cycle_count = 8;
                    break;
                case 0x24:
                    this->shift_left(REG_H);
                    cycle_count = 8;
                    break;
                case 0x25:
                    this->shift_left(REG_L);
                    cycle_count = 8;
                    break;
                case 0x26:
                    this->shift_left(REG_HL);
                    cycle_count = 16;
                    break;
                // SRA n
                case 0x2F:
                    this->shift_right(REG_A, true);
                    cycle_count = 8;
                    break;
                case 0x28:
                    this->shift_right(REG_B, true);
                    cycle_count = 8;
                    break;
                case 0x29:
                    this->shift_right(REG_C, true);
                    cycle_count = 8;
                    break;
                case 0x2A:
                    this->shift_right(REG_D, true);
                    cycle_count = 8;
                    break;
                case 0x2B:
                    this->shift_right(REG_E, true);
                    cycle_count = 8;
                    break;
                case 0x2C:
                    this->shift_right(REG_H, true);
                    cycle_count = 8;
                    break;
                case 0x2D:
                    this->shift_right(REG_L, true);
                    cycle_count = 8;
                    break;
                case 0x2E:
                    this->shift_right(REG_HL, true);
                    cycle_count = 16;
                    break;
                // SRL n
                case 0x3F:
                    this->shift_right(REG_A, false);
                    cycle_count = 8;
                    break;
                case 0x38:
                    this->shift_right(REG_B, false);
                    cycle_count = 8;
                    break;
                case 0x39:
                    this->shift_right(REG_C, false);
                    cycle_count = 8;
                    break;
                case 0x3A:
                    this->shift_right(REG_D, false);
                    cycle_count = 8;
                    break;
                case 0x3B:
                    this->shift_right(REG_E, false);
                    cycle_count = 8;
                    break;
                case 0x3C:
                    this->shift_right(REG_H, false);
                    cycle_count = 8;
                    break;
                case 0x3D:
                    this->shift_right(REG_L, false);
                    cycle_count = 8;
                    break;
                case 0x3E:
                    this->shift_right(REG_HL, false);
                    cycle_count = 16;
                    break;
                /****    Bit Opcodes    ****/
                // BIT 0, r
                case 0x40:
                    this->test_bit(0, REG_B);
                    cycle_count = 8;
                    break;
                case 0x41:
                    this->test_bit(0, REG_C);
                    cycle_count = 8;
                    break;
                case 0x42:
                    this->test_bit(0, REG_D);
                    cycle_count = 8;
                    break;
                case 0x43:
                    this->test_bit(0, REG_E);
                    cycle_count = 8;
                    break;
                case 0x44:
                    this->test_bit(0, REG_H);
                    cycle_count = 8;
                    break;
                case 0x45:
                    this->test_bit(0, REG_L);
                    cycle_count = 8;
                    break;
                case 0x46:
                    this->test_bit(0, REG_HL);
                    cycle_count = 16;
                    break;
                case 0x47:
                    this->test_bit(0, REG_A);
                    cycle_count = 8;
                    break;
                // BIT 1, r
                case 0x48:
                    this->test_bit(1, REG_B);
                    cycle_count = 8;
                    break;
                case 0x49:
                    this->test_bit(1, REG_C);
                    cycle_count = 8;
                    break;
                case 0x4A:
                    this->test_bit(1, REG_D);
                    cycle_count = 8;
                    break;
                case 0x4B:
                    this->test_bit(1, REG_E);
                    cycle_count = 8;
                    break;
                case 0x4C:
                    this->test_bit(1, REG_H);
                    cycle_count = 8;
                    break;
                case 0x4D:
                    this->test_bit(1, REG_L);
                    cycle_count = 8;
                    break;
                case 0x4E:
                    this->test_bit(1, REG_HL);
                    cycle_count = 16;
                    break;
                case 0x4F:
                    this->test_bit(1, REG_A);
                    cycle_count = 8;
                    break;
                // BIT 2, r
                case 0x50:
                    this->test_bit(2, REG_B);
                    cycle_count = 8;
                    break;
                case 0x51:
                    this->test_bit(2, REG_C);
                    cycle_count = 8;
                    break;
                case 0x52:
                    this->test_bit(2, REG_D);
                    cycle_count = 8;
                    break;
                case 0x53:
                    this->test_bit(2, REG_E);
                    cycle_count = 8;
                    break;
                case 0x54:
                    this->test_bit(2, REG_H);
                    cycle_count = 8;
                    break;
                case 0x55:
                    this->test_bit(2, REG_L);
                    cycle_count = 8;
                    break;
                case 0x56:
                    this->test_bit(2, REG_HL);
                    cycle_count = 16;
                    break;
                case 0x57:
                    this->test_bit(2, REG_A);
                    cycle_count = 8;
                    break;
                // BIT 3, r
                case 0x58:
                    this->test_bit(3, REG_B);
                    cycle_count = 8;
                    break;
                case 0x59:
                    this->test_bit(3, REG_C);
                    cycle_count = 8;
                    break;
                case 0x5A:
                    this->test_bit(3, REG_D);
                    cycle_count = 8;
                    break;
                case 0x5B:
                    this->test_bit(3, REG_E);
                    cycle_count = 8;
                    break;
                case 0x5C:
                    this->test_bit(3, REG_H);
                    cycle_count = 8;
                    break;
                case 0x5D:
                    this->test_bit(3, REG_L);
                    cycle_count = 8;
                    break;
                case 0x5E:
                    this->test_bit(3, REG_HL);
                    cycle_count = 16;
                    break;
                case 0x5F:
                    this->test_bit(3, REG_A);
                    cycle_count = 8;
                    break;
                // BIT 4, r
                case 0x60:
                    this->test_bit(4, REG_B);
                    cycle_count = 8;
                    break;
                case 0x61:
                    this->test_bit(4, REG_C);
                    cycle_count = 8;
                    break;
                case 0x62:
                    this->test_bit(4, REG_D);
                    cycle_count = 8;
                    break;
                case 0x63:
                    this->test_bit(4, REG_E);
                    cycle_count = 8;
                    break;
                case 0x64:
                    this->test_bit(4, REG_H);
                    cycle_count = 8;
                    break;
                case 0x65:
                    this->test_bit(4, REG_L);
                    cycle_count = 8;
                    break;
                case 0x66:
                    this->test_bit(4, REG_HL);
                    cycle_count = 16;
                    break;
                case 0x67:
                    this->test_bit(4, REG_A);
                    cycle_count = 8;
                    break;
                // BIT 5, r
                case 0x68:
                    this->test_bit(5, REG_B);
                    cycle_count = 8;
                    break;
                case 0x69:
                    this->test_bit(5, REG_C);
                    cycle_count = 8;
                    break;
                case 0x6A:
                    this->test_bit(5, REG_D);
                    cycle_count = 8;
                    break;
                case 0x6B:
                    this->test_bit(5, REG_E);
                    cycle_count = 8;
                    break;
                case 0x6C:
                    this->test_bit(5, REG_H);
                    cycle_count = 8;
                    break;
                case 0x6D:
                    this->test_bit(5, REG_L);
                    cycle_count = 8;
                    break;
                case 0x6E:
                    this->test_bit(5, REG_HL);
                    cycle_count = 16;
                    break;
                case 0x6F:
                    this->test_bit(5, REG_A);
                    cycle_count = 8;
                    break;
                // BIT 6, r
                case 0x70:
                    this->test_bit(6, REG_B);
                    cycle_count = 8;
                    break;
                case 0x71:
                    this->test_bit(6, REG_C);
                    cycle_count = 8;
                    break;
                case 0x72:
                    this->test_bit(6, REG_D);
                    cycle_count = 8;
                    break;
                case 0x73:
                    this->test_bit(6, REG_E);
                    cycle_count = 8;
                    break;
                case 0x74:
                    this->test_bit(6, REG_H);
                    cycle_count = 8;
                    break;
                case 0x75:
                    this->test_bit(6, REG_L);
                    cycle_count = 8;
                    break;
                case 0x76:
                    this->test_bit(6, REG_HL);
                    cycle_count = 16;
                    break;
                case 0x77:
                    this->test_bit(6, REG_A);
                    cycle_count = 8;
                    break;
                // BIT 7, r
                case 0x78:
                    this->test_bit(7, REG_B);
                    cycle_count = 8;
                    break;
                case 0x79:
                    this->test_bit(7, REG_C);
                    cycle_count = 8;
                    break;
                case 0x7A:
                    this->test_bit(7, REG_D);
                    cycle_count = 8;
                    break;
                case 0x7B:
                    this->test_bit(7, REG_E);
                    cycle_count = 8;
                    break;
                case 0x7C:
                    this->test_bit(7, REG_H);
                    cycle_count = 8;
                    break;
                case 0x7D:
                    this->test_bit(7, REG_L);
                    cycle_count = 8;
                    break;
                case 0x7E:
                    this->test_bit(7, REG_HL);
                    cycle_count = 16;
                    break;
                case 0x7F:
                    this->test_bit(7, REG_A);
                    cycle_count = 8;
                    break;
                // SET 0, r
                case 0xC0:
                    this->set_bit(0, REG_B);
                    cycle_count = 8;
                    break;
                case 0xC1:
                    this->set_bit(0, REG_C);
                    cycle_count = 8;
                    break;
                case 0xC2:
                    this->set_bit(0, REG_D);
                    cycle_count = 8;
                    break;
                case 0xC3:
                    this->set_bit(0, REG_E);
                    cycle_count = 8;
                    break;
                case 0xC4:
                    this->set_bit(0, REG_H);
                    cycle_count = 8;
                    break;
                case 0xC5:
                    this->set_bit(0, REG_L);
                    cycle_count = 8;
                    break;
                case 0xC6:
                    this->set_bit(0, REG_HL);
                    cycle_count = 16;
                    break;
                case 0xC7:
                    this->set_bit(0, REG_A);
                    cycle_count = 8;
                    break;
                // SET 1, r
                case 0xC8:
                    this->set_bit(1, REG_B);
                    cycle_count = 8;
                    break;
                case 0xC9:
                    this->set_bit(1, REG_C);
                    cycle_count = 8;
                    break;
                case 0xCA:
                    this->set_bit(1, REG_D);
                    cycle_count = 8;
                    break;
                case 0xCB:
                    this->set_bit(1, REG_E);
                    cycle_count = 8;
                    break;
                case 0xCC:
                    this->set_bit(1, REG_H);
                    cycle_count = 8;
                    break;
                case 0xCD:
                    this->set_bit(1, REG_L);
                    cycle_count = 8;
                    break;
                case 0xCE:
                    this->set_bit(1, REG_HL);
                    cycle_count = 16;
                    break;
                case 0xCF:
                    this->set_bit(1, REG_A);
                    cycle_count = 8;
                    break;
                // SET 2, r
                case 0xD0:
                    this->set_bit(2, REG_B);
                    cycle_count = 8;
                    break;
                case 0xD1:
                    this->set_bit(2, REG_C);
                    cycle_count = 8;
                    break;
                case 0xD2:
                    this->set_bit(2, REG_D);
                    cycle_count = 8;
                    break;
                case 0xD3:
                    this->set_bit(2, REG_E);
                    cycle_count = 8;
                    break;
                case 0xD4:
                    this->set_bit(2, REG_H);
                    cycle_count = 8;
                    break;
                case 0xD5:
                    this->set_bit(2, REG_L);
                    cycle_count = 8;
                    break;
                case 0xD6:
                    this->set_bit(2, REG_HL);
                    cycle_count = 16;
                    break;
                case 0xD7:
                    this->set_bit(2, REG_A);
                    cycle_count = 8;
                    break;
                // SET 3, r
                case 0xD8:
                    this->set_bit(3, REG_B);
                    cycle_count = 8;
                    break;
                case 0xD9:
                    this->set_bit(3, REG_C);
                    cycle_count = 8;
                    break;
                case 0xDA:
                    this->set_bit(3, REG_D);
                    cycle_count = 8;
                    break;
                case 0xDB:
                    this->set_bit(3, REG_E);
                    cycle_count = 8;
                    break;
                case 0xDC:
                    this->set_bit(3, REG_H);
                    cycle_count = 8;
                    break;
                case 0xDD:
                    this->set_bit(3, REG_L);
                    cycle_count = 8;
                    break;
                case 0xDE:
                    this->set_bit(3, REG_HL);
                    cycle_count = 16;
                    break;
                case 0xDF:
                    this->set_bit(3, REG_A);
                    cycle_count = 8;
                    break;
                // SET 4, r
                case 0xE0:
                    this->set_bit(4, REG_B);
                    cycle_count = 8;
                    break;
                case 0xE1:
                    this->set_bit(4, REG_C);
                    cycle_count = 8;
                    break;
                case 0xE2:
                    this->set_bit(4, REG_D);
                    cycle_count = 8;
                    break;
                case 0xE3:
                    this->set_bit(4, REG_E);
                    cycle_count = 8;
                    break;
                case 0xE4:
                    this->set_bit(4, REG_H);
                    cycle_count = 8;
                    break;
                case 0xE5:
                    this->set_bit(4, REG_L);
                    cycle_count = 8;
                    break;
                case 0xE6:
                    this->set_bit(4, REG_HL);
                    cycle_count = 16;
                    break;
                case 0xE7:
                    this->set_bit(4, REG_A);
                    cycle_count = 8;
                    break;
                // SET 5, r
                case 0xE8:
                    this->set_bit(5, REG_B);
                    cycle_count = 8;
                    break;
                case 0xE9:
                    this->set_bit(5, REG_C);
                    cycle_count = 8;
                    break;
                case 0xEA:
                    this->set_bit(5, REG_D);
                    cycle_count = 8;
                    break;
                case 0xEB:
                    this->set_bit(5, REG_E);
                    cycle_count = 8;
                    break;
                case 0xEC:
                    this->set_bit(5, REG_H);
                    cycle_count = 8;
                    break;
                case 0xED:
                    this->set_bit(5, REG_L);
                    cycle_count = 8;
                    break;
                case 0xEE:
                    this->set_bit(5, REG_HL);
                    cycle_count = 16;
                    break;
                case 0xEF:
                    this->set_bit(5, REG_A);
                    cycle_count = 8;
                    break;
                // SET 6, r
                case 0xF0:
                    this->set_bit(6, REG_B);
                    cycle_count = 8;
                    break;
                case 0xF1:
                    this->set_bit(6, REG_C);
                    cycle_count = 8;
                    break;
                case 0xF2:
                    this->set_bit(6, REG_D);
                    cycle_count = 8;
                    break;
                case 0xF3:
                    this->set_bit(6, REG_E);
                    cycle_count = 8;
                    break;
                case 0xF4:
                    this->set_bit(6, REG_H);
                    cycle_count = 8;
                    break;
                case 0xF5:
                    this->set_bit(6, REG_L);
                    cycle_count = 8;
                    break;
                case 0xF6:
                    this->set_bit(6, REG_HL);
                    cycle_count = 16;
                    break;
                case 0xF7:
                    this->set_bit(6, REG_A);
                    cycle_count = 8;
                    break;
                // SET 7, r
                case 0xF8:
                    this->set_bit(7, REG_B);
                    cycle_count = 8;
                    break;
                case 0xF9:
                    this->set_bit(7, REG_C);
                    cycle_count = 8;
                    break;
                case 0xFA:
                    this->set_bit(7, REG_D);
                    cycle_count = 8;
                    break;
                case 0xFB:
                    this->set_bit(7, REG_E);
                    cycle_count = 8;
                    break;
                case 0xFC:
                    this->set_bit(7, REG_H);
                    cycle_count = 8;
                    break;
                case 0xFD:
                    this->set_bit(7, REG_L);
                    cycle_count = 8;
                    break;
                case 0xFE:
                    this->set_bit(7, REG_HL);
                    cycle_count = 16;
                    break;
                case 0xFF:
                    this->set_bit(7, REG_A);
                    cycle_count = 8;
                    break;
                // RES 0, r
                case 0x80:
                    this->reset_bit(0, REG_B);
                    cycle_count = 8;
                    break;
                case 0x81:
                    this->reset_bit(0, REG_C);
                    cycle_count = 8;
                    break;
                case 0x82:
                    this->reset_bit(0, REG_D);
                    cycle_count = 8;
                    break;
                case 0x83:
                    this->reset_bit(0, REG_E);
                    cycle_count = 8;
                    break;
                case 0x84:
                    this->reset_bit(0, REG_H);
                    cycle_count = 8;
                    break;
                case 0x85:
                    this->reset_bit(0, REG_L);
                    cycle_count = 8;
                    break;
                case 0x86:
                    this->reset_bit(0, REG_HL);
                    cycle_count = 16;
                    break;
                case 0x87:
                    this->reset_bit(0, REG_A);
                    cycle_count = 8;
                    break;
                // RES 1, r
                case 0x88:
                    this->reset_bit(1, REG_B);
                    cycle_count = 8;
                    break;
                case 0x89:
                    this->reset_bit(1, REG_C);
                    cycle_count = 8;
                    break;
                case 0x8A:
                    this->reset_bit(1, REG_D);
                    cycle_count = 8;
                    break;
                case 0x8B:
                    this->reset_bit(1, REG_E);
                    cycle_count = 8;
                    break;
                case 0x8C:
                    this->reset_bit(1, REG_H);
                    cycle_count = 8;
                    break;
                case 0x8D:
                    this->reset_bit(1, REG_L);
                    cycle_count = 8;
                    break;
                case 0x8E:
                    this->reset_bit(1, REG_HL);
                    cycle_count = 16;
                    break;
                case 0x8F:
                    this->reset_bit(1, REG_A);
                    cycle_count = 8;
                    break;
                // RES 2, r
                case 0x90:
                    this->reset_bit(2, REG_B);
                    cycle_count = 8;
                    break;
                case 0x91:
                    this->reset_bit(2, REG_C);
                    cycle_count = 8;
                    break;
                case 0x92:
                    this->reset_bit(2, REG_D);
                    cycle_count = 8;
                    break;
                case 0x93:
                    this->reset_bit(2, REG_E);
                    cycle_count = 8;
                    break;
                case 0x94:
                    this->reset_bit(2, REG_H);
                    cycle_count = 8;
                    break;
                case 0x95:
                    this->reset_bit(2, REG_L);
                    cycle_count = 8;
                    break;
                case 0x96:
                    this->reset_bit(2, REG_HL);
                    cycle_count = 16;
                    break;
                case 0x97:
                    this->reset_bit(2, REG_A);
                    cycle_count = 8;
                    break;
                // RES 3, r
                case 0x98:
                    this->reset_bit(3, REG_B);
                    cycle_count = 8;
                    break;
                case 0x99:
                    this->reset_bit(3, REG_C);
                    cycle_count = 8;
                    break;
                case 0x9A:
                    this->reset_bit(3, REG_D);
                    cycle_count = 8;
                    break;
                case 0x9B:
                    this->reset_bit(3, REG_E);
                    cycle_count = 8;
                    break;
                case 0x9C:
                    this->reset_bit(3, REG_H);
                    cycle_count = 8;
                    break;
                case 0x9D:
                    this->reset_bit(3, REG_L);
                    cycle_count = 8;
                    break;
                case 0x9E:
                    this->reset_bit(3, REG_HL);
                    cycle_count = 16;
                    break;
                case 0x9F:
                    this->reset_bit(3, REG_A);
                    cycle_count = 8;
                    break;
                // RES 4, r
                case 0xA0:
                    this->reset_bit(4, REG_B);
                    cycle_count = 8;
                    break;
                case 0xA1:
                    this->reset_bit(4, REG_C);
                    cycle_count = 8;
                    break;
                case 0xA2:
                    this->reset_bit(4, REG_D);
                    cycle_count = 8;
                    break;
                case 0xA3:
                    this->reset_bit(4, REG_E);
                    cycle_count = 8;
                    break;
                case 0xA4:
                    this->reset_bit(4, REG_H);
                    cycle_count = 8;
                    break;
                case 0xA5:
                    this->reset_bit(4, REG_L);
                    cycle_count = 8;
                    break;
                case 0xA6:
                    this->reset_bit(4, REG_HL);
                    cycle_count = 16;
                    break;
                case 0xA7:
                    this->reset_bit(4, REG_A);
                    cycle_count = 8;
                    break;
                // RES 5, r
                case 0xA8:
                    this->reset_bit(5, REG_B);
                    cycle_count = 8;
                    break;
                case 0xA9:
                    this->reset_bit(5, REG_C);
                    cycle_count = 8;
                    break;
                case 0xAA:
                    this->reset_bit(5, REG_D);
                    cycle_count = 8;
                    break;
                case 0xAB:
                    this->reset_bit(5, REG_E);
                    cycle_count = 8;
                    break;
                case 0xAC:
                    this->reset_bit(5, REG_H);
                    cycle_count = 8;
                    break;
                case 0xAD:
                    this->reset_bit(5, REG_L);
                    cycle_count = 8;
                    break;
                case 0xAE:
                    this->reset_bit(5, REG_HL);
                    cycle_count = 16;
                    break;
                case 0xAF:
                    this->reset_bit(5, REG_A);
                    cycle_count = 8;
                    break;
                // RES 6, r
                case 0xB0:
                    this->reset_bit(6, REG_B);
                    cycle_count = 8;
                    break;
                case 0xB1:
                    this->reset_bit(6, REG_C);
                    cycle_count = 8;
                    break;
                case 0xB2:
                    this->reset_bit(6, REG_D);
                    cycle_count = 8;
                    break;
                case 0xB3:
                    this->reset_bit(6, REG_E);
                    cycle_count = 8;
                    break;
                case 0xB4:
                    this->reset_bit(6, REG_H);
                    cycle_count = 8;
                    break;
                case 0xB5:
                    this->reset_bit(6, REG_L);
                    cycle_count = 8;
                    break;
                case 0xB6:
                    this->reset_bit(6, REG_HL);
                    cycle_count = 16;
                    break;
                case 0xB7:
                    this->reset_bit(6, REG_A);
                    cycle_count = 8;
                    break;
                // RES 7, r
                case 0xB8:
                    this->reset_bit(7, REG_B);
                    cycle_count = 8;
                    break;
                case 0xB9:
                    this->reset_bit(7, REG_C);
                    cycle_count = 8;
                    break;
                case 0xBA:
                    this->reset_bit(7, REG_D);
                    cycle_count = 8;
                    break;
                case 0xBB:
                    this->reset_bit(7, REG_E);
                    cycle_count = 8;
                    break;
                case 0xBC:
                    this->reset_bit(7, REG_H);
                    cycle_count = 8;
                    break;
                case 0xBD:
                    this->reset_bit(7, REG_L);
                    cycle_count = 8;
                    break;
                case 0xBE:
                    this->reset_bit(7, REG_HL);
                    cycle_count = 16;
                    break;
                case 0xBF:
                    this->reset_bit(7, REG_A);
                    cycle_count = 8;
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

void CPU::write_register(Registers_t reg, uint16_t data) {
    m_registers.write_register(reg, data);
}

uint16_t CPU::read_register(Registers_t reg) {
    return m_registers.read_register(reg);
}

void CPU::write_memory(uint8_t data) {
    this->write_memory(REG_HL, data);
}

void CPU::write_memory(Registers_t reg, uint8_t data) {
    uint16_t address = this->read_register(reg);
    this->m_memory_map.write(address, data);
}

uint8_t CPU::read_memory() {
    return this->read_memory(REG_HL);
}

uint8_t CPU::read_memory(Registers_t reg) {
    uint16_t address = this->read_register(reg);
    return this->m_memory_map.read(address);
}

void CPU::set_flag_register(CPUFlag_t flag, bool value) {
    uint8_t flag_register_val = this->read_register(REG_F);
    uint8_t val = (value) ? flag : 0;

    // Reset flag value to 0
    flag_register_val &= ~flag;
    this->write_register(REG_F, flag_register_val);
    // Set new flag value
    flag_register_val |= val;
    this->write_register(REG_F, flag_register_val);
}

bool CPU::read_flag_register(CPUFlag_t flag) {
    return (this->read_register(REG_F) & flag) == flag;
}

void CPU::reset_flag_register() {
    this->write_register(REG_F, 0);
}

uint8_t CPU::read_io_register(IORegisters_t reg) {
    return m_memory_map.read((uint16_t)reg);
}

void CPU::write_io_register(IORegisters_t reg, uint8_t data) {
    m_memory_map.write((uint16_t)reg, data);
}

bool CPU::is_stopped() const {
    return m_stopped;
}

bool CPU::is_running() const {
    return !m_halted && !m_stopped;
}

bool CPU::interrupts_enabled() const {
    return m_interrupts_enabled;
}
