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

    // Check Flag register
    EXPECT_EQ(false, cpu.read_flag_register(ZERO_FLAG));
    EXPECT_EQ(false, cpu.read_flag_register(SUBTRACT_FLAG));
    EXPECT_EQ(false, cpu.read_flag_register(HALF_CARRY_FLAG));
    EXPECT_EQ(false, cpu.read_flag_register(CARRY_FLAG));
}

TEST(InstructionExecuter, ADDCarry) {
    uint8_t opcode = 0x80;
    uint8_t val = 0xFF;
    uint8_t n = 0x10;

    MemoryMap mem_map;
    mem_map.init_memory_map(nullptr);
    CPU cpu(mem_map);

    cpu.write_register("A", val);
    cpu.write_register("B", n);

    EXPECT_EQ(val, cpu.read_register("A"));
    EXPECT_EQ(n, cpu.read_register("B"));

    cpu.decode_op(opcode);

    EXPECT_EQ((val + n) & 0xFF, cpu.read_register("A"));

    // Check Flag register
    EXPECT_EQ(false, cpu.read_flag_register(ZERO_FLAG));
    EXPECT_EQ(false, cpu.read_flag_register(SUBTRACT_FLAG));
    EXPECT_EQ(false, cpu.read_flag_register(HALF_CARRY_FLAG));
    EXPECT_EQ(true, cpu.read_flag_register(CARRY_FLAG));
}

TEST(InstructionExecuter, ADDZero) {
    uint8_t opcode = 0x80;
    uint8_t val = 0x0;
    uint8_t n = 0x0;

    MemoryMap mem_map;
    mem_map.init_memory_map(nullptr);
    CPU cpu(mem_map);

    cpu.write_register("A", val);
    cpu.write_register("B", n);

    EXPECT_EQ(val, cpu.read_register("A"));
    EXPECT_EQ(n, cpu.read_register("B"));

    cpu.decode_op(opcode);

    EXPECT_EQ((val + n) & 0xFF, cpu.read_register("A"));

    // Check Flag register
    EXPECT_EQ(true, cpu.read_flag_register(ZERO_FLAG));
    EXPECT_EQ(false, cpu.read_flag_register(SUBTRACT_FLAG));
    EXPECT_EQ(false, cpu.read_flag_register(HALF_CARRY_FLAG));
    EXPECT_EQ(false, cpu.read_flag_register(CARRY_FLAG));
}

TEST(InstructionExecuter, ADDHalfCarry) {
    uint8_t opcode = 0x80;
    uint8_t val = 0x0F;
    uint8_t n = 0x01;

    MemoryMap mem_map;
    mem_map.init_memory_map(nullptr);
    CPU cpu(mem_map);

    cpu.write_register("A", val);
    cpu.write_register("B", n);

    EXPECT_EQ(val, cpu.read_register("A"));
    EXPECT_EQ(n, cpu.read_register("B"));

    cpu.decode_op(opcode);

    EXPECT_EQ((val + n) & 0xFF, cpu.read_register("A"));

    // Check Flag register
    EXPECT_EQ(false, cpu.read_flag_register(ZERO_FLAG));
    EXPECT_EQ(false, cpu.read_flag_register(SUBTRACT_FLAG));
    EXPECT_EQ(true, cpu.read_flag_register(HALF_CARRY_FLAG));
    EXPECT_EQ(false, cpu.read_flag_register(CARRY_FLAG));
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

    // Check Flag register
    EXPECT_EQ(false, cpu.read_flag_register(ZERO_FLAG));
    EXPECT_EQ(false, cpu.read_flag_register(SUBTRACT_FLAG));
    EXPECT_EQ(false, cpu.read_flag_register(HALF_CARRY_FLAG));
    EXPECT_EQ(false, cpu.read_flag_register(CARRY_FLAG));
}

TEST(InstructionExecuter, ADCZero) {
    uint8_t opcode = 0x88;
    uint8_t val = 0x0;
    uint8_t n = 0x0;

    MemoryMap mem_map;
    mem_map.init_memory_map(nullptr);
    CPU cpu(mem_map);

    cpu.write_register("A", val);
    cpu.write_register("B", n);

    EXPECT_EQ(val, cpu.read_register("A"));
    EXPECT_EQ(n, cpu.read_register("B"));

    // Run twice to ensure flag register is reset
    cpu.decode_op(opcode);
    cpu.decode_op(opcode);

    EXPECT_EQ(val + n, cpu.read_register("A"));

    // Check Flag register
    EXPECT_EQ(true, cpu.read_flag_register(ZERO_FLAG));
    EXPECT_EQ(false, cpu.read_flag_register(SUBTRACT_FLAG));
    EXPECT_EQ(false, cpu.read_flag_register(HALF_CARRY_FLAG));
    EXPECT_EQ(false, cpu.read_flag_register(CARRY_FLAG));
}

TEST(InstructionExecuter, ADCCarry) {
    uint8_t opcode = 0x88;
    uint8_t val = 0xFF;
    uint8_t n = 0x10;

    MemoryMap mem_map;
    mem_map.init_memory_map(nullptr);
    CPU cpu(mem_map);

    cpu.write_register("A", val);
    cpu.write_register("B", n);

    EXPECT_EQ(val, cpu.read_register("A"));
    EXPECT_EQ(n, cpu.read_register("B"));

    // Run twice to ensure flag register is reset
    cpu.decode_op(opcode);
    cpu.decode_op(opcode);

    EXPECT_EQ(val + n, cpu.read_register("A"));

    // Check Flag register
    EXPECT_EQ(false, cpu.read_flag_register(ZERO_FLAG));
    EXPECT_EQ(false, cpu.read_flag_register(SUBTRACT_FLAG));
    EXPECT_EQ(false, cpu.read_flag_register(HALF_CARRY_FLAG));
    EXPECT_EQ(true, cpu.read_flag_register(CARRY_FLAG));
}

TEST(InstructionExecuter, ADCHalfCarry) {
    uint8_t opcode = 0x88;
    uint8_t val = 0x0F;
    uint8_t n = 0x01;

    MemoryMap mem_map;
    mem_map.init_memory_map(nullptr);
    CPU cpu(mem_map);

    cpu.write_register("A", val);
    cpu.write_register("B", n);

    EXPECT_EQ(val, cpu.read_register("A"));
    EXPECT_EQ(n, cpu.read_register("B"));

    cpu.decode_op(opcode);

    EXPECT_EQ(val + n, cpu.read_register("A"));

    // Check Flag register
    EXPECT_EQ(false, cpu.read_flag_register(ZERO_FLAG));
    EXPECT_EQ(false, cpu.read_flag_register(SUBTRACT_FLAG));
    EXPECT_EQ(true, cpu.read_flag_register(HALF_CARRY_FLAG));
    EXPECT_EQ(false, cpu.read_flag_register(CARRY_FLAG));
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

    // Check Flag register
    EXPECT_EQ(false, cpu.read_flag_register(ZERO_FLAG));
    EXPECT_EQ(true, cpu.read_flag_register(SUBTRACT_FLAG));
    EXPECT_EQ(false, cpu.read_flag_register(HALF_CARRY_FLAG));
    EXPECT_EQ(false, cpu.read_flag_register(CARRY_FLAG));
}

TEST(InstructionExecuter, SUBZero) {
    uint8_t opcode = 0x90;
    uint8_t val = 0x20;
    uint8_t n = 0x20;

    MemoryMap mem_map;
    mem_map.init_memory_map(nullptr);
    CPU cpu(mem_map);

    cpu.write_register("A", val);
    cpu.write_register("B", n);

    EXPECT_EQ(val, cpu.read_register("A"));
    EXPECT_EQ(n, cpu.read_register("B"));

    cpu.decode_op(opcode);

    EXPECT_EQ(val - n, cpu.read_register("A"));

    // Check Flag register
    EXPECT_EQ(true, cpu.read_flag_register(ZERO_FLAG));
    EXPECT_EQ(true, cpu.read_flag_register(SUBTRACT_FLAG));
    EXPECT_EQ(false, cpu.read_flag_register(HALF_CARRY_FLAG));
    EXPECT_EQ(false, cpu.read_flag_register(CARRY_FLAG));
}

TEST(InstructionExecuter, SUBCarry) {
    uint8_t opcode = 0x90;
    uint8_t val = 0x60;
    uint8_t n = 0x80;

    MemoryMap mem_map;
    mem_map.init_memory_map(nullptr);
    CPU cpu(mem_map);

    cpu.write_register("A", val);
    cpu.write_register("B", n);

    EXPECT_EQ(val, cpu.read_register("A"));
    EXPECT_EQ(n, cpu.read_register("B"));

    cpu.decode_op(opcode);

    EXPECT_EQ(val - n, cpu.read_register("A"));

    // Check Flag register
    EXPECT_EQ(false, cpu.read_flag_register(ZERO_FLAG));
    EXPECT_EQ(true, cpu.read_flag_register(SUBTRACT_FLAG));
    EXPECT_EQ(false, cpu.read_flag_register(HALF_CARRY_FLAG));
    EXPECT_EQ(true, cpu.read_flag_register(CARRY_FLAG));
}

TEST(InstructionExecuter, SUBHalfCarry) {
    uint8_t opcode = 0x90;
    uint8_t val = 0x06;
    uint8_t n = 0x08;

    MemoryMap mem_map;
    mem_map.init_memory_map(nullptr);
    CPU cpu(mem_map);

    cpu.write_register("A", val);
    cpu.write_register("B", n);

    EXPECT_EQ(val, cpu.read_register("A"));
    EXPECT_EQ(n, cpu.read_register("B"));

    cpu.decode_op(opcode);

    EXPECT_EQ(val - n, cpu.read_register("A"));

    // Check Flag register
    EXPECT_EQ(false, cpu.read_flag_register(ZERO_FLAG));
    EXPECT_EQ(true, cpu.read_flag_register(SUBTRACT_FLAG));
    EXPECT_EQ(true, cpu.read_flag_register(HALF_CARRY_FLAG));
    EXPECT_EQ(false, cpu.read_flag_register(CARRY_FLAG));
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

    // Check Flag register
    EXPECT_EQ(false, cpu.read_flag_register(ZERO_FLAG));
    EXPECT_EQ(true, cpu.read_flag_register(SUBTRACT_FLAG));
    EXPECT_EQ(false, cpu.read_flag_register(HALF_CARRY_FLAG));
    EXPECT_EQ(false, cpu.read_flag_register(CARRY_FLAG));
}

TEST(InstructionExecuter, SBCZero) {
    uint8_t opcode = 0x98;
    uint8_t val = 0x20;
    uint8_t n = 0x20;

    MemoryMap mem_map;
    mem_map.init_memory_map(nullptr);
    CPU cpu(mem_map);

    cpu.write_register("A", val);
    cpu.write_register("B", n);

    EXPECT_EQ(val, cpu.read_register("A"));
    EXPECT_EQ(n, cpu.read_register("B"));

    // Run twice to ensure flag register is reset
    cpu.decode_op(opcode);
    cpu.decode_op(opcode);

    EXPECT_EQ(val - n, cpu.read_register("A"));

    // Check Flag register
    EXPECT_EQ(true, cpu.read_flag_register(ZERO_FLAG));
    EXPECT_EQ(true, cpu.read_flag_register(SUBTRACT_FLAG));
    EXPECT_EQ(false, cpu.read_flag_register(HALF_CARRY_FLAG));
    EXPECT_EQ(false, cpu.read_flag_register(CARRY_FLAG));
}

TEST(InstructionExecuter, SBCCarry) {
    uint8_t opcode = 0x98;
    uint8_t val = 0x60;
    uint8_t n = 0x80;

    MemoryMap mem_map;
    mem_map.init_memory_map(nullptr);
    CPU cpu(mem_map);

    // Ensure no carry flag is set in previous operation
    cpu.write_register("A", 0);
    cpu.write_register("B", 0);
    cpu.decode_op(opcode);

    EXPECT_EQ(0, cpu.read_register("A"));

    cpu.write_register("A", val);
    cpu.write_register("B", n);

    EXPECT_EQ(val, cpu.read_register("A"));
    EXPECT_EQ(n, cpu.read_register("B"));

    cpu.decode_op(opcode);

    EXPECT_EQ(val - n, cpu.read_register("A"));

    // Check Flag register
    EXPECT_EQ(false, cpu.read_flag_register(ZERO_FLAG));
    EXPECT_EQ(true, cpu.read_flag_register(SUBTRACT_FLAG));
    EXPECT_EQ(false, cpu.read_flag_register(HALF_CARRY_FLAG));
    EXPECT_EQ(true, cpu.read_flag_register(CARRY_FLAG));
}

TEST(InstructionExecuter, SBCHalfCarry) {
    uint8_t opcode = 0x98;
    uint8_t val = 0x06;
    uint8_t n = 0x08;

    MemoryMap mem_map;
    mem_map.init_memory_map(nullptr);
    CPU cpu(mem_map);

    // Ensure no carry flag is set in previous operation
    cpu.write_register("A", 0);
    cpu.write_register("B", 0);
    cpu.decode_op(opcode);

    EXPECT_EQ(0, cpu.read_register("A"));

    cpu.write_register("A", val);
    cpu.write_register("B", n);

    EXPECT_EQ(val, cpu.read_register("A"));
    EXPECT_EQ(n, cpu.read_register("B"));

    cpu.decode_op(opcode);

    EXPECT_EQ(val - n, cpu.read_register("A"));

    // Check Flag register
    EXPECT_EQ(false, cpu.read_flag_register(ZERO_FLAG));
    EXPECT_EQ(true, cpu.read_flag_register(SUBTRACT_FLAG));
    EXPECT_EQ(true, cpu.read_flag_register(HALF_CARRY_FLAG));
    EXPECT_EQ(false, cpu.read_flag_register(CARRY_FLAG));
}

TEST(InstructionExecuter, AND) {
    uint8_t opcode = 0xA0;
    uint8_t val = 0x10;
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

    // Check Flag register
    EXPECT_EQ(false, cpu.read_flag_register(ZERO_FLAG));
    EXPECT_EQ(false, cpu.read_flag_register(SUBTRACT_FLAG));
    EXPECT_EQ(true, cpu.read_flag_register(HALF_CARRY_FLAG));
    EXPECT_EQ(false, cpu.read_flag_register(CARRY_FLAG));
}

TEST(InstructionExecuter, ANDZero) {
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

    // Check Flag register
    EXPECT_EQ(true, cpu.read_flag_register(ZERO_FLAG));
    EXPECT_EQ(false, cpu.read_flag_register(SUBTRACT_FLAG));
    EXPECT_EQ(true, cpu.read_flag_register(HALF_CARRY_FLAG));
    EXPECT_EQ(false, cpu.read_flag_register(CARRY_FLAG));
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

    // Check Flag register
    EXPECT_EQ(false, cpu.read_flag_register(ZERO_FLAG));
    EXPECT_EQ(false, cpu.read_flag_register(SUBTRACT_FLAG));
    EXPECT_EQ(false, cpu.read_flag_register(HALF_CARRY_FLAG));
    EXPECT_EQ(false, cpu.read_flag_register(CARRY_FLAG));
}

TEST(InstructionExecuter, ORZero) {
    uint8_t opcode = 0xB0;
    uint8_t val = 0x0;
    uint8_t n = 0x0;

    MemoryMap mem_map;
    mem_map.init_memory_map(nullptr);
    CPU cpu(mem_map);

    cpu.write_register("A", val);
    cpu.write_register("B", n);

    EXPECT_EQ(val, cpu.read_register("A"));
    EXPECT_EQ(n, cpu.read_register("B"));

    cpu.decode_op(opcode);

    EXPECT_EQ(val | n, cpu.read_register("A"));

    // Check Flag register
    EXPECT_EQ(true, cpu.read_flag_register(ZERO_FLAG));
    EXPECT_EQ(false, cpu.read_flag_register(SUBTRACT_FLAG));
    EXPECT_EQ(false, cpu.read_flag_register(HALF_CARRY_FLAG));
    EXPECT_EQ(false, cpu.read_flag_register(CARRY_FLAG));
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

    // Check Flag register
    EXPECT_EQ(false, cpu.read_flag_register(ZERO_FLAG));
    EXPECT_EQ(false, cpu.read_flag_register(SUBTRACT_FLAG));
    EXPECT_EQ(false, cpu.read_flag_register(HALF_CARRY_FLAG));
    EXPECT_EQ(false, cpu.read_flag_register(CARRY_FLAG));
}

TEST(InstructionExecuter, XORZero) {
    uint8_t opcode = 0xA8;
    uint8_t val = 0x10;
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

    // Check Flag register
    EXPECT_EQ(true, cpu.read_flag_register(ZERO_FLAG));
    EXPECT_EQ(false, cpu.read_flag_register(SUBTRACT_FLAG));
    EXPECT_EQ(false, cpu.read_flag_register(HALF_CARRY_FLAG));
    EXPECT_EQ(false, cpu.read_flag_register(CARRY_FLAG));
}


TEST(InstructionExecuter, CPNoMatch) {
    uint8_t opcode = 0xB8;
    uint8_t val = 0x10;
    uint8_t n = 0x20;

    MemoryMap mem_map;
    mem_map.init_memory_map(nullptr);
    CPU cpu(mem_map);

    cpu.write_register("A", val);
    cpu.write_register("B", n);

    EXPECT_EQ(val, cpu.read_register("A"));
    EXPECT_EQ(n, cpu.read_register("B"));

    cpu.decode_op(opcode);

    EXPECT_EQ(val - n, cpu.read_register("A"));

    // Check Flag register
    EXPECT_EQ(false, cpu.read_flag_register(ZERO_FLAG));
    EXPECT_EQ(true, cpu.read_flag_register(SUBTRACT_FLAG));
    EXPECT_EQ(false, cpu.read_flag_register(HALF_CARRY_FLAG));
    EXPECT_EQ(true, cpu.read_flag_register(CARRY_FLAG));
}

TEST(InstructionExecuter, CPMatch) {
    uint8_t opcode = 0xB8;
    uint8_t val = 0x20;
    uint8_t n = 0x20;

    MemoryMap mem_map;
    mem_map.init_memory_map(nullptr);
    CPU cpu(mem_map);

    cpu.write_register("A", val);
    cpu.write_register("B", n);

    EXPECT_EQ(val, cpu.read_register("A"));
    EXPECT_EQ(n, cpu.read_register("B"));

    cpu.decode_op(opcode);

    EXPECT_EQ(val - n, cpu.read_register("A"));

    // Check Flag register
    EXPECT_EQ(true, cpu.read_flag_register(ZERO_FLAG));
    EXPECT_EQ(true, cpu.read_flag_register(SUBTRACT_FLAG));
    EXPECT_EQ(false, cpu.read_flag_register(HALF_CARRY_FLAG));
    EXPECT_EQ(false, cpu.read_flag_register(CARRY_FLAG));
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

    // Check Flag register
    EXPECT_EQ(false, cpu.read_flag_register(ZERO_FLAG));
    EXPECT_EQ(false, cpu.read_flag_register(SUBTRACT_FLAG));
    EXPECT_EQ(false, cpu.read_flag_register(HALF_CARRY_FLAG));
}

TEST(InstructionExecuter, INCHalfCarry) {
    uint8_t opcode = 0x3C;
    uint8_t val = 0x1F;

    MemoryMap mem_map;
    mem_map.init_memory_map(nullptr);
    CPU cpu(mem_map);

    cpu.write_register("A", val);

    EXPECT_EQ(val, cpu.read_register("A"));

    cpu.decode_op(opcode);

    EXPECT_EQ(val + 1, cpu.read_register("A"));

    // Check Flag register
    EXPECT_EQ(false, cpu.read_flag_register(ZERO_FLAG));
    EXPECT_EQ(false, cpu.read_flag_register(SUBTRACT_FLAG));
    EXPECT_EQ(true, cpu.read_flag_register(HALF_CARRY_FLAG));
}

TEST(InstructionExecuter, INC_16Bit) {
    uint8_t opcode = 0x34;
    uint16_t val = 0x1312;

    MemoryMap mem_map;
    mem_map.init_memory_map(nullptr);
    CPU cpu(mem_map);

    cpu.write_register("HL", val);

    EXPECT_EQ(val, cpu.read_register("HL"));

    cpu.decode_op(opcode);

    EXPECT_EQ(val + 1, cpu.read_register("HL"));
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

    // Check Flag register
    EXPECT_EQ(false, cpu.read_flag_register(ZERO_FLAG));
    EXPECT_EQ(true, cpu.read_flag_register(SUBTRACT_FLAG));
    EXPECT_EQ(false, cpu.read_flag_register(HALF_CARRY_FLAG));
}

TEST(InstructionExecuter, DECZero) {
    uint8_t opcode = 0x3D;
    uint8_t val = 0x01;

    MemoryMap mem_map;
    mem_map.init_memory_map(nullptr);
    CPU cpu(mem_map);

    cpu.write_register("A", val);

    EXPECT_EQ(val, cpu.read_register("A"));

    cpu.decode_op(opcode);

    EXPECT_EQ(val - 1, cpu.read_register("A"));

    // Check Flag register
    EXPECT_EQ(true, cpu.read_flag_register(ZERO_FLAG));
    EXPECT_EQ(true, cpu.read_flag_register(SUBTRACT_FLAG));
    EXPECT_EQ(false, cpu.read_flag_register(HALF_CARRY_FLAG));
}

TEST(InstructionExecuter, DEC_16Bit) {
    uint8_t opcode = 0x35;
    uint16_t val = 0x1312;

    MemoryMap mem_map;
    mem_map.init_memory_map(nullptr);
    CPU cpu(mem_map);

    cpu.write_register("HL", val);

    EXPECT_EQ(val, cpu.read_register("HL"));

    cpu.decode_op(opcode);

    EXPECT_EQ(val - 1, cpu.read_register("HL"));
}