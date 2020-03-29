#include "cpu.h"


void CPU::test_bit(int n, const std::string &reg) {
    uint8_t val;
    bool result;

    if (reg == "HL") {
        val = this->read_memory();
    }
    else {
        val = this->read_register(reg);
    }

    #ifdef DEBUG
    std::cout << "BIT " << n <<  ", " << reg << std::endl;
    #endif

    result = ((val >> n) & 0x01) == 0x00;

    this->set_flag_register(ZERO_FLAG, result);
    this->set_flag_register(SUBTRACT_FLAG, false);
    this->set_flag_register(HALF_CARRY_FLAG, true);
}
