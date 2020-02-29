#pragma once

#include <iostream>
#include <exception>

#include "cpu_registers.h"
#include "../memory/memory_map.h"


typedef enum CPUFlag {
    ZERO_FLAG = 0x80,
    SUBTRACT_FLAG = 0x40,
    HALF_CARRY_FLAG = 0x20,
    CARRY_FLAG = 0x10
} CPUFlag_t;


class CPU {
    public:
        CPU(MemoryMap &);
        virtual ~CPU();

        uint8_t fetch_op();
        bool decode_op(uint8_t);

        void write_register(const std::string &, uint16_t);
        uint16_t read_register(const std::string &);

        void set_flag_register(CPUFlag_t, bool);
        bool read_flag_register(CPUFlag_t);
        void reset_flag_register();

    private:
        CPURegisters m_registers;
        MemoryMap &m_memory_map;

        /****    8-Bit ALU    ****/
        // ADD A, n
        // ADC A, n
        void alu_add(const std::string &, bool);
        void alu_add(uint8_t, bool);
        // SUB n
        // SBC n
        void alu_sub(const std::string &, bool);
        void alu_sub(uint8_t, bool);
        // AND n
        void alu_and(const std::string &);
        void alu_and(uint8_t);
        // OR n
        void alu_or(const std::string &);
        void alu_or(uint8_t);
        // XOR n
        void alu_xor(const std::string &);
        void alu_xor(uint8_t);
        // CP n
        void alu_cp(const std::string &);
        void alu_cp(uint8_t);
        // INC n
        void alu_inc(const std::string &);
        // DEC n
        void alu_dec(const std::string &);

        // TODO Add jump instructions
};
