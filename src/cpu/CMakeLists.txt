project(cpu_lib)

add_library(${PROJECT_NAME} STATIC cpu.cpp cpu.h cpu_registers.h cpu_registers.cpp cpu_alu.cpp cpu_jumps.cpp cpu_ld.cpp cpu_restarts.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})