#pragma once

#include <cstdint>
#include <iostream>
#include <exception>

#include "../debugger/logger.h"
#include "../ui/input.h"


typedef enum IORegisters {
    P1 = 0xFF00,
    SB = 0xFF01,
    SC = 0xFF02,
    DIV = 0xFF04,
    TIMA = 0xFF05,
    TMA = 0xFF06,
    TAC = 0xFF07,
    IF = 0xFF0F,
    NR10 = 0xFF10,
    NR11 = 0xFF11,
    NR12 = 0xFF12,
    NR13 = 0xFF13,
    NR14 = 0xFF14,
    NR21 = 0xFF16,
    NR22 = 0xFF17,
    NR23 = 0xFF18,
    NR24 = 0xFF19,
    NR30 = 0xFF1A,
    NR31 = 0xFF1B,
    NR32 = 0xFF1C,
    NR33 = 0xFF1D,
    NR34 = 0xFF1E,
    NR41 = 0xFF20,
    NR42 = 0xFF21,
    NR43 = 0xFF22,
    NR44 = 0xFF23,
    NR50 = 0xFF24,
    NR51 = 0xFF25,
    NR52 = 0xFF26,
    LCDC = 0xFF40,
    STAT = 0xFF41,
    SCY = 0xFF42,
    SCX = 0xFF43,
    LY = 0xFF44,
    LYC = 0xFF45,
    DMA = 0xFF46,
    BGP = 0xFF47,
    OBP0 = 0xFF48,
    OBP1 = 0xFF49,
    WY = 0xFF4A,
    WX = 0xFF4B,
    IE = 0xFFFF
} IORegisters_t;


class IO {
    public:
        IO();
        virtual ~IO();

        uint8_t read(IORegisters_t);
        uint16_t write(IORegisters_t, uint8_t);

        void increment_counter(IORegisters_t);

        void set_button_pressed(Buttons_t, bool);
        uint8_t get_input();

        bool dpad_toggled() const;
        bool buttons_toggled() const;

    private:
        Input m_input;

        uint8_t m_P1;
        uint8_t m_DIV;
        uint8_t m_TIMA;
        uint8_t m_TMA;
        uint8_t m_TAC;
        uint8_t m_IF;
        uint8_t m_LCDC;
        uint8_t m_STAT;
        uint8_t m_SCY;
        uint8_t m_SCX;
        uint8_t m_LY;
        uint8_t m_LYC;
        uint8_t m_DMA;
        uint8_t m_BGP;
        uint8_t m_OBP0;
        uint8_t m_OBP1;
        uint8_t m_WY;
        uint8_t m_WX;
        uint8_t m_IE;
};