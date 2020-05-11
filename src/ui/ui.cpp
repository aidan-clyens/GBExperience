#include "ui.h"


UI::UI(MemoryMap &mem_map):
m_display_open(false),
m_display_initialized(false)
{

}

UI::~UI() {
    if (m_display_initialized) {
        delete m_main_window;
    }
}

void UI::init_display(const std::string &title) {
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
    m_main_window->setKeyRepeatEnabled(false);

    m_image.create(PIXEL_SIZE * LCD_WIDTH, PIXEL_SIZE * LCD_HEIGHT);

    m_display_open = true;
    m_display_initialized = true;
}

void UI::render(FrameBuffer &buffer) {
    this->poll_events();

    m_main_window->clear();
    
    this->draw_pixels(buffer);
    m_texture.loadFromImage(m_image);
    m_sprite.setTexture(m_texture, true);

    m_main_window->draw(m_sprite);

    m_main_window->display();
}

void UI::poll_events() {
    sf::Event event;

    while (m_main_window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            m_display_open = false;
            m_main_window->close();
        }
        else if (event.type == sf::Event::KeyPressed) {
            sf::Keyboard::Key key = event.key.code;
            this->set_key_pressed(key, true);
        }
        else if (event.type == sf::Event::KeyReleased) {
            sf::Keyboard::Key key = event.key.code;
            this->set_key_pressed(key, false);
        }
    }
}

void UI::draw_pixels(FrameBuffer &buffer) {
    for (int y = 0; y < LCD_HEIGHT; y++) {
        for (int x = 0; x < LCD_WIDTH; x++) {
            Colour_t colour = buffer.get_pixel(x, y);
            sf::Color pixel_colour = this->get_pixel_colour(colour);
            this->set_pixel(x, y, pixel_colour);
        }
    }    
}

void UI::set_pixel(int x, int y, sf::Color colour) {
    for (int h = 0; h < PIXEL_SIZE; h++) {
        for (int w = 0; w < PIXEL_SIZE; w++) {
            m_image.setPixel(x * PIXEL_SIZE + w, y * PIXEL_SIZE + h, colour);
        }
    }
}

void UI::set_key_pressed(sf::Keyboard::Key key, bool pressed) {
    switch (key) {
        case sf::Keyboard::Key::W:
            m_input.set_button_pressed(UP, pressed);
            break;
        case sf::Keyboard::Key::A:
            m_input.set_button_pressed(LEFT, pressed);
            break;
        case sf::Keyboard::Key::S:
            m_input.set_button_pressed(DOWN, pressed);
            break;
        case sf::Keyboard::Key::D:
            m_input.set_button_pressed(RIGHT, pressed);
            break;
        case sf::Keyboard::Key::Comma:
            m_input.set_button_pressed(A, pressed);
            break;
        case sf::Keyboard::Key::Period:
            m_input.set_button_pressed(B, pressed);
            break;
        case sf::Keyboard::Key::Enter:
            m_input.set_button_pressed(SELECT, pressed);
            break;
        case sf::Keyboard::Key::Escape:
            m_input.set_button_pressed(START, pressed);
            break;
    }
}

sf::Color UI::get_pixel_colour(Colour_t colour) {
    switch (colour) {
        case WHITE:
            return sf::Color(255, 255, 255);
        case LIGHT_GRAY:
            return sf::Color(170, 170, 170);
        case DARK_GRAY:
            return sf::Color(85, 85, 85);
        case BLACK:
            return sf::Color(0, 0, 0);
        default:
            return sf::Color(255, 255, 255);
        }
}

bool UI::is_display_enabled() const {
    return m_display_open;
}