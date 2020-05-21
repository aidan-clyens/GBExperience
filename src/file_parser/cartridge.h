#pragma once

#include <vector>
#include <cstdint>


class Cartridge {

};


class ROMOnly : public Cartridge {
    public:
        ROMOnly(std::vector<char>);
        virtual ~ROMOnly();

        uint8_t read(uint16_t);
        uint16_t write(uint16_t, uint8_t);

    private:
        std::vector<uint8_t> m_rom_buffer;
};