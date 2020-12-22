#include "timer.h"


#define DIV_CYCLES  256


Timer::Timer(MemoryMap &memory_map):
m_memory_map(memory_map),
m_cycle_counter(0)
{

}

Timer::~Timer() {

}

void Timer::tick(int cycles) {
    m_cycle_counter += cycles;

    if (m_cycle_counter > DIV_CYCLES) {
        m_memory_map.increment_io_counter(DIV);
        m_cycle_counter = 0;
    }
}
