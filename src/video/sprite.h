#pragma once

#include <cstdint>

#include "../memory/memory_map.h"
#include "definitions.h"
#include "tile.h"


class Sprite {
    public:
        Sprite(int, MemoryMap &);
        virtual ~Sprite();

        uint8_t get_x_pos();
        uint8_t get_y_pos();

        uint8_t get_pattern_number();
        
        bool get_priority();
        bool get_x_flip();
        bool get_y_flip();
        
        ObjectPalette_t get_palette();

        Tile get_tile();

    private:
        MemoryMap &m_memory_map;
        uint16_t m_starting_address;
};