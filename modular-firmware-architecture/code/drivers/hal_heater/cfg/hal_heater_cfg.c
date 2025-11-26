#include "hal_heater.h"
#include <stdio.h>

typedef struct { void *gpio_ctx; uint8_t pin; } HAL_Heater_Device_t;

static int heater_init_wrapper(void *dev)
{
    HAL_Heater_Device_t *d = dev;

#ifdef TARGET_HOST
    printf("[HEATER_CFG] init dev=%p port=%p pin=%u\n",
           d, d->gpio_ctx, d->pin);
#endif

    return hal_gpio_init(d->gpio_ctx, d->pin, HAL_GPIO_DIR_OUTPUT);
}

static int heater_set_state_wrapper(void *dev, uint8_t val)
{
    HAL_Heater_Device_t *d = dev;

#ifdef TARGET_HOST
    printf("[HEATER_CFG] write dev=%p port=%p pin=%u val=%u\n",
           d, d->gpio_ctx, d->pin, val);
#endif

    return hal_gpio_write(d->gpio_ctx, d->pin, val);
}

static const HAL_Heater_Driver_t heater_driver =
{
    .init      = heater_init_wrapper,
    .set_state = heater_set_state_wrapper
};

const HAL_Heater_Driver_t* hal_heater_get_drv(void)
{
    return &heater_driver;
}
