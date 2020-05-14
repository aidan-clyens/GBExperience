#include <fstream>
#include <iostream>

#include "debugger/logger.h"
#include "ui/ui.h"
#include "gameboy.h"


const std::string WHITESPACE = " \n\r\t\f\v";


std::string ltrim(const std::string &s) {
    size_t start = s.find_first_not_of(WHITESPACE);
    return (start == std::string::npos) ? "" : s.substr(start);
}

std::string rtrim(const std::string &s) {
    size_t end = s.find_last_not_of(WHITESPACE);
    return (end == std::string::npos) ? "" : s.substr(0, end + 1);
}

std::string trim(const std::string &s) {
    return rtrim(ltrim(s));
}


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
