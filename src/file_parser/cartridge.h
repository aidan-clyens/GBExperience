#pragma once

#include <iostream>
#include <vector>
#include <cstdint>


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


class Cartridge {
    public:
        Cartridge();
        virtual ~Cartridge();

        virtual uint8_t read(uint16_t) = 0;
        virtual uint16_t write(uint16_t, uint8_t) = 0;

        void set_cartridge_type(cartridge_type_t);
        cartridge_type_t get_cartridge_type() const;
        void set_size(int);
        int get_size() const;

    private:
        cartridge_type_t m_cartridge_type;
        int m_cartridge_size;
};


class ROMOnly : public Cartridge {
    public:
        ROMOnly(std::vector<char>);
        virtual ~ROMOnly();

        uint8_t read(uint16_t) override;
        uint16_t write(uint16_t, uint8_t) override;

    private:
        std::vector<uint8_t> m_rom_buffer;
};