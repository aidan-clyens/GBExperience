#include "gtest/gtest.h"
#include "file_parser/file_parser.h"


TEST(FileParser, DefaultConstructor) {
    int buffer_size = 1024;

    FileParser file_parser(buffer_size);

    EXPECT_EQ(buffer_size, file_parser.get_buffer_size());
}

TEST(FileParser, LoadRomValidFile) {
    int buffer_size = 16384;
    std::string rom_file = "../../roms/Tetris.gb";

    FileParser file_parser(buffer_size);

    EXPECT_EQ(buffer_size, file_parser.get_buffer_size());
    EXPECT_TRUE(file_parser.load_rom(rom_file));
}

TEST(FileParser, LoadRomInvalidFile) {
    int buffer_size = 16384;
    std::string rom_file = "../../roms/wrong.gb";

    FileParser file_parser(buffer_size);

    EXPECT_EQ(buffer_size, file_parser.get_buffer_size());
    EXPECT_FALSE(file_parser.load_rom(rom_file));
}

TEST(FileParser, GetByteOutOfRange) {
    int buffer_size = 16384;
    std::string rom_file = "../../roms/Tetris.gb";

    FileParser file_parser(buffer_size);

    EXPECT_TRUE(file_parser.load_rom(rom_file));
    EXPECT_ANY_THROW(file_parser.get_byte(buffer_size + 10));
}

TEST(FileParser, GetROMSize) {
    int buffer_size = 16384;
    std::string rom_file = "../../roms/Tetris.gb";
    uint8_t rom_size = 0x0;

    FileParser file_parser(buffer_size);

    EXPECT_TRUE(file_parser.load_rom(rom_file));
    EXPECT_EQ(rom_size, file_parser.get_byte(0x148));
}

TEST(FileParser, GetRAMSize) {
    int buffer_size = 16384;
    std::string rom_file = "../../roms/Tetris.gb";
    uint8_t ram_size = 0x0;

    FileParser file_parser(buffer_size);

    EXPECT_TRUE(file_parser.load_rom(rom_file));
    EXPECT_EQ(ram_size, file_parser.get_byte(0x149));
}

TEST(FileParser, GetTitle) {
    int buffer_size = 16384;
    std::string rom_file = "../../roms/Tetris.gb";
    std::string title = "TETRIS";

    FileParser file_parser(buffer_size);

    EXPECT_TRUE(file_parser.load_rom(rom_file));
    
    EXPECT_EQ(0x54, file_parser.get_byte(0x134));
    EXPECT_EQ(0x0, file_parser.get_byte(0x142));

    EXPECT_EQ(title, file_parser.get_rom_name());
}

TEST(FileParser, GetEntireBuffer) {
    int buffer_size = 16384;
    std::string rom_file = "../../roms/Tetris.gb";
    std::string title = "TETRIS";
    uint8_t *buffer_ptr;

    FileParser file_parser(buffer_size);

    EXPECT_TRUE(file_parser.load_rom(rom_file));
    buffer_ptr = file_parser.get_buffer_ptr();
    
    EXPECT_EQ(0x54, buffer_ptr[0x134]);
    EXPECT_EQ(0x0, buffer_ptr[0x142]);
}