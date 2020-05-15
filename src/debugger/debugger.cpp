#include "debugger.h"


Debugger::Debugger(UI &ui):
m_ui(ui)
{

}

Debugger::~Debugger() {

}

void Debugger::tick(uint16_t pc) {
    if (m_first_started) {
        this->help();
        m_first_started = false;
    }
    
    if (!m_stopped) {
        if (!this->check_breakpoints(pc)) {
            return;
        }
        else {
            m_stopped = true;
        }
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
            m_quit = true;
            break;
        default:
            break;
    }
}

DebugAction_t Debugger::get_input() {
    std::string buf = "";
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

bool Debugger::check_breakpoints(uint16_t pc) {
    auto it = std::find(m_breakpoints.begin(), m_breakpoints.end(), pc);
    return it !=m_breakpoints.end();
}

void Debugger::help() {
    log_debug("Debug: 's': step, 'c': continue, 'b': add breakpoint, 'q': quit");
}

bool Debugger::quit() const {
    return m_quit;
}