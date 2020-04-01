#include <Arduino.h>

#define LULU_VER 48

/////////////////////////////////////////ID/////////////////////////////////////////

// #define K32_SET_NODEID 81       // board unique id

// #define RUBAN_TYPE LED_WS2812_V1  // LED_WS2812_V1  LED_WS2812B_V1  LED_WS2812B_V2  LED_WS2812B_V3  LED_WS2813_V1  LED_WS2813_V2   LED_WS2813_V3  LED_WS2813_V4  LED_SK6812_V1  LED_SK6812W_V1,
// #define LULU_ID 1                 // permet de calculer l'adresse DMX
// #define LULU_TYPE 8               // 1="Sac" 2="Barre" 3="Pince" 4="Fluo" 5="Flex" 6="H&S" 7="Phone" 8="Atom"
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
int LULU_adr;

String nodeName;

int RUBAN_type;
int RUBAN_size;

/////////////////////////////////////////lib/////////////////////////////////////////
unsigned long lastRefresh_bat = 0;
#define REFRESH_BAT 100

/////////////////////////////////////////K32/////////////////////////////////////////

#include <K32.h> // remote https://github.com/KomplexKapharnaum/K32-lib
K32 *k32;

///////////////////////////////Lib esp32_digital_led_lib//////////////////////////////
#include "variables.h"

///////////////////////////////////////////////// include ////////////////////////////////////////

#include "k32_settings.h"
#include "bat_custom.h"
#include "mem.h"

///////////////////////////////////////////////// SETUP ////////////////////////////////////////
void setup()
{
  //////////////////////////////////////// K32_lib ////////////////////////////////////
  k32 = new K32();

  //////////////////////////////////////// K32 modules ////////////////////////////////////
  k32->init_stm32();

  k32_settings();
  LOG("LULU:   " + nodeName + "\n");

  // WIFI
  k32->init_wifi(nodeName);
  // k32->wifi->staticIP("2.0.0." + String(k32->system->id() + 100), "2.0.0.1", "255.0.0.0");
  // k32->wifi->connect("kxkm24", NULL);//KXKM
  // k32->wifi->connect("riri_new", "B2az41opbn6397");
  k32->wifi->connect("interweb", "superspeed37");


  // PWM
  k32->init_pwm();

  // LEDS
  k32->init_light( RUBAN_type, RUBAN_size );

  // ADD NEW ANIMS
  k32->light->anim( "artnet",    new K32_anim_dmx() );
  k32->light->anim( "manuframe", new K32_anim_dmx() );

  // INIT TEST
  k32->light->load("test")->set(50)->loop(false);
  k32->light->play()->wait();

  // k32->light->load("color")->set(50, 255, 200, 0, 0);
  // k32->light->play(250)->wait();

  // k32->light->load("dmx")->set(MEM[8], LULU_PATCHSIZE)->set(50);
  // k32->light->play(1000)->wait();
  // TODO: ERROR not going black at end

  // k32->light->load("color")->set(50, 0, 200, 0, 0);
  // k32->light->play(1000);


  

  // Start OSC
  // k32->init_osc({
  //     .port_in = 1818,       // osc port input (0 = disable)  // 1818
  //     .port_out = 1819,      // osc port output (0 = disable) // 1819
  //     .beatInterval = 0,     // heartbeat interval milliseconds (0 = disable)
  //     .beaconInterval = 3000 // full beacon interval milliseconds (0 = disable)
  // });                        // OSC

  // remote
  // k32->init_remote(NUMBER_OF_MEM);

  // bat_de_sac
  // bat_custom_on();

  /////////////////////////////////////////////// ARTNET //////////////////////////////////////
  k32->init_artnet({
      .universe   = LULU_uni,
      .address    = LULU_adr,
      .framesize  = LULU_PATCHSIZE
  });
  
  k32->artnet->onDmx( [](uint8_t* data, int length) {
      k32->light->anim("artnet")->set(data, length);
  });

  k32->wifi->onDisconnect( [&](){ 
    // wifi_status(100);                  
    k32->light->anim("wifi")->setdata(1, 100);  // @rssi -100
    k32->light->anim("artnet")->setdata(0, 0);  // @master 0
  });


  ///////////////////////////////////////////////// ATOM  //////////////////////////////////////
  if (k32->system->hw() == 3)
    pinMode(39, INPUT_PULLUP);


  ///////////////////////////////////////////////// MODULO  //////////////////////////////////////
  // k32->init_modulo();
  
} //setup

///////////////////////////////////////// LOOP /////////////////////////////////////////////////
void loop()
{
  
  /////////////////////    if wifi     ///////////////////////
  if (k32->wifi->isConnected()) {
    //wifi_status(k32->wifi->getRSSI());
  }

  /////////////////////  batterie   ///////////////////////
  if (abs(millis() - lastRefresh_bat) > REFRESH_BAT)
  {
    //get_percentage();
    lastRefresh_bat = millis();
  }

  //////////////////     Click on ESP   ////////////////////
  if (k32->system->hw() <= 2)
  {
    if (k32->system->stm32->clicked())
    {
      manu_counter = (manu_counter+1) % NUMBER_OF_MEM;

      k32->light->load("manuframe")->set( MEM[manu_counter], LULU_PATCHSIZE );
      k32->light->play();

      // active_frame(manu_counter);
      // preview_frame(manu_counter);
    }
  }

  //////////////////    Click on Atom    ////////////////////
  else if (k32->system->hw() == 3)
  {
    if ((digitalRead(39) >= 1) && (state_btn != false)) state_btn = false;
    else if ((digitalRead(39) <= 0) && (state_btn != true))
    {
      state_btn = true;
      manu_counter = (manu_counter+1) % NUMBER_OF_MEM;

      k32->light->load("manuframe")->set( MEM[manu_counter], LULU_PATCHSIZE );
      k32->light->play();

      // active_frame(manu_counter);
      // preview_frame(manu_counter);
    }
  }

  //////////////////////  REMOTE CONTROL   ///////////////////////////
/*
  remote_status(k32->remote->getState()); //

  int gpm = k32->remote->getPreviewMacro();
  if (last_gpm != gpm)
  {
    last_gpm = gpm;
    preview_frame(gpm);
  } // getPreviewMacro()

  if (k32->remote->getState() != REMOTE_AUTO)
  {
    // Remote Active
    gpm = k32->remote->getActiveMacro();
    active_frame(gpm);
  } // ! REMOTE_AUTO

  */
} //loop