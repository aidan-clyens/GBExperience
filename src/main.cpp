#include <fstream>
#include <iostream>

#include "display/display.h"
#include "file_parser/file_parser.h"
#include "memory/memory.h"


int main(int argc, char** argv) {
    int rom_size = 32*1024;
    int ram_size = 8*1024;
    std::string rom_file = "roms/Tetris.gb";

    FileParser file_parser(rom_size);
    file_parser.load_rom(rom_file);
    
    Memory memory(ram_size);
    memory.init_memory();

    Display main_display(file_parser.get_rom_name());

    main_display.init_display();
    
    while (main_display.is_display_open()) {
        main_display.poll_events();
        main_display.render();
    }

    return 0;
}
