#include <light/K32_light.h>
#include <LXESP32DMX.h>
#include "esp_task_wdt.h"

class Anim_Out_dmx : public K32_anim
{

public:
    // Loop
    void draw(int data[ANIM_DATA_SLOTS])
    {
    //PWM
 if (k32->pwm)
        {
            k32->pwm->set(0, data[16]);
            k32->pwm->set(1, data[17]);
            k32->pwm->set(2, data[18]);
            k32->pwm->set(3, data[19]);
            // LOGF5("ANIM: -> Red %d PWM %d %d %d %d \n", data[3], data[16], data[17], data[18], data[19]);
        }

        xSemaphoreTake(ESP32DMX.lxDataLock, portMAX_DELAY);

        for (int i = 0; i < LULU_PATCHSIZE - 4; i++)
        {
            ESP32DMX.setSlot(i + 1, data[i]);
        }
        xSemaphoreGive(ESP32DMX.lxDataLock);
    }
};