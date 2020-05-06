#include <fstream>
#include <iostream>

#include "display/display.h"
#include "gameboy.h"


int main(int argc, char** argv) {
    std::string rom_file = "roms/Tetris.gb";
    
    if (argc > 1) {
        rom_file = argv[1];
    }


    gb->load_rom(rom_file);

    main_display.init_display(gb->get_rom_name());

    while (main_display.is_display_open()) {
        gb.tick();

        main_display.poll_events();
        main_display.render();
    }

    return 0;
}
