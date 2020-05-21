#include "gtest/gtest.h"


TEST(Interrupts, InterruptsEnabledByDefault) {
    MemoryMap mem_map;
    CPU cpu(mem_map);

    EXPECT_TRUE(cpu.interrupts_enabled());
}


TEST(Interrupts, ReadInterruptEnableRegister) {
    MemoryMap mem_map;
    CPU cpu(mem_map);

    EXPECT_EQ(0x0, cpu.read_io_register(IE));
}


TEST(Interrupts, ReadInterruptFlagRegister) {
    MemoryMap mem_map;
    CPU cpu(mem_map);

    EXPECT_EQ(0x0, cpu.read_io_register(IF));
}

TEST(Interrupts, WriteInterruptEnableRegister) {
    uint8_t value = 0xFF;

    MemoryMap mem_map;
    CPU cpu(mem_map);

    cpu.write_io_register(IE, value);
    EXPECT_EQ(value, cpu.read_io_register(IE));
}


TEST(Interrupts, WriteInterruptFlagRegister) {
    uint8_t value = 0xFF;

    MemoryMap mem_map;
    CPU cpu(mem_map);

    cpu.write_io_register(IF, value);
    EXPECT_EQ(value, cpu.read_io_register(IF));
}

TEST(Interrupts, SetVBlankEnableBit) {
    MemoryMap mem_map;
    CPU cpu(mem_map);

    cpu.write_io_register(IE, 0x0);
    EXPECT_EQ(0x0, cpu.read_io_register(IE));

    EXPECT_FALSE(cpu.get_interrupt_enable_bit(VBLANK));

    cpu.set_interrupt_enable_bit(VBLANK, true);
    EXPECT_TRUE(cpu.get_interrupt_enable_bit(VBLANK));
    EXPECT_FALSE(cpu.get_interrupt_enable_bit(JOYPAD));
}

TEST(Interrupts, SetVBlankFlagBit) {
    MemoryMap mem_map;
    CPU cpu(mem_map);

    cpu.write_io_register(IF, 0x0);
    EXPECT_EQ(0x0, cpu.read_io_register(IF));

    EXPECT_FALSE(cpu.get_interrupt_flag_bit(VBLANK));

    cpu.set_interrupt_flag_bit(VBLANK, true);
    EXPECT_TRUE(cpu.get_interrupt_flag_bit(VBLANK));
    EXPECT_FALSE(cpu.get_interrupt_flag_bit(JOYPAD));
}

TEST(Interrupts, SetMultipleEnableBits) {
    MemoryMap mem_map;
    CPU cpu(mem_map);

    cpu.write_io_register(IE, 0x0);
    EXPECT_EQ(0x0, cpu.read_io_register(IE));

    EXPECT_FALSE(cpu.get_interrupt_enable_bit(VBLANK));
    EXPECT_FALSE(cpu.get_interrupt_enable_bit(JOYPAD));

    cpu.set_interrupt_enable_bit(VBLANK, true);
    cpu.set_interrupt_enable_bit(JOYPAD, true);
    EXPECT_TRUE(cpu.get_interrupt_enable_bit(VBLANK));
    EXPECT_TRUE(cpu.get_interrupt_enable_bit(JOYPAD));
    EXPECT_FALSE(cpu.get_interrupt_enable_bit(TIMER));
}

TEST(Interrupts, SetMultipleFlagBits) {
    MemoryMap mem_map;
    CPU cpu(mem_map);

    cpu.write_io_register(IF, 0x0);
    EXPECT_EQ(0x0, cpu.read_io_register(IF));

    EXPECT_FALSE(cpu.get_interrupt_flag_bit(VBLANK));
    EXPECT_FALSE(cpu.get_interrupt_flag_bit(JOYPAD));

    cpu.set_interrupt_flag_bit(VBLANK, true);
    cpu.set_interrupt_flag_bit(JOYPAD, true);
    EXPECT_TRUE(cpu.get_interrupt_flag_bit(VBLANK));
    EXPECT_TRUE(cpu.get_interrupt_flag_bit(JOYPAD));
    EXPECT_FALSE(cpu.get_interrupt_flag_bit(TIMER));
}

TEST(Interrupts, ResetVBlankEnableBit) {
    MemoryMap mem_map;
    CPU cpu(mem_map);

    cpu.write_io_register(IE, 0x1F);
    EXPECT_EQ(0x1F, cpu.read_io_register(IE));

    EXPECT_TRUE(cpu.get_interrupt_enable_bit(VBLANK));
    EXPECT_TRUE(cpu.get_interrupt_enable_bit(JOYPAD));

    cpu.set_interrupt_enable_bit(VBLANK, false);
    EXPECT_FALSE(cpu.get_interrupt_enable_bit(VBLANK));
    EXPECT_TRUE(cpu.get_interrupt_enable_bit(JOYPAD));
}

TEST(Interrupts, ResetVBlankFlagBit) {
    MemoryMap mem_map;
    CPU cpu(mem_map);

    cpu.write_io_register(IF, 0x1F);
    EXPECT_EQ(0x1F, cpu.read_io_register(IF));

    EXPECT_TRUE(cpu.get_interrupt_flag_bit(VBLANK));
    EXPECT_TRUE(cpu.get_interrupt_flag_bit(JOYPAD));

    cpu.set_interrupt_flag_bit(VBLANK, false);
    EXPECT_FALSE(cpu.get_interrupt_flag_bit(VBLANK));
    EXPECT_TRUE(cpu.get_interrupt_flag_bit(JOYPAD));
}

TEST(Interrupts, ResetMultipleEnableBits) {
    MemoryMap mem_map;
    CPU cpu(mem_map);

    cpu.write_io_register(IE, 0x1F);
    EXPECT_EQ(0x1F, cpu.read_io_register(IE));

    EXPECT_TRUE(cpu.get_interrupt_enable_bit(VBLANK));
    EXPECT_TRUE(cpu.get_interrupt_enable_bit(JOYPAD));

    cpu.set_interrupt_enable_bit(VBLANK, false);
    cpu.set_interrupt_enable_bit(JOYPAD, false);
    EXPECT_FALSE(cpu.get_interrupt_enable_bit(VBLANK));
    EXPECT_FALSE(cpu.get_interrupt_enable_bit(JOYPAD));
    EXPECT_TRUE(cpu.get_interrupt_enable_bit(TIMER));
}

TEST(Interrupts, TriggerVBlankInterrupt) {
    uint16_t PC = 0xA000;
    std::string rom_file = "../../roms/Tetris.gb";

    enable_interrupt_logging();
    enable_cpu_logging();

    FileParser file_parser;
    Cartridge *cartridge = file_parser.load_rom(rom_file);
    MemoryMap mem_map;
    mem_map.load_rom(cartridge);
    CPU cpu(mem_map);

    // Enable V-Blank interrupts
    cpu.set_interrupt_enable_bit(VBLANK, true);

    cpu.write_register("PC", PC);
    EXPECT_EQ(PC, cpu.read_register("PC"));

    // Trigger VBLANK interrupt
    cpu.write_io_register(IF, VBLANK);
    EXPECT_TRUE(cpu.get_interrupt_enable_bit(VBLANK));
    EXPECT_EQ(VBLANK, cpu.read_io_register(IF));

    cpu.handle_interrupts();

    // Current PC should be pushed to stack
    uint16_t SP = cpu.read_register("SP");
    EXPECT_EQ((PC >> 8), mem_map.read(SP));
    EXPECT_EQ((PC & 0xF), mem_map.read(SP + 1));

    // Should jump to corresponding interrupt service routine
    EXPECT_EQ((uint16_t)VBLANK_ISR, cpu.read_register("PC"));
    // Corresponding bit in IF register should be cleared
    EXPECT_FALSE(cpu.get_interrupt_flag_bit(VBLANK));
    // Interrupts should be disabled until reenabled at the end of the ISR
    EXPECT_FALSE(cpu.interrupts_enabled());
}


TEST(Interrupts, TriggerJoypadInterrupt) {
    uint16_t PC = 0xA000;
    std::string rom_file = "../../roms/Tetris.gb";

    enable_interrupt_logging();
    enable_cpu_logging();

    FileParser file_parser;
    Cartridge *cartridge = file_parser.load_rom(rom_file);
    MemoryMap mem_map;
    mem_map.load_rom(cartridge);
    CPU cpu(mem_map);

    // Enable Joypad interrupts
    cpu.set_interrupt_enable_bit(JOYPAD, true);

    cpu.write_register("PC", PC);
    EXPECT_EQ(PC, cpu.read_register("PC"));

    // Trigger Joypad interrupt
    cpu.write_io_register(IF, JOYPAD);
    EXPECT_TRUE(cpu.get_interrupt_enable_bit(JOYPAD));
    EXPECT_EQ(JOYPAD, cpu.read_io_register(IF));

    cpu.handle_interrupts();

    // Current PC should be pushed to stack
    uint16_t SP = cpu.read_register("SP");
    EXPECT_EQ((PC >> 8), mem_map.read(SP));
    EXPECT_EQ((PC & 0xF), mem_map.read(SP + 1));

    // Should jump to corresponding interrupt service routine
    EXPECT_EQ((uint16_t)JOYPAD_ISR, cpu.read_register("PC"));
    // Corresponding bit in IF register should be cleared
    EXPECT_FALSE(cpu.get_interrupt_flag_bit(JOYPAD));
    // Interrupts should be disabled until reenabled at the end of the ISR
    EXPECT_FALSE(cpu.interrupts_enabled());
}


TEST(Interrupts, TriggerTimerInterrupt) {
    uint16_t PC = 0xA000;
    std::string rom_file = "../../roms/Tetris.gb";

    enable_interrupt_logging();
    enable_cpu_logging();

    FileParser file_parser;
    Cartridge *cartridge = file_parser.load_rom(rom_file);
    MemoryMap mem_map;
    mem_map.load_rom(cartridge);
    CPU cpu(mem_map);

    // Enable Timer Overflow interrupts
    cpu.set_interrupt_enable_bit(TIMER, true);

    cpu.write_register("PC", PC);
    EXPECT_EQ(PC, cpu.read_register("PC"));

    // Trigger Timer Overflow interrupt
    cpu.write_io_register(IF, TIMER);
    EXPECT_TRUE(cpu.get_interrupt_enable_bit(TIMER));
    EXPECT_EQ(TIMER, cpu.read_io_register(IF));

    cpu.handle_interrupts();

    // Current PC should be pushed to stack
    uint16_t SP = cpu.read_register("SP");
    EXPECT_EQ((PC >> 8), mem_map.read(SP));
    EXPECT_EQ((PC & 0xF), mem_map.read(SP + 1));

    // Should jump to corresponding interrupt service routine
    EXPECT_EQ((uint16_t)TIMER_ISR, cpu.read_register("PC"));
    // Corresponoding bit in IF register should be cleared
    EXPECT_FALSE(cpu.get_interrupt_flag_bit(TIMER));
    // Interrupts should be disabled until reenabled at the end of the ISR
    EXPECT_FALSE(cpu.interrupts_enabled());
}


TEST(Interrupts, TriggerLCDStatusInterrupt) {
    uint16_t PC = 0xA000;
    std::string rom_file = "../../roms/Tetris.gb";

    enable_interrupt_logging();
    enable_cpu_logging();

    FileParser file_parser;
    Cartridge *cartridge = file_parser.load_rom(rom_file);
    MemoryMap mem_map;
    mem_map.load_rom(cartridge);
    CPU cpu(mem_map);

    // Enable LCD Status interrupts
    cpu.set_interrupt_enable_bit(LCD_STAT, true);

    cpu.write_register("PC", PC);
    EXPECT_EQ(PC, cpu.read_register("PC"));

    // Trigger LCD Status interrupt
    cpu.write_io_register(IF, LCD_STAT);
    EXPECT_TRUE(cpu.get_interrupt_enable_bit(LCD_STAT));
    EXPECT_EQ(LCD_STAT, cpu.read_io_register(IF));

    cpu.handle_interrupts();

    // Current PC should be pushed to stack
    uint16_t SP = cpu.read_register("SP");
    EXPECT_EQ((PC >> 8), mem_map.read(SP));
    EXPECT_EQ((PC & 0xF), mem_map.read(SP + 1));

    // Should jump to corresponding interrupt service routine
    EXPECT_EQ((uint16_t)LCD_STAT_ISR, cpu.read_register("PC"));
    // Corresponoding bit in IF register should be cleared
    EXPECT_FALSE(cpu.get_interrupt_flag_bit(LCD_STAT));
    // Interrupts should be disabled until reenabled at the end of the ISR
    EXPECT_FALSE(cpu.interrupts_enabled());
}


TEST(Interrupts, TriggerSerialTransferInterrupt) {
    uint16_t PC = 0xA000;
    std::string rom_file = "../../roms/Tetris.gb";

    FileParser file_parser;
    Cartridge *cartridge = file_parser.load_rom(rom_file);
    MemoryMap mem_map;
    mem_map.load_rom(cartridge);
    CPU cpu(mem_map);

    // Enable Serial Transfer interrupts
    cpu.set_interrupt_enable_bit(SERIAL, true);

    cpu.write_register("PC", PC);
    EXPECT_EQ(PC, cpu.read_register("PC"));

    // Trigger Serial Transfer interrupt
    cpu.write_io_register(IF, SERIAL);
    EXPECT_TRUE(cpu.get_interrupt_enable_bit(SERIAL));
    EXPECT_EQ(SERIAL, cpu.read_io_register(IF));

    cpu.handle_interrupts();

    // Current PC should be pushed to stack
    uint16_t SP = cpu.read_register("SP");
    EXPECT_EQ((PC >> 8), mem_map.read(SP));
    EXPECT_EQ((PC & 0xF), mem_map.read(SP + 1));

    // Should jump to corresponding interrupt service routine
    EXPECT_EQ((uint16_t)SERIAL_ISR, cpu.read_register("PC"));
    // Corresponoding bit in IF register should be cleared
    EXPECT_FALSE(cpu.get_interrupt_flag_bit(SERIAL));
    // Interrupts should be disabled until reenabled at the end of the ISR
    EXPECT_FALSE(cpu.interrupts_enabled());
}


TEST(Interrupts, TriggerMultipleInterrupts) {
    uint16_t PC = 0xA000;
    std::string rom_file = "../../roms/Tetris.gb";
    
    enable_interrupt_logging();
    enable_cpu_logging();

    FileParser file_parser;
    Cartridge *cartridge = file_parser.load_rom(rom_file);
    MemoryMap mem_map;
    mem_map.load_rom(cartridge);
    CPU cpu(mem_map);

    // Enable Timer Overflow and Joypad interrupts
    cpu.set_interrupt_enable_bit(TIMER, true);
    cpu.set_interrupt_enable_bit(JOYPAD, true);
    EXPECT_TRUE(cpu.get_interrupt_enable_bit(TIMER));
    EXPECT_TRUE(cpu.get_interrupt_enable_bit(JOYPAD));

    cpu.write_register("PC", PC);
    EXPECT_EQ(PC, cpu.read_register("PC"));

    // Trigger Timer Overflow and Joypad interrupts
    cpu.set_interrupt_flag_bit(TIMER, true);
    cpu.set_interrupt_flag_bit(JOYPAD, true);
    EXPECT_TRUE(cpu.get_interrupt_enable_bit(TIMER));
    EXPECT_TRUE(cpu.get_interrupt_enable_bit(JOYPAD));

    cpu.handle_interrupts();

    // Current PC should be pushed to stack
    uint16_t SP = cpu.read_register("SP");
    EXPECT_EQ((PC >> 8), mem_map.read(SP));
    EXPECT_EQ((PC & 0xF), mem_map.read(SP + 1));

    // Should handle the Timer Overflow interrupt first
    EXPECT_EQ((uint16_t)TIMER_ISR, cpu.read_register("PC"));
    // Corresponding bit in IF register should be cleared
    EXPECT_FALSE(cpu.get_interrupt_flag_bit(TIMER));
    // Interrupts should be disabled until reenabled at the end of the ISR
    EXPECT_FALSE(cpu.interrupts_enabled());

    while (!cpu.interrupts_enabled()) {
        cpu.tick();
    }

    // Interrupts should be reenabled
    EXPECT_TRUE(cpu.interrupts_enabled());

    // Get current PC
    PC = cpu.read_register("PC");

    cpu.handle_interrupts();

    // Current PC should be pushed to stack
    SP = cpu.read_register("SP");
    EXPECT_EQ((PC >> 8), mem_map.read(SP));
    EXPECT_EQ((PC & 0xF), mem_map.read(SP + 1));

    // Should handle the Joypad interrupt next
    EXPECT_EQ((uint16_t)JOYPAD_ISR, cpu.read_register("PC"));
    // Corresponoding bit in IF register should be cleared
    EXPECT_FALSE(cpu.get_interrupt_flag_bit(JOYPAD));
    // Interrupts should be disabled until reenabled at the end of the ISR
    EXPECT_FALSE(cpu.interrupts_enabled());
}
