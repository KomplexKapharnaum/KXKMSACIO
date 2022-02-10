
#define L_NAME "Sac"

#define LULU_STRIP_SIZE     120 
#define LULU_STRIP_TYPE     LED_SK6812W_V3               // Strip type

#define PWR_FAKE_CURRENT    12500

#include "macro/Type/4pwm/mem_4pwm.h"
#include "macro/Type/SK/mem_sk.h"


 
void setup_device() 
{
    //
    // FIXTURES 
    //

    // PWM fixture
    K32_fixture* dimmer = new K32_pwmfixture(pwm);
    light->addFixture( dimmer );


    // LED STRIPS fixtures
    K32_fixture* strips[LED_N_STRIPS] = {nullptr};
    for(int k=0; k<LED_N_STRIPS; k++)
        strips[k] = new K32_ledstrip(k, LEDS_PIN[k32->system->hw()][k], (led_types)LULU_STRIP_TYPE, LULU_STRIP_SIZE + 30);    
    light->addFixtures( strips, LED_N_STRIPS )
         ->copyFixture({strips[0], LULU_STRIP_SIZE, LULU_STRIP_SIZE + 18, strips[1], 0}); // jauge sortie 2

    //
    // TEST Sequence
    //

        // INIT TEST STRIPS
            light->anim( "test-strip", new Anim_test_strip, LULU_STRIP_SIZE )
                ->drawTo(strips, LED_N_STRIPS)
                ->push(300)
                ->master(LULU_PREV_MASTER)
                ->play();

        // PWM TEST
            light->anim( "test-pwm", new Anim_test_pwm, LULU_STRIP_SIZE )
                ->drawTo(dimmer)
                ->push(300)
                ->master(LULU_PREV_MASTER)
                ->play();

        // WAIT END
            light->anim("test-strip")->wait();
            light->anim("test-pwm")->wait();

    
    // 
    //  PRESETS
    // 

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


    //
    // MONITORING
    //

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
    

    // 
    // ARTNET
    //

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
            light->anim("artnet-strip")->push(data, min(sizeSK, length));
            // light->anim("artnet-pwm")->push(data, min(sizePWM,length)); // FIX
        }
    });
    

    //
    // NOWIFI
    //

    // EVENT: wifi lost
    // wifi->onDisconnect([&]()
    // {
    //     LOG("WIFI: connection lost..");
    //     //  light->anim("artnet-strip")->push(MEM_NO_WIFI, LULU_PATCHSIZE);
    //     light->anim("artnet-strip")->push(0); // @master 0
    // });


    //
    // REMOTE
    //

    remote->setMacroMax( light->anim("mem-strip")->bank()->size() );
    
    k32->on("remote/macro", [](Orderz* order){
        light->anim("mem-strip")->mem( order->getData(0)->toInt() );
        light->anim("mem-pwm")->mem( order->getData(0)->toInt() );
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
            light->anim("memprev-strip")->stop();
            light->anim("artnet-strip")->play();
            LOG("REMOTE: -> Mode AUTO");
        }

        // STM
        else if (stateR == REMOTE_MANU_STM)
        {
            light->anim("artnet-strip")->stop();
            light->anim("memprev-strip")->play();
            light->anim("mem-strip")->play();
            LOG("REMOTE: -> Mode STM");
        }

        // MANU
        else if (stateR == REMOTE_MANU || stateR == REMOTE_MANU_LAMP)
        {
            light->anim("artnet-strip")->stop();
            light->anim("mem-strip")->play();
            light->anim("memprev-strip")->play();
            LOG("REMOTE: -> Mode MANU");
        }

        // REMOTE LED
        light->anim("remote-strip")->push(stateR, remote->isLocked());
    });

}


#ifdef zzzzz

// // MEM ON BOOT
    #if (LULU_TYPE >= 20 || LULU_TYPE == 2 || LULU_TYPE == 6)
        // light->anim("artnet-strip")->push(MEM_NO_WIFI, LULU_PATCHSIZE);// settings set
        // light->anim("artnet-strip")->mod(new K32_mod_sinus)->at(2)->period(8500)->phase(0)->mini(-255)->maxi(255); // modulo
        // light->anim("artnet-strip")->push( MEM_SK[20], LULU_PATCHSIZE); // baro auto circulation elp
        // light->anim("artnet-strip")->mod(new K32_mod_sinus)->at(7)->period(8500)->mini(0)->maxi(45);// baro auto circulation elp
    #endif


// // ANIM dmx fixtures  - artnet
    light->anim("artnet-dmxfix", new Anim_datathru , DMXFIXTURE_PATCHSIZE / 4)->play();
    for (int k=0; k<DMX_N_FIXTURES; k++)
        if (dmxfixs[k]) light->anim("artnet-dmxfix")->attach(dmxfixs[k]);

    // ANIM dmx fixtures  - presets
    light->anim("mem-dmxfix", new Anim_datathru , DMXFIXTURE_PATCHSIZE / 4)
        ->bank(new BankSK)
        ->mem(-1)
        ->play();
    for (int k=0; k<DMX_N_FIXTURES; k++)
        if (dmxfixs[k]) light->anim("mem-dmxfix")->drawTo(dmxfixs[k]);



#include <fixtures/K32_dmxfixture.h>
K32_dmxfixture* dmxfixs[DMX_N_FIXTURES] = {nullptr};



//      CHARIOT             FLUO
    #if LULU_TYPE == 9 || LULU_TYPE == 40
        light->copyFixture({strips[0], 0, LULU_STRIP_SIZE, strips[1], 0}); // Clone

    //      STROBEDMX           PARDMX                                        
    #elif LULU_TYPE == 11 || LULU_TYPE == 12
        dmxfixs[0] = new K32_dmxfixture(dmx, DMXOUT_ADDR, DMXFIXTURE_PATCHSIZE);

    // ELP
    #elif LULU_TYPE == 50
        dmxfixs[0] = new K32_dmxfixture(dmx, DMXOUT_ADDR, DMXFIXTURE_PATCHSIZE);
        light->copyFixture({strips[0], 0, LULU_STRIP_SIZE, elp, 0});

    // LYRE
    #elif LULU_TYPE == 60
        int DMX_address = (1 + (light->id() - 1) * 32);  // DMX Offset = 32  =>  Lyre 1 addr=1 / Lyre 2 addr=33 / ...
        dmxfixs[0] = new K32_dmxfixture(dmx, DMX_address, DMXFIXTURE_PATCHSIZE);

    // OTHERS
    #else
        light->copyFixture({strips[0], LULU_STRIP_SIZE, LULU_STRIP_SIZE + 18, strips[1], 0}); // jauge sortie 2
        
    #endif

    // REGISTER dmxfixtures
    for (int k=0; k<DMX_N_FIXTURES; k++)
        if (dmxfixs[k]) light->addFixture(dmxfixs[k]);



    
// ARTNET: subscribe dmx frame
    #if LULU_TYPE == 60
        int FRAME_size = LYRE_PATCHSIZE + 9; // 9: MEM R G B W PWM1 PWM2 PWM3 PWM4
    #else
        int FRAME_size = LULU_PATCHSIZE;
    #endif
        int ARTNET_address = (1 + (light->id() - 1) * LULU_PATCHSIZE);

    artnet->onDmx( {
      .address    = ARTNET_address, 
      .framesize  = FRAME_size, 
      .callback   = [](const uint8_t *data, int length) 
      { 
        
        light->anim("artnet-strip")->push(data, min(length, LULU_PATCHSIZE));

        // LYRE
        #if LULUTYPE == 60
          if (length >= DMXFIXTURE_PATCHSIZE + 9)
          {
            const uint8_t *dataStrip = &data[DMXFIXTURE_PATCHSIZE];

            // MEM ou ARTNET FRAME
            if (dataStrip[0] > 0 && dataStrip[0] <= PRESET_COUNT)
              remote->stmSetMacro(dataStrip[0] - 1);
            else
            {
              int stripframe[LULU_PATCHSIZE] = {255, dataStrip[1], dataStrip[2], dataStrip[3], dataStrip[4], 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 255, dataStrip[5], dataStrip[6], dataStrip[7], dataStrip[8]};
              light->anim("artnet-strip")->push(stripframe, LULU_PATCHSIZE);
              remote->setState(REMOTE_AUTO);
            }
          }
        #endif

        // LOGINL("ARTFRAME: ");
        // LOGF("length=%d ", length);
        // for (int k = 0; k < length; k++)
        //   LOGF("%d ", data[k]);
        // LOG();
      }
    });


// EVENT: wifi lost
    wifi->onDisconnect([&]()
                       {
                         LOG("WIFI: connection lost..");

#if LULU_TYPE >= 20
      //  light->anim("artnet-strip")->push(MEM_NO_WIFI, LULU_PATCHSIZE);
#else
                         light->anim("artnet-strip")->push(0); // @master 0
#endif
                       });

#endif