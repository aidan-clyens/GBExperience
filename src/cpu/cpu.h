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

        void write_register(const std::string &, uint16_t);
        uint16_t read_register(const std::string &);

        void set_flag_register(CPUFlag_t, bool);
        bool read_flag_register(CPUFlag_t);
        void reset_flag_register();

    private:
        CPURegisters m_registers;
        MemoryMap &m_memory_map;
};
