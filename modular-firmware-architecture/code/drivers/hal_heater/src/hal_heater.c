#include "hal_heater.h"
#include <stdio.h>

static const HAL_Heater_Driver_t *s_drv = NULL;

int hal_heater_init(void *dev)
{
    s_drv = hal_heater_get_drv();
    return s_drv && s_drv->init ? s_drv->init(dev) : -1;
}

int hal_heater_write(void *dev, uint8_t val)
{
    return s_drv && s_drv->set_state ? s_drv->set_state(dev, val) : -1;
}

