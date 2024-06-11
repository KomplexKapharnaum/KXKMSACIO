#include <K32_presets.h>
#include <K32_version.h>

class BankPWM : public LBank { 
    public:
        BankPWM() : LBank(PWM_N_CHAN) {

            add( 255,  255,  255,  255);   // 00 

            add( 170,  170,  170,  170);   // 01 

            add( 126,  126,  126,  126);   // 02 

            add(  82,   82,   82,   82);   // 03 

            add( 255,  255,  255,  255);   // 04
                mem->mod(new K32_mod_sinus)->at(1)->at(5)->at(8)->at(3)->at(7)->at(2)->at(6)->period(8500)->phase(0)->mini(-50)->maxi(255);

            add(   0,    0,    0,    0);   // 05 

            add( 255,  170,  126,   82);   // 06
                mem->mod(new K32_mod_pulse)->at(1)->at(2)->at(3)->at(7)->at(8)->at(6)->at(5)->param(1, 10)->period(500);

            add( 170,  126,   82,    0);   // 07 

            add( 126,   82,    0,  255);   // 08 

            add(  82,    0,  255,  170);   // 09
                mem->mod(new K32_mod_sinus)->at(0)->mini(100)->maxi(255)->period(2000);

            add(   0,  255,  170,  126);   // 10
                mem->mod(new K32_mod_sinus)->at(1)->at(2)->period(8500)->phase(0)->mini(0)->maxi(255);

            add( 170,  126,   82,    0);   // 11
                mem->mod(new K32_mod_pulse)->at(2)->at(3)->param(1, 100)->period(7000);

            add( 255,  170,  126,   82);   // 12
                mem->mod(new K32_mod_sinus)->at(1)->period(8500)->phase(0)->mini(0)->maxi(255);
                mem->mod(new K32_mod_sinus)->at(2)->period(8500)->phase(120)->mini(0)->maxi(255);
                mem->mod(new K32_mod_sinus)->at(3)->period(8500)->phase(240)->mini(0)->maxi(255);

            add( 126,   82,    0,  255);   // 13 

            add(  82,    0,  255,  170);   // 14
                mem->mod(new K32_mod_sinus)->at(0)->period(8500)->mini(38)->maxi(217); 

            add(   0,    0,    0,    0);   // 15 BLACK
            add(   0,    0,    0,    0);   // 16 BLACK
            add(   0,    0,    0,    0);   // 17 BLACK
            add(   0,    0,    0,    0);   // 18 BLACK
            add(   0,    0,    0,    0);   // 19 BLACK
            add(   0,    0,    0,    0);   // 20 BLACK


            nowifi( LULU_MEMNOWIFI_MASTER, LULU_MEMNOWIFI_MASTER, LULU_MEMNOWIFI_MASTER, LULU_MEMNOWIFI_MASTER );            
        }
};
