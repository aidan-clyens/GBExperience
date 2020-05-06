#include "cpu.h"


void CPU::handle_interrupts() {
    if (m_interrupts_enabled) {
        uint8_t fired_interrupts = this->read_io_register(IE) & this->read_io_register(IF);

        #ifdef INTERRUPT_DEBUG
        std::cout << "Interrupt fired: " << static_cast<int>(fired_interrupts) << std::endl;
        #endif

        // An interrupt has been generated
        if (fired_interrupts > 0)  {
            // Restart CPU if halted
            m_halted = false;

            // Push current program program counter onto the stack
            this->push_stack("PC");

            // Handle interrupts by order of priority
            bool handled = false;
            handled = this->handle_interrupt(VBLANK, VBLANK_ISR);
            if (handled) {
                return;
            }

            handled = this->handle_interrupt(LCD_STAT, LCD_STAT_ISR);
            if (handled) {
                return;
            }

            handled = this->handle_interrupt(TIMER, TIMER_ISR);
            if (handled) {
                return;
            }

            handled = this->handle_interrupt(SERIAL, SERIAL_ISR);
            if (handled) {
                return;
            }

            handled = this->handle_interrupt(JOYPAD, JOYPAD_ISR);
            if (handled) {
                return;
            }
        }
    }
}

bool CPU::handle_interrupt(InterruptFlag_t flag, InterruptVector_t vector) {
    if (!(this->get_interrupt_flag_bit(flag) && this->get_interrupt_enable_bit(flag))) {
        return false;
    }

    #ifdef CPU_DEBUG
    std::cout << "Handling interrupt: " << flag << std::endl;
    #endif

    // Clear corresponding Interrupt Flag bit
    this->set_interrupt_flag_bit(flag, false);
    // Set PC to corresponding vector for ISR
    this->write_register("PC", (uint16_t)vector);
    // Disable interrupts
    m_interrupts_enabled = false;

    return true;
}

bool CPU::get_interrupt_enable_bit(InterruptFlag_t flag) {
    uint8_t value = this->read_io_register(IE);

    return (value & flag) == flag;
}

bool CPU::get_interrupt_flag_bit(InterruptFlag_t flag) {
    uint8_t value = this->read_io_register(IF);

    return (value & flag) == flag;
}

void CPU::set_interrupt_enable_bit(InterruptFlag_t flag, bool set) {
    uint8_t value = this->read_io_register(IE);

    if (set) {
        value |= flag;
    }
    else {
        value &= ~flag;
    }

    this->write_io_register(IE, value);
}

void CPU::set_interrupt_flag_bit(InterruptFlag_t flag, bool set) {
    uint8_t value = this->read_io_register(IF);

    if (set) {
        value |= flag;
    }
    else {
        value &= ~flag;
    }

    this->write_io_register(IF, value);
}
