#include "gtest/gtest.h"
#include "video/video.h"
#include "memory/memory_map.h"


TEST(Video, ReadIORegister) {
    MemoryMap mem_map;
    Video video(mem_map);

    EXPECT_EQ(0x91, video.read_io_register(LCDC));
}


TEST(Video, WriteIORegister) {
    uint8_t data = 0xAB;

    MemoryMap mem_map;
    Video video(mem_map);

    EXPECT_NO_THROW(video.write_io_register(LCDC, data));
    EXPECT_EQ(data, video.read_io_register(LCDC));
}


TEST(Video, CheckLCDDisplayEnabled) {
    uint8_t LCDC_data = 0xEC;   // 1110 1100

    MemoryMap mem_map;
    Video video(mem_map);

    video.write_io_register(LCDC, LCDC_data);
    EXPECT_EQ(LCDC_data, video.read_io_register(LCDC));

    EXPECT_TRUE(video.lcd_display_enabled());
}


TEST(Video, CheckWindowDisplayEnabled) {
    uint8_t LCDC_data = 0xEC;   // 1110 1100

    MemoryMap mem_map;
    Video video(mem_map);

    video.write_io_register(LCDC, LCDC_data);
    EXPECT_EQ(LCDC_data, video.read_io_register(LCDC));

    EXPECT_TRUE(video.window_display_enabled());
}


TEST(Video, CheckSpriteDisplayEnabled) {
    uint8_t LCDC_data = 0xEC;   // 1110 1100

    MemoryMap mem_map;
    Video video(mem_map);

    video.write_io_register(LCDC, LCDC_data);
    EXPECT_EQ(LCDC_data, video.read_io_register(LCDC));

    EXPECT_FALSE(video.sprite_display_enabled());
}


TEST(Video, CheckBackgroundDisplayEnabled) {
    uint8_t LCDC_data = 0xEC;   // 1110 1100

    MemoryMap mem_map;
    Video video(mem_map);

    video.write_io_register(LCDC, LCDC_data);
    EXPECT_EQ(LCDC_data, video.read_io_register(LCDC));

    EXPECT_FALSE(video.background_display_enabled());
}


TEST(Video, CheckSpriteSize) {
    uint8_t LCDC_data = 0xEC;   // 1110 1100

    MemoryMap mem_map;
    Video video(mem_map);

    video.write_io_register(LCDC, LCDC_data);
    EXPECT_EQ(LCDC_data, video.read_io_register(LCDC));

    EXPECT_EQ(SPRITEx16, video.get_sprite_size());
}


TEST(Video, CheckTileDataTable) {
    uint8_t LCDC_data = 0xEC;   // 1110 1100

    MemoryMap mem_map;
    Video video(mem_map);

    video.write_io_register(LCDC, LCDC_data);
    EXPECT_EQ(LCDC_data, video.read_io_register(LCDC));

    EXPECT_EQ(TILE_DATA_SIGNED, video.get_tile_data_selected());
}


TEST(Video, CheckWindowTileMap) {
    uint8_t LCDC_data = 0xEC;   // 1110 1100

    MemoryMap mem_map;
    Video video(mem_map);

    video.write_io_register(LCDC, LCDC_data);
    EXPECT_EQ(LCDC_data, video.read_io_register(LCDC));

    EXPECT_EQ(TILE_MAP_2, video.get_window_tile_map_selected());
}


TEST(Video, CheckBackgroundTileMap) {
    uint8_t LCDC_data = 0xEC;   // 1110 1100

    MemoryMap mem_map;
    Video video(mem_map);

    video.write_io_register(LCDC, LCDC_data);
    EXPECT_EQ(LCDC_data, video.read_io_register(LCDC));

    EXPECT_EQ(TILE_MAP_2, video.get_background_tile_map_selected());
}