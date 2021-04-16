#include "gtest/gtest.h"


TEST(UI_SFML, Initui) {
    MemoryMap mem_map;
    UI_SFML ui(mem_map);
    ui.init_display("TEST");

    FrameBuffer buffer(LCD_WIDTH, LCD_HEIGHT);

    for (int i = 0; i < DISPLAY_TIME; i++) {
        ui.render(buffer);
    }
}


TEST(UI_SFML, SetPixel) {
    MemoryMap mem_map;
    UI_SFML ui(mem_map);
    ui.init_display("TEST");

    FrameBuffer buffer(LCD_WIDTH, LCD_HEIGHT);
    buffer.set_pixel(20, 20, DARK_GRAY);

    for (int i = 0; i < DISPLAY_TIME; i++) {
        ui.render(buffer);
    }
}


TEST(UI_SFML, SetPixelAllPixels) {
    MemoryMap mem_map;
    UI_SFML ui(mem_map);
    ui.init_display("TEST");

    FrameBuffer buffer(LCD_WIDTH, LCD_HEIGHT);
    for (int y = 0; y < LCD_HEIGHT; y++) {
        for (int x = 0; x < LCD_WIDTH; x++) {
            buffer.set_pixel(x, y, DARK_GRAY);
        }
    }

    for (int i = 0; i < DISPLAY_TIME; i++) {
        ui.render(buffer);
    }
}