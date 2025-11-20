add_subdirectory(hal_adc)
add_subdirectory(hal_buzzer)
add_subdirectory(hal_display)
add_subdirectory(hal_fan)
add_subdirectory(hal_flash)
add_subdirectory(hal_gpio)
add_subdirectory(hal_hum_sensor)
add_subdirectory(hal_i2c)
add_subdirectory(hal_ldr)
add_subdirectory(hal_led)
add_subdirectory(hal_spi)
add_subdirectory(hal_temp_sensor)
add_subdirectory(hal_uart)

add_library(drivers_lib INTERFACE)

target_link_libraries(drivers_lib INTERFACE
    hal_adc_lib
    hal_buzzer_lib
    hal_display_lib
    hal_fan_lib
    hal_flash_lib
    hal_gpio_lib
    hal_hum_sensor_lib
    hal_i2c_lib
    hal_ldr_lib
    hal_led_lib
    hal_spi_lib
    hal_temp_sensor_lib
    hal_uart_lib
)

target_include_directories(drivers_lib INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
)






 
 
 
 
 
 
 
 
 
 
 
 
 
