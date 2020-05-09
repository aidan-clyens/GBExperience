#pragma once


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


class Input {
    public:
        Input();
        virtual ~Input();

        void set_button_pressed(Buttons_t, bool);
        bool get_button_pressed(Buttons_t) const;
    
    private:
        bool m_right;
        bool m_left;
        bool m_up;
        bool m_down;
        bool m_a;
        bool m_b;
        bool m_select;
        bool m_start;
};