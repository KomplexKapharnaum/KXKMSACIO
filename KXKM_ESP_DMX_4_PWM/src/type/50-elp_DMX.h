
#define L_NAME "elp_DMX"

#define ELP_PIXELS 50

#define DMXOUT_ADDR 20
#define DMXFIXTURE_PATCHSIZE ELP_PIXELS

#define ARTNET_ENABLE 1

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
        ->push(0);


    // ANIM leds - artnet
    light->anim("artnet-elp", new Anim_dmx_strip, LULU_STRIP_SIZE)
        ->drawTo(elp)
        ->play();

    // ARTNET: subscribe dmx frame
    int memSize = light->anim("mem-elp")->bank()->preset_size();

    artnet->onDmx( {
        .address    = (1 + (light->id() - 1) * memSize), 
        .framesize  = memSize, 
        .callback   = [](const uint8_t *data, int length) 
            { 
                light->anim("artnet-elp")->push(data, length);
            }
        });


    //
    // REMOTE
    //

    remote->setMacroMax(light->anim("mem-elp")->bank()->size());

    // Bind macro change to Animation mem
    k32->on("remote/macro", [](Orderz *order)
        {
            light->anim("mem-elp")->mem(order->getData(0)->toInt());
            remote->setState(REMOTE_MANU); 
            LOGF("mem-elp: %d\n", order->getData(0)->toInt());
        });

    k32->on("remote/state", [](Orderz* order){

        remoteState stateR = (remoteState) order->getData(0)->toInt();

        // AUTO
        if (stateR == REMOTE_AUTO)
        {
            light->anim("mem-elp")->stop();
            light->anim("artnet-elp")->play();
            LOG("REMOTE: -> Mode AUTO");
        }

        // MANU
        else if (stateR == REMOTE_MANU || stateR == REMOTE_MANU_LAMP || stateR == REMOTE_MANU_STM)
        {
            light->anim("artnet-elp")->stop();
            light->anim("mem-elp")->play();
            LOG("REMOTE: -> Mode MANU");
        }
    });

    
}