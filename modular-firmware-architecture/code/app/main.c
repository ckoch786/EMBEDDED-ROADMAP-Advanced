#include <stdio.h>
#include <unistd.h>

/* App */
#include "fan_controller.h"
#include "light_controller.h"
#include "alarm_controller.h"
#include "heater_controller.h"

/* Middleware */
#include "interfaces.h"
#include "sensors.h"
#include "actuators.h"
#include "storage.h"
#include "logger.h"

int main(void)
{
    /* Middleware */
    interfaces_init();
    sensors_init();
    actuators_init();
    storage_init();
    logger_init();
    logger_log("System boot OK\n");

    while (1)
    {
        alarm_controller_update();
        fan_controller_update();
        light_controller_update();
        heater_controller_update();

#ifdef TARGET_HOST
        break;
#endif
        sleep(10);
    }

    return 0;
}
