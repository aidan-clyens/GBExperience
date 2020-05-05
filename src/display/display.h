#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

#include "../video/framebuffer.h"
#include "../video/definitions.h"


const int PIXEL_SIZE = 4;


class Display {
    public:
        Display(const std::string &);
        virtual ~Display();

        void init_display();

        void render(FrameBuffer &);
        void poll_events();
        void draw_pixels(FrameBuffer &);
        void set_pixel(int, int, sf::Color);

        sf::Color get_pixel_colour(Colour_t);

        bool is_display_open() const;

    private:
        sf::RenderWindow *m_main_window;
        sf::ContextSettings m_window_settings;

        sf::Image m_image;
        sf::Texture m_texture;
        sf::Sprite m_sprite;

        std::string m_title;
        bool m_display_open;
        bool m_display_initialized;
};