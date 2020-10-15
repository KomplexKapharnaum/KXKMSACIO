#ifndef mem_elp_h
#define mem_elp_h

#ifndef NUMBER_OF_MEM
#define NUMBER_OF_MEM 16 // stm leave in last mem
#endif

// 
// MEM ANIMATOR DATA ! modulateur relatif a la valeur du tableau
//
uint8_t MEM_ELP[NUMBER_OF_MEM][3] = {
    { 255,   0,   0}, // 00 Red
    {   0, 255,   0}, // 01 Green
    {   0,   0, 255}, // 02 Blue
    { 255, 255, 255}, // 03 White
    { 255, 255, 255}, // 04 rvb **3 4 5**
    { 255, 255, 255}, // 05 str rnd 67
    { 255, 255, 255}, // 06 str all 67
    { 255, 255, 255}, // 07 str all 42
    { 255, 255, 255}, // 08 str all lent
    { 255, 255, 255}, // 09 circule w **9** 20>255
    { 255, 255, 255}, // 10 circus w b **7** 1>255
    { 255, 255, 255}, // 12 color form
    { 255, 255, 255}, // 11 str w -> blue
    {   0, 127, 255}, // 13 blue parcielle
    {   0,  80, 200}, // 14 respi blue **0**38 > 217 
    {   0,   0,   0}, // 15 BLACK stm leave lset mem
};
//{   r  , g  , b  }

uint8_t MEM_ELP_NO_WIFI[3] = {12,  127,  19};

#endif