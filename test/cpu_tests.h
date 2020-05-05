#include "gtest/gtest.h"


TEST(CPU, InitCPU) {
    MemoryMap mem_map;
    
    CPU cpu(mem_map);
}

TEST(CPU, FetchOpcodeFromRom) {
    std::string rom_file = "../../roms/Tetris.gb";

    FileParser file_parser;
    EXPECT_TRUE(file_parser.load_rom(rom_file));

    MemoryMap mem_map;
    mem_map. load_rom(file_parser.get_buffer_data());
    CPU cpu(mem_map);

    EXPECT_EQ(0x100, cpu.read_register("PC"));
    EXPECT_EQ(file_parser.get_byte(0x100), cpu.fetch_op());
    EXPECT_EQ(file_parser.get_byte(0x101), cpu.fetch_op());
}

TEST(CPU, InitialFlagRegister) {
    MemoryMap mem_map;
    
    CPU cpu(mem_map);

    EXPECT_TRUE(cpu.read_flag_register(ZERO_FLAG));
    EXPECT_FALSE(cpu.read_flag_register(SUBTRACT_FLAG));
    EXPECT_TRUE(cpu.read_flag_register(HALF_CARRY_FLAG));
    EXPECT_TRUE(cpu.read_flag_register(CARRY_FLAG));
}

TEST(CPU, WriteZeroFlag) {
    MemoryMap mem_map;
    
    CPU cpu(mem_map);

    EXPECT_NO_THROW(cpu.set_flag_register(ZERO_FLAG, true));
    EXPECT_EQ(true, cpu.read_flag_register(ZERO_FLAG));

    EXPECT_NO_THROW(cpu.set_flag_register(ZERO_FLAG, false));
    EXPECT_EQ(false, cpu.read_flag_register(ZERO_FLAG));
}

TEST(CPU, WriteSubtractFlag) {
    MemoryMap mem_map;
    
    CPU cpu(mem_map);

    EXPECT_NO_THROW(cpu.set_flag_register(SUBTRACT_FLAG, true));
    EXPECT_EQ(true, cpu.read_flag_register(SUBTRACT_FLAG));

    EXPECT_NO_THROW(cpu.set_flag_register(SUBTRACT_FLAG, false));
    EXPECT_EQ(false, cpu.read_flag_register(SUBTRACT_FLAG));
}

TEST(CPU, WriteHalfCarryFlag) {
    MemoryMap mem_map;
    
    CPU cpu(mem_map);

    EXPECT_NO_THROW(cpu.set_flag_register(HALF_CARRY_FLAG, true));
    EXPECT_EQ(true, cpu.read_flag_register(HALF_CARRY_FLAG));

    EXPECT_NO_THROW(cpu.set_flag_register(HALF_CARRY_FLAG, false));
    EXPECT_EQ(false, cpu.read_flag_register(HALF_CARRY_FLAG));
}

TEST(CPU, WriteCarryFlag) {
    MemoryMap mem_map;
    
    CPU cpu(mem_map);

    EXPECT_NO_THROW(cpu.set_flag_register(CARRY_FLAG, true));
    EXPECT_EQ(true, cpu.read_flag_register(CARRY_FLAG));

    EXPECT_NO_THROW(cpu.set_flag_register(CARRY_FLAG, false));
    EXPECT_EQ(false, cpu.read_flag_register(CARRY_FLAG));
}

TEST(CPU, SetMultipleFlags) {
    MemoryMap mem_map;
    
    CPU cpu(mem_map);

    EXPECT_NO_THROW(cpu.set_flag_register(SUBTRACT_FLAG, true));
    EXPECT_NO_THROW(cpu.set_flag_register(CARRY_FLAG, true));
    
    EXPECT_EQ(true, cpu.read_flag_register(SUBTRACT_FLAG));
    EXPECT_EQ(true, cpu.read_flag_register(CARRY_FLAG));

    EXPECT_NO_THROW(cpu.set_flag_register(SUBTRACT_FLAG, false));

    EXPECT_EQ(false, cpu.read_flag_register(SUBTRACT_FLAG));
    EXPECT_EQ(true, cpu.read_flag_register(CARRY_FLAG));
}

TEST(CPU, ResetFlagRegister) {
    MemoryMap mem_map;
    
    CPU cpu(mem_map);

    EXPECT_NO_THROW(cpu.set_flag_register(ZERO_FLAG, true));
    EXPECT_NO_THROW(cpu.set_flag_register(SUBTRACT_FLAG, true));
    EXPECT_NO_THROW(cpu.set_flag_register(HALF_CARRY_FLAG, true));
    EXPECT_NO_THROW(cpu.set_flag_register(CARRY_FLAG, true));

    cpu.reset_flag_register();

    EXPECT_EQ(0, cpu.read_flag_register(ZERO_FLAG));
    EXPECT_EQ(0, cpu.read_flag_register(SUBTRACT_FLAG));
    EXPECT_EQ(0, cpu.read_flag_register(HALF_CARRY_FLAG));
    EXPECT_EQ(0, cpu.read_flag_register(CARRY_FLAG));
}

TEST(CPU, WriteMemoryHL) {
    uint16_t HL = 0xA000;
    uint8_t val = 0xAB;
    
    MemoryMap mem_map;
    
    CPU cpu(mem_map);

    cpu.write_register("HL", HL);
    EXPECT_EQ(HL, cpu.read_register("HL"));

    cpu.write_memory(val);

    EXPECT_EQ(val, cpu.read_memory());
    EXPECT_EQ(val, cpu.read_memory("HL"));
}

TEST(CPU, WriteMemory) {
    uint16_t BC = 0xA000;
    uint8_t val = 0xAB;
    
    MemoryMap mem_map;
    
    CPU cpu(mem_map);

    cpu.write_register("BC", BC);
    EXPECT_EQ(BC, cpu.read_register("BC"));

    cpu.write_memory("BC", val);

    EXPECT_EQ(val, cpu.read_memory("BC"));
}