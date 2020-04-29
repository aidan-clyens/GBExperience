#include "io.h"


IO::IO():
m_P1(0xFF),
m_DIV(0x0),
m_TIMA(0x0),
m_TMA(0x0),
m_TAC(0x0),
m_LCDC(0x91),
m_SCY(0x0),
m_SCX(0x0),
m_LYC(0x0),
m_BGP(0xFC),
m_OBP0(0xFF),
m_OBP1(0xFF),
m_WY(0x0),
m_WX(0x0),
m_IE(0x0),
m_IF(0x0)
{

}

IO::~IO() {

}

uint8_t IO::read(IORegisters_t address) {
    #ifdef DEBUG
    std::cout << "IO read: " << static_cast<int>(address) << std::endl;
    #endif

    switch (address) {
        case P1:
            return m_P1;
        case DIV:
            return m_DIV;
        case TIMA:
            return m_TIMA;
        case TMA:
            return m_TMA;
        case TAC:
            return m_TAC;
        case IF:
            return m_IF;
        case LCDC:
            return m_LCDC;
        case STAT:
            return m_STAT;
        case SCY:
            return m_SCY;
        case SCX:
            return m_SCX;
        case LY:
            return m_LY;
        case LYC:
            return m_LYC;
        case DMA:
            return m_DMA;
        case BGP:
            return m_BGP;
        case OBP0:
            return m_OBP0;
        case OBP1:
            return m_OBP1;
        case WY:
            return m_WY;
        case WX:
            return m_WX;
        case IE:
            return m_IE;

        default:
            std::cerr << "IO Register: " << static_cast<int>(address) << " does not exist" << std::endl;
            throw new std::exception;
    }
}

uint16_t IO::write(IORegisters_t address, uint8_t data) {
    #ifdef DEBUG
    std::cout << "IO write: " << static_cast<int>(address) << std::endl;
    #endif

    switch (address) {
        case P1:
            m_P1 = data;
            break;
        case DIV:
            m_DIV = data;
            break;
        case TIMA:
            m_TIMA = data;
            break;
        case TMA:
            m_TMA = data;
            break;
        case TAC:
            m_TAC = data;
            break;
        case IF:
            m_IF = data;
            break;
        case LCDC:
            m_LCDC = data;
            break;
        case STAT:
            m_STAT = data;
            break;
        case SCY:
            m_SCY = data;
            break;
        case SCX:
            m_SCX = data;
            break;
        case LY:
            m_LY = data;
            break;
        case LYC:
            m_LYC = data;
            break;
        case DMA:
            m_DMA = data;
            break;
        case BGP:
            m_BGP = data;
            break;
        case OBP0:
            m_OBP0 = data;
            break;
        case OBP1:
            m_OBP1 = data;
            break;
        case WY:
            m_WY = data;
            break;
        case WX:
            m_WX = data;
            break;
        case IE:
            m_IE = data;
            break;

        default:
            std::cerr << "IO Register: " << static_cast<int>(address) << " does not exist" << std::endl;
            throw new std::exception;
    }

    return address;
}