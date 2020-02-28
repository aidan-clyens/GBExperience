#include "gtest/gtest.h"
#include "file_parser_tests.h"
#include "memory_map_tests.h"
#include "memory_tests.h"
#include "cpu_tests.h"
#include "cpu_alu_tests.h"
#include "cpu_registers_tests.h"


int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}