#include "gtest/gtest.h"
#include "cpu/cpu.h"
#include "memory/memory_map.h"
#include "file_parser/file_parser.h"


/****    8-Bit ALU    ****/
TEST(CPU_ALU, ADD) {
    uint8_t opcode = 0x80;
    uint8_t val = 0x20;
    uint8_t n = 0x10;

    MemoryMap mem_map;
    
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

TEST(CPU_ALU, ADD_HL) {
    uint8_t opcode = 0x86;
    uint8_t val = 0x20;
    uint16_t address = 0xA0FF;
    uint8_t n = 0x10;

    MemoryMap mem_map;
    
    CPU cpu(mem_map);

    cpu.write_register("A", val);
    cpu.write_register("HL", address);
    
    cpu.write_memory(n);

    EXPECT_EQ(val, cpu.read_register("A"));
    EXPECT_EQ(address, cpu.read_register("HL"));
    EXPECT_EQ(n, cpu.read_memory());

    cpu.decode_op(opcode);

    EXPECT_EQ(val + n, cpu.read_register("A"));

    // Check Flag register
    EXPECT_EQ(false, cpu.read_flag_register(ZERO_FLAG));
    EXPECT_EQ(false, cpu.read_flag_register(SUBTRACT_FLAG));
    EXPECT_EQ(false, cpu.read_flag_register(HALF_CARRY_FLAG));
    EXPECT_EQ(false, cpu.read_flag_register(CARRY_FLAG));
}

TEST(CPU_ALU, ADD_N) {
    uint8_t opcode = 0xC6;
    uint8_t val = 0x20;
    uint8_t n = 0x10;

    uint16_t PC = 0xA0FF;

    MemoryMap mem_map;
    
    mem_map.write(PC, n);

    EXPECT_EQ(n, mem_map.read(PC));

    CPU cpu(mem_map);

    cpu.write_register("PC", PC);
    cpu.write_register("A", val);

    EXPECT_EQ(PC, cpu.read_register("PC"));
    EXPECT_EQ(val, cpu.read_register("A"));

    cpu.decode_op(opcode);

    EXPECT_EQ(val + n, cpu.read_register("A"));

    // Check Flag register
    EXPECT_EQ(false, cpu.read_flag_register(ZERO_FLAG));
    EXPECT_EQ(false, cpu.read_flag_register(SUBTRACT_FLAG));
    EXPECT_EQ(false, cpu.read_flag_register(HALF_CARRY_FLAG));
    EXPECT_EQ(false, cpu.read_flag_register(CARRY_FLAG));
}

TEST(CPU_ALU, ADDCarry) {
    uint8_t opcode = 0x80;
    uint8_t val = 0xFF;
    uint8_t n = 0x10;

    MemoryMap mem_map;
    
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

TEST(CPU_ALU, ADDZero) {
    uint8_t opcode = 0x80;
    uint8_t val = 0x0;
    uint8_t n = 0x0;

    MemoryMap mem_map;
    
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

TEST(CPU_ALU, ADDHalfCarry) {
    uint8_t opcode = 0x80;
    uint8_t val = 0x0F;
    uint8_t n = 0x01;

    MemoryMap mem_map;
    
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

TEST(CPU_ALU, ADC) {
    uint8_t opcode = 0x80;
    uint8_t val = 0xFF;
    uint8_t n = 0x10;

    MemoryMap mem_map;
    
    CPU cpu(mem_map);

    // First operation sets carry flag
    cpu.write_register("A", val);
    cpu.write_register("B", n);

    EXPECT_EQ(val, cpu.read_register("A"));
    EXPECT_EQ(n, cpu.read_register("B"));

    cpu.decode_op(opcode);

    // Second operation uses carry flag
    opcode = 0x88;
    val = 0x20;
    n = 0x10;

    cpu.write_register("A", val);
    cpu.write_register("B", n);

    EXPECT_EQ(val, cpu.read_register("A"));
    EXPECT_EQ(n, cpu.read_register("B"));

    cpu.decode_op(opcode);

    EXPECT_EQ(val + n + 1, cpu.read_register("A"));

    // Check Flag register
    EXPECT_EQ(false, cpu.read_flag_register(ZERO_FLAG));
    EXPECT_EQ(false, cpu.read_flag_register(SUBTRACT_FLAG));
    EXPECT_EQ(false, cpu.read_flag_register(HALF_CARRY_FLAG));
    EXPECT_EQ(false, cpu.read_flag_register(CARRY_FLAG));
}

TEST(CPU_ALU, ADCZero) {
    uint8_t opcode = 0x88;
    uint8_t val = 0x0;
    uint8_t n = 0x0;

    MemoryMap mem_map;
    
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

TEST(CPU_ALU, ADCCarry) {
    uint8_t opcode = 0x88;
    uint8_t val = 0xFF;
    uint8_t n = 0x02;

    MemoryMap mem_map;
    
    CPU cpu(mem_map);
    
    // First operation ensures that carry flag is set
    cpu.write_register("A", val);
    cpu.write_register("B", n);

    EXPECT_EQ(val, cpu.read_register("A"));
    EXPECT_EQ(n, cpu.read_register("B"));
    cpu.decode_op(opcode);

    // Second operation uses carry flag
    opcode = 0x88;
    val = 0xFF;
    n = 0x10;

    cpu.write_register("A", val);
    cpu.write_register("B", n);

    EXPECT_EQ(val, cpu.read_register("A"));
    EXPECT_EQ(n, cpu.read_register("B"));

    cpu.decode_op(opcode);

    EXPECT_EQ(((val + n) & 0xFF) + 1, cpu.read_register("A"));

    // Check Flag register
    EXPECT_EQ(false, cpu.read_flag_register(ZERO_FLAG));
    EXPECT_EQ(false, cpu.read_flag_register(SUBTRACT_FLAG));
    EXPECT_EQ(false, cpu.read_flag_register(HALF_CARRY_FLAG));
    EXPECT_EQ(true, cpu.read_flag_register(CARRY_FLAG));
}

TEST(CPU_ALU, ADCHalfCarry) {
    uint8_t opcode = 0x88;
    uint8_t val = 0x0F;
    uint8_t n = 0x01;

    MemoryMap mem_map;
    
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

TEST(CPU_ALU, SUB) {
    uint8_t opcode = 0x90;
    uint8_t val = 0xF0;     // 1111 0000
    uint8_t n = 0x50;       // 0101 0000
    uint8_t result = 0xA0;  // 1010 0000

    MemoryMap mem_map;
    
    CPU cpu(mem_map);

    cpu.write_register("A", val);
    cpu.write_register("B", n);

    EXPECT_EQ(val, cpu.read_register("A"));
    EXPECT_EQ(n, cpu.read_register("B"));

    cpu.decode_op(opcode);

    EXPECT_EQ(result, cpu.read_register("A"));

    // Check Flag register
    EXPECT_EQ(false, cpu.read_flag_register(ZERO_FLAG));
    EXPECT_EQ(true, cpu.read_flag_register(SUBTRACT_FLAG));
    EXPECT_EQ(true, cpu.read_flag_register(HALF_CARRY_FLAG));
    EXPECT_EQ(true, cpu.read_flag_register(CARRY_FLAG));
}

TEST(CPU_ALU, SUB_HL) {
    uint8_t opcode = 0x96;
    uint16_t address = 0xA0FF;
    uint8_t val = 0xF0;    // 1111 0000
    uint8_t n = 0x50;      // 0101 0000
    uint8_t result = 0xA0; // 1010 0000

    MemoryMap mem_map;
    
    CPU cpu(mem_map);

    cpu.write_register("A", val);
    cpu.write_register("HL", address);
    cpu.write_memory(n);

    EXPECT_EQ(val, cpu.read_register("A"));
    EXPECT_EQ(address, cpu.read_register("HL"));
    EXPECT_EQ(n, cpu.read_memory());

    cpu.decode_op(opcode);

    EXPECT_EQ(result, cpu.read_register("A"));

    // Check Flag register
    EXPECT_EQ(false, cpu.read_flag_register(ZERO_FLAG));
    EXPECT_EQ(true, cpu.read_flag_register(SUBTRACT_FLAG));
    EXPECT_EQ(true, cpu.read_flag_register(HALF_CARRY_FLAG));
    EXPECT_EQ(true, cpu.read_flag_register(CARRY_FLAG));
}

TEST(CPU_ALU, SUBZero) {
    uint8_t opcode = 0x90;
    uint8_t val = 0xF0;    // 1111 0000
    uint8_t n = 0xF0;      // 1111 0000
    uint8_t result = 0x00; // 0000 0000

    MemoryMap mem_map;
    
    CPU cpu(mem_map);

    cpu.write_register("A", val);
    cpu.write_register("B", n);

    EXPECT_EQ(val, cpu.read_register("A"));
    EXPECT_EQ(n, cpu.read_register("B"));

    cpu.decode_op(opcode);

    EXPECT_EQ(result, cpu.read_register("A"));

    // Check Flag register
    EXPECT_EQ(true, cpu.read_flag_register(ZERO_FLAG));
    EXPECT_EQ(true, cpu.read_flag_register(SUBTRACT_FLAG));
    EXPECT_EQ(true, cpu.read_flag_register(HALF_CARRY_FLAG));
    EXPECT_EQ(true, cpu.read_flag_register(CARRY_FLAG));
}

TEST(CPU_ALU, SUBCarry) {
    uint8_t opcode = 0x90;
    uint8_t val = 0x80;    // 1000 0000
    uint8_t n = 0x70;      // 0111 0000
    uint8_t result = 0x10; // 0001 0000

    MemoryMap mem_map;
    
    CPU cpu(mem_map);

    cpu.write_register("A", val);
    cpu.write_register("B", n);

    EXPECT_EQ(val, cpu.read_register("A"));
    EXPECT_EQ(n, cpu.read_register("B"));

    cpu.decode_op(opcode);

    EXPECT_EQ(result, cpu.read_register("A"));

    // Check Flag register
    EXPECT_EQ(false, cpu.read_flag_register(ZERO_FLAG));
    EXPECT_EQ(true, cpu.read_flag_register(SUBTRACT_FLAG));
    EXPECT_EQ(true, cpu.read_flag_register(HALF_CARRY_FLAG));
    EXPECT_EQ(false, cpu.read_flag_register(CARRY_FLAG));
}

TEST(CPU_ALU, SUBHalfCarry) {
    uint8_t opcode = 0x90;
    uint8_t val = 0x88;    // 1000 1000
    uint8_t n = 0x07;      // 0000 0111
    uint8_t result = 0x81; // 1000 0001

    MemoryMap mem_map;
    
    CPU cpu(mem_map);

    cpu.write_register("A", val);
    cpu.write_register("B", n);

    EXPECT_EQ(val, cpu.read_register("A"));
    EXPECT_EQ(n, cpu.read_register("B"));

    cpu.decode_op(opcode);

    EXPECT_EQ(result, cpu.read_register("A"));

    // Check Flag register
    EXPECT_EQ(false, cpu.read_flag_register(ZERO_FLAG));
    EXPECT_EQ(true, cpu.read_flag_register(SUBTRACT_FLAG));
    EXPECT_EQ(false, cpu.read_flag_register(HALF_CARRY_FLAG));
    EXPECT_EQ(false, cpu.read_flag_register(CARRY_FLAG));
}

TEST(CPU_ALU, SBCCarryNotSet) {
    uint8_t opcode = 0x98;
    uint8_t val = 0xF0;    // 1111 0000
    uint8_t n = 0x50;      // 0101 0000
    uint8_t result = 0xA0; // 1010 0000

    MemoryMap mem_map;
    
    CPU cpu(mem_map);

    cpu.write_register("A", val);
    cpu.write_register("B", n);

    EXPECT_EQ(val, cpu.read_register("A"));
    EXPECT_EQ(n, cpu.read_register("B"));

    // Set carry flag to false
    cpu.set_flag_register(CARRY_FLAG, false);
    EXPECT_FALSE(cpu.read_flag_register(CARRY_FLAG));

    cpu.decode_op(opcode);

    EXPECT_EQ(result, cpu.read_register("A"));

    // Check Flag register
    EXPECT_EQ(false, cpu.read_flag_register(ZERO_FLAG));
    EXPECT_EQ(true, cpu.read_flag_register(SUBTRACT_FLAG));
    EXPECT_EQ(true, cpu.read_flag_register(HALF_CARRY_FLAG));
    EXPECT_EQ(true, cpu.read_flag_register(CARRY_FLAG));
}

TEST(CPU_ALU, SBCCarrySet) {
    uint8_t opcode = 0x98;
    uint8_t val = 0xF0;    // 1111 0000
    uint8_t n = 0x50;      // 0101 0000
    uint8_t result = 0x9F; // 1001 1111

    MemoryMap mem_map;
    
    CPU cpu(mem_map);

    cpu.write_register("A", val);
    cpu.write_register("B", n);

    EXPECT_EQ(val, cpu.read_register("A"));
    EXPECT_EQ(n, cpu.read_register("B"));

    // Set carry flag to false
    cpu.set_flag_register(CARRY_FLAG, true);
    EXPECT_TRUE(cpu.read_flag_register(CARRY_FLAG));

    cpu.decode_op(opcode);

    EXPECT_EQ(result, cpu.read_register("A"));

    // Check Flag register
    EXPECT_EQ(false, cpu.read_flag_register(ZERO_FLAG));
    EXPECT_EQ(true, cpu.read_flag_register(SUBTRACT_FLAG));
    EXPECT_EQ(false, cpu.read_flag_register(HALF_CARRY_FLAG));
    EXPECT_EQ(false, cpu.read_flag_register(CARRY_FLAG));
}

TEST(CPU_ALU, SBCZero) {
    uint8_t opcode = 0x98;
    uint8_t val = 0x20;     // 0010 0000
    uint8_t n = 0x1F;       // 0001 1111
    uint8_t result = 0x00;

    MemoryMap mem_map;
    
    CPU cpu(mem_map);

    cpu.write_register("A", val);
    cpu.write_register("B", n);

    EXPECT_EQ(val, cpu.read_register("A"));
    EXPECT_EQ(n, cpu.read_register("B"));

    cpu.set_flag_register(CARRY_FLAG, true);
    EXPECT_TRUE(cpu.read_flag_register(CARRY_FLAG));

    cpu.decode_op(opcode);

    EXPECT_EQ(result, cpu.read_register("A"));

    // Check Flag register
    EXPECT_EQ(true, cpu.read_flag_register(ZERO_FLAG));
    EXPECT_EQ(true, cpu.read_flag_register(SUBTRACT_FLAG));
    EXPECT_EQ(true, cpu.read_flag_register(HALF_CARRY_FLAG));
    EXPECT_EQ(true, cpu.read_flag_register(CARRY_FLAG));
}

TEST(CPU_ALU, SBCCarry) {
    uint8_t opcode = 0x98;
    uint8_t val = 0x60;     // 0110 0000
    uint8_t n = 0x4F;       // 0100 1111
    uint8_t result = 0x10;  // 0001 0000

    MemoryMap mem_map;
    
    CPU cpu(mem_map);

    cpu.write_register("A", val);
    cpu.write_register("B", n);

    EXPECT_EQ(val, cpu.read_register("A"));
    EXPECT_EQ(n, cpu.read_register("B"));

    cpu.set_flag_register(CARRY_FLAG, true);
    EXPECT_TRUE(cpu.read_flag_register(CARRY_FLAG));

    cpu.decode_op(opcode);

    EXPECT_EQ(result, cpu.read_register("A"));

    // Check Flag register
    EXPECT_EQ(false, cpu.read_flag_register(ZERO_FLAG));
    EXPECT_EQ(true, cpu.read_flag_register(SUBTRACT_FLAG));
    EXPECT_EQ(true, cpu.read_flag_register(HALF_CARRY_FLAG));
    EXPECT_EQ(false, cpu.read_flag_register(CARRY_FLAG));
}

TEST(CPU_ALU, SBCHalfCarry) {
    uint8_t opcode = 0x98;
    uint8_t val = 0x06;     // 0000 0110
    uint8_t n = 0x04;       // 0000 0100
    uint8_t result = 0x01;

    MemoryMap mem_map;
    
    CPU cpu(mem_map);

    cpu.write_register("A", val);
    cpu.write_register("B", n);

    EXPECT_EQ(val, cpu.read_register("A"));
    EXPECT_EQ(n, cpu.read_register("B"));

    cpu.set_flag_register(CARRY_FLAG, true);
    EXPECT_TRUE(cpu.read_flag_register(CARRY_FLAG));

    cpu.decode_op(opcode);

    EXPECT_EQ(result, cpu.read_register("A"));

    // Check Flag register
    EXPECT_EQ(false, cpu.read_flag_register(ZERO_FLAG));
    EXPECT_EQ(true, cpu.read_flag_register(SUBTRACT_FLAG));
    EXPECT_EQ(false, cpu.read_flag_register(HALF_CARRY_FLAG));
    EXPECT_EQ(false, cpu.read_flag_register(CARRY_FLAG));
}

TEST(CPU_ALU, AND) {
    uint8_t opcode = 0xA0;
    uint8_t val = 0x10;
    uint8_t n = 0x10;

    MemoryMap mem_map;
    
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

TEST(CPU_ALU, ANDZero) {
    uint8_t opcode = 0xA0;
    uint8_t val = 0x20;
    uint8_t n = 0x10;

    MemoryMap mem_map;
    
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

TEST(CPU_ALU, OR) {
    uint8_t opcode = 0xB0;
    uint8_t val = 0x20;
    uint8_t n = 0x10;

    MemoryMap mem_map;
    
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

TEST(CPU_ALU, ORZero) {
    uint8_t opcode = 0xB0;
    uint8_t val = 0x0;
    uint8_t n = 0x0;

    MemoryMap mem_map;
    
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

TEST(CPU_ALU, XOR) {
    uint8_t opcode = 0xA8;
    uint8_t val = 0x20;
    uint8_t n = 0x10;

    MemoryMap mem_map;
    
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

TEST(CPU_ALU, XORZero) {
    uint8_t opcode = 0xA8;
    uint8_t val = 0x10;
    uint8_t n = 0x10;

    MemoryMap mem_map;
    
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


TEST(CPU_ALU, CPNoMatch) {
    uint8_t opcode = 0xB8;
    uint8_t val = 0x10;
    uint8_t n = 0x20;

    MemoryMap mem_map;
    
    CPU cpu(mem_map);

    cpu.write_register("A", val);
    cpu.write_register("B", n);

    EXPECT_EQ(val, cpu.read_register("A"));
    EXPECT_EQ(n, cpu.read_register("B"));

    cpu.decode_op(opcode);

    // Check Flag register
    EXPECT_EQ(false, cpu.read_flag_register(ZERO_FLAG));
    EXPECT_EQ(true, cpu.read_flag_register(SUBTRACT_FLAG));
    EXPECT_EQ(false, cpu.read_flag_register(HALF_CARRY_FLAG));
    EXPECT_EQ(true, cpu.read_flag_register(CARRY_FLAG));
}

TEST(CPU_ALU, CPMatch) {
    uint8_t opcode = 0xB8;
    uint8_t val = 0x20;
    uint8_t n = 0x20;

    MemoryMap mem_map;
    
    CPU cpu(mem_map);

    cpu.write_register("A", val);
    cpu.write_register("B", n);

    EXPECT_EQ(val, cpu.read_register("A"));
    EXPECT_EQ(n, cpu.read_register("B"));

    cpu.decode_op(opcode);

    // Check Flag register
    EXPECT_EQ(true, cpu.read_flag_register(ZERO_FLAG));
    EXPECT_EQ(true, cpu.read_flag_register(SUBTRACT_FLAG));
    EXPECT_EQ(false, cpu.read_flag_register(HALF_CARRY_FLAG));
    EXPECT_EQ(false, cpu.read_flag_register(CARRY_FLAG));
}

TEST(CPU_ALU, INC) {
    uint8_t opcode = 0x3C;
    uint8_t val = 0x13;

    MemoryMap mem_map;
    
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

TEST(CPU_ALU, INCHalfCarry) {
    uint8_t opcode = 0x3C;
    uint8_t val = 0x1F;

    MemoryMap mem_map;
    
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

TEST(CPU_ALU, INC_HL) {
    uint8_t opcode = 0x34;
    uint16_t address = 0xA0FF;
    uint8_t val = 0x15;

    MemoryMap mem_map;
    
    CPU cpu(mem_map);

    cpu.write_register("HL", address);
    cpu.write_memory(val);

    EXPECT_EQ(address, cpu.read_register("HL"));
    EXPECT_EQ(val, cpu.read_memory());

    cpu.decode_op(opcode);

    EXPECT_EQ(val + 1, cpu.read_memory());
}

TEST(CPU_ALU, DEC) {
    uint8_t opcode = 0x3D;
    uint8_t val = 0x13;     // 0001 0011
    uint8_t result = 0x12;  // 0001 0010

    MemoryMap mem_map;
    
    CPU cpu(mem_map);

    cpu.write_register("A", val);

    EXPECT_EQ(val, cpu.read_register("A"));

    cpu.decode_op(opcode);

    EXPECT_EQ(result, cpu.read_register("A"));

    // Check Flag register
    EXPECT_EQ(false, cpu.read_flag_register(ZERO_FLAG));
    EXPECT_EQ(true, cpu.read_flag_register(SUBTRACT_FLAG));
    EXPECT_EQ(true, cpu.read_flag_register(HALF_CARRY_FLAG));
}

TEST(CPU_ALU, DECZero) {
    uint8_t opcode = 0x3D;
    uint8_t val = 0x01;     // 0000 0001
    uint8_t result = 0x00;  // 0000 0000

    MemoryMap mem_map;
    
    CPU cpu(mem_map);

    cpu.write_register("A", val);

    EXPECT_EQ(val, cpu.read_register("A"));

    cpu.decode_op(opcode);

    EXPECT_EQ(result, cpu.read_register("A"));

    // Check Flag register
    EXPECT_EQ(true, cpu.read_flag_register(ZERO_FLAG));
    EXPECT_EQ(true, cpu.read_flag_register(SUBTRACT_FLAG));
    EXPECT_EQ(true, cpu.read_flag_register(HALF_CARRY_FLAG));
}

TEST(CPU_ALU, DECHalfCarry) {
    uint8_t opcode = 0x3D;
    uint8_t val = 0x12;     // 0001 0010
    uint8_t result = 0x11;  // 0001 0001

    MemoryMap mem_map;
    
    CPU cpu(mem_map);

    cpu.write_register("A", val);

    EXPECT_EQ(val, cpu.read_register("A"));

    cpu.decode_op(opcode);

    EXPECT_EQ(result, cpu.read_register("A"));

    // Check Flag register
    EXPECT_EQ(false, cpu.read_flag_register(ZERO_FLAG));
    EXPECT_EQ(true, cpu.read_flag_register(SUBTRACT_FLAG));
    EXPECT_EQ(false, cpu.read_flag_register(HALF_CARRY_FLAG));
}

TEST(CPU_ALU, DEC_HL) {
    uint8_t opcode = 0x35;
    uint16_t address = 0xA0FF;
    uint16_t val = 0x13;    // 0001 0011
    uint8_t result = 0x12;  // 0001 0010

    MemoryMap mem_map;
    
    CPU cpu(mem_map);

    cpu.write_register("HL", address);
    cpu.write_memory(val);

    EXPECT_EQ(address, cpu.read_register("HL"));
    EXPECT_EQ(val, cpu.read_memory());

    cpu.decode_op(opcode);

    EXPECT_EQ(result, cpu.read_memory());
}

/****    16-Bit ALU    ****/
TEST(CPU_ALU_16Bit, ADD) {
    uint8_t opcode = 0x09;
    uint16_t val = 0x1020;
    uint16_t n = 0x0314;

    MemoryMap mem_map;
    
    CPU cpu(mem_map);

    cpu.write_register("HL", val);
    cpu.write_register("BC", n);
    
    EXPECT_EQ(val, cpu.read_register("HL"));
    EXPECT_EQ(n, cpu.read_register("BC"));

    cpu.decode_op(opcode);

    EXPECT_EQ(val + n, cpu.read_register("HL"));

    // Check Flag register
    EXPECT_EQ(false, cpu.read_flag_register(SUBTRACT_FLAG));
    EXPECT_EQ(false, cpu.read_flag_register(HALF_CARRY_FLAG));
    EXPECT_EQ(false, cpu.read_flag_register(CARRY_FLAG));
}

TEST(CPU_ALU_16Bit, ADDCarry) {
    uint8_t opcode = 0x09;
    uint16_t val = 0xFFFF;
    uint16_t n = 0x1000;

    MemoryMap mem_map;
    
    CPU cpu(mem_map);

    cpu.write_register("HL", val);
    cpu.write_register("BC", n);

    EXPECT_EQ(val, cpu.read_register("HL"));
    EXPECT_EQ(n, cpu.read_register("BC"));

    cpu.decode_op(opcode);

    EXPECT_EQ((val + n) & 0xFFFF, cpu.read_register("HL"));

    // Check Flag register
    EXPECT_EQ(false, cpu.read_flag_register(SUBTRACT_FLAG));
    EXPECT_EQ(false, cpu.read_flag_register(HALF_CARRY_FLAG));
    EXPECT_EQ(true, cpu.read_flag_register(CARRY_FLAG));
}

TEST(CPU_ALU_16Bit, ADDHalfCarry) {
    uint8_t opcode = 0x09;
    uint16_t val = 0x00F0;
    uint16_t n = 0x0010;

    MemoryMap mem_map;
    
    CPU cpu(mem_map);

    cpu.write_register("HL", val);
    cpu.write_register("BC", n);

    EXPECT_EQ(val, cpu.read_register("HL"));
    EXPECT_EQ(n, cpu.read_register("BC"));

    cpu.decode_op(opcode);

    EXPECT_EQ((val + n) & 0xFFFF, cpu.read_register("HL"));

    // Check Flag register
    EXPECT_EQ(false, cpu.read_flag_register(SUBTRACT_FLAG));
    EXPECT_EQ(true, cpu.read_flag_register(HALF_CARRY_FLAG));
    EXPECT_EQ(false, cpu.read_flag_register(CARRY_FLAG));
}

TEST(CPU_ALU_16Bit, ADD_SP) {
    uint8_t opcode = 0xE8;
    uint16_t val = 0x1020;
    uint8_t n = 0x03;

    uint16_t PC = 0xA000;

    MemoryMap mem_map;
    
    mem_map.write(PC, n);

    EXPECT_EQ(n, mem_map.read(PC));

    CPU cpu(mem_map);
    cpu.write_register("PC", PC);
    cpu.write_register("SP", val);

    EXPECT_EQ(PC, cpu.read_register("PC"));
    EXPECT_EQ(val, cpu.read_register("SP"));

    cpu.decode_op(opcode);

    EXPECT_EQ((val + n) & 0xFFFF, cpu.read_register("SP"));

    // Check Flag register
    EXPECT_EQ(false, cpu.read_flag_register(ZERO_FLAG));
    EXPECT_EQ(false, cpu.read_flag_register(SUBTRACT_FLAG));
    EXPECT_EQ(false, cpu.read_flag_register(HALF_CARRY_FLAG));
    EXPECT_EQ(false, cpu.read_flag_register(CARRY_FLAG));
}

TEST(CPU_ALU_16Bit, ADD_SP_Negative) {
    uint8_t opcode = 0xE8;
    uint16_t val = 0xFFFF;
    int8_t n = 0xFF;
    int signed_n = -1;

    uint16_t PC = 0xA000;

    MemoryMap mem_map;
    
    mem_map.write(PC, n);

    EXPECT_EQ((uint8_t)n, mem_map.read(PC));

    CPU cpu(mem_map);
    cpu.write_register("PC", PC);
    cpu.write_register("SP", val);

    EXPECT_EQ(PC, cpu.read_register("PC"));
    EXPECT_EQ(val, cpu.read_register("SP"));

    cpu.decode_op(opcode);

    EXPECT_EQ((val + signed_n) & 0xFFFF, cpu.read_register("SP"));

    // Check Flag register
    EXPECT_EQ(false, cpu.read_flag_register(ZERO_FLAG));
    EXPECT_EQ(false, cpu.read_flag_register(SUBTRACT_FLAG));
    EXPECT_EQ(true, cpu.read_flag_register(HALF_CARRY_FLAG));
    EXPECT_EQ(false, cpu.read_flag_register(CARRY_FLAG));
}

TEST(CPU_ALU_16Bit, ADD_SP_Carry) {
    uint8_t opcode = 0xE8;
    uint16_t val = 0xFFFF;
    int8_t n = 0x2F;

    uint16_t PC = 0xA000;

    MemoryMap mem_map;
    
    mem_map.write(PC, n);

    EXPECT_EQ(n, mem_map.read(PC));

    CPU cpu(mem_map);
    cpu.write_register("PC", PC);
    cpu.write_register("SP", val);

    EXPECT_EQ(PC, cpu.read_register("PC"));
    EXPECT_EQ(val, cpu.read_register("SP"));

    cpu.decode_op(opcode);

    EXPECT_EQ((val + n) & 0xFFFF, cpu.read_register("SP"));

    // Check Flag register
    EXPECT_EQ(false, cpu.read_flag_register(ZERO_FLAG));
    EXPECT_EQ(false, cpu.read_flag_register(SUBTRACT_FLAG));
    EXPECT_EQ(true, cpu.read_flag_register(HALF_CARRY_FLAG));
    EXPECT_EQ(true, cpu.read_flag_register(CARRY_FLAG));
}

TEST(CPU_ALU_16Bit, ADD_SP_HalfCarry) {
    uint8_t opcode = 0xE8;
    uint16_t val = 0x10FF;
    uint8_t n = 0x03;

    uint16_t PC = 0xA000;

    MemoryMap mem_map;
    
    mem_map.write(PC, n);

    EXPECT_EQ(n, mem_map.read(PC));

    CPU cpu(mem_map);
    cpu.write_register("PC", PC);
    cpu.write_register("SP", val);

    EXPECT_EQ(PC, cpu.read_register("PC"));
    EXPECT_EQ(val, cpu.read_register("SP"));

    cpu.decode_op(opcode);

    EXPECT_EQ((val + n) & 0xFFFF, cpu.read_register("SP"));

    // Check Flag register
    EXPECT_EQ(false, cpu.read_flag_register(ZERO_FLAG));
    EXPECT_EQ(false, cpu.read_flag_register(SUBTRACT_FLAG));
    EXPECT_EQ(true, cpu.read_flag_register(HALF_CARRY_FLAG));
    EXPECT_EQ(false, cpu.read_flag_register(CARRY_FLAG));
}

TEST(CPU_ALU_16Bit, INC) {
    uint8_t opcode = 0x03;
    uint16_t val = 0x1312;

    MemoryMap mem_map;
    
    CPU cpu(mem_map);

    cpu.write_register("BC", val);

    EXPECT_EQ(val, cpu.read_register("BC"));

    cpu.decode_op(opcode);

    EXPECT_EQ(val + 1, cpu.read_register("BC"));
}

TEST(CPU_ALU_16Bit, DEC_16) {
    uint8_t opcode = 0x0B;
    uint16_t val = 0x1312;

    MemoryMap mem_map;
    
    CPU cpu(mem_map);

    cpu.write_register("BC", val);

    EXPECT_EQ(val, cpu.read_register("BC"));

    cpu.decode_op(opcode);

    EXPECT_EQ(val - 1, cpu.read_register("BC"));
}