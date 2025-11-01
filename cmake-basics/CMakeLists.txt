# Minimum CMake version and project setup (C + ASM)
cmake_minimum_required(VERSION 3.15)
project(blinky C ASM) 

# Basic project variables
set(TARGET blinky)
set(MCU cortex-m4)
set(LINKER_SCRIPT ${CMAKE_SOURCE_DIR}/linker.ld)

# Cross-compilation setup for bare-metal ARM
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_ASM_COMPILER arm-none-eabi-gcc)

# Compiler and linker flags
set(COMMON_FLAGS -mcpu=${MCU} -mthumb -O2 -ffreestanding -fno-builtin -Wall -Wextra -Werror -fdata-sections -ffunction-sections -g3)
set(LINKER_FLAGS -T${LINKER_SCRIPT} -nostartfiles -nostdlib -Wl,--gc-sections -Wl,--entry=Reset_Handler -Wl,-Map=${TARGET}.map)

# Source files
set(SRC
    src/main.c
    startup.s
)

# Create ELF executable
add_executable(${TARGET}.elf ${SRC})

# Apply flags and link libgcc
target_compile_options(${TARGET}.elf PRIVATE ${COMMON_FLAGS})
target_link_options(${TARGET}.elf PRIVATE ${LINKER_FLAGS})
target_link_libraries(${TARGET}.elf PRIVATE gcc)

# Place outputs in /build directory
set(OUTPUT_DIR ${CMAKE_SOURCE_DIR}/build)
set_target_properties(${TARGET}.elf PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR})

# Add "flash" target to program MCU via OpenOCD
add_custom_target(flash
    COMMAND openocd -f interface/stlink.cfg -f target/stm32f4x.cfg
            -c "program ${OUTPUT_DIR}/${TARGET}.elf verify reset exit"
    DEPENDS ${TARGET}.elf
    COMMENT "Flashing firmware"
)
