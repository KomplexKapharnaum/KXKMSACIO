
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

        if (rssi > -45)       this->all( {  0, 255,   0} );
        else if (rssi > -58)  this->all( {  0, 128,   0} );
        else if (rssi > -71)  this->all( {255,  64,   0} );
        else if (rssi > -80)  this->all( {255,   0,   0} );
        else if (rssi == 0)   this->all( {  0,   0, 255} );
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
        for(int i=0; i<LULU_PREVPIX; i++) 
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
            this->pixel( first, CRGBW::Green);  
            this->pixel(  last, CRGBW::Black); 
        }
        else if (state == REMOTE_AUTO_LOCK) {
            this->pixel( first, CRGBW::Red);
            this->pixel(  last, CRGBW::Black);
        }
        else  if (state == REMOTE_MANU) {
            this->pixel( first, CRGBW::Green);
            this->pixel(  last, CRGBW::Green);
        }
        else if (state == REMOTE_MANU_LOCK) {
            this->pixel( first, CRGBW::Red);
            this->pixel(  last, CRGBW::Green);
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
            this->pixel( first, CRGBW::Green);
            this->pixel(  last, {0, 255, 0, 255});
        }

    }
};



// ANIM BATTERY
//

class Anim_battery : public K32_anim
{
public:

    K32_mod_pulse* blink{};
    K32_mod_triangle* chase{};


    // Loop
    void draw(int data[ANIM_DATA_SLOTS])
    {
        int& battery = data[0];

        clear();

        /////////////////////  GREEN   ///////////////////////
        if (battery > 50) 
        {
            pixel(0, CRGBW::Green);

            if (battery > 62) pixel(1, CRGBW::Green);
            if (battery > 74) pixel(2, CRGBW::Green);
            if (battery > 86) pixel(3, CRGBW::Green);
        }

        /////////////////////  ORANGE   ///////////////////////

        else if (battery > 33) 
        {   
            pixel(0, CRGBW::Orange);

            if (battery > 38) pixel(1, CRGBW::Orange);
            if (battery > 42) pixel(2, CRGBW::Orange);
            if (battery > 46) pixel(3, CRGBW::Orange);
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
            blink->period(500)->param(1, 50);        
            if ( blink->value() == 0 ) return;   // Blink OFF, nothing to draw
            
            pixel(0, CRGBW::Red);

            if (battery > 12) pixel(1, CRGBW::Red);
            if (battery > 13) pixel(2, CRGBW::Red);
            if (battery > 14) pixel(3, CRGBW::Red);

        }

        /////////////////////  CHASE+BLINK  ///////////////////////

        else
        {   
            blink->period(300)->param(1, 50);
            if ( blink->value() == 0 ) return;   // Blink OFF, nothing to draw

            chase->period(1000*battery/10)->maxi(this->size()-1);
            pixel( chase->value() , CRGBW::Red);
        }
        

    }
};