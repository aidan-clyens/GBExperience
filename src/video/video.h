#pragma once

#include "../memory/memory_map.h"


class Video {
    public:
        Video(MemoryMap &);
        virtual ~Video();

        void tick();

        uint8_t read_io_register(IORegisters_t);
        void write_io_register(IORegisters_t, uint8_t);

    private:
        MemoryMap &m_memory_map;
};