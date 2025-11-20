#ifndef HAL_BUZZER_H
#define HAL_BUZZER_H

#include <stdint.h>

typedef struct
{
    int (*init)(void *dev);
    int (*set_state)(void *dev, uint8_t on);

} HAL_Buzzer_Driver_t;

int hal_buzzer_init(void *dev);
int hal_buzzer_write(void *dev, uint8_t on);

const HAL_Buzzer_Driver_t* hal_buzzer_get_drv(void);

#endif
