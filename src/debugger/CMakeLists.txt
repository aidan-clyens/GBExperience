project(debugger_lib)

add_library(${PROJECT_NAME} STATIC timing_analyzer.h timing_analyzer.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})