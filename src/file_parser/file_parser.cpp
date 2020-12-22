#include "file_parser.h"

FileParser::FileParser():
m_header_buffer_size(0)
{

}

FileParser::~FileParser() {

}

Cartridge *FileParser::load_rom(const std::string &file_name) {
    std::ifstream file_buffer(file_name.c_str(), std::ios::binary | std::ios::ate);

    if (!file_buffer.good()) {
        std::cerr << "Exception opening/reading/closing file\n";
        throw new std::exception;
    }

    std::ifstream::pos_type position = file_buffer.tellg();
    size_t file_size = static_cast<size_t>(position);

    std::vector<char> file_contents(file_size);

    file_buffer.seekg(0, std::ios::beg);
    file_buffer.read(&file_contents[0], position);
    file_buffer.close();

    m_header_buffer_size = file_size;
    m_header_buffer = std::vector<uint8_t>(file_contents.begin(), file_contents.end());

    switch (this->get_cartridge_type()) {
        case ROM_ONLY:
            return new ROMOnly(file_contents, this->get_rom_size_banks());
        case ROM_MBC1:
            return new MBC1(file_contents, this->get_rom_size_banks());
        default:
            std::cerr << "Cartridge type " << this->get_cartridge_type_string() << " not supported" << std::endl;
            throw new std::exception;
    }
}

std::vector<uint8_t> FileParser::get_buffer_data() {
    return m_header_buffer;
}

uint8_t FileParser::get_byte(int index) const {
    if (index > m_header_buffer_size) {
        throw new std::exception;
    }

    return m_header_buffer[index];
}

int FileParser::get_buffer_size() const {
    return m_header_buffer_size;
}

std::string FileParser::get_rom_name() const {
    char buffer[20];

    for (int i=0x134; i<= 0x142; i++) {
        buffer[i - 0x134] = static_cast<char>(static_cast<int>(this->get_byte(i)));
    }

    return std::string(buffer);
}

cartridge_type_t FileParser::get_cartridge_type() const {
    uint8_t cartridge_type_index = this->get_byte(0x147);
    return static_cast<cartridge_type_t>(cartridge_type_index);
}

std::string FileParser::get_cartridge_type_string() const {
    cartridge_type_t cartridge_type = this->get_cartridge_type();

    switch (cartridge_type) {
        case ROM_ONLY:
            return "ROM_ONLY";
        case ROM_MBC1:
            return "ROM_MBC1";
        case ROM_MBC1_RAM:
            return "ROM_MBC1_RAM";
        case ROM_MBC1_RAM_BATT:
            return "ROM_MBC1_RAM_BATT";
        case ROM_MBC2:
            return "ROM_MBC2";
        case ROM_MBC2_BATT:
            return "ROM_MBC2_BATT";
        case ROM_RAM:
            return "ROM_RAM";
        case ROM_RAM_BATT:
            return "ROM_RAM_BATT";
        case ROM_MMM01:
            return "ROM_MMM01";
        case ROM_MMM01_SRAM:
            return "ROM_MMM01_SRAM";
        case ROM_MMM01_SRAM_BATT:
            return "ROM_MMM01_SRAM_BATT";
        case ROM_MBC3_TIMER_BATT:
            return "ROM_MBC3_TIMER_BATT";
        case ROM_MBC3_TIMER_RAM_BATT:
            return "ROM_MBC3_TIMER_RAM_BATT";
        case ROM_MBC3:
            return "ROM_MBC3";
        case ROM_MBC3_RAM:
            return "ROM_MBC3_RAM";
        case ROM_MBC3_RAM_BATT:
            return "ROM_MBC3_RAM_BATT";
        case ROM_MBC5:
            return "ROM_MBC5";
        case ROM_MBC5_RAM:
            return "ROM_MBC5_RAM";
        case ROM_MBC5_RAM_BATT:
            return "ROM_MBC5_RAM_BATT";
        case ROM_MBC5_RUMBLE:
            return "ROM_MBC5_RUMBLE";
        case ROM_MBC5_RUMBLE_SRAM:
            return "ROM_MBC5_RUMBLE_SRAM";
        case ROM_MBC5_RUMBLE_SRAM_BATT:
            return "ROM_MBC5_RUMBLE_SRAM_BATT";
        case POCKET_CAMERA:
            return "POCKET_CAMERA";
        case BANDAI_TAMA5:
            return "BANDAI_TAMA5";
        case HUDSON_HUC_3:
            return "HUDSON_HUC_3";
        case HUDSON_HUC_1:
            return "HUDSON_HUC_1";
    }
}

int FileParser::get_rom_size_banks() const {
    uint8_t rom_size = this->get_byte(0x148);

    switch (rom_size) {
        case 0x0:
            return 2;
        case 0x1:
            return 4;
        case 0x2:
            return 8;
        case 0x3:
            return 16;
        case 0x4:
            return 32;
        case 0x5:
            return 64;
        case 0x6:
            return 128;
        case 0x52:
            return 72;
        case 0x53:
            return 80;
        case 0x54:
            return 96;
    }
}

int FileParser::get_ram_size_banks() const {
    uint8_t ram_size = this->get_byte(0x149);

    switch (ram_size) {
        case 0x0:
            return 0;
        case 0x1:
            return 1;
        case 0x2:
            return 1;
        case 0x3:
            return 4;
        case 0x4:
            return 16;
    }
}

bool FileParser::is_gb_color() const {
    return this->get_byte(0x143) == 0x80;
}

bool FileParser::is_sgb() const {
    return this->get_byte(0x146) == 0x03;
}
