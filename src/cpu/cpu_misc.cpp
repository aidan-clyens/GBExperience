#include "cpu.h"


void CPU::swap(const std::string &reg) {
    uint8_t val;
    
    if (reg == "HL") {
        val = this->read_memory();
    }
    else {
        val = this->read_register(reg);
    }

    uint8_t lower = val & 0x0F;
    uint8_t upper = val & 0xF0;
    uint8_t result = (lower << 4) | (upper >> 4);

    this->reset_flag_register();

    std::cout << "SWAP " << reg << std::endl;

    if (result == 0) {
        this->set_flag_register(ZERO_FLAG, true);
    }

    if (reg == "HL") {
        this->write_memory(result);
    }
    else {
        this->write_register(reg, result);
    }
}