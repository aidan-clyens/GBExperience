#include "gtest/gtest.h"


TEST(Integration, WriteIOFromMemoryMap) {
    uint8_t bgp = 0xAB;
    
    MemoryMap memory_map;
    CPU cpu(memory_map);
    UI ui(memory_map);
    Video video(memory_map, ui);

    memory_map.write(BGP, bgp);
    EXPECT_EQ(bgp, memory_map.read(BGP));
    EXPECT_EQ(bgp, cpu.read_io_register(BGP));
    EXPECT_EQ(bgp, video.read_io_register(BGP));
}


TEST(Integration, WriteIOFromCPU) {
    uint8_t bgp = 0xAB;
    
    MemoryMap memory_map;
    CPU cpu(memory_map);
    UI ui(memory_map);
    Video video(memory_map, ui);

    cpu.write_io_register(BGP, bgp);
    EXPECT_EQ(bgp, memory_map.read(BGP));
    EXPECT_EQ(bgp, cpu.read_io_register(BGP));
    EXPECT_EQ(bgp, video.read_io_register(BGP));
}


TEST(Integration, WriteIOFromVideo) {
    uint8_t bgp = 0xAB;
    
    MemoryMap memory_map;
    CPU cpu(memory_map);
    UI ui(memory_map);
    Video video(memory_map, ui);

    video.write_io_register(BGP, bgp);
    EXPECT_EQ(bgp, memory_map.read(BGP));
    EXPECT_EQ(bgp, cpu.read_io_register(BGP));
    EXPECT_EQ(bgp, video.read_io_register(BGP));
}


TEST(Integration, WriteMemoryFromMemoryMap) {
    uint16_t address = 0xA000;
    uint8_t data = 0xAB;

    MemoryMap memory_map;
    CPU cpu(memory_map);

    cpu.write_register("HL", address);
    EXPECT_EQ(address, cpu.read_register("HL"));

    memory_map.write(address, data);
    EXPECT_EQ(data, memory_map.read(address));
    EXPECT_EQ(data, cpu.read_memory());
}


TEST(Integration, WriteMemoryFromCPU) {
    uint16_t address = 0xA000;
    uint8_t data = 0xAB;

    MemoryMap memory_map;
    CPU cpu(memory_map);

    cpu.write_register("HL", address);
    EXPECT_EQ(address, cpu.read_register("HL"));

    cpu.write_memory(data);
    EXPECT_EQ(data, memory_map.read(address));
    EXPECT_EQ(data, cpu.read_memory());
}