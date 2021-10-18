
#define L_NAME "Sac"

#define LULU_STRIP_SIZE     25              //120 // FIX
#define LULU_STRIP_TYPE     LED_WS2812_V1   //LED_SK6812W_V1       // FIX                // Strip type

#define PWR_FAKE_CURRENT    12500

#include "macro/Type/4pwm/mem_4pwm.h"
#include "macro/Type/SK/mem_sk_1.h"

#include <fixtures/K32_ledstrip.h>
K32_fixture* strips[LED_N_STRIPS] = {nullptr};

#include <fixtures/K32_pwmfixture.h>
K32_fixture* dimmer = nullptr;

 
void init_lights() 
{

    //
    // PWM
    //

    // PWM fixture
    dimmer = new K32_pwmfixture(pwm);
    light->addFixture( dimmer );
    
    // ANIM pwm - artnet
    light->anim("artnet-pwm", new Anim_datathru, PWM_N_CHAN)
        ->drawTo(dimmer);

    // ANIM pwm - presets
    light->anim("mem-pwm", new Anim_datathru, PWM_N_CHAN)
        ->drawTo(dimmer);


    //
    // STRIPS 
    //

    // LED STRIPS fixtures
    for(int k=0; k<LED_N_STRIPS; k++)
        strips[k] = new K32_ledstrip(k, LEDS_PIN[k32->system->hw()][k], (led_types)LULU_STRIP_TYPE, LULU_STRIP_SIZE + 30);    
    light->addFixtures( strips, LED_N_STRIPS )
         ->copyFixture({strips[0], LULU_STRIP_SIZE, LULU_STRIP_SIZE + 18, strips[1], 0}); // jauge sortie 2

    // TEST Sequence
        // INIT TEST STRIPS
            light->anim( "test-strip", new Anim_test_strip, LULU_STRIP_SIZE )
                ->drawTo(strips, LED_N_STRIPS)
                ->push(300)
                ->master(LULU_PREV_MASTER)
                ->play();

        // PWM TEST
            light->anim( "test-pwm", new Anim_test_pwm, LULU_STRIP_SIZE )
                ->drawTo(dimmer)
                ->push(300)
                ->master(LULU_PREV_MASTER)
                ->play();

        // WAIT END
            light->anim("test-strip")->wait();
            light->anim("test-pwm")->wait();


    // ANIM leds - artnet
    light->anim("artnet-strip", new Anim_dmx_strip, LULU_STRIP_SIZE)
        ->drawTo(strips[0])
        ->play();

    // ANIM leds - presets
    light->anim("mem-strip", new Anim_dmx_strip, LULU_STRIP_SIZE)
        ->drawTo(strips[0])
        ->bank(new BankSK)
        ->mem(-1);
    remote->setMacroMax( light->anim("mem-strip")->bank()->size() );


    // ANIM leds - presets preview
    light->anim("memprev-strip", new Anim_preview, LULU_PREV_SIZE, LULU_STRIP_SIZE + 8)
        ->drawTo(strips[0])
        //->bank(new BankSK_PREV)   // TODO
        ->mem(-1)
        ->master(LULU_PREV_MASTER)
        ->play();


    // ANIM leds - monitoring
    light->anim("battery-strip", new Anim_battery, 4, LULU_STRIP_SIZE + 1)
        ->drawTo(strips[0])
        ->master(LULU_PREV_MASTER)
        ->play();

    light->anim("remote-strip", new Anim_remote, LULU_PREV_SIZE + 4, LULU_STRIP_SIZE + 6)
        ->drawTo(strips[0])
        ->master(LULU_PREV_MASTER)
        ->play();

    light->anim("rssi-strip", new Anim_rssi, 1, LULU_STRIP_SIZE + 17)
        ->drawTo(strips[0])
        ->master(LULU_PREV_MASTER * 1.5)
        ->play();
    

    

}


#ifdef zzzzz

// // MEM ON BOOT
    #if (LULU_TYPE >= 20 || LULU_TYPE == 2 || LULU_TYPE == 6)
        // light->anim("artnet-strip")->push(MEM_NO_WIFI, LULU_PATCHSIZE);// settings set
        // light->anim("artnet-strip")->mod(new K32_mod_sinus)->at(2)->period(8500)->phase(0)->mini(-255)->maxi(255); // modulo
        // light->anim("artnet-strip")->push( MEM_SK[20], LULU_PATCHSIZE); // baro auto circulation elp
        // light->anim("artnet-strip")->mod(new K32_mod_sinus)->at(7)->period(8500)->mini(0)->maxi(45);// baro auto circulation elp
    #endif


// // ANIM dmx fixtures  - artnet
    light->anim("artnet-dmxfix", new Anim_datathru , DMXFIXTURE_PATCHSIZE / 4)->play();
    for (int k=0; k<DMX_N_FIXTURES; k++)
        if (dmxfixs[k]) light->anim("artnet-dmxfix")->attach(dmxfixs[k]);

    // ANIM dmx fixtures  - presets
    light->anim("mem-dmxfix", new Anim_datathru , DMXFIXTURE_PATCHSIZE / 4)
        ->bank(new BankSK)
        ->mem(-1)
        ->play();
    for (int k=0; k<DMX_N_FIXTURES; k++)
        if (dmxfixs[k]) light->anim("mem-dmxfix")->drawTo(dmxfixs[k]);



#include <fixtures/K32_dmxfixture.h>
K32_dmxfixture* dmxfixs[DMX_N_FIXTURES] = {nullptr};



//      CHARIOT             FLUO
    #if LULU_TYPE == 9 || LULU_TYPE == 40
        light->copyFixture({strips[0], 0, LULU_STRIP_SIZE, strips[1], 0}); // Clone

    //      STROBEDMX           PARDMX                                        
    #elif LULU_TYPE == 11 || LULU_TYPE == 12
        dmxfixs[0] = new K32_dmxfixture(dmx, DMXOUT_ADDR, DMXFIXTURE_PATCHSIZE);

    // ELP
    #elif LULU_TYPE == 50
        dmxfixs[0] = new K32_dmxfixture(dmx, DMXOUT_ADDR, DMXFIXTURE_PATCHSIZE);
        light->copyFixture({strips[0], 0, LULU_STRIP_SIZE, elp, 0});

    // LYRE
    #elif LULU_TYPE == 60
        int DMX_address = (1 + (LULU_id - 1) * 32);  // DMX Offset = 32  =>  Lyre 1 addr=1 / Lyre 2 addr=33 / ...
        dmxfixs[0] = new K32_dmxfixture(dmx, DMX_address, DMXFIXTURE_PATCHSIZE);

    // OTHERS
    #else
        light->copyFixture({strips[0], LULU_STRIP_SIZE, LULU_STRIP_SIZE + 18, strips[1], 0}); // jauge sortie 2
        
    #endif

    // REGISTER dmxfixtures
    for (int k=0; k<DMX_N_FIXTURES; k++)
        if (dmxfixs[k]) light->addFixture(dmxfixs[k]);



    


#endif