
#include <light/K32_light.h>
#include <xtension/K32_remote.h>
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

        if (rssi == 0)      this->all( CRGBW::Black );

        // WIFI
        else if (rssi < 0) {
            if (rssi > -50)       this->all( CRGBW::Lime );
            else if (rssi > -67)  this->all( CRGBW::Chartreuse );
            else if (rssi > -78)  this->all( CRGBW::Gold );
            else                  this->all( CRGBW::Red ); 
        }

        // BT
        else if (rssi > 0) {
            if (rssi < 50)        this->all( CRGBW::LightCyan );
            else if (rssi < 67)   this->all( CRGBW::Cyan );
            else if (rssi < 78)   this->all( CRGBW::DarkCyan );
            else                  this->all( CRGBW::Blue ); 
        }

        //LOGF("rssi %d\n", rssi);
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
        int& locked = data[1];

        // KEYS pixel
        int first = 0;
        if (locked) this->pixel( first, CRGBW::Red);
        else        this->pixel( first, CRGBW::Lime);  

        // MODE pixel
        int last = this->size()-1;
        if (state == REMOTE_AUTO)           this->pixel(  last, CRGBW::Black); 
        else if (state == REMOTE_MANU)      this->pixel(  last, CRGBW::Lime);
        else if (state == REMOTE_MANU_STM)  this->pixel(  last, CRGBW::Blue);
        else if (state == REMOTE_MANU_LAMP) this->pixel(  last, {0, 255, 0, 255});

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

        // SET MASTER
        master(MASTER_PREV);


        /////////////////////  GREEN   ///////////////////////
        if (battery >= 50) 
        {
            pixel(0, CRGBW::Lime );                       // 62-50%
            if (battery >= 62) pixel(1, CRGBW::Lime);     // 75-62%
            if (battery >= 75) pixel(2, CRGBW::Lime);     // 87-75%
            if (battery >= 87) pixel(3, CRGBW::Lime);     // 100-87%
        }

        /////////////////////  YELLOW   ///////////////////////

        else if (battery >= 15) 
        {   
            pixel(0, CRGBW::Gold);                        // 22-15%
            if (battery >= 23) pixel(1, CRGBW::Gold);     // 31-23%
            if (battery >= 32) pixel(2, CRGBW::Gold);     // 40-32%
            if (battery >= 41) pixel(3, CRGBW::Gold);     // 49-41%
        }

        /////////////////////    RED     ///////////////////////

        else if (battery >= 10)  // SacVP: ~10 min restant
        {   
            pixel(0, CRGBW::Red);                        // 10-11%
            if (battery >= 12) pixel(1, CRGBW::Red);     // 12%
            if (battery >= 13) pixel(2, CRGBW::Red);     // 13%
            if (battery >= 14) pixel(3, CRGBW::Red);     // 14%
        }

        /////////////////////  BLINK   ///////////////////////

        else if (battery >= 4)  // SacVP: ~5 min restant
        {   
            master(255);

            mod("blink")->period(500)->play();      
            if ( mod("blink")->value() == 0 ) return;   // Blink OFF, nothing to draw
            
            pixel(0, CRGBW::Red);                        // 4-5%
            if (battery >= 6) pixel(1, CRGBW::Red);      // 6-7%
            if (battery >= 8) pixel(2, CRGBW::Red);      // 8%
            if (battery >= 9) pixel(3, CRGBW::Red);      // 9%

        }

        /////////////////////  CHASE+BLINK  ///////////////////////

        else if (battery >= 0)    // 0-4%       // SacVP: 3 min (bonus)
        {   
            master(255);

            mod("blink")->period( 100 )->play();
            if ( mod("blink")->value() == 0 ) return;   // Blink OFF, nothing to draw
            
            mod("chase")->period( 300 )->play();
            pixel( mod("chase")->value(), CRGBW::Red);
        }
        
        /////////////////////  CHASE BLUE  ///////////////////////

        else    // -1
        {   
            mod("chase")->period( 700 )->play();
            pixel( mod("chase")->value(), CRGBW::DarkBlue);
        }

        /// STOP MODS IF NO IN USE
        if (battery >= 10) mod("blink")->stop();
        if (battery >= 4) mod("chase")->stop();

    }
};