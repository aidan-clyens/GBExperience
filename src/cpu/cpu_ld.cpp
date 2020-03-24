#include "cpu.h"


void CPU::load(const std::string &r1, const std::string &r2) {
    uint16_t val = this->read_register(r2);

    this->write_register(r1, val);
}

void CPU::load(const std::string &r1, uint16_t n) {
    this->write_register(r1, n);
}

void CPU::load_from_mem(const std::string &r1, const std::string &r2) {
    uint8_t val = this->read_memory(r2);

    this->write_register(r1, val);
}

void CPU::load_from_mem(const std::string &r1, uint16_t nn) {
    uint8_t val = this->m_memory_map.read(nn);

    this->write_register(r1, val);
}

void CPU::load_to_mem(const std::string &r1, const std::string &r2) {
    uint8_t val = this->read_register(r2);

    this->write_memory(r1, val);
}

void CPU::load_to_mem(const std::string &r1, uint16_t n) {
    this->write_memory(r1, n);
}

void CPU::load_to_mem(uint16_t nn, const std::string &r2) {
    uint8_t val = this->read_register(r2);

    this->m_memory_map.write(nn, val);
}

void CPU::load_HL(uint8_t n) {
    uint16_t SP = this->read_register("SP");
    uint16_t result = SP + n;
        
    this->reset_flag_register();
    
    if (SP + n > 0xFFFF) {
        this->set_flag_register(CARRY_FLAG, true);
    }

    if ((SP & 0xFF) + (n & 0xFF) > 0xFF) {
        this->set_flag_register(HALF_CARRY_FLAG, true);
    }

    this->load("HL", result);
}

void CPU::push_stack(const std::string &reg) {
    uint16_t val = this->read_register(reg);
    uint16_t SP = this->read_register("SP");

    this->write_register("SP", SP - 1);
    this->write_memory("SP", val & 0xFF);
    
    this->write_register("SP", SP - 2);
    this->write_memory("SP", val >> 8);
}

void CPU::pop_stack(const std::string &reg) {
    uint16_t SP = this->read_register("SP");

    uint8_t val_1 = this->read_memory("SP");
    this->write_register("SP", SP + 1);

    uint8_t val_2 = this->read_memory("SP");
    this->write_register("SP", SP + 2);

    uint16_t val = (val_1 << 8) | val_2;
    this->write_register(reg, val);
}