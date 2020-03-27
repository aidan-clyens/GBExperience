#include "cpu.h"

void CPU::rotate_left(bool use_carry) {
    this->rotate_left("A", use_carry);
}

void CPU::rotate_left(const std::string &reg, bool use_carry) {
    uint8_t val;

    if (reg == "HL") {
        val = this->read_memory();
    }
    else {
        val = this->read_register(reg);
    }
    
    uint8_t result = val << 1;
    bool bit_7 = (val & 0x80) == 0x80;

    // Set flags
    this->set_flag_register(ZERO_FLAG, (result == 0));
    this->set_flag_register(SUBTRACT_FLAG, false);
    this->set_flag_register(HALF_CARRY_FLAG, false);

    // RLA
    if (use_carry)  {
        bool old_bit_7 = this->read_flag_register(CARRY_FLAG);

        if (reg == "A") {
            std::cout << "RLA" << std::endl;
        }
        else {
            std::cout << "RL " << reg << std::endl;
        }

        if (old_bit_7) {
            result |= 0x01;
        }
    }
    // RLCA
    else {
        if (reg == "A") {
            std::cout << "RLCA" << std::endl;
        }
        else if (reg == "HL") {
            std::cout << "RLC (HL)" << std::endl;
        }
        else {
            std::cout << "RLC " << reg << std::endl;
        }

        if (bit_7) {
            result |= 0x01;
        }
    }

    if (reg == "HL") {
        this->write_memory(result);
    }
    else {
        this->write_register(reg, result);
    }

    this->set_flag_register(CARRY_FLAG, bit_7);
}

void CPU::rotate_right(bool use_carry) {
    rotate_right("A", use_carry);
}

void CPU::rotate_right(const std::string &reg, bool use_carry) {
    uint8_t val;

    if (reg == "HL") {
        val = this->read_memory();
    }
    else {
        val = this->read_register(reg);
    }

    uint8_t result = val >> 1;
    bool bit_0 = (val & 0x01) == 0x01;

    // Set flags
    this->set_flag_register(ZERO_FLAG, (result == 0));
    this->set_flag_register(SUBTRACT_FLAG, false);
    this->set_flag_register(HALF_CARRY_FLAG, false);

    // RRA
    if (use_carry)  {
        bool old_bit_0 = this->read_flag_register(CARRY_FLAG);

        if (reg == "A") {
            std::cout << "RRA" << std::endl;
        }
        else if (reg == "HL") {
            std::cout << "RR (HL)" << std::endl;
        }
        else {
            std::cout << "RR " << reg << std::endl;
        }

        if (old_bit_0) {
            result |= 0x80;
        }
    }
    // RRCA
    else {
        if (reg == "A") {
            std::cout << "RRCA" << std::endl;
        }
        else if (reg == "HL") {
            std::cout << "RRC (HL)" << std::endl;
        }
        else {
            std::cout << "RRC " << reg << std::endl;
        }

        if (bit_0) {
            result |= 0x80;
        }
    }

    if (reg == "HL") {
        this->write_memory(result);
    }
    else {
        this->write_register(reg, result);
    }

    this->set_flag_register(CARRY_FLAG, bit_0);
}