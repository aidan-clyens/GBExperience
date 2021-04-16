#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

#include "../video/framebuffer.h"
#include "../video/definitions.h"
#include "../memory/memory_map.h"


const int PIXEL_SIZE = 4;


class UI_SFML {
    public:
        UI_SFML(MemoryMap &, bool=false);
        virtual ~UI_SFML();

        void init_display(const std::string &);

        void render(FrameBuffer &);

        bool is_display_enabled() const;
        void set_display_enabled(bool);

        void set_headless(bool);
        bool is_headless() const;

    private:
        void poll_events();
        void draw_pixels(FrameBuffer &);
        void set_pixel(int, int, sf::Color);

        void set_key_pressed(sf::Keyboard::Key, bool);

        sf::Color get_pixel_colour(Colour_t);
        sf::RenderWindow *m_main_window;
        sf::ContextSettings m_window_settings;

        sf::Image m_image;
        sf::Texture m_texture;
        sf::Sprite m_sprite;

        MemoryMap &m_memory_map;

        bool m_display_open;
        bool m_display_initialized;
        bool m_headless;
};