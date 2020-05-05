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