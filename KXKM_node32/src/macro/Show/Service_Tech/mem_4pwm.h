#include <K32_presets.h>
#include <K32_version.h>

class BankPWM : public LBank { 
    public:
        BankPWM() : LBank(PWM_N_CHAN) {

            add(   0,    0,    0,    0);   //  0 BLACK
            add(   0,    0,    0,    0);   //  1 BLACK
            add(   0,    0,    0,    0);   //  2 BLACK
            add(   0,    0,    0,    0);   //  3 BLACK
            add(   0,    0,    0,    0);   //  4 BLACK
            add(   0,    0,    0,    0);   //  5 BLACK
            add(   0,    0,    0,    0);   //  6 BLACK
            add(   0,    0,    0,    0);   //  7 BLACK
            add( 255,  255,  255,  255);   //  8 FULL 
            mem->mod(new K32_mod_fadein)->period(1000)->at(0)->at(1)->at(2)->at(3)->mini(0)->maxi(255);



            nowifi( LULU_MEMNOWIFI_MASTER, LULU_MEMNOWIFI_MASTER, LULU_MEMNOWIFI_MASTER, LULU_MEMNOWIFI_MASTER );            
        }
};
