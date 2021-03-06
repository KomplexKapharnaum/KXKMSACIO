#ifndef mem_sk_h
#define mem_sk_h

#define NUMBER_OF_MEM 16 // stm leave in last mem

// 
// MEM ANIMATOR DATA 
//
uint8_t MEM_SK[NUMBER_OF_MEM][16] = {
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

uint8_t MEM_SK_NO_WIFI[16] = { 255,   0,   0,   0,  0,       0,         0,        0,        0,          0,       0,       0,       0,       0,           0,  255};

#endif