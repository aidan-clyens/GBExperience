#include "file_parser.h"

FileParser::FileParser(int buffer_size):
m_buffer_size(buffer_size),
m_buffer(new uint8_t[buffer_size])
{

}

FileParser::~FileParser() {
    delete m_buffer;
}

bool FileParser::load_rom(const std::string &file_name) {
    std::ifstream file_buffer;
    file_buffer.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    
    try {
        file_buffer.open(file_name, std::ios::in | std::ios::binary);
        file_buffer.read((char*)m_buffer, m_buffer_size);

        file_buffer.close();
    }
    catch (std::ifstream::failure e) {
        std::cerr << "Exception opening/reading/closing file\n";
        return false;
    }

    return true;
}

uint8_t *FileParser::get_buffer_ptr() {
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

void FileParser::print_to_file() {
    std::ofstream output("../../bytes.txt", std::ios::out | std::ios::binary);
    output.write((char*)m_buffer, m_buffer_size);
    output.close();
}
