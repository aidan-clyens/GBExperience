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

    GameBoy gb;
    gb.load_rom(rom_file);

    while (gb.is_display_open()) {
        gb.tick();
    }

    return 0;
}
