#include "cpu.h"


void CPU::swap(Registers_t reg) {
    uint8_t val;
    
    if (reg == REG_HL) {
        val = this->read_memory();
    }
    else {
        val = this->read_register(reg);
    }

    uint8_t lower = val & 0x0F;
    uint8_t upper = val & 0xF0;
    uint8_t result = (lower << 4) | (upper >> 4);

    this->reset_flag_register();

    log_cpu("SWAP %s", CPURegisters::to_string(reg));

    if (result == 0) {
        this->set_flag_register(ZERO_FLAG, true);
    }

    if (reg == REG_HL) {
        this->write_memory(result);
    }
    else {
        this->write_register(reg, result);
    }
}

void CPU::complement() {
    uint8_t val = this->read_register(REG_A);
    uint8_t result = ~val;

    
    log_cpu("CPL");
    

    this->set_flag_register(SUBTRACT_FLAG, true);
    this->set_flag_register(HALF_CARRY_FLAG, true);

    this->write_register(REG_A, result);
}

void CPU::complement_carry() {
    bool carry = this->read_flag_register(CARRY_FLAG);

    
    log_cpu("CCF");
    

    this->set_flag_register(SUBTRACT_FLAG, false);
    this->set_flag_register(HALF_CARRY_FLAG, false);
    
    this->set_flag_register(CARRY_FLAG, !carry);
}

void CPU::set_carry() {

    
    log_cpu("SCF");
    

    this->set_flag_register(CARRY_FLAG, true);
}

void CPU::halt() {
    
    log_cpu("HALT");
    

    m_halted = true;
}


void CPU::stop() {
    
    log_cpu("STOP");
    

    m_stopped = true;
}


void CPU::enable_interrupts() {
    
    log_cpu("EI");
    

    m_interrupts_enabled = true;
}

void CPU::disable_interrupts() {
    
    log_cpu("DI");
    

    m_interrupts_enabled = false;
}

void CPU::daa() {
    log_cpu("DAA");

    bool subtract = this->read_flag_register(SUBTRACT_FLAG);
    bool carry = this->read_flag_register(CARRY_FLAG);
    bool half_carry = this->read_flag_register(HALF_CARRY_FLAG);

    uint8_t A = this->read_register(REG_A);

    if (subtract) {
        if (carry) {
            A -= 0x60;
        }
        if (half_carry) {
            A -= 0x06;
        }
    }
    else {
        if (carry || A > 0x99) {
            carry = true;
            A += 0x60;
        }
        if (half_carry || (A & 0x0F) > 0x09) {
            A += 0x06;
        }
    }

    this->write_register(REG_A, A);
    this->set_flag_register(HALF_CARRY_FLAG, false);
    this->set_flag_register(CARRY_FLAG, carry);
    this->set_flag_register(ZERO_FLAG, (A == 0));
}
