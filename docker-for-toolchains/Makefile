TARGET=blinky
MCU=cortex-m4
BUILD_DIR=build

SRC=src/main.c
STARTUP=startup.s
OBJS=$(addprefix $(BUILD_DIR)/,$(notdir $(STARTUP:.s=.o) $(SRC:.c=.o)))

CFLAGS=-mcpu=$(MCU) -mthumb -O2 -ffreestanding -fno-builtin -Wall -Wextra -Werror -fdata-sections -ffunction-sections -g3
LDFLAGS=-T linker.ld -nostartfiles -nostdlib -Wl,--gc-sections -Wl,-Map=$(BUILD_DIR)/$(TARGET).map -Wl,--entry=Reset_Handler
LIBS=-lgcc

all: $(BUILD_DIR) $(BUILD_DIR)/$(TARGET).elf

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/%.o: src/%.c | $(BUILD_DIR)
	arm-none-eabi-gcc $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: %.s | $(BUILD_DIR)
	arm-none-eabi-gcc -mcpu=$(MCU) -mthumb -c $< -o $@

$(BUILD_DIR)/$(TARGET).elf: $(OBJS)
	arm-none-eabi-gcc $(CFLAGS) $(OBJS) $(LDFLAGS) $(LIBS) -o $@

.PHONY: clean flash flash-elf

clean:
	rm -rf $(BUILD_DIR)

flash: $(BUILD_DIR)/$(TARGET).elf
	openocd -f interface/stlink.cfg -f target/stm32f4x.cfg -c "program $< verify reset exit"

FILE ?= $(BUILD_DIR)/$(TARGET).elf
ADDR ?= 0x08000000

flash-elf:
	@echo "Flashing ELF: $(FILE)"
	@test -f "$(FILE)" || (echo "ERROR: $(FILE) doesn't exist"; exit 1)
	openocd -f interface/stlink.cfg -f target/stm32f4x.cfg -c "program $(FILE) verify reset exit"