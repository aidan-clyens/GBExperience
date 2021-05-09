cmake_minimum_required(VERSION 3.10)

project(GameBoy)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SFML_ROOT "C:/SFML/install")
set(SFML_DIR "${SFML_ROOT}/lib/cmake/SFML")
set(SFML_INCLUDE_DIR "${SFML_ROOT}/include")

set(SFML_STATIC_LIBRARIES True CACHE BOOL "Use static SFML libraries")
if (SFML_STATIC_LIBRARIES)
    add_definitions(-DSFML_STATIC)
endif()

find_package(SFML 2 COMPONENTS audio graphics window system network REQUIRED)
set(CMAKE_CXX_FLAGS "-I${SFML_INCLUDE_DIR}" CACHE STRING "SFML include path" FORCE)

if (CMAKE_BUILD_TYPE EQUAL "Debug")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -g")
endif()
if (CMAKE_BUILD_TYPE EQUAL "Release")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
endif()

add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(lib/googletest)
