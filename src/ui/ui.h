#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

#include "../video/framebuffer.h"
#include "../video/definitions.h"


const int PIXEL_SIZE = 4;


class UI {
    public:
        UI();
        virtual ~UI();

        void init_ui(const std::string &);

        void render(FrameBuffer &);
        void poll_events();
        void draw_pixels(FrameBuffer &);
        void set_pixel(int, int, sf::Color);

        sf::Color get_pixel_colour(Colour_t);

        bool is_ui_open() const;

    private:
        sf::RenderWindow *m_main_window;
        sf::ContextSettings m_window_settings;

        sf::Image m_image;
        sf::Texture m_texture;
        sf::Sprite m_sprite;

        bool m_ui_open;
        bool m_ui_initialized;
};