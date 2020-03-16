#include "cpu.h"

void CPU::restart(uint8_t n) {
    // Push current address to stack    
    this->push_stack("PC");
    // Jump to address n
    this->jump(n);
}