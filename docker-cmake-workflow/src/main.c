#include <stdint.h>

#define PERIPH_BASE     (0x40000000U)
#define AHB1PERIPH_BASE (PERIPH_BASE + 0x00020000U)
#define RCC_BASE        (AHB1PERIPH_BASE + 0x3800U)
#define GPIOA_BASE      (AHB1PERIPH_BASE + 0x0000U)

#define RCC_AHB1ENR     (*(volatile uint32_t *)(RCC_BASE + 0x30))
#define GPIOA_MODER     (*(volatile uint32_t *)(GPIOA_BASE + 0x00))
#define GPIOA_ODR       (*(volatile uint32_t *)(GPIOA_BASE + 0x14))

#define RCC_AHB1ENR_GPIOAEN (1U << 0)
#define LED_PIN             (5U)

static void delay(volatile uint32_t t) {
    while (t--) __asm__ volatile("nop");
}

int main(void) {
    /* Enable clock access to GPIOA */
    RCC_AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

    /* PA5 as output */
    GPIOA_MODER &= ~(1U << 11);
    GPIOA_MODER |=  (1U << 10);

    /* Blink */
    for (;;) {
        GPIOA_ODR ^= (1U << LED_PIN);
        delay(120000);
    }
}