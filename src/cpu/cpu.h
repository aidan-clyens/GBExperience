#pragma once

#include <iostream>
#include <exception>
#include <chrono>

#include "cpu_registers.h"
#include "../memory/memory_map.h"
#include "../memory/io.h"
#include "../debugger/logger.h"


const float EXPECTED_FREQ_MHZ = 4.194304;
const long int EXPECTED_CYCLE_TIME_NS = 1000.0 / EXPECTED_FREQ_MHZ;


typedef enum CPUFlag {
    ZERO_FLAG = 0x80,
    SUBTRACT_FLAG = 0x40,
    HALF_CARRY_FLAG = 0x20,
    CARRY_FLAG = 0x10
} CPUFlag_t;

typedef enum InterruptFlag {
    VBLANK = 0x01,
    LCD_STAT = 0x02,
    TIMER = 0x04,
    SERIAL = 0x08,
    JOYPAD = 0x10
} InterruptFlag_t;

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

        long int tick();

        uint8_t fetch_op();
        int decode_op(uint8_t);

        void write_register(const std::string &, uint16_t);
        uint16_t read_register(const std::string &);

        void write_memory(uint8_t);
        void write_memory(const std::string &, uint8_t);
        uint8_t read_memory();
        uint8_t read_memory(const std::string &);

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

        bool is_running() const;
        bool interrupts_enabled() const;

    private:
        CPURegisters m_registers;
        MemoryMap &m_memory_map;

        std::chrono::steady_clock::time_point m_last_time;

        bool m_halted;
        bool m_stopped;
        bool m_interrupts_enabled;
        
        // CPU Timing
        long int get_time_difference_ns();
        std::chrono::steady_clock::time_point get_time();

        /****    8-Bit and 16-Bit Loads    ****/
        void load(const std::string &, const std::string &);
        void load(const std::string &, uint16_t);
        void load_from_mem(const std::string &, const std::string &);
        void load_from_mem(const std::string &, uint16_t);
        void load_to_mem(const std::string &, const std::string &);
        void load_to_mem(const std::string &, uint16_t);
        void load_to_mem(uint16_t, const std::string &);
        void load_HL(int8_t);

        // PUSH nn
        void push_stack(const std::string &);
        // POP nn
        void pop_stack(const std::string &);

        /****    8-Bit ALU    ****/
        // ADD A, n
        // ADC A, n
        void alu_add(const std::string &, bool);
        void alu_add(uint8_t, bool);
        // SUB n
        // SBC n
        void alu_sub(const std::string &, bool);
        void alu_sub(uint8_t, bool);
        // AND n
        void alu_and(const std::string &);
        void alu_and(uint8_t);
        // OR n
        void alu_or(const std::string &);
        void alu_or(uint8_t);
        // XOR n
        void alu_xor(const std::string &);
        void alu_xor(uint8_t);
        // CP n
        void alu_cp(const std::string &);
        void alu_cp(uint8_t);
        // INC n
        void alu_inc(const std::string &);
        // DEC n
        void alu_dec(const std::string &);

        /****    16-Bit ALU    ****/
        // ADD HL, nn
        void alu_add_HL(const std::string &);
        // ADD SP, e
        void alu_add_SP(int8_t);
        // INC nn
        void alu_inc_16bit(const std::string &);
        // DEC nn
        void alu_dec_16bit(const std::string &);

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
        void rotate_left(bool);
        void rotate_left(const std::string &, bool);
        void rotate_right(bool);
        void rotate_right(const std::string &, bool);
        void shift_left(const std::string &);
        void shift_right(const std::string &, bool);

        /****    Bit Opcodes    ****/
        // BIT b, r
        void test_bit(int, const std::string &);
        // SET b, r
        void set_bit(int, const std::string &);
        // RES b, r
        void reset_bit(int, const std::string &);

        /****    Misc.    ****/
        // SWAP n
        void swap(const std::string &);
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
};
