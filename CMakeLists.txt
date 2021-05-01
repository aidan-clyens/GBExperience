cmake_minimum_required(VERSION 3.10)

project(GameBoy)

enable_testing()
set(PYTEST
    ${PROJECT_SOURCE_DIR}/venv/bin/python3
    ${PROJECT_SOURCE_DIR}/venv/bin/pytest
)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
set(SFML_STATIC_LIBRARIES FALSE CACHE BOOL "Use static SFML libraries")
set(SFML_ROOT "C:/SFML-2.3.1")

if (SFML_STATIC_LIBRARIES)
    add_definitions(-DSFML_STATIC)
endif()

if (CMAKE_BUILD_TYPE EQUAL "Debug")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -g")
endif()
if (CMAKE_BUILD_TYPE EQUAL "Release")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
endif()

find_package(SFML 2 COMPONENTS audio graphics window system network REQUIRED)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
else()
    set(SFML_ROOT "" CACHE_PATH "SFML top-level directory")
    message("SFML directory not found")
endif()

add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(lib/googletest)
