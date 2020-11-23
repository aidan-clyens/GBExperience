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

    uint16_t address = 0x134;
    uint8_t data = 0x44;

    ROMOnly* cartridge = (ROMOnly*)file_parser.load_rom(rom_file);
    EXPECT_EQ(data, cartridge->read(address));
}

TEST(Cartridge, ROMOnlyInvalidRead) {
    std::string rom_file = "../../roms/DrMario.gb";

    FileParser file_parser;

    ROMOnly* cartridge = (ROMOnly*)file_parser.load_rom(rom_file);
    EXPECT_ANY_THROW(cartridge->read(0xFFFF));
}
