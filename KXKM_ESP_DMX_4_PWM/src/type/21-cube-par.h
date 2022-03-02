
#define L_NAME "Cube_Par" // a tester

#define PAR_N            1
#define PAR_PATCHSIZE    5

#define ARTNET_ENABLE 1
#define ARTNET_DMXNODE 1


#include "macro/Show/parlement/mem_parled_solo.h"

#define PWM_ON_OFF 1

#ifdef PWM_ON_OFF
#include "macro/Show/parlement/mem_4pwm_parlement.h"
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

        // PWM fixture
    K32_fixture *dimmer = new K32_pwmfixture(pwm);
    light->addFixture(dimmer);

    // STROBE fixtures
    K32_fixture *strobes[STROBE_N] = {nullptr};
    for (int k = 0; k < STROBE_N; k++)
        strobes[k] = new K32_dmxfixture(dmx, 1 + 20 * k, STROBE_PATCHSIZE); // Str 1 : 21 ,Str 2 : 38 ,Str 3 : 55 ,Str 4 : 72
    light->addFixtures(strobes, STROBE_N);

    //  ******  ******   *****  ******     *****  ******   ****   **  **  ******  ***  **  ****** ******
    //    **    **      **        **      **      **      **  **  **  **  **      ***  **  **     **
    //    **    ****    ******    **      ******  ****    ** ***  **  **  ****    ** * **  **     ****
    //    **    **          **    **          **  **      ** ***  **  **  **      **  ***  **     **
    //    **    ******  *****     **      *****   ******   *** *   ****   ******  **   **  ****** ******
    //
    // TEST Sequence

    // INIT TEST STRIPS
    // light->anim("test-strip", new Anim_test_strip, LULU_STRIP_SIZE)
    //     ->drawTo(strips, LED_N_STRIPS)
    //     ->push(300)
    //     ->master(LULU_PREV_MASTER)
    //     ->play();

    // PWM TEST
    light->anim("test-pwm", new Anim_test_pwm, LULU_STRIP_SIZE)
        ->drawTo(dimmer)
        ->push(300)
        ->master(LULU_PREV_MASTER)
        ->play();


    // WAIT END
    // light->anim("test-strip")->wait();
    light->anim("test-pwm")->wait();

    //  ******  *****   ******  ***  **  ******  ******
    //  **  **  **  **    **    ***  **  **        **
    //  ******  *****     **    ** * **  ****      **
    //  **  **  **  **    **    **  ***  **        **
    //  **  **  **  **    **    **   **  ******    **
    //
    // ARTNET

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
    light->anim("mem-par", new Anim_datathru, STROBE_PATCHSIZE)
        ->drawTo(strobes, STROBE_N)
        ->bank(new BankStrobe)
        ->remote(true)
        ->push(0)
        ->play();

    // ANIM strobes - artnet
    light->anim("artnet-par", new Anim_dmx_strip, STROBE_PATCHSIZE)
        ->drawTo(strobes, STROBE_N)
        ->play();

    // ARTNET: subscribe dmx frame
    int memSize = light->anim("mem-par")->bank()->preset_size() + light->anim("mem-pwm")->bank()->preset_size();

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
            light->anim("mem-pwm")->mem(order->getData(0)->toInt());
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
