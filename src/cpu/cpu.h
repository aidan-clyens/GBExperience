#pragma once

#include <iostream>
#include <exception>
#include <string>
#include <map>

#include "../memory/memory_map.h"


class CPU {
    public:
        CPU(MemoryMap &);
        virtual ~CPU();

        void write_register(const std::string &, uint16_t);
        uint16_t read_register(const std::string &);

    private:
        std::map<std::string, uint16_t> m_registers;

        MemoryMap &m_memory_map;
};
