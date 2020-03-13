#include "Arduino.h"

int sinus(int period, int max, int min, int duration)
{
    float factor = 0;
    unsigned long start = millis();
    unsigned long progress = 0;

    while (progress <= period)
    {
        factor = ((0.5f + 0.5f * sin(2 * PI * progress / period - 0.5f * PI)) * (max - min) + min) / 255;
        progress = millis() - start;
    }
    if (duration > 0)
        if (millis() > (start+duration*1000)) {
          return false;
        }
        return factor;
}
