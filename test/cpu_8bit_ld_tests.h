#include "gtest/gtest.h"
#include "cpu/cpu.h"
#include "memory/memory_map.h"


TEST(CPU_LD, LD_R1_R2) {
    uint8_t opcode = 0x7B;
    uint8_t val_1 = 0x20;
    uint8_t val_2 = 0xAC;

    MemoryMap mem_map;
    mem_map.init_memory_map(nullptr);
    CPU cpu(mem_map);

    cpu.write_register("A", val_1);
    cpu.write_register("E", val_2);

    EXPECT_EQ(val_1, cpu.read_register("A"));
    EXPECT_EQ(val_2, cpu.read_register("E"));

    cpu.decode_op(opcode);

    EXPECT_EQ(val_2, cpu.read_register("A"));
    EXPECT_EQ(val_2, cpu.read_register("E"));
}

TEST(CPU_LD, LD_R1_HL) {
    uint8_t opcode = 0x46;
    uint8_t val_1 = 0x20;
    uint8_t val_2 = 0xAC;
    uint16_t address = 0xA0FF;

    MemoryMap mem_map;
    mem_map.init_memory_map(nullptr);
    CPU cpu(mem_map);

    cpu.write_register("B", val_1);
    cpu.write_register("HL", address);
    cpu.write_memory(val_2);

    EXPECT_EQ(val_1, cpu.read_register("B"));
    EXPECT_EQ(val_2, cpu.read_memory());

    cpu.decode_op(opcode);

    EXPECT_EQ(val_2, cpu.read_register("B"));
    EXPECT_EQ(val_2, cpu.read_memory());
}

TEST(CPU_LD, LD_HL_R2) {
    uint8_t opcode = 0x70;
    uint8_t val_1 = 0x20;
    uint8_t val_2 = 0xAC;
    uint16_t address = 0xA0FF;

    MemoryMap mem_map;
    mem_map.init_memory_map(nullptr);
    CPU cpu(mem_map);

    cpu.write_register("HL", address);
    cpu.write_memory(val_1);
    cpu.write_register("B", val_2);

    EXPECT_EQ(val_1, cpu.read_memory());
    EXPECT_EQ(val_2, cpu.read_register("B"));

    cpu.decode_op(opcode);

    EXPECT_EQ(val_2, cpu.read_memory());
    EXPECT_EQ(val_2, cpu.read_register("B"));
}

TEST(CPU_LD, LD_HL_N) {
    uint8_t opcode = 0x36;
    uint8_t val_1 = 0x20;
    uint8_t val_2 = 0xAC;
    uint16_t address = 0xA0FF;
    uint16_t PC = 0xA200;

    MemoryMap mem_map;
    mem_map.init_memory_map(nullptr);
    mem_map.write(PC, val_2);
    CPU cpu(mem_map);
    
    cpu.write_register("PC", PC);
    EXPECT_EQ(PC, cpu.read_register("PC"));

    cpu.write_register("HL", address);
    cpu.write_memory(val_1);

    EXPECT_EQ(val_1, cpu.read_memory());

    cpu.decode_op(opcode);

    EXPECT_EQ(val_2, cpu.read_memory());
}