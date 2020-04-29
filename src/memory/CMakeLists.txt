project(memory_lib)

add_library(${PROJECT_NAME} STATIC memory_map.h memory_map.cpp memory.cpp memory.h io.h io.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})