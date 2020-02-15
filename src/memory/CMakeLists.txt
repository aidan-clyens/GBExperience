project(memory_lib)

add_library(${PROJECT_NAME} STATIC memory.cpp memory.h)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})