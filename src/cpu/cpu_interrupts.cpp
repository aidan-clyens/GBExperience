#include "cpu.h"


void CPU::handle_interrupts() {
    if (m_interrupts_enabled) {
        uint8_t fired_interrupts = this->read_io_register(IE) & this->read_io_register(IF);

        log_interrupts("Interrupt fired: %X", fired_interrupts);

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
                // Restart CPU if stopped
                m_stopped = false;
                return;
            }
        }
    }
}

bool CPU::handle_interrupt(InterruptFlag_t flag, InterruptVector_t vector) {
    if (!(this->get_interrupt_flag_bit(flag) && this->get_interrupt_enable_bit(flag))) {
        return false;
    }

    log_interrupts("Handling interrupt: %d", flag);

    // Clear corresponding Interrupt Flag bit
    this->set_interrupt_flag_bit(flag, false);
    // Set PC to corresponding vector for ISR
    this->jump((uint16_t)vector);
    // Disable interrupts
    m_interrupts_enabled = false;

    return true;
}

bool CPU::get_interrupt_enable_bit(InterruptFlag_t flag) {
    return m_memory_map.get_interrupt_enable_bit(flag);
}

bool CPU::get_interrupt_flag_bit(InterruptFlag_t flag) {
    return m_memory_map.get_interrupt_flag_bit(flag);
}

void CPU::set_interrupt_enable_bit(InterruptFlag_t flag, bool set) {
    m_memory_map.set_interrupt_enable_bit(flag, set);
}

void CPU::set_interrupt_flag_bit(InterruptFlag_t flag, bool set) {
    m_memory_map.set_interrupt_flag_bit(flag, set);
}
