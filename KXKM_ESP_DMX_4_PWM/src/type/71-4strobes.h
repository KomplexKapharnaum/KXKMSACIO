
#define L_NAME "4Strobes"

#define STROBE_N            4
#define STROBE_PATCHSIZE    17

#define ARTNET_ENABLE       0

#include "macro/Show/larochelle/mem_strobe.h"  

void init_lights()  
{
    //
    // FIXTURES 
    //

    // LED STRIPS fixtures
    K32_fixture* strobes[STROBE_N] = {nullptr};
    for(int k=0; k<STROBE_N; k++)
        strobes[k] = new K32_dmxfixture(dmx, 1+20*k, STROBE_PATCHSIZE);  // Str 1 : 21 ,Str 2 : 38 ,Str 3 : 55 ,Str 4 : 72   
    light->addFixtures( strobes, STROBE_N );


    // 
    // ANIM
    //

    // ANIM strobes 
    light->anim("mem-strobe", new Anim_datathru, STROBE_PATCHSIZE)
        ->drawTo(strobes, STROBE_N)
        ->bank(new BankStrobe)
        ->remote(true)
        ->push(0)
        ->play();
    
    //
    // REMOTE
    //

    remote->setMacroMax( light->anim("mem-strobe")->bank()->size() );
    
    k32->on("remote/macro", [](Orderz* order){
        light->anim("mem-strobe")->mem( order->getData(0)->toInt() );
        LOGF("mem-strobe: %d\n", order->getData(0)->toInt());
    });


}








