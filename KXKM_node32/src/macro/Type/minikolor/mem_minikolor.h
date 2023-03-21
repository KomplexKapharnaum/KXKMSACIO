#ifndef mem_minikolor_h
#define mem_minikolor_h

#ifndef PRESET_COUNT
#define PRESET_COUNT 16 // stm leave in last mem
#endif

// 
// MEM ANIMATOR DATA ! modulateur relatif a la valeur du tableau
//
uint8_t MEM_MINIKOLOR[PRESET_COUNT][9] = {
    {  255, 255,   0,   0,    0,    0,    0,    0,    0}, // 00 Red
    {  255,   0, 255,   0,    0,    0,    0,    0,    0}, // 01 Green
    {  255,   0,   0, 255,    0,    0,    0,    0,    0}, // 02 Blue
    {  255, 255, 255, 255,    0,    0,    0,    0,    0}, // 03 White
    {  255, 255, 255, 255,    0,    0,    0,    0,    0}, // 04 rvb **3 4 5**
    {  255, 255, 255, 255,    0,   29,    0,    0,    0}, // 05 str rnd 67
    {  255, 255, 255, 255,    0,   58,    0,    0,    0}, // 06 str all 67
    {  255, 255, 255, 255,    0,  100,    0,    0,    0}, // 07 str all 42
    {  255, 255, 255, 255,    0,  230,    0,    0,    0}, // 08 str all lent
    {  255, 255, 255, 255,    0,    0,    0,    0,    0}, // 09 circule w **9** 20>255
    {  255, 255, 255, 255,    0,    0,    0,    0,    0}, // 10 circus w b **7** 1>255
    {  255, 255, 255, 255,    0,   10,    0,    0,    0}, // 12 color form
    {  255, 255, 255, 255,    0,   89,    0,    0,    0}, // 11 str w -> blue
    {  255,   0, 127, 255,    0,    0,    0,    0,    0}, // 13 blue parcielle
    {  255,   0,  80, 200,    0,    0,    0,    0,    0}, // 14 respi blue **0**38 > 217 
    {    0,   0,   0,   0,    0,    0,    0,    0,    0}, // 15 BLACK stm leave lset mem
};
//{master , r  , g  , b  ,macro, str , auto,speed, id  }

uint8_t MEM_MINIKOLOR_NO_WIFI[9] = { 255,  127,  12,  92,   0,   0,   0,   0,   0};

#endif