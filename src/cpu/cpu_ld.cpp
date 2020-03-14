#include "cpu.h"


void CPU::load(const std::string &r1, const std::string &r2) {
    uint16_t val = this->read_register(r2);

    std::cout << "LD " << r1 << ", " << r2 << std::endl;

    this->write_register(r1, val);
}

void CPU::load(const std::string &r1, uint16_t n) {
    std::cout << "LD " << r1 << ", " << n << std::endl;

    this->write_register(r1, n);
}

void CPU::load_from_mem(const std::string &r1, const std::string &r2) {
    uint8_t val = this->read_memory(r2);

    std::cout << "LD " << r1 << ", " << r2 << std::endl;

    this->write_register(r1, val);
}

void CPU::load_from_mem(const std::string &r1, uint16_t nn) {
    uint8_t val = this->m_memory_map.read(nn);

    std::cout << "LD " << r1 << ", (" << nn << ")" << std::endl;

    this->write_register(r1, val);
}

void CPU::load_to_mem(const std::string &r1, const std::string &r2) {
    uint8_t val = this->read_register(r2);

    std::cout << "LD " << r1 << ", " << r2 << std::endl;

    this->write_memory(r1, val);
}

void CPU::load_to_mem(const std::string &r1, uint16_t n) {
    std::cout << "LD " << r1 << ", " << n << std::endl;

    this->write_memory(r1, n);
}

void CPU::load_to_mem(uint16_t nn, const std::string &r2) {
    uint8_t val = this->read_register(r2);

    std::cout << "LD (" << nn << "), " << r2 << std::endl;

    this->m_memory_map.write(nn, val);
}
