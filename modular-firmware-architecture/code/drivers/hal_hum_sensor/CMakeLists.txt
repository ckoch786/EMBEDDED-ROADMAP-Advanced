add_library(hal_hum_sensor_lib
    src/hal_hum_sensor.c
    cfg/hal_hum_sensor_cfg.c
)

target_link_libraries(hal_hum_sensor_lib
    hal_i2c_lib
)

target_include_directories(hal_hum_sensor_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
