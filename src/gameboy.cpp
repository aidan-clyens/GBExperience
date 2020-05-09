#include "gameboy.h"


GameBoy::GameBoy(UI &ui):
m_cpu(m_memory_map),
m_video(m_memory_map, ui),
m_rom_name("")
{

}


GameBoy::~GameBoy() {

}


void GameBoy::tick() {
    int cycle_count = m_cpu.tick();

    if (!m_cpu.is_stopped()) {
        m_video.tick(cycle_count);
    }
}


void GameBoy::load_rom(const std::string &rom_file) {
    FileParser file_parser;
    file_parser.load_rom(rom_file);

    m_rom_name = file_parser.get_rom_name();
    cartridge_type_t cartridge_type = file_parser.get_cartridge_type();

    std::cout << "Title: " << m_rom_name << std::endl;
    std::cout << "Cartridge Type: " << file_parser.get_cartridge_type_string() << std::endl;
    std::cout << "ROM Size: " << file_parser.get_rom_size_banks() << " banks" << std::endl;
    std::cout << "RAM Size: " << file_parser.get_ram_size_banks() << " banks" << std::endl;
    std::cout << "Super GameBoy: " << (file_parser.is_sgb() ? "YES" : "NO") << std::endl;
    std::cout << "GameBoy Color: " << (file_parser.is_gb_color() ? "YES" : "NO") << std::endl << std::endl;

    if (cartridge_type != ROM_ONLY) {
        std::cerr << "Cartridge type: " << file_parser.get_cartridge_type_string() << " not implemented" << std::endl;
        throw new std::exception;
    }

    m_memory_map.load_rom(file_parser.get_buffer_data());
    m_ui.init_ui(m_rom_name);
}


std::string GameBoy::get_rom_name() const {
    return m_rom_name;
}