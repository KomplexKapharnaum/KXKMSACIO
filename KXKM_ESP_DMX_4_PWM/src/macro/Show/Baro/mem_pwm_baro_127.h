#ifndef mem_pwm_baro_127_h
#define mem_pwm_baro_127_h

#ifndef NUMBER_OF_MEM
#define NUMBER_OF_MEM 16 // stm leave in last mem
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
    {255,  255,  255,  255}, // 05  fade  **5 6 7 8**
    {255,  255,  255,  255}, // 06 str all 
    {255,  255,  255,  255}, // 07 301 on 302 off
    {  0,    0,    0,    0}, // 08 301 off 302 on
    {255,  255,  255,  255}, // 09  on solo
    {  0,  255,  170,  126}, // 10  
    {255,  170,  126,   82}, // 11 
    {170,  126,   82,    0}, // 12 
    {126,   82,    0,  255}, // 13 
    { 82,    0,  255,  170}, // 14 
    {  0,    0,    0,    0}, // 15 BLACK stm leave lset mem
};
//{ pwm1, pwm2, pwm3, pwm4}
//{  5  ,  6  ,  7  , 8   } adr + -1

uint8_t MEM_PWM_NO_WIFI[4] = {ON_NO_WIFI,  ON_NO_WIFI,  ON_NO_WIFI,  ON_NO_WIFI};



#endif