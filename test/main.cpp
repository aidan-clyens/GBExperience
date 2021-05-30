#include "gtest/gtest.h"
#include "includes.h"
#include "file_parser_tests.h"
#include "memory_map_tests.h"
#include "memory_tests.h"
#include "cpu_tests.h"
#include "cpu_alu_tests.h"
#include "cpu_registers_tests.h"
#include "cpu_jumps_tests.h"
#include "cpu_ld_tests.h"
#include "cpu_rotates_tests.h"
#include "cpu_misc_tests.h"
#include "cpu_bit_ops_tests.h"
#include "cpu_interrupts_tests.h"
#include "io_tests.h"
#include "video_tests.h"
#include "tile_tests.h"
#include "sprite_tests.h"
#include "framebuffer_tests.h"
#include "integration_tests.h"
#include "cartridge_tests.h"


int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}