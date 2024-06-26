#ifndef mem_hs_h
#define mem_hs_h

#define PRESET_COUNT 16 // stm leave in last mem

// 
// MEM ANIMATOR DATA 
//
uint8_t MEM[PRESET_COUNT][LULU_PATCHSIZE] = {
    {  133, 133,   0,   0,   0,       0,         0,        0,        0,          0,       0,       0,       0,       0,           0,  255,     0,    0}, // 00 Red
    {  255, 255, 255, 255, 255,       0,         0,        0,        0,          0,       0,       0,       0,       0,           0,  255,     0,    0}, // 01 White
    {  255, 255, 255, 255, 255,       0,         1,      127,        5,          0,       0,       0,       0,       0,           0,  255,     0,    0}, // 02 respi white **0** 38 > 217
    {  255, 255, 255, 255, 255,       0,         1,      127,        5,          0,       0,       0,       0,       0,           0,  255,     0,    0}, // 03 respi white speed **0** 38 > 217
    {  255, 255, 255, 255, 255,       0,         0,      127,       45,        255,       0,       0,       0,       0,           0,  255,     0,    0}, // 04 str rnd lent
    {  255, 255, 255, 255, 255,       0,         0,      127,       45,        171,       0,       0,       0,       0,           0,  255,     0,    0}, // 05 str rnd 67
    {  255, 255, 255, 255, 255,       0,         0,      127,       15,        171,       0,       0,       0,       0,           0,  255,     0,    0}, // 06 str all 67
    {  255, 255, 255, 255, 255,       0,         0,      127,       15,        107,       0,       0,       0,       0,           0,  255,     0,    0}, // 07 str all 42
    {  255, 255, 255, 255, 255,       0,         0,      127,       15,        255,       0,       0,       0,       0,           0,  255,     0,    0}, // 08 str all lent
    {  255, 255, 255, 255, 255,       0,         0,      127,      215,          0,       0,       0,       0,       0,           0,  255,     0,    0}, // 09 circule w **9** 229>238
    {  255, 255, 255, 255, 255,      25,         9,      127,        0,          0,       0,       0,     255,       0,           0,  255,     0,    0}, // 10 circus w b **7** 1>255
    {  255, 255, 255, 255, 255,       0,         0,      127,       15,        255,       0,       0,       0,       0,           0,  255,     0,    0}, // 11 str w -> blue
    {  255,   0,   0, 255,   0,       0,         0,      127,        0,          0,       0,       0,       0,       0,           0,  255,     0,    0}, // 12 blue all
    {  255,   0,   0, 255,   0,      55,       170,       56,        0,          0,       0,       0,       0,       0,          35,  255,     0,    0}, // 13 blue parcielle
    {  255,   0,   0, 255,   0,       0,         1,      127,        5,          0,       0,       0,       0,       0,           0,  255,     0,    0}, // 14 respi blue **0**38 > 217 
    {    0,   0,   0,   0,   0,       0,         0,        0,        0,          0,       0,       0,       0,       0,           0,    0,     0,    0}, // 15 BLACK stm leave lset mem
};
//{master , r  , g  , b  , w  ,pix mod , pix long , pix_pos , str_mod , str_speed , r_fond , g_fond , b_fond , w_fond , mirror_mod , zoom , pw1 , pw2 }
//{0      , 1  , 2  , 3  , 4  ,5       , 6        , 7       , 8       , 9         , 10     , 11     , 12     , 13     , 14         , 15   , 16  , 17  } adr + -1



// 
// PREVIEW PIXEL MAP
//
uint8_t MEM_PREV[PRESET_COUNT][LULU_PREV_SIZE*4] = {
    {1, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0},    // 00 red
    {0, 0, 0, 1,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0},    // 01 white
    {0, 0, 0, 0,  0, 0, 0, 1,  0, 0, 0, 0,  0, 0, 0, 1,  0, 0, 0, 0,  0, 0, 0, 0},    // 02 respi white
    {0, 0, 0, 0,  0, 0, 0, 1,  0, 0, 0, 0,  0, 0, 0, 1,  0, 0, 0, 0,  0, 0, 0, 1},    // 03 respi white speed
    {0, 0, 0, 1,  0, 0, 0, 1,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0},    // 04 str rnd lent
    {0, 0, 0, 1,  0, 0, 0, 1,  0, 0, 0, 1,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0},    // 05 str rnd 67
    {0, 0, 0, 1,  0, 0, 0, 1,  0, 0, 0, 1,  0, 0, 0, 1,  0, 0, 0, 0,  0, 0, 0, 0},    // 06 str all 67
    {0, 0, 0, 1,  0, 0, 0, 1,  0, 0, 0, 1,  0, 0, 0, 1,  0, 0, 0, 1,  0, 0, 0, 0},    // 07 str all 42
    {0, 0, 0, 0,  0, 0, 0, 1,  0, 0, 0, 1,  0, 0, 0, 0,  0, 0, 0, 1,  0, 0, 0, 1},    // 08 str all lent
    {0, 0, 0, 1,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 1},    // 09 circule w
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
void load_mem(K32_anim *anim, int macro) {

    // remove disposable modulators
    //
    anim->unmod();

    // push new data
    //
    anim->push(MEM[macro], LULU_PATCHSIZE);

    // add modulators
    //
    if (macro == 2)
    {
        anim->mod(new K32_mod_sinus)->at(0)->period(8500)->mini(38)->maxi(217);
    }
    else if (macro == 3)
    {
        anim->mod(new K32_mod_sinus)->at(0)->period(4800)->mini(38)->maxi(217);
    }
    else if (macro == 9)
    {
        anim->mod(new K32_mod_sawtooth)->at(9)->mini(229)->maxi(238)->period(3700);
    }
    else if (macro == 10)
    {
        anim->mod(new K32_mod_sawtooth)->at(7)->period(7000);
    }
    else if (macro == 11)
    {
        anim->mod(new K32_mod_pulse)->at(1)->at(2)->at(4)->param(1, 66)->period(7000);
        anim->mod(new K32_mod_pulse)->at(8)              ->param(1, 66)->period(7000);
    }
    else if (macro == 14)
    {
        anim->mod(new K32_mod_sinus)->at(0)->period(8500)->mini(38)->maxi(217);
    }
}

#endif