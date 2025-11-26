add_library(hal_heater_lib
    src/hal_heater.c
    cfg/hal_heater_cfg.c
)

target_include_directories(hal_heater_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
