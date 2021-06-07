#ifndef mem_sucette_baro_132_h
#define mem_sucette_baro_132_h

#ifndef NUMBER_OF_MEM
#define NUMBER_OF_MEM 16 // stm leave in last mem
#endif

// 
// MEM ANIMATOR DATA ! modulateur relatif a la valeur du tableau
//
uint8_t MEM[NUMBER_OF_MEM][LULU_PATCHSIZE] = {0};
uint8_t MEM_NO_WIFI[LULU_PATCHSIZE] = {};

void init_mem()
{
  for (int n = 0 ; n < NUMBER_OF_MEM ; n++)
   {
    //   for (int i = 0 ; i < LULU_PATCHSIZE -4 ; i++) 
    //   {
    //        MEM[n][i] = MEM_PARLED[n][i];
    //        MEM_NO_WIFI[i] = MEM_PARLED_NO_WIFI[i];
    //   }
      for (int i = LULU_PATCHSIZE -4 ; i < LULU_PATCHSIZE  ; i++) 
      {
           MEM[n][i]=MEM_PWM[n][i - (LULU_PATCHSIZE - 4)];
           MEM_NO_WIFI[i] = MEM_PWM_NO_WIFI[i - (LULU_PATCHSIZE-4)];
      }
   }
}

// 
// PREVIEW PIXEL MAP
//
uint8_t MEM_PREV[NUMBER_OF_MEM][LULU_PREVPIX*4] = {
    {1, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0},    // 00 red
    {0, 1, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0},    // 01 Green
    {0, 0, 1, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0},    // 02 Blue
    {0, 0, 0, 1,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0},    // 03 White
    {1, 0, 0, 0,  0, 1, 0, 0,  0, 0, 1, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0},    // 04 fade  **5 6 7 8**
    {0, 0, 0, 1,  0, 0, 0, 1,  0, 0, 0, 1,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0},    // 05 fade  **5 6 7 8** jerome solo
    {0, 0, 0, 1,  0, 0, 0, 1,  0, 0, 0, 1,  0, 0, 0, 1,  0, 0, 0, 0,  0, 0, 0, 0},    // 06 str all 67
    {0, 0, 0, 1,  0, 0, 0, 1,  0, 0, 0, 1,  0, 0, 0, 1,  0, 0, 0, 1,  0, 0, 0, 0},    // 07 str all 42
    {0, 0, 0, 0,  0, 0, 0, 1,  0, 0, 0, 1,  0, 0, 0, 0,  0, 0, 0, 1,  0, 0, 0, 1},    // 08 str all lent
    {0, 0, 0, 1,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 1},    // 09 circule w **9** 20>255
    {0, 0, 0, 1,  0, 0, 0, 1,  0, 0, 1, 0,  0, 0, 1, 0,  0, 0, 0, 0,  0, 0, 0, 0},    // 10 circus w b
    {0, 0, 1, 0,  0, 0, 1, 0,  0, 0, 1, 0,  0, 0, 0, 1,  0, 0, 0, 1,  0, 0, 0, 1},    // 11 str w -> blue
    {0, 0, 1, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0},    // 12 blue all
    {0, 0, 1, 0,  0, 0, 0, 0,  0, 0, 1, 0,  0, 0, 0, 0,  0, 0, 1, 0,  0, 0, 0, 0},    // 13 blue parcielle
    {0, 0, 0, 0,  0, 0, 1, 0,  0, 0, 0, 0,  0, 0, 1, 0,  0, 0, 0, 0,  0, 0, 0, 0},    // 14 respi blue 
    {0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0},    // 15 BLACK stm leave last mem
};
//  {r1,g1,b1,w1, r2,g2,b2,w2, r3,g3,w3,w3, r4,g4,b4,w4, r5,g5,b5,w5, r6,g6,b6,w6},


// 
// APPLY MACRO WITH CUSTOM MODULATORS INTO anim
//
//{master , r  , g  , b  , str , pwm1, pwm2, pwm3, pwm4}
//{0      , 1  , 2  , 3  ,  4  ,  16  ,  17  ,  18  , 19   } adr + -1
void load_mem(K32_anim *anim, int macro) {

    // remove disposable modulators
    //
    anim->unmod();

    // push new data
    //
    anim->push(MEM[macro], LULU_PATCHSIZE);

    // add modulators
    //
    if (macro == 4)
    {
        anim->mod(new K32_mod_sinus)->at(16)->at(19)->at(18)->at(17)->period(8500)->phase(0)->mini(-50)->maxi(255);
    }
    else if (macro == 5)
    {
        anim->mod(new K32_mod_sinus)->at(16)->at(19)->at(18)->at(17)->period(8500)->phase(0)->mini(-50)->maxi(255);
    }
    else if (macro == 6)
    {
        anim->mod(new K32_mod_pulse)->at(18)->at(19)->at(17)->at(16)->param(1, 10)->period(500);
    }
  
}


#endif