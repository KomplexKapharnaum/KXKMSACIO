#include <Arduino.h>

#define LULU_VER 88
#define LULU_TYPE 80
// 1="Sac" 2="Barre" 3="Pince" 4="Fluo" 5="Flex" 6="H&S" 7="Phone" 8="Atom" 9="chariot"
// 10="power" 11="DMX_strobe" 12="DMX_Par_led" 13="NODE_dmx_thru"
// 20="Cube_str" 21="Cube_par"  22="Cube_MiniKOLOR" 23="Cube_Elp"
// 30="Sucette_parled" 31="Sucette_Strobe" 32="Sucette_MiniKolor" 33="sucette_Elp"  34="Banc"
// 40="New_Fluo"
// 50="strip to elp dmx"
// 60="Lyre audio dmx + strip"
// 80="Maree_SK"

/////////////////////////////////////////ID/////////////////////////////////////////

#define K32_SET_NODEID 1  // board unique id
#define K32_SET_CHANNEL 1 // board channel mqtt
#define LULU_ID 1         // permet de calculer l'adresse DMX
#define LULU_UNI 1        // univers artnet
//                    // defo LULU_UNI 0  => LULU-TYPE 6 & 7 & 8 & 10 & 20 & 34
//                    // defo LULU_UNI 1  => LULU-TYPE 1 & 2 & 5 & 50
//                    // defo LULU_UNI 2  => LULU-TYPE 9
//                    // defo LULU_UNI 3  => LULU-TYPE 50
//                    // defo LULU_UNI 4  => LULU-TYPE 11
//                    // defo LULU_UNI 5  => LULU-TYPE 12 & 21 & 22
//                    // defo LULU_UNI 6  => LULU-TYPE 4 & 30 & 31 & 32 & 33 & 40
//                    // defo LULU_UNI 7  => LULU-TYPE 3 & 23
//                    // defo LULU_UNI 16 => LULU-TYPE 60 (Lyres)

/////////////////////////////////////////Adresse/////////////////////////////////////

int LULU_id;
int LULU_type;
int LULU_uni;
int LULU_adr;

String nodeName;

int RUBAN_type;
int RUBAN_size;

int FAKE_current;
int DMXOUT_addr;

int FRAME_size;

/////////////////////////////////////////K32/////////////////////////////////////////

#include "k32_loader.h"
#include "settings.h"

///////////////////////////////////////////////// include ////////////////////////////////////////

#include "anim_monitoring.h"
#include "anim_dmx_test.h"
#include "anim_dmx_strip.h"
#include "anim_dmx_thru.h"
#include "boutons.h"
#include "test.h"

///////////////////////////////////////////////// SETUP ////////////////////////////////////////
void setup()
{

  settings();
  k32_setup();
  boutons_init();

  LOG("NAME:   " + nodeName + "\n");
  LOGF("CHANNEL: %d\n", k32->system->channel());

  /////////////////////////////////////////////// LIGHT //////////////////////////////////////
  init_mem();

  // CLONE STRIP
  //struct copyFixture({ srcFixture, srcStart, srcStop, destFixture, destPos};
  if (LULU_type == 9)
    light->copyFixture({strip[0], 0, RUBAN_size, strip[1], 0}); // chariot clone
  else if (LULU_type == 40)
    light->copyFixture({strip[0], 0, RUBAN_size, strip[1], 0}); // fluo clone
  else if (k32->system->hw() == 4)
    light->copyFixture({strip[0], 0, RUBAN_size, strip[1], 0}); // atom lite clone
  else
    light->copyFixture({strip[0], RUBAN_size, RUBAN_size + 18, strip[1], 0}); // jauge sortie 2

  // TEST Sequence
  light_tests();

  // ANIM leds - artnet
  light->anim(strip[0], "artnet", new Anim_dmx_strip, RUBAN_size)->play();

  // ANIM leds - manuframe
  light->anim(strip[0], "manu", new Anim_dmx_strip, RUBAN_size);

  // ANIM leds - monitoring
  light->anim(strip[0], "battery", new Anim_battery, 4, RUBAN_size + 1)->master(MASTER_PREV)->play();
  light->anim(strip[0], "remote", new Anim_remote, LULU_PREVPIX + 4, RUBAN_size + 6)->master(MASTER_PREV)->play();
  light->anim(strip[0], "preview", new Anim_preview, LULU_PREVPIX, RUBAN_size + 8)->master(MASTER_PREV)->play();
  light->anim(strip[0], "rssi", new Anim_rssi, 1, RUBAN_size + 17)->master(MASTER_PREV * 1.5)->play();

#if LULU_TYPE == 60
  // ANIM dmx thru
  light->anim(lyreaudio, "dmxthru", new Anim_dmx_thru, LYRE_PATCHSIZE / 4)->play();
#elif LULU_TYPE == 12
  // ANIM dmx thru
  light->anim(pardmx, "dmxthru", new Anim_dmx_thru, PAR_PATCHSIZE / 4)->play();
#elif LULU_TYPE == 13
  // ANIM dmx thru
  light->anim(node, "dmxthru", new Anim_dmx_thru, NODE_PATCHSIZE / 4)->play();
#endif

  // REMOTE
  remote->setMacroMax(NUMBER_OF_MEM); // TODO: clean MEM loading (and setMemMax)

// MEM ON BOOT
#if (LULU_TYPE >= 20 || LULU_TYPE == 2 || LULU_TYPE == 6)
      // light->anim("artnet")->push(MEM_NO_WIFI, LULU_PATCHSIZE);// settings set
      // light->anim("artnet")->mod(new K32_mod_sinus)->at(2)->period(8500)->phase(0)->mini(-255)->maxi(255); // modulo
      // light->anim("artnet")->push( MEM_SK[20], LULU_PATCHSIZE); // baro auto circulation elp
      // light->anim("artnet")->mod(new K32_mod_sinus)->at(7)->period(8500)->mini(0)->maxi(45);// baro auto circulation elp
#endif

  /////////////////////////////////////////////// NETWORK //////////////////////////////////////

  ////////////////// WIFI
  if (wifi)
  {
    wifi->setHostname(k32->system->name() + (nodeName != "") ? "-" + nodeName : "");

    if (k32->system->hw() != 4)
    {
      wifi->staticIP("2.0.0." + String(k32->system->id() + 100), "2.0.0.1", "255.0.0.0"); // WARNING: netmask !!
      // wifi->staticIP("10.0.0." + String(k32->system->id() + 100), "10.0.0.1", "255.0.0.0");  // KXKM MESH
    }
    if (k32->system->hw() == 4)
    {
      wifi->staticIP("2.0.1." + String(k32->system->id()), "2.0.0.1", "255.0.0.0"); // hw4
    }
    // wifi->connect("kxkm24", NULL); //KXKM 24
    // wifi->connect("kxkm24lulu", NULL);                                                         //KXKM 24 lulu
    // wifi->connect("mgr4g", NULL);                                                              //Maigre dev
    // wifi->connect("interweb", "superspeed37");                                                 //Maigre dev home
    wifi->connect("riri_new", "B2az41opbn6397"); //Riri dev home
// TODO: if wifi->connect ommited = crash on mqtt/artnet/osc

////////////////// ARTNET
#if LULU_TYPE == 60
    FRAME_size = LYRE_PATCHSIZE + 9; // 9: MEM R G B W PWM1 PWM2 PWM3 PWM4
#else
    FRAME_size = LULU_PATCHSIZE;
#endif

    artnet = new K32_artnet(k32, {.universe = LULU_uni,
                                  .address = LULU_adr,
                                  .framesize = FRAME_size,
                                  .shortName = nodeName,
                                  .longName = nodeName});

    // EVENT: full frame
    //
    artnet->onFullDmx([](const uint8_t *data, int length)
                      {
                        // Force Auto
                        if (length > 511 && data[511] > 250) // data 512 = end dmx trame
                        {
                          remote->setState(REMOTE_AUTO);
                          remote->lock();
                        }
#ifdef DEBUG_dmxframe
                        LOGF("ARTNET fullframe: %d \n", length);
#endif
                      });

#if LULU_TYPE == 13
    artnet->onFullDmx([](const uint8_t *data, int length)
                      {
                        if (length <= 0)
                          return;
#else
    // EVENT: new artnet frame received

    artnet->onDmx([](const uint8_t *data, int length)
                  {
                    if (length <= 0)
                      return;

#endif

////////////////// DMXTHRU
// STROBEDMX
#if LULU_TYPE == 11
                        light->anim("dmxthru")->push(data, min(length, STROBE_PATCHSIZE)); // DMX out

// PARDMX
#elif LULU_TYPE == 12
                    light->anim("dmxthru")->push(data, min(length, PAR_PATCHSIZE)); // DMX out

// NODE
#elif LULU_TYPE == 13
    node->setBuffer(data, length); // full frame DMX out

// LYRE + STRIP
#elif LULU_TYPE == 60
    light->anim("dmxthru")->push(data, min(length, LYRE_PATCHSIZE)); // DMX out

    if (length >= LYRE_PATCHSIZE + 9)
    {
      const uint8_t *dataStrip = &data[LYRE_PATCHSIZE];

      // MEM ou ARTNET FRAME
      if (dataStrip[0] > 0 && dataStrip[0] <= NUMBER_OF_MEM)
        remote->stmSetMacro(dataStrip[0] - 1);
      else
      {
        int stripframe[LULU_PATCHSIZE] = {255, dataStrip[1], dataStrip[2], dataStrip[3], dataStrip[4], 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 255, dataStrip[5], dataStrip[6], dataStrip[7], dataStrip[8]};
        light->anim("artnet")->push(stripframe, LULU_PATCHSIZE);
        remote->setState(REMOTE_AUTO);
      }
    }

// Maree no artnet
#elif LULU_TYPE == 80

// STRIP ONLY
#else
    light->anim("artnet")->push(data, min(length, LULU_PATCHSIZE));
#endif

#ifdef DEBUG_dmxframe
                        LOGINL("ARTFRAME: ");
                        LOGF("length=%d ", length);
                        for (int k = 0; k < length; k++)
                          LOGF("%d ", data[k]);
                        LOG();
#endif
                      });

    // EVENT: wifi lost
    wifi->onDisconnect([&]()
                       {
                         LOG("WIFI: connection lost..");

#if LULU_TYPE >= 20
      //  light->anim("artnet")->push(MEM_NO_WIFI, LULU_PATCHSIZE);
#else
                         light->anim("artnet")->push(0); // @master 0
#endif
                       });

    ////////////////// MQTT
    if (mqtt)
      mqtt->start({
          // .broker = "2.0.0.1", // Komplex
          // .broker = "10.0.0.1", // KXKM MESH
          .broker = "2.0.0.10", // Riri dev home
          // .broker = "192.168.43.132",  // MGR dev home
          .beatInterval = 0,  // heartbeat interval milliseconds (0 = disable) 5000
          .statusInterval = 0 // full beacon interval milliseconds (0 = disable) 15000
      });

    ////////////////// OSC
    if (osc)
      osc->start({
          .port_in = 1818,        // osc port input (0 = disable)  // 1818
          .port_out = 1819,       // osc port output (0 = disable) // 1819
          .beatInterval = 5000,   // heartbeat interval milliseconds (0 = disable)
          .statusInterval = 15000 // full beacon interval milliseconds (0 = disable)
      });
  } // if(wifi)

  ///////////////////// INFO //////////////////////////////////////

  // Monitoring refresh
  k32->timer->every(REFRESH_INFO, []()
                    {
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
  k32->timer->every(100, []()
                    { light->anim("remote")->push(remote->getState(), remote->isLocked()); });

  // Heap Memory log
  // k32->timer->every(1000, []() {
  //   static int lastheap = 0;
  //   int heap = ESP.getFreeHeap();
  // LOGF2("Free memory: %d / %d\n", heap, heap - lastheap);
  //   lastheap = heap;
  // });

  load_mem(light->anim("manu"), 1); //auto play
  light->anim("manu")->push(50, 255, 255, 255, 255, 35, 300, 0);
  light->anim("manu")->mod(new K32_mod_fadeout)->at(0)->at(7)->period(3600000)->mini(0)->maxi(150);
  light->anim("manu")->play(); //auto play
} // setup

///////////////////////////////////////// LOOP /////////////////////////////////////////////////
void loop()
{

  /////////////////// BOUTONS ///////////////////////
  // boutons_loop();
  // int pos = analogRead(33);        // potentiometre rochelle
  // pos = map(pos, 0, 4095, 0, 255); // mapage in
  // LOGF("pos = %d ", pos);

  // for (int pos = 1; pos < 301; pos++)
  // {
  //   light->anim("manu")->push(50, 255, 255, 255, 255, 35, 300, pos);
  //   LOGF(" pos = %d ", pos);
  //   delay(20);
  // }

  delay(20);

} //loop