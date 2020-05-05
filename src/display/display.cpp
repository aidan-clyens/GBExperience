#include "display.h"


Display::Display():
m_display_open(false),
m_display_initialized(false)
{

}

Display::~Display() {
    if (m_display_initialized) {
        delete m_main_window;
    }
}

void Display::init_display(const std::string &title) {
    sf::VideoMode window_bounds(PIXEL_SIZE * LCD_WIDTH, PIXEL_SIZE * LCD_HEIGHT);
    bool fullscreen = false;
    unsigned framerate_limit = 60;
    bool vertical_sync_enabled = false;
    unsigned antialiasing_level = 0;

    m_window_settings.antialiasingLevel = antialiasing_level;

    if (fullscreen) {
        m_main_window = new sf::RenderWindow(window_bounds, title, sf::Style::Fullscreen, m_window_settings);
    }
    else {
        m_main_window = new sf::RenderWindow(window_bounds, title, sf::Style::Titlebar | sf::Style::Close, m_window_settings);
    }

    m_main_window->setFramerateLimit(framerate_limit);
    m_main_window->setVerticalSyncEnabled(vertical_sync_enabled);

    m_image.create(PIXEL_SIZE * LCD_WIDTH, PIXEL_SIZE * LCD_HEIGHT);

    m_display_open = true;
    m_display_initialized = true;
}

void Display::render(FrameBuffer &buffer) {
    this->poll_events();

    m_main_window->clear();
    
    this->draw_pixels(buffer);
    m_texture.loadFromImage(m_image);
    m_sprite.setTexture(m_texture, true);

    m_main_window->draw(m_sprite);

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

void Display::draw_pixels(FrameBuffer &buffer) {
    for (int y = 0; y < LCD_HEIGHT; y++) {
        for (int x = 0; x < LCD_WIDTH; x++) {
            Colour_t colour = buffer.get_pixel(x, y);
            sf::Color pixel_colour = this->get_pixel_colour(colour);
            this->set_pixel(x, y, pixel_colour);
        }
    }    
}

void Display::set_pixel(int x, int y, sf::Color colour) {
    for (int h = 0; h < PIXEL_SIZE; h++) {
        for (int w = 0; w < PIXEL_SIZE; w++) {
            m_image.setPixel(x * PIXEL_SIZE + w, y * PIXEL_SIZE + h, colour);
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