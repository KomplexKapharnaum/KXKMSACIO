#define L_NAME "Flex" // a tester


// #define PIXSIZE 65            // contact 60Led/M // defaut : 186
#define LULU_STRIP_TYPE LED_SK6812W_V3 // Strip type


// #define ARTNET_DMXNODE 1

// #define PWM_ON_OFF 1

#define PREVIEW 

// #include "macro/Type/SK/mem_sk.h" // defo
#include "macro/Show/kontact/mem_sk.h" // Kontact
// #include "macro/Show/larochelle/mem_sk_roch.h"
// #include "macro/Show/esch/mem_sk_esch.h"

#ifdef PWM_ON_OFF
#include "macro/Type/4pwm/mem_4pwm.h"
#endif

void setup_device()
{

    // .########.####.##.....##.########.##.....##.########..########..######.
    // .##........##...##...##.....##....##.....##.##.....##.##.......##....##
    // .##........##....##.##......##....##.....##.##.....##.##.......##......
    // .######....##.....###.......##....##.....##.########..######....######.
    // .##........##....##.##......##....##.....##.##...##...##.............##
    // .##........##...##...##.....##....##.....##.##....##..##.......##....##
    // .##.......####.##.....##....##.....#######..##.....##.########..######.
    //
    // FIXTURES

// PWM fixture
#ifdef PWM_ON_OFF
    // Enable PWM
    for (int k = 0; k < PWM_N_CHAN; k++)
        if (PWM_PIN[k32->system->hw()][k] > 0) // TODO: allow -1 pin but disable output
            pwm->attach(PWM_PIN[k32->system->hw()][k]);

    K32_fixture *dimmer = new K32_pwmfixture(pwm);
    light->addFixture(dimmer);
#endif

    // LED STRIPS fixtures
    K32_fixture *strips[LED_N_STRIPS] = {nullptr};

    int PIXSIZE = k32->system->pixsize();

    #ifdef PREVIEW
        for (int k = 0; k < LED_N_STRIPS; k++)
            strips[k] = new K32_ledstrip(k, LEDS_PIN[k32->system->hw()][k], (led_types)LULU_STRIP_TYPE, PIXSIZE + 30);
        light->addFixtures(strips, LED_N_STRIPS)
            ->copyFixture({strips[0], PIXSIZE, PIXSIZE + 18, strips[1], 0}); // jauge sortie 2
    #else
        for (int k = 0; k < LED_N_STRIPS; k++)
            strips[k] = new K32_ledstrip(k, LEDS_PIN[k32->system->hw()][k], (led_types)LULU_STRIP_TYPE, PIXSIZE);
        light->addFixtures(strips, LED_N_STRIPS)
            ->copyFixture({strips[0], 0, PIXSIZE, strips[1], 0}); //  sortie 2
    #endif

    // ! vérifié que ça fonctionne bien sur la double sortie strip ?
  
  /*          strips[k] = new K32_ledstrip(k, LEDS_PIN[k32->system->hw()][k], (led_types)LULU_STRIP_TYPE, PIXSIZE);
        light->addFixtures(strips, LED_N_STRIPS)
            ->copyFixture({strips[0], 0, PIXSIZE, strips[1], 0}); //  sortie 2
  */          
    // .########.########..######..########.....######..########..#######..##.....##.########.##....##..######..########
    // ....##....##.......##....##....##.......##....##.##.......##.....##.##.....##.##.......###...##.##....##.##......
    // ....##....##.......##..........##.......##.......##.......##.....##.##.....##.##.......####..##.##.......##......
    // ....##....######....######.....##........######..######...##.....##.##.....##.######...##.##.##.##.......######..
    // ....##....##.............##....##.............##.##.......##..##.##.##.....##.##.......##..####.##.......##......
    // ....##....##.......##....##....##.......##....##.##.......##....##..##.....##.##.......##...###.##....##.##......
    // ....##....########..######.....##........######..########..#####.##..#######..########.##....##..######..########
    //
    // TEST Sequence

    // INIT TEST STRIPS
    light->anim("test-strip", new Anim_test_strip, PIXSIZE)
        ->drawTo(strips, LED_N_STRIPS)
        ->push(300)
        ->master(LULU_PREV_MASTER)
        ->play();

// PWM TEST
#ifdef PWM_ON_OFF
    light->anim("test-pwm", new Anim_test_pwm, PIXSIZE)
        ->drawTo(dimmer)
        ->push(300)
        ->master(LULU_PREV_MASTER)
        ->play();
#endif

    // WAIT END
    light->anim("test-strip")->wait();
#ifdef PWM_ON_OFF
    light->anim("test-pwm")->wait();
#endif

    // .########..########..########..######..########.########..######.
    // .##.....##.##.....##.##.......##....##.##..........##....##....##
    // .##.....##.##.....##.##.......##.......##..........##....##......
    // .########..########..######....######..######......##.....######.
    // .##........##...##...##.............##.##..........##..........##
    // .##........##....##..##.......##....##.##..........##....##....##
    // .##........##.....##.########..######..########....##.....######.
    //
    //  PRESETS

// ANIM pwm - presets
#ifdef PWM_ON_OFF
    light->anim("mem-pwm", new Anim_datathru, PWM_N_CHAN)
        ->drawTo(dimmer)
        ->bank(new BankPWM)
        ->remote(true)
        ->mem(-1);
#endif

    // ANIM leds - presets
    light->anim("mem-strip", new Anim_dmx_strip, PIXSIZE)
        ->drawTo(strips[0])
        ->bank(new BankSK)
        ->remote(true)
        ->mem(-1);

// ANIM leds - presets preview
#ifdef PREVIEW

    light->anim("memprev-strip", new Anim_preview, LULU_PREV_SIZE, PIXSIZE + 8)
        ->drawTo(strips[0])
        ->bank(new BankSK) // TODO
        ->mem(-1)
        ->master(LULU_PREV_MASTER);
    // .##.....##..#######..##....##.####.########..#######..########..####.##....##..######..
    // .###...###.##.....##.###...##..##.....##....##.....##.##.....##..##..###...##.##....##.
    // .####.####.##.....##.####..##..##.....##....##.....##.##.....##..##..####..##.##.......
    // .##.###.##.##.....##.##.##.##..##.....##....##.....##.########...##..##.##.##.##...####
    // .##.....##.##.....##.##..####..##.....##....##.....##.##...##....##..##..####.##....##.
    // .##.....##.##.....##.##...###..##.....##....##.....##.##....##...##..##...###.##....##.
    // .##.....##..#######..##....##.####....##.....#######..##.....##.####.##....##..######..
    //
    // MONITORING

    // ANIM leds - monitoring
    light->anim("battery-strip", new Anim_battery, 4, PIXSIZE + 1)
        ->drawTo(strips[0])
        ->master(LULU_PREV_MASTER)
        ->play();

    light->anim("remote-strip", new Anim_remote, LULU_PREV_SIZE + 4, PIXSIZE + 6)
        ->drawTo(strips[0])
        ->master(LULU_PREV_MASTER)
        ->play();

    light->anim("rssi-strip", new Anim_rssi, 1, PIXSIZE + 17)
        ->drawTo(strips[0])
        ->master(LULU_PREV_MASTER * 1.5)
        ->play();
#else
    // light->anim("mem-strip", new Anim_dmx_strip, PIXSIZE)
    //     ->drawTo(strips[0])
    //     ->bank(new BankSK_PREV) // TODO
    //     ->mem(-1)
    //     ->master(LULU_PREV_MASTER);
#endif

    // ....###....########..########.##....##.########.########
    // ...##.##...##.....##....##....###...##.##..........##...
    // ..##...##..##.....##....##....####..##.##..........##...
    // .##.....##.########.....##....##.##.##.######......##...
    // .#########.##...##......##....##..####.##..........##...
    // .##.....##.##....##.....##....##...###.##..........##...
    // .##.....##.##.....##....##....##....##.########....##...
    //
    // ARTNET

// ANIM pwm - artnet
#ifdef PWM_ON_OFF
    light->anim("artnet-pwm", new Anim_datathru, PWM_N_CHAN)
        ->drawTo(dimmer)
        ->play();
#endif

    // ANIM leds - artnet
    light->anim("artnet-strip", new Anim_dmx_strip, PIXSIZE)
        ->drawTo(strips[0])
        ->play();

    // ARTNET: subscribe dmx frame
#ifdef PWM_ON_OFF
    int FRAME_size = light->anim("mem-strip")->bank()->preset_size() + light->anim("mem-pwm")->bank()->preset_size();
#else
    int FRAME_size = light->anim("mem-strip")->bank()->preset_size();
    FRAME_size = 20; // Forced to 20
#endif

    K32_artnet::onDmx({.address = (1 + (k32->system->lightid() - 1) * FRAME_size),
                       .framesize = FRAME_size,
                       .callback = [](const uint8_t *data, int length)
                       {
                           int sizeSK = light->anim("mem-strip")->bank()->preset_size();
#ifdef PWM_ON_OFF
                           int sizePWM = light->anim("mem-pwm")->bank()->preset_size();
#endif

                           // LOGINL("ARTFRAME: "); LOGF("length=%d ", length); for (int k = 0; k < length; k++) LOGF("%d ", data[k]); LOG();
                           light->anim("artnet-strip")->push(data, min(sizeSK, length));
#ifdef PWM_ON_OFF
                           light->anim("artnet-pwm")->push(data, min(sizePWM, length)); // FIX
#endif
                       }});

    // .##....##..#######.....##......##.####.########.####
    // .###...##.##.....##....##..##..##..##..##........##.
    // .####..##.##.....##....##..##..##..##..##........##.
    // .##.##.##.##.....##....##..##..##..##..######....##.
    // .##..####.##.....##....##..##..##..##..##........##.
    // .##...###.##.....##....##..##..##..##..##........##.
    // .##....##..#######......###..###..####.##.......####
    //
    // NOWIFI

    // EVENT: wifi lost
    // wifi->onDisconnect([&]()
    // {
    //     LOG("WIFI: connection lost..");
    //     //  light->anim("artnet-strip")->push(MEM_NO_WIFI, LULU_PATCHSIZE);
    //     light->anim("artnet-strip")->push(0); // @master 0
    // });

    // .########..########.##.....##..#######..########.########
    // .##.....##.##.......###...###.##.....##....##....##......
    // .##.....##.##.......####.####.##.....##....##....##......
    // .########..######...##.###.##.##.....##....##....######..
    // .##...##...##.......##.....##.##.....##....##....##......
    // .##....##..##.......##.....##.##.....##....##....##......
    // .##.....##.########.##.....##..#######.....##....########
    //
    // REMOTE

    remote->setMacroMax(light->anim("mem-strip")->bank()->size());

    k32->on("remote/macro", [](Orderz *order)
            {
                light->anim("mem-strip")->mem(order->getData(0)->toInt());
#ifdef PWM_ON_OFF
                light->anim("mem-pwm")->mem(order->getData(0)->toInt());
#endif
            });

#ifdef PREVIEW
    k32->on("remote/preview", [](Orderz *order)
            { light->anim("memprev-strip")->mem(order->getData(0)->toInt()); });
#endif

    k32->on("remote/lock", [](Orderz *order)
            { light->anim("remote-strip")->push(remote->getState(), true); });

    k32->on("remote/unlock", [](Orderz *order)
            { light->anim("remote-strip")->push(remote->getState(), false); });

    k32->on("remote/state", [](Orderz *order)
            {

        remoteState stateR = (remoteState) order->getData(0)->toInt();

        // AUTO
        if (stateR == REMOTE_AUTO)
        {
            light->anim("mem-strip")->stop();
            #ifdef PREVIEW
            light->anim("memprev-strip")->stop();
            #endif
            light->anim("artnet-strip")->play();
            LOG("REMOTE: -> Mode AUTO");
        }

        // STM
        else if (stateR == REMOTE_MANU_STM)
        {
            light->anim("artnet-strip")->stop();
            #ifdef PREVIEW
            light->anim("memprev-strip")->play();
            #endif
            light->anim("mem-strip")->play();
            LOG("REMOTE: -> Mode STM");
        }

        // MANU
        else if (stateR == REMOTE_MANU || stateR == REMOTE_MANU_LAMP)
        {
            light->anim("artnet-strip")->stop();
            light->anim("mem-strip")->play();
            #ifdef PREVIEW
            light->anim("memprev-strip")->play();
            #endif
            LOG("REMOTE: -> Mode MANU");
        }

        // REMOTE LED
        light->anim("remote-strip")->push(stateR, remote->isLocked()); });
}
