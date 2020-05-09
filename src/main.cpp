#include <fstream>
#include <iostream>

#include "debugger/logger.h"
#include "ui/ui.h"
#include "gameboy.h"


int main(int argc, char** argv) {
    std::string rom_file = "roms/DrMario.gb";
    
    if (argc > 1) {
        rom_file = argv[1];
    }

    UI main_ui;
    std::unique_ptr<GameBoy> gb = std::make_unique<GameBoy>(main_ui);

    gb->load_rom(rom_file);

    main_ui.init_ui(gb->get_rom_name());

    while (main_ui.is_ui_open()) {
        gb->tick();
    }

    return 0;
}
