#include "gtest/gtest.h"


TEST(UI, Initui) {
    UI ui;
    ui.init_ui("TEST");

    FrameBuffer buffer(LCD_WIDTH, LCD_HEIGHT);

    for (int i = 0; i < DISPLAY_TIME; i++) {
        ui.render(buffer);
    }
}


TEST(UI, SetPixel) {
    UI ui;
    ui.init_ui("TEST");

    FrameBuffer buffer(LCD_WIDTH, LCD_HEIGHT);
    buffer.set_pixel(20, 20, DARK_GRAY);

    for (int i = 0; i < DISPLAY_TIME; i++) {
        ui.render(buffer);
    }
}


TEST(UI, SetPixelAllPixels) {
    UI ui;
    ui.init_ui("TEST");

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


TEST(UI, InitInput) {
    Input input;

    EXPECT_FALSE(input.get_button_pressed(RIGHT));
    EXPECT_FALSE(input.get_button_pressed(LEFT));
    EXPECT_FALSE(input.get_button_pressed(UP));
    EXPECT_FALSE(input.get_button_pressed(DOWN));
    EXPECT_FALSE(input.get_button_pressed(A));
    EXPECT_FALSE(input.get_button_pressed(B));
    EXPECT_FALSE(input.get_button_pressed(SELECT));
    EXPECT_FALSE(input.get_button_pressed(START));
}


TEST(UI, SetButtonPressed) {
    Input input;

    input.set_button_pressed(RIGHT, true);
    EXPECT_TRUE(input.get_button_pressed(RIGHT));
}



TEST(UI, SetButtonReleased) {
    Input input;

    input.set_button_pressed(RIGHT, true);
    EXPECT_TRUE(input.get_button_pressed(RIGHT));

    input.set_button_pressed(RIGHT, false);
    EXPECT_FALSE(input.get_button_pressed(RIGHT));
}