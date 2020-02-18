project(cpu_lib)

add_library(${PROJECT_NAME} STATIC cpu.cpp cpu.h)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})