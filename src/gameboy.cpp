#include "gameboy.h"


GameBoy::GameBoy():
m_cpu(m_memory_map),
m_rom_name("")
{

}


GameBoy::~GameBoy() {

}


void GameBoy::tick() {
    m_cpu.tick();
}


void GameBoy::load_rom(const std::string &rom_file, int rom_size) {
    FileParser file_parser(rom_size);
    file_parser.load_rom(rom_file);

    m_memory_map.load_rom(file_parser.get_buffer_ptr());

    m_rom_name = file_parser.get_rom_name();
    cartridge_type_t cartridge_type = file_parser.get_cartridge_type();

    std::cout << "Title: " << m_rom_name << std::endl;
    std::cout << "Cartridge Type: " << cartridge_type << std::endl;
    std::cout << "GameBoy Color: " << file_parser.is_gb_color() << std::endl;
    std::cout << "Super GameBoy: " << file_parser.is_sgb() << std::endl << std::endl;
}


std::string GameBoy::get_rom_name() const {
    return m_rom_name;
}