#include <fstream>
#include <iostream>

#include "display/display.h"
#include "gameboy.h"


int main(int argc, char** argv) {
    std::string rom_file = "roms/DrMario.gb";
    
    if (argc > 1) {
        rom_file = argv[1];
    }

    Display main_display;
    std::unique_ptr<GameBoy> gb = std::make_unique<GameBoy>(main_display);

    gb->load_rom(rom_file);

    main_display.init_display(gb->get_rom_name());

    while (main_display.is_display_open()) {
        gb->tick();
    }

    return 0;
}
