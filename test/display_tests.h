#include "gtest/gtest.h"


const int DISPLAY_TIME = 10;


TEST(Display, InitDisplay) {
    Display display("TEST");
    display.init_display();

    FrameBuffer buffer(LCD_WIDTH, LCD_HEIGHT);

    for (int i = 0; i < DISPLAY_TIME; i++) {
        display.render(buffer);
    }
}


TEST(Display, SetPixel) {
    Display display("TEST");
    display.init_display();

    FrameBuffer buffer(LCD_WIDTH, LCD_HEIGHT);
    buffer.set_pixel(20, 20, DARK_GRAY);

    for (int i = 0; i < DISPLAY_TIME; i++) {
        display.render(buffer);
    }
}