#include <Arduino.h>

#define LULU_VER 58

/////////////////////////////////////////ID/////////////////////////////////////////

#define K32_SET_NODEID 56 // board unique id

// #define RUBAN_TYPE LED_SK6812W_V1 // LED_WS2812_V1  LED_WS2812B_V1  LED_WS2812B_V2  LED_WS2812B_V3  LED_WS2813_V1  LED_WS2813_V2   LED_WS2813_V3  LED_WS2813_V4  LED_SK6812_V1  LED_SK6812W_V1,
#define LULU_ID 2    // permet de calculer l'adresse DMX
#define LULU_TYPE 10 // 1="Sac" 2="Barre" 3="Pince" 4="Fluo" 5="Flex" 6="H&S" 7="Phone" 8="Atom" 9="chariot" 10="power"
// #define LULU_UNI 0                // Univers DM



/////////////////////////////////////////Adresse/////////////////////////////////////
int LULU_id;
int LULU_type;

String nodeName;
bool wifiMode = true;

/////////////////////////////////////////K32/////////////////////////////////////////

#include <K32.h> // https://github.com/KomplexKapharnaum/K32-lib
K32 *k32;

///////////////////////////////////////////////// include ////////////////////////////////////////

#include "settings.h"

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

  /////////////////////////////////////////////// NETWORK //////////////////////////////////////

  wifiMode = true;

  LOGINL("NETWORK: ");
  if (wifiMode)
    LOG("wifi");
  else
    LOG("bluetooth");

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
  }
}

///////////////////////////////////////// LOOP /////////////////////////////////////////////////
void loop()
{
  delay(20);
} 