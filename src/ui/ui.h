#pragma once

#include <iostream>

#include "../video/framebuffer.h"
#include "../memory/memory_map.h"


class UI {
    public:
        UI(MemoryMap &, bool=false);
        virtual ~UI();

        virtual void init_display(const std::string &);
        virtual void render(FrameBuffer &);

        void set_button_pressed(Buttons_t, bool);

        bool is_display_initialized() const;
        void set_display_initialized(bool);

        bool is_display_enabled() const;
        void set_display_enabled(bool);

        void set_headless(bool);
        bool is_headless() const;
    
    protected:
        MemoryMap &m_memory_map;

        bool m_display_open;
        bool m_display_initialized;
        bool m_headless;
};