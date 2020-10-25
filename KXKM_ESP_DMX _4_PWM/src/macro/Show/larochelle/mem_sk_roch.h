#ifndef mem_sk_roch_h
#define mem_sk_roch_h

#define NUMBER_OF_MEM 16 // stm leave in last mem

// 
// MEM ANIMATOR DATA 
//
uint8_t MEM_SK[NUMBER_OF_MEM][16] = {
    {  133, 133,   0,   0,   0,       0,         0,        0,        0,          0,       0,       0,       0,       0,           0,  255}, // 00 Red
    {  255, 255, 255, 255, 255,       0,         0,        0,        0,          0,       0,       0,       0,       0,           0,  255}, // 01 White
    {  255, 255, 255, 255, 255,       0,         1,      127,        5,          0,       0,       0,       0,       0,           0,  255}, // 02 respi white **0** 38 > 217
    {  255, 255, 255, 255, 255,       0,         1,      127,        5,          0,       0,       0,       0,       0,           0,  255}, // 03 respi white speed **0** 38 > 217
    {  255, 255, 255, 255, 255,       0,         0,      127,       45,        255,       0,       0,       0,       0,           0,  255}, // 04 str rnd lent
    {  255, 255, 255, 255, 255,       0,         0,      127,       45,        171,       0,       0,       0,       0,           0,  255}, // 05 str rnd 67
    {  255, 255, 255, 255, 255,       0,         0,      127,       15,        171,       0,       0,       0,       0,           0,  255}, // 06 str all 67
    {  255, 255, 255, 255, 255,       0,         0,      127,       15,        107,       0,       0,       0,       0,           0,  255}, // 07 str all 42
    {  255, 255, 255, 255, 255,       0,         0,      127,       15,        255,       0,       0,       0,       0,           0,  255}, // 08 str all lent
    {  255, 255, 255, 255, 255,       0,         0,      127,      215,          0,       0,       0,       0,       0,           0,  255}, // 09 circule w **9** 229>238
    {  255, 255, 255, 255, 255,      25,         9,      127,        0,          0,       0,       0,     255,       0,           0,  255}, // 10 circus w b **7** 1>255
    {  255, 255, 255, 255, 255,       0,         0,      127,       15,        255,       0,       0,       0,       0,           0,  255}, // 11 str w -> blue
    {  255,   0,   0, 255,   0,       0,         0,      127,        0,          0,       0,       0,       0,       0,           0,  255}, // 12 blue all
    {  255,   0,   0, 255,   0,      55,       170,       56,        0,          0,       0,       0,       0,       0,          35,  255}, // 13 blue parcielle
    {  255,   0,   0, 255,   0,       0,         1,      127,        5,          0,       0,       0,       0,       0,           0,  255}, // 14 respi blue **0**38 > 217 
    {    0,   0,   0,   0,   0,       0,         0,        0,        0,          0,       0,       0,       0,       0,           0,    0}, // 15 BLACK stm leave lset mem
};
//{master , r  , g  , b  , w  ,pix mod , pix long , pix_pos , str_mod , str_speed , r_fond , g_fond , b_fond , w_fond , mirror_mod , zoom }
//{0      , 1  , 2  , 3  , 4  ,5       , 6        , 7       , 8       , 9         , 10     , 11     , 12     , 13     , 14         , 15   } adr + -1

uint8_t MEM_SK_NO_WIFI[16] = { 255,   0,   0, 255,   0,       0,         0,        0,        0,          0,       0,       0,       0,       0,           0,  255};

#endif