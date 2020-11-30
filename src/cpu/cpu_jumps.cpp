#include "cpu.h"

// JP nn
void CPU::jump(uint16_t value) {
    this->write_register(REG_PC, value);
}

// JP cc, nn
void CPU::jump_conditional(uint16_t value, CPUFlag_t flag, bool set) {
    bool flag_set = this->read_flag_register(flag);

    if (!(flag_set ^ set)) {
        this->write_register(REG_PC, value);
    }
}

// JP (HL)
void CPU::jump_hl() {
    uint16_t value = this->read_register(REG_HL);

    
    log_cpu("JP (HL)");
    

    this->write_register(REG_PC, value);
}

// JR n
void CPU::jump_add(int8_t value) {
    uint16_t pc = this->read_register(REG_PC);

    this->write_register(REG_PC, pc + value);
}

// JR cc, n
void CPU::jump_add_conditional(int8_t value, CPUFlag_t flag, bool set) {
    uint16_t pc = this->read_register(REG_PC);
    bool flag_set = this->read_flag_register(flag);

    if (!(flag_set ^ set)) {
        this->write_register(REG_PC, pc + value);
    }
}

void CPU::restart(uint8_t n) {
    // Push current address to stack    
    this->push_stack(REG_PC);
    // Jump to address n
    this->jump(n);
}

void CPU::call(uint16_t nn) {
    uint16_t PC = this->read_register(REG_PC);
    this->write_register(REG_PC, PC);
    // Push current address to stack
    this->push_stack(REG_PC);
    this->write_register(REG_PC, PC);

    // Jump to address nn
    this->jump(nn);
}

void CPU::call(uint16_t nn, CPUFlag_t flag, bool is_set) {
    if (!(this->read_flag_register(flag) ^ is_set)) {
        uint16_t PC = this->read_register(REG_PC);
        this->write_register(REG_PC, PC);
        // Push current address to stack
        this->push_stack(REG_PC);
        this->write_register(REG_PC, PC);

        // Jump to address nn
        this->jump(nn);
    }
}

// RET
void CPU::ret() {
    this->pop_stack(REG_PC);
}

// RET cc
void CPU::ret(CPUFlag_t flag, bool is_set) {
    if (!(this->read_flag_register(flag) ^ is_set)) {
        this->pop_stack(REG_PC);
    }
}

// RETI
void CPU::ret_enable_interrupts() {
    this->pop_stack(REG_PC);
    this->enable_interrupts();
}
