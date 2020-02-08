set(BINARY ${CMAKE_PROJECT_NAME})

add_subdirectory(display)

add_executable(${BINARY}_run main.cpp)
add_library(${BINARY}_lib STATIC main.cpp)

target_link_libraries(${BINARY}_run ${BINARY}_display_lib)
target_link_libraries(${BINARY}_lib ${BINARY}_display_lib)