project(memory_lib)

add_library(${PROJECT_NAME} STATIC memory_map.h memory_map.cpp memory.cpp memory.h mem_io.h mem_io.cpp input.h input.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})