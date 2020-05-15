#pragma once


#include "../ui/ui.h"


typedef enum DebugAction {
    NONE,
    STEP,
    CONTINUE,
    QUIT
} DebugAction_t;


class Debugger {
    public:
        Debugger(UI &);
        virtual ~Debugger();

        void tick(uint8_t);
        DebugAction_t get_input();
    
    private:
        UI m_ui;
};