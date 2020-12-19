#include "cpu.h"

void CPU::rotate_left(bool use_carry) {
    this->rotate_left(REG_A, use_carry);
}

void CPU::rotate_left(Registers_t reg, bool use_carry) {
    uint8_t val;

    if (reg == REG_HL) {
        val = this->read_memory();
    }
    else {
        val = this->read_register(reg);
    }
    
    uint8_t result = val << 1;
    bool bit_7 = (val & 0x80) == 0x80;

    // Set flags
    this->set_flag_register(SUBTRACT_FLAG, false);
    this->set_flag_register(HALF_CARRY_FLAG, false);

    // RLA
    if (use_carry)  {
        bool old_bit_7 = this->read_flag_register(CARRY_FLAG);
        
        if (reg == REG_A) {
            log_cpu("RLA");
        }
        else {
            log_cpu("RL %s", CPURegisters::to_string(reg));
        }
        

        if (old_bit_7) {
            result |= 0x01;
        }
    }
    // RLCA
    else {
        
        if (reg == REG_A) {
            log_cpu("RLCA");
        }
        else if (reg == REG_HL) {
            log_cpu("RLC (HL)" );
        }
        else {
            log_cpu("RLC %s", CPURegisters::to_string(reg));
        }
        

        if (bit_7) {
            result |= 0x01;
        }
    }

    if (reg == REG_HL) {
        this->write_memory(result);
    }
    else {
        this->write_register(reg, result);
    }

    this->set_flag_register(ZERO_FLAG, (result == 0));
    this->set_flag_register(CARRY_FLAG, bit_7);
}

void CPU::rotate_right(bool use_carry) {
    rotate_right(REG_A, use_carry);
}

void CPU::rotate_right(Registers_t reg, bool use_carry) {
    uint8_t val;

    if (reg == REG_HL) {
        val = this->read_memory();
    }
    else {
        val = this->read_register(reg);
    }

    uint8_t result = val >> 1;
    bool bit_0 = (val & 0x01) == 0x01;

    // Set flags
    this->set_flag_register(SUBTRACT_FLAG, false);
    this->set_flag_register(HALF_CARRY_FLAG, false);

    // RRA
    if (use_carry)  {
        bool old_bit_0 = this->read_flag_register(CARRY_FLAG);

        
        if (reg == REG_A) {
            log_cpu("RRA");
        }
        else if (reg == REG_HL) {
            log_cpu("RR (HL)");
        }
        else {
            log_cpu("RR %s", CPURegisters::to_string(reg));
        }
        

        if (old_bit_0) {
            result |= 0x80;
        }
    }
    // RRCA
    else {
        
        if (reg == REG_A) {
            log_cpu("RRCA" );
        }
        else if (reg == REG_HL) {
            log_cpu("RRC (HL)");
        }
        else {
            log_cpu("RRC %s", CPURegisters::to_string(reg));
        }
        

        if (bit_0) {
            result |= 0x80;
        }
    }

    if (reg == REG_HL) {
        this->write_memory(result);
    }
    else {
        this->write_register(reg, result);
    }

    this->set_flag_register(ZERO_FLAG, (result == 0));
    this->set_flag_register(CARRY_FLAG, bit_0);
}

void CPU::shift_left(Registers_t reg) {
    uint8_t val;

    if (reg == REG_HL) {
        val = this->read_memory();
    }
    else {
        val = this->read_register(reg);
    }
    
    uint8_t result = val << 1;
    bool bit_7 = (val & 0x80) == 0x80;

    log_cpu("SLA %s", CPURegisters::to_string(reg));

    // Set flags
    this->set_flag_register(ZERO_FLAG, (result == 0));
    this->set_flag_register(SUBTRACT_FLAG, false);
    this->set_flag_register(HALF_CARRY_FLAG, false);

    if (reg == REG_HL) {
        this->write_memory(result);
    }
    else {
        this->write_register(reg, result);
    }

    this->set_flag_register(CARRY_FLAG, bit_7);
}

void CPU::shift_right(Registers_t reg, bool keep_msb) {
    uint8_t val;

    if (reg == REG_HL) {
        val = this->read_memory();
    }
    else {
        val = this->read_register(reg);
    }
    
    uint8_t result = val >> 1;
    bool bit_0 = (val & 0x01) == 0x01;
    bool bit_7 = (val & 0x80) == 0x80;

    if (keep_msb) {
        if (bit_7) {
            result |= 0x80;
        }

        log_cpu("SRA %s", CPURegisters::to_string(reg));
    }
    else {

        log_cpu("SRL %s", CPURegisters::to_string(reg));
    }

    // Set flags
    this->set_flag_register(ZERO_FLAG, (result == 0));
    this->set_flag_register(SUBTRACT_FLAG, false);
    this->set_flag_register(HALF_CARRY_FLAG, false);

    if (reg == REG_HL) {
        this->write_memory(result);
    }
    else {
        this->write_register(reg, result);
    }

    this->set_flag_register(CARRY_FLAG, bit_0);
}