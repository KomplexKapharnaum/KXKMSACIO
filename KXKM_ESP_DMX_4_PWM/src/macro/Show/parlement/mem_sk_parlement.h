#include <K32_presets.h>



class BankSK : public LBank { 
    public:
        BankSK() : LBank(16) {

            //      {master , r  , g  , b  , w  ,pix mod , pix long , pix_pos , str_mod , str_speed , r_fond , g_fond , b_fond , w_fond , mirror_mod , zoom }
            //      {0      , 1  , 2  , 3  , 4  ,5       , 6        , 7       , 8       , 9         , 10     , 11     , 12     , 13     , 14         , 15   } adr + -1
            add(mem_t {  255,   0,   0, 255,   0,       0,         0,        0,        0,          0,       0,       0,       0,       0,           0,  255}); // 00 bleu

            add(mem_t {  255, 255, 255, 255,   0,       0,         0,        0,        0,          0,       0,       0,       0,       0,           0,  255}); // 01 white

            add(mem_t {  255,   0, 255,   0,   0,      11,        50,       43,        0,          0,       0,       0,       0,       0,           0,  255}); // 02 sablier vert
                mem->mod(new K32_mod_isawtooth)->at(7)->period(8500)->phase(0)->mini(2)->maxi(43)->absolute();
                mem->mod(new K32_mod_pulse)->param(0,2*8500)->at(2)->period(3*8500)->phase(0)->mini(0)->maxi(255)->absolute();
                mem->mod(new K32_mod_pulse)->param(0,2*8500)->at(1)->period(3*8500)->phase(120)->mini(0)->maxi(255)->absolute();

            add(mem_t {  255, 255,   0,   0,   0,       0,         0,        0,       21,        180,       0,       0,       0,       0,           0,  255}); // 03 red smooth

            add(mem_t {  255, 255,   0,   0,   0,       0,         0,        0,       11,        180,       0,       0,       0,       0,           0,  255}); // 04 red str

            add(mem_t {  255, 255, 255, 255,   0,       0,         0,        0,       11,        100,       0,       0,       0,       0,           0,  255}); // 05 white str 

            add(mem_t {  255, 255, 255, 255,   0,       0,         0,        0,       67,        180,       0,       0,       0,       0,           0,  255}); // 06 white str rnd 67


            

            
            
            add(mem_t {  255,   0,   0, 255,   0,       0,         0,        0,        0,          0,       0,       0,      90,       0,           0,  255}); // 07 Blue

            add(mem_t {  255, 255, 255,   0,   0,       0,         0,        0,        0,          0,     100,     100,       0,       0,           0,  255}); // 08 Yellow

            add(mem_t {  255,   0, 255, 255,   0,       0,         0,        0,        0,          0,       0,     100,     100,       0,           0,  255}); // 09 Cyan
                mem->mod(new K32_mod_sinus)->at(0)->mini(100)->maxi(255)->period(2000);
            
            add(mem_t {  255, 255, 255, 255, 255,      25,         9,      127,        0,          0,       0,       0,     255,       0,           0,  255}); // 10 circus w b **7** 1>255
                mem->mod(new K32_mod_sinus)->at(1)->at(2)->period(8500)->phase(0)->mini(0)->maxi(255);
            
            add(mem_t {  255, 255, 255, 255, 255,       0,         0,      127,       15,        255,       0,       0,       0,       0,           0,  255}); // 11 str w -> blue
                mem->mod(new K32_mod_pulse)->at(2)->at(3)->param(1, 100)->period(7000);
            
            add(mem_t {  255,   0,   0, 255,   0,       0,         0,      127,        0,          0,       0,       0,       0,       0,           0,  255}); // 12 blue all
                mem->mod(new K32_mod_sinus)->at(1)->period(8500)->phase(0)->mini(0)->maxi(255);
                mem->mod(new K32_mod_sinus)->at(2)->period(8500)->phase(120)->mini(0)->maxi(255);
                mem->mod(new K32_mod_sinus)->at(3)->period(8500)->phase(240)->mini(0)->maxi(255);
            
            add(mem_t {  255,   0,   0, 255,   0,      55,       170,       56,        0,          0,       0,       0,       0,       0,          35,  255}); // 13 blue parcielle

            add(mem_t {  255,   0,   0, 255,   0,       0,         1,      127,        5,          0,       0,       0,       0,       0,           0,  255}); // 14 respi blue **0**38 > 217 
                mem->mod(new K32_mod_sinus)->at(0)->period(8500)->mini(38)->maxi(217);
            
            add(mem_t {    0,   0,   0,   0,   0,       0,         0,        0,        0,          0,       0,       0,       0,       0,           0,    0}); // 15 BLACK stm leave lset mem


            nowifi(mem_t { 255,   0,   0,   0,    0,       0,         0,        0,        0,          0,       0,       0,       0,       0,           0,  255});            
        }
};


// 
// PREVIEW PIXEL MAP
//

class BankSK_PREV : public LBank { 
    public:
        BankSK_PREV() : LBank(6*4) {

                add(mem_t {1, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0});    // 00 red
                add(mem_t {0, 1, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0});    // 01 Green
                add(mem_t {0, 0, 1, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0});    // 02 Blue
                add(mem_t {0, 0, 0, 1,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0});    // 03 White
                add(mem_t {1, 0, 0, 0,  0, 1, 0, 0,  0, 0, 1, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0});    // 04 rvb **3 4 5**
                add(mem_t {0, 0, 0, 1,  0, 0, 0, 1,  0, 0, 0, 1,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0});    // 05 str rnd 67
                add(mem_t {0, 0, 0, 1,  0, 0, 0, 1,  0, 0, 0, 1,  0, 0, 0, 1,  0, 0, 0, 0,  0, 0, 0, 0});    // 06 str all 67
                add(mem_t {0, 0, 0, 1,  0, 0, 0, 1,  0, 0, 0, 1,  0, 0, 0, 1,  0, 0, 0, 1,  0, 0, 0, 0});    // 07 str all 42
                add(mem_t {0, 0, 0, 0,  0, 0, 0, 1,  0, 0, 0, 1,  0, 0, 0, 0,  0, 0, 0, 1,  0, 0, 0, 1});    // 08 str all lent
                add(mem_t {0, 0, 0, 1,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 1});    // 09 circule w **9** 20>255
                add(mem_t {0, 0, 0, 1,  0, 0, 0, 1,  0, 0, 1, 0,  0, 0, 1, 0,  0, 0, 0, 0,  0, 0, 0, 0});    // 10 circus w b
                add(mem_t {0, 0, 1, 0,  0, 0, 1, 0,  0, 0, 1, 0,  0, 0, 0, 1,  0, 0, 0, 1,  0, 0, 0, 1});    // 11 str w -> blue
                add(mem_t {0, 0, 1, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0});    // 12 blue all
                add(mem_t {0, 0, 1, 0,  0, 0, 0, 0,  0, 0, 1, 0,  0, 0, 0, 0,  0, 0, 1, 0,  0, 0, 0, 0});    // 13 blue parcielle
                add(mem_t {0, 0, 0, 0,  0, 0, 1, 0,  0, 0, 0, 0,  0, 0, 1, 0,  0, 0, 0, 0,  0, 0, 0, 0});    // 14 respi blue 
                add(mem_t {0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0});    // 15 BLACK stm leave last mem
        }
};