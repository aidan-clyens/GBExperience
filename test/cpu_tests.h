#include "gtest/gtest.h"
#include "cpu/cpu.h"
#include "memory/memory_map.h"


TEST(CPU, InitCPU) {
    MemoryMap mem_map;
    mem_map.init_memory_map(nullptr);
    CPU cpu(mem_map);

    EXPECT_EQ(0x0, cpu.read_register("AF"));
    EXPECT_EQ(0x0, cpu.read_register("BC"));
    EXPECT_EQ(0x0, cpu.read_register("DE"));
    EXPECT_EQ(0x0, cpu.read_register("HL"));
    EXPECT_EQ(0x0, cpu.read_register("SP"));
    EXPECT_EQ(0x100, cpu.read_register("PC"));
}

TEST(CPU, ReadInvalidRegister) {
    MemoryMap mem_map;
    mem_map.init_memory_map(nullptr);
    CPU cpu(mem_map);

    EXPECT_ANY_THROW(cpu.read_register("ABC"));
}

TEST(CPU, WriteValidRegister) {
    MemoryMap mem_map;
    mem_map.init_memory_map(nullptr);
    CPU cpu(mem_map);

    uint16_t data = 0xABCD;

    EXPECT_NO_THROW(cpu.write_register("AF", data));
    EXPECT_EQ(data, cpu.read_register("AF"));
}

TEST(CPU, WriteInvalidRegister) {
    MemoryMap mem_map;
    mem_map.init_memory_map(nullptr);
    CPU cpu(mem_map);

    uint16_t data = 0xABCD;

    EXPECT_ANY_THROW(cpu.write_register("ABC", data));
}