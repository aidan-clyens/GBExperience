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

        void tick(uint16_t);
        DebugAction_t get_input();

        void set_breakpoint(uint16_t);

        bool quit() const;

    private:
        UI m_ui;

        bool m_stopped = true;
        bool m_quit = false;

        std::vector<uint16_t> m_breakpoints;
};