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

void CPU::set_bit(int n, const std::string &reg) {
    uint8_t val;
    uint8_t result;
    uint8_t shift = 0x01 << n;

    if (reg == "HL") {
        val = this->read_memory();
    }
    else {
        val = this->read_register(reg);
    }

    #ifdef DEBUG
    std::cout << "SET " << n << ", " << reg << std::endl;
    #endif

    result = val | shift;

    if (reg == "HL") {
        this->write_memory(result);
    }
    else {
        this->write_register(reg, result);
    }
}

void CPU::reset_bit(int n, const std::string &reg) {
    uint8_t val;
    uint8_t result;
    uint8_t shift = 0x01 << n;

    if (reg == "HL") {
        val = this->read_memory();
    }
    else {
        val = this->read_register(reg);
    }

    #ifdef DEBUG
    std::cout << "RES " << n << ", " << reg << std::endl;
    #endif

    result = val & ~shift;

    if (reg == "HL") {
        this->write_memory(result);
    }
    else {
        this->write_register(reg, result);
    }
}