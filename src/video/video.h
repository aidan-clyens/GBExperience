#pragma once

#include "../memory/memory_map.h"
#include "tile.h"


typedef enum SpriteSize {
    SPRITEx8,
    SPRITEx16
} SpriteSize_t;


typedef enum TileDataTableSelect {
    TILE_DATA_UNSIGNED,
    TILE_DATA_SIGNED
} TileDataTableSelect_t;


typedef enum TileMapTableSelect {
    TILE_MAP_1 = 0x9800,
    TILE_MAP_2 = 0x9C00
} TileMapTableSelect_t;


typedef enum VideoMode {
    HBLANK_Mode = 0x00,
    VBLANK_Mode = 0x01,
    OAM_Mode = 0x02,
    Data_Transfer_Mode = 0x03
} VideoMode_t;


typedef enum Colour {
    WHITE = 0x0,
    LIGHT_GRAY = 0x1,
    DARK_GRAY = 0x2,
    BLACK = 0x3
} Colour_t;


struct Palette {
    Colour_t colour0;
    Colour_t colour1;
    Colour_t colour2;
    Colour_t colour3;
};


class Video {
    public:
        Video(MemoryMap &);
        virtual ~Video();

        void tick();

        // LCDC Register
        bool lcd_display_enabled();
        bool window_display_enabled();
        bool sprite_display_enabled();
        bool background_display_enabled();
        SpriteSize_t get_sprite_size();
        TileDataTableSelect_t get_tile_data_selected();
        TileMapTableSelect_t get_window_tile_map_selected();
        TileMapTableSelect_t get_background_tile_map_selected();

        // LCDC STAT Register
        VideoMode_t get_video_mode();
        void set_video_mode(VideoMode_t);
        bool get_coincidence_flag();
        bool coincidence_interrupt_enabled();
        bool oam_interrupt_enabled();
        bool vblank_interrupt_enabled();
        bool hblank_interrupt_enabled();

        // Position and Scrolling
        int get_scroll_y();
        int get_scroll_x();
        int get_lcd_y_coordinate();
        int get_lcd_y_compare();
        int get_window_y();
        int get_window_x();

        // Palette
        Palette get_background_palette();
        Palette get_sprite_palette_0();
        Palette get_sprite_palette_1();

        uint8_t read_io_register(IORegisters_t);
        void write_io_register(IORegisters_t, uint8_t);

    private:
        MemoryMap &m_memory_map;

        VideoMode_t m_current_video_mode;

        void trigger_interrupts();
};