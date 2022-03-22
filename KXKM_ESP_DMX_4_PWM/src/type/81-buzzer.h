
#define L_NAME "Buzzer"

#define LULU_STRIP_SIZE 25            // 5 pour tester avec les jauges de monitoring

#define ARTNET_ENABLE 0

#include "macro/Show/parlement/mem_sk_parlement.h"


void setup_device() 
{

    // LED MATRIX fixtures
    K32_fixture *matrix = new K32_ledstrip(0, LEDS_PIN[k32->system->hw()][0], LED_WS2812_V1, LULU_STRIP_SIZE);
    light->addFixture(matrix);

    // INIT TEST LED MATRIX
    light->anim("test-strip", new Anim_test_strip, LULU_STRIP_SIZE)
        ->drawTo(matrix)
        ->push(300)->master(LULU_PREV_MASTER)
        ->play()->wait();

    // ANIM matrix - presets
    light->anim("mem-strip", new Anim_dmx_strip, LULU_STRIP_SIZE)
        ->drawTo(matrix)
        ->bank(new BankSK)
        ->remote(true)
        ->play();
    
    // MACRO
    remote->setMacroMax(light->anim("mem-strip")->bank()->size());
    k32->on("remote/macro", [](Orderz *order)
    {
        light->anim("mem-strip")->mem( order->getData(0)->toInt() )->play();
    });

    // BTN
    k32->on("atom/btn-click", [](Orderz* order){
        mqtt->publish("k32/event/buzz", String(light->id()).c_str() );
    });

}




