#ifndef node_h
#define node_h

#define PRESET_COUNT 16 // stm leave in last mem

void init_mem() {}

//
// MEM ANIMATOR DATA ! modulateur relatif a la valeur du tableau
//
uint8_t MEM[PRESET_COUNT][LULU_PATCHSIZE] = {
    {255, 255, 0, 0, 0, 255, 255, 255, 255},     // 00 Red
    {255, 0, 255, 0, 0, 170, 170, 170, 170},     // 01 Green
    {255, 0, 0, 255, 0, 126, 126, 126, 126},     // 02 Blue
    {255, 255, 255, 255, 0, 82, 82, 82, 82},     // 03 White
    {255, 255, 255, 255, 0, 255, 255, 255, 255}, // 04 rvb **3 4 5**
    {255, 255, 255, 255, 29, 0, 0, 0, 0},        // 05 str rnd 67
    {255, 255, 255, 255, 58, 255, 170, 126, 82}, // 06 str all 67
    {255, 255, 255, 255, 100, 170, 126, 82, 0},  // 07 str all 42
    {255, 255, 255, 255, 230, 126, 82, 0, 255},  // 08 str all lent
    {255, 255, 255, 255, 0, 82, 0, 255, 170},    // 09 circule w **9** 20>255
    {255, 255, 255, 255, 0, 0, 255, 170, 126},   // 10 circus w b **7** 1>255
    {255, 255, 255, 255, 89, 255, 170, 126, 82}, // 11 str w -> blue
    {255, 255, 255, 255, 10, 170, 126, 82, 0},   // 12 color form
    {255, 0, 127, 255, 0, 126, 82, 0, 255},      // 13 blue parcielle
    {255, 0, 80, 200, 0, 82, 0, 255, 170},       // 14 respi blue **0**38 > 217
    {255, 0, 0, 0, 0, 0, 0, 0, 0},               // 15 BLACK stm leave lset mem
};
//{master , r  , g  , b  , str , pwm1, pwm2, pwm3, pwm4}
//{0      , 1  , 2  , 3  ,  4  ,  5  ,  6  ,  7  , 8   } adr + -1

uint8_t MEM_NO_WIFI[LULU_PATCHSIZE] = {255, 0, 0, 0, 0, LULU_MEMNOWIFI_MASTER, LULU_MEMNOWIFI_MASTER, LULU_MEMNOWIFI_MASTER, LULU_MEMNOWIFI_MASTER};

//
// PREVIEW PIXEL MAP
//
uint8_t MEM_PREV[PRESET_COUNT][LULU_PREV_SIZE * 4] = {
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // 00 red
    {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // 01 Green
    {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // 02 Blue
    {0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // 03 White
    {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // 04 rvb **3 4 5**
    {0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // 05 str rnd 67
    {0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0}, // 06 str all 67
    {0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0}, // 07 str all 42
    {0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1}, // 08 str all lent
    {0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}, // 09 circule w **9** 20>255
    {0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // 10 circus w b
    {0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1}, // 11 str w -> blue
    {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // 12 blue all
    {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0}, // 13 blue parcielle
    {0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // 14 respi blue
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // 15 BLACK stm leave last mem
};
//  {r1,g1,b1,w1, r2,g2,b2,w2, r3,g3,w3,w3, r4,g4,b4,w4, r5,g5,b5,w5, r6,g6,b6,w6},

//
// APPLY MACRO WITH CUSTOM MODULATORS INTO anim
//
void load_mem(K32_anim *anim, int macro)
{

    // remove disposable modulators
    //
    anim->unmod();

    // push new data
    //

    // add modulators
    //
    
}

#endif