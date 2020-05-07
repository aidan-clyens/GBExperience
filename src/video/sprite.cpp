#include "sprite.h"


Sprite::Sprite(int sprite_number, MemoryMap &mem_map):
m_memory_map(mem_map),
m_starting_address(OAM_ADDRESS + sprite_number * SPRITE_BYTES)
{

}

Sprite::~Sprite() {

}

uint8_t Sprite::get_x_pos() {
    return m_memory_map.read(m_starting_address + 1);
}

uint8_t Sprite::get_y_pos() {
    return m_memory_map.read(m_starting_address);
}

uint8_t Sprite::get_pattern_number() {
    return m_memory_map.read(m_starting_address + 2);
}

bool Sprite::get_priority() {
    uint8_t byte3 = m_memory_map.read(m_starting_address + 3);
    return (byte3 >> 7) & 0x01 == 0x01;
}

bool Sprite::get_x_flip() {
    uint8_t byte3 = m_memory_map.read(m_starting_address + 3);
    return (byte3 >> 5) & 0x01 == 0x01;
}

bool Sprite::get_y_flip() {
    uint8_t byte3 = m_memory_map.read(m_starting_address + 3);
    return (byte3 >> 6) & 0x01 == 0x01;
}

ObjectPalette_t Sprite::get_palette() {
    uint8_t byte3 = m_memory_map.read(m_starting_address + 3);
    return ((byte3 >> 4) & 0x01 == 0x01) ? OBJECT_PALETTE_1 : OBJECT_PALETTE_0;
}

Tile Sprite::get_tile() {
    uint8_t pattern_num = this->get_pattern_number();
    uint16_t tile_address = TILE_DATA_UNSIGNED + pattern_num * TILE_BYTE_LENGTH;

    return Tile(tile_address, m_memory_map);
}
