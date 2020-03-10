#include "cpu.h"


void CPU::load(const std::string &r1, const std::string &r2) {
    uint8_t val;

    std::cout << "LD " << r1 << ", " << r2 << std::endl;

    if (r2 == "HL") {
        val = this->read_memory();
    }
    else {
        val = this->read_register(r2);
    }

    if (r1 == "HL") {
        this->write_memory(val);
    }
    else {
        this->write_register(r1, val);
    }
}

void CPU::load(uint8_t n) {
    std::cout << "LD (HL), " << n << std::endl;

    this->write_memory(n);
}