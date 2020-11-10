#include "gtest/gtest.h"


TEST(MemoryMap, Init) {
    MemoryMap mem_map;    
}

TEST(MemoryMap, GetIndexes) {
    MemoryMap mem_map;     

    uint16_t addresses[12] = {
        0x1000,
        0x5000,
        0x9000,
        0xB000,
        0xD000,
        0xF000,
        0xFE0A,
        0xFEFF,
        0xFF0F,
        0xFF50,
        0xFF90,
        0xFFFF
    };

    for (int i=0; i<12; i++) {
        EXPECT_EQ(i, mem_map.get_index(addresses[i]));
    }
}

TEST(MemoryMap, GetIndexesBoundaries) {
    MemoryMap mem_map;

    uint16_t addresses[12] = {
        0x0000,
        0x4000,
        0x8000,
        0xA000,
        0xC000,
        0xE000,
        0xFE00,
        0xFEA0,
        0xFF00,
        0xFF4C,
        0xFF80,
        0xFFFF
    };

    for (int i=0; i<12; i++) {
        EXPECT_EQ(i, mem_map.get_index(addresses[i]));
    }
}

TEST(MemoryMap, WriteSwitchableRAM) {
    MemoryMap mem_map;

    uint16_t address = 0xA100;
    uint16_t mem_address = address - 0xA000;
    uint8_t data = 0x1F;

    EXPECT_EQ(3, mem_map.get_index(address));
    EXPECT_NO_THROW(mem_map.write(address, data));
    EXPECT_EQ(mem_address, mem_map.write(address, data));
    EXPECT_EQ(data, mem_map.read(address));
}

TEST(MemoryMap, WriteInternalRAM) {
    MemoryMap mem_map;

    uint16_t address =0xC100;
    uint16_t mem_address = address - 0xC000;
    uint8_t data = 0x1F;

    EXPECT_EQ(4, mem_map.get_index(address));
    EXPECT_NO_THROW(mem_map.write(address, data));
    EXPECT_EQ(mem_address, mem_map.write(address, data));
    EXPECT_EQ(data, mem_map.read(address));
}

TEST(MemoryMap, ReadRom) {
    std::string rom_file = "../../roms/DrMario.gb";

    FileParser file_parser;

    EXPECT_TRUE(file_parser.load_rom(rom_file));

    MemoryMap mem_map;
    EXPECT_NO_THROW(mem_map.load_rom(file_parser.get_buffer_data()));

    uint16_t address_1 = 0x134;
    uint8_t data_1 = 0x44;

    EXPECT_EQ(0, mem_map.get_index(address_1));
    EXPECT_EQ(data_1, mem_map.read(address_1));
}


TEST(MemoryMap, LoadRom) {
    std::string rom_file = "../../roms/DrMario.gb";

    FileParser file_parser;
    EXPECT_TRUE(file_parser.load_rom(rom_file));

    std::vector<uint8_t> buffer_data = file_parser.get_buffer_data();
    std::cout << file_parser.get_buffer_size() / 2 << std::endl;

    MemoryMap mem_map;
    EXPECT_NO_THROW(mem_map.load_rom(buffer_data));

    for (int i = 0; i < buffer_data.size(); i++) {
        EXPECT_EQ(buffer_data[i], mem_map.read((uint16_t)i));
    }
}

TEST(MemoryMap, WriteToRom) {
    std::string rom_file = "../../roms/DrMario.gb";

    FileParser file_parser;

    EXPECT_TRUE(file_parser.load_rom(rom_file));

    MemoryMap mem_map;
    EXPECT_NO_THROW(mem_map.load_rom(file_parser.get_buffer_data()));

    uint16_t address_1 = 0x134;
    uint8_t data_1 = 0xFF;

    EXPECT_EQ(0, mem_map.get_index(address_1));
    EXPECT_ANY_THROW(mem_map.write(address_1, data_1));
}

TEST(MemoryMap, ReadFromUnimplementedSpace) {
    MemoryMap mem_map;

    uint16_t address = 0xFEAF;

    EXPECT_EQ(7, mem_map.get_index(address));
    EXPECT_ANY_THROW(mem_map.read(address));
}


TEST(MemoryMap, WriteHighRAM) {
    MemoryMap mem_map;

    uint16_t address = 0xFF90;
    uint16_t mem_address = address - 0xFF80;
    uint8_t data = 0x1F;

    EXPECT_EQ(10, mem_map.get_index(address));
    EXPECT_NO_THROW(mem_map.write(address, data));
    EXPECT_EQ(mem_address, mem_map.write(address, data));
    EXPECT_EQ(data, mem_map.read(address));
}


TEST(MemoryMap, WriteToVRAM) {
    MemoryMap mem_map;

    uint16_t address = 0x8000;
    uint8_t data = 0x1F;

    EXPECT_EQ(2, mem_map.get_index(address));
    EXPECT_NO_THROW(mem_map.write(address, data));
    EXPECT_EQ(data, mem_map.read(address));
}


TEST(MemoryMap, WriteEchoRAM) {
    uint16_t echo_ram_address = 0xE100;
    uint16_t ram_address = echo_ram_address - 0x2000;
    uint8_t data = 0xAB;

    MemoryMap mem_map;

    mem_map.write(echo_ram_address, data);

    EXPECT_EQ(data, mem_map.read(echo_ram_address));
    EXPECT_EQ(data, mem_map.read(ram_address));
}


TEST(MemoryMap, IncrementIOCounter) {
    MemoryMap mem_map;

    EXPECT_EQ(0x0, mem_map.read(DIV));

    mem_map.increment_io_counter(DIV);

    EXPECT_EQ(0x1, mem_map.read(DIV));
}