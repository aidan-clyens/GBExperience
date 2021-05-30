#include "cartridge.h"


Cartridge::Cartridge(std::vector<char> file_buffer, int num_rom_banks):
m_cartridge_type(ROM_ONLY),
m_cartridge_size(0),
m_num_rom_banks(num_rom_banks)
{
    int buffer_index = 0;
    for (int i = 0; i < m_num_rom_banks; i++) {
        Memory *mem = new Memory(ROM_BANK_SIZE);
        mem->init_memory();

        int j = 0;
        while (buffer_index < file_buffer.size() && j < ROM_BANK_SIZE) {
            mem->write_memory(j, file_buffer[buffer_index]);

            buffer_index++;
            j++;
        }

        m_rom_banks.push_back(mem);
    }
    // std::cout << "Initialized " << m_rom_banks.size() << " ROM banks" << std::endl;

    if (m_rom_banks.size() != m_num_rom_banks) {
        std::cerr << "Cartridge initialization failed!" << std::endl;
        throw new std::exception;
    }
}

Cartridge::~Cartridge() {
    for (int i = 0; i < m_rom_banks.size(); i++) {
        delete m_rom_banks[i];
    }
}

void Cartridge::set_cartridge_type(cartridge_type_t type) {
    m_cartridge_type = type;
}

cartridge_type_t Cartridge::get_cartridge_type() const {
    return m_cartridge_type;
}

void Cartridge::set_num_rom_banks(int size) {
    m_num_rom_banks = size;
}

int Cartridge::get_num_rom_banks() const {
    return m_num_rom_banks;
}


ROMOnly::ROMOnly(std::vector<char> file_buffer, int num_rom_banks):
Cartridge(file_buffer, num_rom_banks)
{
    Cartridge::set_cartridge_type(ROM_ONLY);
}

ROMOnly::~ROMOnly() {

}

uint8_t ROMOnly::read(uint16_t address) {
    if (address > 2 * ROM_BANK_SIZE) {
        std::cerr << "ROMOnly read: Address out of range" << std::endl;
        throw new std::exception;
    }

    unsigned int index = (unsigned int)address / ROM_BANK_SIZE;
    address = address % ROM_BANK_SIZE;
    return m_rom_banks[index]->read_memory(address);
}

uint16_t ROMOnly::write(uint16_t address, uint8_t data) {
    std::cerr << "ROMOnly: Cannot write to ROM" << std::endl;

    return 0;
}


MBC1::MBC1(std::vector<char> file_buffer, int num_rom_banks):
Cartridge(file_buffer, num_rom_banks),
m_ram_enabled(false),
m_rom_bank_bits(0x0),
m_rom_bank_number(1),
m_mode(ROM_MODE)
{
    Cartridge::set_cartridge_type(ROM_MBC1);
}

MBC1::~MBC1() {
    
}

uint8_t MBC1::read(uint16_t address) {
    if (address > 2 * ROM_BANK_SIZE) {
        std::cerr << "MBC1 read: Address out of range" << std::endl;
        throw new std::exception;
    }

    // Read from ROM bank 00
    if (address <= 0x3FFF) {
        log_warn("MBC1 Read from Bank: 0, Address: %X", address);
        return m_rom_banks[0]->read_memory(address);
    }
    // Read from ROM bank 01 -7F
    else if (address >= 0x4000 & address <= 0x7FFF) {
        address = address - 0x4000;
        log_warn("MBC1 Read from Bank: %d, Address: %X", m_rom_bank_number, address);
        if (m_rom_bank_number >= m_rom_banks.size()) {
            std::cerr << "Error: ROM Bank number greater than expected size" << std::endl;
            throw new std::exception;
        }

        return m_rom_banks[m_rom_bank_number]->read_memory(address);
    }

    return 0x0;
}

uint16_t MBC1::write(uint16_t address, uint8_t data) {
    log_warn("Writing %X to MBC1 address: %X", data, address);

    unsigned int index = (unsigned int)address / ROM_BANK_SIZE;
    if (address > 2 * ROM_BANK_SIZE) {
        std::cerr << "MBC1 write: Address out of range" << std::endl;
        throw new std::exception;
    }

    // RAM Enable
    if (address <= 0x1FFF) {
        m_ram_enabled = ((data & 0xF) == 0x0A);
        log_warn("MBC1 RAM Enable: %d", m_ram_enabled);
    }
    // ROM Bank Number
    else if (address >= 0x2000 && address <= 0x3FFF) {
        m_rom_bank_bits = (data & 0x1F);
        m_rom_bank_number = (int)m_rom_bank_bits % m_num_rom_banks;
        if (m_rom_bank_number == 0) {
            m_rom_bank_number = 1;
        }
        log_warn("MBC1 ROM Bank Number (lower bits): %d", m_rom_bank_number);
    }
    // RAM Bank Number or ROM Bank Number Upper Bits
    else if (address >= 0x4000 && address <= 0x5FFF) {
        data &= 0x3;
        switch (m_mode) {
            case ROM_MODE:
                m_rom_bank_bits = m_rom_bank_bits | (data << 5);
                m_rom_bank_number = (int)m_rom_bank_bits;
                if (m_rom_bank_number == 0) {
                    m_rom_bank_number = 1;
                }
                log_warn("MBC1 ROM Bank Number (with upper bits): %d", m_rom_bank_number);
                break;
            case RAM_MODE:
                log_warn("MBC1 RAM Bank Number: %X", data);
                break;
        }
    }
    // Banking Mode Select
    else if (address >= 0x6000 && address <= 0x7FFF) {
        if (data == 0x00) {
            m_mode = ROM_MODE;
        }
        else if (data == 0x01) {
            m_mode = RAM_MODE;
        }
        log_warn("MBC1 Banking Mode Select: %s", (m_mode == ROM_MODE) ? "ROM_MODE" : "RAM_MODE");
    }
    else {
        // m_rom_buffer[index] = data;
    }

    return address;
}

bool MBC1::is_ram_enabled() const {
    return m_ram_enabled;
}

int MBC1::get_rom_bank_number() const {
    return m_rom_bank_number;
}

mode_select_t MBC1::get_mode() const {
    return m_mode;
}
