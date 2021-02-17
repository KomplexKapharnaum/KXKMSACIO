#include <light/K32_light.h>
#include <light/K32_dmx.h>

class Anim_dmx_out : public K32_anim
{

public:
    // Loop
    void draw(int data[ANIM_DATA_SLOTS])
    {
        //PWM
        if (k32->pwm)
        {
            k32->pwm->set(0, data[LULU_PATCHSIZE - 4] * this->master() / 255); // 5 = par led / 16 = strobe
            k32->pwm->set(1, data[LULU_PATCHSIZE - 3] * this->master() / 255); // 6 = par led / 17 = strobe
            k32->pwm->set(2, data[LULU_PATCHSIZE - 2] * this->master() / 255); // 7 = par led / 18 = strobe
            k32->pwm->set(3, data[LULU_PATCHSIZE - 1] * this->master() / 255); // 8 = par led / 19 = strobe
            // LOGF5("ANIM: -> Red %d PWM %d %d %d %d \n", data[3], data[16], data[17], data[18], data[19]);
        }

#ifndef ELP_Start
        if (k32->dmx)
            k32->dmx->setMultiple(data, LULU_PATCHSIZE - 4);
#endif
    }
};