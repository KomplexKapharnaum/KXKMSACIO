#include <K32_presets.h>

void makeSablier(LPreset* mem, int durationSeconds) 
{
    int ms = 1000*durationSeconds/3;
    mem->mod(new K32_mod_isawtooth)->at(7)->period(ms)->mini(2)->maxi(43)->absolute();                 // decompte position
    mem->mod(new K32_mod_pulse)->at(2)->period(3*ms)->param(0, 2*ms)->mini(0)->maxi(255)->absolute();  // green - cycle 1 & 2
    mem->mod(new K32_mod_pulse)->at(1)->period(3*ms)->param(0,   ms)->mini(255)->maxi(0)->absolute();  // red   - cycle 2 & 3
    mem->mod(new K32_mod_sawtooth)->period(3*ms)->event([](int value){                                 // trigger mqtt + jump to mem2 at the end
                                                            if (value==252) mqtt->publish("k32/event/sablier", String(light->id()).c_str());
                                                            // if (value==254) remote->stmSetMacro(2); (handled by burgerquizz.py)
                                                        });
}


class BankSK : public LBank { 
    public:
        BankSK() : LBank(16) {

            //      {master , r  , g  , b  , w  ,pix mod , pix long , pix_pos , str_mod , str_speed , r_fond , g_fond , b_fond , w_fond , mirror_mod , zoom }
            //      {0      , 1  , 2  , 3  , 4  ,5       , 6        , 7       , 8       , 9         , 10     , 11     , 12     , 13     , 14         , 15   } adr + -1
            
            add(mem_t {  255,   0,   0, 255,   0,       0,         0,        0,        0,          0,       0,       0,       0,       0,           0,  255}); // 00 bleu

            add(mem_t {  255,   0,   0,   0,   0,      11,        50,       43,        0,          0,       0,       0,       0,       0,           0,  255}); // 01 sablier 45 sec
                makeSablier(mem, 45);

            add(mem_t {  255,   0,   0,   0,   0,      11,        50,       43,        0,          0,       0,       0,       0,       0,           0,  255}); // 02 sablier 30 sec
                makeSablier(mem, 30);

            add(mem_t {  255,   0,   0,   0,   0,      11,        50,       43,        0,          0,       0,       0,       0,       0,           0,  255}); // 03 sablier 18 sec
                makeSablier(mem, 18);

            add(mem_t {  255,   0,   0,   0,   0,      11,        50,       43,        0,          0,       0,       0,       0,       0,           0,  255}); // 04 sablier 9 sec
                makeSablier(mem, 9);
            
            add(mem_t {  255,   0,   0,   0,   0,      11,        50,       43,        0,          0,       0,       0,       0,       0,           0,  255}); // 05 sablier 3 sec
                makeSablier(mem, 3);

            add(mem_t {  255, 255, 255, 255,   0,       0,         0,        0,        0,          0,       0,       0,       0,       0,           0,  255}); // 06 white

            add(mem_t {  255, 255,   0,   0,   0,       0,         0,        0,        0,          0,       0,       0,       0,       0,           0,  255}); // 07 red breath
                mem->mod(new K32_mod_sinus)->at(0)->period(2000);

            add(mem_t {    0,   0,   0,   0,   0,       0,         0,        0,        0,          0,       0,       0,       0,       0,           0,  255}); // 08 stop -> black

        }
};
