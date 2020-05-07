#include "gtest/gtest.h"


TEST(Display, InitDisplay) {
    Display display;
    display.init_display("TEST");

    FrameBuffer buffer(LCD_WIDTH, LCD_HEIGHT);

    for (int i = 0; i < DISPLAY_TIME; i++) {
        display.render(buffer);
    }
}


TEST(Display, SetPixel) {
    Display display;
    display.init_display("TEST");

    FrameBuffer buffer(LCD_WIDTH, LCD_HEIGHT);
    buffer.set_pixel(20, 20, DARK_GRAY);

    for (int i = 0; i < DISPLAY_TIME; i++) {
        display.render(buffer);
    }
}


TEST(Display, SetPixelAllPixels) {
    Display display;
    display.init_display("TEST");

    FrameBuffer buffer(LCD_WIDTH, LCD_HEIGHT);
    for (int y = 0; y < LCD_HEIGHT; y++) {
        for (int x = 0; x < LCD_WIDTH; x++) {
            buffer.set_pixel(x, y, DARK_GRAY);
        }
    }

    for (int i = 0; i < DISPLAY_TIME; i++) {
        display.render(buffer);
    }
}