#include "gtest/gtest.h"
#include "cpu/cpu.h"
#include "memory/memory_map.h"
#include "file_parser/file_parser.h"


TEST(CPU, InitCPU) {
    MemoryMap mem_map;
    mem_map.init_memory_map(nullptr);
    CPU cpu(mem_map);

    EXPECT_EQ(0x0, cpu.read_register("A"));
    EXPECT_EQ(0x0, cpu.read_register("F"));
    EXPECT_EQ(0x0, cpu.read_register("AF"));
    EXPECT_EQ(0x0, cpu.read_register("B"));
    EXPECT_EQ(0x0, cpu.read_register("C"));
    EXPECT_EQ(0x0, cpu.read_register("BC"));
    EXPECT_EQ(0x0, cpu.read_register("D"));
    EXPECT_EQ(0x0, cpu.read_register("E"));
    EXPECT_EQ(0x0, cpu.read_register("DE"));
    EXPECT_EQ(0x0, cpu.read_register("H"));
    EXPECT_EQ(0x0, cpu.read_register("L"));
    EXPECT_EQ(0x0, cpu.read_register("HL"));
    EXPECT_EQ(0x0, cpu.read_register("SP"));
    EXPECT_EQ(0x100, cpu.read_register("PC"));
}

TEST(CPU, FetchOpcodeFromRom) {
    int buffer_size = 16384;
    std::string rom_file = "../../roms/Tetris.gb";

    FileParser file_parser(buffer_size);
    EXPECT_TRUE(file_parser.load_rom(rom_file));

    MemoryMap mem_map;
    mem_map.init_memory_map(file_parser.get_buffer_ptr());
    CPU cpu(mem_map);

    EXPECT_EQ(0x100, cpu.read_register("PC"));
    EXPECT_EQ(file_parser.get_byte(0x100), cpu.fetch_op());
    EXPECT_EQ(file_parser.get_byte(0x101), cpu.fetch_op());
}

TEST(CPU, InitialFlagRegister) {
    MemoryMap mem_map;
    mem_map.init_memory_map(nullptr);
    CPU cpu(mem_map);

    EXPECT_EQ(0, cpu.read_flag_register(ZERO_FLAG));
    EXPECT_EQ(0, cpu.read_flag_register(SUBTRACT_FLAG));
    EXPECT_EQ(0, cpu.read_flag_register(HALF_CARRY_FLAG));
    EXPECT_EQ(0, cpu.read_flag_register(CARRY_FLAG));
}

TEST(CPU, WriteZeroFlag) {
    MemoryMap mem_map;
    mem_map.init_memory_map(nullptr);
    CPU cpu(mem_map);

    EXPECT_NO_THROW(cpu.set_flag_register(ZERO_FLAG, true));
    EXPECT_EQ(true, cpu.read_flag_register(ZERO_FLAG));

    EXPECT_NO_THROW(cpu.set_flag_register(ZERO_FLAG, false));
    EXPECT_EQ(false, cpu.read_flag_register(ZERO_FLAG));
}

TEST(CPU, WriteSubtractFlag) {
    MemoryMap mem_map;
    mem_map.init_memory_map(nullptr);
    CPU cpu(mem_map);

    EXPECT_NO_THROW(cpu.set_flag_register(SUBTRACT_FLAG, true));
    EXPECT_EQ(true, cpu.read_flag_register(SUBTRACT_FLAG));

    EXPECT_NO_THROW(cpu.set_flag_register(SUBTRACT_FLAG, false));
    EXPECT_EQ(false, cpu.read_flag_register(SUBTRACT_FLAG));
}

TEST(CPU, WriteHalfCarryFlag) {
    MemoryMap mem_map;
    mem_map.init_memory_map(nullptr);
    CPU cpu(mem_map);

    EXPECT_NO_THROW(cpu.set_flag_register(HALF_CARRY_FLAG, true));
    EXPECT_EQ(true, cpu.read_flag_register(HALF_CARRY_FLAG));

    EXPECT_NO_THROW(cpu.set_flag_register(HALF_CARRY_FLAG, false));
    EXPECT_EQ(false, cpu.read_flag_register(HALF_CARRY_FLAG));
}

TEST(CPU, WriteCarryFlag) {
    MemoryMap mem_map;
    mem_map.init_memory_map(nullptr);
    CPU cpu(mem_map);

    EXPECT_NO_THROW(cpu.set_flag_register(CARRY_FLAG, true));
    EXPECT_EQ(true, cpu.read_flag_register(CARRY_FLAG));

    EXPECT_NO_THROW(cpu.set_flag_register(CARRY_FLAG, false));
    EXPECT_EQ(false, cpu.read_flag_register(CARRY_FLAG));
}

TEST(CPU, SetMultipleFlags) {
    MemoryMap mem_map;
    mem_map.init_memory_map(nullptr);
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
    mem_map.init_memory_map(nullptr);
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
    mem_map.init_memory_map(nullptr);
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
    mem_map.init_memory_map(nullptr);
    CPU cpu(mem_map);

    cpu.write_register("BC", BC);
    EXPECT_EQ(BC, cpu.read_register("BC"));

    cpu.write_memory("BC", val);

    EXPECT_EQ(val, cpu.read_memory("BC"));
}