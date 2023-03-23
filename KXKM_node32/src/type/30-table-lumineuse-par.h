
#define L_NAME "table_lumineuse_par" // a tester

// PAR
#define PAR_N 1
#define PAR_PATCHSIZE 5

// LEDS
#define LULU_STRIP_TYPE   LED_SK6812W_V3  // Type de strip led          
#define LULU_STRIP_SIZE   120
#define STRIP_PATCHSIZE 16

// PATCH
#define PATCHSIZE   25 // PWM_N_CHAN + STRIP_PATCHSIZE + PAR_PATCHSIZE

#define ARTNET_ENABLE 1
#define ARTNET_DMXNODE 0


// #include "macro/Show/Baro/mem_pwm_baro_127.h" // cube 1 3 5 7 9
// #include "macro/Show/Baro/mem_cube_baro_127.h"

// // #include "macro/Show/Baro/mem_pwm_baro_125.h"   // cube 2 4 6 8 10
// // #include "macro/Show/Baro/mem_cube_baro_125.h"

#include "macro/Type/4pwm/mem_4pwm.h"
// #include "macro/Show/parlement/mem_4pwm_parlement.h"
#include "macro/Show/parlement/mem_parled_solo.h"
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
        strips[k] = new K32_ledstrip(k, LEDS_PIN[k32->system->hw()][k], (led_types)LULU_STRIP_TYPE, LULU_STRIP_SIZE);
    light->addFixtures(strips, LED_N_STRIPS);

    // PAR fixtures
    K32_fixture *par[PAR_N] = {nullptr};
    for (int k = 0; k < PAR_N; k++)
        par[k] = new K32_dmxfixture(dmx, (1 + PATCHSIZE * k) + PWM_N_CHAN + STRIP_PATCHSIZE, PAR_PATCHSIZE);
    light->addFixtures(par, PAR_N);

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

    // ANIM par - presets
    light->anim("mem-par", new Anim_datathru, PAR_PATCHSIZE)
        ->drawTo(par, PAR_N)
        ->bank(new BankPar)
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


    // ANIM par - artnet
    light->anim("artnet-par", new Anim_datathru, PAR_PATCHSIZE)
        ->drawTo(par, PAR_N)
        ->play();

    // ARTNET: subscribe dmx frame
    K32_artnet::onDmx({.address = (1 + (k32->system->lightid() - 1) * PATCHSIZE),
                       .framesize = PATCHSIZE,
                       .callback = [](const uint8_t *data, int length)
                       {
                            if (length >= PWM_N_CHAN)
                               light->anim("artnet-pwm")->push(data, PWM_N_CHAN);

                            if (length >= PWM_N_CHAN + STRIP_PATCHSIZE)
                                light->anim("artnet-strip")->push(&data[PWM_N_CHAN], STRIP_PATCHSIZE);

                            if (length >= PATCHSIZE) 
                                light->anim("artnet-par")->push(&data[PWM_N_CHAN + STRIP_PATCHSIZE], PAR_PATCHSIZE);
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

    remote->setMacroMax(light->anim("mem-par")->bank()->size());

    // REMOTE: want macro
    k32->on("remote/macro", [](Orderz *order)
            {
            light->anim("mem-par")  ->mem( order->getData(0)->toInt());
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

                light->anim("mem-par")->stop();
                light->anim("artnet-par")->play();
                
                LOG("REMOTE: -> Mode AUTO");
            }

            // MANU
            else if (stateR == REMOTE_MANU || stateR == REMOTE_MANU_LAMP || stateR == REMOTE_MANU_STM)
            {
                light->anim("artnet-pwm")->stop();
                light->anim("mem-pwm")->play();

                light->anim("artnet-strip")->stop();
                light->anim("mem-strip")->play();
                
                light->anim("artnet-par")->stop();
                light->anim("mem-par")->play();

                LOG("REMOTE: -> Mode MANU");
            } });
}
