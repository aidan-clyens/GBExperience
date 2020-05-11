#include "input.h"


Input::Input() {

}

Input::~Input() {

}

void Input::set_button_pressed(Buttons_t button, bool pressed) {
    switch (button) {
        case RIGHT:
            m_buttons_pressed.right_pressed = pressed;
            break;
        case LEFT:
            m_buttons_pressed.left_pressed = pressed;
            break;
        case UP:
            m_buttons_pressed.up_pressed = pressed;
            break;
        case DOWN:
            m_buttons_pressed.down_pressed = pressed;
            break;
        case A:
            m_buttons_pressed.a_pressed = pressed;
            break;
        case B:
            m_buttons_pressed.b_pressed = pressed;
            break;
        case SELECT:
            m_buttons_pressed.select_pressed = pressed;
            break;
        case START:
            m_buttons_pressed.start_pressed = pressed;
            break;
    }
}

bool Input::get_button_pressed(Buttons_t button) const {
    switch (button) {
        case RIGHT:
            return m_buttons_pressed.right_pressed;
        case LEFT:
            return m_buttons_pressed.left_pressed;
        case UP:
            return m_buttons_pressed.up_pressed;
        case DOWN:
            return m_buttons_pressed.down_pressed;
        case A:
            return m_buttons_pressed.a_pressed;
        case B:
            return m_buttons_pressed.b_pressed;
        case SELECT:
            return m_buttons_pressed.select_pressed;
        case START:
            return m_buttons_pressed.select_pressed;
    }
}

ButtonsPressed_t Input::get_input() {
    return m_buttons_pressed;
}

