#include <Arduino.h>

#define LULU_VER 76

/////////////////////////////////////////ID/////////////////////////////////////////

#define K32_SET_NODEID 26 // board unique id

// #define RUBAN_TYPE LED_SK6812W_V1 // LED_WS2812_V1  LED_WS2812B_V1  LED_WS2812B_V2  LED_WS2812B_V3  LED_WS2813_V1  LED_WS2813_V2   LED_WS2813_V3  LED_WS2813_V4  LED_SK6812_V1  LED_SK6812W_V1,
#define LULU_ID 1    // permet de calculer l'adresse DMX
#define LULU_TYPE 10 // 1="Sac" 2="Barre" 3="Pince" 4="Fluo" 5="Flex" 6="H&S" 7="Phone" 8="Atom" 9="chariot" 10="power" 11="DMX_strobe" 12="DMX_Par_led"
// #define LULU_UNI 0                // Univers DM



/////////////////////////////////////////Adresse/////////////////////////////////////
int LULU_id;
int LULU_type;
int RUBAN_type;
int RUBAN_size;

String nodeName;
bool wifiMode = true;

/////////////////////////////////////////K32/////////////////////////////////////////


///////////////////////////////////////////////// include ////////////////////////////////////////

#include "k32_loader.h"
#include "settings.h"

///////////////////////////////////////////////// SETUP ////////////////////////////////////////
void setup()
{
  //////////////////////////////////////// K32 modules ////////////////////////////////////
  k32_setup();
  settings();
  LOG("NAME:   " + nodeName + "\n");

  /////////////////////////////////////////////// WIFI //////////////////////////////////////
  LOG("INIT WIFI");
  wifi->setHostname(k32->system->name() + (nodeName != "")?"-"+nodeName:"");
  wifi->staticIP("2.0.0." + String(k32->system->id() + 100), "2.0.0.1", "255.0.0.0");
  wifi->connect("kxkm24", NULL); //KXKM
                                      // wifi->connect("kxkm24lulu", NULL);//KXKM
                                      // wifi->connect("interweb", "superspeed37");
}

///////////////////////////////////////// LOOP /////////////////////////////////////////////////
void loop()
{
  delay(20);
} 