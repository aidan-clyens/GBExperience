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

    #ifdef DEBUG
    std::cout << "SWAP " << reg << std::endl;
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

    #ifdef DEBUG
    std::cout << "CPL" << std::endl;
    #endif

    this->set_flag_register(SUBTRACT_FLAG, true);
    this->set_flag_register(HALF_CARRY_FLAG, true);

    this->write_register("A", result);
}

void CPU::complement_carry() {
    bool carry = this->read_flag_register(CARRY_FLAG);

    #ifdef DEBUG
    std::cout << "CCF" << std::endl;
    #endif

    this->set_flag_register(SUBTRACT_FLAG, false);
    this->set_flag_register(HALF_CARRY_FLAG, false);
    
    this->set_flag_register(CARRY_FLAG, !carry);
}

void CPU::set_carry() {

    #ifdef DEBUG
    std::cout << "SCF" << std::endl;
    #endif

    this->set_flag_register(CARRY_FLAG, true);
}

void CPU::halt() {

    #ifdef DEBUG
    std::cout << "HALT" << std::endl;
    #endif

    m_running = false;
}

void CPU::enable_interrupts() {
    #ifdef DEBUG
    std::cout << "EI" << std::endl;
    #endif

    m_interrupts_enabled = true;
}

void CPU::disable_interrupts() {
    #ifdef DEBUG
    std::cout << "DI" << std::endl;
    #endif

    m_interrupts_enabled = false;
}