#include <K32_light.h>
#include <K32_dmx.h>

class Anim_datathru  : public K32_anim
{

public:
    // Loop
    void draw(int data[ANIM_DATA_SLOTS])
    {
        int pixCount = min(ANIM_DATA_SLOTS/4, size());

        // Group 4 consecutive data to one RGBW pixel
        for (int k=0; k<pixCount; k++) 
            this->pixel(k, CRGBW(data[k*4], data[k*4+1], data[k*4+2], data[k*4+3]) );

        // Pixel to DMX will be handled by the fixture
    }
};


