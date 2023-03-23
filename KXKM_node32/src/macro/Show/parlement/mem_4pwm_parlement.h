#include <K32_presets.h>
#include <K32_version.h>

class BankPWM : public LBank { 
    public:
        BankPWM() : LBank(PWM_N_CHAN) {

            add(    0,    0,    0,    0 );   // 00 off

            add(    0,    0,    0,    0 );   // 01 

            add(    0,    0,    0,    0 );   // 02 

            add(    0,    0,    0,    0 );   // 03 

            add(    0,    0,    0,    0 );   // 04

            add(    0,    0,    0,    0 );   // 05 

            add(  255,  255,  255,  255 );   // 06 on

            add(    0,    0,    0,    0 );   // 07 (red breath) -> off

            add(  255,  255,  255,  255 );   // 08 (red breath) -> leader on

            add(    0,    0,    0,    0 );   // 09 BLACK

        }
};
