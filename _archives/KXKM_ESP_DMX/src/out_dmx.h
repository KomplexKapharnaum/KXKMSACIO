#include <light/K32_light.h>
#include <LXESP32DMX.h>
#include "esp_task_wdt.h"

class Anim_Out_dmx : public K32_anim
{
public:
    // Loop
    void draw(int data[ANIM_DATA_SLOTS])
    {
        xSemaphoreTake(ESP32DMX.lxDataLock, portMAX_DELAY);

        for (int i = 0; i < LULU_PATCHSIZE; i++)
        {
            ESP32DMX.setSlot(i+1, data[i]);
        }
        xSemaphoreGive(ESP32DMX.lxDataLock);
    }
};