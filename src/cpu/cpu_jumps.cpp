#include "cpu.h"

// JP nn
void CPU::jump(uint16_t value) {
    // TODO JP nn
}

// JP cc, nn
void CPU::jump_conditional(uint16_t value, CPUFlag_t flag, bool set) {
    // TODO JP cc, nn
}

// JP (HL)
void CPU::jump_hl() {
    // TODO JP (HL)
}

// JR n
void CPU::jump_add(uint8_t value) {
    // TODO JR n
}

// JR cc, n
void CPU::jump_add_conditional(uint8_t value, CPUFlag_t flag, bool set) {
    // TODO JR cc, n
}