#include "video.h"


Video::Video(MemoryMap &mem_map):
m_memory_map(mem_map)
{

}

Video::~Video() {

}

void Video::tick() {

}

bool Video::lcd_display_enabled() {
    // Check bit 7 of the LCDC register
    uint8_t lcdc = this->read_io_register(LCDC);
    
    return ((lcdc >> 7) & 0x01) == 0x01;
}

bool Video::window_display_enabled() {
    // Check bit 5 of the LCDC register
    uint8_t lcdc = this->read_io_register(LCDC);

    return ((lcdc >> 5) & 0x01) == 0x01;
}

bool Video::sprite_display_enabled() {
    // Check bit 1 of the LCDC register
    uint8_t lcdc = this->read_io_register(LCDC);

    return ((lcdc >> 1) & 0x01) == 0x01;
}

bool Video::background_display_enabled() {
    // Check bit 0 of the LCDC register
    uint8_t lcdc = this->read_io_register(LCDC);

    return (lcdc & 0x01) == 0x01;
}

uint8_t Video::read_io_register(IORegisters_t reg) {
    return this->m_memory_map.read(reg);
}

void Video::write_io_register(IORegisters_t reg, uint8_t data) {
    this->m_memory_map.write(reg, data);
}
