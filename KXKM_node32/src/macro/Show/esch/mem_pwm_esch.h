#ifndef mem_pwm_esch_132_h
#define mem_pwm_esch_132_h

#ifndef PRESET_COUNT
#define PRESET_COUNT 16 // stm leave in last mem
#endif

// 
// MEM ANIMATOR DATA ! modulateur relatif a la valeur du tableau
//
uint8_t MEM_PWM[PRESET_COUNT][4] = {
    {255,  255,  255,  255}, // 00 on
    {  0,    0,    0,    0}, // 01 off
    {255,  255,  255,  255}, // 02 circle **5 6 7 8**
    { 82,   82,   82,   82}, // 03  grad ++
    {255,  255,  255,  255}, // 04 fade  **5 6 7 8**
    {255,  255,  255,  255}, // 05 fade  **5 6 7 8** jerome solo
    {255,  255,  255,  255}, // 06 str all 
    {  0,    0,    0,    0}, // 07 301 on 302 off
    {255,  255,  255,  255}, // 08 301 off 302 on
    {  0,    0,    0,    0}, // 09  off
    {  0,  255,  170,  126}, // 10  
    {255,  170,  126,   82}, // 11 
    {170,  126,   82,    0}, // 12 
    {126,   82,    0,  255}, // 13 
    { 82,    0,  255,  170}, // 14 
    {  0,    0,    0,    0}, // 15 BLACK stm leave lset mem
};
//{ pwm1, pwm2, pwm3, pwm4}
//{  5  ,  6  ,  7  , 8   } adr + -1

uint8_t MEM_PWM_NO_WIFI[4] = { LULU_MEMNOWIFI_MASTER,  LULU_MEMNOWIFI_MASTER,  LULU_MEMNOWIFI_MASTER,  LULU_MEMNOWIFI_MASTER};

#endif