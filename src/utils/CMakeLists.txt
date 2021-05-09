project(utils_lib)

add_library(${PROJECT_NAME} STATIC string_utils.h string_utils.cpp subject.h observer.h)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

install(
    TARGETS ${PROJECT_NAME}
    DESTINATION lib
)
