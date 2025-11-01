cmake_minimum_required(VERSION 3.15)

# Set cross-compilation toolchain BEFORE project()
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)
set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_ASM_COMPILER arm-none-eabi-gcc)
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

project(blinky C ASM)

set(TARGET blinky)
set(MCU cortex-m4)
set(LINKER_SCRIPT ${CMAKE_SOURCE_DIR}/linker.ld)

set(COMMON_FLAGS -mcpu=${MCU} -mthumb -O2 -ffreestanding -fno-builtin -Wall -Wextra -Werror -fdata-sections -ffunction-sections -g3)
set(LINKER_FLAGS -T${LINKER_SCRIPT} -nostartfiles -nostdlib -Wl,--gc-sections -Wl,--entry=Reset_Handler -Wl,-Map=${TARGET}.map)

set(SRC
    src/main.c
    startup.s
)

add_executable(${TARGET}.elf ${SRC})
target_compile_options(${TARGET}.elf PRIVATE ${COMMON_FLAGS})
target_link_options(${TARGET}.elf PRIVATE ${LINKER_FLAGS})
target_link_libraries(${TARGET}.elf PRIVATE gcc)

set(OUTPUT_DIR ${CMAKE_SOURCE_DIR}/build)
set_target_properties(${TARGET}.elf PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR})

add_custom_target(flash
    COMMAND openocd -f interface/stlink.cfg -f target/stm32f4x.cfg
            -c "program ${OUTPUT_DIR}/${TARGET}.elf verify reset exit"
    DEPENDS ${TARGET}.elf
    COMMENT "Flashing firmware"
)
