.syntax unified
.cpu cortex-m4
.fpu softvfp
.thumb

.extern main

/* linker symbols for memory sections */
.global _estack
.global _sdata
.global _edata
.global _etext
.global _sbss
.global _ebss

/* interrupt vector table */
.section .isr_vector,"a",%progbits
.type g_pfnVectors, %object
.size g_pfnVectors, .-g_pfnVectors
g_pfnVectors:
  .word _estack            /* initial stack pointer */
  .word Reset_Handler      /* reset handler entry point */
  .word Default_Handler    /* NMI */
  .word Default_Handler    /* HardFault */
  .word Default_Handler    /* MemManage */
  .word Default_Handler    /* BusFault */
  .word Default_Handler    /* UsageFault */
  .word 0,0,0,0
  .word Default_Handler    /* SVC */
  .word Default_Handler    /* DebugMon */
  .word 0
  .word Default_Handler    /* PendSV */
  .word Default_Handler    /* SysTick */
  /* default handlers for all IRQs */
  .rept 82
    .word Default_Handler
  .endr

/* reset handler: executed after reset */
.text
.thumb
.globl Reset_Handler
.type Reset_Handler, %function

Reset_Handler:
  /* copy .data section from flash to RAM */
  ldr r0, =_sdata
  ldr r1, =_edata
  ldr r2, =_etext
1:
  cmp r0, r1
  ittt lt
  ldrlt r3, [r2], #4
  strlt r3, [r0], #4
  blt 1b

  /* zero-initialize .bss section */
  ldr r0, =_sbss
  ldr r1, =_ebss
  movs r2, #0
2:
  cmp r0, r1
  it lt
  strlt r2, [r0], #4
  blt 2b

  /* call main() */
  bl main

  /* if main returns, reset again */
  b Reset_Handler

.size Reset_Handler, .-Reset_Handler

/* default interrupt handler: infinite loop */
.thumb_func
Default_Handler:
  b .
