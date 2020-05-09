#pragma once

#include <string>

#include "cpu/cpu.h"
#include "memory/memory_map.h"
#include "file_parser/file_parser.h"
#include "video/video.h"
#include "ui/ui.h"


class GameBoy {
    public:
        GameBoy(UI &);
        virtual ~GameBoy();

        void tick();

        void load_rom(const std::string &);

        std::string get_rom_name() const;
    
    private:
        CPU m_cpu;
        MemoryMap m_memory_map;
        Video m_video;

        std::string m_rom_name;
};