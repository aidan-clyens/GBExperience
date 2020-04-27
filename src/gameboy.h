#include "cpu/cpu.h"
#include "memory/memory_map.h"
#include "file_parser/file_parser.h"

#include <string>


class GameBoy {
    public:
        GameBoy();
        virtual ~GameBoy();

        void tick();

        void load_rom(const std::string &, int);

        std::string get_rom_name() const;
    
    private:
        CPU m_cpu;
        MemoryMap m_memory_map;

        std::string m_rom_name;
};