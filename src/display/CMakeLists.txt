set(BINARY ${CMAKE_PROJECT_NAME}_display_lib)

add_library(${BINARY} display.cpp display.h)

target_link_libraries(${BINARY} sfml-graphics sfml-window sfml-system)