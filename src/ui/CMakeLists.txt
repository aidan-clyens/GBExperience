project(ui_lib)

include_directories(SYSTEM ${SFML_INCLUDE_DIR})

add_library(${PROJECT_NAME} STATIC ui.h ui.cpp ui_sfml.cpp ui_sfml.h)
target_link_libraries(${PROJECT_NAME} PUBLIC sfml-audio sfml-network sfml-graphics sfml-window sfml-system)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

install(
    TARGETS ${PROJECT_NAME}
    DESTINATION lib
)

if (NOT SFML_STATIC_LIBRARIES)
    file(GLOB SFML_DLL_FILES ${SFML_BIN_DIR}/*.dll)

    install(
        FILES ${SFML_DLL_FILES}
        DESTINATION bin
    )
endif()