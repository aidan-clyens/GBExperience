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

        log_debug("Starting at 0x%X", pc);
    }
    
    if (!m_stopped) {
        if (!this->check_breakpoints(pc)) {
            return;
        }
        else {
            log_debug("Stopped at 0x%X", pc);
            m_stopped = true;
        }
    }

    DebugAction_t input = this->get_input();
    m_step = false;
    
    switch (input) {
        case STEP:
            m_step = true;
            break;
        case CONTINUE:
            m_step = true;
            m_stopped = false;
            break;
        case BREAKPOINT: {
            char buf[10];
            uint16_t line_num;
            std::stringstream ss;
            log_debug_no_new_line("Enter line number (hex): ");
            std::cin >> buf;
            ss << std::hex << buf;
            ss >> line_num;
            this->set_breakpoint((uint16_t)line_num);
            break;
        }
        case HELP:
            this->help();
            break;
        case QUIT:
            m_quit = true;
            break;
        default:
            break;
    }
}

DebugAction_t Debugger::get_input() {
    std::string buf;
    std::getline(std::cin, buf);
    std::istringstream iss(buf);
    std::vector<std::string> args = {
        std::istream_iterator<std::string>(iss),
        std::istream_iterator<std::string>()
    };

    if (args.size() == 0) {
        return NONE;
    }
    else if (args.size() == 1) {
        if (buf == "s") {
            return STEP;
        }
        else if (buf == "c") {
            return CONTINUE;
        }
        else if (buf == "h") {
            return HELP;
        }
        else if (buf == "q") {
            return QUIT; 
        }
    }
    else if (args.size() == 2) {
        if (buf == "b") {
            return BREAKPOINT;
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
    log_debug("Debugger Commands:");
    log_debug("'s': step\n'c': continue\n'b': add breakpoint\n'h': help\n'q': quit");
}

bool Debugger::step() const {
    return m_step;
}

bool Debugger::quit() const {
    return m_quit;
}