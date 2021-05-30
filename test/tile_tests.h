#include "gtest/gtest.h"


// 0, 0, 0, 0, 0, 0, 0, 0
// 0, 0, 0, 0, 0, 0, 0, 0
// 1, 1, 1, 1, 1, 1, 1, 1
// 1, 1, 1, 1, 1, 1, 1, 1
// 2, 2, 2, 2, 2, 2, 2, 2
// 2, 2, 2, 2, 2, 2, 2, 2
// 3, 3, 3, 3, 3, 3, 3, 3
// 3, 3, 3, 3, 3, 3, 3, 3
uint8_t tile_data_1[] = {
    0x00, 0x00,
    0x00, 0x00,
    0xFF, 0x00,
    0xFF, 0x00,
    0x00, 0xFF,
    0x00, 0xFF,
    0xFF, 0xFF,
    0xFF, 0xFF
};

// 0, 0, 1, 1, 2, 2, 3, 3
// 0, 0, 1, 1, 2, 2, 3, 3   
// 0, 0, 1, 1, 2, 2, 3, 3
// 0, 0, 1, 1, 2, 2, 3, 3
// 0, 0, 1, 1, 2, 2, 3, 3
// 0, 0, 1, 1, 2, 2, 3, 3
// 0, 0, 1, 1, 2, 2, 3, 3
// 0, 0, 1, 1, 2, 2, 3, 3
uint8_t tile_data_2[] = {
    0x33, 0x0F,
    0x33, 0x0F,
    0x33, 0x0F,
    0x33, 0x0F,
    0x33, 0x0F,
    0x33, 0x0F,
    0x33, 0x0F,
    0x33, 0x0F
};

MemoryMap setup_tile(uint8_t *tile_data, uint16_t starting_address) {
    MemoryMap mem_map;

    int tile_size = 2 * TILE_HEIGHT;

    for (int i = 0; i < tile_size; i++) {
        mem_map.write(starting_address + i, tile_data[i]);
    }

    return mem_map;
}


TEST(Tile, InitTile) {
    uint16_t starting_address = 0x8000;
    int buffer_size = TILE_WIDTH * TILE_HEIGHT;

    MemoryMap memory_map;
    Tile tile(starting_address, memory_map);

    tile.init_tile();

    PixelColour_t *buffer = tile.get_pixel_buffer();

    for (int i = 0; i < buffer_size; i++) {
        EXPECT_EQ(Colour0, buffer[i]);
    }
}


TEST(Tile, GetTileRow) {
    uint16_t starting_address = 0x8000;
    uint8_t lsb = 0x55; // 0101 0101
    uint8_t msb = 0x33; // 0011 0011

    MemoryMap memory_map;
    TileRow tile_row(starting_address, memory_map);

    std::vector<PixelColour_t> row = tile_row.get_tile_row(lsb, msb);
    EXPECT_EQ(TILE_WIDTH, row.size());

    EXPECT_EQ(Colour0, row[0]);
    EXPECT_EQ(Colour1, row[1]);
    EXPECT_EQ(Colour2, row[2]);
    EXPECT_EQ(Colour3, row[3]);
    EXPECT_EQ(Colour0, row[4]);
    EXPECT_EQ(Colour1, row[5]);
    EXPECT_EQ(Colour2, row[6]);
    EXPECT_EQ(Colour3, row[7]);
}


TEST(Tile, GetTileRowFromMemory) {
    uint16_t starting_address = 0x8000;
    uint8_t lsb = 0x55; // 0101 0101
    uint8_t msb = 0x33; // 0011 0011

    MemoryMap memory_map;
    memory_map.write(starting_address, lsb);
    memory_map.write(starting_address + 1, msb);

    EXPECT_EQ(lsb, memory_map.read(starting_address));
    EXPECT_EQ(msb, memory_map.read(starting_address + 1));

    TileRow tile_row(starting_address, memory_map);

    uint8_t lsb_new = memory_map.read(starting_address);
    uint8_t msb_new = memory_map.read(starting_address + 1);
    std::vector<PixelColour_t> row = tile_row.get_tile_row(lsb_new, msb_new);
    EXPECT_EQ(TILE_WIDTH, row.size());

    EXPECT_EQ(Colour0, row[0]);
    EXPECT_EQ(Colour1, row[1]);
    EXPECT_EQ(Colour2, row[2]);
    EXPECT_EQ(Colour3, row[3]);
    EXPECT_EQ(Colour0, row[4]);
    EXPECT_EQ(Colour1, row[5]);
    EXPECT_EQ(Colour2, row[6]);
    EXPECT_EQ(Colour3, row[7]);
}


TEST(Tile, GetPixelIndexFromTile) {
    uint16_t starting_address = 0x8000;
    // 0  1  2  3  4  5  6  7
    // 8  9  10 11 12 13 14 15
    // 16 17 18 19 20 21 22 23
    // 24 25 26 27 28 29 30 31
    // 32 33 34 35 36 37 38 39
    // 40 41 42 43 44 45 46 47
    // 48 49 50 51 52 53 53 55
    // 56 57 58 59 60 61 62 63
    MemoryMap memory_map;
    Tile tile(starting_address, memory_map);

    EXPECT_EQ(0, tile.get_index(0, 0));
    EXPECT_EQ(35, tile.get_index(3, 4));
    EXPECT_EQ(63, tile.get_index(7, 7));
}


TEST(Tile, LoadTileHorizontal) {
    uint16_t starting_address = 0x8000;

    MemoryMap memory_map = setup_tile(tile_data_1, starting_address);

    Tile tile(starting_address, memory_map);

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


TEST(Tile, LoadTileVertical) {
    uint16_t starting_address = 0x8000;

    MemoryMap memory_map = setup_tile(tile_data_2, starting_address);

    Tile tile(starting_address, memory_map);

    for (int y = 0; y < TILE_HEIGHT; y++) {
        for (int x = 0; x < TILE_WIDTH; x++) {
            if (x <= 1) {
                EXPECT_EQ(Colour0, tile.get_pixel(x, y));
            }
            else if (x > 1 && x <= 3) {
                EXPECT_EQ(Colour1, tile.get_pixel(x, y));
            }
            else if (x > 3 && x <= 5) {
                EXPECT_EQ(Colour2, tile.get_pixel(x, y));
            }
            else {
                EXPECT_EQ(Colour3, tile.get_pixel(x, y));
            }
        }
    }
}
