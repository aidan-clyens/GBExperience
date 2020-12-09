#include "gtest/gtest.h"
#include <chrono>


TEST(CPURegisters, InitCPURegisters) {
    CPURegisters cpu_registers;

    EXPECT_EQ(0x01, cpu_registers.read_register(REG_A));
    EXPECT_EQ(0xB0, cpu_registers.read_register(REG_F));
    EXPECT_EQ(0x01B0, cpu_registers.read_register(REG_AF));
    EXPECT_EQ(0x0, cpu_registers.read_register(REG_B));
    EXPECT_EQ(0x13, cpu_registers.read_register(REG_C));
    EXPECT_EQ(0x0013, cpu_registers.read_register(REG_BC));
    EXPECT_EQ(0x0, cpu_registers.read_register(REG_D));
    EXPECT_EQ(0xD8, cpu_registers.read_register(REG_E));
    EXPECT_EQ(0x00D8, cpu_registers.read_register(REG_DE));
    EXPECT_EQ(0x01, cpu_registers.read_register(REG_H));
    EXPECT_EQ(0x4D, cpu_registers.read_register(REG_L));
    EXPECT_EQ(0x014D, cpu_registers.read_register(REG_HL));
    EXPECT_EQ(0xFFFE, cpu_registers.read_register(REG_SP));
    EXPECT_EQ(0x100, cpu_registers.read_register(REG_PC));
}

TEST(CPURegisters, WriteValid8BitRegister) {
    CPURegisters cpu_registers;

    uint16_t data = 0xAB;

    EXPECT_NO_THROW(cpu_registers.write_register(REG_A, data));
    EXPECT_EQ(data, cpu_registers.read_register(REG_A));
}
TEST(CPURegisters, WriteValid16BitRegister) {
    CPURegisters cpu_registers;

    uint16_t data = 0xABCD;

    EXPECT_NO_THROW(cpu_registers.write_register(REG_BC, data));
    EXPECT_EQ(data, cpu_registers.read_register(REG_BC));
}

TEST(CPURegisters, Write8BitRegisterInvalidData) {
    CPURegisters cpu_registers;

    uint16_t data = 0xABCD;

    EXPECT_NO_THROW(cpu_registers.write_register(REG_A, data));
    EXPECT_NE(data, cpu_registers.read_register(REG_A));
    EXPECT_EQ(data & 0xFF, cpu_registers.read_register(REG_A));
}

TEST(CPURegisters, WriteToFlagRegister) {
    CPURegisters cpu_registers;

    EXPECT_EQ(0xB0, cpu_registers.read_register(REG_F));

    EXPECT_NO_THROW(cpu_registers.write_register(REG_F, 0xA0));
    EXPECT_EQ(0xA0, cpu_registers.read_register(REG_F));

    EXPECT_NO_THROW(cpu_registers.write_register(REG_F, 0xAF));
    EXPECT_EQ(0xA0, cpu_registers.read_register(REG_F));
}

TEST(CPURegisters, RegisterToString) {
    EXPECT_EQ("A", std::string(CPURegisters::to_string(REG_A)));
    EXPECT_EQ("F", std::string(CPURegisters::to_string(REG_F)));
    EXPECT_EQ("B", std::string(CPURegisters::to_string(REG_B)));
    EXPECT_EQ("C", std::string(CPURegisters::to_string(REG_C)));
    EXPECT_EQ("D", std::string(CPURegisters::to_string(REG_D)));
    EXPECT_EQ("E", std::string(CPURegisters::to_string(REG_E)));
    EXPECT_EQ("H", std::string(CPURegisters::to_string(REG_H)));
    EXPECT_EQ("L", std::string(CPURegisters::to_string(REG_L)));
    EXPECT_EQ("AF", std::string(CPURegisters::to_string(REG_AF)));
    EXPECT_EQ("BC", std::string(CPURegisters::to_string(REG_BC)));
    EXPECT_EQ("DE", std::string(CPURegisters::to_string(REG_DE)));
    EXPECT_EQ("HL", std::string(CPURegisters::to_string(REG_HL)));
    EXPECT_EQ("PC", std::string(CPURegisters::to_string(REG_PC)));
    EXPECT_EQ("SP", std::string(CPURegisters::to_string(REG_SP)));
}