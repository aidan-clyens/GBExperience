project(timer_lib)

add_library(${PROJECT_NAME} STATIC timer.h timer.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})