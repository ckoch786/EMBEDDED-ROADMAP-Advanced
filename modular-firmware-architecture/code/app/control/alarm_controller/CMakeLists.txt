add_library(alarm_controller_lib
    src/alarm_controller.c
)

target_link_libraries(alarm_controller_lib PUBLIC
    sensors_lib
    actuators_lib
    logger_lib
)

target_include_directories(alarm_controller_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
