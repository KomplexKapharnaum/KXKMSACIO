
#include <light/K32_light.h>
#include <remote/K32_remote.h>
#include "mem.h"

// ANIM RSSI
//

class Anim_rssi : public K32_anim
{
public:

    // Loop
    void draw(int data[ANIM_DATA_SLOTS])
    {
        int& rssi = data[0];
        
        if (rssi == 0)        this->all( CRGBW::Blue );
        else if (rssi > -50)  this->all( CRGBW::Lime );
        else if (rssi > -67)  this->all( CRGBW::Chartreuse );
        else if (rssi > -78)  this->all( CRGBW::Gold );
        else                  this->all( CRGBW::Red );

        // LOGF("rssi %d\n", rssi);
    }
};


// ANIM PREVIEW
//

class Anim_preview : public K32_anim
{
public:

    // Loop
    void draw(int data[ANIM_DATA_SLOTS])
    {   
        int size = min(this->size(), ANIM_DATA_SLOTS/4);

        for(int i=0; i<size; i++) 
        {
            CRGBW color{data[i*4], data[i*4+1], data[i*4+2], data[i*4+3]};
            this->pixel(i, color*(uint8_t)255);
        }
    }
};



// ANIM REMOTE
//

class Anim_remote : public K32_anim
{
public:

    // Loop
    void draw(int data[ANIM_DATA_SLOTS])
    {
        int& state = data[0];

        int first = 0;
        int last = this->size()-1;

        if (state == REMOTE_AUTO) {
            this->pixel( first, CRGBW::Lime);  
            this->pixel(  last, CRGBW::Black); 
        }
        else if (state == REMOTE_AUTO_LOCK) {
            this->pixel( first, CRGBW::Red);
            this->pixel(  last, CRGBW::Black);
        }
        else  if (state == REMOTE_MANU) {
            this->pixel( first, CRGBW::Lime);
            this->pixel(  last, CRGBW::Lime);
        }
        else if (state == REMOTE_MANU_LOCK) {
            this->pixel( first, CRGBW::Red);
            this->pixel(  last, CRGBW::Lime);
        }
        else  if (state == REMOTE_MANU_STM) {
            this->pixel( first, CRGBW::Blue);
            this->pixel(  last, CRGBW::Blue);
        }
        else if (state == REMOTE_MANU_STM_LOCK) {
            this->pixel( first, CRGBW::Red);
            this->pixel(  last, CRGBW::Blue);
        }
        else  if (state == REMOTE_MANU_LAMP) {
            this->pixel( first, CRGBW::Lime);
            this->pixel(  last, {0, 255, 0, 255});
        }

    }
};



// ANIM BATTERY
//

class Anim_battery : public K32_anim
{
public:

    void init () 
    {
        this->mod("blink", new K32_mod_pulse)->param(1, 50);
        this->mod("chase", new K32_mod_triangle)->maxi(this->size()-1);
    }

    // Loop
    void draw(int data[ANIM_DATA_SLOTS])
    {
        int& battery = data[0];

        // LOGF("ANIM: battery, received value: %d\n", battery);

        clear();

        /////////////////////  GREEN   ///////////////////////
        if (battery > 50) 
        {
            pixel(0, CRGBW::Lime );

            if (battery > 62) pixel(1, CRGBW::Lime);
            if (battery > 74) pixel(2, CRGBW::Lime);
            if (battery > 86) pixel(3, CRGBW::Lime);
        }

        /////////////////////  ORANGE   ///////////////////////

        else if (battery > 33) 
        {   
            pixel(0, CRGBW::Gold);

            if (battery > 38) pixel(1, CRGBW::Gold);
            if (battery > 42) pixel(2, CRGBW::Gold);
            if (battery > 46) pixel(3, CRGBW::Gold);
        }

        /////////////////////    RED     ///////////////////////

        else if (battery > 16) 
        {   
            pixel(0, CRGBW::Red);

            if (battery > 20) pixel(1, CRGBW::Red);
            if (battery > 25) pixel(2, CRGBW::Red);
            if (battery > 29) pixel(3, CRGBW::Red);
        }

        /////////////////////  BLINK   ///////////////////////

        else if (battery > 11)
        {   
            mod("blink")->period(500)->play();      
            if ( mod("blink")->value() == 0 ) return;   // Blink OFF, nothing to draw
            
            pixel(0, CRGBW::Red);

            if (battery > 12) pixel(1, CRGBW::Red);
            if (battery > 13) pixel(2, CRGBW::Red);
            if (battery > 14) pixel(3, CRGBW::Red);

        }

        /////////////////////  CHASE+BLINK  ///////////////////////

        else
        {   
            mod("blink")->period( max(500*battery/10, 100) )->play();
            if ( mod("blink")->value() == 0 ) return;   // Blink OFF, nothing to draw
            
            mod("chase")->period( max(1500*battery/10, 300) )->play();
            pixel( mod("chase")->value(), CRGBW::Red);
        }
        

        /// STOP MODS IF NO IN USE
        if (battery > 16) mod("blink")->stop();
        if (battery > 11) mod("chase")->stop();

        // SET MASTER
        if (battery > 11) master(MASTER_PREV);
        else master(255);

    }
};