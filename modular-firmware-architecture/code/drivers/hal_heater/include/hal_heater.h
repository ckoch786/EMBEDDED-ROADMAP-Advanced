#ifndef HAL_HEATER_H
#define HAL_HEATER_H

#include <stdint.h>

typedef struct
{
    int (*init)(void *dev);
    int (*set_state)(void *dev, uint8_t val);

} HAL_Heater_Driver_t;

int hal_heater_init(void *dev);
int hal_heater_write(void *dev, uint8_t val);

const HAL_Heater_Driver_t* hal_heater_get_drv(void);

#endif
