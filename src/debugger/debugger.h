#pragma once

#include <vector>

#include "../ui/ui.h"


typedef enum DebugAction {
    NONE,
    STEP,
    CONTINUE,
    BREAKPOINT,
    QUIT
} DebugAction_t;


class Debugger {
    public:
        Debugger(UI &);
        virtual ~Debugger();

        void tick(uint8_t);
        DebugAction_t get_input();

        void set_breakpoint(uint8_t);

    private:
        UI m_ui;

        bool m_stopped = true;

        std::vector<uint8_t> m_breakpoints;
};