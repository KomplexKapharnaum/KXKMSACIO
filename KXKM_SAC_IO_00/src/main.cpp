#include <Arduino.h>

#define LULU_VER 64
#define LULU_TYPE 8 // 1="Sac" 2="Barre" 3="Pince" 4="Fluo" 5="Flex" 6="H&S" 7="Phone" 8="Atom" 9="chariot" 10="power" 11="DMX_strobe" 12="DMX_Par_led" 13="Cube_str" 14="Cube_par"

/////////////////////////////////////////ID/////////////////////////////////////////

// #define K32_SET_NODEID 125         // board unique id

// #define RUBAN_TYPE LED_SK6812W_V1 // LED_WS2812_V1  LED_WS2812B_V1  LED_WS2812B_V2  LED_WS2812B_V3  LED_WS2813_V1  LED_WS2813_V2   LED_WS2813_V3  LED_WS2813_V4  LED_SK6812_V1  LED_SK6812W_V1,
// #define LULU_ID 1                // permet de calculer l'adresse DMX


/////////////////////////////////////////Debug///////////////////////////////////////

// #define DEBUG_dmx 1              // !!! IMPLEMENT
// #define DEBUG_dmxframe 1
// #define DEBUG_STR 1
// #define DEBUG_calibre_btn 1
#define DEBUG_btn 1

#define LULU_PREVPIX 6    // Nombre de pixel pour la prévisu

#define MASTER_PREV 40 // Luminosité prévisu

#define REFRESH_INFO 1000 // Refresh affichage Wifi & Battery

/////////////////////////////////////////Adresse/////////////////////////////////////
int LULU_id;
int LULU_type;
int LULU_uni;
int LULU_adr;

String nodeName;
bool wifiMode = true;

int RUBAN_type;
int RUBAN_size;

int FAKE_current;

/////////////////////////////////////////K32/////////////////////////////////////////

#include <K32.h> // https://github.com/KomplexKapharnaum/K32-lib
K32 *k32;

#include "settings.h"

///////////////////////////////////////////////// LIGHT MACRO ////////////////////////////////////////
#include "macro/mem.h"
// #include "macro/mem_h&s.h"
// #include "macro/mem_test.h"

///////////////////////////////////////////////// include ////////////////////////////////////////

#include "mem.h"
#include "anim_monitoring.h"
#include "anim_dmx.h"
#include "boutons.h"
#include "test.h"



///////////////////////////////////////////////// SETUP ////////////////////////////////////////
void setup()
{
  //////////////////////////////////////// K32_lib ////////////////////////////////////
  k32 = new K32();

  //////////////////////////////////////// K32 modules ////////////////////////////////////
  settings();
  LOG("NAME:   " + nodeName + "\n");
  
  // STM32
  k32->init_stm32();

  // PWM
  k32->init_pwm();

  /////////////////////////////////////////////// EXTENSION ////////////////////////////////////

  // MCP
  k32->init_mcp();

  // Power
  if (k32->system->hw() < 3) { 
    k32->init_power(LIPO, true, FAKE_current);  // Batt type, auto gauge, fake external current (if no sensor) mA
  }

  // Remote
  k32->init_remote(NUMBER_OF_MEM);
  boutons_init();

  // WIFI/BT switch
  if (k32->mcp)
    k32->mcp->input(14);


  /////////////////////////////////////////////// LIGHT //////////////////////////////////////

  // LEDS
  k32->init_light(RUBAN_type, RUBAN_size + 30);

  // clone every strip from strip 0
  // k32->light->cloneStrips(0);
  
  //struct copyStrip({ srcStrip, srcStart, srcStop, destStrip, destPos};
  if (LULU_type == 9) k32->light->copyStrip({0, 0, RUBAN_size, 1, 0});// chariot clone
  else k32->light->copyStrip({0, RUBAN_size, RUBAN_size + 18, 1, 0});// jauge sortie 2

  // test sequence
  light_tests();

  // ADD NEW ANIMS (strip, name, anim, size, offset=0)

  // ANIM artnet
  k32->light->anim(0, "artnet", new Anim_dmx, RUBAN_size)->play();

  // ANIM manuframe
  k32->light->anim(0, "manu", new Anim_dmx, RUBAN_size);

  // ANIM monitoring
  k32->light->anim(0, "battery", new Anim_battery, 4, RUBAN_size + 1)->master(MASTER_PREV)->play();
  k32->light->anim(0, "remote", new Anim_remote, LULU_PREVPIX + 4, RUBAN_size + 6)->master(MASTER_PREV)->play();
  k32->light->anim(0, "preview", new Anim_preview, LULU_PREVPIX, RUBAN_size + 8)->master(MASTER_PREV)->play();
  k32->light->anim(0, "rssi", new Anim_rssi, 1, RUBAN_size + 17)->master(MASTER_PREV * 1.5)->play();

  // sampler jpeg sd
  // k32->init_samplerjpeg();

  /////////////////////////////////////////////// NETWORK //////////////////////////////////////

  if (k32->mcp) wifiMode = k32->mcp->state(14);
  else wifiMode = true;
  
  LOGINL("NETWORK: ");
  if (wifiMode) LOG("wifi");
  else LOG("bluetooth");


  ////////////////// WIFI MODE
  if (wifiMode) 
  {

    /////////////////////////////////////////////// WIFI //////////////////////////////////////
    LOG("INIT WIFI");
    k32->init_wifi(nodeName);
    k32->wifi->staticIP("2.0.0." + String(k32->system->id() + 100), "2.0.0.1", "255.0.0.0");
    k32->wifi->connect("kxkm24", NULL); //KXKM
    // k32->wifi->connect("kxkm24lulu", NULL);//KXKM
    // k32->wifi->connect("interweb", "superspeed37");


    /////////////////////////////////////////////// ARTNET //////////////////////////////////////
    k32->init_artnet({.universe = LULU_uni,
                      .address = LULU_adr,
                      .framesize = LULU_PATCHSIZE});


    // EVENT: full frame
    k32->artnet->onFullDmx([](uint8_t *data, int length) 
    {
      // Force Auto
      if (length > 511 && data[511] > 250) // data 512 = end dmx trame 
      {
        k32->remote->setState(REMOTE_AUTO);
        k32->remote->lock();
      }
    });


    // EVENT: new artnet frame received
    k32->artnet->onDmx([](uint8_t *data, int length) 
    {
      // Draw
      k32->light->anim("artnet")->push(data, length);
    });

    // EVENT: wifi lost
    k32->wifi->onDisconnect([&]() {
      LOG("WIFI: connection lost..");

      k32->light->anim("artnet")->push(0); // @master 0
    });


    /////////////////////////////////////// MQTT //////////////////////////////////////
    k32->init_mqtt();

    // k32->mqtt->subscribe({
    //   .topic = "k32/monitor/beat",
    //   .qos = 0,
    //   .callback = [](char *payload, size_t length) 
    //               {
    //                 LOGINL("-- BEAT received:");
    //                 LOGINL(" ");
    //                 LOG(payload);
    //               }
    // });

    // k32->mqtt->subscribe({
    //   .topic = "k32/monitor/status",
    //   .qos = 0,
    //   .callback = [](char *payload, size_t length) 
    //               {
    //                 LOGINL("-- STATUS received:");
    //                 LOGINL(" ");
    //                 LOG(payload);
    //               }
    // });

    k32->mqtt->start({
        .broker = "2.0.0.1", 
        .beatInterval = 2000,          // heartbeat interval milliseconds (0 = disable)
        .beaconInterval = 10000         // full beacon interval milliseconds (0 = disable)
    });


    /////////////////////////////////////////////// OSC //////////////////////////////////////
    // k32->init_osc({
    //     .port_in = 1818,       // osc port input (0 = disable)  // 1818
    //     .port_out = 1819,      // osc port output (0 = disable) // 1819
    //     .beatInterval = 0,     // heartbeat interval milliseconds (0 = disable)
    //     .beaconInterval = 3000 // full beacon interval milliseconds (0 = disable)
    // });                        // OSC
  }

  ////////////////// BLUETOOTH
  else 
  {
    k32->init_bt("k32-"+String(k32->system->id()));

    k32->bt->onConnect([&](){
      k32->bt->send("Yo Rasta!");
    });
  }


  ///////////////////// INFO //////////////////////////////////////

  // Monitoring refresh
  k32->timer->every(REFRESH_INFO, []() {
    
    k32->light->anim("battery")->push(k32->system->stm32->battery());

    static bool toggleRSSI = false;
    toggleRSSI = !toggleRSSI;

    // Wifi
    if (wifiMode) {
      int rssi = k32->wifi->getRSSI();
      if (rssi < 0) k32->light->anim("rssi")->push(rssi);
      else if (toggleRSSI) k32->light->anim("rssi")->push(-100);
      else k32->light->anim("rssi")->push(0);
    }

    // Bluetooth
    else {
      int rssi = k32->bt->getRSSI();
      if (rssi > 0) k32->light->anim("rssi")->push(rssi);
      else if (toggleRSSI) k32->light->anim("rssi")->push(100);
      else k32->light->anim("rssi")->push(0);
    }

  });

  // Remote status refresh
  k32->timer->every(50, []() {
    k32->light->anim("remote")->push(k32->remote->getState(), k32->remote->isLocked());
  });

  // Heap Memory log
  // k32->timer->every(1000, []() {
  //   static int lastheap = 0;
  //   int heap = ESP.getFreeHeap();
  //   LOGF2("Free memory: %d / %d\n", heap, heap-lastheap);
  //   lastheap = heap;
  // });
}

///////////////////////////////////////// LOOP /////////////////////////////////////////////////
void loop()
{

  ///////////////////// BOUTONS ///////////////////////
  boutons_loop();

  delay(20);

} //loopk32->wifi->getRSSI()