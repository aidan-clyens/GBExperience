#include "cpu.h"

// JP nn
void CPU::jump(uint16_t value) {
    this->write_register("PC", value);
}

// JP cc, nn
void CPU::jump_conditional(uint16_t value, CPUFlag_t flag, bool set) {
    bool flag_set = this->read_flag_register(flag);

    if (!(flag_set ^ set)) {
        this->write_register("PC", value);
    }
}

// JP (HL)
void CPU::jump_hl() {
    uint16_t value = this->read_register("HL");

    #ifdef CPU_DEBUG
    log_info("JP (HL)");
    #endif

    this->write_register("PC", value);
}

// JR n
void CPU::jump_add(int8_t value) {
    uint16_t pc = this->read_register("PC");

    this->write_register("PC", pc + value);
}

// JR cc, n
void CPU::jump_add_conditional(int8_t value, CPUFlag_t flag, bool set) {
    uint16_t pc = this->read_register("PC");
    bool flag_set = this->read_flag_register(flag);

    if (!(flag_set ^ set)) {
        this->write_register("PC", pc + value);
    }
}

void CPU::restart(uint8_t n) {
    // Push current address to stack    
    this->push_stack("PC");
    // Jump to address n
    this->jump(n);
}

void CPU::call(uint16_t nn) {
    uint16_t PC = this->read_register("PC");
    this->write_register("PC", PC - 2);
    // Push current address to stack
    this->push_stack("PC");
    this->write_register("PC", PC);

    // Jump to address nn
    this->jump(nn);
}

void CPU::call(uint16_t nn, CPUFlag_t flag, bool is_set) {
    if (!(this->read_flag_register(flag) ^ is_set)) {
        uint16_t PC = this->read_register("PC");
        this->write_register("PC", PC - 2);
        // Push current address to stack
        this->push_stack("PC");
        this->write_register("PC", PC);

        // Jump to address nn
        this->jump(nn);
    }
}

// RET
void CPU::ret() {
    this->pop_stack("PC");
}

// RET cc
void CPU::ret(CPUFlag_t flag, bool is_set) {
    if (!(this->read_flag_register(flag) ^ is_set)) {
        this->pop_stack("PC");
    }
}

// RETI
void CPU::ret_enable_interrupts() {
    this->pop_stack("PC");
    this->enable_interrupts();
}
