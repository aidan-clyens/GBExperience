#pragma once

#include <iostream>
#include <exception>
#include <string>
#include <map>


class CPU {
    public:
        CPU();
        virtual ~CPU();

        void write_register(const std::string &, uint16_t);
        uint16_t read_register(const std::string &);

    private:
        std::map<std::string, uint16_t> m_registers;
};
