#pragma once

#include <sstream>
#include <iterator>
#include <vector>

#include "../utils/string_utils.h"
#include "../cpu/cpu.h"
#include "../user_interface/user_interface_sfml.h"


typedef enum DebugAction {
    NONE,
    STEP,
    CONTINUE,
    BREAKPOINT_LINE,
    BREAKPOINT_OPCODE,
    PRINT,
    HELP,
    QUIT
} DebugAction_t;


typedef enum BreakpointType {
    LINE,
    OPCODE
} BreakpointType_t;


class Debugger {
    public:
        Debugger(CPU &);
        virtual ~Debugger();

        void tick(uint16_t, uint8_t);
        DebugAction_t get_input();

        void set_breakpoint(uint16_t, BreakpointType_t);
        bool check_breakpoints(uint16_t, BreakpointType_t);

        void print_reg(const std::string &);
        void help();
        bool step() const;
        bool quit() const;

    private:
        Registers_t register_from_string(const std::string &) const;

        CPU &m_cpu;

        std::string m_arg;

        bool m_first_started = true;
        bool m_stopped = true;
        bool m_step = false;
        bool m_quit = false;

        std::vector<uint16_t> m_line_breakpoints;
        std::vector<uint16_t> m_opcode_breakpoints;
};