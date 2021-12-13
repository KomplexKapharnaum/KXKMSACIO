
#define L_NAME "elp_DMX"

#define LED_N_STRIPS    2
#define LULU_STRIP_SIZE 50
#define LULU_STRIP_TYPE LED_WS2812_V1 // Strip type

#define DMXOUT_ADDR 20
#define DMXFIXTURE_PATCHSIZE LULU_STRIP_SIZE

#define ARTNET_ENABLE 0

#include "macro/Type/SK/mem_sk.h" // defo

void init_lights()
{
    //
    // FIXTURES
    //

    // ELP fixtures
    K32_fixture *elp = new K32_dmxfixture(dmx, DMXOUT_ADDR, LULU_STRIP_SIZE * 3);


    //
    // TEST Sequence
    //

    // INIT TEST STRIPS
    light->anim("test-strip", new Anim_test_strip, LULU_STRIP_SIZE)
        ->drawTo(strips, LED_N_STRIPS)
        ->push(300)
        ->master(LULU_PREV_MASTER)
        ->play();

    // WAIT END
    light->anim("test-strip")->wait();

    //
    // ANIM
    //

    // ANIM elp
    light->anim("mem-strip", new Anim_dmx_strip, LULU_STRIP_SIZE)
        ->drawTo(strips[0])
        ->bank(new BankSK)
        ->remote(true)
        ->push(0)
        ->play();

    //
    // REMOTE
    //

    remote->setMacroMax(light->anim("mem-strip")->bank()->size());

    k32->on("remote/macro", [](Orderz *order)
            {
                light->anim("mem-strip")->mem(order->getData(0)->toInt());
                LOGF("mem-strip: %d\n", order->getData(0)->toInt());
            });
}
