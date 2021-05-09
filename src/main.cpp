#include <fstream>
#include <iostream>

#include <QtWidgets/QApplication>

#include "debugger/logger.h"
#include "utils/string_utils.h"
#include "gameboy.h"

int main(int argc, char** argv) {
    QApplication app(argc, argv);

    return app.exec();
}

// int main(int argc, char** argv) {
//     std::string rom_file = "";
//     bool debugger_enabled = false;
//     bool headless = false;

//     if (argc > 1) {
//         rom_file = argv[1];
//     }

//     if (argc > 2) {
//         for (int i = 2; i < argc; i++) {
//             std::string arg = trim(std::string(argv[i]));

//             if (arg == "--debug") {
//                 debugger_enabled = true;
//             }

//             if (arg == "--headless") {
//                 headless = true;
//             }

//             if (arg == "--warnings") {
//                 enable_warn_logging();
//             }

//             if (arg == "--trace") {
//                 enable_cpu_logging();
//             }
//         }
//     }

//     GameBoy gb(debugger_enabled, headless);
//     gb.load_rom(rom_file);

//     while (gb.is_display_open()) {
//         gb.tick();
//     }

//     return 0;
// }
