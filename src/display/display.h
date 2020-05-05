#pragma once

#include <SFML/Graphics.hpp>

#include "../video/framebuffer.h"
#include "../video/definitions.h"


class Display {
    public:
        Display(const std::string &);
        virtual ~Display();

        void init_display();

        void render();
        void poll_events();

        sf::Color get_pixel_colour(Colour_t);

        bool is_display_open() const;

    private:
        sf::RenderWindow *m_main_window;
        sf::ContextSettings m_window_settings;

        std::string m_title;
        bool m_display_open;
        bool m_display_initialized;
};