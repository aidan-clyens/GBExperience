#include "cpu.h"

// ADD A, n
// ADC A, n
void CPU::alu_add(Registers_t reg, bool carry) {
    uint8_t A = this->read_register(REG_A);
    uint16_t n;

    if (reg == REG_HL) {
        n = this->read_memory();
    }
    else {
        n = this->read_register(reg);
    }

    uint16_t result_full = A + n;
    uint8_t carry_bit = 0;

    if (carry) {
        carry_bit = (this->read_flag_register(CARRY_FLAG)) ? 1 : 0;
        result_full += carry_bit;
    }

    uint8_t result = static_cast<uint8_t>(result_full);

    this->reset_flag_register();

    if (result == 0) {
        this->set_flag_register(ZERO_FLAG, true);
    }

    if (result_full > 0xFF) {
        this->set_flag_register(CARRY_FLAG, true);
    }

    if (((A & 0xF) + (n & 0xF) + carry_bit) > 0x0F) {
        this->set_flag_register(HALF_CARRY_FLAG, true);
    }

    
    if (carry) { log_cpu("ADC A, %s", reg); }
    else { log_cpu("ADD A, %s", CPURegisters::to_string(reg)); }
    

    this->write_register(REG_A, result);
}

void CPU::alu_add(uint8_t n, bool carry) {
    uint8_t A = this->read_register(REG_A);
    uint16_t result_full = A + n;
    uint8_t carry_bit = 0;

    if (carry) {
        carry_bit = (this->read_flag_register(CARRY_FLAG)) ? 1 : 0;
        result_full += carry_bit;
    }
    uint8_t result = static_cast<uint8_t>(result_full);

    this->reset_flag_register();

    if (result == 0) {
        this->set_flag_register(ZERO_FLAG, true);
    }

    if (result_full > 0xFF) {
        this->set_flag_register(CARRY_FLAG, true);
    }

    if (((A & 0xF) + (n & 0xF) + carry_bit) > 0x0F) {
        this->set_flag_register(HALF_CARRY_FLAG, true);
    }

    
    if (carry) { log_cpu("ADC A, %X", n); }
    else { log_cpu("ADD A, %X", n); }
    


    this->write_register(REG_A, result);
}

// SUB n
// SBC n
void CPU::alu_sub(Registers_t reg, bool carry) {
    uint8_t A = this->read_register(REG_A);
    uint8_t n;
    uint8_t carry_bit = 0;

    if (reg == REG_HL) {
        n = this->read_memory();
    }
    else {
        n = this->read_register(reg);
    }

    if (carry) {
        carry_bit = (this->read_flag_register(CARRY_FLAG)) ? 1 : 0;
    }

    int result_full = A - n - carry_bit;
    uint8_t result = static_cast<uint8_t>(result_full);
    
    if (carry) { log_cpu("SBC A, %s", CPURegisters::to_string(reg)); }
    else { log_cpu("SUB A(%X), %s", A, CPURegisters::to_string(reg)); }

    this->write_register(REG_A, result);
    
    bool borrow = result_full < 0;
    bool half_borrow = ((A & 0xF) - (n & 0xF) - carry_bit) < 0;

    this->reset_flag_register();

    this->set_flag_register(SUBTRACT_FLAG, true);
    this->set_flag_register(ZERO_FLAG, (result == 0));
    this->set_flag_register(HALF_CARRY_FLAG, half_borrow);
    this->set_flag_register(CARRY_FLAG, borrow);
}

void CPU::alu_sub(uint8_t n, bool carry) {
    uint8_t A = this->read_register(REG_A);
    uint8_t carry_bit = 0;

    if (carry) {
        carry_bit = (this->read_flag_register(CARRY_FLAG)) ? 1 : 0;
    }

    int result_full = A - n - carry_bit;
    uint8_t result = static_cast<uint8_t>(result_full);
    
    if (carry) { log_cpu("SBC A, %X", n ); }
    else { log_cpu("SUB A(%X), %X", A, n); }

    this->write_register(REG_A, result);
    
    bool borrow = result_full < 0;
    bool half_borrow = ((A & 0xF) - (n & 0xF) - carry_bit) < 0;

    this->reset_flag_register();

    this->set_flag_register(SUBTRACT_FLAG, true);
    this->set_flag_register(ZERO_FLAG, (result == 0));
    this->set_flag_register(HALF_CARRY_FLAG, half_borrow);
    this->set_flag_register(CARRY_FLAG, borrow);
}

// AND n
void CPU::alu_and(Registers_t reg) {
    this->reset_flag_register();
    this->set_flag_register(HALF_CARRY_FLAG, true);

    uint8_t A = this->read_register(REG_A);
    uint16_t n = this->read_register(reg);
    
    if (reg == REG_HL) {
        n = this->read_memory();
    }

    uint8_t result = A & n;

    if (result == 0) {
        this->set_flag_register(ZERO_FLAG, true);
    }

    log_cpu("AND A, %s", CPURegisters::to_string(reg));

    this->write_register(REG_A, result);
}

void CPU::alu_and(uint8_t n) {
    this->reset_flag_register();
    this->set_flag_register(HALF_CARRY_FLAG, true);

    uint8_t A = this->read_register(REG_A);
    uint8_t result = A & n;

    if (result == 0) {
        this->set_flag_register(ZERO_FLAG, true);
    }

    
    log_cpu("AND A, %X", n );
    

    this->write_register(REG_A, result);
}

// OR n
void CPU::alu_or(Registers_t reg) {
    this->reset_flag_register();

    uint8_t A = this->read_register(REG_A);
    uint16_t n = this->read_register(reg);
    
    if (reg == REG_HL) {
        n = this->read_memory();
    }
    
    uint8_t result = A | n;

    if (result == 0) {
        this->set_flag_register(ZERO_FLAG, true);
    }

    log_cpu("OR A(%X), %s(%X)", A, CPURegisters::to_string(reg), n);

    this->write_register(REG_A, result);
}

void CPU::alu_or(uint8_t n) {
    this->reset_flag_register();

    uint8_t A = this->read_register(REG_A);
    uint8_t result = A | n;

    if (result == 0) {
        this->set_flag_register(ZERO_FLAG, true);
    }

    
    log_cpu("OR A, %X", n );
    

    this->write_register(REG_A, result);
}

// XOR n
void CPU::alu_xor(Registers_t reg) {
    this->reset_flag_register();

    uint8_t A = this->read_register(REG_A);
    uint16_t n = this->read_register(reg);
    
    if (reg == REG_HL) {
        n = this->read_memory();
    }
    
    uint8_t result = A ^ n;

    if (result == 0) {
        this->set_flag_register(ZERO_FLAG, true);
    }

    log_cpu("XOR A, %s", CPURegisters::to_string(reg));

    this->write_register(REG_A, result);
}

void CPU::alu_xor(uint8_t n) {
    this->reset_flag_register();

    uint8_t A = this->read_register(REG_A);
    uint8_t result = A ^ n;

    if (result == 0) {
        this->set_flag_register(ZERO_FLAG, true);
    }
    
    
    log_cpu("XOR A, %X", n);
    

    this->write_register(REG_A, result);
}

// CP n
void CPU::alu_cp(Registers_t reg) {
    uint8_t A = this->read_register(REG_A);
    uint16_t n = this->read_register(reg);
    
    if (reg == REG_HL) {
        n = this->read_memory();
    }

    uint8_t result = static_cast<uint8_t>(A - n);

    bool borrow = A < n;
    bool half_borrow = ((A & 0xF) - (n & 0xF)) < 0;

    this->reset_flag_register();

    this->set_flag_register(SUBTRACT_FLAG, true);
    this->set_flag_register(ZERO_FLAG, (result == 0));
    this->set_flag_register(HALF_CARRY_FLAG, half_borrow);
    this->set_flag_register(CARRY_FLAG, borrow);

    log_cpu("CP A(%X), %s(%X)", A, CPURegisters::to_string(reg), n);
}

void CPU::alu_cp(uint8_t n) {
    uint8_t A = this->read_register(REG_A);
    uint8_t result = static_cast<uint8_t>(A - n);

    bool borrow = A < n;
    bool half_borrow = ((A & 0xF) - (n & 0xF)) < 0;

    this->reset_flag_register();

    this->set_flag_register(SUBTRACT_FLAG, true);
    this->set_flag_register(ZERO_FLAG, (result == 0));
    this->set_flag_register(HALF_CARRY_FLAG, half_borrow);
    this->set_flag_register(CARRY_FLAG, borrow);

    log_cpu("CP A(%X), %X", A, n);
}

// INC n
void CPU::alu_inc(Registers_t reg) {
    uint16_t N = this->read_register(reg);
    
    if (reg == REG_HL) {
        N = this->read_memory();
    }

    uint8_t result = N + 1;

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

    log_cpu("INC %s", CPURegisters::to_string(reg));

    if (reg == REG_HL) {
        this->write_memory(result);
    }
    else {
        this->write_register(reg, result);
    }
}

// DEC n
void CPU::alu_dec(Registers_t reg) {
    uint8_t N = this->read_register(reg);

    if (reg == REG_HL) {
        N = this->read_memory();
    }

    uint8_t result = N;
    result--;

    log_cpu("DEC %s", CPURegisters::to_string(reg));

    bool half_borrow = false;

    for (int i = 0; i < 4; i++) {
        if ((N & (1 << i)) < (1 & (1 << i))) {
            half_borrow = true;
        }
    }

    this->reset_flag_register();

    this->set_flag_register(SUBTRACT_FLAG, true);
    this->set_flag_register(ZERO_FLAG, (result == 0));
    this->set_flag_register(HALF_CARRY_FLAG, !half_borrow);

    if (reg == REG_HL) {
        this->write_memory(result);
    }
    else {
        this->write_register(reg, result);
    }
}

/****    16-Bit ALU    ****/
// ADD HL, nn
void CPU::alu_add_HL(Registers_t reg) {
    uint16_t HL = this->read_register(REG_HL);
    uint16_t nn = this->read_register(reg);
    uint32_t result_full = HL + nn;

    this->set_flag_register(SUBTRACT_FLAG, false);
    this->set_flag_register(CARRY_FLAG, ((result_full & 0x10000) != 0));
    this->set_flag_register(HALF_CARRY_FLAG, ((HL & 0xFFF) + (nn & 0xFFF) > 0xFFF));

    log_cpu("ADD HL, %s", CPURegisters::to_string(reg));

    uint16_t result = static_cast<uint16_t>(result_full);
    this->write_register(REG_HL, result);
}

// ADD SP, e
void CPU::alu_add_SP(int8_t n) {
    uint16_t SP = this->read_register(REG_SP);
    uint16_t result = SP + n;

    this->reset_flag_register();

    if (SP + n > 0xFFFF) {
        this->set_flag_register(CARRY_FLAG, true);
    }

    if ((SP & 0xFF) + (n & 0xFF) > 0x00FF) {
        this->set_flag_register(HALF_CARRY_FLAG, true);
    }

    
    log_cpu("ADD SP, %X", n);
    

    this->write_register(REG_SP, result);
}

// INC nn
void CPU::alu_inc_16bit(Registers_t reg) {
    uint16_t N = this->read_register(reg);
    uint16_t result = N + 1;

    log_cpu("INC %s(%X)", CPURegisters::to_string(reg), result);

    this->write_register(reg, result);
}

// DEC nn
void CPU::alu_dec_16bit(Registers_t reg) {
    uint16_t N = this->read_register(reg);
    uint16_t result = N;
    result--;

    log_cpu("DEC %s", CPURegisters::to_string(reg));

    this->write_register(reg, result);
}
