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

    #ifdef CPU_DEBUG
    log_cpu("SWAP %s", reg.c_str());
    #endif

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

void CPU::complement() {
    uint8_t val = this->read_register("A");
    uint8_t result = ~val;

    #ifdef CPU_DEBUG
    log_cpu("CPL");
    #endif

    this->set_flag_register(SUBTRACT_FLAG, true);
    this->set_flag_register(HALF_CARRY_FLAG, true);

    this->write_register("A", result);
}

void CPU::complement_carry() {
    bool carry = this->read_flag_register(CARRY_FLAG);

    #ifdef CPU_DEBUG
    log_cpu("CCF");
    #endif

    this->set_flag_register(SUBTRACT_FLAG, false);
    this->set_flag_register(HALF_CARRY_FLAG, false);
    
    this->set_flag_register(CARRY_FLAG, !carry);
}

void CPU::set_carry() {

    #ifdef CPU_DEBUG
    log_cpu("SCF");
    #endif

    this->set_flag_register(CARRY_FLAG, true);
}

void CPU::halt() {
    #ifdef CPU_DEBUG
    log_cpu("HALT");
    #endif

    m_halted = true;
}


void CPU::stop() {
    #ifdef CPU_DEBUG
    log_cpu("STOP");
    #endif

    m_stopped = true;
}


void CPU::enable_interrupts() {
    #ifdef CPU_DEBUG
    log_cpu("EI");
    #endif

    m_interrupts_enabled = true;
}

void CPU::disable_interrupts() {
    #ifdef CPU_DEBUG
    log_cpu("DI");
    #endif

    m_interrupts_enabled = false;
}