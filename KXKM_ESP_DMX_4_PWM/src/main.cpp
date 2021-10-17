#include <Arduino.h>

#define LULU_VER 89
#define LULU_TYPE 1
// 1="Sac" 2="Barre" 3="Pince" 4="Fluo" 5="Flex" 6="H&S" 7="Phone" 8="Atom" 9="chariot"
// 10="power" 11="DMX_strobe" 12="DMX_Par_led" 13="NODE_dmx_thru"
// 20="Cube_str" 21="Cube_par"  22="Cube_MiniKOLOR" 23="Cube_Elp"
// 30="Sucette_parled" 31="Sucette_Strobe" 32="Sucette_MiniKolor" 33="sucette_Elp"  34="Banc"
// 40="New_Fluo"
// 50="strip to elp dmx"
// 60="Lyre audio dmx + strip"
// 70="Strobe" 71="4x Strobe"


/////////////////////////////////////////ID/////////////////////////////////////////

#define K32_SET_NODEID 337  // board unique id
#define K32_SET_CHANNEL 1   // board channel mqtt
#define LULU_ID 1           // permet de calculer l'adresse DMX
#define LULU_UNI 1          // univers artnet
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


int LULU_uni;
int LULU_id;

String nodeName;


/////////////////////////////////////////K32/////////////////////////////////////////

#include "k32_loader.h"

///////////////////////////////////////////////// include ////////////////////////////////////////

#include "anim_monitoring.h"
#include "anim_dmx_test.h"
#include "anim_dmx_strip.h"
#include "anim_datathru.h"
#include "boutons.h"
#include "test.h"

///////////////////////////////////////////////// SETUP ////////////////////////////////////////
void setup()
{
  k32_setup();
  boutons_init();

  LOG("\nNAME:   " + nodeName );
  LOGF("CHANNEL: %d\n\n", k32->system->channel());

  /////////////////////////////////////////////// LIGHT //////////////////////////////////////

  // TEST Sequence
  light_tests();

  // ANIM leds - artnet
  light->anim("artnet", new Anim_dmx_strip, LULU_STRIP_SIZE)->attach(strip[0])->play();

  // ANIM leds - manuframe
  light->anim("manu", new Anim_dmx_strip, LULU_STRIP_SIZE)->attach(strip[0]);

  // ANIM leds - monitoring
  light->anim("battery", new Anim_battery, 4, LULU_STRIP_SIZE + 1)->attach(strip[0])->master(LULU_PREV_MASTER)->play();
  light->anim("remote", new Anim_remote, LULU_PREV_SIZE + 4, LULU_STRIP_SIZE + 6)->attach(strip[0])->master(LULU_PREV_MASTER)->play();
  light->anim("preview", new Anim_preview, LULU_PREV_SIZE, LULU_STRIP_SIZE + 8)->attach(strip[0])->master(LULU_PREV_MASTER)->play();
  light->anim("rssi", new Anim_rssi, 1, LULU_STRIP_SIZE + 17)->attach(strip[0])->master(LULU_PREV_MASTER * 1.5)->play();

  // ANIM dmx fixtures 
  light->anim("datathru", new Anim_datathru , DMXFIXTURE_PATCHSIZE / 4)->play();
  for (int k=0; k<DMX_N_FIXTURES; k++)
    if (fixs[k]) light->anim("datathru")->attach(fixs[k]);

  // REMOTE
  remote->setMacroMax(PRESET_COUNT); // TODO: clean MEM loading (and setMemMax)

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

    String router = "2.0.0.1";
    String basenet = router.substring(0, router.indexOf('.', router.indexOf('.')+1));   // 2.0.
    String subnet = "0";
    if (k32->system->hw() == 4) subnet = "1";

    wifi->staticIP(basenet + subnet + "." + String(k32->system->id() + 100), router, "255.0.0.0");

    wifi->connect("kxkm24", NULL); //KXKM 24
    // wifi->connect("kxkm24lulu", NULL);                                                         //KXKM 24 lulu
    // wifi->connect("mgr4g", NULL);                                                              //Maigre dev
    // wifi->connect("interweb", "superspeed37");                                                 //Maigre dev home
    // wifi->connect("riri_new", "B2az41opbn6397");                                               //Riri dev home
    // TODO: if wifi->connect ommited = crash on mqtt/artnet/osc

    ////////////////// ARTNET
    #if LULU_TYPE == 60
        int FRAME_size = LYRE_PATCHSIZE + 9; // 9: MEM R G B W PWM1 PWM2 PWM3 PWM4
    #else
        int FRAME_size = LULU_PATCHSIZE;
    #endif
        int ARTNET_address = (1 + (LULU_id - 1) * LULU_PATCHSIZE);

    
    

    // ARTNET: subscribe dmx frame
    artnet->onDmx( {
      .address    = ARTNET_address, 
      .framesize  = FRAME_size, 
      .callback   = [](const uint8_t *data, int length) 
      { 
        
        if (ARTNET_TO_DMXDIRECT) 
          light->anim("datathru")->push(data, min(length, DMXFIXTURE_PATCHSIZE));
        
        if (ARTNET_TO_STRIPS)
          light->anim("artnet")->push(data, min(length, LULU_PATCHSIZE));

        // LYRE
        #if LULUTYPE == 60
          if (length >= DMXFIXTURE_PATCHSIZE + 9)
          {
            const uint8_t *dataStrip = &data[DMXFIXTURE_PATCHSIZE];

            // MEM ou ARTNET FRAME
            if (dataStrip[0] > 0 && dataStrip[0] <= PRESET_COUNT)
              remote->stmSetMacro(dataStrip[0] - 1);
            else
            {
              int stripframe[LULU_PATCHSIZE] = {255, dataStrip[1], dataStrip[2], dataStrip[3], dataStrip[4], 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 255, dataStrip[5], dataStrip[6], dataStrip[7], dataStrip[8]};
              light->anim("artnet")->push(stripframe, LULU_PATCHSIZE);
              remote->setState(REMOTE_AUTO);
            }
          }
        #endif

        // LOGINL("ARTFRAME: ");
        // LOGF("length=%d ", length);
        // for (int k = 0; k < length; k++)
        //   LOGF("%d ", data[k]);
        // LOG();
      }
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
          .broker = router.c_str(), // Komplex
          // .broker = "2.0.0.10", // Riri dev home
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
  }

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
  //   LOGF2("Free memory: %d / %d\n", heap, heap - lastheap);
  //   lastheap = heap;
  // });

  load_mem(light->anim("manu"), 15); //auto play
  light->anim("manu")->play();       //auto play
} // setup

///////////////////////////////////////// LOOP /////////////////////////////////////////////////
void loop()
{

  /////////////////// BOUTONS ///////////////////////
  boutons_loop();

  delay(20);

} //loop
