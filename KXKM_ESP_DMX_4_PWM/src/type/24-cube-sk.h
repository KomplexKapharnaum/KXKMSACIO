#define L_NAME "Cube-sk"  // a tester 

#define LULU_STRIP_SIZE     120 
#define LULU_STRIP_TYPE     LED_SK6812W_V3               // Strip type


// #define ARTNET_DMXNODE 1

#include "macro/Type/SK/mem_sk.h"  // defo
// #include "macro/Show/larochelle/mem_sk_roch.h"
// #include "macro/Show/esch/mem_sk_esch.h"


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

    // PWM fixture
    K32_fixture *dimmer = new K32_pwmfixture(pwm);
    light->addFixture(dimmer);


    // LED STRIPS fixtures
    K32_fixture* strips[LED_N_STRIPS] = {nullptr};
    for(int k=0; k<LED_N_STRIPS; k++)
        strips[k] = new K32_ledstrip(k, LEDS_PIN[k32->system->hw()][k], (led_types)LULU_STRIP_TYPE, LULU_STRIP_SIZE + 30);    
    light->addFixtures( strips, LED_N_STRIPS )
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
    light->anim( "test-strip", new Anim_test_strip, LULU_STRIP_SIZE )
        ->drawTo(strips, LED_N_STRIPS)
        ->push(300)
        ->master(LULU_PREV_MASTER)
        ->play();

    // PWM TEST
    light->anim("test-pwm", new Anim_test_pwm, LULU_STRIP_SIZE)
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

    // ANIM pwm - presets
    light->anim("mem-pwm", new Anim_datathru, PWM_N_CHAN)
        ->drawTo(dimmer)
        ->bank(new BankPWM)
        ->remote(true)
        ->mem(-1);

    // ANIM leds - presets
    light->anim("mem-strip", new Anim_dmx_strip, LULU_STRIP_SIZE)
        ->drawTo(strips[0])
        ->bank(new BankSK)
        ->remote(true)
        ->mem(-1);


    // ANIM leds - presets preview
    light->anim("memprev-strip", new Anim_preview, LULU_PREV_SIZE, LULU_STRIP_SIZE + 8)
        ->drawTo(strips[0])
        ->bank(new BankSK_PREV)   // TODO
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

    // ANIM pwm - artnet
    light->anim("artnet-pwm", new Anim_datathru, PWM_N_CHAN)
        ->drawTo(dimmer)
        ->play();


    // ANIM leds - artnet
    light->anim("artnet-strip", new Anim_dmx_strip, LULU_STRIP_SIZE)
        ->drawTo(strips[0])
        ->play();

    // ARTNET: subscribe dmx frame
    int FRAME_size = light->anim("mem-strip")->bank()->preset_size() + light->anim("mem-pwm")->bank()->preset_size();

    K32_artnet::onDmx( {
        .address    = (1 + (light->id() - 1) * FRAME_size), 
        .framesize  = FRAME_size, 
        .callback   = [](const uint8_t *data, int length) 
        { 
            int sizeSK = light->anim("mem-strip")->bank()->preset_size();
            int sizePWM = light->anim("mem-pwm")->bank()->preset_size();

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

    remote->setMacroMax( light->anim("mem-strip")->bank()->size() );
    
    k32->on("remote/macro", [](Orderz* order){
        light->anim("mem-strip")->mem( order->getData(0)->toInt() );
        light->anim("mem-pwm")->mem(order->getData(0)->toInt());
    });

    k32->on("remote/preview", [](Orderz* order){
        light->anim("memprev-strip")->mem( order->getData(0)->toInt() );
    });

    k32->on("remote/lock", [](Orderz* order){
        light->anim("remote-strip")->push(remote->getState(), true);
    });

    k32->on("remote/unlock", [](Orderz* order){
        light->anim("remote-strip")->push(remote->getState(), false);
    });

    k32->on("remote/state", [](Orderz* order){

        remoteState stateR = (remoteState) order->getData(0)->toInt();

        // AUTO
        if (stateR == REMOTE_AUTO)
        {
            light->anim("mem-strip")->stop();
            light->anim("mem-pwm")->stop();
            light->anim("memprev-strip")->stop();
            light->anim("artnet-strip")->play();
            light->anim("artnet-pwm")->play();
            LOG("REMOTE: -> Mode AUTO");
        }

        // STM
        else if (stateR == REMOTE_MANU_STM)
        {
            light->anim("artnet-strip")->stop();
            light->anim("artnet-pwm")->stop();
            light->anim("memprev-strip")->play();
            light->anim("mem-pwm")->play();
            light->anim("mem-strip")->play();
            LOG("REMOTE: -> Mode STM");
        }

        // MANU
        else if (stateR == REMOTE_MANU || stateR == REMOTE_MANU_LAMP)
        {
            light->anim("artnet-strip")->stop();
            light->anim("artnet-pwm")->stop();
            light->anim("mem-strip")->play();
            light->anim("mem-pwm")->play();
            light->anim("memprev-strip")->play();
            LOG("REMOTE: -> Mode MANU");
        }

        // REMOTE LED
        light->anim("remote-strip")->push(stateR, remote->isLocked());
    });

}
