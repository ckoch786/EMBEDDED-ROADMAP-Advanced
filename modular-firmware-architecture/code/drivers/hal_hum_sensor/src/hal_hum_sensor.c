#include "hal_hum_sensor.h"
#include <stdio.h>

static const HAL_HumSensor_Driver_t *s_drv = NULL;

int hal_hum_sensor_init(void *dev)
{
    s_drv = hal_hum_get_drv();
    return s_drv && s_drv->init ? s_drv->init(dev) : -1;
}

uint16_t hal_hum_sensor_read(void *dev)
{
    return s_drv && s_drv->read_raw ? s_drv->read_raw(dev) : 0;
}
