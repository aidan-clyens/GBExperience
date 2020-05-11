project(ui_lib)

add_library(${PROJECT_NAME} STATIC ui.cpp ui.h)
target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-window sfml-system)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})