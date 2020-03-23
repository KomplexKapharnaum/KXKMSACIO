#include <Arduino.h>

#define LULU_VER 48

/////////////////////////////////////////ID/////////////////////////////////////////

// #define K32_SET_NODEID 81       // board unique id    

// #define RUBAN_TYPE LED_WS2812_V1  // LED_WS2812_V1  LED_WS2812B_V1  LED_WS2812B_V2  LED_WS2812B_V3  LED_WS2813_V1  LED_WS2813_V2   LED_WS2813_V3  LED_WS2813_V4  LED_SK6812_V1  LED_SK6812W_V1,
// #define LULU_ID 1                 // permet de calculer l'adresse DMX
#define LULU_TYPE 1               // 1="Sac" 2="Barre" 3="Pince" 4="Fluo" 5="Flex" 6="H&S" 7="Phone" 8="Atom"
// #define LULU_UNI 0                // Univers DM

/////////////////////////////////////////Debug///////////////////////////////////////
#define DEBUG 1
// #define DEBUG_dmx 1
// #define DEBUG_dmxframe 1
// #define DEBUG_STR 1
// #define DEBUG_calibre_btn 1
// #define DEBUG_btn 1

#define LULU_PATCHSIZE 19 // Taille du patch DMX pour cet Fixture
#define LEDS_ABSOLUTE_MAX 300



/////////////////////////////////////////Adresse/////////////////////////////////////
int LULU_id;
int LULU_type;
int LULU_uni;
int adr;

String nodeName;
int RUBAN_type;
String L_type;

int NUM_LEDS_PER_STRIP_max;
int NUM_LEDS_PER_STRIP;
int N_L_P_S;

/////////////////////////////////////////lib/////////////////////////////////////////
#include <ArtnetWifi.h> //https://github.com/rstephan/ArtnetWifi
unsigned long lastRefresh = 0;
#define REFRESH 10
unsigned long lastRefresh_bat = 0;
#define REFRESH_BAT 100

/////////////////////////////////////////K32/////////////////////////////////////////

#include <K32.h>  // remote https://github.com/KomplexKapharnaum/K32-lib

K32 *k32;

///////////////////////////////Lib esp32_digital_led_lib//////////////////////////////

#define min(m, n) ((m) < (n) ? (m) : (n))
#define NUM_STRIPS 2
int numberOfChannels;
strand_t STRANDS[NUM_STRIPS];
strand_t *strands[] = {&STRANDS[0], &STRANDS[1]};

#include "variables.h"

///////////////////////////////////// Artnet settings /////////////////////////////////////
ArtnetWifi artnet;
////const int startUniverse = 0; // CHANGE FOR YOUR SETUP most software this is 1, some software send out artnet first universe as 0.
int startUniverse; // CHANGE FOR UNIVERSE.

// Check if we got all universes
int maxUniverses;
bool universesReceived[16];
bool sendFrame = 1;
int previousDataLength = 0;

///////////////////////////////////////////////// include ////////////////////////////////////////

#include "k32_settings.h"
#include "bat_custom.h"
#include "Black.h"
#include "color_rgbw.h"
#include "onDmxFrame.h"
#include "mem.h"
#include "manumode.h"
#include "leds.h"
#include "do_effet_0.h"
#include "do_zoom.h"
#include "effet_modulo.h"
#include "Get_percentage.h"
#include "X_task.h"

///////////////////////////////////////////////// SETUP ////////////////////////////////////////
void setup()
{
  //////////////////////////////////////// K32_lib ////////////////////////////////////
  k32 = new K32();

  //////////////////////////////////////// K32 modules ////////////////////////////////////
  k32->init_stm32();
  k32_settings();

  // LEDS
  // k32->init_light( RUBAN_type, NUM_LEDS_PER_STRIP_max );

  // PWM
  k32->init_pwm();

  // WIFI
  k32->init_wifi(nodeName);
  // k32->wifi->staticIP("2.0.0." + String(k32->system->id() + 100), "2.0.0.1", "255.0.0.0");
  // k32->wifi->connect("interweb", "superspeed37");
  k32->wifi->connect("riri_new", "B2az41opbn6397");///

  // Start OSC
  k32->init_osc({
      .port_in = 1818,       // osc port input (0 = disable)  // 1818
      .port_out = 1819,      // osc port output (0 = disable) // 1819
      .beatInterval = 0,     // heartbeat interval milliseconds (0 = disable)
      .beaconInterval = 3000 // full beacon interval milliseconds (0 = disable)
  });                        // OSC

  // remote
  k32->init_remote(NUMBER_OF_MEM);

  // bat_de_sac
  bat_custom_on();

  LOG("Starting " + nodeName);

  ///////////////////////////////////////////////// LEDS //////////////////////////////////////
  leds_init();
  
  initTest();

  /////////////////////////////////////////////// ARTNET //////////////////////////////////////
  artnet.begin();
  // artnet.setArtDmxCallback(onDmxFrame);
  artnet.setArtDmxCallback(onArtNetFrame);

  ///////////////////////////////////////////////// INIT //////////////////////////////////////
  

  ///////////////////////////////////////////////// CORE //////////////////////////////////////
  //  create a task that will be executed in the Map1code() function, with priority 1 and executed on core 0
  xTaskCreatePinnedToCore(Map1code, "Map1code", 4096, NULL, 1, NULL, 1); // core 1 = loop
  xTaskCreatePinnedToCore(effTask, "effTask", 4096, NULL, 1, NULL, 0);   // core 0 = wifi
  ///////////////////////////////////////////////// osc //////////////////////////////////////

  ///////////////////////////////////////////////// ATOM  //////////////////////////////////////
  if (k32->system->hw() == 3) pinMode(39, INPUT_PULLUP);
  ///////////////////////////////////////////////// MODULO  //////////////////////////////////////

  k32->init_modulo();

} //setup

///////////////////////////////////////// LOOP /////////////////////////////////////////////////
void loop()
{
  eff_modulo();

  /////////////////////    if wifi     ///////////////////////
  if (k32->wifi->isConnected())
  {
    if (k32->remote->getState() != REMOTE_MANULOCK || state_btn == false)
      artnet.read();
    lostConnection = false;
  } // if wifi

  /////////////////////   if millis    ///////////////////////
  if ((millis() - lastRefresh) > REFRESH)
  {
    if (!k32->wifi->isConnected() && !lostConnection)
    {
      if (k32->remote->getState() != REMOTE_MANULOCK)
        ledBlack(); //passe led noir
      lostConnection = true;
    }
    lastRefresh = millis();
  } // if millis

  /////////////////////  batterie   ///////////////////////
  if ((millis() - lastRefresh_bat) > REFRESH_BAT)
  {
    get_percentage();
    lastRefresh_bat = millis();
  }// batterie

  //////////////// MILLIS overflow protection //////////////
  if (millis() < lastRefresh)
    lastRefresh = millis();
  if (millis() < lastRefresh_bat)
    lastRefresh_bat = millis();

  //////////////////     Click on ESP   ////////////////////
  if (k32->system->hw() <= 2) {
    if (k32->system->stm32->clicked())
    {
      if (state_btn == false) 
      {
        state_btn = true;
      }
      manu_frame(++manu_counter);
    }// Click on ESP
  }

  //////////////////    Click on Atom    ////////////////////
  else if (k32->system->hw() == 3) {
    if ((digitalRead(39) >= 1) && (state_btn != false))
    {
      state_btn = false;
    }
    if ((digitalRead(39) <= 0) && (state_btn != true))
    {
      state_btn = true;
      manu_frame(++manu_counter);
    }
  }

  //////////////////////  REMOTE CONTROL   ///////////////////////////

  remote_status(k32->remote->getState()); // 

  int gpm = k32->remote->getPreviewMacro();
  if (last_gpm != gpm)
  {
    last_gpm =gpm;
  preview_frame(gpm);
  }// getPreviewMacro()
  
  if (k32->remote->getState() != REMOTE_AUTO)
  {
    // Remote Active
    gpm = k32->remote->getActiveMacro();
    active_frame(gpm);
    manu_frame(gpm);
  } // ! REMOTE_AUTO

if (state_btn == true){
manu_frame(manu_counter);
}// rafrechire les modulos si manu btn

} //loop