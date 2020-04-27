#include "gtest/gtest.h"
#include "cpu/cpu.h"


TEST(Interrupts, InterruptsEnabledByDefault) {
    MemoryMap mem_map;
    CPU cpu(mem_map);

    EXPECT_TRUE(cpu.interrupts_enabled());
}


TEST(Interrupts, ReadInterruptEnableRegister) {
    MemoryMap mem_map;
    CPU cpu(mem_map);

    EXPECT_EQ(0x1F, cpu.read_io_register(IE));
}


TEST(Interrupts, ReadInterruptFlagRegister) {
    MemoryMap mem_map;
    CPU cpu(mem_map);

    EXPECT_EQ(0x0, cpu.read_io_register(IF));
}

TEST(Interrupts, WriteInterruptEnableRegister) {
    uint8_t value = 0xFF;

    MemoryMap mem_map;
    CPU cpu(mem_map);

    cpu.write_io_register(IE, value);
    EXPECT_EQ(value, cpu.read_io_register(IE));
}


TEST(Interrupts, WriteInterruptFlagRegister) {
    uint8_t value = 0xFF;

    MemoryMap mem_map;
    CPU cpu(mem_map);

    cpu.write_io_register(IF, value);
    EXPECT_EQ(value, cpu.read_io_register(IF));
}

TEST(Interrupts, SetVBlankEnableBit) {
    MemoryMap mem_map;
    CPU cpu(mem_map);

    cpu.write_io_register(IE, 0x0);
    EXPECT_EQ(0x0, cpu.read_io_register(IE));

    EXPECT_FALSE(cpu.get_interrupt_enable_bit(VBLANK));

    cpu.set_interrupt_enable_bit(VBLANK, true);
    EXPECT_TRUE(cpu.get_interrupt_enable_bit(VBLANK));
    EXPECT_FALSE(cpu.get_interrupt_enable_bit(JOYPAD));
}

TEST(Interrupts, SetVBlankFlagBit) {
    MemoryMap mem_map;
    CPU cpu(mem_map);

    cpu.write_io_register(IF, 0x0);
    EXPECT_EQ(0x0, cpu.read_io_register(IF));

    EXPECT_FALSE(cpu.get_interrupt_flag_bit(VBLANK));

    cpu.set_interrupt_flag_bit(VBLANK, true);
    EXPECT_TRUE(cpu.get_interrupt_flag_bit(VBLANK));
    EXPECT_FALSE(cpu.get_interrupt_flag_bit(JOYPAD));
}

TEST(Interrupts, SetMultipleEnableBits) {
    MemoryMap mem_map;
    CPU cpu(mem_map);

    cpu.write_io_register(IE, 0x0);
    EXPECT_EQ(0x0, cpu.read_io_register(IE));

    EXPECT_FALSE(cpu.get_interrupt_enable_bit(VBLANK));
    EXPECT_FALSE(cpu.get_interrupt_enable_bit(JOYPAD));

    cpu.set_interrupt_enable_bit(VBLANK, true);
    cpu.set_interrupt_enable_bit(JOYPAD, true);
    EXPECT_TRUE(cpu.get_interrupt_enable_bit(VBLANK));
    EXPECT_TRUE(cpu.get_interrupt_enable_bit(JOYPAD));
    EXPECT_FALSE(cpu.get_interrupt_enable_bit(TIMER));
}

TEST(Interrupts, SetMultipleFlagBits) {
    MemoryMap mem_map;
    CPU cpu(mem_map);

    cpu.write_io_register(IF, 0x0);
    EXPECT_EQ(0x0, cpu.read_io_register(IF));

    EXPECT_FALSE(cpu.get_interrupt_flag_bit(VBLANK));
    EXPECT_FALSE(cpu.get_interrupt_flag_bit(JOYPAD));

    cpu.set_interrupt_flag_bit(VBLANK, true);
    cpu.set_interrupt_flag_bit(JOYPAD, true);
    EXPECT_TRUE(cpu.get_interrupt_flag_bit(VBLANK));
    EXPECT_TRUE(cpu.get_interrupt_flag_bit(JOYPAD));
    EXPECT_FALSE(cpu.get_interrupt_flag_bit(TIMER));
}

TEST(Interrupts, ResetVBlankEnableBit) {
    MemoryMap mem_map;
    CPU cpu(mem_map);

    cpu.write_io_register(IE, 0x1F);
    EXPECT_EQ(0x1F, cpu.read_io_register(IE));

    EXPECT_TRUE(cpu.get_interrupt_enable_bit(VBLANK));

    cpu.set_interrupt_enable_bit(VBLANK, false);
    EXPECT_FALSE(cpu.get_interrupt_enable_bit(VBLANK));
    EXPECT_TRUE(cpu.get_interrupt_enable_bit(JOYPAD));
}

TEST(Interrupts, ResetVBlankFlagBit) {
    MemoryMap mem_map;
    CPU cpu(mem_map);

    cpu.write_io_register(IF, 0x1F);
    EXPECT_EQ(0x1F, cpu.read_io_register(IF));

    EXPECT_TRUE(cpu.get_interrupt_flag_bit(VBLANK));

    cpu.set_interrupt_flag_bit(VBLANK, false);
    EXPECT_FALSE(cpu.get_interrupt_flag_bit(VBLANK));
    EXPECT_TRUE(cpu.get_interrupt_flag_bit(JOYPAD));
}