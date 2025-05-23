#include <Arduino.h>

#define NODE32_VER 105
// if previous version was < 102 : Upload SPIFFS !
// 102: add Webserver + SPIFFS
// 103: add K32_audio
// 104: reset & web config & some audio tweaks

// .##.......##.....##.##.......##.....##....########.##....##.########..########
// .##.......##.....##.##.......##.....##.......##.....##..##..##.....##.##......
// .##.......##.....##.##.......##.....##.......##......####...##.....##.##......
// .##.......##.....##.##.......##.....##.......##.......##....########..######..
// .##.......##.....##.##.......##.....##.......##.......##....##........##......
// .##.......##.....##.##.......##.....##.......##.......##....##........##......
// .########..#######..########..#######........##.......##....##........########

#define LULU_TYPE 307

// 0="Power" 1="Sac" 2="Barre" 3="Pince" 4="Fluo" 5="Flex" 6="PotSon" 9="chariot"
// 10="power" 11="DMX_strobe" 12="DMX_Par_led" 13="NODE_dmx_thru" 14="DMX_smoke"
// 20="Cube_str" 21="Cube_par"  22="Cube_MiniKOLOR" 23="Cube_Elp" 24="Cube_SK"
// 30="table-lumineuse_parled" 31="table-lumineuse_Strobe" 32="table-lumineuse_MiniKolor" 33="table-lumineuse_Elp"  34="Banc" 38="table-lumineuse-no-artnet&mqtt"
// 40="New_Fluo"
// 50="ELP dmx (sk anim)"
// 60="Lyre audio dmx + strip"
// 70="Strobe" 71="4x Strobe" 72="5x parled"
// ATOM: 80="Atom" 82="Relais" 83="Cloud" 84="Maree"
// ATOM ST: 91: "ST_buzzer"
// 301 DMX_fixture
// 302 Flex out 1 kontact
// 303 manuFlex out 1 kontact
// 304 hotteFlex out 1 kontact
// 305 hotteFlex Animal out 1 kontact
// 306 hotteFlex Machine out 1 kontact
// 307 hotteFlex Vegetale out 1 kontact

//      .####....########.
//      ..##.....##.....##
//      ..##.....##.....##
//      ..##.....##.....##
//      ..##.....##.....##
//      ..##.....##.....##
//      .####....########.

/////////////////////////////////////////ID/////////////////////////////////////////

// #define K32_SET_NODEID 7    // board unique id => V1 only or boards without STM32 !! otherwise read from STM32
// #define K32_SET_HWREV 14    // board hw rev !! only for boards without STM32
//  1: KXKM V1
//  2: KXKM V2
//  3: KXKM V3
// 13: ATOM
// 14: ATOM_LITE

//
// You can now set those using WEB interface !!
//
//    // #define K32_SET_CHANNEL 8      // board channel mqtt elp 1, 2, cube 3, flex 4,  dmx par 5, dmx arca 6, dmx p5 7, barre 8
//    // #define LIGHT_SET_ID 5         // permet de calculer l'adresse DMX
//    // #define ARTNET_SET_UNIVERSE 1  // univers artnet
//                    // defo ARTNET_SET_UNIVERSE 0  => LULU-TYPE 6 & 7 & 8 & 10 & 20 & 34
//                    // defo ARTNET_SET_UNIVERSE 1  => LULU-TYPE 2 & 5 & 50
//                    // defo ARTNET_SET_UNIVERSE 2  => LULU-TYPE 9 & 72
//                    // defo ARTNET_SET_UNIVERSE 3  => LULU-TYPE 50
//                    // defo ARTNET_SET_UNIVERSE 4  => LULU-TYPE 11
//                    // defo ARTNET_SET_UNIVERSE 5  => LULU-TYPE 12 & 21 & 22
//                    // defo ARTNET_SET_UNIVERSE 6  => LULU-TYPE 4 & 30 & 31 & 32 & 33 & 40
//                    // defo ARTNET_SET_UNIVERSE 7  => LULU-TYPE 3 & 23
//                    // defo ARTNET_SET_UNIVERSE 8  => LULU-TYPE 1
//                    // defo ARTNET_SET_UNIVERSE 16 => LULU-TYPE 60 (Lyres)

/////////////////////////////////////////K32/////////////////////////////////////////

#include "k32_loader.h"

// ..######..########.########.##.....##.########.
// .##....##.##..........##....##.....##.##.....##
// .##.......##..........##....##.....##.##.....##
// ..######..######......##....##.....##.########.
// .......##.##..........##....##.....##.##.......
// .##....##.##..........##....##.....##.##.......
// ..######..########....##.....#######..##.......

///////////////////////////////////////////////// SETUP ////////////////////////////////////////
void setup()
{
  k32_setup();

  /////////////////////////////////////////////// NETWORK //////////////////////////////////////

  ////////////////// WIFI
  if (wifi)
  {
    // Define router (also MQTT broker)
    String router = "2.0.0.1";
    // String router = "192.168.1.37";

    // Auto calculate IP, i.e.   ID: 45 => 2.0.0.145  //  ID: 318 => 2.0.3.118  // ID: 100 => 2.0.1.100
    //
    String basenet = router.substring(0, router.indexOf('.', router.indexOf('.') + 1)); // 2.0.
    int subnet = k32->system->id() / 100;
    wifi->staticIP(basenet + "." + String(subnet) + "." + String(k32->system->id() - subnet * 100 + 100), router, "255.0.0.0");

    // Wifi connect (SSID / password)
    //
    // wifi->connect("kxkm24out", NULL);               // KXKM 24 out
    wifi->connect("kxkm24", NULL);                  // KXKM 24
    // wifi->connect("kxkm24kr1", NULL); // KXKM 24 kr1
    // wifi->connect("kxkm24gocab", NULL);             // KXKM 24 gocab
    // wifi->connect("kxkm24iveco", NULL);             // KXKM 24 iveco
    // wifi->connect("kxkm24charette", NULL);          // KXKM 24 charette
    // wifi->connect("kxkm24max", NULL);               // KXKM 24 max
    // wifi->connect("kxkm24christiana", NULL);        // KXKM 24 christiana
    // wifi->connect("kxkm24madone", NULL);               // KXKM 24 madonne
    // wifi->connect("phare", NULL);                   // KXKM phare
    // wifi->connect("kxkm24lulu", NULL);              // KXKM 24 LULU                                        //KXKM 24 lulu
    // wifi->connect("mgr4g", NULL);                   // Maigre                                              //Maigre dev
    // wifi->connect("interweb", "superspeed37");      // Maigre Maizon                                       //Maigre dev home
    // wifi->connect("riri_new", "B2az41opbn6397");    // RIRI dev                                            //Riri dev home
    // TODO: if wifi->connect ommited = crash on mqtt/artnet/osc

    ////////////////// MQTT
    if (mqtt)
      mqtt->start({
          .broker = router.c_str(), // Komplex
          // .broker = "2.0.0.10", // Riri dev home
          // .broker = "192.168.43.132",  // MGR dev home
          .beatInterval = 5000,   // heartbeat interval milliseconds (0 = disable) 5000
          .statusInterval = 15000 // full beacon interval milliseconds (0 = disable) 15000
      });

    ////////////////// OSC
    if (osc)
      osc->start({
          .port_in = 1818,    // osc port input (0 = disable)  // 1818
          .port_out = 1819,   // osc port output (0 = disable) // 1819
          .beatInterval = 0,  // heartbeat interval milliseconds (0 = disable)
          .statusInterval = 0 // full beacon interval milliseconds (0 = disable)
      });
  }

  ////////////////// INFO //////////////////////////////////////
  /*tee*/
  // Monitoring refresh // TODO Move somewhere else !
  if (k32 && int(LULU_TYPE) == 1)
    k32->timer->every(REFRESH_INFO, []()
                      {
            if (stm32)
              light->anim("battery-strip")->push(stm32->battery());

            static bool toggleRSSI = false;
            toggleRSSI = !toggleRSSI;

            // Wifi
            if (wifi && light)
            {
              int rssi = wifi->getRSSI();
              if (rssi < 0)
                light->anim("rssi-strip")->push(rssi);
              else if (toggleRSSI)
                light->anim("rssi-strip")->push(-100);
              else
                light->anim("rssi-strip")->push(0);
            }

            // Bluetooth
            if(bt && light)
            {
              int rssi = bt->getRSSI();
              if (rssi > 0)         light->anim("rssi-strip")->push(rssi);
              else if (toggleRSSI)  light->anim("rssi-strip")->push(100);
              else                  light->anim("rssi-strip")->push(0);
            } });

  // Heap Memory log
  k32->timer->every(1000, []()
                    {
    static int lastheap = 0;
    int heap = ESP.getFreeHeap();
    // LOGF2("Free memory: %d / %d\n", heap, heap - lastheap);
    lastheap = heap;
    if (heap < 50000) LOGF2("WARNING: free memory < 50K, new task might not properly start. %d / %d\n", heap, heap - lastheap); });

} // setup

// .##........#######...#######..########.
// .##.......##.....##.##.....##.##.....##
// .##.......##.....##.##.....##.##.....##
// .##.......##.....##.##.....##.########.
// .##.......##.....##.##.....##.##.......
// .##.......##.....##.##.....##.##.......
// .########..#######...#######..##.......
///////////////////////////////////////// LOOP /////////////////////////////////////////////////
void loop()
{
  delay(200);
  // light->anim("mem-strip")->printWM();
  // light->anim("rssi-strip")->printWM();
  // k32->timer->every(3000, []()
  //                   {
  //                    dipswitch->dipswitch_read();
  //                   });
} // loop
