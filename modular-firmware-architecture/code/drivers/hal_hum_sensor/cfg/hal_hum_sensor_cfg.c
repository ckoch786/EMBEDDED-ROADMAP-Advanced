#include "hal_hum_sensor.h"
#include "hal_i2c.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct { void *i2c_ctx; uint8_t addr; } HAL_HumSensor_Device_t;

static int hum_init_wrapper(void *dev)
{
    HAL_HumSensor_Device_t *d = dev;

#ifdef TARGET_HOST
    printf("[HUM_MOCK] init dev=%p i2c_ctx=%p addr=0x%02X\n",
           d, d->i2c_ctx, d->addr);
#endif

    return hal_i2c_init(d->i2c_ctx);
}

static uint16_t hum_read_wrapper(void *dev)
{
    HAL_HumSensor_Device_t *d = dev;
    uint8_t raw[2];

    hal_i2c_read(d->i2c_ctx, d->addr, raw, 2);

#ifdef TARGET_HOST
    float hum = 20.0f + (rand() % 7000) / 100.0f;
    uint16_t raw12  = (uint16_t)(hum * 40.95f);
    uint16_t packed = raw12 << 4;
    raw[0] = packed >> 8;
    raw[1] = packed & 0xFF;

    printf("[HUM_MOCK] read dev=%p i2c_ctx=%p addr=0x%02X hum=%.2f%% raw12=%u packed=0x%04X\n",
           d, d->i2c_ctx, d->addr, hum, raw12, packed);
#endif

    return ((uint16_t)raw[0] << 8) | raw[1];
}

static const HAL_HumSensor_Driver_t hum_driver =
{
    .init     = hum_init_wrapper,
    .read_raw = hum_read_wrapper
};

const HAL_HumSensor_Driver_t* hal_hum_get_drv(void)
{
    return &hum_driver;
}
