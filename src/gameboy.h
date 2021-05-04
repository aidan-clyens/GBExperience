#pragma once

#include <string>

#include "cpu/cpu.h"
#include "memory/memory_map.h"
#include "file_parser/file_parser.h"
#include "video/video.h"
#include "video/video_observer.h"
#include "ui/ui_sfml.h"
#include "timer/timer.h"
#include "debugger/debugger.h"


class GameBoy {
    public:
        GameBoy(bool=false, bool=false);
        virtual ~GameBoy();

        void tick();

        void load_rom(const std::string &);

        std::string get_rom_name() const;
        bool is_display_open() const;

        void quit();
    
    private:
        CPU m_cpu;
        MemoryMap m_memory_map;
        Video m_video;
        UI m_ui;
        Timer m_timer;

        Debugger m_debugger;
        VideoObserver m_framerate_observer;

        bool m_debugger_enabled;

        std::string m_rom_name;

        std::chrono::steady_clock::time_point m_last_time;

        // CPU Timing
        long int get_time_difference_ns();
        std::chrono::steady_clock::time_point get_time();
};