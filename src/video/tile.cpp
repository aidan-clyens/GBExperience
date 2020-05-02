#include "tile.h"


Tile::Tile(uint16_t starting_address, MemoryMap &mem_map) {
    // Initialize all pixels as colour 0, normally white
    for (int i = 0; i < TILE_WIDTH * TILE_HEIGHT; i++) {
        m_buffer[i] = Colour0;
    }

    int buffer_index = 0;
    for (int y = 0; y < TILE_HEIGHT; y += 2) {
        uint8_t byte1 = mem_map.read(starting_address + y);
        uint8_t byte2 = mem_map.read(starting_address + y + 1);

        std::vector<PixelColour_t> row = this->get_tile_row(byte1, byte2);
        for (int x = 0; x < TILE_WIDTH; x++) {
            m_buffer[buffer_index] = row[x];
            buffer_index++;
        }
    }
}

Tile::~Tile() {

}

PixelColour_t Tile::get_pixel(int x, int y) {
    int index = (y * TILE_WIDTH * 2) + x;

    return m_buffer[index];
}

std::vector<PixelColour_t> Tile::get_tile_row(uint8_t byte1, uint8_t byte2) {
    std::vector<PixelColour_t> pixels;

    for (int i = 7; i >= 0; i--) {
        uint8_t lsb = (byte1 >> i) & 0x1;
        uint8_t msb = (byte2 >> i) & 0x1;

        PixelColour_t pixel = (PixelColour_t)((msb << 1) | lsb);
        pixels.push_back(pixel);
    }

    return pixels;
}
