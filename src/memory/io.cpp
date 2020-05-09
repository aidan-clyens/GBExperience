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
m_LY(0x0),
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
    if (address >= 0xFF30 && address <= 0xFF3F) {
        std::cerr << "Wave Pattern RAM unusable" << std::endl;

        return 0;
    }

    switch (address) {
        case P1:
            log_io("IO: reading %X from P1", m_P1);

            return m_P1;
        case SB:
            std::cerr << "SB not implemented" << std::endl;

            return 0;
        case SC:
            std::cerr << "SB not implemented" << std::endl;

            return 0;
        case DIV:
            log_io("IO: reading %X from DIV", m_DIV);

            return m_DIV;
        case TIMA:
            log_io("IO: reading %X from TIMA", m_TIMA);

            return m_TIMA;
        case TMA:
            log_io("IO: reading %X from TMA", m_TMA);

            return m_TMA;
        case TAC:
            log_io("IO: reading %X from TAC", m_TAC);

            return m_TAC;
        case IF:
            log_io("IO: reading %X from IF", m_IF);

            return m_IF;
        case NR10:
        case NR11:
        case NR12:
        case NR13:
        case NR14:
        case NR21:
        case NR22:
        case NR23:
        case NR24:
        case NR30:
        case NR31:
        case NR32:
        case NR33:
        case NR34:
        case NR41:
        case NR42:
        case NR43:
        case NR44:
        case NR50:
        case NR51:
        case NR52:
            std::cerr << "NR5* not implemented" << std::endl;

            return 0;
        case LCDC:
            log_io("IO: reading %X from LCDC", m_LCDC);

            return m_LCDC;
        case STAT:
            log_io("IO: reading %X from STAT", m_STAT);

            return m_STAT;
        case SCY:
            log_io("IO: reading %X from SCY", m_SCY);

            return m_SCY;
        case SCX:
            log_io("IO: reading %X from SCX", m_SCX);

            return m_SCX;
        case LY:
            log_io("IO: reading %X from LY", m_LY);

            return m_LY;
        case LYC:
            log_io("IO: reading %X from LYC", m_LYC);

            return m_LYC;
        case DMA:
            log_io("IO: reading %X from DMA", m_DMA);

            return m_DMA;
        case BGP:
            log_io("IO: reading %X from BGP", m_BGP);

            return m_BGP;
        case OBP0:
            log_io("IO: reading %X from OBP0", m_OBP0);

            return m_OBP0;
        case OBP1:
            log_io("IO: reading %X from OBP1", m_OBP1);

            return m_OBP1;
        case WY:
            log_io("IO: reading %X from WY", m_WY);

            return m_WY;
        case WX:
            log_io("IO: reading %X from WX", m_WX);

            return m_WX;
        case IE:
            log_io("IO: reading %X from IE", m_IE);

            return m_IE;

        default:
            std::cerr << "IO Register: " << static_cast<int>(address) << " does not exist" << std::endl;
            // throw new std::exception;
            break;
    }
}

uint16_t IO::write(IORegisters_t address, uint8_t data) {
    if (address >= 0xFF30 && address <= 0xFF3F) {
        std::cerr << "Wave Pattern RAM unusable" << std::endl;

        return 0;
    }

    switch (address) {
        case P1:
            log_io("IO: writing %X to P1", data);

            m_P1 = data;
            break;
        case SB:
            std::cerr << "SB not implemented" << std::endl;

            break;
        case SC:
            std::cerr << "SB not implemented" << std::endl;

            break;
        case DIV:
            log_io("IO: writing %X to DIV", data);

            m_DIV = data;
            break;
        case TIMA:
            log_io("IO: writing %X to TIMA", data);

            m_TIMA = data;
            break;
        case TMA:
            log_io("IO: writing %X to TMA", data);

            m_TMA = data;
            break;
        case TAC:
            log_io("IO: writing %X to TAC", data);

            m_TAC = data;
            break;
        case IF:
            log_io("IO: writing %X to IF", data);

            m_IF = data;
            break;
        case NR10:
        case NR11:
        case NR12:
        case NR13:
        case NR14:
        case NR21:
        case NR22:
        case NR23:
        case NR24:
        case NR30:
        case NR31:
        case NR32:
        case NR33:
        case NR34:
        case NR41:
        case NR42:
        case NR43:
        case NR44:
        case NR50:
        case NR51:
        case NR52:
            std::cerr << "NR5* not implemented" << std::endl;

            break;
        case LCDC:
            log_io("IO: writing %X to LCDC", data);

            m_LCDC = data;
            break;
        case STAT:
            log_io("IO: writing %X to STAT", data);

            m_STAT = data;
            break;
        case SCY:
            log_io("IO: writing %X to SCY", data);

            m_SCY = data;
            break;
        case SCX:
            log_io("IO: writing %X to SCX", data);

            m_SCX = data;
            break;
        case LY:
            log_io("IO: writing %X to LY", 0x0);
            // LY resets when written to
            m_LY = 0x0;
            break;
        case LYC:
            log_io("IO: writing %X to LYC", data);

            m_LYC = data;
            break;
        case DMA:
            log_io("IO: writing %X to DMA", data);

            m_DMA = data;
            break;
        case BGP:
            log_io("IO: writing %X to BGP", data);

            m_BGP = data;
            break;
        case OBP0:
            log_io("IO: writing %X to OBP0", data);

            m_OBP0 = data;
            break;
        case OBP1:
            log_io("IO: writing %X to OBP1", data);

            m_OBP1 = data;
            break;
        case WY:
            log_io("IO: writing %X to WY", data);

            m_WY = data;
            break;
        case WX:
            log_io("IO: writing %X to WX", data);

            m_WX = data;
            break;
        case IE:
            log_io("IO: writing %X to IE", data);

            m_IE = data;
            break;

        default:
            std::cerr << "IO Register: " << static_cast<int>(address) << " does not exist" << std::endl;
            throw new std::exception;
    }

    return address;
}

void IO::increment_counter(IORegisters_t reg) {
    switch (reg) {
        case LY:
            
            log_io("IO: Incremented LY");
            
            m_LY++;
            break;
        case DIV:
            
            log_io("IO: Incremented DIV");
            
            m_DIV++;
            break;
        default:
            std::cerr << "IO register is not a counter. Cannot be incremented." << std::endl;
            throw new std::exception;
    }
}