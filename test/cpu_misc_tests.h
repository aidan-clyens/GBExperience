#include "gtest/gtest.h"


// SWAP A
TEST(CPU_MISC, SWAP) {
    uint16_t PC = 0xFF80;
    uint8_t opcode = 0x37;
    uint8_t A = 0xAB;
    uint8_t result = 0xBA;
    bool is_zero = false;

    MemoryMap mem_map = setup_cb_instruction(PC, opcode);
    CPU cpu(mem_map);

    cpu.write_register(REG_PC, PC);
    cpu.write_register(REG_A, A);

    EXPECT_EQ(PC, cpu.read_register(REG_PC));
    EXPECT_EQ(A, cpu.read_register(REG_A));

    opcode = cpu.fetch_op();
    EXPECT_EQ(0xCB, opcode);
    
    cpu.decode_op(opcode);

    // Check value of A register
    EXPECT_EQ(result, cpu.read_register(REG_A));
    // Check zero, subtract, and half-carry flags
    EXPECT_EQ(is_zero, cpu.read_flag_register(ZERO_FLAG));
    EXPECT_EQ(false, cpu.read_flag_register(SUBTRACT_FLAG));
    EXPECT_EQ(false, cpu.read_flag_register(HALF_CARRY_FLAG));
    EXPECT_EQ(false, cpu.read_flag_register(CARRY_FLAG));
}

// SWAP (HL)
TEST(CPU_MISC, SWAP_HL) {
    uint16_t PC = 0xFF80;
    uint16_t HL = 0xFFF0;
    uint8_t opcode = 0x36;
    uint8_t val = 0xAB;
    uint8_t result = 0xBA;
    bool is_zero = false;

    MemoryMap mem_map = setup_cb_instruction(PC, opcode);
    CPU cpu(mem_map);

    cpu.write_register(REG_PC, PC);
    cpu.write_register(REG_HL, HL);
    cpu.write_memory(val);

    EXPECT_EQ(PC, cpu.read_register(REG_PC));
    EXPECT_EQ(HL, cpu.read_register(REG_HL));
    EXPECT_EQ(val, cpu.read_memory());

    opcode = cpu.fetch_op();
    EXPECT_EQ(0xCB, opcode);

    cpu.decode_op(opcode);

    // Check value of HL memory location
    EXPECT_EQ(result, cpu.read_memory());
    // Check zero, subtract, and half-carry flags
    EXPECT_EQ(is_zero, cpu.read_flag_register(ZERO_FLAG));
    EXPECT_EQ(false, cpu.read_flag_register(SUBTRACT_FLAG));
    EXPECT_EQ(false, cpu.read_flag_register(HALF_CARRY_FLAG));
    EXPECT_EQ(false, cpu.read_flag_register(CARRY_FLAG));
}

// CPL
TEST(CPU_MISC, CPL) {
    uint8_t opcode = 0x2F;
    uint8_t A = 0xAB;       // 1010 1011
    uint8_t result = 0x54;  // 0101 0100

    MemoryMap mem_map;
    
    CPU cpu(mem_map);

    cpu.write_register(REG_A, A);
    EXPECT_EQ(A, cpu.read_register(REG_A));

    cpu.decode_op(opcode);

    // Check value of A register
    EXPECT_EQ(result, cpu.read_register(REG_A));
    // Check subtract and half-carry flags
    EXPECT_EQ(true, cpu.read_flag_register(SUBTRACT_FLAG));
    EXPECT_EQ(true, cpu.read_flag_register(HALF_CARRY_FLAG));
}

// CCF
TEST(CPU_MISC, CCF) {
    uint8_t opcode = 0x3F;
    bool carry = true;

    MemoryMap mem_map;
    
    CPU cpu(mem_map);

    cpu.set_flag_register(CARRY_FLAG, carry);
    EXPECT_EQ(carry, cpu.read_flag_register(CARRY_FLAG));

    cpu.decode_op(opcode);

    // Check subtract, half-carry, and carry flags
    EXPECT_EQ(false, cpu.read_flag_register(SUBTRACT_FLAG));
    EXPECT_EQ(false, cpu.read_flag_register(HALF_CARRY_FLAG));
    EXPECT_EQ(!carry, cpu.read_flag_register(CARRY_FLAG));
}

// SCF
TEST(CPU_MISC, SCF) {
    uint8_t opcode = 0x37;
    bool carry = false;

    MemoryMap mem_map;
    
    CPU cpu(mem_map);

    cpu.reset_flag_register();
    cpu.set_flag_register(CARRY_FLAG, carry);
    EXPECT_EQ(carry, cpu.read_flag_register(CARRY_FLAG));

    cpu.decode_op(opcode);

    // Check subtract, half-carry, and carry flags
    EXPECT_EQ(false, cpu.read_flag_register(SUBTRACT_FLAG));
    EXPECT_EQ(false, cpu.read_flag_register(HALF_CARRY_FLAG));
    EXPECT_EQ(true, cpu.read_flag_register(CARRY_FLAG));
}

// NOP
TEST(CPU_MISC, NOP) {
    uint8_t opcode = 0x00;

    MemoryMap mem_map;
    
    CPU cpu(mem_map);

    int count = cpu.decode_op(opcode);

    EXPECT_EQ(4, count);
}

// HALT
TEST(CPU_MISC, HALT) {
    uint8_t opcode = 0x76;
    std::string rom_file = get_test_rom();

    enable_interrupt_logging();

    FileParser file_parser;
    Cartridge *cartridge;
    EXPECT_NO_THROW(cartridge = file_parser.load_rom(rom_file));

    MemoryMap mem_map;
    mem_map. load_rom(cartridge);
    CPU cpu(mem_map);

    cpu.decode_op(opcode);

    EXPECT_FALSE(cpu.is_running());
    EXPECT_EQ(4, cpu.tick());

    // Trigger any interrupt
    cpu.set_interrupt_enable_bit(VBLANK, true);
    cpu.set_interrupt_flag_bit(VBLANK, true);
    EXPECT_TRUE(cpu.get_interrupt_enable_bit(VBLANK));
    EXPECT_TRUE(cpu.get_interrupt_flag_bit(VBLANK));

    cpu.tick();

    // CPU should continue running
    EXPECT_TRUE(cpu.is_running());
}

// STOP
TEST(CPU_MISC, STOP) {
    uint8_t opcode = 0x10;
    std::string rom_file = get_test_rom();

    enable_interrupt_logging();

    FileParser file_parser;
    Cartridge *cartridge;
    EXPECT_NO_THROW(cartridge = file_parser.load_rom(rom_file));

    MemoryMap mem_map;
    mem_map. load_rom(cartridge);
    CPU cpu(mem_map);

    cpu.decode_op(opcode);

    EXPECT_FALSE(cpu.is_running());
    EXPECT_EQ(4, cpu.tick());

    // Trigger a Joypad interrupt
    cpu.set_interrupt_enable_bit(JOYPAD, true);
    cpu.set_interrupt_flag_bit(JOYPAD, true);
    EXPECT_TRUE(cpu.get_interrupt_enable_bit(JOYPAD));
    EXPECT_TRUE(cpu.get_interrupt_flag_bit(JOYPAD));

    cpu.tick();

    // CPU should continue running
    EXPECT_TRUE(cpu.is_running());
}

// EI
TEST(CPU_MISC, EI) {
    uint8_t opcode = 0xFB;

    MemoryMap mem_map;
    
    CPU cpu(mem_map);

    cpu.decode_op(opcode);

    EXPECT_TRUE(cpu.interrupts_enabled());
}

// DI
TEST(CPU_MISC, DI) {
    uint8_t opcode = 0xF3;

    MemoryMap mem_map;
    
    CPU cpu(mem_map);

    cpu.decode_op(opcode);

    EXPECT_FALSE(cpu.interrupts_enabled());
}

// DAA ADD
TEST(CPU_MISC, DAA_ADD) {
    uint8_t add_opcode = 0x80;
    uint8_t daa_opcode = 0x27;

    MemoryMap mem_map;
    CPU cpu(mem_map);

    // ADD
    uint8_t val = 0x05;
    uint8_t n = 0x75;
    uint8_t add_result = 0x7A;
    uint8_t daa_result = 0x80;

    cpu.write_register(REG_A, val);
    cpu.write_register(REG_B, n);

    EXPECT_EQ(val, cpu.read_register(REG_A));
    EXPECT_EQ(n, cpu.read_register(REG_B));
    
    cpu.decode_op(add_opcode);

    EXPECT_EQ(add_result, cpu.read_register(REG_A));

    // DAA
    cpu.decode_op(daa_opcode);
    EXPECT_EQ(daa_result, cpu.read_register(REG_A));
}

// DAA ADD Boundary
TEST(CPU_MISC, DAA_ADD_BOUNDARY) {
    uint8_t add_opcode = 0x80;
    uint8_t daa_opcode = 0x27;

    MemoryMap mem_map;
    CPU cpu(mem_map);

    // ADD
    uint8_t val = 0x90;
    uint8_t n = 0x10;
    uint8_t add_result = 0xA0;
    uint8_t daa_result = 0x00;

    cpu.write_register(REG_A, val);
    cpu.write_register(REG_B, n);

    EXPECT_EQ(val, cpu.read_register(REG_A));
    EXPECT_EQ(n, cpu.read_register(REG_B));
    
    cpu.decode_op(add_opcode);

    EXPECT_EQ(add_result, cpu.read_register(REG_A));

    // DAA
    cpu.decode_op(daa_opcode);
    EXPECT_EQ(daa_result, cpu.read_register(REG_A));
    EXPECT_TRUE(cpu.read_flag_register(CARRY_FLAG));
    EXPECT_TRUE(cpu.read_flag_register(ZERO_FLAG));
}

// DAA SUB
TEST(CPU_MISC, DAA_SUB) {
    uint8_t sub_opcode = 0x90;
    uint8_t daa_opcode = 0x27;

    MemoryMap mem_map;
    CPU cpu(mem_map);

    // SUB
    uint8_t val = 0x80;
    uint8_t n = 0x75;
    uint8_t sub_result = 0x0B;
    uint8_t daa_result = 0x05;

    cpu.write_register(REG_A, val);
    cpu.write_register(REG_B, n);

    EXPECT_EQ(val, cpu.read_register(REG_A));
    EXPECT_EQ(n, cpu.read_register(REG_B));
    
    cpu.decode_op(sub_opcode);

    EXPECT_EQ(sub_result, cpu.read_register(REG_A));

    // DAA
    cpu.decode_op(daa_opcode);
    EXPECT_EQ(daa_result, cpu.read_register(REG_A));
}