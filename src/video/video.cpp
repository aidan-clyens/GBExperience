#include "video.h"


Video::Video(MemoryMap &mem_map):
m_memory_map(mem_map)
{
    m_current_video_mode = this->get_video_mode();
}

Video::~Video() {

}

void Video::tick() {
    this->trigger_interrupts();
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

void Video::set_video_mode(VideoMode_t video_mode) {
    uint8_t stat = this->read_io_register(STAT);

    stat &= ~0x03;
    stat |= video_mode;

    m_current_video_mode = video_mode;
    this->write_io_register(STAT, stat);
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

int Video::get_window_y() {
    return (int)this->read_io_register(WY);
}

int Video::get_window_x() {
    return (int)this->read_io_register(WX);
}


/******   Palette   ******/
Palette Video::get_background_palette() {
    Palette palette;
    uint8_t bgp = this->read_io_register(BGP);

    palette.colour0 = (Colour_t)(bgp & 0x03);
    palette.colour1 = (Colour_t)((bgp >> 2) & 0x03);
    palette.colour2 = (Colour_t)((bgp >> 4) & 0x03);
    palette.colour3 = (Colour_t)((bgp >> 6) & 0x03);

    return palette;
}


uint8_t Video::read_io_register(IORegisters_t reg) {
    return this->m_memory_map.read(reg);
}

void Video::write_io_register(IORegisters_t reg, uint8_t data) {
    this->m_memory_map.write(reg, data);
}

void Video::trigger_interrupts() {
    VideoMode_t video_mode = this->get_video_mode();
    bool trigger_vblank_interrupt = false;
    bool trigger_stat_interrupt = false;

    if (video_mode != m_current_video_mode) {
        switch (video_mode) {
            case HBLANK_Mode:
                if (this->hblank_interrupt_enabled()) {
                    trigger_stat_interrupt = true;
                }
                break;
            case VBLANK_Mode:
                if (this->vblank_interrupt_enabled()) {
                    trigger_vblank_interrupt = true;
                }
                break;
            case OAM_Mode:
                if (this->oam_interrupt_enabled()) {
                    trigger_stat_interrupt = true;
                }
                break;
        }
    }

    if (this->coincidence_interrupt_enabled() && this->get_coincidence_flag()) {
        trigger_stat_interrupt = true;
    }

    if (trigger_vblank_interrupt || trigger_stat_interrupt) {
        uint8_t interrupt_flag = this->read_io_register(IF);

        if (trigger_vblank_interrupt) {
            interrupt_flag |= 0x01;
        }

        if (trigger_stat_interrupt) {
            interrupt_flag |= 0x02;
        }

        this->write_io_register(IF, interrupt_flag);
    }

    m_current_video_mode = video_mode;
}