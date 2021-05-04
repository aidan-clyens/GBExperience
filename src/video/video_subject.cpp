#include "video_subject.h"


void VideoSubject::attach(Observer *observer) {
    m_observers.push_back(observer);
}

void VideoSubject::notify() {
    for (int i = 0; i < m_observers.size(); i++) {
        m_observers[i]->update();
    }
}