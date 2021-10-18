

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

#include <fixtures/K32_ledstrip.h>
K32_ledstrip* strip[LED_N_STRIPS] = {nullptr};

#include <fixtures/K32_elp.h>
K32_elp* elp = nullptr;

#include <fixtures/K32_lyreaudio.h>
K32_lyreaudio* lyreaudio = nullptr;

#include <fixtures/K32_pardmx.h>
K32_pardmx* pardmx = nullptr;

#include <fixtures/K32_node.h>
K32_node* node = nullptr;

#include <fixtures/K32_strobedmx.h>
K32_strobedmx* strobedmx = nullptr;

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

    //////////////////////////////////////// K32 modules ////////////////////////////////////
    // STM32
    #ifdef HW_ENABLE_STM32
        stm32 = new K32_stm32(k32, true);
    #endif

    // MCP
    mcp = new K32_mcp(MCP_PIN[k32->system->hw()]);
    // TODO : what happens if MCP is missing ?

    // POWER
    power = new K32_power(stm32, LIPO, true);
    power->setMCPcalib(mcp);
    //power->setExternalCurrentSensor(HO10_P_SP33, CURRENT_PIN[k32->system->hw()], 15000);  // TODO: test sensor

    // Remote
    // TODO: pluginify remote
    remote = new K32_remote(k32, mcp);

    /////////////////////////////////////////////// LIGHT //////////////////////////////////////

    light = new K32_light(k32);

    for(int k=0; k<LED_N_STRIPS; k++)
        if(LEDS_PIN[k32->system->hw()][k] > 0) {  // TODO: allow -1 pin but disable output
            strip[k] = new K32_ledstrip(k, LEDS_PIN[k32->system->hw()][k], (led_types)RUBAN_type, RUBAN_size + 30);
            light->addFixture( strip[k] );
        }

    // STROBEDMX
    #if LULU_TYPE == 11
        strobedmx = new K32_strobedmx(DMX_PIN[k32->system->hw()], LULU_adr);
        light->addFixture( strobedmx );

    // PARDMX
    #elif LULU_TYPE == 12
        pardmx = new K32_pardmx(DMX_PIN[k32->system->hw()], LULU_adr);
        light->addFixture( pardmx );

        // NODE
    #elif LULU_TYPE == 13
        node = new K32_node(DMX_PIN[k32->system->hw()], LULU_adr);
        light->addFixture( node );
    
    // ELP
    #elif LULU_TYPE == 50
        elp = new K32_elp(DMX_PIN[k32->system->hw()], DMXOUT_addr, RUBAN_size);
        light->addFixture( elp ); // TODO: replace system->hw()
        light->copyFixture({strip[0], 0, RUBAN_size, elp, 0});

    // LYRE
    #elif LULU_TYPE == 60
        lyreaudio = new K32_lyreaudio(DMX_PIN[k32->system->hw()], LULU_adr);
        light->addFixture( lyreaudio ); // TODO: replace system->hw()
    #endif

    // PWM
    for (int k = 0; k < PWM_N_CHAN; k++)
        if (PWM_PIN[k32->system->hw()][k] > 0) // TODO: allow -1 pin but disable output
            light->pwm->attach(PWM_PIN[k32->system->hw()][k]);


    /////////////////////////////////////////////// NETWORK //////////////////////////////////////

    ////////////////// WIFI MODE
    if (wifiMode()) 
    {
        ////////////////// WIFI
        LOG("NETWORK: wifi");
        wifi = new K32_wifi(k32);
        mqtt = new K32_mqtt(k32, wifi, stm32);
        // osc = new K32_osc(k32, wifi);
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


