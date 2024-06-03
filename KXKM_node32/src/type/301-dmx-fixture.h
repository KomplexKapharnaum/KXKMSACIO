
#define L_NAME "DMX Fixture" // a tester

// // LEDS
// #define LULU_STRIP_TYPE LED_SK6812W_V3 // Type de strip led
// #define LULU_STRIP_SIZE 120
// #define STRIP_PATCHSIZE 16

// PAR
#define PAR_N 1
#define PAR_PATCH_SIZE 5

// ARCALINE
#define ARCA_N 1
#define ARCA_PATCH_SIZE 7 // 1 r , 2 v, 3 b, 4 blanc, 5 str, 6 macro color, 7 dim

// P5
#define P5_N 1
#define P5_PATCH_SIZE 6 // 1 str, 2 dim, 3 red, 4 green, 5 blue, 6 white

// PATCH
#define PATCHSIZE PAR_PATCH_SIZE + ARCA_PATCH_SIZE + P5_PATCH_SIZE

#define ARTNET_ENABLE 1
#define ARTNET_DMXNODE 0

#include "macro/Type/parled/mem_pwm_parled_dmx.h"
#include "macro/Type/arcaline/mem_arca_dmx_mod_1.h"
#include "macro/Type/p5/mem_p5_dmx_mod_1.h"

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
    // for (int k = 0; k < PWM_N_CHAN; k++)
    //     if (PWM_PIN[k32->system->hw()][k] > 0) // TODO: allow -1 pin but disable output
    //         pwm->attach(PWM_PIN[k32->system->hw()][k]);

    // PWM fixture
    // K32_fixture *dimmer = new K32_pwmfixture(pwm);
    // light->addFixture(dimmer);

    // LED STRIPS fixtures
    // K32_fixture *strips[LED_N_STRIPS] = {nullptr};
    // for (int k = 0; k < LED_N_STRIPS; k++)
    //     strips[k] = new K32_ledstrip(k, LEDS_PIN[k32->system->hw()][k], (led_types)LULU_STRIP_TYPE, LULU_STRIP_SIZE);
    // light->addFixtures(strips, LED_N_STRIPS);

    int size_par;
    int size_arca;
    int size_p5;

    // PAR fixtures
    K32_fixture *par[PAR_N] = {nullptr};
    for (int k = 0; k < PAR_N; k++)
    {
        par[k] = new K32_dmxfixture(dmx, (1 + PAR_PATCH_SIZE * k), PAR_PATCH_SIZE);
        size_par = (1 + PAR_PATCH_SIZE * k) + PAR_PATCH_SIZE;
    }
    light->addFixtures(par, PAR_N);

    // ARCA fixture
    K32_fixture *arca[ARCA_N] = {nullptr};
    for (int k = 0; k < ARCA_N; k++)
    {
        arca[k] = new K32_dmxfixture(dmx, (size_par + ARCA_PATCH_SIZE * k), ARCA_PATCH_SIZE);
        size_arca = (size_par + ARCA_PATCH_SIZE * k) + ARCA_PATCH_SIZE;
    }
    light->addFixtures(arca, ARCA_N);

    // P5
    K32_fixture *p5[P5_N] = {nullptr};
    for (int k = 0; k < P5_N; k++)
    {
        arca[k] = new K32_dmxFixture(dmx, (size_arca + P5_PATCH_SIZE * k), P5_PATCH_SIZE);
        size_p5 = (size_arca + P5_PATCH_SIZE * k) + P5_PATCH_SIZE
    }
    light->addFixtures(p5 , P5_N);

                  // .########.########..######..########.....######..########..#######..##.....##.########.##....##..######..########
                  // ....##....##.......##....##....##.......##....##.##.......##.....##.##.....##.##.......###...##.##....##.##......
                  // ....##....##.......##..........##.......##.......##.......##.....##.##.....##.##.......####..##.##.......##......
                  // ....##....######....######.....##........######..######...##.....##.##.....##.######...##.##.##.##.......######..
                  // ....##....##.............##....##.............##.##.......##..##.##.##.....##.##.......##..####.##.......##......
                  // ....##....##.......##....##....##.......##....##.##.......##....##..##.....##.##.......##...###.##....##.##......
                  // ....##....########..######.....##........######..########..#####.##..#######..########.##....##..######..########

    // TODO test for fixture

    // TEST Seque 
    // PWM TEST
    // light->anim("test-pwm", new Anim_test_pwm, PWM_N_CHAN)
    //     ->drawTo(dimmer)
    //     ->push(300)
    //     ->master(LULU_PREV_MASTER)
    //     ->play();

    // // INIT TEST STRIPS
    // light->anim("test-strip", new Anim_test_strip, LULU_STRIP_SIZE)
    //     ->drawTo(strips, LED_N_STRIPS)
    //     ->push(300)
    //     ->master(LULU_PREV_MASTER)
    //     ->play();

    // // WAIT END
    // light->anim("test-strip")->wait();
    // light->anim("test-pwm")->wait();

    // .########..########..########..######..########.########..######.
    // .##.....##.##.....##.##.......##....##.##..........##....##....##
    // .##.....##.##.....##.##.......##.......##..........##....##......
    // .########..########..######....######..######......##.....######.
    // .##........##...##...##.............##.##..........##..........##
    // .##........##....##..##.......##....##.##..........##....##....##
    // .##........##.....##.########..######..########....##.....######.

    // ANIM pwm - presets
    // light->anim("mem-pwm", new Anim_datathru, PWM_N_CHAN)
    //     ->drawTo(dimmer)
    //     ->bank(new BankPWM)
    //     ->remote(true)
    //     ->mem(-1);

    // // ANIM leds - presets
    // light->anim("mem-strip", new Anim_dmx_strip, LULU_STRIP_SIZE)
    //     ->drawTo(strips, LED_N_STRIPS)
    //     ->bank(new BankSK)
    //     ->remote(true)
    //     ->mem(-1);

    // ANIM par - presets
    light->anim("mem-par", new Par_datathru, PAR_PATCH_SIZE)
        ->drawTo(par, PAR_N)
        ->bank(new BankPar)
        ->remote(true)
        ->mem(-1);

    // ANIM arca - presets
    light->anim("mem-arca", new Arca_datathru, ARCA_PATCH_SIZE)
        ->drawTo(arca, ARCA_N)
        ->bank(new BankArca)
        ->remote(true)
        ->mem(-1);

    // ANIM P5 - presets
    light->anim("mem-p5", new P5_datathru, P5_PATCH_SIZE)
        ->drawTo(p5, P5_N)
        ->bank(new BankP5)
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
    // light->anim("artnet-pwm", new Anim_datathru, PWM_N_CHAN)
    //     ->drawTo(dimmer)
    //     ->play();

    // ANIM pwm - artnet
    // light->anim("artnet-strip", new Anim_dmx_strip, PWM_N_CHAN)
    //     ->drawTo(strips, LED_N_STRIPS)
    //     ->play();

    // ANIM par - artnet
    light->anim("artnet-par", new Par_datathru, PAR_PATCH_SIZE)
        ->drawTo(par, PAR_N)
        ->play();

        // ANIM arca - artnet
    light->anim("artnet-arca", new Arca_datathru, ARCA_PATCH_SIZE)
        ->drawTo(arca, ARCA_N)
        ->play();

        // ANIM p5 - artnet
    light->anim("artnet-p5", new P5_datathru, P5_PATCH_SIZE)
        ->drawTo(p5, P5_N)
        ->play();

    // ARTNET: subscribe dmx frame
    K32_artnet::onDmx({.address = (1 + (k32->system->lightid() - 1) * PATCHSIZE),
                       .framesize = PATCHSIZE,
                       .callback = [](const uint8_t *data, int length)
                       {
                        //    if (length >= PWM_N_CHAN)
                        //        light->anim("artnet-pwm")->push(data, PWM_N_CHAN);

                           // if (length >= PWM_N_CHAN + STRIP_PATCHSIZE)
                           //     light->anim("artnet-strip")->push(&data[PWM_N_CHAN], STRIP_PATCHSIZE);

                        if (length >= PAR_PATCH_SIZE)
                            light->anim("artnet-par")->push(data, PAR_PATCH_SIZE);
                        if (length >= PAR_PATCH_SIZE + ARCA_PATCH_SIZE)
                            light->anim("artnet-arca")->push(&data[PAR_PATCH_SIZE], ARCA_PATCH_SIZE);
                        if (length >= PAR_PATCH_SIZE + ARCA_PATCH_SIZE + P5_PATCH_SIZE)
                            light->anim("artnet-p5")->push(&data[PAR_PATCH_SIZE + ARCA_PATCH_SIZE], P5_PATCH_SIZE);
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
            light->anim("mem-arca")->mem( order->getData(0)->toInt());
            light->anim("mem-p5")  ->mem( order->getData(0)->toInt());
            remote->setState(REMOTE_MANU); 
            LOGF("mem: %d\n", order->getData(0)->toInt()); });

    // REMOTE: state changed
    k32->on("remote/state", [](Orderz *order)
            {
            remoteState stateR = (remoteState) order->getData(0)->toInt();

            // AUTO
            if (stateR == REMOTE_AUTO)
            {
                light->anim("mem-par")->stop();
                light->anim("artnet-par")->play();

                light->anim("mem-arca")->stop();
                light->anim("artnet-arca")->play();

                light->anim("mem-p5")->stop();
                light->anim("artnet-p5")->play();

                
                LOG("REMOTE: -> Mode AUTO");
            }

            // MANU
            else if (stateR == REMOTE_MANU || stateR == REMOTE_MANU_LAMP || stateR == REMOTE_MANU_STM)
            {
                light->anim("artnet-par")->stop();
                light->anim("mem-par")->play();

                light->anim("artnet-arca")->stop();
                light->anim("mem-arca")->play();

                light->anim("artnet-p5")->stop();
                light->anim("mem-p5")->play();
                

                LOG("REMOTE: -> Mode MANU");
            } });
}
