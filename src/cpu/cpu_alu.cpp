#include "cpu.h"

// ADD A, n
// ADC A, n
void CPU::alu_add(const std::string &reg, bool carry) {
    uint8_t A = this->read_register("A");
    uint8_t n = this->read_register(reg);

    if (carry) std::cout << "ADC A, " << reg << std::endl;
    else std::cout << "ADD A, " << reg << std::endl;

    this->write_register("A", A + n);
    // TODO Implement carry
}

void CPU::alu_add(uint8_t n, bool carry) {
    uint8_t A = this->read_register("A");

    if (carry) std::cout << "ADC A, " << n << std::endl;
    else std::cout << "ADD A, " << n << std::endl;

    this->write_register("A", A + n);
    // TODO Implement carry
}

// SUB n
// SBC n
void CPU::alu_sub(const std::string &reg, bool carry) {
    uint8_t A = this->read_register("A");
    uint8_t n = this->read_register(reg);

    if (carry) std::cout << "SBC A, " << reg << std::endl;
    else std::cout << "SUB A, " << reg << std::endl;

    this->write_register("A", A - n);
    // TODO Implement carry
}

void CPU::alu_sub(uint8_t n, bool carry) {
    uint8_t A = this->read_register("A");

    if (carry) std::cout << "SBC A, " << n << std::endl;
    else std::cout << "SUB A, " << n << std::endl;

    this->write_register("A", A - n);
    // TODO Implement carry
}

// AND n
void CPU::alu_and(const std::string &reg) {
    uint8_t A = this->read_register("A");
    uint8_t n = this->read_register(reg);

    std::cout << "AND A, " << reg << std::endl;

    this->write_register("A", A & n);
}

void CPU::alu_and(uint8_t n) {
    uint8_t A = this->read_register("A");

    std::cout << "AND A, " << n << std::endl;

    this->write_register("A", A & n);
}

// OR n
void CPU::alu_or(const std::string &reg) {
    uint8_t A = this->read_register("A");
    uint8_t n = this->read_register(reg);

    std::cout << "OR A, " << reg << std::endl;

    this->write_register("A", A | n);
}

void CPU::alu_or(uint8_t n) {
    uint8_t A = this->read_register("A");

    std::cout << "OR A, " << n << std::endl;

    this->write_register("A", A | n);
}

// XOR n
void CPU::alu_xor(const std::string &reg) {
    uint8_t A = this->read_register("A");
    uint8_t n = this->read_register(reg);

    std::cout << "XOR A, " << reg << std::endl;

    this->write_register("A", A ^ n);
}

void CPU::alu_xor(uint8_t n) {
    uint8_t A = this->read_register("A");

    std::cout << "XOR A, " << n << std::endl;

    this->write_register("A", A ^ n);
}

// CP n
void alu_cp(const std::string &);
void alu_cp(uint8_t);
// INC n
void CPU::alu_inc(const std::string &reg) {
    uint16_t N = this->read_register(reg);

    std::cout << "INC " << reg << std::endl;

    this->write_register(reg, N + 1);
}

// DEC n
void alu_dec(const std::string &reg);