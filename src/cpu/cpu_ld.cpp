#include "cpu.h"


void CPU::load(const std::string &r1, const std::string &r2) {
    uint16_t val = this->read_register(r2);

    #ifdef CPU_DEBUG
    log_cpu("LD %s, %s", r1.c_str(), r2.c_str());
    #endif

    this->write_register(r1, val);
}

void CPU::load(const std::string &r1, uint16_t n) {
    this->write_register(r1, n);

    #ifdef CPU_DEBUG
    log_cpu("LD %s, %X", r1.c_str(), n);
    #endif
}

void CPU::load_from_mem(const std::string &r1, const std::string &r2) {
    uint8_t val = this->read_memory(r2);

    #ifdef CPU_DEBUG
    log_cpu("LD %s, (%s)", r1.c_str(), r2.c_str());
    #endif

    this->write_register(r1, val);
}

void CPU::load_from_mem(const std::string &r1, uint16_t nn) {
    uint8_t val = this->m_memory_map.read(nn);

    #ifdef CPU_DEBUG
    log_cpu("LD %s, (%X)", r1.c_str(), nn);
    #endif

    this->write_register(r1, val);
}

void CPU::load_to_mem(const std::string &r1, const std::string &r2) {
    uint8_t val = this->read_register(r2);

    #ifdef CPU_DEBUG
    log_cpu("LD (%s), %s", r1.c_str(), r2.c_str());
    #endif

    this->write_memory(r1, val);
}

void CPU::load_to_mem(const std::string &r1, uint16_t n) {
    this->write_memory(r1, n);

    #ifdef CPU_DEBUG
    log_cpu("LD (%s), %X", r1.c_str(), n);
    #endif
}

void CPU::load_to_mem(uint16_t nn, const std::string &r2) {
    uint8_t val = this->read_register(r2);

    #ifdef CPU_DEBUG
    log_cpu("LD (%X), %s", nn, r2.c_str());
    #endif

    this->m_memory_map.write(nn, val);
}

void CPU::load_HL(int8_t n) {
    uint16_t SP = this->read_register("SP");
    uint16_t result = SP + n;

    #ifdef CPU_DEBUG
    log_cpu("LDHL %X", n);
    #endif

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