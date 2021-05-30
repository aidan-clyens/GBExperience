project(${CMAKE_PROJECT_NAME}_tests)

set(PYTEST
    ${PROJECT_SOURCE_DIR}/venv/bin/python3
    ${PROJECT_SOURCE_DIR}/venv/bin/pytest
)

add_executable(${PROJECT_NAME} main.cpp includes.h file_parser_tests.h memory_map_tests.h memory_tests.h cpu_tests.h cpu_registers_tests.h cpu_alu_tests.h cpu_jumps_tests.h cpu_rotates_tests.h cpu_misc_tests.h cpu_bit_ops_tests.h cpu_interrupts_tests.h io_tests.h video_tests.h tile_tests.h framebuffer_tests.h integration_tests.h sprite_tests.h cartridge_tests.h)

target_link_libraries(${PROJECT_NAME} PRIVATE ${CMAKE_PROJECT_NAME}_lib user_interface_lib file_parser_lib memory_lib cpu_lib video_lib debugger_lib gtest)

add_test(NAME blargg_tests
COMMAND ${PYTEST} test/run_blargg_tests.py
WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/..
)

include(GoogleTest)
gtest_add_tests(TARGET ${PROJECT_NAME})