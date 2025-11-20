add_library(hal_buzzer_lib
    src/hal_buzzer.c
    cfg/hal_buzzer_cfg.c
)

target_link_libraries(hal_buzzer_lib
    hal_gpio_lib
)

target_include_directories(hal_buzzer_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
