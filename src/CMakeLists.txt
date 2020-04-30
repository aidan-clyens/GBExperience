project(GameBoy)

add_subdirectory(display)
add_subdirectory(file_parser)
add_subdirectory(memory)
add_subdirectory(cpu)
add_subdirectory(video)
add_subdirectory(debugger)

add_library(${PROJECT_NAME}_lib STATIC main.cpp gameboy.h gameboy.cpp)
target_include_directories(${PROJECT_NAME}_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(${PROJECT_NAME}_run main.cpp gameboy.h gameboy.cpp)
target_link_libraries(${PROJECT_NAME}_run display_lib file_parser_lib memory_lib cpu_lib video_lib debugger_lib)

add_executable(${PROJECT_NAME}_timing timing_analysis.cpp)
target_link_libraries(${PROJECT_NAME}_timing display_lib file_parser_lib memory_lib cpu_lib video_lib debugger_lib)