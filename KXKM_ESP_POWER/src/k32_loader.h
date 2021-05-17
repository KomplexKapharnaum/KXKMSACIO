

#include <K32.h> // https://github.com/KomplexKapharnaum/K32-lib
K32* k32 = nullptr;

#include <hardware/K32_stm32.h>
K32_stm32* stm32 = nullptr;

#include <hardware/K32_power.h>
K32_power* power = nullptr;

#include <K32_wifi.h>
K32_wifi* wifi = nullptr;

#include <K32_osc.h>
K32_osc* osc = nullptr;

#include <K32_mqtt.h>
K32_mqtt* mqtt = nullptr;

#include <fixtures/K32_ledstrip.h>
K32_ledstrip* strip[LED_N_STRIPS] = {nullptr};

#include <K32_light.h>
K32_light* light = nullptr;



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

    // POWER
    power = new K32_power(stm32, LIPO, true);


    /////////////////////////////////////////////// LIGHT //////////////////////////////////////

    light = new K32_light(k32);

    for(int k=0; k<LED_N_STRIPS; k++)
        if(LEDS_PIN[k32->system->hw()][k] > 0) {  // TODO: allow -1 pin but disable output
            strip[k] = new K32_ledstrip(k, LEDS_PIN[k32->system->hw()][k], (led_types)RUBAN_type, RUBAN_size + 30);
            light->addFixture( strip[k] );
        }


    /////////////////////////////////////////////// NETWORK //////////////////////////////////////

    ////////////////// WIFI
    LOG("NETWORK: wifi");
    wifi = new K32_wifi(k32);
    mqtt = new K32_mqtt(k32, wifi);
    osc = new K32_osc(k32, wifi);
}


