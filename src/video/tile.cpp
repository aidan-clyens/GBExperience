#include "tile.h"


Tile::Tile(uint16_t starting_address, MemoryMap &mem_map) {
    // Initialize all pixels as colour 0, normally white
    this->init_tile();

    int buffer_index = 0;
    for (int i = 0; i < 2 * TILE_HEIGHT; i += 2) {
        TileRow row(starting_address + i, mem_map);

        for (int x = 0; x < TILE_WIDTH; x++) {
            m_buffer[buffer_index] = row.get_pixel(x);
            buffer_index++;
        }
    }
}

Tile::~Tile() {

}

PixelColour_t Tile::get_pixel(int x, int y) {
    int index = this->get_index(x, y);

    return m_buffer[index];
}

void Tile::init_tile() {
    for (int i = 0; i < TILE_WIDTH * TILE_HEIGHT; i++) {
        m_buffer[i] = Colour0;
    }
}

PixelColour_t *Tile::get_pixel_buffer() {
    return m_buffer;
}

int Tile::get_index(int x, int y) {
    return y * TILE_WIDTH + x;
}


/******   TileRow   ******/
TileRow::TileRow(uint16_t address, MemoryMap &mem_map) {
    uint8_t byte1 = mem_map.read(address);
    uint8_t byte2 = mem_map.read(address + 1);

    m_row = this->get_tile_row(byte1, byte2);
}

TileRow::~TileRow() {

}

PixelColour_t TileRow::get_pixel(int x) {
    return m_row[x];
}

std::vector<PixelColour_t> TileRow::get_tile_row(uint8_t byte1, uint8_t byte2) {
    std::vector<PixelColour_t> pixels;

    for (int i = 7; i >= 0; i--) {
        uint8_t lsb = (byte1 >> i) & 0x1;
        uint8_t msb = (byte2 >> i) & 0x1;

        PixelColour_t pixel = (PixelColour_t)((msb << 1) | lsb);
        pixels.push_back(pixel);
    }

    return pixels;
}