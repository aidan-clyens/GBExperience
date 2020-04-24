#pragma once

#include <map>
#include <exception>

#include "memory.h"


class MemoryMap {
    public:
        MemoryMap();
        virtual ~MemoryMap();

        bool init_memory_map();
        void load_rom(void *);
        uint16_t write(uint16_t, uint8_t);
        uint8_t read(uint16_t);

        int get_index(uint16_t) const;
    
    private:
        int m_address_space[12];
        std::map<int, void*> m_memory_map;

        uint8_t m_interrupt_enable_register;
};
