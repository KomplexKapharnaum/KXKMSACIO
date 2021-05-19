#include <Arduino.h>

#define LULU_VER 77
#define LULU_TYPE 50 // 1="Sac" 2="Barre" 3="Pince" 4="Fluo" 5="Flex" 6="H&S" 7="Phone" 8="Atom" 9="chariot" \
                    // 10="power" 11="DMX_strobe" 12="DMX_Par_led"                                          \
                    // 20="Cube_str" 21="Cube_par"  22="Cube_MiniKOLOR" 23="Cube_Elp"                       \
                    // 30="Sucette_parled" 31="Sucette_Strobe" 32="Sucette_MiniKolor" 33="sucette_Elp"  34="Banc"     \
                    // 40="New_Fluo" \
                    // 50="strip to elp dmx"

#define LULU_PATCHSIZE 20 

/////////////////////////////////////////ID/////////////////////////////////////////

// #define K32_SET_NODEID 18 // board unique id
#define LULU_ID 8  // permet de calculer l'adresse DMX
#define LULU_UNI 1 // univers artnet
//                        // defo LULU_UNI 0 => LULU-TYPE 6 & 7 & 8 & 10 & 20
//                        // defo LULU_UNI 1 => LULU-TYPE 1 & 2 & 5
//                        // defo LULU_UNI 2 => LULU-TYPE 9
//                        // defo LULU_UNI 3 => LULU-TYPE 50
//                        // defo LULU_UNI 4 => LULU-TYPE 11
//                        // defo LULU_UNI 5 => LULU-TYPE 12 & 21 & 22
//                        // defo LULU_UNI 6 => LULU-TYPE 4 & 30 & 31 & 32 & 33 & 40
//                        // defo LULU_UNI 7 => LULU-TYPE 3 & 23

/////////////////////////////////////////Debug///////////////////////////////////////

// #define DEBUG_dmx 1              // !!! IMPLEMENT
// #define DEBUG_dmxframe 1
// #define DEBUG_STR 1
// #define DEBUG_calibre_btn 1
#define DEBUG_btn 1

#define DMXOUT_addr 20 // Replace ELP_Start

#define LULU_PREVPIX 40
// Nombre de pixel pour la prévisu
#define MASTER_PREV 40    // Luminosité prévisu
#define REFRESH_INFO 1000 // Refresh affichage Wifi & Battery

/////////////////////////////////////////Adresse/////////////////////////////////////
int LULU_id;
int LULU_type;
int LULU_uni;
int LULU_adr;

String nodeName;

int RUBAN_type;
int RUBAN_size;

int FAKE_current;

/////////////////////////////////////////K32/////////////////////////////////////////

#include "k32_loader.h"
#include "settings.h"

///////////////////////////////////////////////// include ////////////////////////////////////////

#include "anim_monitoring.h"
#include "anim_dmx_test.h"
#include "anim_dmx_strip.h"
#include "anim_dmx_out.h"
#include "boutons.h"
#include "test.h"

///////////////////////////////////////////////// SETUP ////////////////////////////////////////
void setup()
{

  settings();
  k32_setup();
  boutons_init();

  LOG("NAME:   " + nodeName + "\n");

  /////////////////////////////////////////////// LIGHT //////////////////////////////////////
  init_mem();

// CLONE STRIP
//struct copyFixture({ srcFixture, srcStart, srcStop, destFixture, destPos};
// if (LULU_type == 9)
//   light->copyFixture({strip[0], 0, RUBAN_size, strip[1], 0}); // chariot clone
// else if (LULU_type == 40)
//   light->copyFixture({strip[0], 0, RUBAN_size, strip[1], 0}); // fluo clone
// else
//   light->copyFixture({strip[0], RUBAN_size, RUBAN_size + 18, strip[1], 0}); // jauge sortie 2

// COPY Strip-0 to DMX
#ifdef DMXOUT_addr
  light->copyFixture({strip[0], 0, RUBAN_size, dmxout, 0});
#endif

  // TEST Sequence
  light_tests();

  // ADD NEW ANIMS (strip, name, anim, size, offset=0)

  // ANIM artnet
  // light->anim(1, "artnet", new Anim_dmx_out, 1)->play();  // dmx         // TODO: anim straight to dmx
  light->anim(strip[0], "artnet", new Anim_dmx_strip, RUBAN_size)->play(); // sk  // TODO: attach multiple fixture to anim

  // ANIM manuframe
  // light->anim(1, "manu", new Anim_dmx_out, 1);// dmx                   // TODO: anim straight to dmx
  light->anim(strip[0], "manu", new Anim_dmx_strip, RUBAN_size); // sk

// MEM NO WIFI
#if (LULU_TYPE >= 20 || LULU_TYPE == 2 || LULU_TYPE == 6)
  light->anim("artnet")->push(MEM_NO_WIFI, LULU_PATCHSIZE);
  // light->anim("artnet")->mod(new K32_mod_sinus)->at(2)->period(8500)->phase(0)->mini(-255)->maxi(255); // modulo
#endif

  // ANIM monitoring
  light->anim(strip[0], "battery", new Anim_battery, 4, RUBAN_size + 1)->master(MASTER_PREV)->play();
  light->anim(strip[0], "remote", new Anim_remote, LULU_PREVPIX + 4, RUBAN_size + 6)->master(MASTER_PREV)->play();
  light->anim(strip[0], "preview", new Anim_preview, LULU_PREVPIX, RUBAN_size + 8)->master(MASTER_PREV)->play();
  light->anim(strip[0], "rssi", new Anim_rssi, 1, RUBAN_size + 17)->master(MASTER_PREV * 1.5)->play();

  // sampler jpeg sd
  // k32->init_samplerjpeg();

  // REMOTE
  remote->setMacroMax(NUMBER_OF_MEM); // TODO: clean MEM loading (and setMemMax)

  /////////////////////////////////////////////// NETWORK //////////////////////////////////////

  ////////////////// WIFI
  if (wifi)
  {
    wifi->setHostname(k32->system->name() + (nodeName != "") ? "-" + nodeName : "");

    wifi->staticIP("2.0.0." + String(k32->system->id() + 100), "2.0.0.1", "255.0.0.0"); // WARNING: netmask !!
    wifi->connect("kxkm24", NULL);                                                      //KXKM
    // wifi->connect("kxkm24lulu", NULL); //KXKM
    // wifi->connect("mgr4g", NULL); //Maigre dev
    // wifi->connect("interweb", "superspeed37"); //Maigre dev home
    // wifi->connect("riri_new", "B2az41opbn6397"); //Riri dev home
    // TODO: if wifi->connect ommited = crash on mqtt/artnet/osc

    ////////////////// ARTNET
    artnet = new K32_artnet(k32, {.universe = LULU_uni,
                                  .address = LULU_adr,
                                  .framesize = LULU_PATCHSIZE});

    // EVENT: full frame
    artnet->onFullDmx([](const uint8_t *data, int length) {
      // Force Auto
      if (length > 511 && data[511] > 250) // data 512 = end dmx trame
      {
        remote->setState(REMOTE_AUTO);
        remote->lock();
      }
      // LOGF2("ARTNET: %d %d \n", data[511], length);
    });

    // EVENT: new artnet frame received
    artnet->onDmx([](const uint8_t *data, int length) {
      light->anim("artnet")->push(data, length);
      // LOGINL("ARTFRAME: ");
      // for (int k=0; k<length; k++) LOGF("%d ", data[k]);
      // LOG();
    });

    // EVENT: wifi lost
    wifi->onDisconnect([&]() {
      LOG("WIFI: connection lost..");

#if LULU_TYPE >= 20
      light->anim("artnet")->push(MEM_NO_WIFI, LULU_PATCHSIZE);
#else
      light->anim("artnet")->push(0); // @master 0
#endif
    });

    ////////////////// MQTT
    if (mqtt)
      mqtt->start({
          .broker = "2.0.0.1", // Komplex
          // .broker = "2.0.0.10",     // Riri dev home
          // .broker = "192.168.43.132",  // MGR dev home
          .beatInterval = 5000,   // heartbeat interval milliseconds (0 = disable)
          .statusInterval = 15000 // full beacon interval milliseconds (0 = disable)
      });

    ////////////////// OSC
    if (osc)
      osc->start({
          .port_in = 1818,        // osc port input (0 = disable)  // 1818
          .port_out = 1819,       // osc port output (0 = disable) // 1819
          .beatInterval = 5000,   // heartbeat interval milliseconds (0 = disable)
          .statusInterval = 15000 // full beacon interval milliseconds (0 = disable)
      });
  }

  ///////////////////// INFO //////////////////////////////////////

  // Monitoring refresh
  k32->timer->every(REFRESH_INFO, []() {
    if (stm32)
      light->anim("battery")->push(stm32->battery());

    static bool toggleRSSI = false;
    toggleRSSI = !toggleRSSI;

    // Wifi
    if (wifi)
    {
      int rssi = wifi->getRSSI();
      if (rssi < 0)
        light->anim("rssi")->push(rssi);
      else if (toggleRSSI)
        light->anim("rssi")->push(-100);
      else
        light->anim("rssi")->push(0);
    }

    // Bluetooth
    // TODO: enable BT
    // if(bt)
    // {
    //   int rssi = bt->getRSSI();
    //   if (rssi > 0)         light->anim("rssi")->push(rssi);
    //   else if (toggleRSSI)  light->anim("rssi")->push(100);
    //   else                  light->anim("rssi")->push(0);
    // }
  });

  // Remote status refresh
  k32->timer->every(100, []() {
    light->anim("remote")->push(remote->getState(), remote->isLocked());
  });

  // Heap Memory log
  k32->timer->every(1000, []() {
    static int lastheap = 0;
    int heap = ESP.getFreeHeap();
    LOGF2("Free memory: %d / %d\n", heap, heap - lastheap);
    lastheap = heap;
  });

} // setup

///////////////////////////////////////// LOOP /////////////////////////////////////////////////
void loop()
{

  ///////////////////// BOUTONS ///////////////////////
  boutons_loop();

  delay(20);

} //loop
