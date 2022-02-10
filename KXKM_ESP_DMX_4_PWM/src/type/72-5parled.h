
#define L_NAME "5parled"

#define PAR_N            1
#define PAR_PATCHSIZE    25

#define ARTNET_ENABLE       0

  
#include "macro/Show/parlement/mem_parled.h"  

void init_lights()  
{
    //
    // FIXTURES 
    //

    // LED STRIPS fixtures
    K32_fixture* pars[PAR_N] = {nullptr};
    for(int k=0; k<PAR_N; k++)
        pars[k] = new K32_dmxfixture(dmx, 1+5*k, PAR_PATCHSIZE);  // Str 1 : 21 ,Str 2 : 38 ,Str 3 : 55 ,Str 4 : 72   
    light->addFixtures( pars, PAR_N );


    // 
    // ANIM
    //

    // ANIM pars 
    light->anim("mem-pars", new Anim_datathru, PAR_PATCHSIZE)
        ->drawTo(pars, PAR_N)
        ->bank(new BankPar)
        ->remote(true)
        ->push(0)
        ->play();
    
    //
    // REMOTE
    //

    remote->setMacroMax( light->anim("mem-pars")->bank()->size() );
    
    k32->on("remote/macro", [](Orderz* order){
        light->anim("mem-pars")->mem( order->getData(0)->toInt() );
        LOGF("mem-pars: %d\n", order->getData(0)->toInt());
    });


}








