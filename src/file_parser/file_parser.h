#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

typedef enum cartridge_type {
    ROM_ONLY = 0x0,
    ROM_MBC1 = 0x1,
    ROM_MBC1_RAM = 0x2,
    ROM_MBC1_RAM_BATT = 0x3,
    ROM_MBC2 = 0x5,
    ROM_MBC2_BATT = 0x6,
    ROM_RAM = 0x8,
    ROM_RAM_BATT = 0x9,
    ROM_MMM01 = 0xB,
    ROM_MMM01_SRAM = 0xC,
    ROM_MMM01_SRAM_BATT = 0xD,
    ROM_MBC3_TIMER_BATT = 0xF,
    ROM_MBC3_TIMER_RAM_BATT = 0x10,
    ROM_MBC3 = 0x11,
    ROM_MBC3_RAM = 0x12,
    ROM_MBC3_RAM_BATT = 0x13,
    ROM_MBC5 = 0x19,
    ROM_MBC5_RAM = 0x1A,
    ROM_MBC5_RAM_BATT = 0x1B,
    ROM_MBC5_RUMBLE = 0x1C,
    ROM_MBC5_RUMBLE_SRAM = 0x1D,
    ROM_MBC5_RUMBLE_SRAM_BATT = 0x1E,
    POCKET_CAMERA = 0x1F,
    BANDAI_TAMA5 = 0xFD,
    HUDSON_HUC_3 = 0xFE,
    HUDSON_HUC_1 = 0xFF
} cartridge_type_t;

class FileParser {
    public:
        FileParser();
        virtual ~FileParser();
    
        bool load_rom(const std::string &);

        std::vector<uint8_t> get_buffer_data();
        uint8_t get_byte(int) const;
        int get_buffer_size() const;

        std::string get_rom_name() const;
        cartridge_type_t get_cartridge_type() const;
        std::string get_cartridge_type_string() const;

        bool is_gb_color() const;
        bool is_sgb() const;
    
    private:
        std::vector<uint8_t> m_buffer;

        size_t m_buffer_size;
};