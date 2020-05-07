#include "gtest/gtest.h"

int x = 25;
int y = 50;

uint8_t pattern_num = 0x10;

bool priority = true;
bool x_flip = false;
bool y_flip = true;
ObjectPalette_t palette_num = OBJECT_PALETTE_0;


MemoryMap setup_sprite(int sprite_num) {
    uint16_t sprite_address = OAM_ADDRESS + sprite_num * SPRITE_BYTES;
    uint16_t tile_starting_address = TILE_DATA_UNSIGNED + pattern_num * TILE_BYTE_LENGTH;

    MemoryMap mem_map;

    mem_map.write(sprite_address, y);
    mem_map.write(sprite_address + 1, x);
    mem_map.write(sprite_address + 2, pattern_num);

    uint8_t byte3 = 0x0;
    if (priority) byte3 |= 0x80;
    if (y_flip) byte3 |= 0x40;
    if (x_flip) byte3 |= 0x20;
    if (palette_num == OBJECT_PALETTE_1) byte3 |= 0x10;

    mem_map.write(sprite_address + 3, byte3);

    // 0, 0, 0, 0, 0, 0, 0, 0
    // 0, 0, 0, 0, 0, 0, 0, 0
    // 1, 1, 1, 1, 1, 1, 1, 1
    // 1, 1, 1, 1, 1, 1, 1, 1
    // 2, 2, 2, 2, 2, 2, 2, 2
    // 2, 2, 2, 2, 2, 2, 2, 2
    // 3, 3, 3, 3, 3, 3, 3, 3
    // 3, 3, 3, 3, 3, 3, 3, 3
    int tile_size = 2 * TILE_HEIGHT;
    uint8_t tile_data[] = {
        0x00, 0x00,
        0x00, 0x00,
        0xFF, 0x00,
        0xFF, 0x00,
        0x00, 0xFF,
        0x00, 0xFF,
        0xFF, 0xFF,
        0xFF, 0xFF
    };

    for (int i = 0; i < tile_size; i++) {
        mem_map.write(tile_starting_address + i, tile_data[i]);
    }

    return mem_map;
}


TEST(Sprite, InitSprite) {
    int sprite_num = 0;

    MemoryMap memory_map = setup_sprite(sprite_num);
    Sprite sprite(sprite_num, memory_map);
}


TEST(Sprite, GetYPos) {
    int sprite_num = 0;

    MemoryMap memory_map = setup_sprite(sprite_num);
    Sprite sprite(sprite_num, memory_map);

    EXPECT_EQ(y, sprite.get_y_pos());
}


TEST(Sprite, GetXPos) {
    int sprite_num = 0;

    MemoryMap memory_map = setup_sprite(sprite_num);

    Sprite sprite(sprite_num, memory_map);

    EXPECT_EQ(x, sprite.get_x_pos());
}


TEST(Sprite, GetPatternNumber) {
    int sprite_num = 0;

    MemoryMap memory_map = setup_sprite(sprite_num);
    Sprite sprite(sprite_num, memory_map);

    EXPECT_EQ(pattern_num, sprite.get_pattern_number());
}


TEST(Sprite, GetPriority) {
    int sprite_num = 0;

    MemoryMap memory_map = setup_sprite(sprite_num);
    Sprite sprite(sprite_num, memory_map);

    EXPECT_EQ(priority, sprite.get_priority());
}


TEST(Sprite, GetYFlip) {
    int sprite_num = 0;

    MemoryMap memory_map = setup_sprite(sprite_num);
    Sprite sprite(sprite_num, memory_map);

    EXPECT_EQ(y_flip, sprite.get_y_flip());
}


TEST(Sprite, GetXFlip) {
    int sprite_num = 0;

    MemoryMap memory_map = setup_sprite(sprite_num);
    Sprite sprite(sprite_num, memory_map);

    EXPECT_EQ(x_flip, sprite.get_x_flip());
}


TEST(Sprite, GetPalette) {
    int sprite_num = 0;

    MemoryMap memory_map = setup_sprite(sprite_num);
    Sprite sprite(sprite_num, memory_map);

    EXPECT_EQ(palette_num, sprite.get_palette());
}


TEST(Sprite, GetTile) {
    int sprite_num = 0;

    MemoryMap memory_map = setup_sprite(sprite_num);
    Sprite sprite(sprite_num, memory_map);

    Tile tile = sprite.get_tile();

    for (int y = 0; y < TILE_HEIGHT; y++) {
        for (int x = 0; x < TILE_WIDTH; x++) {
            if (y <= 1) {
                EXPECT_EQ(Colour0, tile.get_pixel(x, y));
            }
            else if (y > 1 && y <= 3) {
                EXPECT_EQ(Colour1, tile.get_pixel(x, y));
            }
            else if (y > 3 && y <= 5) {
                EXPECT_EQ(Colour2, tile.get_pixel(x, y));
            }
            else {
                EXPECT_EQ(Colour3, tile.get_pixel(x, y));
            }
        }
    }
}