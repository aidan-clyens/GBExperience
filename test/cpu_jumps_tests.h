#include "gtest/gtest.h"
#include "cpu/cpu.h"

MemoryMap setup_mem_map(uint16_t PC, uint16_t value) {
    MemoryMap mem_map;
    mem_map.init_memory_map(nullptr);
    mem_map.write(PC, (value & 0xFF));
    mem_map.write(PC + 1, (value >> 8));

    EXPECT_EQ((value & 0xFF), mem_map.read(PC));
    EXPECT_EQ((value >> 8), mem_map.read(PC + 1));

    return mem_map;
}


TEST(CPU_JUMP, JumpImmediateValue) {
    uint16_t PC = 0xA000;
    uint16_t value = 0xABCD;
    uint8_t opcode = 0xC3;

    MemoryMap mem_map = setup_mem_map(PC, value);

    CPU cpu(mem_map);
    cpu.write_register("PC", PC);

    cpu.decode_op(opcode);

    EXPECT_EQ(value, cpu.read_register("PC"));
}

TEST(CPU_JUMP, JumpImmediateValueNotZeroFlagFalse) {
    uint16_t PC = 0xA000;
    uint16_t value = 0xABCD;
    uint8_t opcode = 0xC2;

    MemoryMap mem_map = setup_mem_map(PC, value);

    CPU cpu(mem_map);
    cpu.write_register("PC", PC);
    cpu.set_flag_register(ZERO_FLAG, false);

    cpu.decode_op(opcode);

    EXPECT_EQ(value, cpu.read_register("PC"));
}

TEST(CPU_JUMP, JumpImmediateValueNotZeroFlagTrue) {
    uint16_t PC = 0xA000;
    uint16_t value = 0xABCD;
    uint8_t opcode = 0xC2;

    MemoryMap mem_map = setup_mem_map(PC, value);

    CPU cpu(mem_map);
    cpu.write_register("PC", PC);
    cpu.set_flag_register(ZERO_FLAG, true);

    cpu.decode_op(opcode);

    EXPECT_EQ(PC + 2, cpu.read_register("PC"));
}

TEST(CPU_JUMP, JumpImmediateValueZeroFlagFalse) {
    uint16_t PC = 0xA000;
    uint16_t value = 0xABCD;
    uint8_t opcode = 0xCA;

    MemoryMap mem_map = setup_mem_map(PC, value);

    CPU cpu(mem_map);
    cpu.write_register("PC", PC);
    cpu.set_flag_register(ZERO_FLAG, false);

    cpu.decode_op(opcode);

    EXPECT_EQ(PC + 2, cpu.read_register("PC"));
}

TEST(CPU_JUMP, JumpImmediateValueZeroFlagTrue) {
    uint16_t PC = 0xA000;
    uint16_t value = 0xABCD;
    uint8_t opcode = 0xCA;

    MemoryMap mem_map = setup_mem_map(PC, value);

    CPU cpu(mem_map);
    cpu.write_register("PC", PC);
    cpu.set_flag_register(ZERO_FLAG, true);

    cpu.decode_op(opcode);

    EXPECT_EQ(value, cpu.read_register("PC"));
}

TEST(CPU_JUMP, JumpImmediateValueNotCarryFlagFalse) {
    uint16_t PC = 0xA000;
    uint16_t value = 0xABCD;
    uint8_t opcode = 0xD2;

    MemoryMap mem_map = setup_mem_map(PC, value);

    CPU cpu(mem_map);
    cpu.write_register("PC", PC);
    cpu.set_flag_register(CARRY_FLAG, false);

    cpu.decode_op(opcode);

    EXPECT_EQ(value, cpu.read_register("PC"));
}

TEST(CPU_JUMP, JumpImmediateValueNotCarryFlagTrue) {
    uint16_t PC = 0xA000;
    uint16_t value = 0xABCD;
    uint8_t opcode = 0xD2;

    MemoryMap mem_map = setup_mem_map(PC, value);

    CPU cpu(mem_map);
    cpu.write_register("PC", PC);
    cpu.set_flag_register(CARRY_FLAG, true);

    cpu.decode_op(opcode);

    EXPECT_EQ(PC + 2, cpu.read_register("PC"));
}

TEST(CPU_JUMP, JumpImmediateValueCarryFlagFalse) {
    uint16_t PC = 0xA000;
    uint16_t value = 0xABCD;
    uint8_t opcode = 0xDA;

    MemoryMap mem_map = setup_mem_map(PC, value);

    CPU cpu(mem_map);
    cpu.write_register("PC", PC);
    cpu.set_flag_register(CARRY_FLAG, false);

    cpu.decode_op(opcode);

    EXPECT_EQ(PC + 2, cpu.read_register("PC"));
}

TEST(CPU_JUMP, JumpImmediateValueCarryFlagTrue) {
    uint16_t PC = 0xA000;
    uint16_t value = 0xABCD;
    uint8_t opcode = 0xDA;

    MemoryMap mem_map = setup_mem_map(PC, value);

    CPU cpu(mem_map);
    cpu.write_register("PC", PC);
    cpu.set_flag_register(CARRY_FLAG, true);

    cpu.decode_op(opcode);

    EXPECT_EQ(value, cpu.read_register("PC"));
}

TEST(CPU_JUMP, JumpHL) {
    uint16_t PC = 0xA000;
    uint16_t value = 0xABCD;
    uint8_t opcode = 0xE9;

    MemoryMap mem_map = setup_mem_map(PC, value);

    CPU cpu(mem_map);
    cpu.write_register("PC", PC);
    cpu.write_register("HL", value);

    cpu.decode_op(opcode);

    EXPECT_EQ(value, cpu.read_register("PC"));
}

TEST(CPU_JUMP, JumpAdd) {
    uint16_t PC = 0xA000;
    uint8_t value = 0xAB;
    uint8_t opcode = 0x18;

    MemoryMap mem_map = setup_mem_map(PC, value);

    CPU cpu(mem_map);
    cpu.write_register("PC", PC);
    cpu.write_register("HL", value);

    cpu.decode_op(opcode);

    EXPECT_EQ(PC + value, cpu.read_register("PC"));
}

TEST(CPU_JUMP, JumpAddNotZeroFlagFalse) {
    uint16_t PC = 0xA000;
    uint8_t value = 0xAB;
    uint8_t opcode = 0x20;

    MemoryMap mem_map = setup_mem_map(PC, value);

    CPU cpu(mem_map);
    cpu.write_register("PC", PC);
    cpu.set_flag_register(ZERO_FLAG, false);

    cpu.decode_op(opcode);

    EXPECT_EQ(PC + value, cpu.read_register("PC"));
}

TEST(CPU_JUMP, JumpAddNotZeroFlagTrue) {
    uint16_t PC = 0xA000;
    uint8_t value = 0xAB;
    uint8_t opcode = 0x20;

    MemoryMap mem_map = setup_mem_map(PC, value);

    CPU cpu(mem_map);
    cpu.write_register("PC", PC);
    cpu.set_flag_register(ZERO_FLAG, true);

    cpu.decode_op(opcode);

    EXPECT_EQ(PC + 1, cpu.read_register("PC"));
}

TEST(CPU_JUMP, JumpAddZeroFlagFalse) {
    uint16_t PC = 0xA000;
    uint8_t value = 0xAB;
    uint8_t opcode = 0x28;

    MemoryMap mem_map = setup_mem_map(PC, value);

    CPU cpu(mem_map);
    cpu.write_register("PC", PC);
    cpu.set_flag_register(ZERO_FLAG, false);

    cpu.decode_op(opcode);

    EXPECT_EQ(PC + 1, cpu.read_register("PC"));
}

TEST(CPU_JUMP, JumpAddZeroFlagTrue) {
    uint16_t PC = 0xA000;
    uint8_t value = 0xAB;
    uint8_t opcode = 0x28;

    MemoryMap mem_map = setup_mem_map(PC, value);

    CPU cpu(mem_map);
    cpu.write_register("PC", PC);
    cpu.set_flag_register(ZERO_FLAG, true);

    cpu.decode_op(opcode);

    EXPECT_EQ(PC + value, cpu.read_register("PC"));
}

TEST(CPU_JUMP, JumpAddNotCarryFlagFalse) {
    uint16_t PC = 0xA000;
    uint8_t value = 0xAB;
    uint8_t opcode = 0x30;

    MemoryMap mem_map = setup_mem_map(PC, value);

    CPU cpu(mem_map);
    cpu.write_register("PC", PC);
    cpu.set_flag_register(CARRY_FLAG, false);

    cpu.decode_op(opcode);

    EXPECT_EQ(PC + value, cpu.read_register("PC"));
}

TEST(CPU_JUMP, JumpAddNotCarryFlagTrue) {
    uint16_t PC = 0xA000;
    uint8_t value = 0xAB;
    uint8_t opcode = 0x30;

    MemoryMap mem_map = setup_mem_map(PC, value);

    CPU cpu(mem_map);
    cpu.write_register("PC", PC);
    cpu.set_flag_register(CARRY_FLAG, true);

    cpu.decode_op(opcode);

    EXPECT_EQ(PC + 1, cpu.read_register("PC"));
}

TEST(CPU_JUMP, JumpAddCarryFlagFalse) {
    uint16_t PC = 0xA000;
    uint8_t value = 0xAB;
    uint8_t opcode = 0x38;

    MemoryMap mem_map = setup_mem_map(PC, value);

    CPU cpu(mem_map);
    cpu.write_register("PC", PC);
    cpu.set_flag_register(CARRY_FLAG, false);

    cpu.decode_op(opcode);

    EXPECT_EQ(PC + 1, cpu.read_register("PC"));
}

TEST(CPU_JUMP, JumpAddCarryFlagTrue) {
    uint16_t PC = 0xA000;
    uint8_t value = 0xAB;
    uint8_t opcode = 0x38;

    MemoryMap mem_map = setup_mem_map(PC, value);

    CPU cpu(mem_map);
    cpu.write_register("PC", PC);
    cpu.set_flag_register(CARRY_FLAG, true);

    cpu.decode_op(opcode);

    EXPECT_EQ(PC + value, cpu.read_register("PC"));
}

// RST 10
TEST(CPU_RST, RST) {
    uint8_t opcode = 0xD7;
    uint16_t PC = 0xA000;
    uint16_t SP = 0xC000;

    MemoryMap mem_map;
    mem_map.init_memory_map(nullptr);
    CPU cpu(mem_map);

    cpu.write_register("PC", PC);
    cpu.write_register("SP", SP);
    EXPECT_EQ(PC, cpu.read_register("PC"));
    EXPECT_EQ(SP, cpu.read_register("SP"));

    cpu.decode_op(opcode);

    EXPECT_EQ(SP - 2, cpu.read_register("SP"));

    cpu.write_register("DE", SP - 1);
    cpu.write_register("HL", SP - 2);

    EXPECT_EQ(PC & 0xFF, cpu.read_memory("DE"));
    EXPECT_EQ(PC >> 8, cpu.read_memory("HL"));
}

// CALL nn
TEST(CPU_CALL, CALL_NN) {
    uint8_t opcode = 0xCD;
    uint16_t PC = 0xA000;
    uint16_t SP = 0xC000;
    uint16_t val = 0xA0FF;

    MemoryMap mem_map;
    mem_map.init_memory_map(nullptr);
    mem_map.write(PC, val & 0xFF);
    mem_map.write(PC + 1, val >> 8);
    CPU cpu(mem_map);

    cpu.write_register("PC", PC);
    cpu.write_register("SP", SP);

    EXPECT_EQ(PC, cpu.read_register("PC"));
    EXPECT_EQ(SP, cpu.read_register("SP"));

    cpu.decode_op(opcode);

    EXPECT_EQ(SP - 2, cpu.read_register("SP"));

    cpu.write_register("DE", SP - 1);
    cpu.write_register("HL", SP - 2);

    EXPECT_EQ(PC & 0xFF, cpu.read_memory("DE"));
    EXPECT_EQ(PC >> 8, cpu.read_memory("HL"));

    EXPECT_EQ(val, cpu.read_register("PC"));
}

// CALL cc, nn
TEST(CPU_CALL, CALL_CC_NN_NoFlags) {
    uint8_t opcode = 0xDC;
    uint16_t PC = 0xA000;
    uint16_t SP = 0xC000;
    uint16_t val = 0xA0FF;

    MemoryMap mem_map;
    mem_map.init_memory_map(nullptr);
    mem_map.write(PC, val & 0xFF);
    mem_map.write(PC + 1, val >> 8);
    CPU cpu(mem_map);

    cpu.write_register("PC", PC);
    cpu.write_register("SP", SP);

    EXPECT_EQ(PC, cpu.read_register("PC"));
    EXPECT_EQ(SP, cpu.read_register("SP"));

    cpu.set_flag_register(CARRY_FLAG, false);

    EXPECT_EQ(false, cpu.read_flag_register(CARRY_FLAG));

    cpu.decode_op(opcode);

    EXPECT_EQ(PC + 2, cpu.read_register("PC"));
}

// CALL cc, nn
TEST(CPU_CALL, CALL_CC_NN_Carry) {
    uint8_t opcode = 0xDC;
    uint16_t PC = 0xA000;
    uint16_t SP = 0xC000;
    uint16_t val = 0xA0FF;

    MemoryMap mem_map;
    mem_map.init_memory_map(nullptr);
    mem_map.write(PC, val & 0xFF);
    mem_map.write(PC + 1, val >> 8);
    CPU cpu(mem_map);

    cpu.write_register("PC", PC);
    cpu.write_register("SP", SP);

    EXPECT_EQ(PC, cpu.read_register("PC"));
    EXPECT_EQ(SP, cpu.read_register("SP"));

    cpu.set_flag_register(CARRY_FLAG, true);

    EXPECT_EQ(true, cpu.read_flag_register(CARRY_FLAG));

    cpu.decode_op(opcode);

    EXPECT_EQ(SP - 2, cpu.read_register("SP"));

    cpu.write_register("DE", SP - 1);
    cpu.write_register("HL", SP - 2);

    EXPECT_EQ(PC & 0xFF, cpu.read_memory("DE"));
    EXPECT_EQ(PC >> 8, cpu.read_memory("HL"));

    EXPECT_EQ(val, cpu.read_register("PC"));
} 