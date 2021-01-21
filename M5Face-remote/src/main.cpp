#include <M5Stack.h>
#include <M5ez.h>

#define KEYBOARD_I2C_ADDR 0X08
#define KEYBOARD_INT 5

#define MAIN_DECLARED

#include <K32.h> // https://github.com/KomplexKapharnaum/K32-lib
K32 *k32;

#include "menu.h"

void setup()
{
#include <themes/dark.h>
  ezt::setDebug(INFO);
  ez.begin();

  M5.Power.begin();
  M5.Speaker.mute();

  // ez.screen.clear();

  // ez.header.show("M5-Remote");
  // ez.canvas.lmargin(10);
  // ez.canvas.scroll(true);
  // ez.canvas.font(&FreeSans9pt7b);
  // ez.canvas.println("Hello world");

  //////////////////////////////////////// M5 Face Keyboard ////////////////////////////////
  Wire.begin();
  pinMode(KEYBOARD_INT, INPUT_PULLUP);

  //////////////////////////////////////// K32_lib ////////////////////////////////////
  k32 = new K32();

  /////////////////////////////////////////////// WIFI //////////////////////////////////////
  k32->init_wifi("M5-Remote");
  k32->wifi->staticIP("2.0.0.11", "2.0.0.1", "255.0.0.0");
  // k32->wifi->connect("kxkm24", NULL); //KXKM
  // k32->wifi->connect("mgr4g", NULL); //MGR
  k32->wifi->connect("riri_new", "B2az41opbn6397"); //Riri dev home

  /////////////////////////////////////// MQTT //////////////////////////////////////
  k32->init_mqtt({
      // .broker = "2.0.0.1",// Komplex
      .broker = "2.0.0.10", // Riri dev home
      // .broker = "192.168.43.100",//MGR
      .beatInterval = 0,  // heartbeat interval milliseconds (0 = disable)
      .beaconInterval = 0 // full beacon interval milliseconds (0 = disable)
  });

  mainmenu ();
}

void loop()
{

}