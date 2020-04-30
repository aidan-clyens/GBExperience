#include "video.h"


Video::Video(MemoryMap &mem_map):
m_memory_map(mem_map)
{

}

Video::~Video() {

}

void Video::tick() {

}

uint8_t Video::read_io_register(IORegisters_t reg) {
    return this->m_memory_map.read(reg);
}

void Video::write_io_register(IORegisters_t reg, uint8_t data) {
    this->m_memory_map.write(reg, data);
}
