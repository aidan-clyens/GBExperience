#include "file_parser.h"

FileParser::FileParser():
m_buffer_size(0)
{

}

FileParser::~FileParser() {

}

bool FileParser::load_rom(const std::string &file_name) {
    std::ifstream file_buffer(file_name.c_str(), std::ios::binary | std::ios::ate);

    if (!file_buffer.good()) {
        std::cerr << "Exception opening/reading/closing file\n";
        return false;
    }

    std::ifstream::pos_type position = file_buffer.tellg();
    size_t file_size = static_cast<size_t>(position);

    std::vector<char> file_contents(file_size);

    file_buffer.seekg(0, std::ios::beg);
    file_buffer.read(&file_contents[0], position);
    file_buffer.close();

    m_buffer_size = file_size;

    m_buffer = std::vector<uint8_t>(file_contents.begin(), file_contents.end());

    return true;
}

std::vector<uint8_t> FileParser::get_buffer_data() {
    return m_buffer;
}

uint8_t FileParser::get_byte(int index) const {
    if (index > m_buffer_size) {
        throw new std::exception;
    }

    return m_buffer[index];
}

int FileParser::get_buffer_size() const {
    return m_buffer_size;
}

std::string FileParser::get_rom_name() const {
    char buffer[0x142 - 0x134];

    for (int i=0x134; i<= 0x142; i++) {
        buffer[i - 0x134] = static_cast<char>(static_cast<int>(this->get_byte(i)));
    }

    return std::string(buffer);
}

cartridge_type_t FileParser::get_cartridge_type() const {
    uint8_t cartridge_type_index = this->get_byte(0x147);
    return static_cast<cartridge_type_t>(cartridge_type_index);
}

bool FileParser::is_gb_color() const {
    return this->get_byte(0x143) == 0x80;
}

bool FileParser::is_sgb() const {
    return this->get_byte(0x146) == 0x03;
}

