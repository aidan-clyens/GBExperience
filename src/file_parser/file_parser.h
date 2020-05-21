#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "cartridge.h"


class FileParser {
    public:
        FileParser();
        virtual ~FileParser();
    
        Cartridge load_rom(const std::string &);

        std::vector<uint8_t> get_buffer_data();
        uint8_t get_byte(int) const;
        int get_buffer_size() const;

        std::string get_rom_name() const;
        cartridge_type_t get_cartridge_type() const;
        std::string get_cartridge_type_string() const;
        int get_rom_size_banks() const;
        int get_ram_size_banks() const;

        bool is_gb_color() const;
        bool is_sgb() const;
    
    private:
        std::vector<uint8_t> m_header_buffer;

        size_t m_header_buffer_size;
};