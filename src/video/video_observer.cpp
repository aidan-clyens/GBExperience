#include "video_observer.h"
#include <iostream>


VideoObserver::VideoObserver(Subject *subject):
m_subject(subject),
m_framecount(0),
m_framerate(0),
m_last_frame_time(this->get_time())
{
    m_subject->attach(this);
}

VideoObserver::~VideoObserver() {

}

void VideoObserver::update() {
    std::chrono::steady_clock::time_point time = get_time();
    int ms = std::chrono::duration_cast<std::chrono::milliseconds>(time - m_last_frame_time).count();

    m_framecount++;

    if (ms > 1000) {
        m_framerate = (float)m_framecount * 1000 / (float)ms;

        m_last_frame_time = time;
        m_framecount = 0;
    }
}

int VideoObserver::get_framerate() const {
    return m_framerate;
}

std::chrono::steady_clock::time_point VideoObserver::get_time() {
    return std::chrono::steady_clock::now();
}