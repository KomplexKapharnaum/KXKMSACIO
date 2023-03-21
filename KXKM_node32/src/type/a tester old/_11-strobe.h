#define L_NAME "Dmx_strobe"

#include "macro/Type/strobe/mem_strobe_dmx.h"   // mem global

#define LULU_STRIP_SIZE         0
#define LULU_PATCHSIZE          STROBE_PRESET_SIZE                      // Total size of Preset
#define DMXFIXTURE_PATCHSIZE    16


void init_mem() {}


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
    if (macro == 4)
    {
        anim->mod(new K32_mod_sinus)->at(3)->period(8500)->phase(0)->mini(0)->maxi(255);
        anim->mod(new K32_mod_sinus)->at(4)->period(8500)->phase(120)->mini(0)->maxi(255);
        anim->mod(new K32_mod_sinus)->at(5)->period(8500)->phase(240)->mini(0)->maxi(255);
    }
    else if (macro == 9)
    {
        anim->mod(new K32_mod_sinus)->at(9)->mini(100)->maxi(255)->period(2000);
    }
    else if (macro == 10)
    {
        anim->mod(new K32_mod_sawtooth)->at(7)->period(7000);
    }
    else if (macro == 11)
    {
        anim->mod(new K32_mod_pulse)->at(3)->at(4)->param(1, 100)->period(7000);
    }
    else if (macro == 12)
    {
        anim->mod(new K32_mod_sinus)->at(3)->period(8500)->phase(0)->mini(0)->maxi(255);
        anim->mod(new K32_mod_sinus)->at(4)->period(8500)->phase(120)->mini(0)->maxi(255);
        anim->mod(new K32_mod_sinus)->at(5)->period(8500)->phase(240)->mini(0)->maxi(255);
    }
    else if (macro == 14)
    {
        anim->mod(new K32_mod_sinus)->at(0)->period(8500)->mini(38)->maxi(217);
    }
}
