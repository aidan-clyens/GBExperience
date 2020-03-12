#include "cpu.h"


void CPU::load(const std::string &r1, const std::string &r2) {
    uint8_t val = this->read_register(r2);

    std::cout << "LD " << r1 << ", " << r2 << std::endl;

    if (r1 == "HL") {
        this->write_memory(val);
    }
    else {
        this->write_register(r1, val);
    }
}

void CPU::load(const std::string &r1, uint8_t n) {
    std::cout << "LD " << r1 << ", " << n << std::endl;

    if (r1 == "HL") {
        this->write_memory(n);
    }
    else {
        this->write_register(r1, n);
    }
}

void CPU::load_from_mem(const std::string &r1, const std::string &r2) {
    uint8_t val = this->read_memory(r2);

    std::cout << "LD " << r1 << ", " << r2 << std::endl;

    if (r1 == "HL") {
        this->write_memory(val);
    }
    else {
        this->write_register(r1, val);
    }
}

void CPU::load_from_mem(const std::string &r1, uint16_t nn) {
    uint8_t val = this->m_memory_map.read(nn);

    std::cout << "LD " << r1 << ", (" << nn << ")" << std::endl;

    if (r1 == "HL") {
        this->write_memory(val);
    }
    else {
        this->write_register(r1, val);
    }
}