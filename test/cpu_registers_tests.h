#include "gtest/gtest.h"


TEST(CPURegisters, InitCPURegisters) {
    CPURegisters cpu_registers;

    EXPECT_EQ(0x01, cpu_registers.read_register("A"));
    EXPECT_EQ(0xB0, cpu_registers.read_register("F"));
    EXPECT_EQ(0x01B0, cpu_registers.read_register("AF"));
    EXPECT_EQ(0x0, cpu_registers.read_register("B"));
    EXPECT_EQ(0x13, cpu_registers.read_register("C"));
    EXPECT_EQ(0x0013, cpu_registers.read_register("BC"));
    EXPECT_EQ(0x0, cpu_registers.read_register("D"));
    EXPECT_EQ(0xD8, cpu_registers.read_register("E"));
    EXPECT_EQ(0x00D8, cpu_registers.read_register("DE"));
    EXPECT_EQ(0x01, cpu_registers.read_register("H"));
    EXPECT_EQ(0x4D, cpu_registers.read_register("L"));
    EXPECT_EQ(0x014D, cpu_registers.read_register("HL"));
    EXPECT_EQ(0xFFFE, cpu_registers.read_register("SP"));
    EXPECT_EQ(0x100, cpu_registers.read_register("PC"));
}

TEST(CPURegisters, ReadInvalid8BitRegister) {
    CPURegisters cpu_registers;

    EXPECT_ANY_THROW(cpu_registers.read_register("X"));
}

TEST(CPURegisters, ReadInvalid16BitRegister) {
    CPURegisters cpu_registers;

    EXPECT_ANY_THROW(cpu_registers.read_register("AB"));
}

TEST(CPURegisters, ReadInvalidRegister) {
    CPURegisters cpu_registers;

    EXPECT_ANY_THROW(cpu_registers.read_register("ABC"));
}

TEST(CPURegisters, WriteValid8BitRegister) {
    CPURegisters cpu_registers;

    uint16_t data = 0xAB;

    EXPECT_NO_THROW(cpu_registers.write_register("A", data));
    EXPECT_EQ(data, cpu_registers.read_register("A"));
}
TEST(CPURegisters, WriteValid16BitRegister) {
    CPURegisters cpu_registers;

    uint16_t data = 0xABCD;

    EXPECT_NO_THROW(cpu_registers.write_register("AF", data));
    EXPECT_EQ(data, cpu_registers.read_register("AF"));
}

TEST(CPURegisters, WriteInvalid8BitRegister) {
    CPURegisters cpu_registers;

    uint16_t data = 0xAB;

    EXPECT_ANY_THROW(cpu_registers.write_register("X", data));
}

TEST(CPURegisters, Write8BitRegisterInvalidData) {
    CPURegisters cpu_registers;

    uint16_t data = 0xABCD;

    EXPECT_NO_THROW(cpu_registers.write_register("A", data));
    EXPECT_NE(data, cpu_registers.read_register("A"));
    EXPECT_EQ(data & 0xFF, cpu_registers.read_register("A"));
}

TEST(CPURegisters, WriteInvalid16BitRegister) {
    CPURegisters cpu_registers;

    uint16_t data = 0xABCD;

    EXPECT_ANY_THROW(cpu_registers.write_register("AB", data));
}

TEST(CPURegisters, WriteInvalidRegister) {
    CPURegisters cpu_registers;

    uint16_t data = 0xABCD;

    EXPECT_ANY_THROW(cpu_registers.write_register("ABC", data));
}