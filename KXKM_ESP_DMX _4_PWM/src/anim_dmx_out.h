#include <light/K32_light.h>
#include <light/K32_dmx.h>


class Anim_dmx_out : public K32_anim
{

public:
    // Loop
    void draw(int data[ANIM_DATA_SLOTS])
    {
        if (k32->dmx)
            k32->dmx->setMultiple(data, ANIM_DATA_SLOTS);
    }
};