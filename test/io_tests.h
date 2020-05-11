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
    uint8_t p1 = 0xEF;  // 1110 1111

    IO registers;
    registers.write(P1, p1);

    EXPECT_TRUE(registers.dpad_toggled());
    EXPECT_FALSE(registers.buttons_toggled());
}


TEST(IO, GetButtonsToggled) {
    uint8_t p1 = 0xDF;  // 1101 1111

    IO registers;
    registers.write(P1, p1);

    EXPECT_FALSE(registers.dpad_toggled());
    EXPECT_TRUE(registers.buttons_toggled());
}