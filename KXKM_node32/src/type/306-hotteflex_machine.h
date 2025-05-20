#define L_NAME "MACHINE" // a tester
#define LULU_STRIP_TYPE LED_SK6812W_V3 // Strip type

// #define ARTNET_DMXNODE 1
// #define PWM_ON_OFF 1

// #include "macro/Type/SK/mem_sk.h" // defo
#include "macro/Show/kontact/mem_machine_sk.h" // Kontact
// #include "macro/Show/larochelle/mem_sk_roch.h"
// #include "macro/Show/esch/mem_sk_esch.h"

#ifdef PWM_ON_OFF
#include "macro/Type/4pwm/mem_4pwm.h"
#endif

void setup_device()
{   
    // DIP SWITCH SETTINGS
    // 1. ON = DMX / OFF = ARTNET
    // 3. ON = Disable presets / OFF = Enable presets

    const int DMX_ARTNET = dipswitch->dip1();
    const int PRESETS_ENABLE = !dipswitch->dip3();
    
    if (DMX_ARTNET) LOG("DIP1 = 1 : DMX only, Artnet disabled..");
    else LOG("DIP1 = 0 : Artnet enabled..");

    if (PRESETS_ENABLE) LOG("DIP3 = 0 : Presets enabled..");
    else LOG("DIP3 = 1 : Presets disabled..");

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

    int PIXSIZE = k32->system->pixsize(); // web config

    for (int k = 0; k < LED_N_STRIPS; k++)
        strips[k] = new K32_ledstrip(k, LEDS_PIN[k32->system->hw()][k], (led_types)LULU_STRIP_TYPE, PIXSIZE);

    light->addFixtures(strips, LED_N_STRIPS)
        ->copyFixture({strips[0], 0, PIXSIZE, strips[1], 0}); //  copie strip0 sur strip1

       
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

    // WAIT END
    light->anim("test-strip")->wait();

    #ifdef PWM_ON_OFF
    // PWM TEST
    light->anim("test-pwm", new Anim_test_pwm, PIXSIZE)
        ->drawTo(dimmer)
        ->push(300)
        ->master(LULU_PREV_MASTER)
        ->play();
    
    // WAIT END
    light->anim("test-pwm")->wait();
    #endif


    // ....###....########..########.##....##.########.########
    // ...##.##...##.....##....##....###...##.##..........##...
    // ..##...##..##.....##....##....####..##.##..........##...
    // .##.....##.########.....##....##.##.##.######......##...
    // .#########.##...##......##....##..####.##..........##...
    // .##.....##.##....##.....##....##...###.##..........##...
    // .##.....##.##.....##....##....##....##.########....##...

    // ARTNET: subscribe artnet/dmx frame size
    int FRAME_size = 20;
    int DMX_ADDRESS = (1 + (k32->system->lightid() - 1) * FRAME_size);  

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
    
    dmxsub subscription = {
        .address = DMX_ADDRESS,
        .framesize = FRAME_size,
        .callback = [](const uint8_t *data, int length)
        {       
                //int sizeSK = light->anim("mem-strip")->bank()->preset_size();
                #ifdef PWM_ON_OFF
                int sizePWM = light->anim("mem-pwm")->bank()->preset_size();
                #endif

                // force
                int sizeSK = 20;

                // LOGINL("ARTFRAME: "); LOGF("length=%d ", length); for (int k = 0; k < length; k++) LOGF("%d ", data[k]); LOG();
                light->anim("artnet-strip")->push(data, min(sizeSK, length));
                #ifdef PWM_ON_OFF
                light->anim("artnet-pwm")->push(data, min(sizePWM, length)); // FIX
                #endif
        }};

    //
    // DMX ONLY !
    if (DMX_ARTNET) K32_dmx::onDmx(subscription);
    
    //
    // ARTNET
    else K32_artnet::onDmx(subscription);


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

    // .########..########..########..######..########.########..######.
    // .##.....##.##.....##.##.......##....##.##..........##....##....##
    // .##.....##.##.....##.##.......##.......##..........##....##......
    // .########..########..######....######..######......##.....######.
    // .##........##...##...##.............##.##..........##..........##
    // .##........##....##..##.......##....##.##..........##....##....##
    // .##........##.....##.########..######..########....##.....######.
    //
    //  PRESETS

    if (PRESETS_ENABLE)
    {
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
    }

    // .########..########.##.....##..#######..########.########
    // .##.....##.##.......###...###.##.....##....##....##......
    // .##.....##.##.......####.####.##.....##....##....##......
    // .########..######...##.###.##.##.....##....##....######..
    // .##...##...##.......##.....##.##.....##....##....##......
    // .##....##..##.......##.....##.##.....##....##....##......
    // .##.....##.########.##.....##..#######.....##....########
    //
    // REMOTE
    
    if (PRESETS_ENABLE)
    {
        remote->setMacroMax(light->anim("mem-strip")->bank()->size());

        k32->on("remote/macro", [](Orderz *order)
                {
                    light->anim("mem-strip")->mem(order->getData(0)->toInt());
                    #ifdef PWM_ON_OFF
                    light->anim("mem-pwm")->mem(order->getData(0)->toInt());
                    #endif
                });

        k32->on("remote/state", [](Orderz *order)
                {

                    remoteState stateR = (remoteState) order->getData(0)->toInt();

                    // AUTO
                    if (stateR == REMOTE_AUTO)
                    {
                        light->anim("mem-strip")->stop();
                        light->anim("artnet-strip")->play();
                        LOG("REMOTE: -> Mode AUTO");
                    }

                    // STM
                    else if (stateR == REMOTE_MANU_STM)
                    {
                        light->anim("artnet-strip")->stop();
                        light->anim("mem-strip")->play();
                        LOG("REMOTE: -> Mode STM");
                    }

                    // MANU
                    else if (stateR == REMOTE_MANU || stateR == REMOTE_MANU_LAMP)
                    {
                        light->anim("artnet-strip")->stop();
                        light->anim("mem-strip")->play();
                        LOG("REMOTE: -> Mode MANU");
                    }

            });

            remote->stmNext();
    }
}
