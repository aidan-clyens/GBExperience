#include "gtest/gtest.h"


// LD B, #
TEST(CPU_LD, LD_NN_N) {
    uint8_t opcode = 0x06;
    uint8_t val_1 = 0x20;
    uint8_t val_2 = 0xAC;
    uint16_t PC = 0xFF80;

    MemoryMap mem_map;
    
    mem_map.write(PC, val_2);
    CPU cpu(mem_map);

    cpu.write_register(REG_PC, PC);
    EXPECT_EQ(PC, cpu.read_register(REG_PC));
    
    cpu.write_register(REG_B, val_1);
    EXPECT_EQ(val_1, cpu.read_register(REG_B));

    cpu.decode_op(opcode);

    EXPECT_EQ(val_2, cpu.read_register(REG_B));  
}

// LD A, E
TEST(CPU_LD, LD_R1_R2) {
    uint8_t opcode = 0x7B;
    uint8_t val_1 = 0x20;
    uint8_t val_2 = 0xAC;

    MemoryMap mem_map;
    
    CPU cpu(mem_map);

    cpu.write_register(REG_A, val_1);
    cpu.write_register(REG_E, val_2);

    EXPECT_EQ(val_1, cpu.read_register(REG_A));
    EXPECT_EQ(val_2, cpu.read_register(REG_E));

    cpu.decode_op(opcode);

    EXPECT_EQ(val_2, cpu.read_register(REG_A));
    EXPECT_EQ(val_2, cpu.read_register(REG_E));
}

// LD B, (HL)
TEST(CPU_LD, LD_R1_HL) {
    uint8_t opcode = 0x46;
    uint8_t val_1 = 0x20;
    uint8_t val_2 = 0xAC;
    uint16_t address = 0xFF80;

    MemoryMap mem_map;
    
    CPU cpu(mem_map);

    cpu.write_register(REG_B, val_1);
    cpu.write_register(REG_HL, address);
    cpu.write_memory(val_2);

    EXPECT_EQ(val_1, cpu.read_register(REG_B));
    EXPECT_EQ(val_2, cpu.read_memory());

    cpu.decode_op(opcode);

    EXPECT_EQ(val_2, cpu.read_register(REG_B));
    EXPECT_EQ(val_2, cpu.read_memory());
}

// LD (HL), B
TEST(CPU_LD, LD_HL_R2) {
    uint8_t opcode = 0x70;
    uint8_t val_1 = 0x20;
    uint8_t val_2 = 0xAC;
    uint16_t address = 0xFF80;

    MemoryMap mem_map;
    
    CPU cpu(mem_map);

    cpu.write_register(REG_HL, address);
    cpu.write_memory(val_1);
    cpu.write_register(REG_B, val_2);

    EXPECT_EQ(val_1, cpu.read_memory());
    EXPECT_EQ(val_2, cpu.read_register(REG_B));

    cpu.decode_op(opcode);

    EXPECT_EQ(val_2, cpu.read_memory());
    EXPECT_EQ(val_2, cpu.read_register(REG_B));
}

// LD (HL), #
TEST(CPU_LD, LD_HL_N) {
    uint8_t opcode = 0x36;
    uint8_t val_1 = 0x20;
    uint8_t val_2 = 0xAC;
    uint16_t address = 0xFF80;
    uint16_t PC = 0xFFF0;

    MemoryMap mem_map;
    
    mem_map.write(PC, val_2);
    CPU cpu(mem_map);
    
    cpu.write_register(REG_PC, PC);
    EXPECT_EQ(PC, cpu.read_register(REG_PC));

    cpu.write_register(REG_HL, address);
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
    uint16_t address = 0xFF80;

    MemoryMap mem_map;
    
    CPU cpu(mem_map);

    cpu.write_register(REG_A, val_1);
    cpu.write_register(REG_BC, address);
    cpu.write_memory(REG_BC, val_2);

    EXPECT_EQ(val_1, cpu.read_register(REG_A));
    EXPECT_EQ(val_2, cpu.read_memory(REG_BC));

    cpu.decode_op(opcode);

    EXPECT_EQ(val_2, cpu.read_register(REG_A));
    EXPECT_EQ(val_2, cpu.read_memory(REG_BC));
}

// LD A, (nn)
TEST(CPU_LD, LD_A_NN) {
    uint8_t opcode = 0xFA;
    uint8_t val_1 = 0x20;
    uint8_t val_2 = 0xAC;
    uint16_t address = 0xFF80;
    uint16_t PC = 0xFFF0;

    MemoryMap mem_map;
    
    mem_map.write(PC, address & 0xFF);
    mem_map.write(PC + 1, address >> 8);
    mem_map.write(address, val_2);

    CPU cpu(mem_map);

    cpu.write_register(REG_PC, PC);
    cpu.write_register(REG_A, val_1);

    EXPECT_EQ(val_1, cpu.read_register(REG_A));

    cpu.decode_op(opcode);

    EXPECT_EQ(val_2, cpu.read_register(REG_A));
}

// LD A, #
TEST(CPU_LD, LD_A_N) {
    uint8_t opcode = 0x3E;
    uint8_t val_1 = 0x20;
    uint8_t val_2 = 0xAC;
    uint16_t PC = 0xFF80;

    MemoryMap mem_map;
    
    mem_map.write(PC, val_2);
    CPU cpu(mem_map);

    cpu.write_register(REG_PC, PC);
    EXPECT_EQ(PC, cpu.read_register(REG_PC));
    
    cpu.write_register(REG_A, val_1);
    EXPECT_EQ(val_1, cpu.read_register(REG_A));

    cpu.decode_op(opcode);

    EXPECT_EQ(val_2, cpu.read_register(REG_A));
}

// LD B, A
TEST(CPU_LD, LD_N_A) {
    uint8_t opcode = 0x47;
    uint8_t val_1 = 0x20;
    uint8_t val_2 = 0xAC;

    MemoryMap mem_map;
    
    CPU cpu(mem_map);

    cpu.write_register(REG_B, val_1);
    cpu.write_register(REG_A, val_2);

    EXPECT_EQ(val_1, cpu.read_register(REG_B));
    EXPECT_EQ(val_2, cpu.read_register(REG_A));

    cpu.decode_op(opcode);

    EXPECT_EQ(val_2, cpu.read_register(REG_B));
    EXPECT_EQ(val_2, cpu.read_register(REG_A));
}

// LD (BC), A
TEST(CPU_LD, LD_BC_A) {
    uint8_t opcode = 0x02;
    uint8_t val_1 = 0x20;
    uint8_t val_2 = 0xAC;
    uint16_t address = 0xFF80;

    MemoryMap mem_map;
    
    CPU cpu(mem_map);

    cpu.write_register(REG_BC, address);
    cpu.write_memory(REG_BC, val_1);
    cpu.write_register(REG_A, val_2);

    EXPECT_EQ(val_1, cpu.read_memory(REG_BC));
    EXPECT_EQ(val_2, cpu.read_register(REG_A));

    cpu.decode_op(opcode);

    EXPECT_EQ(val_2, cpu.read_memory(REG_BC));
    EXPECT_EQ(val_2, cpu.read_register(REG_A));
}

// LD (nn), A
TEST(CPU_LD, LD_NN_A) {
    uint8_t opcode = 0xEA;
    uint8_t val_1 = 0x20;
    uint8_t val_2 = 0xAC;
    uint16_t address = 0xFF80;
    uint16_t PC = 0xFFF0;

    MemoryMap mem_map;
    
    mem_map.write(PC, address & 0xFF);
    mem_map.write(PC + 1, address >> 8);
    mem_map.write(address, val_1);

    CPU cpu(mem_map);

    cpu.write_register(REG_PC, PC);
    cpu.write_register(REG_A, val_2);

    EXPECT_EQ(val_2, cpu.read_register(REG_A));

    cpu.decode_op(opcode);

    cpu.write_register(REG_BC, address);
    EXPECT_EQ(val_2, cpu.read_memory(REG_BC));
}

// LD A, (C)
TEST(CPU_LD, LD_A_C) {
    uint8_t opcode = 0xF2;
    IORegisters_t io_reg = STAT;
    uint8_t val_C = (uint16_t)io_reg - 0xFF00;
    uint8_t data = 0xAB;

    MemoryMap mem_map;
    CPU cpu(mem_map);
    cpu.write_register(REG_C, val_C);
    cpu.write_register(REG_A, 0x0);
    cpu.write_register(REG_HL, io_reg);
    EXPECT_EQ(val_C, cpu.read_register(REG_C));
    EXPECT_EQ(0x0, cpu.read_register(REG_A));
    EXPECT_EQ(io_reg, cpu.read_register(REG_HL));

    cpu.write_io_register(io_reg, data);
    EXPECT_EQ(data, cpu.read_io_register(io_reg));
    EXPECT_EQ(data, cpu.read_memory());

    cpu.decode_op(opcode);

    EXPECT_EQ(data, cpu.read_register(REG_A));
}


// LD (C), A
TEST(CPU_LD, LD_C_A) {
    uint8_t opcode = 0xE2;
    IORegisters_t io_reg = STAT;
    uint8_t val_C = (uint16_t)io_reg - 0xFF00;
    uint8_t data = 0xAB;

    MemoryMap mem_map;
    CPU cpu(mem_map);
    cpu.write_register(REG_C, val_C);
    cpu.write_register(REG_A, data);
    cpu.write_register(REG_HL, io_reg);
    EXPECT_EQ(val_C, cpu.read_register(REG_C));
    EXPECT_EQ(data, cpu.read_register(REG_A));
    EXPECT_EQ(io_reg, cpu.read_register(REG_HL));

    cpu.write_io_register(io_reg, 0x0);
    EXPECT_EQ(0x0, cpu.read_io_register(io_reg));
    EXPECT_EQ(0x0, cpu.read_memory());

    cpu.decode_op(opcode);

    EXPECT_EQ(data, cpu.read_io_register(io_reg));
    EXPECT_EQ(data, cpu.read_memory());
}

// LDD A, (HL)
TEST(CPU_LD, LDD_A_HL) {
    uint8_t opcode = 0x3A;
    uint8_t val_1 = 0x20;
    uint8_t val_2 = 0xAC;
    uint16_t address = 0xFF80;

    MemoryMap mem_map;
    
    CPU cpu(mem_map);

    cpu.write_register(REG_A, val_1);
    cpu.write_register(REG_HL, address);
    cpu.write_memory(REG_HL, val_2);

    EXPECT_EQ(val_1, cpu.read_register(REG_A));
    EXPECT_EQ(val_2, cpu.read_memory(REG_HL));

    cpu.decode_op(opcode);

    EXPECT_EQ(val_2, cpu.read_register(REG_A));

    EXPECT_EQ(address - 1, cpu.read_register(REG_HL));
}

// LDD (HL), A
TEST(CPU_LD, LDD_HL_A) {
    uint8_t opcode = 0x32;
    uint8_t val_1 = 0x20;
    uint8_t val_2 = 0xAC;
    uint16_t address = 0xFF80;

    MemoryMap mem_map;
    
    CPU cpu(mem_map);

    cpu.write_register(REG_HL, address);
    cpu.write_memory(REG_HL, val_1);
    cpu.write_register(REG_A, val_2);

    cpu.write_register(REG_BC, address);

    EXPECT_EQ(val_1, cpu.read_memory(REG_HL));
    EXPECT_EQ(val_2, cpu.read_register(REG_A));

    cpu.decode_op(opcode);

    EXPECT_EQ(val_2, cpu.read_memory(REG_BC));
    EXPECT_EQ(val_2, cpu.read_register(REG_A));

    EXPECT_EQ(address - 1, cpu.read_register(REG_HL));
}

// LDI A, (HL)
TEST(CPU_LD, LDI_A_HL) {
    uint8_t opcode = 0x2A;
    uint8_t val_1 = 0x20;
    uint8_t val_2 = 0xAC;
    uint16_t address = 0xFF80;

    MemoryMap mem_map;
    
    CPU cpu(mem_map);

    cpu.write_register(REG_A, val_1);
    cpu.write_register(REG_HL, address);
    cpu.write_memory(REG_HL, val_2);

    EXPECT_EQ(val_1, cpu.read_register(REG_A));
    EXPECT_EQ(val_2, cpu.read_memory(REG_HL));

    cpu.decode_op(opcode);

    EXPECT_EQ(val_2, cpu.read_register(REG_A));

    EXPECT_EQ(address + 1, cpu.read_register(REG_HL));
}

// LDI (HL), A
TEST(CPU_LD, LDI_HL_A) {
    uint8_t opcode = 0x22;
    uint8_t val_1 = 0x20;
    uint8_t val_2 = 0xAC;
    uint16_t address = 0xFF80;

    MemoryMap mem_map;
    
    CPU cpu(mem_map);

    cpu.write_register(REG_HL, address);
    cpu.write_memory(REG_HL, val_1);
    cpu.write_register(REG_A, val_2);

    cpu.write_register(REG_BC, address);

    EXPECT_EQ(val_1, cpu.read_memory(REG_HL));
    EXPECT_EQ(val_2, cpu.read_register(REG_A));

    cpu.decode_op(opcode);

    EXPECT_EQ(val_2, cpu.read_memory(REG_BC));
    EXPECT_EQ(val_2, cpu.read_register(REG_A));

    EXPECT_EQ(address + 1, cpu.read_register(REG_HL));
}

// LDH (n), A
TEST(CPU_LD, LD_n_A) {
    uint8_t opcode = 0xE0;
    IORegisters_t io_reg = STAT;
    uint8_t val_n = (uint16_t)io_reg - 0xFF00;
    uint8_t data = 0xAB;
    uint16_t PC = 0xFF80;

    MemoryMap mem_map;
    mem_map.write(PC, val_n);
    EXPECT_EQ(val_n, mem_map.read(PC));

    CPU cpu(mem_map);
    cpu.write_register(REG_PC, PC);
    cpu.write_register(REG_A, data);
    cpu.write_register(REG_HL, io_reg);
    EXPECT_EQ(PC, cpu.read_register(REG_PC));
    EXPECT_EQ(data, cpu.read_register(REG_A));
    EXPECT_EQ(io_reg, cpu.read_register(REG_HL));

    cpu.write_io_register(io_reg, 0x0);
    EXPECT_EQ(0x0, cpu.read_io_register(io_reg));
    EXPECT_EQ(0x0, cpu.read_memory());

    cpu.decode_op(opcode);

    EXPECT_EQ(data, cpu.read_io_register(io_reg));
    EXPECT_EQ(data, cpu.read_memory());
}

// LD A, (n)
TEST(CPU_LD, LD_A_n) {
    uint8_t opcode = 0xF0;
    IORegisters_t io_reg = STAT;
    uint8_t val_n = (uint16_t)io_reg - 0xFF00;
    uint8_t data = 0xAB;
    uint16_t PC = 0xFF80;

    MemoryMap mem_map;
    mem_map.write(PC, val_n);
    EXPECT_EQ(val_n, mem_map.read(PC));

    CPU cpu(mem_map);
    cpu.write_register(REG_PC, PC);
    cpu.write_register(REG_A, 0x0);
    cpu.write_register(REG_HL, io_reg);
    EXPECT_EQ(PC, cpu.read_register(REG_PC));
    EXPECT_EQ(0x0, cpu.read_register(REG_A));
    EXPECT_EQ(io_reg, cpu.read_register(REG_HL));

    cpu.write_io_register(io_reg, data);
    EXPECT_EQ(data, cpu.read_io_register(io_reg));
    EXPECT_EQ(data, cpu.read_memory());

    cpu.decode_op(opcode);

    EXPECT_EQ(data, cpu.read_register(REG_A));
}

// LD BC, nn
TEST(CPU_LD_16Bit, LD_N_NN) {
    uint8_t opcode = 0x01;
    uint16_t val_1 = 0x1234;
    uint16_t val_2 = 0xABCD;
    uint16_t PC = 0xFF80;

    MemoryMap mem_map;
    
    mem_map.write(PC, val_2 & 0xFF);
    mem_map.write(PC + 1, val_2 >> 8);
    CPU cpu(mem_map);

    cpu.write_register(REG_PC, PC);
    EXPECT_EQ(PC, cpu.read_register(REG_PC));

    cpu.write_register(REG_BC, val_1);

    EXPECT_EQ(val_1, cpu.read_register(REG_BC));

    cpu.decode_op(opcode);

    EXPECT_EQ(val_2, cpu.read_register(REG_BC));
}

// LD SP, HL
TEST(CPU_LD_16Bit, LD_SP_HL) {
    uint8_t opcode = 0xF9;
    uint16_t val_1 = 0x1234;
    uint16_t val_2 = 0xABCD;

    MemoryMap mem_map;
    
    CPU cpu(mem_map);

    cpu.write_register(REG_SP, val_1);
    cpu.write_register(REG_HL, val_2);

    EXPECT_EQ(val_1, cpu.read_register(REG_SP));
    EXPECT_EQ(val_2, cpu.read_register(REG_HL));

    cpu.decode_op(opcode);

    EXPECT_EQ(val_2, cpu.read_register(REG_SP));
}

// LDHL SP, n
TEST(CPU_LD_16Bit, LDHL_SP_N) {
    uint8_t opcode = 0xF8;
    uint16_t val_1 = 0x1234;
    uint16_t SP = 0xFFF0;
    int8_t n = 0x02;
    uint16_t PC = 0xFF80;

    MemoryMap mem_map;
    
    mem_map.write(PC, n);
    CPU cpu(mem_map);

    cpu.write_register(REG_PC, PC);

    EXPECT_EQ(PC, cpu.read_register(REG_PC));

    cpu.write_register(REG_HL, val_1);
    cpu.write_register(REG_SP, SP);

    EXPECT_EQ(val_1, cpu.read_register(REG_HL));
    EXPECT_EQ(SP, cpu.read_register(REG_SP));

    cpu.decode_op(opcode);

    EXPECT_EQ((SP + n) & 0xFFFF, cpu.read_register(REG_HL));

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
    uint16_t SP = 0xFFF0;
    int8_t n = 0xF2;
    int signed_n = -14;
    uint16_t PC = 0xFF80;

    MemoryMap mem_map;
    
    mem_map.write(PC, n);
    CPU cpu(mem_map);

    cpu.write_register(REG_PC, PC);

    EXPECT_EQ(PC, cpu.read_register(REG_PC));

    cpu.write_register(REG_HL, val_1);
    cpu.write_register(REG_SP, SP);

    EXPECT_EQ(val_1, cpu.read_register(REG_HL));
    EXPECT_EQ(SP, cpu.read_register(REG_SP));

    cpu.decode_op(opcode);

    EXPECT_EQ((SP + signed_n) & 0xFFFF, cpu.read_register(REG_HL));

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
    uint16_t PC = 0xFF80;

    MemoryMap mem_map;
    
    mem_map.write(PC, n);
    CPU cpu(mem_map);

    cpu.write_register(REG_PC, PC);

    EXPECT_EQ(PC, cpu.read_register(REG_PC));

    cpu.write_register(REG_HL, val_1);
    cpu.write_register(REG_SP, SP);

    EXPECT_EQ(val_1, cpu.read_register(REG_HL));
    EXPECT_EQ(SP, cpu.read_register(REG_SP));

    cpu.decode_op(opcode);

    EXPECT_EQ((SP + n) & 0xFFFF, cpu.read_register(REG_HL));

    // Check flags
    EXPECT_EQ(false, cpu.read_flag_register(ZERO_FLAG));
    EXPECT_EQ(false, cpu.read_flag_register(SUBTRACT_FLAG));
    EXPECT_EQ(true, cpu.read_flag_register(HALF_CARRY_FLAG));
    EXPECT_EQ(true, cpu.read_flag_register(CARRY_FLAG));
}

// LD (nn), SP
TEST(CPU_LD_16Bit, LD_NN_SP) {
    uint8_t opcode = 0x08;
    uint16_t address = 0xFF90;
    uint16_t SP = 0xFFFE;
    uint8_t n = 0x02;
    uint16_t PC = 0xFF80;

    MemoryMap mem_map;

    mem_map.write(PC, (address & 0xFF));
    mem_map.write(PC + 1, (address >> 8));
    EXPECT_EQ(address & 0xFF, mem_map.read(PC));
    EXPECT_EQ(address >> 8, mem_map.read(PC + 1));

    CPU cpu(mem_map);
    cpu.write_register(REG_PC, PC);
    cpu.write_register(REG_SP, SP);
    EXPECT_EQ(PC, cpu.read_register(REG_PC));
    EXPECT_EQ(SP, cpu.read_register(REG_SP));

    cpu.decode_op(opcode);

    cpu.write_register(REG_HL, address);
    EXPECT_EQ((SP & 0xFF), cpu.read_memory());
    cpu.write_register(REG_HL, address+1);
    EXPECT_EQ((SP >> 8), cpu.read_memory());
}

// PUSH BC
TEST(CPU_LD_16Bit, LD_PUSH_NN) {
    uint8_t opcode = 0xC5;
    uint16_t val_1 = 0xABCD;
    uint16_t SP = 0xFFFE;

    MemoryMap mem_map;
    
    CPU cpu(mem_map);

    cpu.write_register(REG_SP, SP);

    EXPECT_EQ(SP, cpu.read_register(REG_SP));

    cpu.write_register(REG_BC, val_1);

    EXPECT_EQ(val_1, cpu.read_register(REG_BC));

    cpu.decode_op(opcode);

    EXPECT_EQ(SP - 2, cpu.read_register(REG_SP));

    cpu.write_register(REG_DE, SP - 1);
    cpu.write_register(REG_HL, SP - 2);

    EXPECT_EQ(val_1 & 0xFF, cpu.read_memory(REG_DE));
    EXPECT_EQ(val_1 >> 8, cpu.read_memory(REG_HL));
}

// POP BC
TEST(CPU_LD_16Bit, LD_POP_NN) {
    uint8_t opcode = 0xC5;
    uint16_t val_1 = 0xABCD;
    uint16_t SP = 0xFFFE;

    MemoryMap mem_map;
    
    CPU cpu(mem_map);

    cpu.write_register(REG_SP, SP);

    EXPECT_EQ(SP, cpu.read_register(REG_SP));

    cpu.write_register(REG_BC, val_1);

    EXPECT_EQ(val_1, cpu.read_register(REG_BC));

    cpu.decode_op(opcode);

    EXPECT_EQ(SP - 2, cpu.read_register(REG_SP));

    cpu.write_register(REG_DE, SP - 1);
    cpu.write_register(REG_HL, SP - 2);

    EXPECT_EQ(val_1 & 0xFF, cpu.read_memory(REG_DE));
    EXPECT_EQ(val_1 >> 8, cpu.read_memory(REG_HL));

    opcode = 0xD1;

    cpu.decode_op(opcode);

    EXPECT_EQ(val_1, cpu.read_register(REG_DE));
    EXPECT_EQ(SP, cpu.read_register(REG_SP));
}