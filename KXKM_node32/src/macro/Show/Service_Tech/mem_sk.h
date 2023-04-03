#include <K32_presets.h>

#define STRIP_PATCHSIZE 16


// 
// MEM ANIMATOR DATA 
//

class BankSK : public LBank { 
    public:
        BankSK() : LBank(STRIP_PATCHSIZE) {
//                  {0      , 1  , 2  , 3  , 4  ,5       , 6        , 7       , 8       , 9         , 10     , 11     , 12     , 13     , 14         , 15   } adr + -1
//                  {master , r  , g  , b  , w  ,pix mod , pix long , pix_pos , str_mod , str_speed , r_fond , g_fond , b_fond , w_fond , mirror_mod , zoom }
            add(    0,   0,   0,   0,   0,       0,         0,        0,        0,          0,       0,       0,       0,       0,           0,    0); //  0 BLACK 
            add(    0,   0,   0,   0,   0,       0,         0,        0,        0,          0,       0,       0,       0,       0,           0,    0); //  1 BLACK 
            add(    0,   0,   0,   0,   0,       0,         0,        0,        0,          0,       0,       0,       0,       0,           0,    0); //  2 BLACK 
            add(  255, 255, 255, 255, 255,      22,        10,       80,        0,          0,     255,     255,     255,     255,           0,  255); //  3 respi white 
            mem->mod(new K32_mod_sinus)->period(1000)->at(1)->at(2)->at(3)->at(4)->phase(0)->mini(0)->maxi(255);
            mem->mod(new K32_mod_sinus)->period(1000)->at(10)->at(11)->at(12)->at(13)->phase(180)->mini(0)->maxi(255);
            add(    0,   0,   0,   0,   0,       0,         0,        0,        0,          0,       0,       0,       0,       0,           0,    0); //  4 BLACK 
            add(  255, 255, 255, 255, 255,      22,         8,       80,        0,          0,     255,     255,     255,     255,           0,  255); //  5 respi white 
            mem->mod(new K32_mod_sinus)->period(1000)->at(1)->at(2)->at(3)->at(4)->phase(0)->mini(0)->maxi(255);
            mem->mod(new K32_mod_sinus)->period(1000)->at(10)->at(11)->at(12)->at(13)->phase(180)->mini(0)->maxi(255);
            add(    0,   0,   0,   0,   0,       0,         0,        0,        0,          0,       0,       0,       0,       0,           0,    0); //  6 BLACK 
            add(  255, 255, 255, 255, 255,      22,         4,       80,        0,          0,     255,     255,     255,     255,           0,  255); //  7 respi white 
            mem->mod(new K32_mod_sinus)->period(1000)->at(1)->at(2)->at(3)->at(4)->phase(0)->mini(0)->maxi(255);
            mem->mod(new K32_mod_sinus)->period(1000)->at(10)->at(11)->at(12)->at(13)->phase(180)->mini(0)->maxi(255);
            add(    0,   0,   0,   0,   0,       0,         0,        0,        0,          0,       0,       0,       0,       0,           0,    0); //  8 BLACK 
            
            add(    0,   0,   0,   0,   0,       0,         0,        0,        0,          0,       0,       0,       0,       0,           0,    0); //  BLACK stm leave lset mem
       
        }
};

// 
// PREVIEW PIXEL MAP
//

class BankSK_PREV : public LBank { 
    public:
        BankSK_PREV() : LBank(6*4) {

                      //  {r1,g1,b1,w1, r2,g2,b2,w2, r3,g3,w3,w3, r4,g4,b4,w4, r5,g5,b5,w5, r6,g6,b6,w6},
                add(1, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0);    // 00 red
                add(0, 1, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0);    // 01 Green
                add(0, 0, 1, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0);    // 02 Blue
                add(0, 0, 0, 1,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0);    // 03 White
                add(1, 0, 0, 0,  0, 1, 0, 0,  0, 0, 1, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0);    // 04 rvb **3 4 5**
                add(0, 0, 0, 1,  0, 0, 0, 1,  0, 0, 0, 1,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0);    // 05 str rnd 67
                add(0, 0, 0, 1,  0, 0, 0, 1,  0, 0, 0, 1,  0, 0, 0, 1,  0, 0, 0, 0,  0, 0, 0, 0);    // 06 str all 67
                add(0, 0, 0, 1,  0, 0, 0, 1,  0, 0, 0, 1,  0, 0, 0, 1,  0, 0, 0, 1,  0, 0, 0, 0);    // 07 str all 42
                add(0, 0, 0, 0,  0, 0, 0, 1,  0, 0, 0, 1,  0, 0, 0, 0,  0, 0, 0, 1,  0, 0, 0, 1);    // 08 str all lent
                add(0, 0, 0, 1,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 1);    // 09 circule w **9** 20>255
                add(0, 0, 0, 1,  0, 0, 0, 1,  0, 0, 1, 0,  0, 0, 1, 0,  0, 0, 0, 0,  0, 0, 0, 0);    // 10 circus w b
                add(0, 0, 1, 0,  0, 0, 1, 0,  0, 0, 1, 0,  0, 0, 0, 1,  0, 0, 0, 1,  0, 0, 0, 1);    // 11 str w -> blue
                add(0, 0, 1, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0);    // 12 blue all
                add(0, 0, 1, 0,  0, 0, 0, 0,  0, 0, 1, 0,  0, 0, 0, 0,  0, 0, 1, 0,  0, 0, 0, 0);    // 13 blue parcielle
                add(0, 0, 0, 0,  0, 0, 1, 0,  0, 0, 0, 0,  0, 0, 1, 0,  0, 0, 0, 0,  0, 0, 0, 0);    // 14 respi blue 
                add(0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0);    // 15 BLACK stm leave last mem
        }
};