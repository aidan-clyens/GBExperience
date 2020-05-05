#pragma once

#include <SFML/Graphics.hpp>


class Display {
    public:
        Display(const std::string &);
        virtual ~Display();

        void init_display();

        void render();
        void poll_events();

        bool is_display_open() const;

    private:
        sf::RenderWindow *m_main_window;
        sf::ContextSettings m_window_settings;

        std::string m_title;
        bool m_display_open;
        bool m_display_initialized;
};