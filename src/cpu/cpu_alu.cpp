#include "cpu.h"

// ADD A, n
// ADC A, n
void CPU::alu_add(const std::string &reg, bool carry) {
    uint8_t A = this->read_register("A");
    uint16_t n;

    if (reg == "HL") {
        n = this->read_memory();
    }
    else {
        n = this->read_register(reg);
    }

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

    #ifdef CPU_DEBUG
    if (carry) { log_info("ADC A, %s", reg.c_str()); }
    else { log_info("ADD A, %s", reg.c_str()); }
    #endif

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

    #ifdef CPU_DEBUG
    if (carry) { log_info("ADC A, %X", n); }
    else { log_info("ADD A, %X", n); }
    #endif


    this->write_register("A", result);
}

// SUB n
// SBC n
void CPU::alu_sub(const std::string &reg, bool carry) {
    uint8_t A = this->read_register("A");
    uint8_t n;

    if (reg == "HL") {
        n = this->read_memory();
    }
    else {
        n = this->read_register(reg);
    }

    if (carry & this->read_flag_register(CARRY_FLAG)) {
        n++;
    }

    uint8_t result = A - n;

    #ifdef CPU_DEBUG
    if (carry) { log_info("SBC A, %s", reg.c_str()); }
    else { log_info("SUB A, %s", reg.c_str()); }
    #endif

    this->write_register("A", result);
    
    bool borrow = false;
    bool half_borrow = false;

    for (int i = 0; i < 8; i++) {
        if ((A & (1 << i)) < (n & (1 << i))) {
            if (i < 4) {
                half_borrow = true;
            }
            
            borrow = true;
        }
    }

    this->reset_flag_register();

    this->set_flag_register(SUBTRACT_FLAG, true);
    this->set_flag_register(ZERO_FLAG, (result == 0));
    this->set_flag_register(HALF_CARRY_FLAG, !half_borrow);
    this->set_flag_register(CARRY_FLAG, !borrow);
}

void CPU::alu_sub(uint8_t n, bool carry) {
    uint8_t A = this->read_register("A");

    if (carry & this->read_flag_register(CARRY_FLAG)) {
        n++;
    }

    uint8_t result = A - n;

    #ifdef CPU_DEBUG
    if (carry) { log_info("SBC A, %X", n ); }
    else { log_info("SUB A, %X", n ); }
    #endif

    this->write_register("A", result);
    
    bool borrow = false;
    bool half_borrow = false;

    for (int i = 0; i < 8; i++) {
        if ((A & (1 << i)) < (n & (1 << i))) {
            if (i < 4) {
                half_borrow = true;
            }

            borrow = true;
        }
    }

    this->reset_flag_register();

    this->set_flag_register(SUBTRACT_FLAG, true);
    this->set_flag_register(ZERO_FLAG, (result == 0));
    this->set_flag_register(HALF_CARRY_FLAG, !half_borrow);
    this->set_flag_register(CARRY_FLAG, !borrow);
}

// AND n
void CPU::alu_and(const std::string &reg) {
    this->reset_flag_register();
    this->set_flag_register(HALF_CARRY_FLAG, true);

    uint8_t A = this->read_register("A");
    uint16_t n = this->read_register(reg);
    
    if (reg == "HL") {
        n = this->read_memory();
    }

    uint8_t result = A & n;

    if (result == 0) {
        this->set_flag_register(ZERO_FLAG, true);
    }

    #ifdef CPU_DEBUG
    log_info("AND A, %s", reg.c_str() );
    #endif

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

    #ifdef CPU_DEBUG
    log_info("AND A, %X", n );
    #endif

    this->write_register("A", result);
}

// OR n
void CPU::alu_or(const std::string &reg) {
    this->reset_flag_register();

    uint8_t A = this->read_register("A");
    uint16_t n = this->read_register(reg);
    
    if (reg == "HL") {
        n = this->read_memory();
    }
    
    uint8_t result = A | n;

    if (result == 0) {
        this->set_flag_register(ZERO_FLAG, true);
    }

    #ifdef CPU_DEBUG
    log_info("OR A, %s", reg.c_str() );
    #endif

    this->write_register("A", result);
}

void CPU::alu_or(uint8_t n) {
    this->reset_flag_register();

    uint8_t A = this->read_register("A");
    uint8_t result = A | n;

    if (result == 0) {
        this->set_flag_register(ZERO_FLAG, true);
    }

    #ifdef CPU_DEBUG
    log_info("OR A, %X", n );
    #endif

    this->write_register("A", result);
}

// XOR n
void CPU::alu_xor(const std::string &reg) {
    this->reset_flag_register();

    uint8_t A = this->read_register("A");
    uint16_t n = this->read_register(reg);
    
    if (reg == "HL") {
        n = this->read_memory();
    }
    
    uint8_t result = A ^ n;

    if (result == 0) {
        this->set_flag_register(ZERO_FLAG, true);
    }

    #ifdef CPU_DEBUG
    log_info("XOR A, %s", reg.c_str() );
    #endif

    this->write_register("A", result);
}

void CPU::alu_xor(uint8_t n) {
    this->reset_flag_register();

    uint8_t A = this->read_register("A");
    uint8_t result = A ^ n;

    if (result == 0) {
        this->set_flag_register(ZERO_FLAG, true);
    }
    
    #ifdef CPU_DEBUG
    log_info("XOR A, %X", n);
    #endif

    this->write_register("A", result);
}

// CP n
void CPU::alu_cp(const std::string &reg) {
    this->reset_flag_register();
    this->set_flag_register(SUBTRACT_FLAG, true);

    uint8_t A = this->read_register("A");
    uint16_t n = this->read_register(reg);
    
    if (reg == "HL") {
        n = this->read_memory();
    }

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

    #ifdef CPU_DEBUG
    log_info("CP A, %s", reg.c_str() );
    #endif
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

    #ifdef CPU_DEBUG
    log_info("CP A, %X", n);
    #endif
}

// INC n
void CPU::alu_inc(const std::string &reg) {
    uint16_t N = this->read_register(reg);
    
    if (reg == "HL") {
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

    #ifdef CPU_DEBUG
    log_info("INC %s", reg.c_str() );
    #endif

    if (reg == "HL") {
        this->write_memory(result);
    }
    else {
        this->write_register(reg, result);
    }
}

// DEC n
void CPU::alu_dec(const std::string &reg) {
    uint8_t N = this->read_register(reg);

    if (reg == "HL") {
        N = this->read_memory();
    }

    uint8_t result = N;
    result--;

    #ifdef CPU_DEBUG
    log_info("DEC %s", reg.c_str() );
    #endif

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

    if (reg == "HL") {
        this->write_memory(result);
    }
    else {
        this->write_register(reg, result);
    }
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

    #ifdef CPU_DEBUG
    log_info("ADD HL, %s", reg.c_str() );
    #endif

    this->write_register("HL", result);
}

// ADD SP, e
void CPU::alu_add_SP(int8_t n) {
    uint16_t SP = this->read_register("SP");
    uint16_t result = SP + n;

    this->reset_flag_register();

    if (SP + n > 0xFFFF) {
        this->set_flag_register(CARRY_FLAG, true);
    }

    if ((SP & 0xFF) + (n & 0xFF) > 0x00FF) {
        this->set_flag_register(HALF_CARRY_FLAG, true);
    }

    #ifdef CPU_DEBUG
    log_info("ADD SP, %X", n);
    #endif

    this->write_register("SP", result);
}

// INC nn
void CPU::alu_inc_16bit(const std::string &reg) {
    uint16_t N = this->read_register(reg);
    uint16_t result = N + 1;

    #ifdef CPU_DEBUG
    log_info("INC %s", reg.c_str() );
    #endif

    this->write_register(reg, result);
}

// DEC nn
void CPU::alu_dec_16bit(const std::string &reg) {
    uint16_t N = this->read_register(reg);
    uint16_t result = N;
    result--;

    #ifdef CPU_DEBUG
    log_info("DEC %s", reg.c_str() );
    #endif

    this->write_register(reg, result);
}
