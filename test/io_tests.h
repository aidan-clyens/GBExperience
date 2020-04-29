#include "gtest/gtest.h"
#include "memory/io.h"


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