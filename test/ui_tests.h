#include "gtest/gtest.h"


TEST(UI, Initui) {
    UI ui;
    ui.init_display("TEST");

    FrameBuffer buffer(LCD_WIDTH, LCD_HEIGHT);

    for (int i = 0; i < DISPLAY_TIME; i++) {
        ui.render(buffer);
    }
}


TEST(UI, SetPixel) {
    UI ui;
    ui.init_display("TEST");

    FrameBuffer buffer(LCD_WIDTH, LCD_HEIGHT);
    buffer.set_pixel(20, 20, DARK_GRAY);

    for (int i = 0; i < DISPLAY_TIME; i++) {
        ui.render(buffer);
    }
}


TEST(UI, SetPixelAllPixels) {
    UI ui;
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


TEST(UI, InitInput) {
    MemoryMap mem_map;
    Input input(mem_map);

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
    MemoryMap mem_map;
    Input input(mem_map);

    input.set_button_pressed(RIGHT, true);
    EXPECT_TRUE(input.get_button_pressed(RIGHT));
}



TEST(UI, SetButtonReleased) {
    MemoryMap mem_map;
    Input input(mem_map);

    input.set_button_pressed(RIGHT, true);
    EXPECT_TRUE(input.get_button_pressed(RIGHT));

    input.set_button_pressed(RIGHT, false);
    EXPECT_FALSE(input.get_button_pressed(RIGHT));
}


TEST(UI, GetDPADToggled) {
    MemoryMap mem_map;
    Input input(mem_map);

    // Ports of P1 register are active low
    EXPECT_EQ(0xFF, mem_map.read(P1));
    EXPECT_FALSE(input.dpad_toggled());
    EXPECT_FALSE(input.buttons_toggled());

    // Set port P14 to low
    uint8_t p1 = 0xFF & ~P14;  // 1110 1111
    mem_map.write(P1, p1);
    EXPECT_TRUE(input.dpad_toggled());
    EXPECT_FALSE(input.buttons_toggled());
}


TEST(UI, GetButtonsToggled) {
    MemoryMap mem_map;
    Input input(mem_map);

    // Ports of P1 register are active low
    EXPECT_EQ(0xFF, mem_map.read(P1));
    EXPECT_FALSE(input.dpad_toggled());
    EXPECT_FALSE(input.buttons_toggled());

    // Set port P15 to low
    uint8_t p1 = 0xFF & ~P15;  // 1101 1111
    mem_map.write(P1, p1);
    EXPECT_FALSE(input.dpad_toggled());
    EXPECT_TRUE(input.buttons_toggled());
}


TEST(UI, SelectDPAD) {
    MemoryMap mem_map;
    Input input(mem_map);

    // Ports of P1 register are active low
    EXPECT_EQ(0xFF, mem_map.read(P1));

    // Enable DPAD
    uint8_t p1 = 0xFF & ~P14; // 1110 1111
    mem_map.write(P1, p1);
    EXPECT_TRUE(input.dpad_toggled());

    // Set Left button pressed
    input.set_button_pressed(LEFT, true);
    EXPECT_TRUE(input.get_button_pressed(LEFT));
    // Also set A button pressed
    input.set_button_pressed(A, true);
    EXPECT_TRUE(input.get_button_pressed(A));

    // Only P11 for the Left button should be set to low in the P1 register
    uint8_t result_p1 = 0xED;   // 1110 1101
    EXPECT_EQ(result_p1, mem_map.read(P1));
}


TEST(UI, SelectButtons) {
    MemoryMap mem_map;
    Input input(mem_map);

    // Ports of P1 register are active low
    EXPECT_EQ(0xFF, mem_map.read(P1));

    // Enable Buttons
    uint8_t p1 = 0xFF & ~P15; // 1101 1111
    mem_map.write(P1, p1);
    EXPECT_TRUE(input.buttons_toggled());

    // Set Left button pressed
    input.set_button_pressed(LEFT, true);
    EXPECT_TRUE(input.get_button_pressed(LEFT));
    // Also set B button pressed
    input.set_button_pressed(A, true);
    EXPECT_TRUE(input.get_button_pressed(A));

    // Only P10 for the A button should be set to low in the P1 register
    uint8_t result_p1 = 0xDE;   // 1101 1110
    EXPECT_EQ(result_p1, mem_map.read(P1));
}