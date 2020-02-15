#pragma once

#include <cstdint>
#include <exception>


class Memory {
    public:
        Memory(int);
        virtual ~Memory();

        bool init_memory();

        void write_memory(uint16_t, uint8_t);
        uint8_t read_memory(uint16_t);

        int get_size() const;

    private:
        uint8_t *m_memory; 
        int m_memory_size;
};