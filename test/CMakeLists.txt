project(${CMAKE_PROJECT_NAME}_tests)

add_executable(${PROJECT_NAME} main.cpp)
add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME} PRIVATE GameBoy_lib display_lib gtest)
