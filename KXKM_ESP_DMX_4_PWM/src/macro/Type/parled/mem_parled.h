#ifndef mem_parled_h
#define mem_parled_h

#ifndef NUMBER_OF_MEM
#define NUMBER_OF_MEM 17 // stm leave in last mem
#endif

// 
// MEM ANIMATOR DATA 
//
uint8_t MEM_PARLED[NUMBER_OF_MEM][5] = {
    {  255, 255,   0,   0,   0}, // 00 Red
    {  255,   0, 255,   0,   0}, // 01 Green
    {  255,   0,   0, 255,   0}, // 02 Blue
    {  255, 255, 255, 255,   0}, // 03 White
    {  255, 255, 255, 255,   0}, // 04 rvb **3 4 5**
    {  255, 255, 255, 255,  29}, // 05 str rnd 67
    {  255, 255, 255, 255,  58}, // 06 str all 67
    {  255, 255, 255, 255, 100}, // 07 str all 42
    {  255, 255, 255, 255, 230}, // 08 str all lent
    {  255, 255, 255, 255,   0}, // 09 circule w **9** 20>255
    {  255, 255, 255, 255,   0}, // 10 circus w b **7** 1>255
    {  255, 255, 255, 255,  89}, // 11 str w -> blue
    {  255, 255, 255, 255,  10}, // 12 color form
    {  255,   0, 127, 255,   0}, // 13 blue parcielle
    {  255,   0,  80, 200,   0}, // 14 respi blue **0**38 > 217 
    {    0,   0,   0,   0,   0}, // 15 BLACK stm leave lset mem
};
//{master , r  , g  , b  , str }
//{0      , 1  , 2  , 3  , 4  } adr + -1

uint8_t MEM_PARLED_NO_WIFI[5] = { 255,  127,  12,  92,   0};


#endif