#include "cpu.h"


void CPU::load(Registers_t r1, Registers_t r2) {
    uint16_t val = this->read_register(r2);

    log_cpu("LD %s, %s", CPURegisters::to_string(r1), CPURegisters::to_string(r2));

    this->write_register(r1, val);
}

void CPU::load(Registers_t r1, uint16_t n) {
    this->write_register(r1, n);

    log_cpu("LD %s, %X", CPURegisters::to_string(r1), n);
}

void CPU::load_from_mem(Registers_t r1, Registers_t r2) {
    uint8_t val = this->read_memory(r2);

    log_cpu("LD %s, (%s)", CPURegisters::to_string(r1), CPURegisters::to_string(r2));

    this->write_register(r1, val);
}

void CPU::load_from_mem(Registers_t r1, uint16_t nn) {
    uint8_t val = this->m_memory_map.read(nn);

    log_cpu("LD %s, (%X)", CPURegisters::to_string(r1), nn);

    this->write_register(r1, val);
}

void CPU::load_to_mem(Registers_t r1, Registers_t r2) {
    uint8_t val = this->read_register(r2);

    log_cpu("LD (%s), %s", CPURegisters::to_string(r1), CPURegisters::to_string(r2));

    this->write_memory(r1, val);
}

void CPU::load_to_mem(Registers_t r1, uint16_t n) {
    this->write_memory(r1, n);

    log_cpu("LD (%s), %X", CPURegisters::to_string(r1), n);
}

void CPU::load_to_mem(uint16_t nn, Registers_t r2) {
    uint8_t val = this->read_register(r2);

    log_cpu("LD (%X), %s", nn, CPURegisters::to_string(r2));

    this->m_memory_map.write(nn, val);
}

void CPU::load_to_mem16bit(uint16_t nn, Registers_t r2) {
    uint16_t val = this->read_register(r2);
    uint8_t lower_bits = val & 0xFF;
    uint8_t upper_bits = val >> 8;

    log_cpu("LD (%X), %s", nn, CPURegisters::to_string(r2));

    this->m_memory_map.write(nn, lower_bits);
    this->m_memory_map.write(nn+1, upper_bits);
}

void CPU::load_HL(int8_t n) {
    uint16_t SP = this->read_register(REG_SP);
    int result_full = static_cast<int>(SP + n);
    uint16_t result = static_cast<uint16_t>(result_full);
    
    log_cpu("LDHL %X", n);

    this->reset_flag_register();
    this->set_flag_register(CARRY_FLAG, ((SP ^ n ^ (result & 0xFFFF)) & 0x100) == 0x100);
    this->set_flag_register(HALF_CARRY_FLAG, ((SP ^ n ^ (result & 0xFFFF)) & 0x10) == 0x10);

    this->load(REG_HL, result);
}

void CPU::push_stack(Registers_t reg) {
    uint16_t val = this->read_register(reg);
    uint16_t SP = this->read_register(REG_SP);

    this->write_register(REG_SP, SP - 1);
    this->write_memory(REG_SP, val & 0xFF);
    
    this->write_register(REG_SP, SP - 2);
    this->write_memory(REG_SP, val >> 8);
}

void CPU::pop_stack(Registers_t reg) {
    uint16_t SP = this->read_register(REG_SP);

    uint8_t val_1 = this->read_memory(REG_SP);
    this->write_register(REG_SP, SP + 1);

    uint8_t val_2 = this->read_memory(REG_SP);
    this->write_register(REG_SP, SP + 2);

    uint16_t val = (val_1 << 8) | val_2;
    this->write_register(reg, val);
}