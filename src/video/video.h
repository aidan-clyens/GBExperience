#pragma once

#include "../memory/memory_map.h"
#include "../ui/ui_sfml.h"
#include "../debugger/logger.h"
#include "definitions.h"
#include "tile.h"
#include "sprite.h"
#include "framebuffer.h"


class Video {
    public:
        Video(MemoryMap &, UI_SFML &, bool=false);
        virtual ~Video();

        void tick(int);

        // LCDC Register
        bool lcd_display_enabled();
        void set_lcd_display_enabled(bool);
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
        void set_coincidence_flag(bool);
        bool coincidence_interrupt_enabled();
        bool oam_interrupt_enabled();
        bool vblank_interrupt_enabled();
        bool hblank_interrupt_enabled();

        // Position and Scrolling
        int get_scroll_y();
        int get_scroll_x();
        int get_line();
        int get_line_compare();
        int get_window_y();
        int get_window_x();

        // Palette
        Palette get_background_palette();
        Palette get_sprite_palette_0();
        Palette get_sprite_palette_1();

        // Draw
        void draw();
        void write_scanline(uint8_t);
        void draw_background_line(uint8_t);
        void draw_window_line(uint8_t);
        void draw_sprites();
        void draw_sprite(int);

        Colour_t get_real_colour(PixelColour_t, Palette);
        PixelColour_t get_pixel_colour_from_real_colour(Colour_t, Palette);

        uint8_t read_io_register(IORegisters_t);
        void write_io_register(IORegisters_t, uint8_t);

        FrameBuffer &get_buffer();

    private:
        MemoryMap &m_memory_map;
        UI_SFML &m_ui;
        int m_cycle_counter;
        int m_lines_drawn;

        bool m_headless;

        VideoMode_t m_current_video_mode;

        FrameBuffer m_buffer;

        void trigger_coincidence_interrupt();
        void increment_line();
        void reset_line();
};