#pragma once

#include <iostream>
#include <exception>
#include <chrono>

#include "cpu_registers.h"
#include "../memory/memory_map.h"
#include "../memory/mem_io.h"
#include "../debugger/logger.h"


typedef enum CPUFlag {
    ZERO_FLAG = 0x80,
    SUBTRACT_FLAG = 0x40,
    HALF_CARRY_FLAG = 0x20,
    CARRY_FLAG = 0x10
} CPUFlag_t;

typedef enum InteruptVector {
    VBLANK_ISR = 0x40,
    LCD_STAT_ISR = 0x48,
    TIMER_ISR = 0x50,
    SERIAL_ISR = 0x58,
    JOYPAD_ISR = 0x60
} InterruptVector_t;

class CPU {
    public:
        CPU(MemoryMap &);
        virtual ~CPU();

        int tick();

        uint8_t fetch_op();
        int decode_op(uint8_t);

        void write_register(Registers_t, uint16_t);
        uint16_t read_register(Registers_t);

        void write_memory(uint8_t);
        void write_memory(Registers_t, uint8_t);
        uint8_t read_memory();
        uint8_t read_memory(Registers_t);

        void set_flag_register(CPUFlag_t, bool);
        bool read_flag_register(CPUFlag_t);
        void reset_flag_register();

        uint8_t read_io_register(IORegisters_t);
        void write_io_register(IORegisters_t, uint8_t);

        void handle_interrupts();
        bool handle_interrupt(InterruptFlag_t, InterruptVector_t);
        bool get_interrupt_enable_bit(InterruptFlag_t);
        bool get_interrupt_flag_bit(InterruptFlag_t);
        void set_interrupt_enable_bit(InterruptFlag_t, bool);
        void set_interrupt_flag_bit(InterruptFlag_t, bool);

        bool is_stopped() const;
        bool is_running() const;
        bool interrupts_enabled() const;

    private:
        CPURegisters m_registers;
        MemoryMap &m_memory_map;

        bool m_halted;
        bool m_stopped;
        bool m_interrupts_enabled;

        /****    8-Bit and 16-Bit Loads    ****/
        void load(Registers_t, Registers_t);
        void load(Registers_t, uint16_t);
        void load_from_mem(Registers_t, Registers_t);
        void load_from_mem(Registers_t, uint16_t);
        void load_to_mem(Registers_t, Registers_t);
        void load_to_mem(Registers_t, uint16_t);
        void load_to_mem(uint16_t, Registers_t);
        void load_to_mem16bit(uint16_t, Registers_t);
        void load_HL(int8_t);

        // PUSH nn
        void push_stack(Registers_t);
        // POP nn
        void pop_stack(Registers_t);

        /****    8-Bit ALU    ****/
        // ADD A, n
        // ADC A, n
        void alu_add(Registers_t, bool);
        void alu_add(uint8_t, bool);
        // SUB n
        // SBC n
        void alu_sub(Registers_t, bool);
        void alu_sub(uint8_t, bool);
        // AND n
        void alu_and(Registers_t);
        void alu_and(uint8_t);
        // OR n
        void alu_or(Registers_t);
        void alu_or(uint8_t);
        // XOR n
        void alu_xor(Registers_t);
        void alu_xor(uint8_t);
        // CP n
        void alu_cp(Registers_t);
        void alu_cp(uint8_t);
        // INC n
        void alu_inc(Registers_t);
        // DEC n
        void alu_dec(Registers_t);

        /****    16-Bit ALU    ****/
        // ADD HL, nn
        void alu_add_HL(Registers_t);
        // ADD SP, e
        void alu_add_SP(int8_t);
        // INC nn
        void alu_inc_16bit(Registers_t);
        // DEC nn
        void alu_dec_16bit(Registers_t);

        /****    Jumps    ****/
        // JP nn
        void jump(uint16_t);
        // JP cc, nn
        void jump_conditional(uint16_t, CPUFlag_t, bool);
        // JP (HL)
        void jump_hl();
        // JR n
        void jump_add(int8_t);
        // JR cc, n
        void jump_add_conditional(int8_t, CPUFlag_t, bool);

        /****    Restarts    ****/
        // RST nn
        void restart(uint8_t);

        /****    Calls    ****/
        // CALL nn
        void call(uint16_t);
        // CALL cc, nn
        void call(uint16_t, CPUFlag_t, bool);

        /****    Returns    ****/
        // RET
        void ret();
        // RET cc
        void ret(CPUFlag_t, bool);
        // RETI
        void ret_enable_interrupts();

        /****    Rotates and Shifts    ****/
        void rotate_left_A(bool);
        void rotate_left(Registers_t, bool, bool);
        void rotate_right_A(bool);
        void rotate_right(Registers_t, bool, bool);
        void shift_left(Registers_t);
        void shift_right(Registers_t, bool);

        /****    Bit Opcodes    ****/
        // BIT b, r
        void test_bit(int, Registers_t);
        // SET b, r
        void set_bit(int, Registers_t);
        // RES b, r
        void reset_bit(int, Registers_t);

        /****    Misc.    ****/
        // SWAP n
        void swap(Registers_t);
        // CPL
        void complement();
        // CCF
        void complement_carry();
        // SCF
        void set_carry();
        // HALT
        void halt();
        // STOP
        void stop();
        // EI
        void enable_interrupts();
        // DI
        void disable_interrupts();
        // DAA
        void daa();
};
