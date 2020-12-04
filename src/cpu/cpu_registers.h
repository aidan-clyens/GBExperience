#pragma once

#include <iostream>
#include <exception>
#include <map>
#include <string>
#include <vector>
#include <algorithm>

enum Registers_t {
    REG_A,
    REG_F,
    REG_B,
    REG_C,
    REG_D,
    REG_E,
    REG_H,
    REG_L,
    REG_AF,
    REG_BC,
    REG_DE,
    REG_HL,
    REG_PC,
    REG_SP
};

class CPURegisters {
    public:
        CPURegisters();
        virtual ~CPURegisters();

        void write_register(Registers_t, uint16_t);
        uint16_t read_register(Registers_t);

        static const char *to_string(Registers_t);

    private:
        std::map<Registers_t, uint8_t> m_registers;

        uint16_t m_PC;
        uint16_t m_SP;
};
