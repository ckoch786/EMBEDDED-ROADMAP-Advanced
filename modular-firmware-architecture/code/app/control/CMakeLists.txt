add_subdirectory(fan_controller)
add_subdirectory(light_controller)
add_subdirectory(alarm_controller)
add_subdirectory(heater_controller)

add_library(control_lib INTERFACE)

target_link_libraries(control_lib INTERFACE
    fan_controller_lib
    light_controller_lib
    alarm_controller_lib
    heater_controller_lib
)

target_include_directories(control_lib INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
)
