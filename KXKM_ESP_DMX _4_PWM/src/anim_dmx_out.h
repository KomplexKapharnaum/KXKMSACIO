#include <K32_light.h>
#include <K32_dmx.h>

class Anim_dmx_out : public K32_anim
{

public:
    // Loop
    void draw(int data[ANIM_DATA_SLOTS])
    {
        //PWM
        if (light->pwm)
        {
            light->pwm->set(0, data[LULU_PATCHSIZE - 4] * this->master() / 255); // 5 = par led / 16 = strobe
            light->pwm->set(1, data[LULU_PATCHSIZE - 3] * this->master() / 255); // 6 = par led / 17 = strobe
            light->pwm->set(2, data[LULU_PATCHSIZE - 2] * this->master() / 255); // 7 = par led / 18 = strobe
            light->pwm->set(3, data[LULU_PATCHSIZE - 1] * this->master() / 255); // 8 = par led / 19 = strobe
            // LOGF5("ANIM: -> Red %d PWM %d %d %d %d \n", data[3], data[16], data[17], data[18], data[19]);
        }

#ifndef ELP_Start
        if (light->dmx)
            light->dmx->setMultiple(data, LULU_PATCHSIZE - 4);
#endif
    }
};


