#pragma once


#include <cstdint>
#include <vector>

#include "video.h"
#include "../memory/memory_map.h"


const int TILE_WIDTH = 8;
const int TILE_HEIGHT = 8;


typedef enum PixelColour {
    Colour0,
    Colour1,
    Colour2,
    Colour3
} PixelColour_t;


class Tile {
    public:
        Tile(uint16_t, MemoryMap &);
        virtual ~Tile();

        PixelColour_t get_pixel(int x, int y);

    private:
        PixelColour_t m_buffer[TILE_WIDTH * TILE_HEIGHT];

        std::vector<PixelColour_t> get_tile_row(uint8_t, uint8_t);
};