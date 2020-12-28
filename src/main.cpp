#include <fstream>
#include <iostream>

#include "debugger/logger.h"
#include "utils/string_utils.h"
#include "ui/ui.h"
#include "gameboy.h"


int main(int argc, char** argv) {
    std::string rom_file = "";
    bool debugger_enabled = false;
    bool headless = false;

    if (argc > 1) {
        rom_file = argv[1];
    }

    if (argc > 2) {
        std::string arg = trim(std::string(argv[2]));

        if (arg == "--debug") {
            debugger_enabled = true;
        }
        else if (arg == "--warnings") {
            enable_warn_logging();
        }
        else if (arg == "--trace") {
            enable_cpu_logging();
        }
        else if (arg == "--headless") {
            headless = true;
        }
    }

    GameBoy gb(debugger_enabled, headless);
    gb.load_rom(rom_file);

    while (gb.is_display_open()) {
        gb.tick();
    }

    return 0;
}
