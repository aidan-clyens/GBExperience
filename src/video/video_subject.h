#pragma once

#include "../utils/subject.h"


class VideoSubject : public Subject {
    public:
        void attach(Observer *) override;
        void notify() override;

    private:
        std::vector<Observer *> m_observers;
};