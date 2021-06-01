////////////////// DEFAULT VALUE (can be overriden) /////////////////

#define L_NAME          "Unknown"
#define RUBAN_SIZE      0

#define LULU_PATCHSIZE  20  // Size of artnet frame to listen to

#define DMXOUT_ADDR     1   // DMX output start address
#define OUT_PATCHSIZE   20  // DMX passthru size (frame size to copy from Artnet to DMX)

#define ON_NO_WIFI      0
#define FAKE_CURRENT    0

#define LULU_PREVPIX 40

#define MASTER_PREV 40    // Luminosité prévisu

#define REFRESH_INFO 1000 // Refresh affichage Wifi & Battery


/////////////////////////////////////////Debug///////////////////////////////////////

// #define DEBUG_dmx 1              // !!! IMPLEMENT
// #define DEBUG_dmxframe 1
// #define DEBUG_STR 1
// #define DEBUG_calibre_btn 1
#define DEBUG_btn 1


/////////////////////////////////////////def RUBAN_TYPE & LULU_TYPE /////////////////////////////////////////

#ifdef LULU_TYPE

#if LULU_TYPE == 1
  #define L_NAME "Sac"
  #define RUBAN_SIZE 120
  #define FAKE_CURRENT 12500
  // #include "macro/Type/SK/mem.h"

  #include "macro/Type/4pwm/mem_4pwm.h" // defo
  #include "macro/Type/SK/mem_sk.h"     // defo
  #include "macro/mem_sac_pwm.h"

#elif LULU_TYPE == 2
  #define L_NAME "Barre"
  #define RUBAN_SIZE 120
  // #include "macro/Type/SK/mem.h" // mem global sk & pwm

  #include "macro/Type/4pwm/mem_4pwm.h" // defo
  // #include "macro/Type/SK/mem_sk.h"  // defo
  // #include "macro/Show/larochelle/mem_sk_roch.h"
  #include "macro/Show/esch/mem_sk_esch.h"
  #include "macro/mem_barre_pwm.h"

#elif LULU_TYPE == 3
  #define L_NAME "Pince"
  #define RUBAN_SIZE 17
  // #include "macro/Type/SK/mem.h" // mem global sk & pwm

  #include "macro/Type/4pwm/mem_4pwm.h" // defo
  #include "macro/Type/SK/mem_sk.h"     // defo
  #include "macro/mem_pince_pwm.h"

#elif LULU_TYPE == 4
  #define L_NAME "Fluo"
  #define RUBAN_SIZE 73
  // #include "macro/Type/SK/mem.h" // mem global sk & pwm

  #include "macro/Type/4pwm/mem_4pwm.h" // defo
  #include "macro/Type/SK/mem_sk.h"     // defo
  #include "macro/mem_fluo_pwm.h"

#elif LULU_TYPE == 5
  #define L_NAME "Flex"
  #define RUBAN_SIZE 186
  // #include "macro/Type/SK/mem.h" // mem global sk & pwm

  #include "macro/Type/4pwm/mem_4pwm.h" // defo
  #include "macro/Type/SK/mem_sk.h"     // defo
  #include "macro/mem_flex_pwm.h"

#elif LULU_TYPE == 6
  #define L_NAME "Barrette"
  #define RUBAN_SIZE 60
  // #include "macro/Type/SK/mem.h" // mem global sk & pwm

  #include "macro/Type/4pwm/mem_4pwm.h" // defo
  // #include "macro/Type/SK/mem_sk.h"  // defo
  #include "macro/Show/larochelle/mem_sk_roch.h"
  #include "macro/mem_barre_pwm.h"

#elif LULU_TYPE == 7
  #define L_NAME "Phone"
  #define RUBAN_SIZE 35
  // #include "macro/Type/SK/mem.h" // mem global sk & pwm

  #include "macro/Type/4pwm/mem_4pwm.h" // defo
  #include "macro/Type/SK/mem_sk.h"     // defo
  #include "macro/mem_phone_pwm.h"

#elif LULU_TYPE == 8
  #define L_NAME "Atom"
  #define RUBAN_SIZE 25     // 5 pour tester avec les jauges de monitoring
  // #include "macro/Type/SK/mem.h" // mem global sk & pwm

  #include "macro/Type/4pwm/mem_4pwm.h" // defo
  #include "macro/Type/SK/mem_sk.h"     // defo
  #include "macro/mem_atom_pwm.h"

#elif LULU_TYPE == 9
  #define L_NAME "Chariot"
  #define RUBAN_SIZE 120
  // #include "macro/Show/H&S/mem_h&s.h" // mem global sk & pwm

  #include "macro/Type/4pwm/mem_4pwm.h" // defo
  // #include "macro/Type/SK/mem_sk.h"  // defo

  #include "macro/Show/H&S/mem_h&s_sk.h"
  #include "macro/mem_chariot_pwm.h"

#elif LULU_TYPE == 10
  #define L_NAME "Power"
  #define RUBAN_SIZE 120
  #include "macro/Type/SK/mem.h"

#elif LULU_TYPE == 11
  #define L_NAME "Dmx_strobe"
  #define RUBAN_SIZE 0
  #define OUT_PATCHSIZE 16 // 20 = sk_pw / 16 = strobe led / 5 = par led / 20 = cube strobe dmx / 9 = cube par led dmx / 13 = cube minikolor
  #include "macro/Type/strobe/mem_strobe_dmx.h"

#elif LULU_TYPE == 12
  #define RUBAN_SIZE 0
  #define L_NAME "Dmx_par"
  #define OUT_PATCHSIZE 5 // 20 = sk_pw / 16 = strobe led / 5 = par led / 20 = cube strobe dmx / 9 = cube par led dmx / 13 = cube minikolor
  #include "macro/Type/parled/mem_parled_dmx.h"

#elif LULU_TYPE == 20
  #define RUBAN_SIZE 60
  #define L_NAME "Cube_str"
  #define ON_NO_WIFI 255
  #include "macro/Type/strobe/mem_strobe.h"
  #include "macro/Type/4pwm/mem_4pwm.h"
  #include "macro/mem_cube_strobe.h"

#elif LULU_TYPE == 21
  #define RUBAN_SIZE 60
  #define L_NAME "Cube_par"
  #define OUT_PATCHSIZE 9 // 20 = sk_pw / 16 = strobe led / 5 = par led / 20 = cube strobe dmx / 9 = cube par led dmx / 13 = cube minikolor
  #define ON_NO_WIFI 255
  // #include "macro/Type/parled/mem_parled.h"
  #include "macro/Show/larochelle/mem_parled_roch.h"

  #include "macro/Type/4pwm/mem_4pwm.h" // defo
  // #include "macro/mem_cube_parled.h"
  #include "macro/Show/larochelle/mem_cube_parled_roch.h"

  // #include "macro/Show/Baro/mem_pwm_baro_127.h"   // cube 1 3 5 7 9
  // #include "macro/Show/Baro/mem_cube_baro_127.h"

  // #include "macro/Show/Baro/mem_pwm_baro_125.h"   // cube 2 4 6 8 10
  // #include "macro/Show/Baro/mem_cube_baro_125.h"

#elif LULU_TYPE == 22
  #define RUBAN_SIZE 60
  #define L_NAME "Cube_minikolor"
  #define OUT_PATCHSIZE 13 //  20 = sk_pw / 16 = strobe led / 5 = par led / 20 = cube strobe dmx / 9 = cube par led dmx / 13 = cube minikolor
  #define ON_NO_WIFI 255
  #include "macro/Type/4pwm/mem_4pwm.h"           //
  #include "macro/Type/minikolor/mem_minikolor.h" //
  #include "macro/mem_cube_minikolor.h"           //

  #elif LULU_TYPE == 23
  #define RUBAN_SIZE 60
  #define L_NAME "Cube_elp"
  #define OUT_PATCHSIZE 7 //  20 = sk_pw / 16 = strobe led / 5 = par led / 20 = cube strobe dmx / 9 = cube par led dmx / 13 = cube minikolor / = elp
  #define ON_NO_WIFI 255
  #include "macro/Type/4pwm/mem_4pwm.h" //
  #include "macro/Type/elp/mem_elp.h"   //
  #include "macro/mem_cube_elp.h"       //

#elif LULU_TYPE == 30
  #define RUBAN_SIZE 60
  #define L_NAME "Sucette_parled"
  #define OUT_PATCHSIZE 9 // 20 = sk_pw / 16 = strobe led / 5 = par led / 20 = cube strobe dmx / 9 = cube par led dmx / 13 = cube minikolor
  #define ON_NO_WIFI 255 // 82 niveau pour les statics baronnie
  #include "macro/Type/parled/mem_parled.h"

  // #include "macro/Type/4pwm/mem_4pwm.h"            // defo
  // #include "macro/mem_sucette_parled.h"

  //////////////////////////////// Baronie
  // #include "macro/Show/Baro/mem_pwm_baro_131.h"     // vincent
  // #include "macro/Show/Baro/mem_sucette_baro_131.h"

  // #include "macro/Show/Baro/mem_pwm_baro_132.h"     // jerome
  // #include "macro/Show/Baro/mem_sucette_baro_132.h"

  //////////////////////////////// Esch
  #include "macro/Show/esch/mem_pwm_esch.h"
  #include "macro/Show/esch/mem_sucette_esch.h"

#elif LULU_TYPE == 31
  #define RUBAN_SIZE 60
  #define L_NAME "Sucette_strobe"
  #define OUT_PATCHSIZE 9 // 20 = sk_pw / 16 = strobe led / 5 = par led / 20 = cube strobe dmx / 9 = cube par led dmx / 13 = cube minikolor
  #define ON_NO_WIFI 255 //
  #include "macro/Type/strobe/mem_strobe.h"

  #include "macro/Type/4pwm/mem_4pwm.h" // defo
  #include "macro/mem_sucette_strobe.h"

#elif LULU_TYPE == 32
  #define RUBAN_SIZE 60
  #define L_NAME "Sucette_MiniKolor"
  #define OUT_PATCHSIZE 9 // 20 = sk_pw / 16 = strobe led / 5 = par led / 20 = cube strobe dmx / 9 = cube par led dmx / 13 = cube minikolor
  #define ON_NO_WIFI 255 //
  #include "macro/Type/minikolor/mem_minikolor.h"

  #include "macro/Type/4pwm/mem_4pwm.h" // defo
  #include "macro/mem_sucette_minikolor.h"

#elif LULU_TYPE == 33
  #define RUBAN_SIZE 60
  #define L_NAME "Sucette_Elp"
  #define OUT_PATCHSIZE 9 // 20 = sk_pw / 16 = strobe led / 5 = par led / 20 = cube strobe dmx / 9 = cube par led dmx / 13 = cube minikolor
  #define ON_NO_WIFI 255 //
  #include "macro/Type/elp/mem_elp.h"

  #include "macro/Type/4pwm/mem_4pwm.h" // defo
  #include "macro/mem_sucette_elp.h"

#elif LULU_TYPE == 34
  #define RUBAN_SIZE 60
  #define L_NAME "Banc_parled"
  #define ON_NO_WIFI 127 // 82 niveau pour les statics baronnie
  #include "macro/Type/parled/mem_parled.h"

  // #include "macro/Type/4pwm/mem_4pwm.h"            // defo
  // #include "macro/mem_sucette_parled.h"

  //////////////////////////////// Baronie
  // #include "macro/Show/Baro/mem_pwm_baro_131.h"     // vincent
  // #include "macro/Show/Baro/mem_sucette_baro_131.h"

  // #include "macro/Show/Baro/mem_pwm_baro_132.h"     // jerome
  // #include "macro/Show/Baro/mem_sucette_baro_132.h"

  //////////////////////////////// Esch
  #include "macro/Show/esch/mem_pwm_esch.h"
  #include "macro/Show/esch/mem_sucette_esch.h"

#elif LULU_TYPE == 40
  #define L_NAME "New_Fluo"
  #define RUBAN_SIZE 73 / 20 = newfluo
  #define ON_NO_WIFI 255                //
  #include "macro/Type/4pwm/mem_4pwm.h" // defo
  #include "macro/Type/SK/mem_fluo.h"

  #include "macro/mem_new_fluo_pwm.h"

#elif LULU_TYPE == 50
  #define L_NAME "elp_DMX"
  #define RUBAN_SIZE 50
  #define OUT_PATCHSIZE 20
  #define DMXOUT_ADDR 20

  #include "macro/Type/4pwm/mem_4pwm.h" // defo
  #include "macro/Type/SK/mem_sk.h"     // defo
  #include "macro/mem_barre_pwm.h"

#elif LULU_TYPE == 60
  #define L_NAME "lyre_DMX"
  #define RUBAN_SIZE 28
  #define OUT_PATCHSIZE 16
  #define DMXOUT_ADDR 1

  #include "macro/Type/4pwm/mem_4pwm.h" // defo
  #include "macro/Type/SK/mem_sk.h"     // defo
  #include "macro/mem_barre_pwm.h"

#endif
#endif

#include <Preferences.h>
Preferences prefs;

void settings()
{

  prefs.begin("k32-settings", false);

// Save to EEPROM if DEFINE
#ifdef LULU_ID
  prefs.putUInt("LULU_id", LULU_ID);
  LULU_id = LULU_ID;
#else
  LULU_id = prefs.getUInt("LULU_id", 1);
#endif

#if LULU_TYPE == 60
  LULU_adr = (1 + (LULU_id - 1) * 32);  // DMX Offset = 32
#else
  LULU_adr = (1 + (LULU_id - 1) * LULU_PATCHSIZE);
#endif

#ifdef LULU_TYPE
  prefs.putUInt("LULU_type", LULU_TYPE);
  LULU_type = LULU_TYPE;
#else
  LULU_type = prefs.getUInt("LULU_type", 5);
#endif

#ifdef LULU_UNI
  prefs.putUInt("LULU_uni", LULU_UNI);
  LULU_uni = LULU_UNI;
#else
  LULU_uni = prefs.getUInt("LULU_uni", 0);
#endif

#ifdef RUBAN_TYPE
  prefs.putUInt("LULU_ruban", RUBAN_TYPE);
  RUBAN_type = RUBAN_TYPE;
#else
  if (LULU_type == 8)
  {
    RUBAN_type = prefs.getUInt("LULU_ruban", LED_WS2812_V1);
  }
  else
  {
    RUBAN_type = prefs.getUInt("LULU_ruban", LED_SK6812W_V1);
  }
#endif

  String L_name;
#ifdef L_NAME
  prefs.putString("L_NAME", L_name);
  L_name = L_NAME;
#else
  L_name = prefs.getString("L_NAME", "Flex");
#endif

#ifdef RUBAN_SIZE
  prefs.putUInt("RUBAN_size", RUBAN_SIZE);
  RUBAN_size = RUBAN_SIZE;
#else
  RUBAN_size = prefs.getUInt("RUBAN_size", 300);
#endif

#ifdef DMXOUT_ADDR
  prefs.putUInt("DMXOUT_addr", DMXOUT_ADDR);
  DMXOUT_addr = DMXOUT_ADDR;
#else
  DMXOUT_addr = prefs.getUInt("DMXOUT_addr", 1);
#endif

#ifdef FAKE_CURRENT
  prefs.putUInt("FAKE_current", FAKE_CURRENT);
  FAKE_current = FAKE_CURRENT;
#else
  FAKE_current = prefs.getUInt("FAKE_current", 0);
#endif

  // NAME
  nodeName = L_name;
  if (RUBAN_type == LED_SK6812_V1)
    nodeName += "-SK";
  else if (RUBAN_type == LED_SK6812W_V1)
    nodeName += "-SKW";
  else
    nodeName += "-WS";
  nodeName += "-" + String(LULU_id) + "-v" + String(LULU_VER);

  prefs.end();

} //k32_settings()