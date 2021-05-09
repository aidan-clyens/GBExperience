project(file_parser_lib)

add_library(${PROJECT_NAME} STATIC file_parser.cpp file_parser.h cartridge.h cartridge.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

install(
    TARGETS ${PROJECT_NAME}
    DESTINATION lib
)
