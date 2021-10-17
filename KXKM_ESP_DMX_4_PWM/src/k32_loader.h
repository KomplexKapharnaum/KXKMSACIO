#include <Preferences.h>
Preferences prefs;

#include <K32.h> // https://github.com/KomplexKapharnaum/K32-lib
K32* k32 = nullptr;

#include <hardware/K32_stm32.h>
K32_stm32* stm32 = nullptr;

#include <hardware/K32_mcp.h>
K32_mcp* mcp = nullptr;

#include <hardware/K32_power.h>
K32_power* power = nullptr;

#include <hardware/K32_remote.h>
K32_remote* remote = nullptr;

#include <K32_wifi.h>
K32_wifi* wifi = nullptr;

// #include <K32_bluetooth.h>
// K32_bluetooth* bt = nullptr;
// TODO: re-enable BT

#include <K32_osc.h>
K32_osc* osc = nullptr;

#include <K32_mqtt.h>
K32_mqtt* mqtt = nullptr;

#include <K32_artnet.h>
K32_artnet* artnet = nullptr;

#include <K32_light.h>
K32_light* light = nullptr;

#include "K32_dmx.h"
K32_dmx* dmx = nullptr;

#include <fixtures/K32_ledstrip.h>
K32_ledstrip* strip[LED_N_STRIPS] = {nullptr};

#include <fixtures/K32_dmxfixture.h>
K32_dmxfixture* fixs[DMX_N_FIXTURES] = {nullptr};


#include "settings.h"

// CHECK MCP SWITCH to select Wifi or BT
//
bool wifiMode() {
    if (mcp) {
        mcp->input(14);
        return mcp->state(14);
    }
    else return true;
}

// K32 loader
//
void k32_setup() {

    prefs.begin("k32-settings", false);

    #ifdef LULU_ID
        prefs.putUInt("LULU_id", LULU_ID);
        LULU_id = LULU_ID;
    #else
        LULU_id = prefs.getUInt("LULU_id", 1);
    #endif


    #ifdef LULU_UNI
        prefs.putUInt("LULU_uni", LULU_UNI);
        LULU_uni = LULU_UNI;
    #else
        LULU_uni = prefs.getUInt("LULU_uni", 0);
    #endif


    // NAME
    nodeName = L_NAME;

    if (LULU_STRIP_TYPE == LED_SK6812_V1)         nodeName += "-SK";
    else if (LULU_STRIP_TYPE == LED_SK6812W_V1)   nodeName += "-SKW";
    else                                          nodeName += "-WS";

    nodeName += "-" + String(LULU_id) + "-v" + String(LULU_VER);

    prefs.end();

    //////////////////////////////////////// K32_lib ////////////////////////////////////
    k32 = new K32();

    //////////////////////////////////////// K32 modules ////////////////////////////////////
    // STM32
    #ifdef HW_ENABLE_STM32
        stm32 = new K32_stm32(k32, true);
    #endif

    // MCP
    mcp = new K32_mcp(MCP_PIN[k32->system->hw()]);

    // POWER
    power = new K32_power(stm32, LIPO, true);
    //power->setExternalCurrentSensor(HO10_P_SP33, CURRENT_PIN[k32->system->hw()], PWR_FAKE_CURRENT);  // TODO: test sensor
    if(mcp->ok) power->setMCPcalib(mcp);

    // Remote
    remote = new K32_remote(k32, mcp);

    /////////////////////////////////////////////// LIGHT //////////////////////////////////////

    light = new K32_light(k32);

    // LED STRIPS
    for(int k=0; k<LED_N_STRIPS; k++) { 
        strip[k] = new K32_ledstrip(k, LEDS_PIN[k32->system->hw()][k], (led_types)LULU_STRIP_TYPE, LULU_STRIP_SIZE + 30);
        light->addFixture( strip[k] );
    }

    // PWM
    for (int k = 0; k < PWM_N_CHAN; k++)
        if (PWM_PIN[k32->system->hw()][k] > 0) // TODO: allow -1 pin but disable output
            light->pwm->attach(PWM_PIN[k32->system->hw()][k]);  // TODO: convert PWM into DIMMER fixture
    
    // DMX
    dmx = new K32_dmx(DMX_PIN[k32->system->hw()], DMX_OUT);


    //      CHARIOT             FLUO
    #if LULU_TYPE == 9 || LULU_TYPE == 40
        light->copyFixture({strip[0], 0, LULU_STRIP_SIZE, strip[1], 0}); // Clone

    //      STROBEDMX           PARDMX                                        
    #elif LULU_TYPE == 11 || LULU_TYPE == 12
        fixs[0] = new K32_dmxfixture(dmx, DMXOUT_ADDR, DMXFIXTURE_PATCHSIZE);

    // ELP
    #elif LULU_TYPE == 50
        fixs[0] = new K32_dmxfixture(dmx, DMXOUT_ADDR, DMXFIXTURE_PATCHSIZE);
        light->copyFixture({strip[0], 0, LULU_STRIP_SIZE, elp, 0});

    // LYRE
    #elif LULU_TYPE == 60
        int DMX_address = (1 + (LULU_id - 1) * 32);  // DMX Offset = 32  =>  Lyre 1 addr=1 / Lyre 2 addr=33 / ...
        fixs[0] = new K32_dmxfixture(dmx, DMX_address, DMXFIXTURE_PATCHSIZE);

    // OTHERS
    #else
        light->copyFixture({strip[0], LULU_STRIP_SIZE, LULU_STRIP_SIZE + 18, strip[1], 0}); // jauge sortie 2
        
    #endif

    // REGISTER dmxfixtures
    for (int k=0; k<DMX_N_FIXTURES; k++)
        if (fixs[k]) light->addFixture(fixs[k]);

    // LOAD MACRO AND PRESETS
    init_mem();

    /////////////////////////////////////////////// NETWORK //////////////////////////////////////

    ////////////////// WIFI MODE
    if (wifiMode()) 
    {
        // WIFI
        LOG("NETWORK: wifi");
        wifi = new K32_wifi(k32);
        wifi->setHostname(k32->system->name() + (nodeName != "") ? "-" + nodeName : "");


        // MQTT
        mqtt = new K32_mqtt(k32, wifi, stm32);
        

        // OSC
        // osc = new K32_osc(k32, wifi);    // TODO: re-enable OSC
        

        //ARTNET
        artnet = new K32_artnet(k32, nodeName, LULU_uni); 

        artnet->onFullDmx([](const uint8_t *data, int length)
        {
            // Force Auto
            if (length > 511 && data[511] > 250) // data 512 = end dmx trame
            {
            remote->setState(REMOTE_AUTO);
            remote->lock();
            }
            // LOGF("ARTNET fullframe: %d \n", length);

            // FULL NODE
            if (ARTNET_DMXNODE && dmx) 
            dmx->setMultiple(data, length);
        });


    }
    
    ////////////////// BLUETOOTH MODE
    // TODO: re-enable BT
    // else {
    //     LOG("NETWORK: bluetooth");
        
    //     bt = new K32_bluetooth(k32, "k32-" + String(k32->system->id()));

    //     bt->onConnect([&]() {
    //         bt->send("Yo Rasta!");
    //     });
    // }



}

