#define L_NAME "Flex"

#include "macro/Type/4pwm/mem_4pwm.h" // defo
#include "macro/Type/SK/mem_sk.h"     // defo


#define LULU_STRIP_SIZE     186                                  
#define LULU_STRIP_TYPE     LED_SK6812W_V1                      // Strip type
#define LULU_PATCHSIZE      SK_PRESET_SIZE+PWM_PRESET_SIZE      // Total size of Preset


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
      for (int i = SK_PRESET_SIZE ; i < LULU_PATCHSIZE  ; i++) 
      {
           MEM[n][i]=MEM_PWM[n][i - SK_PRESET_SIZE];
           MEM_NO_WIFI[i] = MEM_PWM_NO_WIFI[i - SK_PRESET_SIZE];
      }
   }
}


// 
// APPLY MACRO WITH CUSTOM MODULATORS INTO anim
//
//{master , r  , g  , b  , w  ,pix mod , pix long , pix_pos , str_mod , str_speed , r_fond , g_fond , b_fond , w_fond , mirror_mod , zoom }
//{0      , 1  , 2  , 3  , 4  ,5       , 6        , 7       , 8       , 9         , 10     , 11     , 12     , 13     , 14         , 15   } adr + -1

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
        anim->mod(new K32_mod_sinus)->at(1)->at(5)->at(8)->at(3)->at(7)->at(2)->at(6)->period(8500)->phase(0)->mini(-50)->maxi(255);
    }
    else if (macro == 6)
    {
        anim->mod(new K32_mod_pulse)->at(1)->at(2)->at(3)->at(7)->at(8)->at(6)->at(5)->param(1, 10)->period(500);
    }
    else if (macro == 9)
    {
        anim->mod(new K32_mod_sinus)->at(0)->mini(100)->maxi(255)->period(2000);
    }
    else if (macro == 10)
    {
        anim->mod(new K32_mod_sinus)->at(1)->at(2)->period(8500)->phase(0)->mini(0)->maxi(255);
    }
    else if (macro == 11)
    {
        anim->mod(new K32_mod_pulse)->at(2)->at(3)->param(1, 100)->period(7000);
    }
    else if (macro == 12)
    {
        anim->mod(new K32_mod_sinus)->at(1)->period(8500)->phase(0)->mini(0)->maxi(255);
        anim->mod(new K32_mod_sinus)->at(2)->period(8500)->phase(120)->mini(0)->maxi(255);
        anim->mod(new K32_mod_sinus)->at(3)->period(8500)->phase(240)->mini(0)->maxi(255);
    }
    else if (macro == 14)
    {
        anim->mod(new K32_mod_sinus)->at(0)->period(8500)->mini(38)->maxi(217);
    }
}

