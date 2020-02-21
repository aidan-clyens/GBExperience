#pragma once

#include <iostream>
#include <exception>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

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
        bool _check_register_valid(const std::string &);
        void _write_8bit_register(const std::string &, uint8_t);
        uint8_t _read_8bit_register(const std::string &);

        std::vector<std::string> m_valid_8bit_registers;
        std::vector<std::string> m_valid_16bit_registers;

        std::map<std::string, uint8_t> m_registers;
        uint16_t m_PC;
        uint16_t m_SP;

        MemoryMap &m_memory_map;
};
