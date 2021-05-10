project(GameBoy)

add_subdirectory(user_interface)
add_subdirectory(file_parser)
add_subdirectory(memory)
add_subdirectory(cpu)
add_subdirectory(video)
add_subdirectory(timer)
add_subdirectory(debugger)
add_subdirectory(utils)

add_library(${PROJECT_NAME}_lib STATIC gameboy.h gameboy.cpp)
target_include_directories(${PROJECT_NAME}_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

if (GAMEBOY_EXE_CLI)
    add_executable(${PROJECT_NAME}_cli main_cli.cpp gameboy.h gameboy.cpp)
    target_link_libraries(${PROJECT_NAME}_cli user_interface_lib file_parser_lib memory_lib cpu_lib video_lib timer_lib debugger_lib utils_lib)
    target_link_libraries(${PROJECT_NAME}_cli Qt5::Widgets)
endif()

if (GAMEBOY_EXE_GUI)
    add_executable(${PROJECT_NAME} WIN32 main_gui.cpp gameboy.h gameboy.cpp)
    target_link_libraries(${PROJECT_NAME} user_interface_lib file_parser_lib memory_lib cpu_lib video_lib timer_lib debugger_lib utils_lib)
    target_link_libraries(${PROJECT_NAME} Qt5::Widgets)
    
    install(
        TARGETS ${PROJECT_NAME}
        DESTINATION bin
    )

    if (WIN32)
    # Ensure the Qt runtime libraries are installed
        include(Windeployqt)
        windeployqt(${PROJECT_NAME} bin)
    endif()
endif()


if (NOT SFML_STATIC_LIBRARIES)
    file(GLOB SFML_DLL_FILES ${SFML_BIN_DIR}/*.dll)

    install(
        FILES ${SFML_DLL_FILES}
        DESTINATION bin
    )
endif()
