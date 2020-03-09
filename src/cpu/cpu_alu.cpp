#include "cpu.h"

// ADD A, n
// ADC A, n
void CPU::alu_add(const std::string &reg, bool carry) {
    uint8_t A = this->read_register("A");
    uint8_t n = this->read_register(reg);
    uint8_t result = A + n;

    if (carry) {
        result += (this->read_flag_register(CARRY_FLAG)) ? 1 : 0;
    }

    this->reset_flag_register();

    if (result == 0) {
        this->set_flag_register(ZERO_FLAG, true);
    }

    if (A + n > 0xFF) {
        this->set_flag_register(CARRY_FLAG, true);
    }

    if ((A & 0xF) + (n & 0xF) > 0x0F) {
        this->set_flag_register(HALF_CARRY_FLAG, true);
    }

    if (carry) std::cout << "ADC A, " << reg << std::endl;
    else std::cout << "ADD A, " << reg << std::endl;


    this->write_register("A", result);
}

void CPU::alu_add(uint8_t n, bool carry) {
    uint8_t A = this->read_register("A");
    uint8_t result = A + n;

    if (carry) {
        result += (this->read_flag_register(CARRY_FLAG)) ? 1 : 0;
    }

    this->reset_flag_register();

    if (result == 0) {
        this->set_flag_register(ZERO_FLAG, true);
    }

    if (A + n > 0xFF) {
        this->set_flag_register(CARRY_FLAG, true);
    }

    if ((A & 0xF) + (n & 0xF) > 0x0F) {
        this->set_flag_register(HALF_CARRY_FLAG, true);
    }

    if (carry) std::cout << "ADC A, " << n << std::endl;
    else std::cout << "ADD A, " << n << std::endl;


    this->write_register("A", result);
}

// SUB n
// SBC n
void CPU::alu_sub(const std::string &reg, bool carry) {
    uint8_t A = this->read_register("A");
    uint8_t n = this->read_register(reg);

    if (carry) std::cout << "SBC A, " << reg << std::endl;
    else std::cout << "SUB A, " << reg << std::endl;

    this->write_register("A", A - n);
    // TODO Implement carry
}

void CPU::alu_sub(uint8_t n, bool carry) {
    uint8_t A = this->read_register("A");

    if (carry) std::cout << "SBC A, " << n << std::endl;
    else std::cout << "SUB A, " << n << std::endl;

    this->write_register("A", A - n);
    // TODO Implement carry
}

// AND n
void CPU::alu_and(const std::string &reg) {
    this->reset_flag_register();
    this->set_flag_register(HALF_CARRY_FLAG, true);

    uint8_t A = this->read_register("A");
    uint8_t n = this->read_register(reg);
    uint8_t result = A & n;

    if (result == 0) {
        this->set_flag_register(ZERO_FLAG, true);
    }

    std::cout << "AND A, " << reg << std::endl;

    this->write_register("A", result);
}

void CPU::alu_and(uint8_t n) {
    this->reset_flag_register();
    this->set_flag_register(HALF_CARRY_FLAG, true);

    uint8_t A = this->read_register("A");
    uint8_t result = A & n;

    if (result == 0) {
        this->set_flag_register(ZERO_FLAG, true);
    }

    std::cout << "AND A, " << n << std::endl;

    this->write_register("A", result);
}

// OR n
void CPU::alu_or(const std::string &reg) {
    this->reset_flag_register();

    uint8_t A = this->read_register("A");
    uint8_t n = this->read_register(reg);
    uint8_t result = A | n;

    if (result == 0) {
        this->set_flag_register(ZERO_FLAG, true);
    }

    std::cout << "OR A, " << reg << std::endl;

    this->write_register("A", result);
}

void CPU::alu_or(uint8_t n) {
    this->reset_flag_register();

    uint8_t A = this->read_register("A");
    uint8_t result = A | n;

    if (result == 0) {
        this->set_flag_register(ZERO_FLAG, true);
    }

    std::cout << "OR A, " << n << std::endl;

    this->write_register("A", result);
}

// XOR n
void CPU::alu_xor(const std::string &reg) {
    this->reset_flag_register();

    uint8_t A = this->read_register("A");
    uint8_t n = this->read_register(reg);
    uint8_t result = A ^ n;

    if (result == 0) {
        this->set_flag_register(ZERO_FLAG, true);
    }

    std::cout << "XOR A, " << reg << std::endl;

    this->write_register("A", result);
}

void CPU::alu_xor(uint8_t n) {
    this->reset_flag_register();

    uint8_t A = this->read_register("A");
    uint8_t result = A ^ n;

    if (result == 0) {
        this->set_flag_register(ZERO_FLAG, true);
    }

    std::cout << "XOR A, " << n << std::endl;

    this->write_register("A", result);
}

// CP n
void CPU::alu_cp(const std::string &reg) {
    this->reset_flag_register();
    this->set_flag_register(SUBTRACT_FLAG, true);

    uint8_t A = this->read_register("A");
    uint8_t n = this->read_register(reg);
    uint8_t result = A - n;

    if (result == 0) {
        this->set_flag_register(ZERO_FLAG, true);
    }

    if (A < n) {
        this->set_flag_register(CARRY_FLAG, true);
    }

    if ((A & 0x0F) < (n & 0xF)) {
        this->set_flag_register(HALF_CARRY_FLAG, true);
    }

    std::cout << "CP A, " << reg << std::endl;
}

void CPU::alu_cp(uint8_t n) {
    this->reset_flag_register();
    this->set_flag_register(SUBTRACT_FLAG, true);

    uint8_t A = this->read_register("A");
    uint8_t result = A - n;

    if (result == 0) {
        this->set_flag_register(ZERO_FLAG, true);
    }

    if (A < n) {
        this->set_flag_register(CARRY_FLAG, true);
    }

    if ((A & 0x0F) < (n & 0xF)) {
        this->set_flag_register(HALF_CARRY_FLAG, true);
    }

    std::cout << "CP A, " << n << std::endl;
}

// INC n
void CPU::alu_inc(const std::string &reg) {
    uint16_t N = this->read_register(reg);
    uint16_t result = N + 1;

    if (N < 0xFF) {
        this->set_flag_register(ZERO_FLAG, false);
        this->set_flag_register(SUBTRACT_FLAG, false);
        this->set_flag_register(HALF_CARRY_FLAG, false);
    }    

    if (result == 0) {
        this->set_flag_register(ZERO_FLAG, true);
    }

    if ((N & 0xF) + 1 > 0x0F) {
        this->set_flag_register(HALF_CARRY_FLAG, true);
    }

    std::cout << "INC " << reg << std::endl;

    this->write_register(reg, result);
}

// DEC n
void CPU::alu_dec(const std::string &reg) {
    uint16_t N = this->read_register(reg);
    uint16_t result = N - 1;

    if (N < 0xFF) {
        this->set_flag_register(ZERO_FLAG, false);
        this->set_flag_register(SUBTRACT_FLAG, true);
        this->set_flag_register(HALF_CARRY_FLAG, false);
    }    

    if (result == 0) {
        this->set_flag_register(ZERO_FLAG, true);
    }

    // TODO Implement half carry flag

    std::cout << "DEC " << reg << std::endl;

    this->write_register(reg, result);
}

/****    16-Bit ALU    ****/
// ADD HL, nn
void CPU::alu_add_HL(const std::string &reg) {
    uint16_t HL = this->read_register("HL");
    uint16_t nn = this->read_register(reg);
    uint16_t result = HL + nn;

    this->reset_flag_register();

    if (HL + nn > 0xFFFF) {
        this->set_flag_register(CARRY_FLAG, true);
    }

    if ((HL & 0xFF) + (nn & 0xFF) > 0x00FF) {
        this->set_flag_register(HALF_CARRY_FLAG, true);
    }

    std::cout << "ADD HL, " << reg << std::endl;

    this->write_register("HL", result);
}

// ADD SP, e
void CPU::alu_add_SP(uint8_t n) {
    uint16_t SP = this->read_register("SP");
    uint16_t result = SP + n;

    this->reset_flag_register();

    if (SP + n > 0xFFFF) {
        this->set_flag_register(CARRY_FLAG, true);
    }

    if ((SP & 0xFF) + (n & 0xFF) > 0x00FF) {
        this->set_flag_register(HALF_CARRY_FLAG, true);
    }

    std::cout << "ADD SP, " << static_cast<int>(n) << std::endl;

    this->write_register("SP", result);
}

// INC nn
void CPU::alu_inc_16bit(const std::string &reg) {
    // TODO
    std::cout << "INC " << reg << std::endl;
}

// DEC nn
void CPU::alu_dec_16bit(const std::string &reg) {
    // TODO    
    std::cout << "DEC" << reg << std::endl;
}
