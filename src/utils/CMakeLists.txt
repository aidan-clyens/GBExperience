project(utils_lib)

add_library(${PROJECT_NAME} STATIC string_utils.h string_utils.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})