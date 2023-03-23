#include <K32_presets.h>
#include <K32_version.h>

class BankPWM : public LBank { 
    public:
        BankPWM() : LBank(PWM_N_CHAN) {

            add(   0,    0,    0,    0 );   // 00 off

            add( 255,    0,    0,    0 );   // 01 on

            add(   0,    0,    0,    0 );   // 02 sablier 1m30

            add( 255,    0,    0,    0 );   // 03 red ready
                mem->mod(new K32_mod_sinus)->at(0)->period(1000);

            add(   0,    0,    0,    0 );   // 04 sablier 1m00

            add(  0,    0,    0,    0 );   // 05 sablier 0m30

            add(   0,    0,    0,    0 );   // 06

            add(   0,    0,    0,    0 );   // 07 

            add(   0,    0,    0,    0 );   // 08 

            add(   0,    0,    0,    0 );   // 09

            add(   0,    0,    0,    0 );   // 10

            add(   0,    0,    0,    0 );   // 11

            add(   0,    0,    0,    0 );   // 12

            add(   0,    0,    0,    0 );   // 13 

            add(   0,    0,    0,    0 );   // 14

            add(   0,    0,    0,    0 );   // 15 BLACK

        }
};
