
#define L_NAME "Sac"

// MEMS
#include "macro/Type/SK/mem_sk.h"
#include "macro/Type/4pwm/mem_4pwm.h"

// LEDS
#define LULU_STRIP_TYPE LED_SK6812W_V3 // Strip type
#define LULU_STRIP_SIZE 120

// LEDS ATOM
// #define LULU_STRIP_TYPE LED_WS2812B_V3 // Strip type
// #define LULU_STRIP_SIZE 5

// PATCH
#define PATCHSIZE  (STRIP_PATCHSIZE + PWM_N_CHAN)   // 20

// POWER
#define PWR_FAKE_CURRENT 12500

// ARTNET
#define ARTNET_ENABLE 1
#define ARTNET_DMXNODE 0


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

    // Enable PWM 
    for (int k = 0; k < PWM_N_CHAN; k++)
        if (PWM_PIN[k32->system->hw()][k] > 0) // TODO: allow -1 pin but disable output
            pwm->attach(PWM_PIN[k32->system->hw()][k]);

    // PWM fixture
    K32_fixture *dimmer = new K32_pwmfixture(pwm);
    light->addFixture(dimmer);

    // LED STRIPS fixtures
    K32_fixture *strips[LED_N_STRIPS] = {nullptr};
    for (int k = 0; k < LED_N_STRIPS; k++)
        strips[k] = new K32_ledstrip(k, LEDS_PIN[k32->system->hw()][k], (led_types)LULU_STRIP_TYPE, LULU_STRIP_SIZE + 30);
    light->addFixtures(strips, LED_N_STRIPS)
        ->copyFixture({strips[0], LULU_STRIP_SIZE, LULU_STRIP_SIZE + 18, strips[1], 0}); // jauge sortie 2

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
    light->anim("test-strip", new Anim_test_strip, LULU_STRIP_SIZE + 30)
        ->drawTo(strips, LED_N_STRIPS)
        ->push(300)
        ->master(LULU_PREV_MASTER)
        ->play();

    // PWM TEST
    light->anim("test-pwm", new Anim_test_pwm, PWM_N_CHAN)
        ->drawTo(dimmer)
        ->push(300)
        ->master(LULU_PREV_MASTER)
        ->play();

    // WAIT END
    light->anim("test-strip")->wait();
    light->anim("test-pwm")->wait();


    // .########..########..########..######..########.########..######.
    // .##.....##.##.....##.##.......##....##.##..........##....##....##
    // .##.....##.##.....##.##.......##.......##..........##....##......
    // .########..########..######....######..######......##.....######.
    // .##........##...##...##.............##.##..........##..........##
    // .##........##....##..##.......##....##.##..........##....##....##
    // .##........##.....##.########..######..########....##.....######.
    //
    //  PRESETS

    // ANIM leds - presets
    light->anim("mem-strip", new Anim_dmx_strip, LULU_STRIP_SIZE)
        ->drawTo(strips[0])
        ->bank(new BankSK)
        ->remote(true)
        ->mem(-1);

    // ANIM leds - presets preview
    light->anim("memprev-strip", new Anim_preview, LULU_PREV_SIZE, LULU_STRIP_SIZE + 8)
        ->drawTo(strips[0])
        ->bank(new BankSK_PREV) // TODO
        ->master(LULU_PREV_MASTER)
        ->mem(-1);

    // ANIM pwm - presets
    light->anim("mem-pwm", new Anim_datathru, PWM_N_CHAN)
        ->drawTo(dimmer)
        ->bank(new BankPWM)
        ->remote(true)
        ->mem(-1);

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

    // ....###....########..########.##....##.########.########
    // ...##.##...##.....##....##....###...##.##..........##...
    // ..##...##..##.....##....##....####..##.##..........##...
    // .##.....##.########.....##....##.##.##.######......##...
    // .#########.##...##......##....##..####.##..........##...
    // .##.....##.##....##.....##....##...###.##..........##...
    // .##.....##.##.....##....##....##....##.########....##...
    //
    // ARTNET

    // ANIM leds - artnet
    light->anim("artnet-strip", new Anim_dmx_strip, LULU_STRIP_SIZE)
        ->drawTo(strips[0])
        ->play();

    // ANIM pwm - artnet
    light->anim("artnet-pwm", new Anim_datathru, PWM_N_CHAN)
        ->drawTo(dimmer)
        ->play();

    // ARTNET: subscribe dmx frame
    K32_artnet::onDmx({.address = (1 + (k32->system->lightid() - 1) * int(PATCHSIZE)),
                       .framesize = PATCHSIZE,
                       .callback = [](const uint8_t *data, int length)
                       {
                           // LOGINL("ARTFRAME: "); LOGF("length=%d ", length); for (int k = 0; k < length; k++) LOGF("%d ", data[k]); LOG();
                            if (length >= STRIP_PATCHSIZE)
                                light->anim("artnet-strip")->push(data, STRIP_PATCHSIZE);

                            if (length >= STRIP_PATCHSIZE + PWM_N_CHAN)
                                light->anim("artnet-pwm")->push(&data[STRIP_PATCHSIZE], PWM_N_CHAN);
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
    K32_wifi::onDisconnect([]()
    {
        LOG("WIFI: connection lost..");
        // light->anim("artnet-strip")->push(255, 255, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 255);
        // light->anim("artnet-pwm")->push(0, 0, 0, 0);
    });

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

    // init Remote leds 
    light->anim("remote-strip")->push(remote->getState(), remote->isLocked());

    k32->on("btn/atom", [](Orderz *order)
            { remote->stmNext(); });

    k32->on("remote/macro", [](Orderz *order)
            {
                light->anim("mem-strip")->mem(order->getData(0)->toInt());
                light->anim("mem-pwm")->mem(order->getData(0)->toInt());
            });

    k32->on("remote/preview", [](Orderz *order)
            { light->anim("memprev-strip")->mem(order->getData(0)->toInt()); });

    k32->on("remote/lock", [](Orderz *order)
            { light->anim("remote-strip")->push(remote->getState(), remote->isLocked()); });

    k32->on("remote/unlock", [](Orderz *order)
            { light->anim("remote-strip")->push(remote->getState(), remote->isLocked()); });

    k32->on("remote/state", [](Orderz *order)
            {
                remoteState stateR = (remoteState) order->getData(0)->toInt();

                // AUTO
                if (stateR == REMOTE_AUTO)
                {
                    light->anim("mem-strip")->stop();
                    light->anim("memprev-strip")->stop();
                    light->anim("artnet-strip")->play();
                    LOG("REMOTE: -> Mode AUTO");
                }

                // STM
                else if (stateR == REMOTE_MANU_STM)
                {
                    light->anim("artnet-strip")->stop();
                    light->anim("memprev-strip")->play();
                    light->anim("mem-strip")->play();
                    LOG("REMOTE: -> Mode STM");
                }

                // MANU
                else if (stateR == REMOTE_MANU || stateR == REMOTE_MANU_LAMP)
                {
                    light->anim("artnet-strip")->stop();
                    light->anim("mem-strip")->play();
                    light->anim("memprev-strip")->play();
                    LOG("REMOTE: -> Mode MANU");
                }

                // REMOTE LED
                light->anim("remote-strip")->push(remote->getState(), remote->isLocked()); 
            });
}
