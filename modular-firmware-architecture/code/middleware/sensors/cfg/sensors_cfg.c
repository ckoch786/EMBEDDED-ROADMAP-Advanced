#include "sensors.h"
#include "interfaces.h"

#include "hal_temp_sensor.h"
#include "hal_hum_sensor.h"
#include "hal_ldr.h"

#include <stdio.h>

typedef struct { const void *i2c_ctx; uint8_t addr;    } TempSensor_Device_t;
typedef struct { const void *i2c_ctx; uint8_t addr;    } HumSensor_Device_t; 
typedef struct { const void *adc_ctx; uint8_t channel; } LdrSensor_Device_t;

static TempSensor_Device_t temp_dev;
static HumSensor_Device_t  hum_dev;
static LdrSensor_Device_t  ldr_dev;

static void temp_init_wrapper(void)
{
    temp_dev.i2c_ctx = interfaces_get("i2c1");
    temp_dev.addr    = 0x48;

    hal_temp_sensor_init(&temp_dev);
}

static float temp_read_wrapper(void)
{
    uint16_t raw = hal_temp_sensor_read(&temp_dev);
    uint16_t raw12 = raw >> 4;

    return (float)raw12 * 0.0625f;
}

static void hum_init_wrapper(void)
{
    hum_dev.i2c_ctx = interfaces_get("i2c1");
    hum_dev.addr = 0x44;

    hal_hum_sensor_init(&hum_dev);
}

static float hum_read_wrapper(void)
{
    uint16_t raw = hal_hum_sensor_read(&hum_dev);
    uint16_t raw12 = raw >> 4;

    return (float)raw12 * 0.0625f;
}

static void ldr_init_wrapper(void)
{
    ldr_dev.adc_ctx  = interfaces_get("adc1");
    ldr_dev.channel  = 1;

    hal_ldr_init(&ldr_dev);
}

static float ldr_read_wrapper(void)
{
    uint16_t raw = hal_ldr_read(&ldr_dev);

    return (raw / 4095.0f) * 100.0f;
}

static SensorDesc_t sensor_table[] =
{
    { "temperature_celsius", temp_init_wrapper, temp_read_wrapper },
    { "light_percent",       ldr_init_wrapper,  ldr_read_wrapper },
    { "humidity_percent",    hum_init_wrapper,   hum_read_wrapper }
};

const SensorDesc_t* sensors_get_table(size_t *count)
{
    *count = sizeof(sensor_table) / sizeof(sensor_table[0]);
    return sensor_table;
}
