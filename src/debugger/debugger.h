#pragma once

#include <sstream>
#include <iterator>
#include <vector>

#include "../ui/ui.h"


typedef enum DebugAction {
    NONE,
    STEP,
    CONTINUE,
    BREAKPOINT,
    HELP,
    QUIT
} DebugAction_t;


class Debugger {
    public:
        Debugger(UI &);
        virtual ~Debugger();

        void tick(uint16_t);
        DebugAction_t get_input();

        void set_breakpoint(uint16_t);
        bool check_breakpoints(uint16_t);

        void help();
        bool step() const;
        bool quit() const;

    private:
        UI m_ui;

        bool m_first_started = true;
        bool m_stopped = true;
        bool m_step = false;
        bool m_quit = false;

        std::vector<uint16_t> m_breakpoints;
};