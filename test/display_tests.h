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