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
#define LULU_PREVSIZE 25 // Taille du patch DMX pour cet Fixture

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
#define REFRESH_INFO 300

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

  // ADD NEW ANIMS (name, anim, strip, size, offset)
  k32->light->anim( "test0",   new K32_anim_test, 0 );
  k32->light->anim( "test1",   new K32_anim_test, 1 );

  k32->light->anim( "artnet",  new K32_anim_dmx, 0, RUBAN_size);
  k32->light->anim( "manu",    new K32_anim_dmx, 0, RUBAN_size);

  // k32->light->anim( "preview", new K32_anim_preview, 0, 6, RUBAN_size+2);
  // k32->light->anim( "remote",  new K32_anim_remote,  0, 6, RUBAN_size+2);
  // k32->light->anim( "rssi",    new K32_anim_rssi,    0, 6, RUBAN_size+2);
  // k32->light->anim( "battery", new K32_anim_battery, 0, 6, RUBAN_size+2);


  // INIT TEST
    // k32->light->anim("test0")->push(50)->loop(false)->play()->wait();
    // k32->light->anim("test1")->push(50)->loop(false)->play()->wait();

  // COLOR T0EST
    // k32->light->anim("colorA", new K32_anim_color, 0, 10, 5 );
    // k32->light->anim("colorB", new K32_anim_color, 0,  1, 1 );

    // k32->light->anim("colorA")->push(50, 255, 200, 0, 0)->play(1000);

    // k32->light->anim("colorB")->push(255, 255, 0, 0, 0)->play();  
    // k32->light->anim("colorB")->modulate(1, "sin_red",   new K32_mod_sinus(120, 0, 255)  );
    // k32->light->anim("colorB")->modulate(2, "sin_green", new K32_mod_sinus(1000, 0, 180) );
    // k32->light->anim("colorB")->modulate(3, "ran_blue",  new K32_mod_random(1000, 0, 255) );
    // delay(1000);
    // k32->light->anim("colorB")->modulate("sin_red")->pause();
    // delay(1000);
    // k32->light->anim("colorB")->modulate("sin_red")->param(0, 3000)->play();

  K32_anim* artnet = k32->light->anim("artnet");
  artnet->push(MEM[8], LULU_PATCHSIZE)->setdata(0,100)->play();
  artnet->modulate(7, "sin_pos", new K32_mod_sinus(1000, 0, 255));


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
  
  // event: new artnet frame received
  //
  k32->artnet->onDmx( [](uint8_t* data, int length) 
  {
      k32->light->anim("artnet")->push(data, length);
  });

  // event: wifi lost
  //
  k32->wifi->onDisconnect( [&]()
  { 
    k32->light->anim("artnet")->push(0);  // @master 0
  });


  ///////////////////////////////////////////////// ATOM  //////////////////////////////////////
  if (k32->system->hw() == 3) pinMode(39, INPUT_PULLUP);


  ///////////////////////////////////////////////// INFO //////////////////////////////////////
  //
  k32->timer->every(REFRESH_INFO, [](){
    // k32->light->anim("battery")->push( k32->system->stm32->battery() );
    // k32->light->anim("rssi")->push( k32->wifi->getRSSI() );
  });

} //pushup

///////////////////////////////////////// LOOP /////////////////////////////////////////////////
void loop()
{

  //////////////////     Click on ESP   ////////////////////
  if (k32->system->stm32->clicked())
  {
    manu_counter = (manu_counter+1) % NUMBER_OF_MEM;

    k32->light->anim("manu")->push( MEM[manu_counter], LULU_PATCHSIZE );
    // k32->light->anim("preview")->push( MEM_PREV[manu_counter], LULU_PREVSIZE );
  }


  //////////////////    Click on Atom    ////////////////////
  if (k32->system->hw() == 3)
  {
    if ((digitalRead(39) >= 1) && (state_btn != false)) state_btn = false;
    else if ((digitalRead(39) <= 0) && (state_btn != true))
    {
      state_btn = true;
      manu_counter = (manu_counter+1) % NUMBER_OF_MEM;

      k32->light->anim("manu")->push( MEM[manu_counter], LULU_PATCHSIZE );
      // k32->light->anim("preview")->push( MEM_PREV[manu_counter], LULU_PREVSIZE );

    }
  }

  //////////////////////  REMOTE CONTROL   ///////////////////////////

  // k32->light->anim("remote")->push( k32->remote->getState() );

  // int gpm = k32->remote->getPreviewMacro();
  // if (last_gpm != gpm)
  // {
  //   last_gpm = gpm;
  //   // k32->light->anim("preview")->push( MEM_PREV[gpm], LULU_PREVSIZE );
  // }

  // if (k32->remote->getState() != REMOTE_AUTO)
  // {
  //   // Remote Active
  //   gpm = k32->remote->getActiveMacro();
  //   k32->light->anim("manu")->push( MEM[gpm], LULU_PATCHSIZE );
    
  // }


} //loop