#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

#include "../video/framebuffer.h"
#include "../video/definitions.h"
#include "../memory/memory_map.h"
#include "input.h"


const int PIXEL_SIZE = 4;


class UI {
    public:
        UI(MemoryMap &);
        virtual ~UI();

        void init_display(const std::string &);

        void render(FrameBuffer &);
        void poll_events();
        void draw_pixels(FrameBuffer &);
        void set_pixel(int, int, sf::Color);

        sf::Color get_pixel_colour(Colour_t);

        bool is_display_enabled() const;

    private:
        sf::RenderWindow *m_main_window;
        sf::ContextSettings m_window_settings;

        sf::Image m_image;
        sf::Texture m_texture;
        sf::Sprite m_sprite;

        Input m_input;

        bool m_display_open;
        bool m_display_initialized;
};