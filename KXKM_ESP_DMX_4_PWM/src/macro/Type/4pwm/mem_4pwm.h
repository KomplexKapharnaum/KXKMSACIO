#ifndef mem_4pwm_h
#define mem_4pwm_h

#ifndef NUMBER_OF_MEM
#define NUMBER_OF_MEM 24 // stm leave in last mem
#endif

// 
// MEM ANIMATOR DATA ! modulateur relatif a la valeur du tableau
//
uint8_t MEM_PWM[NUMBER_OF_MEM][4] = {
    {  255,  255,  255,  255}, // 00 
    {  170,  170,  170,  170}, // 01 
    {  126,  126,  126,  126}, // 02 
    {   82,   82,   82,   82}, // 03 
    {  255,  255,  255,  255}, // 04 **
    {    0,    0,    0,    0}, // 05 
    {  255,  170,  126,   82}, // 06 
    {  170,  126,   82,    0}, // 07 
    {  126,   82,    0,  255}, // 08 
    {   82,    0,  255,  170}, // 09 
    {    0,  255,  170,  126}, // 10 
    {  170,  126,   82,    0}, // 12 
    {  255,  170,  126,   82}, // 11 
    {  126,   82,    0,  255}, // 13 
    {   82,    0,  255,  170}, // 14 
    {    0,    0,    0,    0}, // 15 BLACK
    {    0,    0,    0,    0}, // 16 BLACK
    {    0,    0,    0,    0}, // 17 BLACK
    {    0,    0,    0,    0}, // 18 BLACK
    {    0,    0,    0,    0}, // 19 BLACK
    {    0,    0,    0,    0}, // 20 BLACK
    {    0,    0,    0,    0}, // 21 BLACK
    {    0,    0,    0,    0}, // 22 BLACK
    {    0,    0,    0,    0}, // 23 BLACK stm leave lset mem
};
//  { pwm1, pwm2, pwm3, pwm4}
//{  5  ,  6  ,  7  , 8   } adr + -1

uint8_t MEM_PWM_NO_WIFI[4] = { LULU_MEMNOWIFI_MASTER,  LULU_MEMNOWIFI_MASTER,  LULU_MEMNOWIFI_MASTER,  LULU_MEMNOWIFI_MASTER};

#endif