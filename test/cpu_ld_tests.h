#include "gtest/gtest.h"
#include "cpu/cpu.h"
#include "memory/memory_map.h"


// LD B, #
TEST(CPU_LD, LD_NN_N) {
    uint8_t opcode = 0x06;
    uint8_t val_1 = 0x20;
    uint8_t val_2 = 0xAC;
    uint16_t PC = 0xA0FF;

    MemoryMap mem_map;
    
    mem_map.write(PC, val_2);
    CPU cpu(mem_map);

    cpu.write_register("PC", PC);
    EXPECT_EQ(PC, cpu.read_register("PC"));
    
    cpu.write_register("B", val_1);
    EXPECT_EQ(val_1, cpu.read_register("B"));

    cpu.decode_op(opcode);

    EXPECT_EQ(val_2, cpu.read_register("B"));  
}

// LD A, E
TEST(CPU_LD, LD_R1_R2) {
    uint8_t opcode = 0x7B;
    uint8_t val_1 = 0x20;
    uint8_t val_2 = 0xAC;

    MemoryMap mem_map;
    
    CPU cpu(mem_map);

    cpu.write_register("A", val_1);
    cpu.write_register("E", val_2);

    EXPECT_EQ(val_1, cpu.read_register("A"));
    EXPECT_EQ(val_2, cpu.read_register("E"));

    cpu.decode_op(opcode);

    EXPECT_EQ(val_2, cpu.read_register("A"));
    EXPECT_EQ(val_2, cpu.read_register("E"));
}

// LD B, (HL)
TEST(CPU_LD, LD_R1_HL) {
    uint8_t opcode = 0x46;
    uint8_t val_1 = 0x20;
    uint8_t val_2 = 0xAC;
    uint16_t address = 0xA0FF;

    MemoryMap mem_map;
    
    CPU cpu(mem_map);

    cpu.write_register("B", val_1);
    cpu.write_register("HL", address);
    cpu.write_memory(val_2);

    EXPECT_EQ(val_1, cpu.read_register("B"));
    EXPECT_EQ(val_2, cpu.read_memory());

    cpu.decode_op(opcode);

    EXPECT_EQ(val_2, cpu.read_register("B"));
    EXPECT_EQ(val_2, cpu.read_memory());
}

// LD (HL), B
TEST(CPU_LD, LD_HL_R2) {
    uint8_t opcode = 0x70;
    uint8_t val_1 = 0x20;
    uint8_t val_2 = 0xAC;
    uint16_t address = 0xA0FF;

    MemoryMap mem_map;
    
    CPU cpu(mem_map);

    cpu.write_register("HL", address);
    cpu.write_memory(val_1);
    cpu.write_register("B", val_2);

    EXPECT_EQ(val_1, cpu.read_memory());
    EXPECT_EQ(val_2, cpu.read_register("B"));

    cpu.decode_op(opcode);

    EXPECT_EQ(val_2, cpu.read_memory());
    EXPECT_EQ(val_2, cpu.read_register("B"));
}

// LD (HL), #
TEST(CPU_LD, LD_HL_N) {
    uint8_t opcode = 0x36;
    uint8_t val_1 = 0x20;
    uint8_t val_2 = 0xAC;
    uint16_t address = 0xA0FF;
    uint16_t PC = 0xA200;

    MemoryMap mem_map;
    
    mem_map.write(PC, val_2);
    CPU cpu(mem_map);
    
    cpu.write_register("PC", PC);
    EXPECT_EQ(PC, cpu.read_register("PC"));

    cpu.write_register("HL", address);
    cpu.write_memory(val_1);

    EXPECT_EQ(val_1, cpu.read_memory());

    cpu.decode_op(opcode);

    EXPECT_EQ(val_2, cpu.read_memory());
}

// LD A, (BC)
TEST(CPU_LD, LD_A_BC) {
    uint8_t opcode = 0x0A;
    uint8_t val_1 = 0x20;
    uint8_t val_2 = 0xAC;
    uint16_t address = 0xA0FF;

    MemoryMap mem_map;
    
    CPU cpu(mem_map);

    cpu.write_register("A", val_1);
    cpu.write_register("BC", address);
    cpu.write_memory("BC", val_2);

    EXPECT_EQ(val_1, cpu.read_register("A"));
    EXPECT_EQ(val_2, cpu.read_memory("BC"));

    cpu.decode_op(opcode);

    EXPECT_EQ(val_2, cpu.read_register("A"));
    EXPECT_EQ(val_2, cpu.read_memory("BC"));
}

// LD A, (nn)
TEST(CPU_LD, LD_A_NN) {
    uint8_t opcode = 0xFA;
    uint8_t val_1 = 0x20;
    uint8_t val_2 = 0xAC;
    uint16_t address = 0xA0FF;
    uint16_t PC = 0xA200;

    MemoryMap mem_map;
    
    mem_map.write(PC, address & 0xFF);
    mem_map.write(PC + 1, address >> 8);
    mem_map.write(address, val_2);

    CPU cpu(mem_map);

    cpu.write_register("PC", PC);
    cpu.write_register("A", val_1);

    EXPECT_EQ(val_1, cpu.read_register("A"));

    cpu.decode_op(opcode);

    EXPECT_EQ(val_2, cpu.read_register("A"));
}

// LD A, #
TEST(CPU_LD, LD_A_N) {
    uint8_t opcode = 0x3E;
    uint8_t val_1 = 0x20;
    uint8_t val_2 = 0xAC;
    uint16_t PC = 0xA0FF;

    MemoryMap mem_map;
    
    mem_map.write(PC, val_2);
    CPU cpu(mem_map);

    cpu.write_register("PC", PC);
    EXPECT_EQ(PC, cpu.read_register("PC"));
    
    cpu.write_register("A", val_1);
    EXPECT_EQ(val_1, cpu.read_register("A"));

    cpu.decode_op(opcode);

    EXPECT_EQ(val_2, cpu.read_register("A"));
}

// LD B, A
TEST(CPU_LD, LD_N_A) {
    uint8_t opcode = 0x47;
    uint8_t val_1 = 0x20;
    uint8_t val_2 = 0xAC;

    MemoryMap mem_map;
    
    CPU cpu(mem_map);

    cpu.write_register("B", val_1);
    cpu.write_register("A", val_2);

    EXPECT_EQ(val_1, cpu.read_register("B"));
    EXPECT_EQ(val_2, cpu.read_register("A"));

    cpu.decode_op(opcode);

    EXPECT_EQ(val_2, cpu.read_register("B"));
    EXPECT_EQ(val_2, cpu.read_register("A"));
}

// LD (BC), A
TEST(CPU_LD, LD_BC_A) {
    uint8_t opcode = 0x02;
    uint8_t val_1 = 0x20;
    uint8_t val_2 = 0xAC;
    uint16_t address = 0xA0FF;

    MemoryMap mem_map;
    
    CPU cpu(mem_map);

    cpu.write_register("BC", address);
    cpu.write_memory("BC", val_1);
    cpu.write_register("A", val_2);

    EXPECT_EQ(val_1, cpu.read_memory("BC"));
    EXPECT_EQ(val_2, cpu.read_register("A"));

    cpu.decode_op(opcode);

    EXPECT_EQ(val_2, cpu.read_memory("BC"));
    EXPECT_EQ(val_2, cpu.read_register("A"));
}

// LD (nn), A
TEST(CPU_LD, LD_NN_A) {
    uint8_t opcode = 0xEA;
    uint8_t val_1 = 0x20;
    uint8_t val_2 = 0xAC;
    uint16_t address = 0xA0FF;
    uint16_t PC = 0xA200;

    MemoryMap mem_map;
    
    mem_map.write(PC, address & 0xFF);
    mem_map.write(PC + 1, address >> 8);
    mem_map.write(address, val_1);

    CPU cpu(mem_map);

    cpu.write_register("PC", PC);
    cpu.write_register("A", val_2);

    EXPECT_EQ(val_2, cpu.read_register("A"));

    cpu.decode_op(opcode);

    cpu.write_register("BC", address);
    EXPECT_EQ(val_2, cpu.read_memory("BC"));
}

// LD A, (C)
TEST(CPU_LD, LD_A_C) {
    // TODO Fix when memory-mapped I/O is implemented
    uint8_t opcode = 0xF2;
    uint8_t val_1 = 0x20;
    uint8_t val_2 = 0xAC;
    uint8_t val_C = 0x14;
    uint16_t address = 0xFF00 + val_C;

    MemoryMap mem_map;
    
    mem_map.write(address, val_2);
    
    EXPECT_EQ(val_2, mem_map.read(address));
    
    CPU cpu(mem_map);
    
    cpu.write_register("A", val_1);
    cpu.write_register("C", val_C);

    EXPECT_EQ(val_1, cpu.read_register("A"));
    EXPECT_EQ(val_C, cpu.read_register("C"));

    cpu.decode_op(opcode);

    EXPECT_EQ(val_2, cpu.read_register("A"));
}


// LD (C), A
TEST(CPU_LD, LD_C_A) {
    // TODO Fix when memory-mapped I/O is implemented
    uint8_t opcode = 0xE2;
    uint8_t val_1 = 0x20;
    uint8_t val_2 = 0xAC;
    uint8_t val_C = 0x14;
    uint16_t address = 0xFF00 + val_C;

    MemoryMap mem_map;
    
    mem_map.write(address, val_1);
    CPU cpu(mem_map);
    
    cpu.write_register("C", val_C);
    cpu.write_register("A", val_2);

    EXPECT_EQ(val_C, cpu.read_register("C"));
    EXPECT_EQ(val_2, cpu.read_register("A"));

    cpu.decode_op(opcode);

    cpu.write_register("DE", address);
    EXPECT_EQ(val_2, cpu.read_memory("DE"));
}

// LDD A, (HL)
TEST(CPU_LD, LDD_A_HL) {
    uint8_t opcode = 0x3A;
    uint8_t val_1 = 0x20;
    uint8_t val_2 = 0xAC;
    uint16_t address = 0xA0FF;

    MemoryMap mem_map;
    
    CPU cpu(mem_map);

    cpu.write_register("A", val_1);
    cpu.write_register("HL", address);
    cpu.write_memory("HL", val_2);

    EXPECT_EQ(val_1, cpu.read_register("A"));
    EXPECT_EQ(val_2, cpu.read_memory("HL"));

    cpu.decode_op(opcode);

    EXPECT_EQ(val_2, cpu.read_register("A"));

    EXPECT_EQ(address - 1, cpu.read_register("HL"));
}

// LDD (HL), A
TEST(CPU_LD, LDD_HL_A) {
    uint8_t opcode = 0x32;
    uint8_t val_1 = 0x20;
    uint8_t val_2 = 0xAC;
    uint16_t address = 0xA0FF;

    MemoryMap mem_map;
    
    CPU cpu(mem_map);

    cpu.write_register("HL", address);
    cpu.write_memory("HL", val_1);
    cpu.write_register("A", val_2);

    cpu.write_register("BC", address);

    EXPECT_EQ(val_1, cpu.read_memory("HL"));
    EXPECT_EQ(val_2, cpu.read_register("A"));

    cpu.decode_op(opcode);

    EXPECT_EQ(val_2, cpu.read_memory("BC"));
    EXPECT_EQ(val_2, cpu.read_register("A"));

    EXPECT_EQ(address - 1, cpu.read_register("HL"));
}

// LDI A, (HL)
TEST(CPU_LD, LDI_A_HL) {
    uint8_t opcode = 0x2A;
    uint8_t val_1 = 0x20;
    uint8_t val_2 = 0xAC;
    uint16_t address = 0xA0FF;

    MemoryMap mem_map;
    
    CPU cpu(mem_map);

    cpu.write_register("A", val_1);
    cpu.write_register("HL", address);
    cpu.write_memory("HL", val_2);

    EXPECT_EQ(val_1, cpu.read_register("A"));
    EXPECT_EQ(val_2, cpu.read_memory("HL"));

    cpu.decode_op(opcode);

    EXPECT_EQ(val_2, cpu.read_register("A"));

    EXPECT_EQ(address + 1, cpu.read_register("HL"));
}

// LDI (HL), A
TEST(CPU_LD, LDI_HL_A) {
    uint8_t opcode = 0x22;
    uint8_t val_1 = 0x20;
    uint8_t val_2 = 0xAC;
    uint16_t address = 0xA0FF;

    MemoryMap mem_map;
    
    CPU cpu(mem_map);

    cpu.write_register("HL", address);
    cpu.write_memory("HL", val_1);
    cpu.write_register("A", val_2);

    cpu.write_register("BC", address);

    EXPECT_EQ(val_1, cpu.read_memory("HL"));
    EXPECT_EQ(val_2, cpu.read_register("A"));

    cpu.decode_op(opcode);

    EXPECT_EQ(val_2, cpu.read_memory("BC"));
    EXPECT_EQ(val_2, cpu.read_register("A"));

    EXPECT_EQ(address + 1, cpu.read_register("HL"));
}

// LDH (n), A
TEST(CPU_LD, LD_n_A) {
    // TODO Fix when memory-mapped I/O is implemented
    uint8_t opcode = 0xE0;
    uint8_t val_1 = 0x20;
    uint8_t val_2 = 0xAC;
    uint8_t val_n = 0x14;
    uint16_t address = 0xFF00 + val_n;
    uint16_t PC = 0xA0FF;

    MemoryMap mem_map;
    
    mem_map.write(PC, val_n);
    mem_map.write(address, val_1);
    CPU cpu(mem_map);
    
    cpu.write_register("PC", PC);
    cpu.write_register("A", val_2);

    EXPECT_EQ(PC, cpu.read_register("PC"));
    EXPECT_EQ(val_2, cpu.read_register("A"));

    cpu.decode_op(opcode);

    cpu.write_register("DE", address);
    EXPECT_EQ(val_2, cpu.read_memory("DE"));
}

// LD A, (n)
TEST(CPU_LD, LD_A_n) {
    // TODO Fix when memory-mapped I/O is implemented
    uint8_t opcode = 0xF0;
    uint8_t val_1 = 0x20;
    uint8_t val_2 = 0xAC;
    uint8_t val_n = 0x14;
    uint16_t address = 0xFF00 + val_n;
    uint16_t PC = 0xA0FF;

    MemoryMap mem_map;
    
    mem_map.write(PC, val_n);
    mem_map.write(address, val_2);
    
    EXPECT_EQ(val_2, mem_map.read(address));
    
    CPU cpu(mem_map);
    
    cpu.write_register("PC", PC);
    cpu.write_register("A", val_1);

    EXPECT_EQ(PC, cpu.read_register("PC"));
    EXPECT_EQ(val_1, cpu.read_register("A"));

    cpu.decode_op(opcode);

    EXPECT_EQ(val_2, cpu.read_register("A"));
}

// LD BC, nn
TEST(CPU_LD_16Bit, LD_N_NN) {
    uint8_t opcode = 0x01;
    uint16_t val_1 = 0x1234;
    uint16_t val_2 = 0xABCD;
    uint16_t PC = 0xA200;

    MemoryMap mem_map;
    
    mem_map.write(PC, val_2 & 0xFF);
    mem_map.write(PC + 1, val_2 >> 8);
    CPU cpu(mem_map);

    cpu.write_register("PC", PC);
    EXPECT_EQ(PC, cpu.read_register("PC"));

    cpu.write_register("BC", val_1);

    EXPECT_EQ(val_1, cpu.read_register("BC"));

    cpu.decode_op(opcode);

    EXPECT_EQ(val_2, cpu.read_register("BC"));
}

// LD SP, HL
TEST(CPU_LD_16Bit, LD_SP_HL) {
    uint8_t opcode = 0xF9;
    uint16_t val_1 = 0x1234;
    uint16_t val_2 = 0xABCD;

    MemoryMap mem_map;
    
    CPU cpu(mem_map);

    cpu.write_register("SP", val_1);
    cpu.write_register("HL", val_2);

    EXPECT_EQ(val_1, cpu.read_register("SP"));
    EXPECT_EQ(val_2, cpu.read_register("HL"));

    cpu.decode_op(opcode);

    EXPECT_EQ(val_2, cpu.read_register("SP"));
}

// LDHL SP, n
TEST(CPU_LD_16Bit, LDHL_SP_N) {
    uint8_t opcode = 0xF8;
    uint16_t val_1 = 0x1234;
    uint16_t SP = 0xABFF;
    int8_t n = 0x02;
    uint16_t PC = 0xA0FF;

    MemoryMap mem_map;
    
    mem_map.write(PC, n);
    CPU cpu(mem_map);

    cpu.write_register("PC", PC);

    EXPECT_EQ(PC, cpu.read_register("PC"));

    cpu.write_register("HL", val_1);
    cpu.write_register("SP", SP);

    EXPECT_EQ(val_1, cpu.read_register("HL"));
    EXPECT_EQ(SP, cpu.read_register("SP"));

    cpu.decode_op(opcode);

    EXPECT_EQ((SP + n) & 0xFFFF, cpu.read_register("HL"));

    // Check flags
    EXPECT_EQ(false, cpu.read_flag_register(ZERO_FLAG));
    EXPECT_EQ(false, cpu.read_flag_register(SUBTRACT_FLAG));
    EXPECT_EQ(true, cpu.read_flag_register(HALF_CARRY_FLAG));
    EXPECT_EQ(false, cpu.read_flag_register(CARRY_FLAG));
}

// LDHL SP, n
TEST(CPU_LD_16Bit, LDHL_SP_N_Negative) {
    uint8_t opcode = 0xF8;
    uint16_t val_1 = 0x1234;
    uint16_t SP = 0xABFF;
    int8_t n = 0xF2;
    int signed_n = -14;
    uint16_t PC = 0xA0FF;

    MemoryMap mem_map;
    
    mem_map.write(PC, n);
    CPU cpu(mem_map);

    cpu.write_register("PC", PC);

    EXPECT_EQ(PC, cpu.read_register("PC"));

    cpu.write_register("HL", val_1);
    cpu.write_register("SP", SP);

    EXPECT_EQ(val_1, cpu.read_register("HL"));
    EXPECT_EQ(SP, cpu.read_register("SP"));

    cpu.decode_op(opcode);

    EXPECT_EQ((SP + signed_n) & 0xFFFF, cpu.read_register("HL"));

    // Check flags
    EXPECT_EQ(false, cpu.read_flag_register(ZERO_FLAG));
    EXPECT_EQ(false, cpu.read_flag_register(SUBTRACT_FLAG));
    EXPECT_EQ(true, cpu.read_flag_register(HALF_CARRY_FLAG));
    EXPECT_EQ(false, cpu.read_flag_register(CARRY_FLAG));
}

// LDHL SP, n
TEST(CPU_LD_16Bit, LDHL_SP_N_Carry) {
    uint8_t opcode = 0xF8;
    uint16_t val_1 = 0x1234;
    uint16_t SP = 0xFFFF;
    uint8_t n = 0x02;
    uint16_t PC = 0xA0FF;

    MemoryMap mem_map;
    
    mem_map.write(PC, n);
    CPU cpu(mem_map);

    cpu.write_register("PC", PC);

    EXPECT_EQ(PC, cpu.read_register("PC"));

    cpu.write_register("HL", val_1);
    cpu.write_register("SP", SP);

    EXPECT_EQ(val_1, cpu.read_register("HL"));
    EXPECT_EQ(SP, cpu.read_register("SP"));

    cpu.decode_op(opcode);

    EXPECT_EQ((SP + n) & 0xFFFF, cpu.read_register("HL"));

    // Check flags
    EXPECT_EQ(false, cpu.read_flag_register(ZERO_FLAG));
    EXPECT_EQ(false, cpu.read_flag_register(SUBTRACT_FLAG));
    EXPECT_EQ(true, cpu.read_flag_register(HALF_CARRY_FLAG));
    EXPECT_EQ(true, cpu.read_flag_register(CARRY_FLAG));
}

// LD (nn), SP
TEST(CPU_LD_16Bit, LD_NN_SP) {
    // TODO Learn how to implement this instruction

    EXPECT_TRUE(false);
}

// PUSH BC
TEST(CPU_LD_16Bit, LD_PUSH_NN) {
    uint8_t opcode = 0xC5;
    uint16_t val_1 = 0xABCD;
    uint16_t SP = 0xC000;

    MemoryMap mem_map;
    
    CPU cpu(mem_map);

    cpu.write_register("SP", SP);

    EXPECT_EQ(SP, cpu.read_register("SP"));

    cpu.write_register("BC", val_1);

    EXPECT_EQ(val_1, cpu.read_register("BC"));

    cpu.decode_op(opcode);

    EXPECT_EQ(SP - 2, cpu.read_register("SP"));

    cpu.write_register("DE", SP - 1);
    cpu.write_register("HL", SP - 2);

    EXPECT_EQ(val_1 & 0xFF, cpu.read_memory("DE"));
    EXPECT_EQ(val_1 >> 8, cpu.read_memory("HL"));
}

// POP BC
TEST(CPU_LD_16Bit, LD_POP_NN) {
    uint8_t opcode = 0xC5;
    uint16_t val_1 = 0xABCD;
    uint16_t SP = 0xC000;

    MemoryMap mem_map;
    
    CPU cpu(mem_map);

    cpu.write_register("SP", SP);

    EXPECT_EQ(SP, cpu.read_register("SP"));

    cpu.write_register("BC", val_1);

    EXPECT_EQ(val_1, cpu.read_register("BC"));

    cpu.decode_op(opcode);

    EXPECT_EQ(SP - 2, cpu.read_register("SP"));

    cpu.write_register("DE", SP - 1);
    cpu.write_register("HL", SP - 2);

    EXPECT_EQ(val_1 & 0xFF, cpu.read_memory("DE"));
    EXPECT_EQ(val_1 >> 8, cpu.read_memory("HL"));

    opcode = 0xD1;

    cpu.decode_op(opcode);

    EXPECT_EQ(val_1, cpu.read_register("DE"));
    EXPECT_EQ(SP, cpu.read_register("SP"));
}