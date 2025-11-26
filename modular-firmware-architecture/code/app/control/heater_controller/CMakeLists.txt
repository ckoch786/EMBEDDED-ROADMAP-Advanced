add_library(heater_controller_lib
    src/heater_controller.c
)

target_link_libraries(heater_controller_lib PUBLIC
    sensors_lib
    actuators_lib
    logger_lib
)

target_include_directories(heater_controller_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
