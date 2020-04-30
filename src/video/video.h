#pragma once

#include "../memory/memory_map.h"


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

        uint8_t read_io_register(IORegisters_t);
        void write_io_register(IORegisters_t, uint8_t);

    private:
        MemoryMap &m_memory_map;
};