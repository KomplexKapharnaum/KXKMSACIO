
#define L_NAME "Buzzer"

#define LULU_STRIP_SIZE 25             // 5 pour tester avec les jauges de monitoring
#define LULU_STRIP_TYPE LED_WS2812_V1 // Strip type

#define ARTNET_ENABLE 0

#include "macro/Type/buzzer/mem_buzzer.h"
#include "utils/K32_timer.h"

#define ATOM_LED 27
#define ATOM_BUZBTN 26
#define ATOM_SWITCH 22
#define ATOM_BUZLIGHT 32

bool stateB = false;
K32_timeout* timeout1;
K32_timeout* timeout2;
K32_timeout* timeout3;
K32_timeout* timeout4;
K32_timeout* timeout5;
K32_timeout* timeout6;
K32_timeout* timeout7;
K32_timeout* timeout8;

// CHANNEL 1: ACCUEIL
//
void channel_1() 
{   
    // Door CLOSED -> start
    k32->on("btn/switch-on", [](Orderz *order) { 
        stateB = false;
        k32->emit("btn/buzzer-on");
    });

    // Buzzer PRESSED
    k32->on("btn/buzzer-on", [](Orderz *order) { 
        if (!mqtt) return;

        // Cancel Timeout
        if (timeout1) timeout1->cancel();
        if (timeout2) timeout2->cancel();
        if (timeout3) timeout3->cancel();
        if (timeout4) timeout4->cancel();
        if (timeout5) timeout5->cancel();
        if (timeout6) timeout6->cancel();
        if (timeout7) timeout7->cancel();
        if (timeout8) timeout8->cancel();
        
        // START
        if (!stateB) {
            
            // STEP 1 INTRO MANIF
            mqtt->publishToChannel("event/start");
            mqtt->publishToChannel("event/relayOFF");
            mqtt->publishToChannel("leds/mem", "1");
            mqtt->publish("rpi/india/play", "1_*");
            
            // STEP 2 GYRO
            if (timeout1) delete timeout1;
            timeout1 = new K32_timeout(5000, []() {
                mqtt->publishToChannel("leds/mem", "2");
                mqtt->publishToChannel("event/relayON");
            });

            // STEP 3 ITW
            if (timeout2) delete timeout2;
            timeout2 = new K32_timeout(15000, []() {
                mqtt->publishToChannel("leds/mem", "3");
                mqtt->publishToChannel("event/relayOFF");
            });

            // STEP 4 RUBIS
            if (timeout3) delete timeout3;
            timeout3 = new K32_timeout(30000, []() {
                mqtt->publishToChannel("leds/mem", "4");
                mqtt->publishToChannel("event/relayON");
            });

            // STEP 5 ITW
            if (timeout4) delete timeout4;
            timeout4 = new K32_timeout(40000, []() {
                mqtt->publishToChannel("leds/mem", "5");
                mqtt->publishToChannel("event/relayOFF");
            });

             // STEP 6 POLICE
            if (timeout5) delete timeout5;
            timeout5 = new K32_timeout(55000, []() {
                mqtt->publishToChannel("leds/mem", "6");

            });

             // STEP 7 ITW
            if (timeout6) delete timeout6;
            timeout6 = new K32_timeout(65000, []() {
                mqtt->publishToChannel("leds/mem", "7");

            });

             // STEP 8 SORTIE
            if (timeout7) delete timeout7;
            timeout7 = new K32_timeout(80000, []() {
                mqtt->publishToChannel("leds/mem", "8");

            });

             // STEP 9 => STOP
            if (timeout8) delete timeout8;
            timeout8 = new K32_timeout(90000, []() {
                k32->emit("btn/buzzer-on");
                mqtt->publishToChannel("leds/mem", "0");
            });

        }

        // STOP
        else {
            mqtt->publishToChannel("event/stop");
            mqtt->publishToChannel("event/relayOFF");
            mqtt->publishToChannel("leds/mem", "0");
            mqtt->publish("rpi/lima/stop");
        }
    });

    // START / STOP
    k32->on("event/start", [](Orderz *order) { stateB = true; });
    k32->on("event/stop", [](Orderz *order) { stateB = false; });

}

// REPOS
//
void channel_2() 
{   
    // Door CLOSED -> start
    k32->on("btn/switch-on", [](Orderz *order) { 
        stateB = false;
        k32->emit("btn/buzzer-on");
    });

    // Buzzer PRESSED
    k32->on("btn/buzzer-on", [](Orderz *order) { 
        if (!mqtt) return;

        // Cancel Timeout
        if (timeout1) timeout1->cancel();
        if (timeout2) timeout2->cancel();
        if (timeout3) timeout3->cancel();
        if (timeout4) timeout4->cancel();

        
        // START
        if (!stateB) {
            
            // STEP 1
            mqtt->publishToChannel("event/start");
            mqtt->publishToChannel("leds/mem", "1");
            mqtt->publish("rpi/oscar/play", "1_*");

            // STEP 2
            if (timeout1) delete timeout1;
            timeout1 = new K32_timeout(2000, []() {
                mqtt->publishToChannel("leds/mem", "2");
            });

            // STEP 3
            if (timeout2) delete timeout2;
            timeout2 = new K32_timeout(4000, []() {
                mqtt->publishToChannel("leds/mem", "3");
            });

            // STEP 4
            if (timeout3) delete timeout3;
            timeout3 = new K32_timeout(6000, []() {
                mqtt->publishToChannel("leds/mem", "4");
            });

            // STEP 5 => STOP
            if (timeout4) delete timeout4;
            timeout4 = new K32_timeout(8000, []() {
                k32->emit("btn/buzzer-on");
            });

        }

        // STOP
        else {
            mqtt->publishToChannel("event/stop");
            mqtt->publishToChannel("leds/mem", "0");
            mqtt->publish("rpi/oscar/stop");
        }
    });

    // START / STOP
    k32->on("event/start", [](Orderz *order) { stateB = true; });
    k32->on("event/stop", [](Orderz *order) { stateB = false; });

}



// SETUP COMMON
//
void setup_device() 
{
    // LED DOT fixtures (internal LEDS)
    K32_fixture *dot = new K32_ledstrip(0, ATOM_LED, LED_WS2812_V1, LULU_STRIP_SIZE);
    light->addFixture(dot);

    // ANIM DOT - presets
    light->anim("mem-strip", new Anim_dmx_strip, LULU_STRIP_SIZE)
        ->drawTo(dot)
        ->bank(new BankSK)
        ->remote(true)
        ->play()
        ->mem(0);

    // BUZZER LIGHT PWM
    pwm->attach(ATOM_BUZLIGHT);
    K32_fixture *dimmer = new K32_pwmfixture(pwm);
    light->addFixture(dimmer);

    // ANIM pwm - presets
    light->anim("mem-pwm", new Anim_datathru, PWM_N_CHAN)
        ->drawTo(dimmer)
        ->bank(new BankPWM)
        ->remote(true)
        ->play()
        ->mem(0);
    
    // MACRO
    remote->setMacroMax(light->anim("mem-strip")->bank()->size());
    k32->on("remote/macro", [](Orderz *order)
    {
        light->anim("mem-strip")->mem( order->getData(0)->toInt() );
        light->anim("mem-pwm"  )->mem( order->getData(0)->toInt() );
    });

    // BUZZER BTN
    buttons->add(ATOM_BUZBTN, "buzzer");
    buttons->add(ATOM_SWITCH, "switch");

    // ATOM BTN -> re-map as BUZZER
    k32->on("btn/atom-on", [](Orderz *order) { k32->emit("btn/buzzer-on"); });
    k32->on("btn/atom-off", [](Orderz *order) { k32->emit("btn/buzzer-off"); });


    // SCENARII
    if (k32->system->channel() == 1) channel_1();
    if (k32->system->channel() == 2) channel_2();

}







