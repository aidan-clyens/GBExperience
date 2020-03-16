#include "gtest/gtest.h"
#include "cpu/cpu.h"

// RST 10
TEST(CPU_RST, RST) {
    uint8_t opcode = 0xD7;
    uint16_t PC = 0xA000;
    uint16_t SP = 0xC000;

    MemoryMap mem_map;
    mem_map.init_memory_map(nullptr);
    CPU cpu(mem_map);

    cpu.write_register("PC", PC);
    cpu.write_register("SP", SP);
    EXPECT_EQ(PC, cpu.read_register("PC"));
    EXPECT_EQ(SP, cpu.read_register("SP"));

    cpu.decode_op(opcode);

    EXPECT_EQ(SP - 2, cpu.read_register("SP"));

    cpu.write_register("DE", SP - 1);
    cpu.write_register("HL", SP - 2);

    EXPECT_EQ(PC & 0xFF, cpu.read_memory("DE"));
    EXPECT_EQ(PC >> 8, cpu.read_memory("HL"));
}