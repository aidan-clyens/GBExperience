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


TEST(Video, SetVideoMode) {
    MemoryMap mem_map;
    Video video(mem_map);

    video.set_video_mode(Data_Transfer_Mode);
    EXPECT_EQ(Data_Transfer_Mode, video.get_video_mode());
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


TEST(Video, TriggerVBlankInterrupt) {
    uint8_t stat = 0x11;    // 0001 0001

    MemoryMap mem_map;
    Video video(mem_map);

    // Initialize in OAM mode
    video.set_video_mode(OAM_Mode);
    EXPECT_EQ(OAM_Mode, video.get_video_mode());

    // Change to V-Blank mode
    video.write_io_register(STAT, stat);
    EXPECT_EQ(VBLANK_Mode, video.get_video_mode());
    EXPECT_TRUE(video.vblank_interrupt_enabled());
    
    // No interrupts should be triggered yet
    EXPECT_EQ(0x0, video.read_io_register(IF));

    video.tick();

    // A V-Blank interrupt should be triggered
    EXPECT_EQ(0x01, video.read_io_register(IF));
    video.write_io_register(IF, 0x0);

    // Run a second cycle
    video.tick();

    // Interrupt should only be triggered at the start of the V-Blank period
    EXPECT_EQ(0x0, video.read_io_register(IF));
}


TEST(Video, TriggerLCDCStatusOAMInterrupt) {
    uint8_t stat = 0x22; // 0010 0010

    MemoryMap mem_map;
    Video video(mem_map);

    // Initialize in V-Blank mode
    video.set_video_mode(VBLANK_Mode);
    EXPECT_EQ(VBLANK_Mode, video.get_video_mode());

    // Change to OAM mode
    video.write_io_register(STAT, stat);
    EXPECT_EQ(OAM_Mode, video.get_video_mode());
    EXPECT_TRUE(video.oam_interrupt_enabled());

    // No interrupts should be triggered yet
    EXPECT_EQ(0x0, video.read_io_register(IF));

    video.tick();

    // A LCDC status interrupt should be triggered
    EXPECT_EQ(0x02, video.read_io_register(IF));
    video.write_io_register(IF, 0x0);

    // Run a second cycle
    video.tick();

    // Interrupt should only be triggered at the start of the OAM period
    EXPECT_EQ(0x0, video.read_io_register(IF));
}


TEST(Video, TriggerLCDCStatusCoincidenceInterrupt) {
    uint8_t stat = 0x46; // 0100 0110

    MemoryMap mem_map;
    Video video(mem_map);

    // Set coincidence flag to true
    video.write_io_register(STAT, stat);
    EXPECT_EQ(stat, video.read_io_register(STAT));
    EXPECT_TRUE(video.get_coincidence_flag());
    EXPECT_TRUE(video.coincidence_interrupt_enabled());

    // No interrupts should be triggered yet
    EXPECT_EQ(0x0, video.read_io_register(IF));

    video.tick();

    // A LCDC status interrupt should be triggered
    EXPECT_EQ(0x02, video.read_io_register(IF));
}


TEST(Video, GetBackgroundPalette) {
    // LIGHT GRAY, BLACK, WHITE, DARK GRAY
    uint8_t bgp = 0x72; // 0111 0010

    MemoryMap mem_map;
    Video video(mem_map);

    video.write_io_register(BGP, bgp);
    EXPECT_EQ(bgp, video.read_io_register(BGP));

    Palette palette = video.get_background_palette();
    EXPECT_EQ(DARK_GRAY, palette.colour0);
    EXPECT_EQ(WHITE, palette.colour1);
    EXPECT_EQ(BLACK, palette.colour2);
    EXPECT_EQ(LIGHT_GRAY, palette.colour3);
}