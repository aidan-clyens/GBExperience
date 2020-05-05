#include "gtest/gtest.h"


// BIT 2, B
TEST(CPU_BIT_OPS, BIT_B_R) {
    uint16_t PC = 0xA000;
    uint8_t opcode = 0x50;
    uint8_t B = 0xAB;     // 1010 1011
    bool is_zero = true;

    MemoryMap mem_map = setup_cb_instruction(PC, opcode);
    CPU cpu(mem_map);

    cpu.write_register("PC", PC);
    cpu.write_register("B", B);
    EXPECT_EQ(PC, cpu.read_register("PC"));
    EXPECT_EQ(B, cpu.read_register("B"));

    opcode = cpu.fetch_op();
    EXPECT_EQ(0xCB, opcode);

    cpu.decode_op(opcode);

    EXPECT_EQ(is_zero, cpu.read_flag_register(ZERO_FLAG));
    EXPECT_EQ(false, cpu.read_flag_register(SUBTRACT_FLAG));
    EXPECT_EQ(true, cpu.read_flag_register(HALF_CARRY_FLAG));
}

// BIT 1, (HL)
TEST(CPU_BIT_OPS, BIT_B_HL) {
    uint16_t PC = 0xA000;
    uint8_t opcode = 0x4E;
    uint16_t HL = 0xA0FF;
    uint8_t val = 0xAB;     // 1010 1011
    bool is_zero = false;

    MemoryMap mem_map = setup_cb_instruction(PC, opcode);
    CPU cpu(mem_map);

    cpu.write_register("PC", PC);
    cpu.write_register("HL", HL);
    cpu.write_memory(val);
    EXPECT_EQ(PC, cpu.read_register("PC"));
    EXPECT_EQ(HL, cpu.read_register("HL"));
    EXPECT_EQ(val, cpu.read_memory());

    opcode = cpu.fetch_op();
    EXPECT_EQ(0xCB, opcode);

    cpu.decode_op(opcode);

    EXPECT_EQ(is_zero, cpu.read_flag_register(ZERO_FLAG));
    EXPECT_EQ(false, cpu.read_flag_register(SUBTRACT_FLAG));
    EXPECT_EQ(true, cpu.read_flag_register(HALF_CARRY_FLAG));
}

// SET 2, B
TEST(CPU_BIT_OPS, SET_B_R) {
    uint16_t PC = 0xA000;
    uint8_t opcode = 0x50;
    uint8_t B = 0xAB; // 1010 1011
    uint8_t result = 0xAF;  // 1010 1111
    bool is_zero = true;

    MemoryMap mem_map = setup_cb_instruction(PC, opcode);
    CPU cpu(mem_map);

    cpu.write_register("PC", PC);
    cpu.write_register("B", B);
    EXPECT_EQ(PC, cpu.read_register("PC"));
    EXPECT_EQ(B, cpu.read_register("B"));

    opcode = cpu.fetch_op();
    EXPECT_EQ(0xCB, opcode);

    cpu.decode_op(opcode);
}

// SET 1, (HL)
TEST(CPU_BIT_OPS, SET_B_HL) {
    uint16_t PC = 0xA000;
    uint8_t opcode = 0xCE;
    uint16_t HL = 0xA0FF;
    uint8_t val = 0xA9;     // 1010 1001
    uint8_t result = 0xAB;      // 1010 1010

    MemoryMap mem_map = setup_cb_instruction(PC, opcode);
    CPU cpu(mem_map);

    cpu.write_register("PC", PC);
    cpu.write_register("HL", HL);
    cpu.write_memory(val);
    EXPECT_EQ(PC, cpu.read_register("PC"));
    EXPECT_EQ(HL, cpu.read_register("HL"));
    EXPECT_EQ(val, cpu.read_memory());

    opcode = cpu.fetch_op();
    EXPECT_EQ(0xCB, opcode);

    cpu.decode_op(opcode);

    EXPECT_EQ(result, cpu.read_memory());
}

// RES 1, B
TEST(CPU_BIT_OPS, RES_B_R) {
    uint16_t PC = 0xA000;
    uint8_t opcode = 0x88;
    uint8_t B = 0xAB; // 1010 1011
    uint8_t result = 0xA9;  // 1010 1001
    bool is_zero = true;

    MemoryMap mem_map = setup_cb_instruction(PC, opcode);
    CPU cpu(mem_map);

    cpu.write_register("PC", PC);
    cpu.write_register("B", B);
    EXPECT_EQ(PC, cpu.read_register("PC"));
    EXPECT_EQ(B, cpu.read_register("B"));

    opcode = cpu.fetch_op();
    EXPECT_EQ(0xCB, opcode);

    cpu.decode_op(opcode);
}

// RES 2, (HL)
TEST(CPU_BIT_OPS, RES_B_HL) {
    uint16_t PC = 0xA000;
    uint8_t opcode = 0x96;
    uint16_t HL = 0xA0FF;
    uint8_t val = 0xAF;     // 1010 1111
    uint8_t result = 0xAB;   // 1010 1011

    MemoryMap mem_map = setup_cb_instruction(PC, opcode);
    CPU cpu(mem_map);

    cpu.write_register("PC", PC);
    cpu.write_register("HL", HL);
    cpu.write_memory(val);
    EXPECT_EQ(PC, cpu.read_register("PC"));
    EXPECT_EQ(HL, cpu.read_register("HL"));
    EXPECT_EQ(val, cpu.read_memory());

    opcode = cpu.fetch_op();
    EXPECT_EQ(0xCB, opcode);

    cpu.decode_op(opcode);

    EXPECT_EQ(result, cpu.read_memory());
}