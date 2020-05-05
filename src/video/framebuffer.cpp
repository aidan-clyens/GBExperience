#include "framebuffer.h"


FrameBuffer::FrameBuffer(int w, int h):
m_width(w),
m_height(h)
{
    for (int i = 0; i < (w * h); i++) {
        m_buffer.push_back(WHITE);
    }
}

FrameBuffer::~FrameBuffer() {

}

Colour_t FrameBuffer::get_pixel(int x, int y) {
    int index = y * m_width + x;
    return m_buffer[index];
}

void FrameBuffer::set_pixel(int x, int y, Colour_t colour) {
    int index = y * m_width + x;
    m_buffer[index] = colour;
}

void FrameBuffer::reset() {
    for (int y = 0; y < m_height; y++) {
        for (int x = 0; x < m_width; x++) {
            this->set_pixel(x, y, WHITE);
        }
    }
}