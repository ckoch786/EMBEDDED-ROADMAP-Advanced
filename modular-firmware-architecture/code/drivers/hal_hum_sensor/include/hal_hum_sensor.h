#ifndef HAL_HUM_SENSOR_H
#define HAL_HUM_SENSOR_H

#include <stdint.h>

typedef struct
{
    int      (*init)(void *dev);
    uint16_t (*read_raw)(void *dev);

} HAL_HumSensor_Driver_t;

int      hal_hum_sensor_init(void *dev);
uint16_t hal_hum_sensor_read(void *dev);

const HAL_HumSensor_Driver_t* hal_hum_get_drv(void);

#endif
