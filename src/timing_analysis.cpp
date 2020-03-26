#include <fstream>
#include <iostream>

#include "display/display.h"
#include "file_parser/file_parser.h"
#include "memory/memory_map.h"
#include "memory/memory.h"
#include "cpu/cpu.h"
#include "debugger/timing_analyzer.h"


const int ITERATION_COUNT = 5000;
const float EXPECTED_FREQ_MHZ = 4.194304;
const long int EXPECTED_CYCLE_TIME_NS = 1000.0 / EXPECTED_FREQ_MHZ;


MemoryMap setup_mem_map(uint8_t opcode) {
    MemoryMap memory_map;
    memory_map.init_memory_map(nullptr);

    for (int i = 0; i < 2*ITERATION_COUNT; i++) {
        memory_map.write(0xA000 + i, opcode);
    }

    return memory_map;
}


int main(int argc, char** argv) {        
    TimingAnalyzer timing_analyzer("output/timing_analysis.csv");

    MemoryMap memory_map = setup_mem_map(0x68); // 4 cycles

    CPU cpu(memory_map);
    cpu.write_register("PC", 0xA000);
    cpu.write_register("HL", 0xA100);

    for (int i = 0; i < ITERATION_COUNT; i++) {
        timing_analyzer.get_start_time();

        uint8_t opcode = cpu.fetch_op();
        int cycle_count = cpu.decode_op(opcode);

        long int dt = timing_analyzer.get_time_difference_ns();

        while (dt < cycle_count * EXPECTED_CYCLE_TIME_NS) {
            // Wait until expected cycle time is reached
            dt = timing_analyzer.get_time_difference_ns();
        }


        timing_analyzer.log_time(cycle_count * EXPECTED_CYCLE_TIME_NS, dt);
    }
    
    timing_analyzer.save_times();

    return 0;
}
