#include "video.h"


Video::Video(MemoryMap &mem_map):
m_memory_map(mem_map)
{

}

Video::~Video() {

}

void Video::tick() {

}

/******   LCDC Register   ******/
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

SpriteSize_t Video::get_sprite_size() {
    // Check bit 2 of the LCDC register
    uint8_t lcdc = this->read_io_register(LCDC);
    bool bit2 = ((lcdc >> 2) & 0x01) == 0x01;

    return (bit2) ? SPRITEx16 : SPRITEx8;
}

TileDataTableSelect_t Video::get_tile_data_selected() {
    // Check bit 4 of the LCDC register
    uint8_t lcdc = this->read_io_register(LCDC);
    bool bit4 = ((lcdc >> 4) & 0x01) == 0x01;

    return (bit4) ? TILE_DATA_UNSIGNED : TILE_DATA_SIGNED;
}

TileMapTableSelect_t Video::get_window_tile_map_selected() {
    // Check bit 6 of the LCDC register
    uint8_t lcdc = this->read_io_register(LCDC);
    bool bit6 = ((lcdc >> 6) & 0x01) == 0x01;

    return (bit6) ? TILE_MAP_2 : TILE_MAP_1;
}

TileMapTableSelect_t Video::get_background_tile_map_selected() {
    // Check bit 3 of the LCDC register
    uint8_t lcdc = this->read_io_register(LCDC);
    bool bit3 = ((lcdc >> 3) & 0x01) == 0x01;

    return (bit3) ? TILE_MAP_2 : TILE_MAP_1;
}

/******   LCDC Register   ******/
VideoMode_t Video::get_video_mode() {
    // Check bits 0 and 1 of the LCDC STAT register
    uint8_t stat = this->read_io_register(STAT);
    return (VideoMode_t)(stat & 0x03);
}

bool Video::get_coincidence_flag() {
    // Check bit 2 of the LCDC STAT register
    uint8_t stat = this->read_io_register(STAT);
    return ((stat >> 2) & 0x01) == 0x01;
}

bool Video::coincidence_interrupt_enabled() {
    // Check bit 6 of the LCDC STAT register
    uint8_t stat = this->read_io_register(STAT);
    return ((stat >> 6) & 0x01) == 0x01;
}

bool Video::oam_interrupt_enabled() {
    // Check bit 5 of the LCDC STAT register
    uint8_t stat = this->read_io_register(STAT);
    return ((stat >> 5) & 0x01) == 0x01;
}

bool Video::vblank_interrupt_enabled() {
    // Check bit 4 of the LCDC STAT register
    uint8_t stat = this->read_io_register(STAT);
    return ((stat >> 4) & 0x01) == 0x01;
}

bool Video::hblank_interrupt_enabled() {
    // Check bit 3 of the LCDC STAT register
    uint8_t stat = this->read_io_register(STAT);
    return ((stat >> 3) & 0x01) == 0x01;
}

int Video::get_scroll_y() {
    return (int)this->read_io_register(SCY);
}

int Video::get_scroll_x() {
    return (int)this->read_io_register(SCX);
}

int Video::get_lcd_y_coordinate() {
    return (int)this->read_io_register(LY);
}

int Video::get_lcd_y_compare() {
    return (int)this->read_io_register(LYC);
}


uint8_t Video::read_io_register(IORegisters_t reg) {
    return this->m_memory_map.read(reg);
}

void Video::write_io_register(IORegisters_t reg, uint8_t data) {
    this->m_memory_map.write(reg, data);
}
