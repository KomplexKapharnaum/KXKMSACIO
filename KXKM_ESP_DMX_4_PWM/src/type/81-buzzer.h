
#define L_NAME "Buzzer"

#define LULU_STRIP_SIZE 1             // 5 pour tester avec les jauges de monitoring
#define LULU_STRIP_TYPE LED_WS2812_V1 // Strip type

#define ARTNET_ENABLE 0

#include "macro/Show/parlement/mem_sk_parlement.h"
#include "macro/Show/parlement/mem_pwm_buzzer.h"


void setup_device() 
{

    // LED DOT fixtures
    K32_fixture *dot = new K32_ledstrip(0, LEDS_PIN[k32->system->hw()][0], LED_WS2812_V1, LULU_STRIP_SIZE);
    light->addFixture(dot);

    // BUZZER LIGHT PWM
    K32_fixture *dimmer = new K32_pwmfixture(pwm);
    light->addFixture(dimmer);

    // INIT TEST LED DOT
    light->anim("test-strip", new Anim_test_strip, LULU_STRIP_SIZE)
        ->drawTo(dot)
        ->push(300)->master(LULU_PREV_MASTER)
        ->play()->wait();

    // ANIM DOT - presets
    light->anim("mem-strip", new Anim_dmx_strip, LULU_STRIP_SIZE)
        ->drawTo(dot)
        ->bank(new BankSK)
        ->remote(true)
        ->play();

    // ANIM pwm - presets
    light->anim("mem-pwm", new Anim_datathru, PWM_N_CHAN)
        ->drawTo(dimmer)
        ->bank(new BankPWM)
        ->remote(true)
        ->mem(-1);
    
    // MACRO
    remote->setMacroMax(light->anim("mem-strip")->bank()->size());
    k32->on("remote/macro", [](Orderz *order)
    {
        light->anim("mem-strip")->mem( order->getData(0)->toInt() )->play();
        light->anim("mem-pwm"  )->mem( order->getData(0)->toInt() )->play();
    });

    // BTN
    buttons->add(26, "buzzer");
    k32->on("btn/buzzer", [](Orderz* order){
        if (mqtt) mqtt->publish("k32/event/buzz", String(light->id()).c_str() );
    });
    k32->on("btn/atom", [](Orderz* order){
        if (mqtt) mqtt->publish("k32/event/buzz", String(light->id()).c_str() );
    });

}




