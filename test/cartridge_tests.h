#include "gtest/gtest.h"

// ROM Only
TEST(Cartridge, ROMOnlyInit) {
    std::vector<char> contents;
    ROMOnly cartridge(contents, 2);
    EXPECT_EQ(2, cartridge.get_num_rom_banks());

    EXPECT_EQ(ROM_ONLY, cartridge.get_cartridge_type());
}

TEST(Cartridge, ROMOnlyLoadFile) {
    std::string rom_file = "../../roms/DrMario.gb";

    FileParser file_parser;

    ROMOnly* cartridge = (ROMOnly*)file_parser.load_rom(rom_file);
    EXPECT_EQ(ROM_ONLY, cartridge->get_cartridge_type());
    EXPECT_EQ(2, cartridge->get_num_rom_banks());
}

TEST(Cartridge, ROMOnlyRead) {
    std::string rom_file = "../../roms/DrMario.gb";

    FileParser file_parser;

    uint16_t address0 = 0x134;
    uint8_t data0 = 0x44;
    uint16_t address1 = 0x4000;
    uint8_t data1 = 0x88;

    ROMOnly* cartridge = (ROMOnly*)file_parser.load_rom(rom_file);
    EXPECT_EQ(data0, cartridge->read(address0));
    EXPECT_EQ(data1, cartridge->read(address1));
}

TEST(Cartridge, ROMOnlyInvalidRead) {
    std::string rom_file = "../../roms/DrMario.gb";

    FileParser file_parser;

    ROMOnly* cartridge = (ROMOnly*)file_parser.load_rom(rom_file);
    EXPECT_ANY_THROW(cartridge->read(0xFFFF));
}

TEST(Cartridge, ROMOnlyWrite) {
    std::string rom_file = "../../roms/DrMario.gb";

    FileParser file_parser;

    ROMOnly* cartridge = (ROMOnly*)file_parser.load_rom(rom_file);
}

// MBC1
TEST(Cartridge, MBC1Init) {
    std::vector<char> contents;
    MBC1 cartridge(contents, 4);
    EXPECT_EQ(4, cartridge.get_num_rom_banks());

    EXPECT_EQ(ROM_MBC1, cartridge.get_cartridge_type());
}

TEST(Cartridge, MBC1LoadFile) {
    std::string rom_file = get_test_rom();

    FileParser file_parser;

    MBC1* cartridge = (MBC1*)file_parser.load_rom(rom_file);
    EXPECT_EQ(ROM_MBC1, cartridge->get_cartridge_type());
    EXPECT_EQ(4, cartridge->get_num_rom_banks());
}

TEST(Cartridge, MBC1EnableRam) {
    std::string rom_file = get_test_rom();

    FileParser file_parser;

    MBC1* cartridge = (MBC1*)file_parser.load_rom(rom_file);
    EXPECT_EQ(ROM_MBC1, cartridge->get_cartridge_type());

    EXPECT_FALSE(cartridge->is_ram_enabled());

    cartridge->write(0x0000, 0x00);
    EXPECT_FALSE(cartridge->is_ram_enabled());
    cartridge->write(0x0000, 0xFF);
    EXPECT_FALSE(cartridge->is_ram_enabled());
    cartridge->write(0x1000, 0x00);
    EXPECT_FALSE(cartridge->is_ram_enabled());
    cartridge->write(0x2000, 0x0A);
    EXPECT_FALSE(cartridge->is_ram_enabled());
    cartridge->write(0x0000, 0x0A);
    EXPECT_TRUE(cartridge->is_ram_enabled());
}

TEST(Cartridge, MBC1SelectRomBank) {
    std::string rom_file = get_test_rom();

    FileParser file_parser;

    MBC1* cartridge = (MBC1*)file_parser.load_rom(rom_file);
    EXPECT_EQ(ROM_MBC1, cartridge->get_cartridge_type());

    EXPECT_EQ(1, cartridge->get_rom_bank_number());

    cartridge->write(0x2000, 0x02);
    EXPECT_EQ(2, cartridge->get_rom_bank_number());
    cartridge->write(0x2000, 0x03);
    EXPECT_EQ(3, cartridge->get_rom_bank_number());
    cartridge->write(0x2000, 0x05);
    EXPECT_EQ(1, cartridge->get_rom_bank_number());
    cartridge->write(0x2000, 0x00);
    EXPECT_EQ(1, cartridge->get_rom_bank_number());

    cartridge->write(0x0000, 0x02);
    EXPECT_EQ(1, cartridge->get_rom_bank_number());
}

TEST(Cartridge, MBC1ReadRomBank00) {
    std::string rom_file = get_test_rom();

    FileParser file_parser;

    MBC1* cartridge = (MBC1*)file_parser.load_rom(rom_file);
    EXPECT_EQ(ROM_MBC1, cartridge->get_cartridge_type());

    EXPECT_EQ(0, cartridge->read(0x100));
    EXPECT_EQ(0x3C, cartridge->read(0x0));
    EXPECT_EQ(0x06, cartridge->read(0x3FFF));
}

TEST(Cartridge, MBC1SwitchToROMMode) {
    std::string rom_file = get_test_rom();

    FileParser file_parser;

    MBC1* cartridge = (MBC1*)file_parser.load_rom(rom_file);
    EXPECT_EQ(ROM_MBC1, cartridge->get_cartridge_type());
    EXPECT_EQ(ROM_MODE, cartridge->get_mode());

    cartridge->write(0x6000, 0x00);
    EXPECT_EQ(ROM_MODE, cartridge->get_mode());
    cartridge->write(0x7FFF, 0x00);
    EXPECT_EQ(ROM_MODE, cartridge->get_mode());
}

TEST(Cartridge, MBC1SwitchToRAMMode) {
    std::string rom_file = get_test_rom();

    FileParser file_parser;

    MBC1* cartridge = (MBC1*)file_parser.load_rom(rom_file);
    EXPECT_EQ(ROM_MBC1, cartridge->get_cartridge_type());
    EXPECT_EQ(ROM_MODE, cartridge->get_mode());

    cartridge->write(0x6000, 0x02);
    EXPECT_EQ(ROM_MODE, cartridge->get_mode());
    cartridge->write(0x6000, 0x01);
    EXPECT_EQ(RAM_MODE, cartridge->get_mode());
    cartridge->write(0x7FFF, 0x00);
    EXPECT_EQ(ROM_MODE, cartridge->get_mode());
    cartridge->write(0x7FFF, 0x01);
    EXPECT_EQ(RAM_MODE, cartridge->get_mode());
}