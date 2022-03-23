
#define L_NAME "table_lumineuse_strobe" // a tester

// STROBE
#define VERSION_STROBE 2 // 1=strobe rgb 16 ch 5 division 2=strobe rgb 17 ch 4 division
#define STROBE_N 4       // nombre de strobe

#if VERSION_STROBE == 1
#define STROBE_PATCHSIZE 16
#include "macro/Type/strobe/mem_strobe_dmx_mod_1.h"
#elif VERSION_STROBE == 2
#define STROBE_PATCHSIZE 17
#include "macro/Type/strobe/mem_strobe_dmx_mod_2.h"
#endif

// LEDS
#define LULU_STRIP_TYPE   LED_SK6812W_V3  // Type de strip led          
#define LULU_STRIP_SIZE   120
#define STRIP_PATCHSIZE 16

// PATCH
#define PATCHSIZE   PWM_N_CHAN + STRIP_PATCHSIZE + STROBE_PATCHSIZE

#define ARTNET_ENABLE 1
#define ARTNET_DMXNODE 0


#include "macro/Type/4pwm/mem_4pwm.h"
#include "macro/Show/parlement/mem_sk_parlement.h"


void setup_device()
{
    // .########.####.##.....##.########.##.....##.########..########..######.
    // .##........##...##...##.....##....##.....##.##.....##.##.......##....##
    // .##........##....##.##......##....##.....##.##.....##.##.......##......
    // .######....##.....###.......##....##.....##.########..######....######.
    // .##........##....##.##......##....##.....##.##...##...##.............##
    // .##........##...##...##.....##....##.....##.##....##..##.......##....##
    // .##.......####.##.....##....##.....#######..##.....##.########..######.

    // FIXTURES

    // PWM fixture
    K32_fixture *dimmer = new K32_pwmfixture(pwm);
    light->addFixture(dimmer);

    // LED STRIPS fixtures
    K32_fixture *strips[LED_N_STRIPS] = {nullptr};
    for (int k = 0; k < LED_N_STRIPS; k++)
        strips[k] = new K32_ledstrip(k, LEDS_PIN[k32->system->hw()][k], (led_types)LULU_STRIP_TYPE, LULU_STRIP_SIZE);
    light->addFixtures(strips, LED_N_STRIPS);

    // strobes fixtures
    K32_fixture *strobes[STROBE_N] = {nullptr};
    for (int k = 0; k < STROBE_N; k++)
        strobes[k] = new K32_dmxfixture(dmx, (1 + PATCHSIZE * k) + PWM_N_CHAN + STRIP_PATCHSIZE, STROBE_PATCHSIZE);
    light->addFixtures(strobes, STROBE_N);

    // .########.########..######..########.....######..########..#######..##.....##.########.##....##..######..########
    // ....##....##.......##....##....##.......##....##.##.......##.....##.##.....##.##.......###...##.##....##.##......
    // ....##....##.......##..........##.......##.......##.......##.....##.##.....##.##.......####..##.##.......##......
    // ....##....######....######.....##........######..######...##.....##.##.....##.######...##.##.##.##.......######..
    // ....##....##.............##....##.............##.##.......##..##.##.##.....##.##.......##..####.##.......##......
    // ....##....##.......##....##....##.......##....##.##.......##....##..##.....##.##.......##...###.##....##.##......
    // ....##....########..######.....##........######..########..#####.##..#######..########.##....##..######..########

    // TEST Sequence

    // PWM TEST
    light->anim("test-pwm", new Anim_test_pwm, PWM_N_CHAN)
        ->drawTo(dimmer)
        ->push(300)
        ->master(LULU_PREV_MASTER)
        ->play();

    // INIT TEST STRIPS
    light->anim("test-strip", new Anim_test_strip, LULU_STRIP_SIZE)
        ->drawTo(strips, LED_N_STRIPS)
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

    // ANIM pwm - presets
    light->anim("mem-pwm", new Anim_datathru, PWM_N_CHAN)
        ->drawTo(dimmer)
        ->bank(new BankPWM)
        ->remote(true)
        ->mem(-1);

    // ANIM leds - presets
    light->anim("mem-strip", new Anim_dmx_strip, LULU_STRIP_SIZE)
        ->drawTo(strips, LED_N_STRIPS)
        ->bank(new BankSK)
        ->remote(true)
        ->mem(-1);

    // ANIM strobes - presets
    light->anim("mem-strobes", new Anim_datathru, STROBE_PATCHSIZE)
        ->drawTo(strobes, STROBE_N)
        ->bank(new BankStrobe)
        ->remote(true)
        ->mem(-1);

    // .##.....##..#######..##....##.####.########..#######..########..####.##....##..######..
    // .###...###.##.....##.###...##..##.....##....##.....##.##.....##..##..###...##.##....##.
    // .####.####.##.....##.####..##..##.....##....##.....##.##.....##..##..####..##.##.......
    // .##.###.##.##.....##.##.##.##..##.....##....##.....##.########...##..##.##.##.##...####
    // .##.....##.##.....##.##..####..##.....##....##.....##.##...##....##..##..####.##....##.
    // .##.....##.##.....##.##...###..##.....##....##.....##.##....##...##..##...###.##....##.
    // .##.....##..#######..##....##.####....##.....#######..##.....##.####.##....##..######..

    // ....###....########..########.##....##.########.########
    // ...##.##...##.....##....##....###...##.##..........##...
    // ..##...##..##.....##....##....####..##.##..........##...
    // .##.....##.########.....##....##.##.##.######......##...
    // .#########.##...##......##....##..####.##..........##...
    // .##.....##.##....##.....##....##...###.##..........##...
    // .##.....##.##.....##....##....##....##.########....##...

    // ANIM pwm - artnet
    light->anim("artnet-pwm", new Anim_datathru, PWM_N_CHAN)
        ->drawTo(dimmer)
        ->play();

    // ANIM pwm - artnet
    light->anim("artnet-strip", new Anim_dmx_strip, PWM_N_CHAN)
        ->drawTo(strips, LED_N_STRIPS)
        ->play();


    // ANIM strobes - artnet
    light->anim("artnet-strobes", new Anim_datathru, STROBE_PATCHSIZE)
        ->drawTo(strobes, STROBE_N)
        ->play();

    // ARTNET: subscribe dmx frame
    K32_artnet::onDmx({.address = (1 + (light->id() - 1) * PATCHSIZE),
                       .framesize = PATCHSIZE,
                       .callback = [](const uint8_t *data, int length)
                       {
                            if (length >= PWM_N_CHAN)
                               light->anim("artnet-pwm")->push(data, PWM_N_CHAN);

                            if (length >= PWM_N_CHAN + STRIP_PATCHSIZE)
                                light->anim("artnet-strip")->push(&data[PWM_N_CHAN], STRIP_PATCHSIZE);

                            if (length >= PATCHSIZE) 
                                light->anim("artnet-strobes")->push(&data[PWM_N_CHAN + STRIP_PATCHSIZE], STROBE_PATCHSIZE);
                       }});

    // .##....##..#######.....##......##.####.########.####
    // .###...##.##.....##....##..##..##..##..##........##.
    // .####..##.##.....##....##..##..##..##..##........##.
    // .##.##.##.##.....##....##..##..##..##..######....##.
    // .##..####.##.....##....##..##..##..##..##........##.
    // .##...###.##.....##....##..##..##..##..##........##.
    // .##....##..#######......###..###..####.##.......####

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

    // REMOTE

    remote->setMacroMax(light->anim("mem-strobes")->bank()->size());

    // REMOTE: want macro
    k32->on("remote/macro", [](Orderz *order)
            {
            light->anim("mem-strobes")  ->mem( order->getData(0)->toInt());
            light->anim("mem-strip")->mem( order->getData(0)->toInt());
            light->anim("mem-pwm")  ->mem( order->getData(0)->toInt());
            remote->setState(REMOTE_MANU); 
            LOGF("mem: %d\n", order->getData(0)->toInt()); });

    // REMOTE: state changed
    k32->on("remote/state", [](Orderz *order)
            {
            remoteState stateR = (remoteState) order->getData(0)->toInt();

            // AUTO
            if (stateR == REMOTE_AUTO)
            {
                light->anim("mem-pwm")->stop();
                light->anim("artnet-pwm")->play();

                light->anim("mem-strip")->stop();
                light->anim("artnet-strip")->play();

                light->anim("mem-strobes")->stop();
                light->anim("artnet-strobes")->play();
                
                LOG("REMOTE: -> Mode AUTO");
            }

            // MANU
            else if (stateR == REMOTE_MANU || stateR == REMOTE_MANU_LAMP || stateR == REMOTE_MANU_STM)
            {
                light->anim("artnet-pwm")->stop();
                light->anim("mem-pwm")->play();

                light->anim("artnet-strip")->stop();
                light->anim("mem-strip")->play();
                
                light->anim("artnet-strobes")->stop();
                light->anim("mem-strobes")->play();

                LOG("REMOTE: -> Mode MANU");
            } });
}
