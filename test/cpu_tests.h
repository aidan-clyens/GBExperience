#include "gtest/gtest.h"
#include "cpu/cpu.h"


TEST(CPU, InitCPU) {
    CPU cpu;

    EXPECT_EQ(0x0, cpu.read_register("AF"));
    EXPECT_EQ(0x0, cpu.read_register("BC"));
    EXPECT_EQ(0x0, cpu.read_register("DE"));
    EXPECT_EQ(0x0, cpu.read_register("HL"));
    EXPECT_EQ(0x0, cpu.read_register("SP"));
    EXPECT_EQ(0x100, cpu.read_register("PC"));
}

TEST(CPU, ReadInvalidRegister) {
    CPU cpu;

    EXPECT_ANY_THROW(cpu.read_register("ABC"));
}

TEST(CPU, WriteValidRegister) {
    CPU cpu;

    uint16_t data = 0xABCD;

    EXPECT_NO_THROW(cpu.write_register("AF", data));
    EXPECT_EQ(data, cpu.read_register("AF"));
}

TEST(CPU, WriteInvalidRegister) {
    CPU cpu;

    uint16_t data = 0xABCD;

    EXPECT_ANY_THROW(cpu.write_register("ABC", data));
}