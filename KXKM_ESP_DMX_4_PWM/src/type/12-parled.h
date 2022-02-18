
#define L_NAME "Dmx_parled" // a tester

#define VERSION_PAR 2 // 1= fullkolor 2= minikolor
#define PAR_N 4 // nombre de par

#define ARTNET_ENABLE 1
#define ARTNET_DMXNODE 1


#if VERSION_PAR == 1
#define PAR_PATCHSIZE 5
#elif VERSION_PAR == 2
#define PAR_PATCHSIZE 9
#endif


#if VERSION_PAR == 1
#include "macro/Type/parled/mem_par_dmx_mod_1.h"
#elif VERSION_PAR == 2
#include "macro/Type/minikolor/mem_minikolor_dmx_mod_2.h"
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

    // PAR fixtures
    K32_fixture *pars[PAR_N] = {nullptr};
    for (int k = 0; k < PAR_N; k++)
        pars[k] = new K32_dmxfixture(dmx, 1 + 20 * k, PAR_PATCHSIZE); // Str 1 : 21 ,Str 2 : 38 ,Str 3 : 55 ,Str 4 : 72
    light->addFixtures(pars, PAR_N);

    //  ******  *****   ******  ***  **  ******  ******
    //  **  **  **  **    **    ***  **  **        **
    //  ******  *****     **    ** * **  ****      **
    //  **  **  **  **    **    **  ***  **        **
    //  **  **  **  **    **    **   **  ******    **
    //
    // ARTNET

    // ANIM pars
    light->anim("mem-par", new Anim_datathru, PAR_PATCHSIZE)
        ->drawTo(pars, PAR_N)
        ->bank(new BankPars)
        ->remote(true)
        ->push(0)
        ->play();

    // ANIM pars - artnet
    light->anim("artnet-par", new Anim_dmx_strip, PAR_PATCHSIZE)
        ->drawTo(pars, PAR_N)
        ->play();

    // ARTNET: subscribe dmx frame
    int memSize = light->anim("mem-par")->bank()->preset_size();

    K32_artnet::onDmx({
        .address = (1 + (light->id() - 1) * memSize),
        .framesize = memSize,
        .callback = [](const uint8_t *data, int length)
            {
                light->anim("artnet-par")->push(data, length);
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

    remote->setMacroMax(light->anim("mem-par")->bank()->size());

    k32->on("remote/macro", [](Orderz *order)
        {
            light->anim("mem-par")->mem( order->getData(0)->toInt());
            remote->setState(REMOTE_MANU); 
            LOGF("mem-par: %d\n", order->getData(0)->toInt());
        });

    k32->on("remote/state", [](Orderz *order){

        remoteState stateR = (remoteState) order->getData(0)->toInt();

        // AUTO
        if (stateR == REMOTE_AUTO)
        {
            light->anim("mem-par")->stop();
            light->anim("artnet-par")->play();
            LOG("REMOTE: -> Mode AUTO");
        }

        // MANU
        else if (stateR == REMOTE_MANU || stateR == REMOTE_MANU_LAMP || stateR == REMOTE_MANU_STM)
        {
            light->anim("artnet-par")->stop();
            light->anim("mem-par")->play();
            LOG("REMOTE: -> Mode MANU");
        }
    });

}
