#pragma once

#include <iostream>
#include <exception>
#include <string>

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
        uint8_t m_A;
        uint8_t m_F;
        uint8_t m_B;
        uint8_t m_C;
        uint8_t m_D;
        uint8_t m_E;
        uint8_t m_H;
        uint8_t m_L;
        uint16_t m_PC;
        uint16_t m_SP;
};
