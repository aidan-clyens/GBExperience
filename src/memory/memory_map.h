#pragma once

#include <map>
#include <exception>
#include <vector>

#include "memory.h"
#include "io.h"
#include "../video/definitions.h"
#include "../debugger/logger.h"


class MemoryMap {
    public:
        MemoryMap();
        virtual ~MemoryMap();

        bool init_memory_map();
        void load_rom(std::vector<uint8_t>);
        uint16_t write(uint16_t, uint8_t);
        uint8_t read(uint16_t);

        uint16_t write_vram(uint16_t, uint8_t);
        uint8_t read_vram(uint16_t);

        int get_index(uint16_t) const;

        void set_input(uint8_t);
        void increment_io_counter(IORegisters_t);

    private:
        int m_address_space[12];
        std::map<int, void*> m_memory_map;

        IO m_io;
};
