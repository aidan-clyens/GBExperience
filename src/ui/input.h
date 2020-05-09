#pragma once


#include "../memory/memory_map.h"


typedef enum Buttons {
    RIGHT,
    LEFT,
    UP,
    DOWN,
    A,
    B,
    SELECT,
    START
} Buttons_t;


typedef enum JoypadPorts {
    P10 = 0x01,
    P11 = 0x02,
    P12 = 0x04,
    P13 = 0x08,
    P14 = 0x10,
    P15 = 0x20
} JoypadPorts_t;


class Input {
    public:
        Input(MemoryMap &);
        virtual ~Input();

        void set_button_pressed(Buttons_t, bool);
        bool get_button_pressed(Buttons_t) const;

        void set_input();
    
    private:
        MemoryMap &m_memory_map;

        bool m_right;
        bool m_left;
        bool m_up;
        bool m_down;
        bool m_a;
        bool m_b;
        bool m_select;
        bool m_start;
};