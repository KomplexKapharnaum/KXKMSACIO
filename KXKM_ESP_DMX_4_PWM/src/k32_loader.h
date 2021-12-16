
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

#include <hardware/K32_pwm.h>
K32_pwm* pwm = nullptr;

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

    //////////////////////////////////////// K32_lib ////////////////////////////////////
    k32 = new K32();

    //////////////////////////////////////// K32 hardware ////////////////////////////////////
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

    k32->on("stm32/btn-click", [](Orderz* order){
        remote->stmNext();
    });
    k32->on("atom/btn-click", [](Orderz* order){
        remote->stmNext();
    });



    // PWM
    pwm = new K32_pwm(k32);
    for (int k = 0; k < PWM_N_CHAN; k++)
        if (PWM_PIN[k32->system->hw()][k] > 0) // TODO: allow -1 pin but disable output
            pwm->attach(PWM_PIN[k32->system->hw()][k]);

    /////////////////////////////////////////////// LIGHT //////////////////////////////////////

    light = new K32_light(k32);
    light->loadprefs();
    
    dmx = new K32_dmx(DMX_PIN[k32->system->hw()], DMX_OUT);    

    init_lights();


    /////////////////////////////////////////////// NAME //////////////////////////////////////

    String nodeName = L_NAME;
    // if (LULU_STRIP_TYPE == LED_SK6812_V1)         nodeName += "-SK";
    // else if (LULU_STRIP_TYPE == LED_SK6812W_V1)   nodeName += "-SKW";
    // else                                          nodeName += "-WS";
    nodeName += "-" + String(light->id()) + "-v" + String(LULU_VER);

    LOG("\nNAME:   " + nodeName );
    LOGF("CHANNEL: %d\n\n", k32->system->channel());
    
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
        #ifdef ARTNET_ENABLE
            artnet = new K32_artnet(k32, wifi, nodeName);
            artnet->loadprefs();
            artnet->start(); 

            K32_artnet::onFullDmx([](const uint8_t *data, int length)
            {
                // LOGF("ARTNET fullframe: %d \n", length);

                // Force Auto
                if (length > 511 && data[511] > 250) // data 512 = end dmx trame   
                    remote->setState(REMOTE_AUTO)->lock();

                // FULL NODE
                if (ARTNET_DMXNODE && dmx) 
                    dmx->setMultiple(data, length);
            });
        #endif


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

