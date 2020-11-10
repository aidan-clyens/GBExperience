#include "gtest/gtest.h"


TEST(FileParser, DefaultConstructor) {
    FileParser file_parser;

    EXPECT_EQ(0, file_parser.get_buffer_size());
}

TEST(FileParser, LoadRomValidFile) {
    std::string rom_file = "../../roms/DrMario.gb";

    FileParser file_parser;

    EXPECT_NO_THROW(file_parser.load_rom(rom_file));
    EXPECT_EQ(BUFFER_SIZE, file_parser.get_buffer_size());
}

TEST(FileParser, LoadRomInvalidFile) {
    std::string rom_file = "../../roms/wrong.gb";

    FileParser file_parser;

    EXPECT_ANY_THROW(file_parser.load_rom(rom_file));
    EXPECT_EQ(0, file_parser.get_buffer_size());
}

TEST(FileParser, GetByteOutOfRange) {
    std::string rom_file = "../../roms/DrMario.gb";

    FileParser file_parser;

    EXPECT_NO_THROW(file_parser.load_rom(rom_file));
    EXPECT_ANY_THROW(file_parser.get_byte(BUFFER_SIZE + 10));
}

TEST(FileParser, GetROMSize) {
    std::string rom_file = "../../roms/DrMario.gb";
    uint8_t rom_size = 0x0;

    FileParser file_parser;

    EXPECT_NO_THROW(file_parser.load_rom(rom_file));
    EXPECT_EQ(rom_size, file_parser.get_byte(0x148));
    EXPECT_EQ(ROM_SIZE, file_parser.get_rom_size_banks());
}

TEST(FileParser, GetRAMSize) {
    std::string rom_file = "../../roms/DrMario.gb";
    uint8_t ram_size = 0x0;

    FileParser file_parser;

    EXPECT_NO_THROW(file_parser.load_rom(rom_file));
    EXPECT_EQ(ram_size, file_parser.get_byte(0x149));
    EXPECT_EQ(0, file_parser.get_ram_size_banks());
}

TEST(FileParser, GetCartridgeType) {
    std::string rom_file = "../../roms/DrMario.gb";
    cartridge_type_t type = ROM_ONLY;

    FileParser file_parser;

    EXPECT_NO_THROW(file_parser.load_rom(rom_file));
    EXPECT_EQ(type, file_parser.get_cartridge_type());
}

TEST(FileParser, CheckGameBoyColor) {
    std::string rom_file = "../../roms/DrMario.gb";
    bool is_gameboy_color = false;

    FileParser file_parser;

    EXPECT_NO_THROW(file_parser.load_rom(rom_file));
    EXPECT_EQ(is_gameboy_color, file_parser.is_gb_color());
}

TEST(FileParser, CheckSuperGameBoy) {
    std::string rom_file = "../../roms/DrMario.gb";
    bool is_super_gameboy = false;

    FileParser file_parser;

    EXPECT_NO_THROW(file_parser.load_rom(rom_file));
    EXPECT_EQ(is_super_gameboy, file_parser.is_sgb());
}

TEST(FileParser, GetTitle) {
    std::string rom_file = "../../roms/DrMario.gb";
    std::string title = "DR.MARIO";

    FileParser file_parser;

    EXPECT_TRUE(file_parser.load_rom(rom_file));
    
    EXPECT_EQ(0x44, file_parser.get_byte(0x134));
    EXPECT_EQ(0x0, file_parser.get_byte(0x142));

    EXPECT_EQ(title, file_parser.get_rom_name());
}

TEST(FileParser, GetEntireBuffer) {
    std::string rom_file = "../../roms/DrMario.gb";
    std::string title = "DR.MARIO";
    std::vector<uint8_t> buffer_data;
    uint8_t ram_size = 0x0;
    uint8_t rom_size = 0x1;

    FileParser file_parser;

    EXPECT_NO_THROW(file_parser.load_rom(rom_file));
    buffer_data = file_parser.get_buffer_data();

    EXPECT_EQ(0x44, buffer_data[0x134]);
    EXPECT_EQ(0x0, buffer_data[0x142]);

    for (int i = 0; i < buffer_data.size(); i++) {
        std::cout << static_cast<int>(buffer_data[i]) << std::endl;
    }
}