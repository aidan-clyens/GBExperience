#pragma once


#include <cstdint>

#include "../debugger/logger.h"


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


typedef struct ButtonsPressed {
    bool left_pressed = false;
    bool right_pressed = false;
    bool up_pressed = false;
    bool down_pressed = false;
    bool a_pressed = false;
    bool b_pressed = false;
    bool select_pressed = false;
    bool start_pressed = false;
} ButtonsPressed_t;


class Input {
    public:
        Input();
        virtual ~Input();

        void set_button_pressed(Buttons_t, bool);
        bool get_button_pressed(Buttons_t) const;

        ButtonsPressed_t get_input();

    private:
        ButtonsPressed_t m_buttons_pressed;
};