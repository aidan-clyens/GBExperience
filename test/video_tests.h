#include "gtest/gtest.h"
#include "video/video.h"
#include "video/tile.h"
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

    EXPECT_EQ(ly, video.get_ly());
}


TEST(Video, GetLYCompare) {
    int lyc = 150;

    MemoryMap mem_map;
    Video video(mem_map);

    video.write_io_register(LYC, lyc);
    EXPECT_EQ(lyc, video.read_io_register(LYC));

    EXPECT_EQ(lyc, video.get_ly_compare());
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

    video.tick(1);

    // A V-Blank interrupt should be triggered
    EXPECT_EQ(0x01, video.read_io_register(IF));
    video.write_io_register(IF, 0x0);

    // Run a second cycle
    video.tick(1);

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

    video.tick(1);

    // A LCDC status interrupt should be triggered
    EXPECT_EQ(0x02, video.read_io_register(IF));
    video.write_io_register(IF, 0x0);

    // Run a second cycle
    video.tick(1);

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

    video.tick(1);

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


TEST(Video, GetSpritePalette0) {
    // LIGHT GRAY, BLACK, WHITE
    uint8_t obp0 = 0x70; // 0111 0000

    MemoryMap mem_map;
    Video video(mem_map);

    video.write_io_register(OBP0, obp0);
    EXPECT_EQ(obp0, video.read_io_register(OBP0));

    Palette palette = video.get_sprite_palette_0();
    EXPECT_EQ(WHITE, palette.colour1);
    EXPECT_EQ(BLACK, palette.colour2);
    EXPECT_EQ(LIGHT_GRAY, palette.colour3);
}


TEST(Video, GetSpritePalette1) {
    // LIGHT GRAY, BLACK, WHITE
    uint8_t obp1 = 0x70; // 0111 0000

    MemoryMap mem_map;
    Video video(mem_map);

    video.write_io_register(OBP1, obp1);
    EXPECT_EQ(obp1, video.read_io_register(OBP1));

    Palette palette = video.get_sprite_palette_1();
    EXPECT_EQ(WHITE, palette.colour1);
    EXPECT_EQ(BLACK, palette.colour2);
    EXPECT_EQ(LIGHT_GRAY, palette.colour3);
}


TEST(Video, InitTile) {
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


TEST(Video, GetTileRow) {
    uint16_t starting_address = 0x8000;
    uint8_t lsb = 0x55; // 0101 0101
    uint8_t msb = 0x33; // 0011 0011

    MemoryMap memory_map;
    Tile tile(starting_address, memory_map);

    std::vector<PixelColour_t> row = tile.get_tile_row(lsb, msb);
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


TEST(Video, GetTileRowFromMemory) {
    uint16_t starting_address = 0x8000;
    uint8_t lsb = 0x55; // 0101 0101
    uint8_t msb = 0x33; // 0011 0011

    MemoryMap memory_map;
    memory_map.write(starting_address, lsb);
    memory_map.write(starting_address + 1, msb);

    EXPECT_EQ(lsb, memory_map.read(starting_address));
    EXPECT_EQ(msb, memory_map.read(starting_address + 1));

    Tile tile(starting_address, memory_map);

    uint8_t lsb_new = memory_map.read(starting_address);
    uint8_t msb_new = memory_map.read(starting_address + 1);
    std::vector<PixelColour_t> row = tile.get_tile_row(lsb_new, msb_new);
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


TEST(Video, GetPixelIndexFromTile) {
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


TEST(Video, LoadTile) {
    uint16_t starting_address = 0x8000;

    MemoryMap memory_map;
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
        memory_map.write(starting_address + i, tile_data[i]);
        EXPECT_EQ(tile_data[i], memory_map.read(starting_address + i));
    }

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


TEST(Video, TestScanlineTiming) {
    int scanline_cycles = HBLANK_CLOCKS + OAM_CLOCKS + DATA_TRANSFER_CLOCKS;

    MemoryMap mem_map;
    Video video(mem_map);

    // Initialize in H-Blank mode
    video.set_video_mode(HBLANK_Mode);
    EXPECT_EQ(HBLANK_Mode, video.get_video_mode());

    // Check cycle timing for each scanline
    for (int i = 0; i < scanline_cycles; i++) {
        video.tick(1);

        if (i < HBLANK_CLOCKS) {
            EXPECT_EQ(HBLANK_Mode, video.get_video_mode());
        }
        else if (i > HBLANK_CLOCKS && i < HBLANK_CLOCKS + OAM_CLOCKS) {
            EXPECT_EQ(OAM_Mode, video.get_video_mode());
        }
        else if (i >= HBLANK_CLOCKS + OAM_CLOCKS && i < scanline_cycles){
            EXPECT_EQ(Data_Transfer_Mode, video.get_video_mode());
        }
    }
}


TEST(Video, TestVideoModeTiming) {
    int scanline_cycles = HBLANK_CLOCKS + OAM_CLOCKS + DATA_TRANSFER_CLOCKS;
    int total_scanlines = 144;

    MemoryMap mem_map;
    Video video(mem_map);

    // Initialize in H-Blank mode
    video.set_video_mode(HBLANK_Mode);
    EXPECT_EQ(HBLANK_Mode, video.get_video_mode());

    for (int j = 0; j < total_scanlines; j++) {
        // Check cycle timing for each scanline
        for (int i = 0; i < scanline_cycles; i++) {
            video.tick(1);

            if (i < HBLANK_CLOCKS) {
                EXPECT_EQ(HBLANK_Mode, video.get_video_mode());
            }
            else if (i > HBLANK_CLOCKS && i < HBLANK_CLOCKS + OAM_CLOCKS) {
                EXPECT_EQ(OAM_Mode, video.get_video_mode());
            }
            else if (i >= HBLANK_CLOCKS + OAM_CLOCKS && i < scanline_cycles){
                EXPECT_EQ(Data_Transfer_Mode, video.get_video_mode());
            }
        }
    }

    for (int i = 0; i < HBLANK_CLOCKS; i++) {
        video.tick(1);

        EXPECT_EQ(HBLANK_Mode, video.get_video_mode());
    }

    for (int i = 0; i < VBLANK_CLOCKS; i++) {
        video.tick(1);

        EXPECT_EQ(VBLANK_Mode, video.get_video_mode());
    }

    video.tick(1);
    EXPECT_EQ(OAM_Mode, video.get_video_mode());
}
