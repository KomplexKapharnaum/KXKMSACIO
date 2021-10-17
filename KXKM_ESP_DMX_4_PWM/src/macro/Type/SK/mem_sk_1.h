
#ifdef SK_PRESET_COUNT
    #error "MEM_SK already loaded.. please load only one MEM_SK !"
#endif

#define SK_PRESET_COUNT 16
#define SK_PRESET_SIZE  16

// LIMITER
#if !defined(PRESET_COUNT) || PRESET_COUNT >  SK_PRESET_COUNT
    #define PRESET_COUNT                       SK_PRESET_COUNT
#endif

// ²
// MEM ANIMATOR DATA 
//
uint8_t MEM_SK[SK_PRESET_COUNT][ANIM_DATA_SLOTS] = {
    {  133, 133,   0,   0,   0,       0,         0,        0,        0,          0,       0,       0,       0,       0,           0,  255}, // 00 Red
    {  255,  35,  45,  15,   0,     235,       127,      127,        0,          0,       0,       0,       0,       0,           0,  255}, // 01 bleu blanc rouge
    {  255, 255, 255, 255,   0,      65,       255,      127,        0,          0,       0,     255,       0,       0,           0,  255}, // 02 arc
    {  255, 255, 255, 255, 255,       0,         1,      127,        5,          0,       0,       0,       0,       0,           0,  255}, // 03 respi white speed **0** 38 > 217
    {  255, 127, 255, 255,   0,      15,        86,      177,        0,          0,       0,       0,       0,       0,           0,  255}, // 04 vert blanc rouge
    {  255, 255, 255,   0,   0,      12,        53,      205,        0,          0,       0,       0,       0,       0,           0,  255}, // 05 str rnd 67
    {  255,   0, 255,   0,   0,       0,         0,        0,        0,          0,       0,      90,       0,       0,           0,  255}, // 06 Green
    {  255,   0,   0, 255,   0,       0,         0,        0,        0,          0,       0,       0,      90,       0,           0,  255}, // 07 Blue
    {  255, 255, 255,   0,   0,       0,         0,        0,        0,          0,     100,     100,       0,       0,           0,  255}, // 08 Yellow
    {  255,   0, 255, 255,   0,       0,         0,        0,        0,          0,       0,     100,     100,       0,           0,  255}, // 09 Cyan
    {  255, 255, 255, 255, 255,      25,         9,      127,        0,          0,       0,       0,     255,       0,           0,  255}, // 10 circus w b **7** 1>255
    {  255, 255, 255, 255, 255,       0,         0,      127,       15,        255,       0,       0,       0,       0,           0,  255}, // 11 str w -> blue
    {  255,   0,   0, 255,   0,       0,         0,      127,        0,          0,       0,       0,       0,       0,           0,  255}, // 12 blue all
    {  255,   0,   0, 255,   0,      55,       170,       56,        0,          0,       0,       0,       0,       0,          35,  255}, // 13 blue parcielle
    {  255,   0,   0, 255,   0,       0,         1,      127,        5,          0,       0,       0,       0,       0,           0,  255}, // 14 respi blue **0**38 > 217 
    {    0,   0,   0,   0,   0,       0,         0,        0,        0,          0,       0,       0,       0,       0,           0,    0}, // 15 BLACK stm leave lset mem
};
//{master , r  , g  , b  , w  ,pix mod , pix long , pix_pos , str_mod , str_speed , r_fond , g_fond , b_fond , w_fond , mirror_mod , zoom }
//{0      , 1  , 2  , 3  , 4  ,5       , 6        , 7       , 8       , 9         , 10     , 11     , 12     , 13     , 14         , 15   } adr + -1

uint8_t MEM_SK_NOWIFI[16] = 
    { 255,   0,   0,   0,    0,       0,         0,        0,        0,          0,       0,       0,       0,       0,           0,  255};

// 
// PREVIEW PIXEL MAP
//
uint8_t MEM_SK_PREV[SK_PRESET_COUNT][LULU_PREV_SIZE*4] = {
    {1, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0},    // 00 red
    {0, 1, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0},    // 01 Green
    {0, 0, 1, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0},    // 02 Blue
    {0, 0, 0, 1,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0},    // 03 White
    {1, 0, 0, 0,  0, 1, 0, 0,  0, 0, 1, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0},    // 04 rvb **3 4 5**
    {0, 0, 0, 1,  0, 0, 0, 1,  0, 0, 0, 1,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0},    // 05 str rnd 67
    {0, 0, 0, 1,  0, 0, 0, 1,  0, 0, 0, 1,  0, 0, 0, 1,  0, 0, 0, 0,  0, 0, 0, 0},    // 06 str all 67
    {0, 0, 0, 1,  0, 0, 0, 1,  0, 0, 0, 1,  0, 0, 0, 1,  0, 0, 0, 1,  0, 0, 0, 0},    // 07 str all 42
    {0, 0, 0, 0,  0, 0, 0, 1,  0, 0, 0, 1,  0, 0, 0, 0,  0, 0, 0, 1,  0, 0, 0, 1},    // 08 str all lent
    {0, 0, 0, 1,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 1},    // 09 circule w **9** 20>255
    {0, 0, 0, 1,  0, 0, 0, 1,  0, 0, 1, 0,  0, 0, 1, 0,  0, 0, 0, 0,  0, 0, 0, 0},    // 10 circus w b
    {0, 0, 1, 0,  0, 0, 1, 0,  0, 0, 1, 0,  0, 0, 0, 1,  0, 0, 0, 1,  0, 0, 0, 1},    // 11 str w -> blue
    {0, 0, 1, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0},    // 12 blue all
    {0, 0, 1, 0,  0, 0, 0, 0,  0, 0, 1, 0,  0, 0, 0, 0,  0, 0, 1, 0,  0, 0, 0, 0},    // 13 blue parcielle
    {0, 0, 0, 0,  0, 0, 1, 0,  0, 0, 0, 0,  0, 0, 1, 0,  0, 0, 0, 0,  0, 0, 0, 0},    // 14 respi blue 
    {0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0},    // 15 BLACK stm leave last mem
};
//  {r1,g1,b1,w1, r2,g2,b2,w2, r3,g3,w3,w3, r4,g4,b4,w4, r5,g5,b5,w5, r6,g6,b6,w6},

// 
// APPLY MACRO WITH CUSTOM MODULATORS INTO anim
//
//{master , r  , g  , b  , w  ,pix mod , pix long , pix_pos , str_mod , str_speed , r_fond , g_fond , b_fond , w_fond , mirror_mod , zoom }
//{0      , 1  , 2  , 3  , 4  ,5       , 6        , 7       , 8       , 9         , 10     , 11     , 12     , 13     , 14         , 15   } adr + -1


void load_mem_sk(K32_anim *anim, int macro) {

    // remove disposable modulators
    //
    anim->unmod();

    // push new data
    //
    anim->push(MEM_SK[macro]);

    // add modulators
    //
    if (macro == 4)
    {
        anim->mod(new K32_mod_sinus)->at(1)->at(5)->at(8)->at(3)->at(7)->at(2)->at(6)->period(8500)->phase(0)->mini(-50)->maxi(255);
    }
    else if (macro == 6)
    {
        anim->mod(new K32_mod_pulse)->at(1)->at(2)->at(3)->at(7)->at(8)->at(6)->at(5)->param(1, 10)->period(500);
    }
    else if (macro == 9)
    {
        anim->mod(new K32_mod_sinus)->at(0)->mini(100)->maxi(255)->period(2000);
    }
    else if (macro == 10)
    {
        anim->mod(new K32_mod_sinus)->at(1)->at(2)->period(8500)->phase(0)->mini(0)->maxi(255);
    }
    else if (macro == 11)
    {
        anim->mod(new K32_mod_pulse)->at(2)->at(3)->param(1, 100)->period(7000);
    }
    else if (macro == 12)
    {
        anim->mod(new K32_mod_sinus)->at(1)->period(8500)->phase(0)->mini(0)->maxi(255);
        anim->mod(new K32_mod_sinus)->at(2)->period(8500)->phase(120)->mini(0)->maxi(255);
        anim->mod(new K32_mod_sinus)->at(3)->period(8500)->phase(240)->mini(0)->maxi(255);
    }
    else if (macro == 14)
    {
        anim->mod(new K32_mod_sinus)->at(0)->period(8500)->mini(38)->maxi(217);
    }
}