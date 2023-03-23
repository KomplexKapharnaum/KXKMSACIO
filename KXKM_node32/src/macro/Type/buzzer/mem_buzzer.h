#include <K32_presets.h>
#include <K32_version.h>
#include <K32_mods.h>

class BankPWM : public LBank { 
    public:
        BankPWM() : LBank(PWM_N_CHAN) {

            add(   0,    0,    0,    0 );   // 00 off

            add( 255,    0,    0,    0 );   // 01 on

            add( 255,    0,    0,    0 );   // 02 breath slow
                mem->mod(new K32_mod_sinus)->at(0)->period(2000);

            add( 255,    0,    0,    0 );   // 03 breath fast
                mem->mod(new K32_mod_sinus)->at(0)->period(800);

            add( 255,    0,    0,    0 );   // 04 blink slow
                mem->mod(new K32_mod_pulse)->param(1,10)->at(0)->period(1000);

            add( 255,    0,    0,    0 );   // 05 blink fast
                mem->mod(new K32_mod_pulse)->param(1,10)->at(0)->period(200);
        }
};



#define STRIP_PATCHSIZE 16

class BankSK : public LBank { 
    public:
        BankSK() : LBank(STRIP_PATCHSIZE) {

            //      {master , r  , g  , b  , w  ,pix mod , pix long , pix_pos , str_mod , str_speed , r_fond , g_fond , b_fond , w_fond , mirror_mod , zoom }
            //      {0      , 1  , 2  , 3  , 4  ,5       , 6        , 7       , 8       , 9         , 10     , 11     , 12     , 13     , 14         , 15   } adr + -1
            
            add(255,   0,   50,   0,   0,       0,         0,        0,        0,          0,       0,       0,       0,       0,           0,  255 ); // 00 off

            add(255,   255,   0,   0,   0,     0,         0,        0,        0,          0,       0,       0,       0,       0,           0,  255 );  // 01 on

            add(255,   255,   0,   0,   0,     0,         0,        0,        0,          0,       0,       0,       0,       0,           0,  255 ); // 02 breath slow
                mem->mod(new K32_mod_sinus)->at(0)->period(2000);

            add(255,   255,   0,   0,   0,     0,         0,        0,        0,          0,       0,       0,       0,       0,           0,  255 );  // 03 breath fast
                mem->mod(new K32_mod_sinus)->at(0)->period(800);

            add(255,   255,   0,   0,   0,     0,         0,        0,        0,          0,       0,       0,       0,       0,           0,  255 );  // 04 blink slow
                mem->mod(new K32_mod_pulse)->param(1,10)->at(0)->period(1000);
            
            add(255,   255,   0,   0,   0,     0,         0,        0,        0,          0,       0,       0,       0,       0,           0,  255 );  // 05 blink fast
                mem->mod(new K32_mod_pulse)->param(1,10)->at(0)->period(200);

        }
};
