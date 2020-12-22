#pragma once

#include <iostream>
#include <vector>
#include <cstdint>

#include "../memory/memory.h"
#include "../debugger/logger.h"


const int ROM_BANK_SIZE = 16 * 1024;


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


typedef enum mode_select {
    ROM_MODE,
    RAM_MODE
} mode_select_t;


class Cartridge {
    public:
        Cartridge(std::vector<char>, int);
        virtual ~Cartridge();

        virtual uint8_t read(uint16_t) = 0;
        virtual uint16_t write(uint16_t, uint8_t) = 0;

        void set_cartridge_type(cartridge_type_t);
        cartridge_type_t get_cartridge_type() const;
        void set_num_rom_banks(int);
        int get_num_rom_banks() const;

    protected:
        cartridge_type_t m_cartridge_type;
        int m_cartridge_size;
        int m_num_rom_banks;

        std::vector<Memory *> m_rom_banks;
};


class ROMOnly : public Cartridge {
    public:
        ROMOnly(std::vector<char>, int);
        virtual ~ROMOnly();

        uint8_t read(uint16_t) override;
        uint16_t write(uint16_t, uint8_t) override;
};


class MBC1: public Cartridge {
    public:
        MBC1(std::vector<char>, int);
        virtual ~MBC1();

        uint8_t read(uint16_t) override;
        uint16_t write(uint16_t, uint8_t) override;

        bool is_ram_enabled() const;
        int get_rom_bank_number() const;
        mode_select_t get_mode() const;
    private:
        bool m_ram_enabled;
        uint8_t m_rom_bank_bits;
        int m_rom_bank_number;

        mode_select_t m_mode;
};