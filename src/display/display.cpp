#include "display.h"


Display::Display(const std::string &title):
m_title(title),
m_display_open(false),
m_display_initialized(false)
{

}

Display::~Display() {
    if (m_display_initialized) {
        delete m_main_window;
    }
}

void Display::init_display() {
    sf::VideoMode window_bounds(4*160, 4*144);
    bool fullscreen = false;
    unsigned framerate_limit = 60;
    bool vertical_sync_enabled = false;
    unsigned antialiasing_level = 0;

    m_window_settings.antialiasingLevel = antialiasing_level;

    if (fullscreen) {
        m_main_window = new sf::RenderWindow(window_bounds, m_title, sf::Style::Fullscreen, m_window_settings);
    }
    else {
        m_main_window = new sf::RenderWindow(window_bounds, m_title, sf::Style::Titlebar | sf::Style::Close, m_window_settings);
    }

    m_main_window->setFramerateLimit(framerate_limit);
    m_main_window->setVerticalSyncEnabled(vertical_sync_enabled);

    m_display_open = true;
    m_display_initialized = true;
}

void Display::render() {
    m_main_window->clear();
    m_main_window->display();
}

void Display::poll_events() {
    sf::Event event;

    while (m_main_window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            m_display_open = false;
            m_main_window->close();
        }
    }
}

sf::Color Display::get_pixel_colour(Colour_t colour) {
    switch (colour) {
        case WHITE:
            return sf::Color(255, 255, 255);
        case LIGHT_GRAY:
            return sf::Color(170, 170, 170);
        case DARK_GRAY:
            return sf::Color(85, 85, 85);
        case BLACK:
            return sf::Color(0, 0, 0);
        }
}

bool Display::is_display_open() const {
    return m_display_open;
}