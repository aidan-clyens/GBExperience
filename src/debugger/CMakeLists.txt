project(debugger_lib)

add_library(${PROJECT_NAME} STATIC debugger.h debugger.cpp timing_analyzer.h timing_analyzer.cpp logger.h logger.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

install(
    TARGETS ${PROJECT_NAME}
    DESTINATION lib
)
