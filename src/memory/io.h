#pragma once

#include <cstdint>
#include <iostream>
#include <exception>


typedef enum IORegisters {
    P1 = 0xFF00,
    DIV = 0xFF04,
    TIMA = 0xFF05,
    TMA = 0xFF06,
    TAC = 0xFF07,
    IF = 0xFF0F,
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
    
    private:
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