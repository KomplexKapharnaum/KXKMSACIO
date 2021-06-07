#ifndef mem_pwm_baro_127_h
#define mem_pwm_baro_127_h

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
    {255,  255,  255,  255}, // 05  fade  **5 6 7 8**
    {255,  255,  255,  255}, // 06 str all 
    {255,  255,  255,  255}, // 07 301 on 302 off
    {  0,    0,    0,    0}, // 08 301 off 302 on
    {255,  255,  255,  255}, // 09  on solo  
    {255,  255,  255,  255}, // 10  all cube
    {255,  255,  255,  255}, // 11  cube imp
    {  0,    0,    0,    0}, // 12  cube pair
    {  0,    0,    0,    0}, // 13  all table
    {  0,    0,    0,    0}, // 14  table pair
    {  0,    0,    0,    0}, // 15  table imp
    {  0,    0,    0,    0}, // 16 BLACK stm leave lset mem
};
//{ pwm1, pwm2, pwm3, pwm4}
//{  5  ,  6  ,  7  , 8   } adr + -1

uint8_t MEM_PWM_NO_WIFI[4] = {ON_NO_WIFI,  ON_NO_WIFI,  ON_NO_WIFI,  ON_NO_WIFI};



#endif