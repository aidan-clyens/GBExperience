#include <fstream>
#include <iostream>

#include "ui/ui.h"
#include "file_parser/file_parser.h"
#include "memory/memory_map.h"
#include "memory/memory.h"
#include "cpu/cpu.h"
#include "debugger/timing_analyzer.h"


const int ITERATION_COUNT = 5000;


MemoryMap setup_mem_map(uint8_t opcode) {
    MemoryMap memory_map;

    for (int i = 0; i < 2*ITERATION_COUNT; i++) {
        memory_map.write(0xA000 + i, opcode);
    }

    return memory_map;
}


int main(int argc, char** argv) {        
    TimingAnalyzer timing_analyzer("output/timing_analysis.csv");
    uint8_t opcode = 0x68; // 4 cycles
    int cycle_count = 4;
    long int expected_time = cycle_count * EXPECTED_CYCLE_TIME_NS;

    MemoryMap memory_map = setup_mem_map(opcode);

    CPU cpu(memory_map);
    cpu.write_register("PC", 0xA000);
    cpu.write_register("HL", 0xA100);

    long int dt; 
    for (int i = 0; i < ITERATION_COUNT; i++) {
        dt = cpu.tick();

        timing_analyzer.log_time(expected_time, dt);
    }
    
    timing_analyzer.save_times();

    return 0;
}
