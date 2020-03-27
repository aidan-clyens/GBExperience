#include "gtest/gtest.h"
#include "cpu/cpu.h"


MemoryMap setup_cb_instruction(uint16_t PC, uint8_t opcode) {
    MemoryMap mem_map;
    mem_map.init_memory_map(nullptr);
    mem_map.write(PC, 0xCB);
    mem_map.write(PC + 1, opcode);

    EXPECT_EQ(0xCB, mem_map.read(PC));
    EXPECT_EQ(opcode, mem_map.read(PC + 1));

    return mem_map;
}


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

// RLC B
TEST(CPU_ROTATES, RLC_N) {
    uint16_t PC = 0xA000;
    uint8_t opcode = 0x00;
    uint8_t B = 0xC6;      // 1100 0110
    uint8_t result = 0x8D; // 1000 1101
    bool bit_7 = true;

    MemoryMap mem_map = setup_cb_instruction(PC, opcode);
    CPU cpu(mem_map);
    cpu.write_register("PC", PC);
    cpu.write_register("B", B);

    EXPECT_EQ(PC, cpu.read_register("PC"));
    EXPECT_EQ(B, cpu.read_register("B"));

    opcode = cpu.fetch_op();
    EXPECT_EQ(0xCB, opcode);

    cpu.decode_op(opcode);

    // Check value of B register
    EXPECT_EQ(result, cpu.read_register("B"));
    // Check carry flag for old bit 7
    EXPECT_EQ(bit_7, cpu.read_flag_register(CARRY_FLAG));
    // Check zero, subtract, and half-carry flags
    EXPECT_EQ(false, cpu.read_flag_register(ZERO_FLAG));
    EXPECT_EQ(false, cpu.read_flag_register(SUBTRACT_FLAG));
    EXPECT_EQ(false, cpu.read_flag_register(HALF_CARRY_FLAG));
}

// RLC (HL)
TEST(CPU_ROTATES, RLC_N_HL) {
    uint16_t PC = 0xA000;
    uint8_t opcode = 0x06;
    uint16_t HL = 0xA0FF;
    uint8_t value = 0xC6;      // 1100 0110
    uint8_t result = 0x8D; // 1000 1101
    bool bit_7 = true;

    MemoryMap mem_map = setup_cb_instruction(PC, opcode);
    CPU cpu(mem_map);
    cpu.write_register("PC", PC);
    cpu.write_register("HL", HL);
    cpu.write_memory(value);

    EXPECT_EQ(PC, cpu.read_register("PC"));
    EXPECT_EQ(HL, cpu.read_register("HL"));
    EXPECT_EQ(value, cpu.read_memory());

    opcode = cpu.fetch_op();
    EXPECT_EQ(0xCB, opcode);

    cpu.decode_op(opcode);

    // Check value of (HL) memory location
    EXPECT_EQ(result, cpu.read_memory());
    // Check carry flag for old bit 7
    EXPECT_EQ(bit_7, cpu.read_flag_register(CARRY_FLAG));
    // Check zero, subtract, and half-carry flags
    EXPECT_EQ(false, cpu.read_flag_register(ZERO_FLAG));
    EXPECT_EQ(false, cpu.read_flag_register(SUBTRACT_FLAG));
    EXPECT_EQ(false, cpu.read_flag_register(HALF_CARRY_FLAG));
}

// RL B
TEST(CPU_ROTATES, RL_N_CarryNotSet) {
    uint16_t PC = 0xA000;
    uint8_t opcode = 0x10;
    uint8_t B = 0xC6;       // 1100 0110
    uint8_t result = 0x8C;  // 1000 1100
    bool bit_7 = true;

    MemoryMap mem_map = setup_cb_instruction(PC, opcode);
    CPU cpu(mem_map);

    cpu.write_register("PC", PC);
    cpu.write_register("B", B);
    EXPECT_EQ(PC, cpu.read_register("PC"));
    EXPECT_EQ(B, cpu.read_register("B"));

    // Set carry flag to false
    cpu.set_flag_register(CARRY_FLAG, false);
    EXPECT_EQ(false, cpu.read_flag_register(CARRY_FLAG));

    opcode = cpu.fetch_op();
    EXPECT_EQ(0xCB, opcode);

    cpu.decode_op(opcode);

    // Check value of B register
    EXPECT_EQ(result, cpu.read_register("B"));
    // Check carry flag for old bit 7
    EXPECT_EQ(bit_7, cpu.read_flag_register(CARRY_FLAG));
    // Check zero, subtract, and half-carry flags
    EXPECT_EQ(false, cpu.read_flag_register(ZERO_FLAG));
    EXPECT_EQ(false, cpu.read_flag_register(SUBTRACT_FLAG));
    EXPECT_EQ(false, cpu.read_flag_register(HALF_CARRY_FLAG));
}

// RL B
TEST(CPU_ROTATES, RL_N_CarrySet) {
    uint16_t PC = 0xA000;
    uint8_t opcode = 0x10;
    uint8_t B = 0xC6;       // 1100 0110
    uint8_t result = 0x8D;  // 1000 1101
    bool bit_7 = true;

    MemoryMap mem_map = setup_cb_instruction(PC, opcode);
    CPU cpu(mem_map);

    cpu.write_register("PC", PC);
    cpu.write_register("B", B);
    EXPECT_EQ(PC, cpu.read_register("PC"));
    EXPECT_EQ(B, cpu.read_register("B"));

    // Set carry flag to true
    cpu.set_flag_register(CARRY_FLAG, true);
    EXPECT_EQ(true, cpu.read_flag_register(CARRY_FLAG));

    opcode = cpu.fetch_op();
    EXPECT_EQ(0xCB, opcode);

    cpu.decode_op(opcode);

    // Check value of B register
    EXPECT_EQ(result, cpu.read_register("B"));
    // Check carry flag for old bit 7
    EXPECT_EQ(bit_7, cpu.read_flag_register(CARRY_FLAG));
    // Check zero, subtract, and half-carry flags
    EXPECT_EQ(false, cpu.read_flag_register(ZERO_FLAG));
    EXPECT_EQ(false, cpu.read_flag_register(SUBTRACT_FLAG));
    EXPECT_EQ(false, cpu.read_flag_register(HALF_CARRY_FLAG));
}

// RRC B
TEST(CPU_ROTATES, RRC_N) {
    uint16_t PC = 0xA000;
    uint8_t opcode = 0x08;
    uint8_t B = 0xC5;       // 1100 0101
    uint8_t result = 0xE2;  // 1110 0010
    bool bit_0 = true;

    MemoryMap mem_map = setup_cb_instruction(PC, opcode);
    CPU cpu(mem_map);

    cpu.write_register("PC", PC);
    cpu.write_register("B", B);
    EXPECT_EQ(PC, cpu.read_register("PC"));
    EXPECT_EQ(B, cpu.read_register("B"));

    opcode = cpu.fetch_op();
    EXPECT_EQ(0xCB, opcode);

    cpu.decode_op(opcode);

    // Check value of B register
    EXPECT_EQ(result, cpu.read_register("B"));
    // Check carry flag for old bit 0
    EXPECT_EQ(bit_0, cpu.read_flag_register(CARRY_FLAG));
    // Check zero, subtract, and half-carry flags
    EXPECT_EQ(false, cpu.read_flag_register(ZERO_FLAG));
    EXPECT_EQ(false, cpu.read_flag_register(SUBTRACT_FLAG));
    EXPECT_EQ(false, cpu.read_flag_register(HALF_CARRY_FLAG));
}

// RRC (HL)
TEST(CPU_ROTATES, RRC_N_HL) {
    uint16_t PC = 0xA000;
    uint8_t opcode = 0x0E;
    uint16_t HL = 0xA0FF;
    uint8_t val = 0xC5;       // 1100 0101
    uint8_t result = 0xE2;  // 1110 0010
    bool bit_0 = true;

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

    // Check value of (HL) memory location
    EXPECT_EQ(result, cpu.read_memory());
    // Check carry flag for old bit 0
    EXPECT_EQ(bit_0, cpu.read_flag_register(CARRY_FLAG));
    // Check zero, subtract, and half-carry flags
    EXPECT_EQ(false, cpu.read_flag_register(ZERO_FLAG));
    EXPECT_EQ(false, cpu.read_flag_register(SUBTRACT_FLAG));
    EXPECT_EQ(false, cpu.read_flag_register(HALF_CARRY_FLAG));
}

// RR B
TEST(CPU_ROTATES, RR_N_CarryNotSet) {
    uint16_t PC = 0xA000;
    uint8_t opcode = 0x18;
    uint8_t B = 0xC5;      // 1100 0101
    uint8_t result = 0x62; // 0110 0010
    bool bit_0 = true;

    MemoryMap mem_map = setup_cb_instruction(PC, opcode);
    CPU cpu(mem_map);

    cpu.write_register("PC", PC);
    cpu.write_register("B", B);
    EXPECT_EQ(PC, cpu.read_register("PC"));
    EXPECT_EQ(B, cpu.read_register("B"));

    // Set carry flag to false
    cpu.set_flag_register(CARRY_FLAG, false);
    EXPECT_EQ(false, cpu.read_flag_register(CARRY_FLAG));

    opcode = cpu.fetch_op();
    EXPECT_EQ(0xCB, opcode);

    cpu.decode_op(opcode);

    // Check value of B register
    EXPECT_EQ(result, cpu.read_register("B"));
    // Check carry flag for old bit 7
    EXPECT_EQ(bit_0, cpu.read_flag_register(CARRY_FLAG));
    // Check zero, subtract, and half-carry flags
    EXPECT_EQ(false, cpu.read_flag_register(ZERO_FLAG));
    EXPECT_EQ(false, cpu.read_flag_register(SUBTRACT_FLAG));
    EXPECT_EQ(false, cpu.read_flag_register(HALF_CARRY_FLAG));
}

// RR B
TEST(CPU_ROTATES, RR_N_CarrySet) {
    uint16_t PC = 0xA000;
    uint8_t opcode = 0x18;
    uint8_t B = 0xC5;      // 1100 0101
    uint8_t result = 0xE2; // 1110 0010
    bool bit_0 = true;

    MemoryMap mem_map = setup_cb_instruction(PC, opcode);
    CPU cpu(mem_map);

    cpu.write_register("PC", PC);
    cpu.write_register("B", B);
    EXPECT_EQ(PC, cpu.read_register("PC"));
    EXPECT_EQ(B, cpu.read_register("B"));

    // Set carry flag to true
    cpu.set_flag_register(CARRY_FLAG, true);
    EXPECT_EQ(true, cpu.read_flag_register(CARRY_FLAG));

    opcode = cpu.fetch_op();
    EXPECT_EQ(0xCB, opcode);

    cpu.decode_op(opcode);

    // Check value of B register
    EXPECT_EQ(result, cpu.read_register("B"));
    // Check carry flag for old bit 7
    EXPECT_EQ(bit_0, cpu.read_flag_register(CARRY_FLAG));
    // Check zero, subtract, and half-carry flags
    EXPECT_EQ(false, cpu.read_flag_register(ZERO_FLAG));
    EXPECT_EQ(false, cpu.read_flag_register(SUBTRACT_FLAG));
    EXPECT_EQ(false, cpu.read_flag_register(HALF_CARRY_FLAG));
}