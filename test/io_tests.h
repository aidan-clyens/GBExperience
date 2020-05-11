#include "gtest/gtest.h"


TEST(IO, ReadIO) {
    IO registers;

    EXPECT_EQ(0x0, registers.read(DIV));
}

TEST(IO, WriteIO) {
    uint8_t data = 0xAB;

    IO registers;

    EXPECT_NO_THROW(registers.write(DIV, data));
    EXPECT_EQ(data, registers.read(DIV));
}

TEST(IO, WriteLY) {
    uint8_t data = 0xAB;

    IO registers;

    // LY should reset when written to
    EXPECT_NO_THROW(registers.write(LY, data));
    EXPECT_EQ(0, registers.read(LY));
}

TEST(IO, IncrementLY) {
    IO registers;

    EXPECT_EQ(0x0, registers.read(LY));

    registers.increment_counter(LY);

    EXPECT_EQ(0x1, registers.read(LY));
}


TEST(IO, IncrementDIV) {
    IO registers;

    EXPECT_EQ(0x0, registers.read(DIV));

    registers.increment_counter(DIV);

    EXPECT_EQ(0x1, registers.read(DIV));
}



TEST(IO, IncrementInvalidRegister) {
    IO registers;

    EXPECT_EQ(0xFF, registers.read(P1));

    EXPECT_ANY_THROW(registers.increment_counter(P1));
}


TEST(IO, GetDPADToggled) {
    uint8_t p1 = 0xE0;  // 1110 0000

    IO registers;
    registers.write(P1, p1);

    EXPECT_TRUE(registers.dpad_toggled());
    EXPECT_FALSE(registers.buttons_toggled());
}


TEST(IO, GetButtonsToggled) {
    uint8_t p1 = 0xD0;  // 1101 0000

    IO registers;
    registers.write(P1, p1);

    EXPECT_FALSE(registers.dpad_toggled());
    EXPECT_TRUE(registers.buttons_toggled());
}


TEST(IO, SetButtonPressedDefault) {
    uint8_t result = 0xF;   // 1111

    IO registers;

    EXPECT_EQ(result, registers.get_input());
}


TEST(IO, SetButtonPressedNoToggle) {
    uint8_t result = 0xF;   // 1111

    IO registers;

    registers.set_button_pressed(RIGHT, true);

    EXPECT_EQ(result, registers.get_input());
}


TEST(IO, SetButtonPressedDPAD) {
    uint8_t result = 0xE;   // 1110
    uint8_t p1 = 0xE0;      // 1110 0000

    IO registers;
    registers.write(P1, p1);

    registers.set_button_pressed(B, true);
    registers.set_button_pressed(RIGHT, true);
    EXPECT_TRUE(registers.dpad_toggled());
    EXPECT_EQ(result, registers.get_input());
}


TEST(IO, SetButtonPressedButtons) {
    uint8_t result = 0xD;   // 1101
    uint8_t p1 = 0xD0;      // 1101 0000

    IO registers;
    registers.write(P1, p1);

    registers.set_button_pressed(B, true);
    registers.set_button_pressed(RIGHT, true);
    EXPECT_TRUE(registers.buttons_toggled());
    EXPECT_EQ(result, registers.get_input());
}


TEST(IO, ReadP1) {
    uint8_t result = 0xDD;  // 1101 1101
    uint8_t p1 = 0xD0;      // 1101 0000

    IO registers;
    registers.write(P1, p1);

    registers.set_button_pressed(B, true);
    registers.set_button_pressed(RIGHT, true);
    EXPECT_TRUE(registers.buttons_toggled());
    EXPECT_EQ((result & 0xF), registers.get_input());

    EXPECT_EQ(result, registers.read(P1));
}