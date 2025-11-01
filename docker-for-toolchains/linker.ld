/* Memory map of STM32F401RE */
MEMORY
{
  FLASH (rx) : ORIGIN = 0x08000000, LENGTH = 512K   /* program + constants */
  RAM   (rwx): ORIGIN = 0x20000000, LENGTH = 96K    /* variables + stack */
}

/* top of the stack (end of RAM) */
_estack = ORIGIN(RAM) + LENGTH(RAM);

SECTIONS
{
  /* interrupt vector table in flash */
  .isr_vector : {
    KEEP(*(.isr_vector))
  } > FLASH

  /* program code and constants */
  .text : {
    *(.text*) *(.rodata*)
    _etext = .;    /* end of text section */
  } > FLASH

  /* initialized variables (.data) live in RAM but are stored in flash at _etext */
  .data : AT ( _etext ) {
    _sdata = .;
    *(.data*)
    _edata = .;
  } > RAM

  /* zero-initialized variables (.bss) in RAM */
  .bss : {
    _sbss = .;
    *(.bss*) *(COMMON)
    _ebss = .;
  } > RAM

  /* stack area (no data preloaded) */
  ._user_stack (NOLOAD): {
  } > RAM
}
