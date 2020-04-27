#include <fstream>
#include <iostream>

#include "display/display.h"
#include "gameboy.h"


int main(int argc, char** argv) {
    int rom_size = 32*1024;

    std::string rom_file = "roms/Tetris.gb";
    
    if (argc > 1) {
        rom_file = argv[1];
    }


    GameBoy gb;
    gb.load_rom(rom_file, rom_size);

    Display main_display(gb.get_rom_name());

    main_display.init_display();
    
    while (main_display.is_display_open()) {
        gb.tick();

        main_display.poll_events();
        main_display.render();
    }

    return 0;
}
