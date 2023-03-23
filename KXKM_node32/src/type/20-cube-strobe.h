
#define L_NAME "Cube_Str" // a tester

#define VERSION_STROBE 2 // 1=strobe rgb 16 ch 5 division 2=strobe rgb 17 ch 4 division
#define STROBE_N 4       // nombre de strobe

#define ARTNET_ENABLE 1
#define ARTNET_DMXNODE 0

#if VERSION_STROBE == 1
#define STROBE_PATCHSIZE 16
#elif VERSION_STROBE == 2
#define STROBE_PATCHSIZE 17
#endif

#if VERSION_STROBE == 1
#include "macro/Type/strobe/mem_strobe_dmx_mod_1.h"
#elif VERSION_STROBE == 2
#include "macro/Type/strobe/mem_strobe_dmx_mod_2.h"
#endif

#include "macro/Type/4pwm/mem_4pwm.h"

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

    // STROBE fixtures
    K32_fixture *strobes[STROBE_N] = {nullptr};
    for (int k = 0; k < STROBE_N; k++)
        strobes[k] = new K32_dmxfixture(dmx, (1 + 20 * k) + PWM_N_CHAN, STROBE_PATCHSIZE); // Str 1 : 21 ,Str 2 : 38 ,Str 3 : 55 ,Str 4 : 72
    light->addFixtures(strobes, STROBE_N);

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
    // light->anim("test-strip", new Anim_test_strip, LULU_STRIP_SIZE)
    //     ->drawTo(strips, LED_N_STRIPS)
    //     ->push(300)
    //     ->master(LULU_PREV_MASTER)
    //     ->play();

    // PWM TEST
    light->anim("test-pwm", new Anim_test_pwm, PWM_N_CHAN)
        ->drawTo(dimmer)
        ->push(300)
        ->master(LULU_PREV_MASTER)
        ->play();

    // WAIT END
    // light->anim("test-strip")->wait();
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

    // // ANIM leds - presets
    // light->anim("mem-strip", new Anim_dmx_strip, LULU_STRIP_SIZE)
    //     ->drawTo(strips[0])
    //     ->bank(new BankSK)
    //     ->remote(true)
    //     ->mem(-1);

    // // ANIM leds - presets preview
    // light->anim("memprev-strip", new Anim_preview, LULU_PREV_SIZE, LULU_STRIP_SIZE + 8)
    //     ->drawTo(strips[0])
    //     ->bank(new BankSK_PREV) // TODO
    //     ->mem(-1)
    //     ->master(LULU_PREV_MASTER);

    // ANIM strobes
    light->anim("mem-strobe", new Anim_datathru, STROBE_PATCHSIZE)
        ->drawTo(strobes, STROBE_N)
        ->bank(new BankStrobe)
        ->remote(true)
        ->push(0)
        ->play();

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
    //
    // ARTNET

    // ANIM pwm - artnet
    light->anim("artnet-pwm", new Anim_datathru, PWM_N_CHAN)
        ->drawTo(dimmer)
        ->play();

    // ANIM strobes - artnet
    light->anim("artnet-strobe", new Anim_dmx_strip, STROBE_PATCHSIZE)
        ->drawTo(strobes, STROBE_N)
        ->play();

    // ARTNET: subscribe dmx frame
    int memSize = PWM_N_CHAN + STROBE_PATCHSIZE;

    K32_artnet::onDmx({.address = (1 + (k32->system->lightid() - 1) * memSize),
                       .framesize = memSize,
                       .callback = [](const uint8_t *data, int length)
                       {
                           if (length >= PWM_N_CHAN)
                               light->anim("artnet-pwm")->push(data, PWM_N_CHAN);

                           if (length >= PWM_N_CHAN + STROBE_PATCHSIZE)
                               light->anim("artnet-strobe")->push(&data[PWM_N_CHAN], STROBE_PATCHSIZE);
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

    remote->setMacroMax(light->anim("mem-strobe")->bank()->size());

    k32->on("remote/macro", [](Orderz *order)
            {
            light->anim("mem-strobe")->mem( order->getData(0)->toInt());
            light->anim("mem-pwm")->mem(order->getData(0)->toInt());
            remote->setState(REMOTE_MANU); 
            LOGF("mem-strobe: %d\n", order->getData(0)->toInt()); });

    k32->on("remote/state", [](Orderz *order)
            {
            remoteState stateR = (remoteState) order->getData(0)->toInt();

        // AUTO
        if (stateR == REMOTE_AUTO)
        {
            light->anim("mem-strobe")->stop();
            light->anim("artnet-strobe")->play();
            LOG("REMOTE: -> Mode AUTO");
        }

        // MANU
        else if (stateR == REMOTE_MANU || stateR == REMOTE_MANU_LAMP || stateR == REMOTE_MANU_STM)
        {
            light->anim("artnet-pwm")->stop();
            light->anim("mem-pwm")->play();

            light->anim("artnet-strobe")->stop();
            light->anim("mem-strobe")->play();

            LOG("REMOTE: -> Mode MANU");
        } });
}
