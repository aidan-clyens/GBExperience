#pragma once

#include <chrono>

#include "../utils/observer.h"
#include "../utils/subject.h"


class VideoObserver : public Observer {
    public:
        VideoObserver(Subject*);
        virtual ~VideoObserver();

        void update() override;

        int get_framerate() const;
    
    private:
        Subject *m_subject;

        int m_framecount;
        int m_framerate;
        std::chrono::steady_clock::time_point m_last_frame_time;

        std::chrono::steady_clock::time_point get_time();
};