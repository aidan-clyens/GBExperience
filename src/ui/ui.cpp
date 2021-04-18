#include "ui.h"


UI::UI(MemoryMap &mem_map, bool headless):
m_memory_map(mem_map),
m_display_open(false),
m_display_initialized(false),
m_headless(headless)
{

}

UI::~UI() {

}

void UI::init_display(const std::string &rom_name) {
    this->set_display_enabled(true);
}

void UI::render(FrameBuffer &buffer) {

}

void UI::set_button_pressed(Buttons_t key, bool pressed) {
    m_memory_map.set_button_pressed(key, pressed);
}

void UI::set_display_initialized(bool initialized) {
    m_display_initialized = initialized;
}


bool UI::is_display_initialized() const {
    return m_display_initialized;
}

void UI::set_display_enabled(bool enabled) {
    m_display_open = enabled;
}


bool UI::is_display_enabled() const {
    return m_display_open;
}

void UI::set_headless(bool value) {
    m_headless = value;
}

bool UI::is_headless() const {
    return m_headless;
}