
#define L_NAME "elp_DMX"

#define ELP_PIXELS 50

#define DMXOUT_ADDR 20
#define DMXFIXTURE_PATCHSIZE ELP_PIXELS

#define ARTNET_ENABLE 0

#include "macro/Type/SK/mem_sk.h" // defo

void init_lights()
{
    //
    // FIXTURES
    //

    // ELP fixtures
    K32_fixture *elp = new K32_dmxfixture(dmx, DMXOUT_ADDR, ELP_PIXELS * 3, true);
    light->addFixture(elp);

    //
    // TEST Sequence
    //

    // INIT TEST STRIPS
    light->anim("test-elp", new Anim_test_strip, ELP_PIXELS)
        ->drawTo(elp)
        ->push(300)
        ->master(LULU_PREV_MASTER)
        ->play()
        ->wait(); // WAIT END

    
    //
    // ANIM
    //

    // ANIM elp
    light->anim("mem-elp", new Anim_dmx_strip, ELP_PIXELS)
        ->drawTo(elp)
        ->bank(new BankSK)
        ->remote(true)
        ->push(0)
        ->play();


    //
    // REMOTE
    //

    remote->setMacroMax(light->anim("mem-elp")->bank()->size());

    // Bind macro change to Animation mem
    k32->on("remote/macro", [](Orderz *order)
        {
            light->anim("mem-elp")->mem(order->getData(0)->toInt())->play();
            LOGF("mem-elp: %d\n", order->getData(0)->toInt());
        });

    
}
