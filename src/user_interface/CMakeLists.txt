project(user_interface_lib)

include_directories(SYSTEM ${SFML_INCLUDE_DIR})

add_library(${PROJECT_NAME} STATIC user_interface.h user_interface.cpp user_interface_sfml.cpp user_interface_sfml.h launch_window.h launch_window.cpp launch_window.ui game_thread.h game_thread.cpp)
target_link_libraries(${PROJECT_NAME} PUBLIC sfml-audio sfml-network sfml-graphics sfml-window sfml-system Qt5::Widgets Qt5::Core)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

install(
    TARGETS ${PROJECT_NAME}
    DESTINATION lib
)