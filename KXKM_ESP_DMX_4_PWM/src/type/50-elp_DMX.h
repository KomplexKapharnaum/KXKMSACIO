
#define L_NAME "elp_DMX"
#define LULU_STRIP_SIZE 50
#define LULU_STRIP_TYPE LED_WS2812_V1 // Strip type
#define DMXOUT_ADDR 20
#define DMXFIXTURE_PATCHSIZE LULU_STRIP_SIZE

#define STROBE_N 4
#define STROBE_PATCHSIZE 17

#define ARTNET_ENABLE 0

#include "macro/Type/SK/mem_sk.h" // defo

void init_lights()
{
    //
    // FIXTURES
    //

    // LED STRIPS fixtures
    K32_fixture *strips[LED_N_STRIPS] = {nullptr};
    for (int k = 0; k < LED_N_STRIPS; k++)
        strips[k] = new K32_ledstrip(k, LEDS_PIN[k32->system->hw()][k], (led_types)LULU_STRIP_TYPE, LULU_STRIP_SIZE + 30);

    K32_fixture *elp = {nullptr};
    elp = new K32_dmxfixture(dmx, DMXOUT_ADDR, LULU_STRIP_SIZE * 3);
    light->addFixture(elp); 
    light->copyFixture({strips[0], 0, LULU_STRIP_SIZE, elp, 0});
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
