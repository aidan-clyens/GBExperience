#include "cpu.h"


CPU::CPU(MemoryMap &mem_map):
m_memory_map(mem_map)
{

}

CPU::~CPU() {

}

uint8_t CPU::fetch_op() {
    uint16_t address = this->read_register("PC");
    this->write_register("PC", address + 1);

    return m_memory_map.read(address);
}

void CPU::write_register(const std::string &reg, uint16_t data) {
    m_registers.write_register(reg, data);
}

uint16_t CPU::read_register(const std::string &reg) {
    return m_registers.read_register(reg);
}

void CPU::set_flag_register(CPUFlag_t flag, bool value) {
    uint8_t flag_register_val = this->read_register("F");
    uint8_t val = (value) ? flag : 0;

    // Reset flag value to 0
    flag_register_val &= ~flag;
    this->write_register("F", flag_register_val);
    // Set new flag value
    flag_register_val |= val;
    this->write_register("F", flag_register_val);
}

bool CPU::read_flag_register(CPUFlag_t flag) {
    return (this->read_register("F") & flag) == flag;
}

void CPU::reset_flag_register() {
    this->write_register("F", 0);
}