
#define L_NAME "DMX Fixture" // a tester
#define PRESET_COUNT 16      // stm leave in last mem

// TODO Régler besoin d'apeller 2 fois la mémoire pour que ça fonctionne
// // LEDS
// #define LULU_STRIP_TYPE LED_SK6812W_V3 // Type de strip led
// #define LULU_STRIP_SIZE 120
// #define STRIP_PATCHSIZE 16

// PAR
#define PAR_N 1 // nombre de PAR
#define PAR_PATCH_SIZE 5

// ARCALINE
#define ARCA_N 1          // nombre de ARCALINE
#define ARCA_PATCH_SIZE 7 // 1 r , 2 v, 3 b, 4 blanc, 5 str, 6 macro color, 7 dim

// P5
#define P5_N 1          // nombre de P5
#define P5_PATCH_SIZE 6 // 1 str, 2 dim, 3 red, 4 green, 5 blue, 6 white

// PATCH
#if PAR_N != 0 && ARCA_N != 0 && P5_N != 0
#define PATCHSIZE PAR_PATCH_SIZE + ARCA_PATCH_SIZE + P5_PATCH_SIZE
#elif PAR_N != 0 && ARCA_N != 0
#define PATCHSIZE PAR_PATCH_SIZE + ARCA_PATCH_SIZE
#define P5_PATCH_SIZE 0
#elif PAR_N != 0 && P5_N != 0
#define PATCHSIZE PAR_PATCH_SIZE + P5_PATCH_SIZE
#define ARCA_PATCH_SIZE 0
#elif ARCA_N != 0 && P5_N != 0
#define PATCHSIZE ARCA_PATCH_SIZE + P5_PATCH_SIZE
#define PAR_PATCH_SIZE 0
#elif PAR_N != 0
#define PATCHSIZE PAR_PATCH_SIZE
#define ARCA_PATCH_SIZE 0
#define P5_PATCH_SIZE 0
#elif ARCA_N != 0
#define PATCHSIZE ARCA_PATCH_SIZE
#define PAR_PATCH_SIZE 0
#define P5_PATCH_SIZE 0
#elif P5_N != 0
#define PATCHSIZE P5_PATCH_SIZE
#define PAR_PATCH_SIZE 0
#define ARCA_PATCH_SIZE 0
#endif

#define ARTNET_ENABLE 1
#define ARTNET_DMXNODE 0

#if PAR_N != 0
#include "macro/Type/parled/mem_parled_dmx.h"
#endif
#if ARCA_N != 0
#include "macro/Type/arcaline/mem_arca_dmx_mod_1.h"
#endif
#if P5_N != 0
#include "macro/Type/p5/mem_p5_dmx_mod_1.h"
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
    int size_add = 1;

    // PAR fixtures
#if PAR_N != 0
    K32_fixture *par[PAR_N] = {nullptr};
    for (int k = 0; k < PAR_N; k++)
    {
        par[k] = new K32_dmxfixture(dmx, (size_add + PAR_PATCH_SIZE * k), PAR_PATCH_SIZE);
        size_par = (size_add + PAR_PATCH_SIZE * k) + PAR_PATCH_SIZE;
    }
    light->addFixtures(par, PAR_N);
    size_add = 0;
#endif
    // ARCA fixture
#if ARCA_N != 0
    K32_fixture *arca[ARCA_N] = {nullptr};
    for (int k = 0; k < ARCA_N; k++)
    {
        arca[k] = new K32_dmxfixture(dmx, (size_add + size_par + ARCA_PATCH_SIZE * k), ARCA_PATCH_SIZE);
        size_arca = (size_add + size_par + ARCA_PATCH_SIZE * k) + ARCA_PATCH_SIZE;
    }
    light->addFixtures(arca, ARCA_N);
    size_add = 0;
#endif
    // P5
#if P5_N != 0
    K32_fixture *p5[P5_N] = {nullptr};
    for (int k = 0; k < P5_N; k++)
    {
        p5[k] = new K32_dmxfixture(dmx, (size_add + size_arca + P5_PATCH_SIZE * k), P5_PATCH_SIZE);
        size_p5 = (size_add + size_arca + P5_PATCH_SIZE * k) + P5_PATCH_SIZE;
    }
    light->addFixtures(p5, P5_N);
    size_add = 0;
#endif
    // .########.########..######..########.....######..########..#######..##.....##.########.##....##..######..########
    // ....##....##.......##....##....##.......##....##.##.......##.....##.##.....##.##.......###...##.##....##.##......
    // ....##....##.......##..........##.......##.......##.......##.....##.##.....##.##.......####..##.##.......##......
    // ....##....######....######.....##........######..######...##.....##.##.....##.######...##.##.##.##.......######..
    // ....##....##.............##....##.............##.##.......##..##.##.##.....##.##.......##..####.##.......##......
    // ....##....##.......##....##....##.......##....##.##.......##....##..##.....##.##.......##...###.##....##.##......
    // ....##....########..######.....##........######..########..#####.##..#######..########.##....##..######..########

    // TODO : adapter les animation pour réagir correctement

#if PAR_N != 0
    // INIT TEST STRIPS
    for (int k = 0; k < PAR_N; k++)
    {
        light->anim("test-par", new Anim_dmx_test, PAR_PATCH_SIZE)
            ->drawTo(par[k])
            ->push(300)
            ->master(LULU_PREV_MASTER)
            ->play()
            ->wait(); // WAIT END
    }
#endif
#if ARCA_N != 0
    for (int k = 0; k < ARCA_N; k++)
    {
        light->anim("test-arca", new Anim_dmx_test, ARCA_PATCH_SIZE)
            ->drawTo(arca[k])
            ->push(300)
            ->master(LULU_PREV_MASTER)
            ->play()
            ->wait(); // WAIT END
    }
#endif
#if P5_N != 0
    for (int k = 0; k < P5_N; k++)
    {
        light->anim("test-p5", new Anim_dmx_test, P5_PATCH_SIZE)
            ->drawTo(p5[k])
            ->push(300)
            ->master(LULU_PREV_MASTER)
            ->play()
            ->wait(); // WAIT END
    }
#endif

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

#if PAR_N != 0
    // ANIM par - presets
    light->anim("mem-par", new Anim_datathru, PAR_PATCH_SIZE)
        ->drawTo(par, PAR_N)
        ->bank(new BankPar)
        ->remote(true)
        ->mem(-1);
#endif
#if ARCA_N != 0
    // ANIM arca - presets
    light->anim("mem-arca", new Anim_datathru, ARCA_PATCH_SIZE)
        ->drawTo(arca, ARCA_N)
        ->bank(new BankArca)
        ->remote(true)
        ->mem(-1);
#endif
#if P5_N != 0
    // ANIM P5 - presets
    light->anim("mem-p5", new Anim_datathru, P5_PATCH_SIZE)
        ->drawTo(p5, P5_N)
        ->bank(new BankP5)
        ->remote(true)
        ->mem(-1);
#endif

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

#if PAR_N != 0
    // ANIM par - artnet
    light->anim("artnet-par", new Anim_datathru, PAR_PATCH_SIZE)
        ->drawTo(par, PAR_N)
        ->play();
#endif
#if ARCA_N != 0
    // ANIM arca - artnet
    light->anim("artnet-arca", new Anim_datathru, ARCA_PATCH_SIZE)
        ->drawTo(arca, ARCA_N)
        ->play();
#endif
#if P5_N != 0
    // ANIM p5 - artnet
    light->anim("artnet-p5", new Anim_datathru, P5_PATCH_SIZE)
        ->drawTo(p5, P5_N)
        ->play();
#endif

    // ARTNET: subscribe dmx frame
    K32_artnet::onDmx({.address = (1 + (k32->system->lightid() - 1) * PATCHSIZE),
                       .framesize = PATCHSIZE,
                       .callback = [](const uint8_t *data, int length)
                       {
    //    if (length >= PWM_N_CHAN)
    //        light->anim("artnet-pwm")->push(data, PWM_N_CHAN);

    // if (length >= PWM_N_CHAN + STRIP_PATCHSIZE)
    //     light->anim("artnet-strip")->push(&data[PWM_N_CHAN], STRIP_PATCHSIZE);

#if PAR_N != 0
                           if (length >= PAR_PATCH_SIZE)
                               light->anim("artnet-par")->push(data, PAR_PATCH_SIZE);
#endif
#if ARCA_N != 0
                           if (length >= PAR_PATCH_SIZE + ARCA_PATCH_SIZE)
                               light->anim("artnet-arca")->push(&data[PAR_PATCH_SIZE], ARCA_PATCH_SIZE);
#endif
#if P5_N != 0
                           if (length >= PAR_PATCH_SIZE + ARCA_PATCH_SIZE + P5_PATCH_SIZE)
                               light->anim("artnet-p5")->push(&data[PAR_PATCH_SIZE + ARCA_PATCH_SIZE], P5_PATCH_SIZE);
#endif
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
#if PAR_N != 0
    remote->setMacroMax(light->anim("mem-par")->bank()->size());
#endif
#if ARCA_N != 0
    remote->setMacroMax(light->anim("mem-arca")->bank()->size());
#endif
#if P5_N != 0
    remote->setMacroMax(light->anim("mem-p5")->bank()->size());
#endif
    // REMOTE: want macro
    k32->on("remote/macro", [](Orderz *order)
            {
#if PAR_N != 0
            light->anim("mem-par")  ->mem( order->getData(0)->toInt());
#endif
#if ARCA_N != 0
            light->anim("mem-arca")->mem( order->getData(0)->toInt());
#endif
#if P5_N != 0
            light->anim("mem-p5")  ->mem( order->getData(0)->toInt());
#endif
            remote->setState(REMOTE_MANU); 
            LOGF("mem: %d\n", order->getData(0)->toInt()); });

    // REMOTE: state changed
    k32->on("remote/state", [](Orderz *order)
            {
            remoteState stateR = (remoteState) order->getData(0)->toInt();

            // AUTO
            if (stateR == REMOTE_AUTO)
            {
#if PAR_N != 0
                light->anim("mem-par")->stop();
                light->anim("artnet-par")->play();
#endif
#if ARCA_N != 0
                light->anim("mem-arca")->stop();
                light->anim("artnet-arca")->play();
#endif
#if P5_N != 0
                light->anim("mem-p5")->stop();
                light->anim("artnet-p5")->play();
#endif
                
                LOG("REMOTE: -> Mode AUTO");
            }

            // MANU
            else if (stateR == REMOTE_MANU || stateR == REMOTE_MANU_LAMP || stateR == REMOTE_MANU_STM)
            {

#if P5_N != 0
delayMicroseconds(22668); // temps d'une trame DMX permet de ne pas avoir de conflit
                light->anim("artnet-p5")->stop();
                light->anim("mem-p5")->play();
#endif
#if ARCA_N != 0
delayMicroseconds(22668); // temps d'une trame DMX permet de ne pas avoir de conflit
                light->anim("artnet-arca")->stop();
                light->anim("mem-arca")->play();
                delay(100);
#endif
#if PAR_N != 0
delayMicroseconds(22668); // temps d'une trame DMX permet de ne pas avoir de conflit
                light->anim("artnet-par")->stop();
                light->anim("mem-par")->play();
#endif
                LOG("REMOTE: -> Mode MANU");
            } });
}
