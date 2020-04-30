project(${CMAKE_PROJECT_NAME}_tests)

add_executable(${PROJECT_NAME} main.cpp file_parser_tests.h memory_map_tests.h memory_tests.h cpu_tests.h cpu_registers_tests.h cpu_alu_tests.h cpu_jumps_tests.h cpu_rotates_tests.h cpu_misc_tests.h cpu_bit_ops_tests.h cpu_interrupts_tests.h io_tests.h video_tests.h)
add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME} PRIVATE GameBoy_lib display_lib file_parser_lib memory_lib cpu_lib video_lib gtest)
