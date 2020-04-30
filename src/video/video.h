#pragma once

#include "../memory/memory_map.h"


class Video {
    public:
        Video(MemoryMap &);
        virtual ~Video();

        void tick();

        // LCDC Register
        bool lcd_display_enabled();
        bool window_display_enabled();
        bool sprite_display_enabled();
        bool background_display_enabled();

        uint8_t read_io_register(IORegisters_t);
        void write_io_register(IORegisters_t, uint8_t);

    private:
        MemoryMap &m_memory_map;
};