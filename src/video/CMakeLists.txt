project(video_lib)

add_library(${PROJECT_NAME} STATIC video.h video.cpp tile.h tile.cpp framebuffer.h framebuffer.cpp definitions.h)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})