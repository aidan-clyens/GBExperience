#include "debugger.h"


Debugger::Debugger(CPU &cpu):
m_cpu(cpu)
{

}

Debugger::~Debugger() {

}

void Debugger::tick(uint16_t pc, uint8_t opcode) {
    if (m_first_started) {
        this->help();
        m_first_started = false;

        log_debug("Starting at 0x%X", pc);
    }
    
    if (!m_stopped) {
        if (!this->check_breakpoints(pc, LINE)) {
            if (!this->check_breakpoints(opcode, OPCODE)) {
                return;
            }
            else {
                log_debug("Stopped at opcode 0x%X", opcode);
                m_stopped = true;
            }
        }
        else {
            log_debug("Stopped at line 0x%X", pc);
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
        case BREAKPOINT_LINE: {
            uint16_t line_num = get_input_hex(m_arg);
            this->set_breakpoint((uint16_t)line_num, LINE);
            log_debug("Set breakpoint at line 0x%X", line_num);
            break;
        }
        case BREAKPOINT_OPCODE: {
            uint16_t opcode = get_input_hex(m_arg);
            this->set_breakpoint((uint16_t)opcode, OPCODE);
            log_debug("Set breakpoint at opcode 0x%X", opcode);
            break;
        }
        case PRINT:
            this->print_reg(m_arg);
            break;
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
    std::vector<std::string> args = get_input_words_list();

    if (args.size() == 0) {
        return NONE;
    }
    else if (args.size() == 1) {
        std::string cmd = args[0];

        if (cmd == "s") {
            return STEP;
        }
        else if (cmd == "c") {
            return CONTINUE;
        }
        else if (cmd == "h") {
            return HELP;
        }
        else if (cmd == "q") {
            return QUIT; 
        }
    }
    else if (args.size() == 2) {
        std::string cmd = args[0];
        m_arg = args[1];
        if (cmd == "bl") {
            return BREAKPOINT_LINE;
        }
        else if (cmd == "bo") {
            return BREAKPOINT_OPCODE;
        }
        else if (cmd == "p") {
            return PRINT;
        }
    }

    return NONE;
}

void Debugger::set_breakpoint(uint16_t val, BreakpointType_t type) {
    switch (type) {
        case LINE:
            m_line_breakpoints.push_back(val);
            break;
        case OPCODE:
            m_opcode_breakpoints.push_back(val);
            break;
    }
}

bool Debugger::check_breakpoints(uint16_t val, BreakpointType_t type) {
    switch (type) {
        case LINE: {
            auto it = std::find(m_line_breakpoints.begin(), m_line_breakpoints.end(), val);
            return it !=m_line_breakpoints.end();
        }
        case OPCODE: {
            auto it = std::find(m_opcode_breakpoints.begin(), m_opcode_breakpoints.end(), val);
            return it != m_opcode_breakpoints.end();
        }
    }
}

void Debugger::print_reg(const std::string &reg_str) {
    Registers_t reg = register_from_string(reg_str);
    log_debug("%s = 0x%X", reg_str.c_str(), m_cpu.read_register(reg));
}

void Debugger::help() {
    log_debug("Debugger Commands:");
    log_debug("'s': step\n'c': continue\n'bl': add line breakpoint\n'bo': add opcode breakpoint\n'p': print register\n'h': help\n'q': quit");
}

bool Debugger::step() const {
    return m_step;
}

bool Debugger::quit() const {
    return m_quit;
}

Registers_t Debugger::register_from_string(const std::string &reg_str) const {
    if (reg_str == "A")
        return REG_A;
    else if (reg_str == "F")
        return REG_F;
    else if (reg_str == "B")
        return REG_B;
    else if (reg_str == "C")
        return REG_C;
    else if (reg_str == "D")
        return REG_D;
    else if (reg_str == "E")
        return REG_E;
    else if (reg_str == "H")
        return REG_H;
    else if (reg_str == "L")
        return REG_L;
    else if (reg_str == "AF")
        return REG_AF;
    else if (reg_str == "BC")
        return REG_BC;
    else if (reg_str == "DE")
        return REG_DE;
    else if (reg_str == "HL")
        return REG_HL;
    else if (reg_str == "PC")
        return REG_PC;
    else if (reg_str == "SP")
        return REG_SP;
    else
        std::cerr << "Error: Register does not exist!" << std::endl;
}
