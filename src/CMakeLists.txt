set(BINARY ${CMAKE_PROJECT_NAME})

add_executable(${BINARY}_run main.cpp)
add_library(${BINARY}_lib STATIC main.cpp)

target_link_libraries(${BINARY}_run sfml-graphics sfml-window sfml-system)
target_link_libraries(${BINARY}_lib sfml-graphics sfml-window sfml-system)
