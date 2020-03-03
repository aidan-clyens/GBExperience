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

    this->write_register("PC", value);
}

// JR n
void CPU::jump_add(uint8_t value) {
    uint16_t pc = this->read_register("PC");

    // TODO Implement error checking for PC overflow
    this->write_register("PC", pc + value - 1);
}

// JR cc, n
void CPU::jump_add_conditional(uint8_t value, CPUFlag_t flag, bool set) {
    uint16_t pc = this->read_register("PC");
    bool flag_set = this->read_flag_register(flag);

    // TODO Implement error checking for PC overflow
    if (!(flag_set ^ set)) {
        this->write_register("PC", pc + value - 1);
    }
}