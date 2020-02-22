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

TEST(InstructionExecuter, ADD) {
    uint8_t opcode = 0x80;
    uint8_t val = 0x20;
    uint8_t n = 0x10;

    MemoryMap mem_map;
    mem_map.init_memory_map(nullptr);
    CPU cpu(mem_map);

    cpu.write_register("A", val);
    cpu.write_register("B", n);
    
    EXPECT_EQ(val, cpu.read_register("A"));
    EXPECT_EQ(n, cpu.read_register("B"));

    cpu.decode_op(opcode);

    EXPECT_EQ(val + n, cpu.read_register("A"));
}

TEST(InstructionExecuter, ADC) {
    uint8_t opcode = 0x88;
    uint8_t val = 0x20;
    uint8_t n = 0x10;

    MemoryMap mem_map;
    mem_map.init_memory_map(nullptr);
    CPU cpu(mem_map);

    cpu.write_register("A", val);
    cpu.write_register("B", n);

    EXPECT_EQ(val, cpu.read_register("A"));
    EXPECT_EQ(n, cpu.read_register("B"));

    cpu.decode_op(opcode);

    EXPECT_EQ(val + n, cpu.read_register("A"));
    // TODO Check carry flag added
    EXPECT_TRUE(false);
}

TEST(InstructionExecuter, SUB) {
    uint8_t opcode = 0x90;
    uint8_t val = 0x20;
    uint8_t n = 0x10;

    MemoryMap mem_map;
    mem_map.init_memory_map(nullptr);
    CPU cpu(mem_map);

    cpu.write_register("A", val);
    cpu.write_register("B", n);

    EXPECT_EQ(val, cpu.read_register("A"));
    EXPECT_EQ(n, cpu.read_register("B"));

    cpu.decode_op(opcode);

    EXPECT_EQ(val - n, cpu.read_register("A"));
}

TEST(InstructionExecuter, SBC) {
    uint8_t opcode = 0x98;
    uint8_t val = 0x20;
    uint8_t n = 0x10;

    MemoryMap mem_map;
    mem_map.init_memory_map(nullptr);
    CPU cpu(mem_map);

    cpu.write_register("A", val);
    cpu.write_register("B", n);

    EXPECT_EQ(val, cpu.read_register("A"));
    EXPECT_EQ(n, cpu.read_register("B"));

    cpu.decode_op(opcode);

    EXPECT_EQ(val - n, cpu.read_register("A"));
    // TODO Check carry flag added
    EXPECT_TRUE(false);
}

TEST(InstructionExecuter, AND) {
    uint8_t opcode = 0xA0;
    uint8_t val = 0x20;
    uint8_t n = 0x10;

    MemoryMap mem_map;
    mem_map.init_memory_map(nullptr);
    CPU cpu(mem_map);

    cpu.write_register("A", val);
    cpu.write_register("B", n);

    EXPECT_EQ(val, cpu.read_register("A"));
    EXPECT_EQ(n, cpu.read_register("B"));

    cpu.decode_op(opcode);

    EXPECT_EQ(val & n, cpu.read_register("A"));
}

TEST(InstructionExecuter, OR) {
    uint8_t opcode = 0xB0;
    uint8_t val = 0x20;
    uint8_t n = 0x10;

    MemoryMap mem_map;
    mem_map.init_memory_map(nullptr);
    CPU cpu(mem_map);

    cpu.write_register("A", val);
    cpu.write_register("B", n);

    EXPECT_EQ(val, cpu.read_register("A"));
    EXPECT_EQ(n, cpu.read_register("B"));

    cpu.decode_op(opcode);

    EXPECT_EQ(val | n, cpu.read_register("A"));
}

TEST(InstructionExecuter, XOR) {
    uint8_t opcode = 0xA8;
    uint8_t val = 0x20;
    uint8_t n = 0x10;

    MemoryMap mem_map;
    mem_map.init_memory_map(nullptr);
    CPU cpu(mem_map);

    cpu.write_register("A", val);
    cpu.write_register("B", n);

    EXPECT_EQ(val, cpu.read_register("A"));
    EXPECT_EQ(n, cpu.read_register("B"));

    cpu.decode_op(opcode);

    EXPECT_EQ(val ^ n, cpu.read_register("A"));
}

TEST(InstructionExecuter, CP) {
    uint8_t opcode = 0xB8;
    uint8_t val = 0x20;
    uint8_t n = 0x10;

    MemoryMap mem_map;
    mem_map.init_memory_map(nullptr);
    CPU cpu(mem_map);

    cpu.write_register("A", val);
    cpu.write_register("B", n);

    EXPECT_EQ(val, cpu.read_register("A"));
    EXPECT_EQ(n, cpu.read_register("B"));

    cpu.decode_op(opcode);

    // TODO Check flag bits
    EXPECT_TRUE(false);
}

TEST(InstructionExecuter, INC) {
    uint8_t opcode = 0x3C;
    uint8_t val = 0x13;

    MemoryMap mem_map;
    mem_map.init_memory_map(nullptr);
    CPU cpu(mem_map);

    cpu.write_register("A", val);

    EXPECT_EQ(val, cpu.read_register("A"));

    cpu.decode_op(opcode);

    EXPECT_EQ(val + 1, cpu.read_register("A"));
}

TEST(InstructionExecuter, DEC) {
    uint8_t opcode = 0x3D;
    uint8_t val = 0x13;

    MemoryMap mem_map;
    mem_map.init_memory_map(nullptr);
    CPU cpu(mem_map);

    cpu.write_register("A", val);

    EXPECT_EQ(val, cpu.read_register("A"));

    cpu.decode_op(opcode);

    EXPECT_EQ(val - 1, cpu.read_register("A"));
}