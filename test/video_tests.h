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


TEST(Video, CheckVideoMode) {
    uint8_t stat = 0xE9; // 1110 1001

    MemoryMap mem_map;
    Video video(mem_map);

    video.write_io_register(STAT, stat);
    EXPECT_EQ(stat, video.read_io_register(STAT));

    EXPECT_EQ(VBLANK_Mode, video.get_video_mode());
}


TEST(Video, CheckCoincidenceFlag) {
    uint8_t stat = 0xE9; // 1110 1001

    MemoryMap mem_map;
    Video video(mem_map);

    video.write_io_register(STAT, stat);
    EXPECT_EQ(stat, video.read_io_register(STAT));

    EXPECT_FALSE(video.get_coincidence_flag());
}


TEST(Video, CheckCoincidenceInterruptEnabled) {
    uint8_t stat = 0xE9; // 1110 1001

    MemoryMap mem_map;
    Video video(mem_map);

    video.write_io_register(STAT, stat);
    EXPECT_EQ(stat, video.read_io_register(STAT));

    EXPECT_TRUE(video.coincidence_interrupt_enabled());
}


TEST(Video, CheckOAMInterruptEnabled) {
    uint8_t stat = 0xE9; // 1110 1001

    MemoryMap mem_map;
    Video video(mem_map);

    video.write_io_register(STAT, stat);
    EXPECT_EQ(stat, video.read_io_register(STAT));

    EXPECT_TRUE(video.oam_interrupt_enabled());
}


TEST(Video, CheckVBlankInterruptEnabled) {
    uint8_t stat = 0xE9; // 1110 1001

    MemoryMap mem_map;
    Video video(mem_map);

    video.write_io_register(STAT, stat);
    EXPECT_EQ(stat, video.read_io_register(STAT));

    EXPECT_FALSE(video.vblank_interrupt_enabled());
}


TEST(Video, CheckHBlankInterruptEnabled) {
    uint8_t stat = 0xE9; // 1110 1001

    MemoryMap mem_map;
    Video video(mem_map);

    video.write_io_register(STAT, stat);
    EXPECT_EQ(stat, video.read_io_register(STAT));

    EXPECT_TRUE(video.hblank_interrupt_enabled());
}


TEST(Video, GetScrollY) {
    int scy = 25;

    MemoryMap mem_map;
    Video video(mem_map);

    video.write_io_register(SCY, scy);
    EXPECT_EQ(scy, video.read_io_register(SCY));

    EXPECT_EQ(scy, video.get_scroll_y());
}


TEST(Video, GetScrollX) {
    int scx = 50;

    MemoryMap mem_map;
    Video video(mem_map);

    video.write_io_register(SCX, scx);
    EXPECT_EQ(scx, video.read_io_register(SCX));

    EXPECT_EQ(scx, video.get_scroll_x());
}


TEST(Video, GetLY) {
    int ly = 100;

    MemoryMap mem_map;
    Video video(mem_map);

    video.write_io_register(LY, ly);
    EXPECT_EQ(ly, video.read_io_register(LY));

    EXPECT_EQ(ly, video.get_lcd_y_coordinate());
}


TEST(Video, GetLYCompare) {
    int lyc = 150;

    MemoryMap mem_map;
    Video video(mem_map);

    video.write_io_register(LYC, lyc);
    EXPECT_EQ(lyc, video.read_io_register(LYC));

    EXPECT_EQ(lyc, video.get_lcd_y_compare());
}


TEST(Video, GetWindowY) {
    int wy = 150;

    MemoryMap mem_map;
    Video video(mem_map);

    video.write_io_register(WY, wy);
    EXPECT_EQ(wy, video.read_io_register(WY));

    EXPECT_EQ(wy, video.get_window_y());
}


TEST(Video, GetWindowX) {
    int wx = 150;

    MemoryMap mem_map;
    Video video(mem_map);

    video.write_io_register(WX, wx);
    EXPECT_EQ(wx, video.read_io_register(WX));

    EXPECT_EQ(wx, video.get_window_x());
}