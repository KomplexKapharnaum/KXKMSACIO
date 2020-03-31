#define NUMBER_OF_MEM 13 // stm leave in last mem
int MEM[NUMBER_OF_MEM][LULU_PATCHSIZE] = {
    {  255,  35,  45,  15,   0,     235,       127,      127,        0,          0,       0,       0,       0,       0,          0,           0,  240,     0,    0}, // bleu blanc rouge
    {  255,   0,   0,   0, 255,       0,         0,        0,        0,          0,      90,      90,      90,      90,          0,           0,  255,    30,  255}, // white
    {  255, 255,   0,   0,   0,       0,       255,        0,        0,          0,       0,       0,       0,       0,          0,           0,  255,    60,  240}, // Red
    {  255,   0, 255,   0,   0,       0,         0,        0,        0,          0,       0,      90,       0,       0,          0,           0,  255,    90,  210}, // Green
    {  255,   0,   0, 255,   0,       0,         0,        0,        0,          0,       0,       0,      90,       0,          0,           0,  255,   120,  180}, // Blue
    {  255, 255, 255,   0,   0,       0,         0,        0,        0,          0,     100,     100,       0,       0,          0,           0,  255,   150,  150}, // Yellow
    {  255,   0, 255, 255,   0,       0,         0,        0,        0,          0,       0,     100,     100,       0,          0,           0,  255,   180,  120}, // Cyan
    {  255, 255,   0, 255,   0,       0,         0,        0,        0,          0,     110,       0,     110,       0,          0,           0,  255,   210,   90}, // Magenta
    {  255, 255, 255, 255,   0,       0,       255,        0,        0,          0,       0,     255,       0,       0,         15,           0,  255,   240,   60}, // arc
    {  255, 255, 255, 255, 255,       0,         0,        0,       11,         80,     110,     110,     110,     110,          0,           0,  255,   255,   30}, // str white
    {  255, 255, 255, 255,   0,       0,       255,      127,        0,          0,     127,     255,       0,       0,         15,           0,  255,   240,   60}, // arc mouv
    {  255, 100, 100, 100,   0,       0,         0,        0,        0,          0,      90,      90,      90,      90,          0,           0,  255,     0,    0}, // modulo rvb
    {    0,   0,   0,   0,   0,       0,         0,        0,        0,          0,       0,       0,       0,       0,          0,           0,    0,     0,    0}, // BLACK stm leave lst mem
};
//{master , r  , g  , b  , w  ,pix mod , pix long , pix_pos , str_mod , str_speed , r_fond , g_fond , b_fond , w_fond , color_mod , mirror_mod , zoom , pw1 , pw2 }
//{0      , 1  , 2  , 3  , 4  ,5       , 6        , 7       , 8       , 9         , 10     , 11     , 12     , 13     , 14        , 15         , 16   , 17  , 18  } adr + -1

#define COEF_PREV 25
int MEM_PREV[NUMBER_OF_MEM][24] = {
    { 0, 0,01, 0,  0, 0,01, 0,  0, 0, 0,01,  0, 0, 0,01, 01, 0, 0, 0, 01, 0, 0, 0},    // bleu blanc rouge
    { 0, 0, 0,01,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0},    // white
    {01, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0},    // Red
    { 0,01, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0},    // Green
    { 0, 0,01, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0},    // Blue
    {01,01, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0},    // Yellow
    { 0,01,01, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0},    // Cyan
    {01, 0,01, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0},    // Magenta
    {01, 0, 0, 0, 01,01, 0, 0,  0,01, 0, 0,  0,01,01, 0,  0, 0,01, 0, 01, 0,01, 0},    // Arc
    { 0, 0, 0,01,  0, 0, 0, 0,  0, 0, 0,01,  0, 0, 0, 0,  0, 0, 0,01,  0, 0, 0, 0},    // str white
    {01, 0, 0, 0, 01,01, 0, 0,  0,01, 0, 0,  0,01,01, 0,  0, 0,01, 0, 01, 0,01, 0},    // Arc mouv
    {01, 0, 0, 0,  0,01, 0, 0,  0, 0,01, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0},    // modulo rvb
    { 0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0},    // BLACK stm leave last mem
};
//  {r1,g1,b1,w1, r2,g2,b2,w2, r3,g3,w3,w3, r4,g4,b4,w4, r5,g5,b5,w5, r6,g6,b6,w6},
