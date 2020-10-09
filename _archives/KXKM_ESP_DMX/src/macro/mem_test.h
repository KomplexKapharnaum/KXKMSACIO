#ifndef memtest_h
#define memtest_h

#define NUMBER_OF_MEM 15 // stm leave in last mem

// 
// MEM ANIMATOR DATA 
//
uint8_t MEM[NUMBER_OF_MEM][LULU_PATCHSIZE] = {
    {  255,  35,  45,  15,   0,     235,       127,      127,        0,          0,       0,       0,       0,       0,           0,  255,     0,    0}, // 00 bleu blanc rouge
    {  255,   0,   0,   0, 255,       0,         0,        0,        0,          0,      90,      90,      90,      90,           0,  255,     0,    0}, // 01 white
    {  255, 255,   0,   0,   0,       0,         0,        0,        0,          0,      90,       0,       0,       0,           0,  255,     0,    0}, // 02 Red
    {  255,   0, 255,   0,   0,       0,         0,        0,        0,          0,       0,      90,       0,       0,           0,  255,     0,    0}, // 03 Green
    {  255,   0,   0, 255,   0,       0,         0,        0,        0,          0,       0,       0,      90,       0,           0,  255,     0,    0}, // 04 Blue
    {  255, 255, 255,   0,   0,       0,         0,        0,        0,          0,     100,     100,       0,       0,           0,  255,     0,    0}, // 05 Yellow
    {  255,   0, 255, 255,   0,       0,         0,        0,        0,          0,       0,     100,     100,       0,           0,  255,     0,    0}, // 06 Cyan
    {  255, 255,   0, 255,   0,       0,         0,        0,        0,          0,     110,       0,     110,       0,           0,  255,     0,    0}, // 07 Magenta
    {  255, 255, 255, 255,   0,      65,       255,      127,        0,          0,       0,     255,       0,       0,           0,  255,     0,    0}, // 08 arc
    {  255, 255, 255, 255, 255,       0,         0,        0,       11,         80,     110,     110,     110,     110,           0,  255,     0,    0}, // 09 str white
    {  255, 255, 255, 255,   0,      65,       255,      127,        0,          0,     127,     255,       0,       0,           0,  255,     0,    0}, // 10 arc mouv
    {  255, 100, 100, 100,   0,       0,         0,        0,        0,          0,      90,      90,      90,      90,           0,  255,     0,    0}, // 11 modulo rvb
    {  255,  25,  45,  15,   0,     235,       127,      127,        0,          0,       0,       0,       0,       0,           0,  255,     0,    0}, // 12 vert blanc rouge
    {    0,   0,   0,   0,   0,       0,         0,        0,        0,          0,       0,       0,       0,       0,           0,    0,     0,    0}, // 13 BLACK stm leave lst mem
    {    0,   0,   0,   0,   0,       0,         0,        0,        0,          0,       0,       0,       0,       0,           0,    0,     0,    0}, // 14 BLACK stm leave lset mem
};
//{master , r  , g  , b  , w  ,pix mod , pix long , pix_pos , str_mod , str_speed , r_fond , g_fond , b_fond , w_fond , mirror_mod , zoom , pw1 , pw2 }
//{0      , 1  , 2  , 3  , 4  ,5       , 6        , 7       , 8       , 9         , 10     , 11     , 12     , 13     , 14         , 15   , 16  , 17  } adr + -1



// 
// PREVIEW PIXEL MAP
//
uint8_t MEM_PREV[NUMBER_OF_MEM][LULU_PREVPIX*4] = {
    {0, 0, 1, 0,  0, 0, 1, 0,  0, 0, 0, 1,  0, 0, 0, 1,  1, 0, 0, 0,  1, 0, 0, 0},    // 00 bleu blanc rouge
    {0, 0, 0, 1,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0},    // 01 white
    {1, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0},    // 02 Red
    {0, 1, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0},    // 03 Green
    {0, 0, 1, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0},    // 04 Blue
    {1, 1, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0},    // 05 Yellow
    {0, 1, 1, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0},    // 06 Cyan
    {1, 0, 1, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0},    // 07 Magenta
    {1, 0, 0, 0,  1, 1, 0, 0,  0, 1, 0, 0,  0, 1, 1, 0,  0, 0, 1, 0,  1, 0, 1, 0},    // 08 Arc
    {0, 0, 0, 1,  0, 0, 0, 0,  0, 0, 0, 1,  0, 0, 0, 0,  0, 0, 0, 1,  0, 0, 0, 0},    // 09 str white
    {1, 0, 0, 0,  1, 1, 0, 0,  0, 1, 0, 0,  0, 1, 1, 0,  0, 0, 1, 0,  1, 0, 1, 0},    // 10 Arc mouv
    {1, 0, 0, 0,  0, 1, 0, 0,  0, 0, 1, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0},    // 11 modulo rvb
    {0, 1, 0, 0,  0, 1, 0, 0,  0, 0, 0, 1,  0, 0, 0, 1,  1, 0, 0, 0,  1, 0, 0, 0},    // 12 vert blanc rouge
    {0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0},    // 13 BLACK stm leave last mem
    {0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0},    // 14 BLACK stm leave last mem
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