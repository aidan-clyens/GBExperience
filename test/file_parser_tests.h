#include "gtest/gtest.h"

const int BUFFER_SIZE = 2 * 32 * 1024;
const std::string TEST_ROM = "../../test/test_roms/cpu_instrs/cpu_instrs.gb";
const std::string ROM_TITLE = "CPU_INSTRS";
const int ROM_SIZE = 4;
const cartridge_type_t CARTRIDGE_TYPE = ROM_MBC1;
const bool GB_COLOR_SUPPORTED = true;
const bool SGB_SUPPORTED = false;


TEST(FileParser, DefaultConstructor) {
    FileParser file_parser;

    EXPECT_EQ(0, file_parser.get_buffer_size());
}

TEST(FileParser, LoadRomValidFile) {
    FileParser file_parser;

    EXPECT_TRUE(file_parser.load_rom(TEST_ROM));
    EXPECT_EQ(BUFFER_SIZE, file_parser.get_buffer_size());
}

TEST(FileParser, LoadRomInvalidFile) {
    std::string rom_file = "../../roms/wrong.gb";

    FileParser file_parser;

    EXPECT_FALSE(file_parser.load_rom(rom_file));
    EXPECT_EQ(0, file_parser.get_buffer_size());
}

TEST(FileParser, GetByteOutOfRange) {
    FileParser file_parser;
    file_parser.load_rom(TEST_ROM);

    EXPECT_TRUE(file_parser.load_rom(TEST_ROM));
    EXPECT_ANY_THROW(file_parser.get_byte(BUFFER_SIZE + 10));
}

TEST(FileParser, GetROMSize) {
    uint8_t rom_size = 0x1;

    FileParser file_parser;

    EXPECT_TRUE(file_parser.load_rom(TEST_ROM));
    EXPECT_EQ(rom_size, file_parser.get_byte(0x148));
    EXPECT_EQ(ROM_SIZE, file_parser.get_rom_size_banks());
}

TEST(FileParser, GetRAMSize) {
    uint8_t ram_size = 0x0;

    FileParser file_parser;

    EXPECT_TRUE(file_parser.load_rom(TEST_ROM));
    EXPECT_EQ(ram_size, file_parser.get_byte(0x149));
    EXPECT_EQ(0, file_parser.get_ram_size_banks());
}

TEST(FileParser, GetCartridgeType) {
    FileParser file_parser;

    EXPECT_TRUE(file_parser.load_rom(TEST_ROM));
    EXPECT_EQ(CARTRIDGE_TYPE, file_parser.get_cartridge_type());
}

TEST(FileParser, CheckGameBoyColor) {
    FileParser file_parser;

    EXPECT_TRUE(file_parser.load_rom(TEST_ROM));
    EXPECT_EQ(GB_COLOR_SUPPORTED, file_parser.is_gb_color());
}

TEST(FileParser, CheckSuperGameBoy) {
    FileParser file_parser;

    EXPECT_TRUE(file_parser.load_rom(TEST_ROM));
    EXPECT_EQ(SGB_SUPPORTED, file_parser.is_sgb());
}

TEST(FileParser, GetTitle) {
    FileParser file_parser;

    EXPECT_TRUE(file_parser.load_rom(TEST_ROM));
    EXPECT_EQ(ROM_TITLE, file_parser.get_rom_name());
}

TEST(FileParser, GetEntireBuffer) {
    std::vector<uint8_t> buffer_data;
    uint8_t ram_size = 0x0;
    uint8_t rom_size = 0x1;

    FileParser file_parser;

    EXPECT_TRUE(file_parser.load_rom(TEST_ROM));
    buffer_data = file_parser.get_buffer_data();

    EXPECT_EQ(ram_size, file_parser.get_byte(0x149));
    EXPECT_EQ(rom_size, file_parser.get_byte(0x148));

    for (int i = 0; i < buffer_data.size(); i++) {
        std::cout << static_cast<int>(buffer_data[i]) << std::endl;
    }
}