#pragma once

#include "../memory/memory_map.h"
#include "../memory/mem_io.h"


class Timer {
    public:
        Timer(MemoryMap &);
        virtual ~Timer();

        void tick(int);
    
    private:
        MemoryMap &m_memory_map;

        int m_cycle_counter;
};