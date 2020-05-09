#include "input.h"


Input::Input(MemoryMap &mem_map):
m_memory_map(mem_map),
m_right(false),
m_left(false),
m_up(false),
m_down(false),
m_a(false),
m_b(false),
m_select(false),
m_start(false)
{

}

Input::~Input() {

}

void Input::set_button_pressed(Buttons_t button, bool pressed) {
    switch (button) {
        case RIGHT:
            m_right = pressed;
            break;
        case LEFT:
            m_left = pressed;
            break;
        case UP:
            m_up = pressed;
            break;
        case DOWN:
            m_down = pressed;
            break;
        case A:
            m_a = pressed;
            break;
        case B:
            m_b = pressed;
            break;
        case SELECT:
            m_select = pressed;
            break;
        case START:
            m_select = pressed;
            break;
    }

    this->set_input();
}

bool Input::get_button_pressed(Buttons_t button) const {
    switch (button) {
        case RIGHT:
            return m_right;
        case LEFT:
            return m_left;
        case UP:
            return m_up;
        case DOWN:
            return m_down;
        case A:
            return m_a;
        case B:
            return m_b;
        case SELECT:
            return m_select;
        case START:
            return m_select;
    }
}

void Input::set_input() {
    uint8_t p1 = m_memory_map.read(P1);

    if (this->dpad_toggled()) {
        if (m_right) {
            p1 &= ~P10;
        }

        if (m_left) {
            p1 &= ~P11;
        }

        if (m_up) {
            p1 &= ~P12;
        }

        if (m_down) {
            p1 &= ~P13;
        }
    }

    if (this->buttons_toggled()) {
        if (m_a) {
            p1 &= ~P10;
        }

        if (m_b) {
            p1 &= ~P11;
        }

        if (m_select) {
            p1 &= ~P12;
        }

        if (m_start) {
            p1 &= ~P13;
        }
    }

    m_memory_map.write(P1, p1);
}

bool Input::dpad_toggled() const {
    uint8_t p1 = m_memory_map.read(P1);

    // DPAD is toggled if P14 is set low
    return (p1 & P14) == 0;
}

bool Input::buttons_toggled() const {
    uint8_t p1 = m_memory_map.read(P1);

    // Buttons are toggled if P15 is set low
    return (p1 & P15) == 0;
}
