#include "gameboy.h"


GameBoy::GameBoy(bool debug, bool headless):
m_ui(m_memory_map, headless),
m_cpu(m_memory_map),
m_video(m_memory_map, m_ui, headless),
m_timer(m_memory_map),
m_debugger(m_cpu),
m_framerate_observer(&m_video),
m_debugger_enabled(debug),
m_rom_name("")
{
    if (debug) {
        enable_debug_logging();
        enable_warn_logging();
        enable_cpu_logging();
    }
}


GameBoy::~GameBoy() {

}


void GameBoy::tick() {
    uint16_t pc = m_cpu.read_register(REG_PC);

    if (m_debugger_enabled) {
        uint8_t opcode = m_cpu.read_memory(REG_PC);
        m_debugger.tick(pc, opcode);

        if (m_debugger.quit()) {
            this->quit();
        }

        if (!m_debugger.step()) {
            return;
        }
    }

    int cycle_count = m_cpu.tick();

    if (!m_cpu.is_stopped()) {
        m_timer.tick(cycle_count);
        m_video.tick(cycle_count);
    }
}


void GameBoy::load_rom(const std::string &rom_file) {
    FileParser file_parser;
    Cartridge *cartridge = file_parser.load_rom(rom_file);

    m_rom_name = file_parser.get_rom_name();
    cartridge_type_t cartridge_type = file_parser.get_cartridge_type();

    std::cout << "Title: " << m_rom_name << std::endl;
    std::cout << "Cartridge Type: " << file_parser.get_cartridge_type_string() << std::endl;
    std::cout << "ROM Size: " << file_parser.get_rom_size_banks() << " banks" << std::endl;
    std::cout << "RAM Size: " << file_parser.get_ram_size_banks() << " banks" << std::endl;
    std::cout << "Super GameBoy: " << (file_parser.is_sgb() ? "YES" : "NO") << std::endl;
    std::cout << "GameBoy Color: " << (file_parser.is_gb_color() ? "YES" : "NO") << std::endl << std::endl;

    m_memory_map.load_rom(cartridge);
    m_ui.init_display(m_rom_name);
}


std::string GameBoy::get_rom_name() const {
    return m_rom_name;
}

bool GameBoy::is_display_open() const {
    return m_ui.is_display_enabled();
}

void GameBoy::quit() {
    m_ui.set_display_enabled(false);
}

long int GameBoy::get_time_difference_ns() {
    std::chrono::steady_clock::time_point end = get_time();
    return std::chrono::duration_cast<std::chrono::nanoseconds>(end - m_last_time).count();
}

std::chrono::steady_clock::time_point GameBoy::get_time() {
    return std::chrono::steady_clock::now();
}