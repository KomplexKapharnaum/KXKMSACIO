#ifndef memstrobe_h
#define memstrobe_h

#define NUMBER_OF_MEM 16 // stm leave in last mem

// 
// MEM ANIMATOR DATA 
//
uint8_t MEM[NUMBER_OF_MEM][LULU_PATCHSIZE] = {
    {  255,   2,        0, 255,   0,   0,         0,        0,        0,          0,       0,      0,      0,      0,        0,             255}, // 00 Red
    {  255,   2,        0,   0, 255,   0,         0,        0,        0,          0,       0,      0,      0,      0,        0,             255}, // 01 Green
    {  255,   2,        0,   0,   0, 255,         0,        0,        0,          0,       0,      0,      0,      0,        0,             255}, // 02 Blue
    {  255,   2,        0, 255, 255, 255,         0,        0,        0,          0,       0,      0,      0,      0,        0,             255}, // 03 White
    {  255,   2,        0, 255, 255, 255,         0,        0,        0,          0,       0,      0,      0,      0,        0,             255}, // 04 rvb **3 4 5**
    {  255,  29,       67, 255, 255, 255,         0,      127,       45,        171,       0,      0,      0,      0,        0,             255}, // 05 str rnd 67
    {  255, 230,       67, 255, 255, 255,         0,      127,       15,        171,       0,      0,      0,      0,        0,             255}, // 06 str all 67
    {  255, 230,       42, 255, 255, 255,         0,      127,       15,        107,       0,      0,      0,      0,        0,             255}, // 07 str all 42
    {  255, 230,      127, 255, 255, 255,         0,      127,       15,        255,       0,      0,      0,      0,        0,             255}, // 08 str all lent
    {  255,   2,        0, 255, 255, 255,         0,        0,      167,         14,      10,      0,      0,      0,      255,             255}, // 09 circule w **9** 20>255
    {  255,   2,        0, 255, 255, 255,         9,      127,       45,          0,       0,      0,      0,    255,      255,             255}, // 10 circus w b **7** 1>255
    {  255, 230,      180, 255, 255, 255,         0,        0,        0,          0,       0,      0,      0,    255,      255,             255}, // 11 str w -> blue
    {  255, 230,      180, 255, 255, 255,         0,        0,      122,         78,       0,      0,      0,    255,      255,             255}, // 12 color form
    {  255,   2,        0,   0, 127, 255,       170,       56,        0,          0,       0,      0,      0,      0,       35,             255}, // 13 blue parcielle
    {  255,   2 ,       0,   0,  80, 200,         1,      127,       85,          0,       0,      0,     10,    255,      255,             255}, // 14 respi blue **0**38 > 217 
    {    0,   0,        0,   0,   0,   0,         0,        0,        0,          0,       0,      0,      0,      0,        0,               0}, // 15 BLACK stm leave lset mem
};
//{master , str,str speed, r  , g  , b  , color mod, color eff,type eff, blast eff ,  ? eff , r eff , g eff , b eff , dim eff , background dim }
//{0      , 1  ,      2  , 3  , 4  , 5  , 6        ,  7       , 8      , 9         , 10     , 11    , 12    , 13    , 14      , 15             } adr + -1


// 
// PREVIEW PIXEL MAP
//
uint8_t MEM_PREV[NUMBER_OF_MEM][LULU_PREVPIX*4] = {
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
void load_mem(K32_anim *anim, int macro) {

    // remove disposable modulators
    //
    anim->unmod();

    // push new data
    //
    anim->push(MEM[macro], LULU_PATCHSIZE);

    // add modulators
    //
    if (macro == 4)
    {
        anim->mod(new K32_mod_sinus)->at(3)->period(8500)->phase(0)->mini(0)->maxi(255);
        anim->mod(new K32_mod_sinus)->at(4)->period(8500)->phase(120)->mini(0)->maxi(255);
        anim->mod(new K32_mod_sinus)->at(5)->period(8500)->phase(240)->mini(0)->maxi(255);
    }
    else if (macro == 9)
    {
        anim->mod(new K32_mod_sinus)->at(9)->mini(100)->maxi(255)->period(2000);
    }
    else if (macro == 10)
    {
        anim->mod(new K32_mod_sawtooth)->at(7)->period(7000);
    }
    else if (macro == 11)
    {
        anim->mod(new K32_mod_pulse)->at(3)->at(4)->param(1, 100)->period(7000);
    }
    else if (macro == 12)
    {
        anim->mod(new K32_mod_sinus)->at(3)->period(8500)->phase(0)->mini(0)->maxi(255);
        anim->mod(new K32_mod_sinus)->at(4)->period(8500)->phase(120)->mini(0)->maxi(255);
        anim->mod(new K32_mod_sinus)->at(5)->period(8500)->phase(240)->mini(0)->maxi(255);
    }
    else if (macro == 14)
    {
        anim->mod(new K32_mod_sinus)->at(0)->period(8500)->mini(38)->maxi(217);
    }
}



#endif