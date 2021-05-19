cmake_minimum_required(VERSION 3.10)

project(GBExperience VERSION 1.1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
set(CMAKE_CXX_FLAGS "-static-libgcc -static-libstdc++" CACHE STRING "GCC static library flags" FORCE)

set(GAMEBOY_EXE_CLI CACHE BOOL True "Build CLI Executable")
set(GAMEBOY_EXE_GUI CACHE BOOL True "Build GUI Executable")

###### SFML ######
# CHANGE TO YOUR SFML ROOT DIRECTORY
set(SFML_ROOT "C:/SFML/install")
set(SFML_DIR "${SFML_ROOT}/lib/cmake/SFML")
set(SFML_INCLUDE_DIR "${SFML_ROOT}/include")
set(SFML_BIN_DIR "${SFML_ROOT}/bin")

set(SFML_STATIC_LIBRARIES False CACHE BOOL "Use static SFML libraries")
if (SFML_STATIC_LIBRARIES)
    add_definitions(-DSFML_STATIC)
endif()

find_package(SFML 2 COMPONENTS audio graphics window system network REQUIRED)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -I${SFML_INCLUDE_DIR}" CACHE STRING "SFML include path" FORCE)

###### Qt ######
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# CHANGE TO YOUR QT5 ROOT DIRECTORY
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

if (MINGW)
    message( STATUS "    Installing system-libraries: MinGW DLLs." )
    get_filename_component(CMAKE_CXX_COMPILER_PATH ${CMAKE_CXX_COMPILER} PATH )
    set(CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS ${CMAKE_CXX_COMPILER_PATH}/libgcc_s_dw2-1.dll ${CMAKE_CXX_COMPILER_PATH}/libstdc++-6.dll ${CMAKE_CXX_COMPILER_PATH}/libwinpthread-1.dll)
endif()

include(InstallRequiredSystemLibraries)

if(CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS)
    install(
        PROGRAMS ${CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS}
        DESTINATION bin
    )
endif()

set(CPACK_GENERATOR NSIS)
set(CPACK_PACKAGE_NAME ${CMAKE_PROJECT_NAME})
set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})
set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})
set(CPACK_PACKAGE_EXECUTABLES "${PROJECT_NAME}" "${PROJECT_NAME}")
set(CPACK_NSIS_MODIFY_PATH "ON")

include(CPack)
