#include "debugger.h"


Debugger::Debugger(UI &ui):
m_ui(ui)
{

}

Debugger::~Debugger() {

}

void Debugger::tick(uint16_t pc) {
    if (!m_stopped) {
        return;
    }

    DebugAction_t input = this->get_input();
    
    switch (input) {
        case STEP:
            break;
        case CONTINUE:
            m_stopped = false;
            break;
        case BREAKPOINT: {
            unsigned int line_num;
            log_debug_no_new_line("Enter line number: ");
            std::cin >> line_num;
            this->set_breakpoint((uint16_t)line_num);
            break;
        }
        case QUIT:
            break;
        default:
            break;
    }
}

DebugAction_t Debugger::get_input() {
    std::string buf = "";
    log_debug("Debug: 's': step, 'c': continue, 'b': add breakpoint, 'q': quit");
    std::cin >> buf;

    if (!buf.empty()) {
        if (buf == "s") {
            return STEP;
        }
        else if (buf == "c") {
            return CONTINUE;
        }
        else if (buf == "b") {
            return BREAKPOINT;
        }
        else if (buf == "q") {
            return QUIT; 
        }
    }

    return NONE;
}

void Debugger::set_breakpoint(uint16_t pc) {
    m_breakpoints.push_back(pc);
}
