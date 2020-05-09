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
            
            log_io("IO read: P1");
            

            return m_P1;
        case SB:
            
            std::cerr << "SB not implemented" << std::endl;
            

            return 0;
        case SC:
            
            std::cerr << "SB not implemented" << std::endl;
            

            return 0;
        case DIV:
            
            log_io("IO read: DIV");
            

            return m_DIV;
        case TIMA:
            
            log_io("IO read: TIMA");
            

            return m_TIMA;
        case TMA:
            
            log_io("IO read: TMA");
            

            return m_TMA;
        case TAC:
            
            log_io("IO read: TAC");
            

            return m_TAC;
        case IF:
            
            log_io("IO read: IF");
            

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
            
            log_io("IO read: LCDC");
            

            return m_LCDC;
        case STAT:
            
            log_io("IO read: STAT");
            

            return m_STAT;
        case SCY:
            
            log_io("IO read: SCY");
            

            return m_SCY;
        case SCX:
            
            log_io("IO read: SCX");
            

            return m_SCX;
        case LY:
            
            log_io("IO read: LY");
            

            return m_LY;
        case LYC:
            
            log_io("IO read: LYC");
            

            return m_LYC;
        case DMA:
            
            log_io("IO read: DMA");
            

            return m_DMA;
        case BGP:
            
            log_io("IO read: BGP");
            

            return m_BGP;
        case OBP0:
            
            log_io("IO read: OBP0");
            

            return m_OBP0;
        case OBP1:
            
            log_io("IO read: OBP1");
            

            return m_OBP1;
        case WY:
            
            log_io("IO read: WY");
            

            return m_WY;
        case WX:
            
            log_io("IO read: WX");
            

            return m_WX;
        case IE:
            
            log_io("IO read: IE");
            

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
            
            log_io("IO write: P1");
            

            m_P1 = data;
            break;
        case SB:
            
            std::cerr << "SB not implemented" << std::endl;
            

            break;
        case SC:
            
            std::cerr << "SB not implemented" << std::endl;
            

            break;
        case DIV:
            
            log_io("IO write: DIV");
            

            m_DIV = data;
            break;
        case TIMA:
            
            log_io("IO write: TIMA");
            

            m_TIMA = data;
            break;
        case TMA:
            
            log_io("IO write: TMA");
            

            m_TMA = data;
            break;
        case TAC:
            
            log_io("IO write: TAC");
            

            m_TAC = data;
            break;
        case IF:
            
            log_io("IO write: IF");
            

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
            
            log_io("IO write: LCDC");
            

            m_LCDC = data;
            break;
        case STAT:
            
            log_io("IO write: STAT");
            

            m_STAT = data;
            break;
        case SCY:
            
            log_io("IO write: SCY");
            

            m_SCY = data;
            break;
        case SCX:
            
            log_io("IO write: SCX");
            

            m_SCX = data;
            break;
        case LY:
            
            log_io("IO write: LY");
            

            m_LY = data;
            break;
        case LYC:
            
            log_io("IO write: LYC");
            

            m_LYC = data;
            break;
        case DMA:
            
            log_io("IO write: DMA");
            

            m_DMA = data;
            break;
        case BGP:
            
            log_io("IO write: BGP");
            

            m_BGP = data;
            break;
        case OBP0:
            
            log_io("IO write: OBP0");
            

            m_OBP0 = data;
            break;
        case OBP1:
            
            log_io("IO write: OBP1");
            

            m_OBP1 = data;
            break;
        case WY:
            
            log_io("IO write: WY");
            

            m_WY = data;
            break;
        case WX:
            
            log_io("IO write: WX");
            

            m_WX = data;
            break;
        case IE:
            
            log_io("IO write: IE");
            

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