
#define L_NAME "Dmx_strobe" // a tester

#define VERSION_STROBE 2 // 1=strobe rgb 16 ch 5 division 2=strobe rgb 17 ch 4 division 3=strobe rgb 17 ch 4 division + fog 3 ch 

#if VERSION_STROBE == 1
#define STROBE_PATCHSIZE 16
#include "macro/Type/strobe/mem_strobe_dmx_mod_1.h"
#elif VERSION_STROBE == 2
#define STROBE_PATCHSIZE 17
#include "macro/Show/Service_Tech/mem_strobe_dmx_mod_2.h" // channel 2
#elif VERSION_STROBE == 3
#define STROBE_PATCHSIZE 20
// #include "macro/Type/strobe/mem_strobe_dmx_mod_2.h"
#include "macro/Show/Service_Tech/mem_strobe_dmx_mod_3.h" // channel 1
#endif

#define ARTNET_ENABLE 1

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

    // STROBE fixtures
    K32_fixture *strobe = new K32_dmxfixture(dmx, 1, STROBE_PATCHSIZE);     // Strobe en DMX 1
    light->addFixture(strobe);


    // .########..########..########..######..########.########..######.
    // .##.....##.##.....##.##.......##....##.##..........##....##....##
    // .##.....##.##.....##.##.......##.......##..........##....##......
    // .########..########..######....######..######......##.....######.
    // .##........##...##...##.............##.##..........##..........##
    // .##........##....##..##.......##....##.##..........##....##....##
    // .##........##.....##.########..######..########....##.....######.

    // ANIM strobes
    light->anim("mem-strobe", new Anim_datathru, STROBE_PATCHSIZE)
        ->drawTo(strobe)
        ->bank(new BankStrobe)
        ->remote(true)
        ->play();

    // ....###....########..########.##....##.########.########
    // ...##.##...##.....##....##....###...##.##..........##...
    // ..##...##..##.....##....##....####..##.##..........##...
    // .##.....##.########.....##....##.##.##.######......##...
    // .#########.##...##......##....##..####.##..........##...
    // .##.....##.##....##.....##....##...###.##..........##...
    // .##.....##.##.....##....##....##....##.########....##...
    //

    // ANIM strobes - artnet
    light->anim("artnet-strobe", new Anim_datathru, STROBE_PATCHSIZE)
        ->drawTo(strobe);

    // ARTNET: subscribe dmx frame
    K32_artnet::onDmx({.address = (1 + (k32->system->lightid() - 1) * 20),
                       .framesize = STROBE_PATCHSIZE,
                       .callback = [](const uint8_t *data, int length)
                       {
                           light->anim("artnet-strobe")->push(data, length);
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

    // SELECT MEM
    k32->on("remote/macro", [](Orderz *order)
    {
        light->anim("mem-strobe")->mem( order->getData(0)->toInt());
        remote->setState(REMOTE_MANU); 
        LOGF("mem-strobe: %d\n", order->getData(0)->toInt()); 
    });

    // CHANGE MODE
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
            light->anim("artnet-strobe")->stop();
            light->anim("mem-strobe")->play();
            LOG("REMOTE: -> Mode MANU");
        } 
    });
}
