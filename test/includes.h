#pragma once


#include "cpu/cpu.h"
#include "cpu/cpu_registers.h"
#include "file_parser/file_parser.h"
#include "file_parser/cartridge.h"
#include "memory/memory.h"
#include "memory/memory_map.h"
#include "memory/io.h"
#include "memory/input.h"
#include "video/definitions.h"
#include "video/framebuffer.h"
#include "video/video.h"
#include "video/tile.h"
#include "video/sprite.h"
#include "ui/ui_sfml.h"
#include "debugger/logger.h"
#include "gameboy.h"

#include <stdio.h>
#include <unistd.h>
#include <iostream>


const int DISPLAY_TIME = 50;

const std::string TEST_ROM = "/test/test-roms/cpu_instrs/cpu_instrs.gb";
const int BUFFER_SIZE = 2 * 32 * 1024;
const std::string ROM_TITLE = "CPU_INSTRS";
const int ROM_SIZE = 4;
const cartridge_type_t CARTRIDGE_TYPE = ROM_MBC1;
const bool GB_COLOR_SUPPORTED = true;
const bool SGB_SUPPORTED = false;


std::string get_current_dir() {
    char buff[FILENAME_MAX];
    getcwd(buff, FILENAME_MAX);
    std::string current_working_dir(buff);
    return current_working_dir;
}


std::string get_test_rom() {
    std::string dir = get_current_dir();

    // Check if in build directory
    std::size_t pos = dir.find("build");
    std::string project_dir = dir;
    if (pos != std::string::npos) {
        project_dir = dir.substr(0, pos-1);
    }

    return project_dir + TEST_ROM;
}