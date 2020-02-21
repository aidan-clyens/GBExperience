#include "gtest/gtest.h"
#include "cpu/cpu.h"
#include "memory/memory_map.h"
#include "file_parser/file_parser.h"


TEST(InstructionDecoder, CheckAllOpcodes) {
    int buffer_size = 16384;
    std::string rom_file = "../../roms/Tetris.gb";

    FileParser file_parser(buffer_size);
    EXPECT_TRUE(file_parser.load_rom(rom_file));

    MemoryMap mem_map;
    mem_map.init_memory_map(file_parser.get_buffer_ptr());
    CPU cpu(mem_map);

    for (uint8_t i=0x0; i<0xFF; i++) {
        if (i != 0xCB || i != 0xD3) {
            EXPECT_TRUE(cpu.decode_op(i));
        }
    }
}