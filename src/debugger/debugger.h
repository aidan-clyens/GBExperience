#pragma once

#include <sstream>
#include <iterator>
#include <vector>

#include "../utils/string_utils.h"
#include "../cpu/cpu.h"
#include "../ui/ui_sfml.h"


typedef enum DebugAction {
    NONE,
    STEP,
    CONTINUE,
    BREAKPOINT,
    PRINT,
    HELP,
    QUIT
} DebugAction_t;


class Debugger {
    public:
        Debugger(UI &, CPU &);
        virtual ~Debugger();

        void tick(uint16_t);
        DebugAction_t get_input();

        void set_breakpoint(uint16_t);
        bool check_breakpoints(uint16_t);

        void print_reg(const std::string &);
        void help();
        bool step() const;
        bool quit() const;

    private:
        Registers_t register_from_string(const std::string &) const;

        UI &m_ui;
        CPU &m_cpu;

        std::string m_arg;

        bool m_first_started = true;
        bool m_stopped = true;
        bool m_step = false;
        bool m_quit = false;

        std::vector<uint16_t> m_breakpoints;
};