#pragma once

#include <vector>

#include "definitions.h"


class FrameBuffer {
    public:
        FrameBuffer(int, int);
        virtual ~FrameBuffer();

        Colour_t get_pixel(int, int);
        void set_pixel(int, int, Colour_t);

        void reset();
    
    private:
        std::vector<Colour_t> m_buffer;

        int m_width;
        int m_height;
};