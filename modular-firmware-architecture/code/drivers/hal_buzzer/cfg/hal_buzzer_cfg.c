#include "hal_buzzer.h"
#include "hal_gpio.h"
#include <stdio.h>

typedef struct { void *gpio_ctx; uint8_t pin; } HAL_Buzzer_Device_t;

static int buzzer_init_wrapper(void *dev)
{
    HAL_Buzzer_Device_t *d = dev;

#ifdef TARGET_HOST
    printf("[BUZZER_MOCK] init dev=%p port=%p pin=%u\n",
           d, d->gpio_ctx, d->pin);
#endif

    return hal_gpio_init(d->gpio_ctx, d->pin, HAL_GPIO_DIR_OUTPUT);
}

static int buzzer_set_state_wrapper(void *dev, uint8_t on)
{
    HAL_Buzzer_Device_t *d = dev;

#ifdef TARGET_HOST
    printf("[BUZZER_MOCK] write dev=%p port=%p pin=%u val=%u\n",
           d, d->gpio_ctx, d->pin, on);
#endif

    return hal_gpio_write(d->gpio_ctx, d->pin, on);
}

static const HAL_Buzzer_Driver_t buzzer_driver =
{
    .init      = buzzer_init_wrapper,
    .set_state = buzzer_set_state_wrapper
};

const HAL_Buzzer_Driver_t* hal_buzzer_get_drv(void)
{
    return &buzzer_driver;
}
