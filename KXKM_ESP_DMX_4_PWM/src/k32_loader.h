
#include <K32.h> // https://github.com/KomplexKapharnaum/K32-lib
K32* k32 = nullptr;

#include <hardware/K32_stm32.h>
K32_stm32* stm32 = nullptr;

#include <hardware/K32_buttons.h>
K32_buttons* buttons = nullptr;

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

#include <K32_bluetooth.h>
K32_bluetooth* bt = nullptr;

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
    if (mcp) return mcp->state(14);
    else return true;
}

// K32 loader
//
void k32_setup() {

    //////////////////////////////////////// K32_lib ////////////////////////////////////
    k32 = new K32();
    // Serial.begin(115200, SERIAL_8N1);
    
    //////////////////////////////////////// K32 hardware ////////////////////////////////////
    // STM32
    #ifdef HW_ENABLE_STM32
        stm32 = new K32_stm32(k32, true);
    #endif

    // BUTTONS (GPIO)
    buttons = new K32_buttons(k32);
    if (k32->system->hw() >= 3) // ATOM
        buttons->add(39, "atom");

    // MCP 
    mcp = new K32_mcp(k32);
    if (mcp) {
        k32->on("mcp/press", [](Orderz* order){
            if (order->getData(0)->toInt() == 14 && strcmp(order->getData(1)->toStr(), "long") == 0) k32->system->reset();
        });
        k32->on("mcp/release", [](Orderz* order){
            if (order->getData(0)->toInt() == 14 && strcmp(order->getData(1)->toStr(), "long") == 0) k32->system->reset();
        });
    }

    // POWER
    power = new K32_power(stm32, LIPO, true);
    //power->setExternalCurrentSensor(HO10_P_SP33, CURRENT_PIN[k32->system->hw()], PWR_FAKE_CURRENT);  // TODO: test sensor
    if(mcp->ok) power->setMCPcalib(mcp);

    // Remote
    remote = new K32_remote(k32, mcp);

    k32->on("stm32/btn-click", [](Orderz* order){
        remote->stmNext();
    });


    // PWM
    pwm = new K32_pwm(k32);
    for (int k = 0; k < PWM_N_CHAN; k++)
        if (PWM_PIN[k32->system->hw()][k] > 0) // TODO: allow -1 pin but disable output
            pwm->attach(PWM_PIN[k32->system->hw()][k]);

    // /////////////////////////////////////////////// LIGHT //////////////////////////////////////

    light = new K32_light(k32);
    light->loadprefs();
    
    dmx = new K32_dmx(DMX_PIN[k32->system->hw()], DMX_OUT);    

    


    // /////////////////////////////////////////////// NAME //////////////////////////////////////

    String nodeName = String(L_NAME) + "-" + String(light->id()) + "-v" + String(LULU_VER);

    LOG("\nNAME:   " + nodeName );
    LOGF("CHANNEL: %d\n\n", k32->system->channel());
    LOGF("LIGHT ID: %d\n", light->id());
    
    /////////////////////////////////////////////// NETWORK //////////////////////////////////////

    ////////////////// WIFI MODE
    if (wifiMode()) 
    {
        // WIFI
        LOG("NETWORK: wifi");
        wifi = new K32_wifi(k32);
        wifi->setHostname(k32->system->name() + (nodeName != "") ? "-" + nodeName : "");


        // MQTT
        mqtt = new K32_mqtt(k32, wifi, stm32, light);
        

        // OSC
        osc = new K32_osc(k32, wifi, stm32);    // TODO: re-enable OSC
        

        //ARTNET
        #if ARTNET_ENABLE == 1
            artnet = new K32_artnet(k32, wifi, nodeName);
            artnet->loadprefs();
            artnet->start(); 

            K32_artnet::onFullDmx([](const uint8_t *data, int length)
            {
                // LOGF("Artnet frame %d\n", length);

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
    else {
        // BLUETOOTH
        LOG("NETWORK: bluetooth");
        
        bt = new K32_bluetooth(k32, "k32-" + String(k32->system->id()));

        // // TODO use event !
        // bt->onConnect([&]() {
        //     bt->send("Yo Rasta!");
        // });

    }
    
    ////////////////// RUN SPECIFIC DEVICE
    setup_device();


    ///////////////// BLINK READY
    uint8_t l[6] = {255,255,255,255,255,255};
    if (stm32) stm32->blink(l, 500);
}
