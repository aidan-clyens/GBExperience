#include "cpu.h"

// JP nn
void CPU::jump(uint16_t value) {
    #ifdef DEBUG
    std::cout << "JP " << static_cast<int>(value) << std::endl; 
    #endif

    this->write_register("PC", value);
}

// JP cc, nn
void CPU::jump_conditional(uint16_t value, CPUFlag_t flag, bool set) {
    bool flag_set = this->read_flag_register(flag);

    #ifdef DEBUG
    std::cout << "JP cc, " << static_cast<int>(value) << std::endl;
    #endif

    if (!(flag_set ^ set)) {
        this->write_register("PC", value);
    }
}

// JP (HL)
void CPU::jump_hl() {
    uint16_t value = this->read_register("HL");

    #ifdef DEBUG
    std::cout << "JP (HL)" << std::endl;
    #endif

    this->write_register("PC", value);
}

// JR n
void CPU::jump_add(int8_t value) {
    uint16_t pc = this->read_register("PC");

    #ifdef DEBUG
    std::cout << "JR " << static_cast<int>(value) << std::endl;
    #endif

    this->write_register("PC", pc + value - 1);
}

// JR cc, n
void CPU::jump_add_conditional(int8_t value, CPUFlag_t flag, bool set) {
    uint16_t pc = this->read_register("PC");
    bool flag_set = this->read_flag_register(flag);

    #ifdef DEBUG
    switch (flag) {
        case ZERO_FLAG:
            if (set) {
                std::cout << "JR Z " << static_cast<int>(value) << std::endl;
            } else {
                std::cout << "JR NZ " << static_cast<int>(value) << std::endl;
            }
            break;

        case CARRY_FLAG:
            if (set) {
                std::cout << "JR C " << static_cast<int>(value) << std::endl;
            } else {
                std::cout << "JR NC " << static_cast<int>(value) << std::endl;
            }
            break;
    }
    #endif

    if (!(flag_set ^ set)) {
        this->write_register("PC", pc + value - 1);
    }
}

void CPU::restart(uint8_t n) {
    #ifdef DEBUG
    std::cout << "RST " << static_cast<int>(n) << std::endl;
    #endif

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

    #ifdef DEBUG
    std::cout << "CALL " << static_cast<int>(nn) << std::endl;
    #endif

    // Jump to address nn
    this->jump(nn);
}

void CPU::call(uint16_t nn, CPUFlag_t flag, bool is_set) {
    #ifdef DEBUG
    std::cout << "CALL cc, " << static_cast<int>(nn) << std::endl;
    #endif

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
    #ifdef DEBUG
    std::cout << "RET" << std::endl;
    #endif

    this->pop_stack("PC");
}

// RET cc
void CPU::ret(CPUFlag_t flag, bool is_set) {
    #ifdef DEBUG
    std::cout << "RET cc" << std::endl;
    #endif

    if (!(this->read_flag_register(flag) ^ is_set)) {
        this->pop_stack("PC");
    }
}

// RETI
void CPU::ret_enable_interrupts() {
    #ifdef DEBUG
    std::cout << "RETI" << std::endl;
    #endif

    this->pop_stack("PC");
    this->enable_interrupts();
}
