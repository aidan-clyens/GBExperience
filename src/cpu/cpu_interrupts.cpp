#include "cpu.h"

void CPU::handle_interrupts() {

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
