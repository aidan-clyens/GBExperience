#include <fstream>
#include <iostream>

#include "display/display.h"
#include "file_parser/file_parser.h"
#include "memory/memory_map.h"
#include "memory/memory.h"
#include "cpu/cpu.h"
#include "debugger/timing_analyzer.h"


int main(int argc, char** argv) {
    int rom_size = 32*1024;
    std::string rom_file = "roms/Tetris.gb";

    TimingAnalyzer timing_analyzer("output/timing.csv");

    FileParser file_parser(rom_size);
    file_parser.load_rom(rom_file);
    
    MemoryMap memory_map;
    memory_map.init_memory_map(file_parser.get_buffer_ptr());

    CPU cpu(memory_map);

    Display main_display(file_parser.get_rom_name());

    main_display.init_display();
    
    while (main_display.is_display_open()) {
        timing_analyzer.get_start_time();

        uint8_t opcode =  cpu.fetch_op();

        cpu.decode_op(opcode);

        main_display.poll_events();
        main_display.render();

        long int dt = timing_analyzer.get_time_difference_us();
        timing_analyzer.log_cycle_time(opcode, dt);
    }

    timing_analyzer.save_cycle_times();

    return 0;
}
