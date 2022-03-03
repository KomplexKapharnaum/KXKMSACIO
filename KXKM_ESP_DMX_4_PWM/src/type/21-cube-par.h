
#define L_NAME "Cube_Par" // a tester

#define PAR_N 1
#define PAR_PATCHSIZE 5

#define ARTNET_ENABLE 1
#define ARTNET_DMXNODE 0

#define PWM_ON_OFF 1

// #include "macro/Show/Baro/mem_pwm_baro_127.h" // cube 1 3 5 7 9
// #include "macro/Show/Baro/mem_cube_baro_127.h"

// // #include "macro/Show/Baro/mem_pwm_baro_125.h"   // cube 2 4 6 8 10
// // #include "macro/Show/Baro/mem_cube_baro_125.h"

#include "macro/Show/parlement/mem_4pwm_parlement.h"
#include "macro/Show/parlement/mem_parled_solo.h"

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

    // PAR fixtures
    K32_fixture *par[PAR_N] = {nullptr};
    for (int k = 0; k < PAR_N; k++)
        par[k] = new K32_dmxfixture(dmx, (1 + 20 * k) + PWM_N_CHAN, PAR_PATCHSIZE);
    light->addFixtures(par, PAR_N);

    // .########.########..######..########.....######..########..#######..##.....##.########.##....##..######..########
    // ....##....##.......##....##....##.......##....##.##.......##.....##.##.....##.##.......###...##.##....##.##......
    // ....##....##.......##..........##.......##.......##.......##.....##.##.....##.##.......####..##.##.......##......
    // ....##....######....######.....##........######..######...##.....##.##.....##.######...##.##.##.##.......######..
    // ....##....##.............##....##.............##.##.......##..##.##.##.....##.##.......##..####.##.......##......
    // ....##....##.......##....##....##.......##....##.##.......##....##..##.....##.##.......##...###.##....##.##......
    // ....##....########..######.....##........######..########..#####.##..#######..########.##....##..######..########

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
        ->remote(true);

    // ANIM par - presets
    light->anim("mem-par", new Anim_datathru, PAR_PATCHSIZE)
        ->drawTo(par, PAR_N)
        ->bank(new BankPar)
        ->remote(true)
        ->push(0);

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

    // ANIM par - artnet
    light->anim("artnet-par", new Anim_datathru, PAR_PATCHSIZE)
        ->drawTo(par, PAR_N)
        ->play();

    // ARTNET: subscribe dmx frame
    int patchSize = PWM_N_CHAN + PAR_PATCHSIZE;

    K32_artnet::onDmx({.address = (1 + (light->id() - 1) * patchSize),
                       .framesize = patchSize,
                       .callback = [](const uint8_t *data, int length)
                       {
                           if (length >= PWM_N_CHAN)
                               light->anim("artnet-pwm")->push(data, PWM_N_CHAN);

                           if (length >= PWM_N_CHAN + PAR_PATCHSIZE)
                               light->anim("artnet-par")->push(&data[PWM_N_CHAN], PAR_PATCHSIZE);
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
            light->anim("mem-par")->mem( order->getData(0)->toInt());
            light->anim("mem-pwm")->mem( order->getData(0)->toInt());
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

                light->anim("mem-par")->stop();
                light->anim("artnet-par")->play();
                
                LOG("REMOTE: -> Mode AUTO");
            }

            // MANU
            else if (stateR == REMOTE_MANU || stateR == REMOTE_MANU_LAMP || stateR == REMOTE_MANU_STM)
            {
                light->anim("artnet-pwm")->stop();
                light->anim("mem-pwm")->play();
                
                light->anim("artnet-par")->stop();
                light->anim("mem-par")->play();

                LOG("REMOTE: -> Mode MANU");
            } });
}
