#include <light/K32_light.h>
#include <light/K32_dmx.h>

class Anim_dmx_test : public K32_anim
{

public:

    // Setup
    void init() {
      this->loop(false);
    }

    // Loop
    void draw(int data[ANIM_DATA_SLOTS])
    {
      int out_r_g_b[512] = {0};

      int stepMS = data[0];

      // RED
      //
      for (int i=0; i< size() * 3; i++) 
        if (i%3 == 0) out_r_g_b[i] = master();
        else out_r_g_b[i] = 0;

      k32->dmx->setMultiple(out_r_g_b, 512, 1);

      this->pause(stepMS);


      // GREEN 
      //
      for (int i=0; i< size() * 3; i++) 
        if (i%3 == 1) out_r_g_b[i] = master();
        else out_r_g_b[i] = 0;
        
      k32->dmx->setMultiple(out_r_g_b, 512, 1);

      this->pause(stepMS);

      // BLUE 
      //
      for (int i=0; i< size() * 3; i++) 
        if (i%3 == 2) out_r_g_b[i] = master();
        else out_r_g_b[i] = 0;
        
      k32->dmx->setMultiple(out_r_g_b, 512, 1);

      this->pause(stepMS);

      // WHITE 
      //
      for (int i=0; i< size() * 3; i++) 
        out_r_g_b[i] = master();
        
      k32->dmx->setMultiple(out_r_g_b, 512, 1);

      this->pause(stepMS);

      // CLEAR 
      //
      for (int i=0; i< size() * 3; i++) 
        out_r_g_b[i] = 0;
        
      k32->dmx->setMultiple(out_r_g_b, 512, 1);
    }
};


