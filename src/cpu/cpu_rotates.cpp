#include "cpu.h"


void CPU::rotate_left(bool use_carry) {
    uint8_t A = this->read_register("A");
    uint8_t result = A << 1;
    bool bit_7 = (A & 0x80) == 0x80;

    // Set flags
    this->set_flag_register(ZERO_FLAG, (result == 0));
    this->set_flag_register(SUBTRACT_FLAG, false);
    this->set_flag_register(HALF_CARRY_FLAG, false);

    // RLA
    if (use_carry)  {
        bool old_bit_7 = this->read_flag_register(CARRY_FLAG);

        std::cout << "RLA" << std::endl;

        if (old_bit_7) {
            result |= 0x01;
        }
    }
    // RLCA
    else {
        std::cout << "RLCA" << std::endl;

        if (bit_7) {
            result |= 0x01;
        }
    }

    this->write_register("A", result);
    this->set_flag_register(CARRY_FLAG, bit_7);
}

void CPU::rotate_right(bool use_carry) {
    uint8_t A = this->read_register("A");
    uint8_t result = A >> 1;
    bool bit_0 = (A & 0x01) == 0x01;

    // Set flags
    this->set_flag_register(ZERO_FLAG, (result == 0));
    this->set_flag_register(SUBTRACT_FLAG, false);
    this->set_flag_register(HALF_CARRY_FLAG, false);

    // RRA
    if (use_carry)  {
        bool old_bit_0 = this->read_flag_register(CARRY_FLAG);

        std::cout << "RRA" << std::endl;

        if (old_bit_0) {
            result |= 0x80;
        }
    }
    // RRCA
    else {
        std::cout << "RRCA" << std::endl;

        if (bit_0) {
            result |= 0x80;
        }
    }

    this->write_register("A", result);
    this->set_flag_register(CARRY_FLAG, bit_0);
}