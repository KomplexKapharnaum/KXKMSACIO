#ifndef mem_pwm_baro_132_h
#define mem_pwm_baro_132_h

#ifndef NUMBER_OF_MEM
#define NUMBER_OF_MEM 16 // stm leave in last mem
#endif

// 
// MEM ANIMATOR DATA ! modulateur relatif a la valeur du tableau
//
uint8_t MEM_PWM[NUMBER_OF_MEM][4] = {
    {255,  255,  255,  255}, // 00 on
    {170,  170,  170,  170}, // 01 grad
    {126,  126,  126,  126}, // 02 grad +
    { 82,   82,   82,   82}, // 03  grad ++
    {255,  255,  255,  255}, // 04 fade  **5 6 7 8**
    {  0,    0,    0,    0}, // 05 fade  **5 6 7 8** jerome solo
    {255,  255,  255,  255}, // 06 str all 
    {  0,    0,    0,    0}, // 07 301 on 302 off
    {255,  255,  255,  255}, // 08 301 off 302 on
    {  0,    0,    0,    0}, // 09  off
    {  0,    0,    0,    0}, // 10  all cube
    {  0,    0,    0,    0}, // 11  cube imp
    {  0,    0,    0,    0}, // 12  cube pair
    {255,  255,  255,  255}, // 13  all table
    {255,  255,  255,  255}, // 14  table pair
    {  0,    0,    0,    0}, // 15  table imp
    {  0,    0,    0,    0}, // 16 BLACK stm leave lset mem
};
//{ pwm1, pwm2, pwm3, pwm4}
//{  5  ,  6  ,  7  , 8   } adr + -1

uint8_t MEM_PWM_NO_WIFI[4] = { ON_NO_WIFI,  ON_NO_WIFI,  ON_NO_WIFI,  ON_NO_WIFI};

#endif