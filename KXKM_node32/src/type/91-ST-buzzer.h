
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

#define CHANNEL1_NMEDIA 3
#define CHANNEL2_NMEDIA 1

int mediaIndex = 0;

int stateB = 0;
K32_timeout* timeout0 = nullptr;
K32_timeout* timeout1 = nullptr;
K32_timeout* timeout2 = nullptr;
K32_timeout* timeout3 = nullptr;
K32_timeout* timeout4 = nullptr;
K32_timeout* timeout5 = nullptr;
K32_timeout* timeout6 = nullptr;
K32_timeout* timeout7 = nullptr;
K32_timeout* timeout8 = nullptr;



// CHANNEL 1: ACCUEIL
//
void channel_1() 
{   
    // ATOM direct ON/OFF
    k32->on("btn/atom-on", [](Orderz *order) { 
        if (stateB == 1) stateB = 2;
        else if (stateB > 1) stateB = 0;
        k32->emit("btn/buzzer-on"); 
    });

    // Door CLOSED -> start
    k32->on("btn/switch-long", [](Orderz *order) { 
        if (stateB == 0) k32->emit("btn/buzzer-on");
    });

    // Door CLOSED -> start after 1000
    k32->on("btn/switch-on", [](Orderz *order) { 
        if (timeout0) {
            timeout0->cancel();
            delete timeout0;
            timeout0 = nullptr;
        }
    });

    // Door OPEN -> stop after 1000
    k32->on("btn/switch-off", [](Orderz *order) 
    { 
        if (timeout0) {
            timeout0->cancel();
            delete timeout0;
        }
        timeout0 = new K32_timeout(1000, []() {
            stateB = 3; 
            k32->emit("btn/buzzer-on");
        });
    });

    // Buzzer PRESSED
    k32->on("btn/buzzer-on", [](Orderz *order) { 
        if (!mqtt) return;

        // Cancel Timeout
        if (timeout0) timeout0->cancel();
        if (timeout1) timeout1->cancel();
        if (timeout2) timeout2->cancel();
        if (timeout3) timeout3->cancel();
        if (timeout4) timeout4->cancel();
        if (timeout5) timeout5->cancel();
        if (timeout6) timeout6->cancel();
        if (timeout7) timeout7->cancel();
        if (timeout8) timeout8->cancel();

        // START
        if (stateB == 0) {
            
            mediaIndex = (mediaIndex + 1) % CHANNEL1_NMEDIA;

            // STEP 1 INTRO MANIF
            stateB = 1;
            mqtt->publishToChannel("event/relayOFF");
            mqtt->publishToChannel("leds/mem", "1");
            mqtt->publish("rpi/india/play", (String(mediaIndex+1)+"_*").c_str());
            
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
                stateB = 2;
                k32->emit("btn/buzzer-on");
            });

        }

        // STOP
        if (stateB >= 2) {
            mqtt->publishToChannel("event/relayOFF");
            mqtt->publishToChannel("leds/mem", "0");
            mqtt->publish("rpi/india/stop");
            if (stateB == 3) stateB = 0; // Re-ARM for next door close
        }

        LOG(stateB);
    });

}

// REPOS
//
void channel_2() 
{   
    // Door CLOSED -> stop
    k32->on("btn/switch-on", [](Orderz *order) { 
        stateB = true;
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
            
            mediaIndex = (mediaIndex + 1) % CHANNEL2_NMEDIA;

            // STEP 1
            mqtt->publishToChannel("event/start");
            mqtt->publishToChannel("leds/mem", "1");
            mqtt->publish("rpi/oscar/play", (String(mediaIndex+1)+"_*").c_str());

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


    // SCENARII
    if (k32->system->channel() == 1) channel_1();
    if (k32->system->channel() == 2) channel_2();

}







