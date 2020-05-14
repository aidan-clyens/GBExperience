#pragma once

#include <string>

#include "cpu/cpu.h"
#include "memory/memory_map.h"
#include "file_parser/file_parser.h"
#include "video/video.h"
#include "ui/ui.h"
#include "../debugger/debugger.h"


class GameBoy {
    public:
        GameBoy(bool=false);
        virtual ~GameBoy();

        void tick();

        void load_rom(const std::string &);

        std::string get_rom_name() const;
        bool is_display_open() const;
    
    private:
        CPU m_cpu;
        MemoryMap m_memory_map;
        Video m_video;
        UI m_ui;

        Debugger m_debugger;

        std::string m_rom_name;
};