
#define L_NAME "Atom"

#define LULU_STRIP_SIZE     25                                  // 5 pour tester avec les jauges de monitoring
#define LULU_STRIP_TYPE     LED_WS2812_V1                       // Strip type

#define ARTNET_ENABLE   1

#include "macro/Type/4pwm/mem_4pwm.h" // defo
#include "macro/Type/SK/mem_sk.h"     // defo



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
        strips[k] = new K32_ledstrip(k, LEDS_PIN[k32->system->hw()][k], (led_types)LULU_STRIP_TYPE, LULU_STRIP_SIZE);    
    light->addFixtures( strips, LED_N_STRIPS );


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
        ->remote(true);

    // ANIM leds - presets
    light->anim("mem-strip", new Anim_dmx_strip, LULU_STRIP_SIZE)
        ->drawTo(strips, LED_N_STRIPS)
        ->bank(new BankSK)
        ->remote(true);
    

    // 
    // ARTNET
    //

    // ANIM pwm - artnet
    light->anim("artnet-pwm", new Anim_datathru, PWM_N_CHAN)
        ->drawTo(dimmer)
        ->play();

    // ANIM leds - artnet
    light->anim("artnet-strip", new Anim_dmx_strip, LULU_STRIP_SIZE)
        ->drawTo(strips, LED_N_STRIPS)
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

        remote->setState(REMOTE_MANU);
    });

    k32->on("remote/state", [](Orderz* order){

        remoteState stateR = (remoteState) order->getData(0)->toInt();

        // AUTO
        if (stateR == REMOTE_AUTO)
        {
            light->anim("mem-strip")->stop();
            light->anim("mem-pwm")->stop();

            light->anim("artnet-strip")->play();
            light->anim("artnet-pwm")->play();

            LOG("REMOTE: -> Mode AUTO");
        }

        // MANU
        else if (stateR == REMOTE_MANU || stateR == REMOTE_MANU_LAMP || stateR == REMOTE_MANU_STM)
        {
            light->anim("artnet-strip")->stop();
            light->anim("artnet-pwm")->stop();

            light->anim("mem-strip")->play();
            light->anim("mem-pwm")->play();

            LOG("REMOTE: -> Mode MANU");
        }
    });

    
}









#ifdef zzzzzzz


// 
// MEM ANIMATOR DATA ! modulateur relatif a la valeur du tableau
//
uint8_t MEM[PRESET_COUNT][LULU_PATCHSIZE] = {};
uint8_t MEM_NO_WIFI[LULU_PATCHSIZE] = {};


void init_mem()
{
  for (int n = 0 ; n < PRESET_COUNT ; n++)
   {
      for (int i = 0 ; i < SK_PRESET_SIZE ; i++) 
      {
           MEM[n][i] = MEM_SK[n][i];
           MEM_NO_WIFI[i] = MEM_SK_NO_WIFI[i];
      }
      for (int i = SK_PRESET_SIZE ; i < LULU_PATCHSIZE  ; i++) 
      {
           MEM[n][i]=MEM_PWM[n][i - SK_PRESET_SIZE];
           MEM_NO_WIFI[i] = MEM_PWM_NO_WIFI[i - SK_PRESET_SIZE];
      }
   }
}


// 
// APPLY MACRO WITH CUSTOM MODULATORS INTO anim
//
//{master , r  , g  , b  , w  ,pix mod , pix long , pix_pos , str_mod , str_speed , r_fond , g_fond , b_fond , w_fond , mirror_mod , zoom }
//{0      , 1  , 2  , 3  , 4  ,5       , 6        , 7       , 8       , 9         , 10     , 11     , 12     , 13     , 14         , 15   } adr + -1

void load_mem(K32_anim *anim, int macro) {

    // remove disposable modulators
    //
    anim->unmod();

    // push new data
    //
    anim->push(MEM[macro], LULU_PATCHSIZE);

    // add modulators
    //
    if (macro == 4)
    {
        anim->mod(new K32_mod_sinus)->at(1)->at(5)->at(8)->at(3)->at(7)->at(2)->at(6)->period(8500)->phase(0)->mini(-50)->maxi(255);
    }
    else if (macro == 6)
    {
        anim->mod(new K32_mod_pulse)->at(1)->at(2)->at(3)->at(7)->at(8)->at(6)->at(5)->param(1, 10)->period(500);
    }
    else if (macro == 9)
    {
        anim->mod(new K32_mod_sinus)->at(0)->mini(100)->maxi(255)->period(2000);
    }
    else if (macro == 10)
    {
        anim->mod(new K32_mod_sinus)->at(1)->at(2)->period(8500)->phase(0)->mini(0)->maxi(255);
    }
    else if (macro == 11)
    {
        anim->mod(new K32_mod_pulse)->at(2)->at(3)->param(1, 100)->period(7000);
    }
    else if (macro == 12)
    {
        anim->mod(new K32_mod_sinus)->at(1)->period(8500)->phase(0)->mini(0)->maxi(255);
        anim->mod(new K32_mod_sinus)->at(2)->period(8500)->phase(120)->mini(0)->maxi(255);
        anim->mod(new K32_mod_sinus)->at(3)->period(8500)->phase(240)->mini(0)->maxi(255);
    }
    else if (macro == 14)
    {
        anim->mod(new K32_mod_sinus)->at(0)->period(8500)->mini(38)->maxi(217);
    }
}

#endif