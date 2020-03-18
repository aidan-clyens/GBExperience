#include "gtest/gtest.h"
#include "cpu/cpu.h"


// RLCA
TEST(CPU_ROTATES, RLCA) {
    uint8_t opcode = 0x07;
    uint8_t A = 0xC6;       // 1100 0110
    uint8_t result = 0x8D;  // 1000 1101
    bool bit_7 = true;

    MemoryMap mem_map;
    mem_map.init_memory_map(nullptr);
    CPU cpu(mem_map);

    cpu.write_register("A", A);
    EXPECT_EQ(A, cpu.read_register("A"));

    cpu.decode_op(opcode);

    // Check value of A register
    EXPECT_EQ(result, cpu.read_register("A"));
    // Check carry flag for old bit 7
    EXPECT_EQ(bit_7, cpu.read_flag_register(CARRY_FLAG));
    // Check zero, subtract, and half-carry flags
    EXPECT_EQ(false, cpu.read_flag_register(ZERO_FLAG));
    EXPECT_EQ(false, cpu.read_flag_register(SUBTRACT_FLAG));
    EXPECT_EQ(false, cpu.read_flag_register(HALF_CARRY_FLAG));
}

// RLA
TEST(CPU_ROTATES, RLA_CarryNotSet) {
    uint8_t opcode = 0x17;
    uint8_t A = 0xC6;       // 1100 0110
    uint8_t result = 0x8C;  // 1000 1100
    bool bit_7 = true;

    MemoryMap mem_map;
    mem_map.init_memory_map(nullptr);
    CPU cpu(mem_map);

    cpu.write_register("A", A);
    EXPECT_EQ(A, cpu.read_register("A"));

    // Set carry flag to false
    cpu.set_flag_register(CARRY_FLAG, false);
    EXPECT_EQ(false, cpu.read_flag_register(CARRY_FLAG));

    cpu.decode_op(opcode);

    // Check value of A register
    EXPECT_EQ(result, cpu.read_register("A"));
    // Check carry flag for old bit 7
    EXPECT_EQ(bit_7, cpu.read_flag_register(CARRY_FLAG));
    // Check zero, subtract, and half-carry flags
    EXPECT_EQ(false, cpu.read_flag_register(ZERO_FLAG));
    EXPECT_EQ(false, cpu.read_flag_register(SUBTRACT_FLAG));
    EXPECT_EQ(false, cpu.read_flag_register(HALF_CARRY_FLAG));
}

// RLA
TEST(CPU_ROTATES, RLA_CarrySet) {
    uint8_t opcode = 0x17;
    uint8_t A = 0xC6;       // 1100 0110
    uint8_t result = 0x8D;  // 1000 1101
    bool bit_7 = true;

    MemoryMap mem_map;
    mem_map.init_memory_map(nullptr);
    CPU cpu(mem_map);

    cpu.write_register("A", A);
    EXPECT_EQ(A, cpu.read_register("A"));

    // Set carry flag to true
    cpu.set_flag_register(CARRY_FLAG, true);
    EXPECT_EQ(true, cpu.read_flag_register(CARRY_FLAG));

    cpu.decode_op(opcode);

    // Check value of A register
    EXPECT_EQ(result, cpu.read_register("A"));
    // Check carry flag for old bit 7
    EXPECT_EQ(bit_7, cpu.read_flag_register(CARRY_FLAG));
    // Check zero, subtract, and half-carry flags
    EXPECT_EQ(false, cpu.read_flag_register(ZERO_FLAG));
    EXPECT_EQ(false, cpu.read_flag_register(SUBTRACT_FLAG));
    EXPECT_EQ(false, cpu.read_flag_register(HALF_CARRY_FLAG));
}

// RRCA
TEST(CPU_ROTATES, RRCA) {
    uint8_t opcode = 0x0F;
    uint8_t A = 0xC5;       // 1100 0101
    uint8_t result = 0xE2;  // 1110 0010
    bool bit_0 = true;

    MemoryMap mem_map;
    mem_map.init_memory_map(nullptr);
    CPU cpu(mem_map);

    cpu.write_register("A", A);
    EXPECT_EQ(A, cpu.read_register("A"));

    cpu.decode_op(opcode);

    // Check value of A register
    EXPECT_EQ(result, cpu.read_register("A"));
    // Check carry flag for old bit 0
    EXPECT_EQ(bit_0, cpu.read_flag_register(CARRY_FLAG));
    // Check zero, subtract, and half-carry flags
    EXPECT_EQ(false, cpu.read_flag_register(ZERO_FLAG));
    EXPECT_EQ(false, cpu.read_flag_register(SUBTRACT_FLAG));
    EXPECT_EQ(false, cpu.read_flag_register(HALF_CARRY_FLAG));
}

// RRA
TEST(CPU_ROTATES, RRA_CarryNotSet) {
    uint8_t opcode = 0x1F;
    uint8_t A = 0xC5;       // 1100 0101
    uint8_t result = 0x62;  // 0110 0010
    bool bit_0 = true;

    MemoryMap mem_map;
    mem_map.init_memory_map(nullptr);
    CPU cpu(mem_map);

    cpu.write_register("A", A);
    EXPECT_EQ(A, cpu.read_register("A"));

    // Set carry flag to false
    cpu.set_flag_register(CARRY_FLAG, false);
    EXPECT_EQ(false, cpu.read_flag_register(CARRY_FLAG));

    cpu.decode_op(opcode);

    // Check value of A register
    EXPECT_EQ(result, cpu.read_register("A"));
    // Check carry flag for old bit 0
    EXPECT_EQ(bit_0, cpu.read_flag_register(CARRY_FLAG));
    // Check zero, subtract, and half-carry flags
    EXPECT_EQ(false, cpu.read_flag_register(ZERO_FLAG));
    EXPECT_EQ(false, cpu.read_flag_register(SUBTRACT_FLAG));
    EXPECT_EQ(false, cpu.read_flag_register(HALF_CARRY_FLAG));
}

// RRA
TEST(CPU_ROTATES, RRA_CarrySet) {
    uint8_t opcode = 0x1F;
    uint8_t A = 0xC5;       // 1100 0101
    uint8_t result = 0xE2;  // 1110 0010
    bool bit_0 = true;

    MemoryMap mem_map;
    mem_map.init_memory_map(nullptr);
    CPU cpu(mem_map);

    cpu.write_register("A", A);
    EXPECT_EQ(A, cpu.read_register("A"));

    // Set carry flag to true
    cpu.set_flag_register(CARRY_FLAG, true);
    EXPECT_EQ(true, cpu.read_flag_register(CARRY_FLAG));

    cpu.decode_op(opcode);

    // Check value of A register
    EXPECT_EQ(result, cpu.read_register("A"));
    // Check carry flag for old bit 0
    EXPECT_EQ(bit_0, cpu.read_flag_register(CARRY_FLAG));
    // Check zero, subtract, and half-carry flags
    EXPECT_EQ(false, cpu.read_flag_register(ZERO_FLAG));
    EXPECT_EQ(false, cpu.read_flag_register(SUBTRACT_FLAG));
    EXPECT_EQ(false, cpu.read_flag_register(HALF_CARRY_FLAG));
}