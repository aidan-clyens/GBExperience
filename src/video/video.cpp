#include "video.h"


Video::Video(MemoryMap &mem_map):
m_memory_map(mem_map),
m_cycle_counter(0),
m_background_buffer(MAP_SIZE, MAP_SIZE)
{
    m_current_video_mode = this->get_video_mode();
}

Video::~Video() {

}

void Video::tick(int cycles) {
    m_cycle_counter += cycles;

    switch (m_current_video_mode) {
        case HBLANK_Mode:
            if (m_cycle_counter > HBLANK_CLOCKS) {
                m_cycle_counter = m_cycle_counter % HBLANK_CLOCKS;

                this->write_scanline(this->get_line());

                #ifdef DEBUG
                std::cout << "Scanlines drawn: " << this->get_line() << std::endl;
                #endif
                this->increment_line();

                if (this->get_line() == 144) {
                    #ifdef DEBUG
                    std::cout << "Switching to V-Blank mode" << std::endl;
                    #endif
                    this->set_video_mode(VBLANK_Mode);
                } else {
                    #ifdef DEBUG
                    std::cout << "Switching to OAM mode" << std::endl;
                    #endif
                    this->set_video_mode(OAM_Mode);
                }
            }
            break;
        case VBLANK_Mode:
            if (m_cycle_counter > VBLANK_SCANLINE_CLOCKS) {
                m_cycle_counter = m_cycle_counter % VBLANK_SCANLINE_CLOCKS;

                this->increment_line();

                if (this->get_line() == 154) {
                    this->reset_line();

                    #ifdef DEBUG
                    std::cout << "Switching to OAM mode" << std::endl;
                    #endif
                    this->set_video_mode(OAM_Mode);
                }
            }
            break;
        case OAM_Mode:
            if (m_cycle_counter > OAM_CLOCKS) {
                m_cycle_counter = m_cycle_counter % OAM_CLOCKS;

                #ifdef DEBUG
                std::cout << "Switching to Data Transfer mode" << std::endl;
                #endif
                this->set_video_mode(Data_Transfer_Mode);
            }
            break;
        case Data_Transfer_Mode:
            if (m_cycle_counter > DATA_TRANSFER_CLOCKS) {
                m_cycle_counter = m_cycle_counter % DATA_TRANSFER_CLOCKS;

                this->trigger_coincidence_interrupt();

                #ifdef DEBUG
                std::cout << "Switching to H-Blank mode" << std::endl;
                #endif
                this->set_video_mode(HBLANK_Mode);
            }
            break;
    }
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

    bool vblank_interrupt_set = false;
    bool lcdc_stat_interrupt_set = false;
    switch (video_mode) {
        case HBLANK_Mode:
            if (this->hblank_interrupt_enabled()) {
                lcdc_stat_interrupt_set = true;
            }
            break;
        case VBLANK_Mode:
            if (this->vblank_interrupt_enabled()) {
                vblank_interrupt_set = true;
            }
            break;
        case OAM_Mode:
            if (this->oam_interrupt_enabled()) {
                lcdc_stat_interrupt_set = true;
            }
            break;
    }

    uint8_t interrupt_flag = this->read_io_register(IF);

    if (vblank_interrupt_set) {
        interrupt_flag |= 0x01;
    }
    
    if (lcdc_stat_interrupt_set) {
        interrupt_flag |= 0x02;
    }

    this->write_io_register(IF, interrupt_flag);
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

int Video::get_line() {
    return (int)this->read_io_register(LY);
}

int Video::get_line_compare() {
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

Palette Video::get_sprite_palette_0() {
    Palette palette;
    uint8_t obp0 = this->read_io_register(OBP0);

    palette.colour1 = (Colour_t)((obp0 >> 2) & 0x03);
    palette.colour2 = (Colour_t)((obp0 >> 4) & 0x03);
    palette.colour3 = (Colour_t)((obp0 >> 6) & 0x03);

    return palette;
}

Palette Video::get_sprite_palette_1() {
    Palette palette;
    uint8_t obp1 = this->read_io_register(OBP1);

    palette.colour1 = (Colour_t)((obp1 >> 2) & 0x03);
    palette.colour2 = (Colour_t)((obp1 >> 4) & 0x03);
    palette.colour3 = (Colour_t)((obp1 >> 6) & 0x03);

    return palette;
}

/******   Draw   ******/
void Video::write_scanline(uint8_t line) {
    if (!this->lcd_display_enabled()) return;

    if (this->background_display_enabled()) {
        this->draw_background_line(line);
    }

    if (this->window_display_enabled()) {
        // this->draw_window_line(line);
    }
}

void Video::draw_background_line(uint8_t line) {
    Palette palette = this->get_background_palette();
    TileDataTableSelect_t tile_data_set = this->get_tile_data_selected();
    TileMapTableSelect_t tile_map = this->get_background_tile_map_selected();

    unsigned int scroll_x = this->get_scroll_x();
    unsigned int scroll_y = this->get_scroll_y();

    unsigned int y = line;

    for (unsigned int x = 0; x < LCD_WIDTH; x++) {
        // Add scroll to current coordinates
        unsigned int sc_x = x + scroll_x;
        unsigned int sc_y = y + scroll_y;

        // Background wraps around
        unsigned int bg_x = sc_x % MAP_SIZE;
        unsigned int bg_y = sc_y % MAP_SIZE;

        // Get tile index
        unsigned int tile_x = bg_x / TILE_WIDTH;
        unsigned int tile_y = bg_y / TILE_HEIGHT;
    
        // Get tile from tile data
        unsigned int tile_index = tile_y * TILES_PER_LINE + tile_x;
        uint16_t tile_id_address = (uint16_t)tile_map + tile_index;
        uint8_t tile_id = m_memory_map.read(tile_id_address);

        // Depending on the selected Tile Data Set, index is either signed or unsigned
        unsigned int tile_offset = (tile_data_set == TILE_DATA_UNSIGNED) ? tile_id * TILE_BYTE_LENGTH : (static_cast<int8_t>(tile_id) + 128) * TILE_BYTE_LENGTH;
        uint16_t tile_address = (uint16_t)tile_data_set + tile_offset + (tile_y * 2);
    
        TileRow row(tile_address, m_memory_map);

        PixelColour_t pixel = row.get_pixel(x);
        Colour_t real_pixel = this->get_real_colour(pixel, palette);
        m_background_buffer.set_pixel(x, y, real_pixel);
    }
}

Colour_t Video::get_real_colour(PixelColour_t colour, Palette palette) {
    switch (colour) {
        case Colour0:
            return palette.colour0;
        case Colour1:
            return palette.colour1;
        case Colour2:
            return palette.colour2;
        case Colour3:
            return palette.colour3;
    }
}


uint8_t Video::read_io_register(IORegisters_t reg) {
    return this->m_memory_map.read(reg);
}

void Video::write_io_register(IORegisters_t reg, uint8_t data) {
    this->m_memory_map.write(reg, data);
}

void Video::trigger_coincidence_interrupt() {
    if (this->coincidence_interrupt_enabled()) {
        if (this->get_coincidence_flag()) {
            uint8_t interrupt_flag = this->read_io_register(IF);

            interrupt_flag |= 0x02;

            this->write_io_register(IF, interrupt_flag);
        }
    }
}

void Video::increment_line() {
    this->m_memory_map.increment_io_counter(LY);
}

void Video::reset_line() {
    this->write_io_register(LY, 0);
}

FrameBuffer &Video::get_background_buffer() {
    return m_background_buffer;
}
