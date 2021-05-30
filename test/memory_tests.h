#include "gtest/gtest.h"


TEST(Memory, Init) {
    int mem_size = 1024;
    Memory mem(mem_size);

    EXPECT_EQ(mem_size, mem.get_size());
    EXPECT_TRUE(mem.init_memory());
}

TEST(Memory, WriteValid) {
    int mem_size = 1024;
    uint16_t address = 0xFF;
    uint8_t data = 0x12;

    Memory mem(mem_size);

    EXPECT_TRUE(mem.init_memory());
    EXPECT_NO_THROW(mem.write_memory(address, data));
    EXPECT_EQ(data, mem.read_memory(address));
}

TEST(Memory, WriteInvalidAddress) {
    int mem_size = 1024;
    uint16_t address = 0xFFFF;
    uint8_t data = 0x12;
    
    Memory mem(mem_size);

    EXPECT_TRUE(mem.init_memory());
    EXPECT_ANY_THROW(mem.write_memory(address, data));
}

TEST(Memory, WriteFirstAddress) {
    int mem_size = 1024;
    uint16_t address = 0x0;
    uint8_t data = 0x12;

    Memory mem(mem_size);

    EXPECT_TRUE(mem.init_memory());
    EXPECT_NO_THROW(mem.write_memory(address, data));
    EXPECT_EQ(data, mem.read_memory(address));
}

TEST(Memory, WriteLastAddress) {
    int mem_size = 1024;
    uint16_t address = mem_size - 1;
    uint8_t data = 0x12;

    Memory mem(mem_size);

    EXPECT_TRUE(mem.init_memory());
    EXPECT_NO_THROW(mem.write_memory(address, data));
    EXPECT_EQ(data, mem.read_memory(address));
}

TEST(Memory, ReadInvalidAddress) {
    int mem_size = 1024;
    uint16_t address = mem_size - 1;
    uint16_t read_address = 0xFFFF;
    uint8_t data = 0x12;

    Memory mem(mem_size);

    EXPECT_TRUE(mem.init_memory());
    EXPECT_NO_THROW(mem.write_memory(address, data));
    EXPECT_ANY_THROW(mem.read_memory(read_address));
}
