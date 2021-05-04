#pragma once

#include <vector>

#include "observer.h"


class Subject {
    public:
        virtual void attach(Observer*) = 0;
        virtual void notify() = 0;
};