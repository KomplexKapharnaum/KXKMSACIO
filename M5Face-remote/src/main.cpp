#include <M5Stack.h>
#include <M5ez.h>

#define KEYBOARD_I2C_ADDR 0X08
#define KEYBOARD_INT 5

#define MAIN_DECLARED // Menu ez

///////////////////////////////////////////// ID ////////////////////////////////////////////
#define K32_SET_NODEID 9001 // board unique id  9xxx for M5

//////////////////////////////////////////// K32 ////////////////////////////////////////////
#include <K32.h> // https://github.com/KomplexKapharnaum/K32-lib
K32 *k32;

#include "tableau.h"
#include "incoming.h"
#include "menu.h"

////\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//
//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\ SETUP //\\//\\//\\//\\//\\//\\//\\//\\//\\//\\/
////\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//
void setup()
{
#include <themes/dark.h>
  ezt::setDebug(INFO);
  ez.begin();

  M5.Power.begin();
  M5.Speaker.mute();

  //////////////////////////////////////// M5 Face Keyboard /////////////////////////////////
  Wire.begin();
  pinMode(KEYBOARD_INT, INPUT_PULLUP);

  //////////////////////////////////////// K32_lib //////////////////////////////////////////
  k32 = new K32();

  /////////////////////////////////////////////// WIFI //////////////////////////////////////
  k32->init_wifi("M5-Remote");
  k32->wifi->staticIP("2.0.0.11", "2.0.0.1", "255.0.0.0");
  // k32->wifi->connect("kxkm24", NULL); //KXKM
  // k32->wifi->connect("mgr4g", NULL); //MGR
  k32->wifi->connect("riri_new", "B2az41opbn6397"); //Riri dev home

  ///////////////////////////////////////////// MQTT ////////////////////////////////////////
  k32->init_mqtt();

      k32->mqtt->subscribe({
      .topic = "k32/monitor/beat",
      .qos = 0,
      .callback = [](char *payload, size_t length) 
                  {
                    LOGINL("-- BEAT received:");
                    LOGINL(" ");
                    LOG(payload);
                  }
    });

  k32->mqtt->subscribe({
    .topic = "k32/monitor/status",
    .qos = 0,
    .callback = [](char *payload, size_t length) 
                {
                  LOGINL("-- STATUS received:");
                  LOGINL(" ");
                  LOG(payload);
                  incoming (payload,length);
                }
  });

  k32->mqtt->start({
      // .broker = "2.0.0.1",// Komplex
      .broker = "2.0.0.10", // Riri dev home
      // .broker = "192.168.43.100",//MGR
      .beatInterval = 0,  // heartbeat interval milliseconds (0 = disable)
      .beaconInterval = 0 // full beacon interval milliseconds (0 = disable)
  });

  mainmenu();
}

///////////////////////////////////////////// LOOP //////////////////////////////////////////
void loop()
{
}