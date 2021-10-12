#ifndef mem_pwm_baro_131_h
#define mem_pwm_baro_131_h

#ifndef NUMBER_OF_MEM
#define NUMBER_OF_MEM 17 // stm leave in last mem
#endif

// 
// MEM ANIMATOR DATA ! modulateur relatif a la valeur du tableau
//
uint8_t MEM_PWM[NUMBER_OF_MEM][4] = {
    {255,  255,  255,  255}, // 00 Red on
    {170,  170,  170,  170}, // 01 Green grad
    {126,  126,  126,  126}, // 02 Blue grad +
    { 82,   82,   82,   82}, // 03 White grad ++
    {255,  255,  255,  255}, // 04 fade  **5 6 7 8**
    {255,  255,  255,  255}, // 05  on fade
    {255,  255,  255,  255}, // 06 str all 
    {255,  255,  255,  255}, // 07 301 on 302 off
    {  0,    0,    0,    0}, // 08 301 off 302 on
    {  0,    0,    0,    0}, // 09  off
    {  0,    0,    0,    0}, // 10  all cube
    {  0,    0,    0,    0}, // 11  cube imp
    {  0,    0,    0,    0}, // 12  cube pair
    {255,  255,  255,  255}, // 13  all table
    {  0,    0,    0,    0}, // 15  table pair
    {255,  255,  255,  255}, // 14  table impair
    {  0,    0,    0,    0}, // 16 BLACK stm leave lset mem
};
//{master , r  , g  , b  , str , pwm1, pwm2, pwm3, pwm4}
//{0      , 1  , 2  , 3  ,  4  ,  16  ,  17  ,  18  , 19   } adr + -1

uint8_t MEM_PWM_NO_WIFI[4] = {LULU_MEMNOWIFI_MASTER,  LULU_MEMNOWIFI_MASTER,  LULU_MEMNOWIFI_MASTER,  LULU_MEMNOWIFI_MASTER};

#endif