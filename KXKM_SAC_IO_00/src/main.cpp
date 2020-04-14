#include <Arduino.h>

#define LULU_VER 51

/////////////////////////////////////////ID/////////////////////////////////////////

// #define K32_SET_NODEID 82       // board unique id

// #define RUBAN_TYPE LED_SK6812W_V1    // LED_WS2812_V1  LED_WS2812B_V1  LED_WS2812B_V2  LED_WS2812B_V3  LED_WS2813_V1  LED_WS2813_V2   LED_WS2813_V3  LED_WS2813_V4  LED_SK6812_V1  LED_SK6812W_V1,
// #define LULU_ID 1                 // permet de calculer l'adresse DMX
// #define LULU_TYPE 1               // 1="Sac" 2="Barre" 3="Pince" 4="Fluo" 5="Flex" 6="H&S" 7="Phone" 8="Atom"
// #define LULU_UNI 0                // Univers DM

/////////////////////////////////////////Debug///////////////////////////////////////

// #define DEBUG_dmx 1              // !!! IMPLEMENT
// #define DEBUG_dmxframe 1
// #define DEBUG_STR 1
// #define DEBUG_calibre_btn 1
// #define DEBUG_btn 1

#define LULU_PATCHSIZE 18 // Taille du patch DMX pour cet Fixture
#define LULU_PREVPIX 6    // Nombre de pixel pour la prévisu

#define MASTER_PREV 40    // Luminosité prévisu

#define REFRESH_INFO 1000 // Refresh affichage Wifi & Battery

/////////////////////////////////////////Adresse/////////////////////////////////////
int LULU_id;
int LULU_type;
int LULU_uni;
int LULU_adr;

String nodeName;

int RUBAN_type;
int RUBAN_size;


/////////////////////////////////////////K32/////////////////////////////////////////

#include <K32.h>          // https://github.com/KomplexKapharnaum/K32-lib
K32 *k32;

///////////////////////////////////////////////// include ////////////////////////////////////////

#include "settings.h"
#include "mem.h"
#include "anim_monitoring.h"
#include "anim_dmx.h"
#include "boutons.h"
#include "bat_custom.h"
#include "test.h"


///////////////////////////////////////////////// SETUP ////////////////////////////////////////
void setup()
{
  //////////////////////////////////////// K32_lib ////////////////////////////////////
  k32 = new K32();

  //////////////////////////////////////// K32 modules ////////////////////////////////////
  k32->init_stm32();

  settings();
  LOG("LULU:   " + nodeName + "\n");

  // WIFI
    k32->init_wifi(nodeName);
    k32->wifi->staticIP("2.0.0." + String(k32->system->id() + 100), "2.0.0.1", "255.0.0.0");
    // k32->wifi->connect("kxkm24", NULL);//KXKM
    k32->wifi->connect("riri_new", "B2az41opbn6397");
    // k32->wifi->connect("interweb", "superspeed37");


  // PWM
    k32->init_pwm();


  /////////////////////////////////////////////// LIGHT //////////////////////////////////////

  // LEDS
    k32->init_light( RUBAN_type, RUBAN_size+30 );

    light_tests();

  // ADD NEW ANIMS (strip, name, anim, size, offset=0)
    
    // ANIM artnet
    k32->light->anim( 0, "artnet",  new Anim_dmx, RUBAN_size)->play();

    // ANIM manuframe
    k32->light->anim( 0, "manu",    new Anim_dmx, RUBAN_size);

    // ANIM monitoring
    k32->light->anim( 0, "battery", new Anim_battery,  4, RUBAN_size+1)->play();
    k32->light->anim( 0, "rssi",    new Anim_rssi,     1, RUBAN_size+17)->master(MASTER_PREV*1.5)->play();
    k32->light->anim( 0, "remote",  new Anim_remote,   LULU_PREVPIX+4, RUBAN_size+6) ->master(MASTER_PREV)->play();
    k32->light->anim( 0, "preview", new Anim_preview,  LULU_PREVPIX,   RUBAN_size+8) ->master(MASTER_PREV)->play();

  // Start OSC
    // k32->init_osc({
    //     .port_in = 1818,       // osc port input (0 = disable)  // 1818
    //     .port_out = 1819,      // osc port output (0 = disable) // 1819
    //     .beatInterval = 0,     // heartbeat interval milliseconds (0 = disable)
    //     .beaconInterval = 3000 // full beacon interval milliseconds (0 = disable)
    // });                        // OSC

  // Remote
    k32->init_remote(NUMBER_OF_MEM);

  // BAT Custom
    bat_custom_on();

  // Boutons
    boutons_init();

  // sampler jpeg sd
    // k32->init_samplerjpeg();


  /////////////////////////////////////////////// ARTNET //////////////////////////////////////
  k32->init_artnet({
      .universe   = LULU_uni,
      .address    = LULU_adr,
      .framesize  = LULU_PATCHSIZE
  });
 

  // EVENT: new artnet frame received
    k32->artnet->onDmx( [](uint8_t* data, int length) 
    {
      // Force Auto
      if (data[14] > 250) 
        k32->remote->setState(REMOTE_AUTO_LOCK);


      // Draw
      k32->light->anim("artnet")->push(data, length);

      // Set PWM  // !!! TODO: meilleur manière pour débrayer la lampe -> boutons.h ?
      if (k32->light->anim("artnet")->isPlaying())
        if (k32->remote->getLamp() == -1)
        {
          k32->pwm->set(0, data[16]);
          k32->pwm->set(1, data[17]);
          LOGF2("ARTNET: -> Lamp %d %d \n", data[16], data[17]);
        }

    });


  // EVENT: wifi lost
    k32->wifi->onDisconnect( [&]()
    { 
      LOG("WIFI: connection lost..");

      k32->light->anim("artnet")->push(0);  // @master 0   
    });


  ///////////////////// INFO //////////////////////////////////////

  // Monitoring refresh
    k32->timer->every(REFRESH_INFO, []()
    {
      k32->light->anim("battery")->push( k32->system->stm32->battery() );
      k32->light->anim("rssi")->push( k32->wifi->getRSSI() );
    });


  // Remote status refresh
    k32->timer->every(50, []()
    {
      k32->light->anim("remote")->push( k32->remote->getState() );
    });


  // Heap Memory log
    k32->timer->every(1000, []()
    { 
      static int lastheap = 0;
      int heap = ESP.getFreeHeap();
      // LOGF2("Free memory: %d / %d\n", heap, heap-lastheap);
      lastheap = heap;
    });

}

///////////////////////////////////////// LOOP /////////////////////////////////////////////////
void loop()
{

  ///////////////////// BOUTONS ///////////////////////
  boutons_loop();

  delay(20);

} //loop