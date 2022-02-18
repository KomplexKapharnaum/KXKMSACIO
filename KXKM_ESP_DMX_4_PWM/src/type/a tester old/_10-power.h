
#define L_NAME "Power"

#include "macro/Type/SK/mem_sk.h"     // defo


#define LULU_STRIP_SIZE     120                                  
#define LULU_STRIP_TYPE     LED_SK6812W_V1                      // Strip type
#define LULU_PATCHSIZE      SK_PRESET_SIZE                      // Total size of Preset


// 
// MEM ANIMATOR DATA ! modulateur relatif a la valeur du tableau
//
uint8_t MEM[PRESET_COUNT][LULU_PATCHSIZE] = {};
uint8_t MEM_NO_WIFI[LULU_PATCHSIZE] = {};


void init_mem()
{
  for (int n = 0 ; n < PRESET_COUNT ; n++)
   {
      for (int i = 0 ; i < SK_PRESET_SIZE ; i++) 
      {
           MEM[n][i] = MEM_SK[n][i];
           MEM_NO_WIFI[i] = MEM_SK_NO_WIFI[i];
      }
   }
}


// 
// APPLY MACRO WITH CUSTOM MODULATORS INTO anim
//
void load_mem(K32_anim *anim, int macro) {

    // remove disposable modulators
    //
    anim->unmod();

    // push new data
    //
    anim->push(MEM[macro], LULU_PATCHSIZE);

    // add modulators
    //
    if (macro == 2)
    {
        anim->mod(new K32_mod_sinus)->at(0)->period(8500)->mini(38)->maxi(217);
    }
    else if (macro == 3)
    {
        anim->mod(new K32_mod_sinus)->at(0)->period(4800)->mini(38)->maxi(217);
    }
    else if (macro == 9)
    {
        anim->mod(new K32_mod_sawtooth)->at(9)->mini(229)->maxi(238)->period(3700);
    }
    else if (macro == 10)
    {
        anim->mod(new K32_mod_sawtooth)->at(7)->period(7000);
    }
    else if (macro == 11)
    {
        anim->mod(new K32_mod_pulse)->at(1)->at(2)->at(4)->param(1, 66)->period(7000);
        anim->mod(new K32_mod_pulse)->at(8)              ->param(1, 66)->period(7000);
    }
    else if (macro == 14)
    {
        anim->mod(new K32_mod_sinus)->at(0)->period(8500)->mini(38)->maxi(217);
    }
}

