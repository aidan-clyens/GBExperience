#pragma once

#include <exception>

#include "memory.h"
#include "mem_io.h"
#include "../file_parser/cartridge.h"
#include "../video/definitions.h"
#include "../debugger/logger.h"


typedef enum InterruptFlag {
    VBLANK = 0x01,
    LCD_STAT = 0x02,
    TIMER = 0x04,
    SERIAL = 0x08,
    JOYPAD = 0x10
} InterruptFlag_t;


class MemoryMap {
    public:
        MemoryMap();
        virtual ~MemoryMap();

        void init_memory_map();
        void load_rom(Cartridge*);
        uint16_t write(uint16_t, uint8_t);
        uint8_t read(uint16_t);

        uint16_t write_vram(uint16_t, uint8_t);
        uint8_t read_vram(uint16_t);
        uint16_t write_oam(uint16_t, uint8_t);
        uint8_t read_oam(uint16_t);

        void dma_transfer(uint8_t);

        bool get_interrupt_enable_bit(InterruptFlag_t);
        bool get_interrupt_flag_bit(InterruptFlag_t);
        void set_interrupt_enable_bit(InterruptFlag_t, bool);
        void set_interrupt_flag_bit(InterruptFlag_t, bool);

        void set_button_pressed(Buttons_t, bool);

        void increment_io_counter(IORegisters_t);

    private:
        int m_address_space[12];

        Memory *m_vram;
        Memory *m_oam;
        Memory *m_internal_ram;
        Memory *m_high_ram;

        Cartridge *m_cartridge;

        IO m_io;
};
