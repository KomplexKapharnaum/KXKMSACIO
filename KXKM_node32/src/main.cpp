#include <Arduino.h>

#define LULU_VER 101

// .##.......##.....##.##.......##.....##....########.##....##.########..########
// .##.......##.....##.##.......##.....##.......##.....##..##..##.....##.##......
// .##.......##.....##.##.......##.....##.......##......####...##.....##.##......
// .##.......##.....##.##.......##.....##.......##.......##....########..######..
// .##.......##.....##.##.......##.....##.......##.......##....##........##......
// .##.......##.....##.##.......##.....##.......##.......##....##........##......
// .########..#######..########..#######........##.......##....##........########

#define LULU_TYPE 8

// 0="Power" 1="Sac" 2="Barre" 3="Pince" 4="Fluo" 5="Flex" 6="H&S" 7="Phone" 8="Atom" 9="chariot"
// 10="power" 11="DMX_strobe" 12="DMX_Par_led" 13="NODE_dmx_thru"
// 20="Cube_str" 21="Cube_par"  22="Cube_MiniKOLOR" 23="Cube_Elp" 24="Cube_SK"
// 30="table-lumineuse_parled" 31="table-lumineuse_Strobe" 32="table-lumineuse_MiniKolor" 33="table-lumineuse_Elp"  34="Banc" 38="table-lumineuse-no-artnet&mqtt"
// 40="New_Fluo"
// 50="ELP dmx (sk anim)"
// 60="Lyre audio dmx + strip"
// 70="Strobe" 71="4x Strobe" 72="5x parled"
// 80="Maree atom-lite"
// 81="Buzzer atom-lite"
// 83="Cloud"

//      .####....########.
//      ..##.....##.....##
//      ..##.....##.....##
//      ..##.....##.....##
//      ..##.....##.....##
//      ..##.....##.....##
//      .####....########.

/////////////////////////////////////////ID/////////////////////////////////////////

// #define K32_SET_NODEID 1    // board unique id => V1 only or boards without STM32 !! otherwise read from STM32
// #define K32_SET_HWREV 13    // board hw rev !! only for boards without STM32
                                        //  1: KXKM V1
                                        //  2: KXKM V2
                                        //  3: KXKM V3
                                        // 13: ATOM
                                        // 14: ATOM_LITE


//
// You can now set those using WEB interface !!  
//
//    // #define K32_SET_CHANNEL 8      // board channel mqtt elp 1 barre 8 cube 3
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
    // String router = "192.168.1.129";

    // Auto calculate IP, i.e.   ID: 45 => 2.0.0.145  //  ID: 318 => 2.0.3.118  // ID: 100 => 2.0.1.100
    //
    String basenet = router.substring(0, router.indexOf('.', router.indexOf('.') + 1)); // 2.0.
    int subnet = k32->system->id() / 100;
    wifi->staticIP(basenet + "." + String(subnet) + "." + String(k32->system->id() - subnet * 100 + 100), router, "255.0.0.0");

    // Wifi connect (SSID / password)
    //
    // wifi->connect("kxkm24out", NULL);            // KXKM 24 out
    wifi->connect("kxkm24", NULL);                  // KXKM 24
    // wifi->connect("phare", NULL);                // KXKM phare
    // wifi->connect("kxkm24lulu", NULL);           // KXKM 24 LULU                                                        //KXKM 24 lulu
    // wifi->connect("mgr4g", NULL);                // Maigre                                                            //Maigre dev
    // wifi->connect("interweb", "superspeed37");    // Maigre Maizon                                             //Maigre dev home
    // wifi->connect("riri_new", "B2az41opbn6397"); // RIRI dev                                              //Riri dev home
    // TODO: if wifi->connect ommited = crash on mqtt/artnet/osc

    ////////////////// MQTT
    if (mqtt)
      mqtt->start({
          .broker = router.c_str(), // Komplex
          // .broker = "2.0.0.10", // Riri dev home
          // .broker = "192.168.43.132",  // MGR dev home
          .beatInterval = 5000, // heartbeat interval milliseconds (0 = disable) 5000
          .statusInterval = 15000   // full beacon interval milliseconds (0 = disable) 15000
      });

    ////////////////// OSC
    if (osc)
      osc->start({
          .port_in = 1818,        // osc port input (0 = disable)  // 1818
          .port_out = 1819,       // osc port output (0 = disable) // 1819
          .beatInterval = 0,   // heartbeat interval milliseconds (0 = disable)
          .statusInterval = 0 // full beacon interval milliseconds (0 = disable)
      });
  }

  ////////////////// INFO //////////////////////////////////////

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
            }
          });

  // Heap Memory log
  k32->timer->every(1000, []() {
    static int lastheap = 0;
    int heap = ESP.getFreeHeap();
    // LOGF2("Free memory: %d / %d\n", heap, heap - lastheap);
    lastheap = heap;
    if (heap < 50000) LOGF2("WARNING: free memory < 50K, new task might not properly start. %d / %d\n", heap, heap - lastheap);
  });

  

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
} // loop
