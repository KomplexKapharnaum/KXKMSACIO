
#define L_NAME "Dmx_strobe" // a tester

#define VERSION_STROBE 2 // 1=strobe rgb 16 ch 5 division 2=strobe rgb 17 ch 4 division
#define STROBE_N 4 // nombre de strobe

#define ARTNET_ENABLE 1
#define ARTNET_DMXNODE 1


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

void setup_device()
{
    // ******  **  **  **  ******  **  **  *****   ******   *****
    // **           *  *     **    **  **  **  **  **      **
    // ****    **    **      **    **  **  *****   ****    ******
    // **      **   *  *     **    **  **  **  **  **          **
    // **      **  **  **    **     ****   **  **  ******  *****
    //
    // FIXTURES

    // STROBE fixtures
    K32_fixture *strobes[STROBE_N] = {nullptr};
    for (int k = 0; k < STROBE_N; k++)
        strobes[k] = new K32_dmxfixture(dmx, 1 + 20 * k, STROBE_PATCHSIZE); // Str 1 : 21 ,Str 2 : 38 ,Str 3 : 55 ,Str 4 : 72
    light->addFixtures(strobes, STROBE_N);

    //  ******  *****   ******  ***  **  ******  ******
    //  **  **  **  **    **    ***  **  **        **
    //  ******  *****     **    ** * **  ****      **
    //  **  **  **  **    **    **  ***  **        **
    //  **  **  **  **    **    **   **  ******    **
    //
    // ARTNET

    // ANIM strobes
    light->anim("mem-strobe", new Anim_datathru, STROBE_PATCHSIZE)
        ->drawTo(strobes, STROBE_N)
        ->bank(new BankStrobe)
        ->remote(true)
        ->push(0)
        ->play();

    // ANIM strobes - artnet
    light->anim("artnet-strobe", new Anim_dmx_strip, STROBE_PATCHSIZE)
        ->drawTo(strobes, STROBE_N)
        ->play();

    // ARTNET: subscribe dmx frame
    int memSize = light->anim("mem-strobe")->bank()->preset_size();

    K32_artnet::onDmx({
        .address = (1 + (light->id() - 1) * memSize),
        .framesize = memSize,
        .callback = [](const uint8_t *data, int length)
            {
                light->anim("artnet-strobe")->push(data, length);
            }
        });

    //  ***  **   ****      **       **  **  ****** **
    //  ***  **  **  **     **       **      **
    //  ** * **  **  **     **   *   **  **  ****   **
    //  **  ***  **  **      *  * *  *   **  **     **
    //  **   **   ****        **   **    **  **     **
    //
    // NOWIFI

    // EVENT: wifi lost
    // wifi->onDisconnect([&]()
    // {
    //     LOG("WIFI: connection lost..");
    //     //  light->anim("artnet-strip")->push(MEM_NO_WIFI, LULU_PATCHSIZE);
    //     light->anim("artnet-strip")->push(0); // @master 0
    // });

    //  *****   ******  ***   ***   ****   ******  ******
    //  **  **  **      ***   ***  **  **    **    **
    //  *****   ****    ** * * **  **  **    **    ****
    //  **  **  **      **  *  **  **  **    **    **
    //  **  **  ******  **     **   ****     **    ******
    //
    // REMOTE

    remote->setMacroMax(light->anim("mem-strobe")->bank()->size());

    k32->on("remote/macro", [](Orderz *order)
        {
            light->anim("mem-strobe")->mem( order->getData(0)->toInt());
            remote->setState(REMOTE_MANU); 
            LOGF("mem-strobe: %d\n", order->getData(0)->toInt());
        });

    k32->on("remote/state", [](Orderz *order){

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
