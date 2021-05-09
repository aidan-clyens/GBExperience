cmake_minimum_required(VERSION 3.10)

project(GameBoy)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

###### SFML ######
set(SFML_ROOT "C:/SFML/install")
set(SFML_DIR "${SFML_ROOT}/lib/cmake/SFML")
set(SFML_INCLUDE_DIR "${SFML_ROOT}/include")
set(SFML_BIN_DIR "${SFML_ROOT}/bin")

set(SFML_STATIC_LIBRARIES False CACHE BOOL "Use static SFML libraries")
if (SFML_STATIC_LIBRARIES)
    add_definitions(-DSFML_STATIC)
endif()

find_package(SFML 2 COMPONENTS audio graphics window system network REQUIRED)
set(CMAKE_CXX_FLAGS "-I${SFML_INCLUDE_DIR}" CACHE STRING "SFML include path" FORCE)

###### Qt ######
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(QT5_ROOT "C:/Qt/5.14.2/mingw73_32")
set(QT5_INCLUDE_DIR "${QT5_ROOT}/include")
set(QT5_BIN_DIR "${QT5_ROOT}/bin")

find_package(Qt5 COMPONENTS Widgets Core REQUIRED)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -I${QT5_INCLUDE_DIR}" CACHE STRING "Qt5 include path" FORCE)
file(GLOB CHILDREN RELATIVE ${QT5_INCLUDE_DIR} ${QT5_INCLUDE_DIR}/*)
foreach (CHILD ${CHILDREN})
if (IS_DIRECTORY ${QT5_INCLUDE_DIR}/${CHILD})
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -I${QT5_INCLUDE_DIR}/${CHILD}" CACHE STRING "Qt5 include path" FORCE)
endif()
endforeach()

if (CMAKE_BUILD_TYPE EQUAL "Debug")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -g")
endif()
if (CMAKE_BUILD_TYPE EQUAL "Release")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
endif()

add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(lib/googletest)

include(InstallRequiredSystemLibraries)
set(CPACK_GENERATOR NSIS)
set(CPACK_PACKAGE_NAME ${CMAKE_PROJECT_NAME})
set(CPACK_PACKAGE_VERSION "1.1")
set(CPACK_PACKAGE_VERSION_MAJOR "1")
set(CPACK_PACKAGE_VERSION_MINOR "1")
set(CPACK_PACKAGE_EXECUTABLES "${PROJECT_NAME}" "${PROJECT_NAME}")
set(CPACK_NSIS_MODIFY_PATH "ON")

include(CPack)
