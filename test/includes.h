#pragma once


#include "cpu/cpu.h"
#include "cpu/cpu_registers.h"
#include "file_parser/file_parser.h"
#include "memory/memory.h"
#include "memory/memory_map.h"
#include "memory/io.h"
#include "memory/input.h"
#include "video/definitions.h"
#include "video/framebuffer.h"
#include "video/video.h"
#include "video/tile.h"
#include "video/sprite.h"
#include "ui/ui.h"
#include "debugger/logger.h"
#include "gameboy.h"


const int DISPLAY_TIME = 50;

const int BUFFER_SIZE = 2 * 32 * 1024;
const std::string TEST_ROM = "../../test/test_roms/cpu_instrs/cpu_instrs.gb";
const std::string ROM_TITLE = "CPU_INSTRS";
const int ROM_SIZE = 4;
const cartridge_type_t CARTRIDGE_TYPE = ROM_MBC1;
const bool GB_COLOR_SUPPORTED = true;
const bool SGB_SUPPORTED = false;