#pragma once

#include <iostream>
#include <exception>

#include "cpu_registers.h"
#include "../memory/memory_map.h"


class CPU {
    public:
        CPU(MemoryMap &);
        virtual ~CPU();

        uint8_t fetch_op();
        bool decode_op(uint8_t);

        void write_register(const std::string &, uint16_t);
        uint16_t read_register(const std::string &);

    private:
        CPURegisters m_registers;
        MemoryMap &m_memory_map;
};
