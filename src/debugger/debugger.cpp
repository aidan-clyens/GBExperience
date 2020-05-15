#include "debugger.h"


Debugger::Debugger(UI &ui):
m_ui(ui)
{

}

Debugger::~Debugger() {

}

void Debugger::tick() {
    DebugAction_t input = this->get_input();
    
    switch (input) {
        case STEP:
            break;
        case CONTINUE:
            break;
        case QUIT:
            break;
        default:
            break;
    }
}

DebugAction_t Debugger::get_input() {
    std::string buf = "";
    log_debug("Debug: 's': step, 'c': continue, 'q': quit");
    std::cin >> buf;

    if (!buf.empty()) {
        if (buf == "s") {
            return STEP;
        }
        else if (buf == "c") {
            return CONTINUE;
        }
        else if (buf == "q") {
            return QUIT; 
        }
    }

    return NONE;
}
