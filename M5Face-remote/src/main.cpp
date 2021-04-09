// platformio run --target uploadfs

#define DEBUGi

///////////////////////////////////////////// ID ////////////////////////////////////////////
#define K32_SET_NODEID 9003 // board unique id  9xxx for M5

//////////////////////////////////////////// K32 ////////////////////////////////////////////
#include <K32.h> // https://github.com/KomplexKapharnaum/K32-lib
K32 *k32;

//////////////////////////////////////////// M5 /////////////////////////////////////////////
#include "FS.h"
#include <M5Stack.h>
#include "K32_M5ez.h"

#define KEYBOARD_I2C_ADDR 0X08
#define KEYBOARD_INT 5

#define MAIN_DECLARED // Menu ez

//////////////////////////////////////////// include ////////////////////////////////////////
#include "tableau.h"
#include "incombeat.h"
#include "incoming.h"
#include "main_menu.h"

////\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//
//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\ SETUP //\\//\\//\\//\\//\\//\\//\\//\\//\\//\\/
////\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//
void setup()
{
  //////////////////////////////////////// K32_lib //////////////////////////////////////////
  k32 = new K32();

#include "themes/dark.h"
  ezt::setDebug(INFO);
  ez.begin(k32);

  M5.Power.begin();
  M5.Speaker.mute();

  if (!SPIFFS.begin(true))
  {
    Serial.println("SPIFFS Mount Failed");
    return;
  }
  M5.Lcd.drawJpgFile(SPIFFS, "/KXKM_logo.jpg", 0, 0);
  M5.update();
  delay(2000);

  //////////////////////////////////////// M5 Face Keyboard /////////////////////////////////
  Wire.begin();
  pinMode(KEYBOARD_INT, INPUT_PULLUP);

  /////////////////////////////////////////////// WIFI //////////////////////////////////////
  k32->init_wifi("M5-Remote");
  k32->wifi->staticIP("2.0.0.93", "2.0.0.1", "255.0.0.0");
  // k32->wifi->connect("kxkm24", NULL); //KXKM
  // k32->wifi->connect("mgr4g", NULL); //MGR
  k32->wifi->connect("riri_new", "B2az41opbn6397"); //Riri dev home

  // ez.wifi.add("SSID", "KEY", "IP", "MASK", "GATEWAY","BROKER");
  ez.wifi.add("kxkm24", "", "2.0.0.93", "255.0.0.0", "2.0.0.1", "2.0.0.1");                        //KXKM
  ez.wifi.add("kxkm24lulu", "", "2.0.0.93", "255.0.0.0", "2.0.0.1", "2.0.0.1");                    //KXKM lulu
  ez.wifi.add("kxkm-wifi", "KOMPLEXKAPHARNAUM", "0.0.0.0", "0.0.0.0", "0.0.0.0");                  //KXKM
  ez.wifi.add("mgr4g", "", "0.0.0.0", "0.0.0.0", "0.0.0.0", "0.0.0.0");                            //MGR
  ez.wifi.add("interweb", "superspeed37", "0.0.0.0", "0.0.0.0", "0.0.0.0", "0.0.0.0");             //Maigre dev home
  ez.wifi.add("riri_new", "B2az41opbn6397", "2.0.0.13", "255.0.0.0", "192.168.0.254", "2.0.0.10"); //Riri dev home
  ez.wifi.add("riri_new", "B2az41opbn6397", "0.0.0.0", "0.0.0.0", "0.0.0.0", "0.0.0.0");           //Riri dev home

  ///////////////////////////////////////////// MQTT ////////////////////////////////////////
  k32->init_mqtt();

  k32->mqtt->subscribe({.topic = "k32/monitor/beat",
                        .qos = 0,
                        .callback = [](char *payload, size_t length) {
                          incombeat(payload, length);
                        }});

  k32->mqtt->subscribe({.topic = "k32/monitor/status",
                        .qos = 0,
                        .callback = [](char *payload, size_t length) {
                          incoming(payload, length);
                        }});

  k32->mqtt->start({
      // .broker = "2.0.0.1",// Komplex
      .broker = "2.0.0.10", // Riri dev home
      // .broker = "192.168.43.100",//MGR
      .beatInterval = 0,  // heartbeat interval milliseconds (0 = disable)
      .beaconInterval = 0 // full beacon interval milliseconds (0 = disable)
  });

  ///////////////////////////////////////////////// CORE //////////////////////////////////////
  //  create a task that will be executed in the Map1code() function, with priority 1 and executed on core 0
  // xTaskCreatePinnedToCore(handleClient, "handleClient", 4096, NULL, 1, NULL, 0); // core 0 = wifi

  ez.Spiffs();
  ///////////////////////////////////////////// MENU LOOP ////////////////////////////////////////
  main_menu();
}

///////////////////////////////////////////// LOOP //////////////////////////////////////////
void loop()
{
  // server.handleClient();
  // if(k32->mqtt->isConnected()) {

  // }

}