#include "memory_map.h"


MemoryMap::MemoryMap() {
    // 32 kB Cartridge ROM Bank #0
    m_address_space[0] = 0x0000;
    // 32 kB Cartridge Switchable ROM Bank
    m_address_space[1] = 0x4000;
    // Video RAM
    m_address_space[2] = 0x8000;
    // Switchable RAM Bank
    m_address_space[3] = 0xA000;
    // Internal RAM
    m_address_space[4] = 0xC000;
    // Echo RAM
    m_address_space[5] = 0xE000;
    // Sprite Attributes
    m_address_space[6] = 0xFE00;
    // Unusable
    m_address_space[7] = 0xFEA0;
    // I/O Ports
    m_address_space[8] = 0xFF00;
    // Unusable
    m_address_space[9] = 0xFF4C;
    // High RAM
    m_address_space[10] = 0xFF80;
    // Interrupt Enable Register
    m_address_space[11] = 0xFFFF;

    this->init_memory_map();
}

MemoryMap::~MemoryMap() {
    delete m_vram;
    delete m_oam;
    delete m_internal_ram;
    delete m_high_ram;
}

void MemoryMap::init_memory_map() {
    m_vram = new Memory(m_address_space[3] - m_address_space[2]);
    m_oam = new Memory(m_address_space[7] - m_address_space[6]);
    m_internal_ram = new Memory(m_address_space[5] - m_address_space[4]);
    m_high_ram = new Memory(m_address_space[11] - m_address_space[10]);

    m_vram->init_memory();
    m_oam->init_memory();
    m_internal_ram->init_memory();
    m_high_ram->init_memory();
}

void MemoryMap::load_rom(Cartridge *cartridge) {
    m_cartridge = cartridge;
}

uint16_t MemoryMap::write(uint16_t address, uint8_t data) {
    int index = this->get_index(address);

    switch (index) {
        case 0:
        case 1:
            if (m_cartridge->get_cartridge_type() == ROM_ONLY) {
                log_warn("Cannot write to ROM");
                break;
            }

            return m_cartridge->write(address, data);
        case 2:
            return this->write_vram(address, data);
        case 6:
            return this->write_oam(address, data);
        case 3: {
            if (m_cartridge->get_cartridge_type() == ROM_ONLY) {
                log_warn("Cannot write to interal RAM with a ROM_ONLY cartridge");
            }
            break;
        }
        case 4:
        case 5:
            return m_internal_ram->write_memory(address - m_address_space[index], data);
        case 10:
            return m_high_ram->write_memory(address - m_address_space[index], data);
        case 7:
        case 9:
            log_warn("Address space unusable: %d. Address: %X", index, address);
            break;
        case 8:
        case 11:
            if (address == DMA) {
                this->dma_transfer(data);
            }

            return this->m_io.write((IORegisters_t)address, data);
        default: {
            std::cerr << "Invalid address: " << static_cast<int>(address) << std::endl;
            throw new std::exception;
        }
    }

    return 0x0;
}

uint8_t MemoryMap::read(uint16_t address) {
    int index = this->get_index(address);

    switch (index) {
        case 0:
        case 1:
            return m_cartridge->read(address);
        case 2:
            return this->read_vram(address);
        case 6:
            return this->read_oam(address);
        case 3: {
            if (m_cartridge->get_cartridge_type() == ROM_ONLY) {
                log_warn("Cannot read to interal RAM with a ROM_ONLY cartridge");
            }
            break;
        }
        case 4:
        case 5:
            return m_internal_ram->read_memory(address - m_address_space[index]);
        case 10:
            return m_high_ram->read_memory(address - m_address_space[index]);
        case 7:
        case 9:
            log_warn("Address space unusable: %d. Address: %X", index, address);
            break;

        case 8:
        case 11:
            return this->m_io.read((IORegisters_t)address);
        
        default: {
            std::cerr << "Invalid address: " << static_cast<int>(address) << std::endl;
            throw new std::exception;
        }
    }

    return 0x0;
}

uint16_t MemoryMap::write_vram(uint16_t address, uint8_t data) {
    
    if (address >= TILE_DATA_UNSIGNED && address < TILE_MAP_0) {
        log_memory("MemoryMap: Writing %X to Tile Data Table at address %X", data, address);
    }
    else if (address >= TILE_MAP_0 && address < TILE_MAP_1) {
        log_memory("MemoryMap: Writing %X to Background Map 0 at address %X", data, address);
    }
    else if (address >= TILE_MAP_1) {
        log_memory("MemoryMap: Writing %X to Background Map 1 at address %X", data, address);
    }

    return m_vram->write_memory(address - m_address_space[2], data);
}

uint8_t MemoryMap::read_vram(uint16_t address) {
    uint8_t data = m_vram->read_memory(address - m_address_space[2]);
    
    if (address >= TILE_DATA_UNSIGNED && address < TILE_MAP_0) {
        log_memory("MemoryMap: Reading %X from Tile Data Table at address %X", data, address);
    }
    else if (address >= TILE_MAP_0 && address < TILE_MAP_1) {
        log_memory("MemoryMap: Reading %X from Background Map 0 at address %X", data, address);
    }
    else if (address >= TILE_MAP_1) {
        log_memory("MemoryMap: Reading %X from Background Map 1 at address %X", data, address);
    }

    return data;
}

uint16_t MemoryMap::write_oam(uint16_t address, uint8_t data) {
    int sprite_index = (address - m_address_space[6]) / 40;
    log_memory("MemoryMap: Writing %X to OAM at address %X. Sprite index: %d", data, address, sprite_index);

    return m_oam->write_memory(address - m_address_space[6], data);
}

uint8_t MemoryMap::read_oam(uint16_t address) {
    int sprite_index = (address - m_address_space[6]) / 40;

    uint8_t data = m_oam->read_memory(address - m_address_space[6]);

    log_memory("MemoryMap: Reading %X from OAM at address %X. Sprite index: %d", data, address, sprite_index);

    return data;
}

void MemoryMap::dma_transfer(uint8_t index) {
    uint16_t source_address = index * 0x100;
    uint16_t dest_address = 0xFE00;
    uint8_t oam_length = 0x9F;

    for (uint8_t i = 0; i <= oam_length; i++) {
        uint8_t data = this->read(source_address + i);
        this->write(dest_address + i, data);
    }
}

int MemoryMap::get_index(uint16_t address) const {
    for (int i=0; i<12; i++) {
        if (address < m_address_space[i]) {
            return i-1;
        }
    }

    if (address == 0xFFFF) {
        return 11;
    }

    return -1;
}

bool MemoryMap::get_interrupt_enable_bit(InterruptFlag_t flag) {
    uint8_t value = this->read(IE);

    return (value & flag) == flag;
}

bool MemoryMap::get_interrupt_flag_bit(InterruptFlag_t flag) {
    uint8_t value = this->read(IF);

    return (value & flag) == flag;
}

void MemoryMap::set_interrupt_enable_bit(InterruptFlag_t flag, bool set) {
    uint8_t value = this->read(IE);

    if (set) {
        value |= flag;
    }
    else {
        value &= ~flag;
    }

    this->write(IE, value);
}

void MemoryMap::set_interrupt_flag_bit(InterruptFlag_t flag, bool set) {
    uint8_t value = this->read(IF);

    if (set) {
        value |= flag;
    }
    else {
        value &= ~flag;
    }

    this->write(IF, value);
}

void MemoryMap::set_button_pressed(Buttons_t button, bool pressed) {
    m_io.set_button_pressed(button, pressed);
}

void MemoryMap::increment_io_counter(IORegisters_t reg) {
    m_io.increment_counter(reg);
}
