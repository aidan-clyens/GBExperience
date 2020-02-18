project(GameBoy)

add_subdirectory(display)
add_subdirectory(file_parser)
add_subdirectory(memory)
add_subdirectory(cpu)

add_library(${PROJECT_NAME}_lib STATIC main.cpp)
target_include_directories(${PROJECT_NAME}_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(${PROJECT_NAME}_run main.cpp)
target_link_libraries(${PROJECT_NAME}_run display_lib file_parser_lib memory_lib cpu_lib)