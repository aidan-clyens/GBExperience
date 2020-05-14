#pragma once


#include "../ui/ui.h"


class Debugger {
    public:
        Debugger(UI &);
        virtual ~Debugger();

        void tick();
    
    private:
        UI m_ui;
};