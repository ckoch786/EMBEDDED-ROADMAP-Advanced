#include "heater_controller.h"

#include "sensors.h"
#include "actuators.h"
#include "logger.h"

#include <stdio.h>

static const char *sensor_temp = "temperature_celsius";
static const char *actuator_heater = "heater";

static float threshold_on  = 30.0f;
static float threshold_off = 27.0f;

static int heater_state = 0;

void heater_controller_update(void)
{
    float temp = sensors_read(sensor_temp);

    char buf_display[64];
    snprintf(buf_display, sizeof(buf_display),
             "Temperature: %.2f C\n", temp);
    logger_log(buf_display);

    int new_state = heater_state;

    if (!heater_state && temp > threshold_on)
        new_state = 1;
    else if (heater_state && temp < threshold_off)
        new_state = 0;

    if (new_state != heater_state)
    {
        heater_state = new_state;
        actuators_write(actuator_heater, &heater_state);
    }

    char buf_flash[128];
    snprintf(buf_flash, sizeof(buf_flash),
             "[HEATER] TEMP=%.2f | STATE=%s\n",
             temp,
             heater_state ? "ON" : "OFF");

    logger_log_to("flash", buf_flash);
}
