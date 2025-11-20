#include "alarm_controller.h"
#include "sensors.h"
#include "actuators.h"
#include "logger.h"

#include <stdio.h>

static float alarm_threshold_hum = 70.0f;

static const char *sensor_hum     = "humidity_percent";
static const char *actuator_alarm = "alarm";

static int alarm_state = 0;

void alarm_controller_update(void)
{
    float hum = sensors_read(sensor_hum);

    char buf_display[64];
    snprintf(buf_display, sizeof(buf_display),
             "Humidity: %.2f %%\n", hum);
    logger_log(buf_display);

    int new_state = hum > alarm_threshold_hum ? 1 : 0;

    if (new_state != alarm_state)
    {
        alarm_state = new_state;
        actuators_write(actuator_alarm, &alarm_state);
    }

    char buf_flash[128];
    snprintf(buf_flash, sizeof(buf_flash),
             "[ALARM] HUM=%.2f %s %.2f | STATE=%s\n",
             hum,
             hum > alarm_threshold_hum ? ">" : "<=",
             alarm_threshold_hum,
             alarm_state ? "ON" : "OFF");

    logger_log_to("flash", buf_flash);
}
