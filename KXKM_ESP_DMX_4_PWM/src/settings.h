////////////////// DEFAULT VALUE (can be overriden) /////////////////

#define L_NAME "Unknown"

#define LULU_PATCHSIZE 20 // Size of artnet frame to listen to

#define DMXOUT_ADDR           1   // DMX output start address
#define DMXFIXTURE_PATCHSIZE  32  // DMX fixture patch size

#define PWR_FAKE_CURRENT  0   // Courant virtuel si gauge adaptative désactivée

#define LULU_STRIP_TYPE   LED_SK6812W_V1  // Type de strip led          
#define LULU_STRIP_SIZE   5

#define LULU_PREV_SIZE    6         // Nbr pixel prévisu
#define LULU_PREV_MASTER  40        // Luminosité prévisu

#define LULU_MEMNOWIFI_MASTER 0     // Luminosité Preset NOWIFI

#define ARTNET_ENABLE       1       // enable/disable ArtNet
#define ARTNET_DMXNODE      0       // send Artnet full-frame -> DmxOut (NODE)

#define HAS_LED_STRIPS      0       // 
#define HAS_DMX_FIXTURES    0       // 
#define HAS_PWM_FIXTURES    0       // 

#define REFRESH_INFO 1000 // Refresh affichage Wifi & Battery

/////////////////////////////////////////Debug///////////////////////////////////////

// #define DEBUG_dmx 1              // !!! IMPLEMENT
// #define DEBUG_dmxframe 1
// #define DEBUG_STR 1
// #define DEBUG_calibre_btn 1
#define DEBUG_btn 1

/////////////////////////////////////////def LULU_STRIP_TYPE & LULU_TYPE /////////////////////////////////////////

// LIGHT ANIMATIONS
#include <animations/K32_anim_basics.h>
#include "anim_monitoring.h"
#include "anim_dmx_test.h"
#include "anim_dmx_strip.h"
#include "anim_maree.h"

// LIGHT FIXTURES
#include <fixtures/K32_ledstrip.h>
#include <fixtures/K32_pwmfixture.h>


#ifdef LULU_TYPE

#if LULU_TYPE == 1
#include "type/01-sac.h"

#elif LULU_TYPE == 2
#include "type/02-barre.h"

#elif LULU_TYPE == 3
#include "type/03-pince.h"

#elif LULU_TYPE == 4
#include "type/04-fluo.h"

#elif LULU_TYPE == 5
#include "type/05-flex.h"

#elif LULU_TYPE == 6
#include "type/06-barrette.h"

#elif LULU_TYPE == 7
#include "type/07-phone.h"

#elif LULU_TYPE == 8
#include "type/08-atom.h"

#elif LULU_TYPE == 9
#include "type/09-chariot.h"

#elif LULU_TYPE == 10
#include "type/10-power.h"

#elif LULU_TYPE == 11
#include "type/11-strobe.h"

#elif LULU_TYPE == 12
#define L_NAME "Dmx_par"
#define LULU_STRIP_SIZE 0
#define DMXFIXTURE_PATCHSIZE 5                           // 20 = sk_pw / 16 = strobe led / 5 = par led / 20 = cube strobe dmx / 9 = cube par led dmx / 13 = cube minikolor
#include "macro/Type/parled/mem_pwm_parled_dmx.h" // mem global

#elif LULU_TYPE == 13
#define L_NAME "NODE"
#define LULU_STRIP_SIZE 0
#define ARTNET_DMXNODE 1
#include "macro/Type/node/node.h" // mem global

#elif LULU_TYPE == 20
#define LULU_STRIP_SIZE 60
#define L_NAME "Cube_str"
#define LULU_MEMNOWIFI_MASTER 255
#include "macro/Type/strobe/mem_strobe.h" // defo
#include "macro/Type/4pwm/mem_4pwm.h"     // defo
#include "macro/mem_cube_strobe.h"

#elif LULU_TYPE == 21
#define LULU_STRIP_SIZE 60
#define L_NAME "Cube_par"
#define DMXFIXTURE_PATCHSIZE 9        // 20 = sk_pw / 16 = strobe led / 5 = par led / 20 = cube strobe dmx / 9 = cube par led dmx / 13 = cube minikolor
#define LULU_MEMNOWIFI_MASTER 255
#include "macro/Type/parled/mem_parled.h"
// #include "macro/Show/larochelle/mem_parled_roch.h"

// #include "macro/Type/4pwm/mem_4pwm.h" // defo
// #include "macro/mem_cube_parled.h"
// #include "macro/Show/larochelle/mem_cube_parled_roch.h"

#include "macro/Show/Baro/mem_pwm_baro_127.h" // cube 1 3 5 7 9
#include "macro/Show/Baro/mem_cube_baro_127.h"

// #include "macro/Show/Baro/mem_pwm_baro_125.h"   // cube 2 4 6 8 10
// #include "macro/Show/Baro/mem_cube_baro_125.h"

#elif LULU_TYPE == 22
#define LULU_STRIP_SIZE 60
#define L_NAME "Cube_minikolor"
#define DMXFIXTURE_PATCHSIZE 13                 //  20 = sk_pw / 16 = strobe led / 5 = par led / 20 = cube strobe dmx / 9 = cube par led dmx / 13 = cube minikolor
#define LULU_MEMNOWIFI_MASTER 255
#include "macro/Type/4pwm/mem_4pwm.h"           // defo
#include "macro/Type/minikolor/mem_minikolor.h" // defo
#include "macro/mem_cube_minikolor.h"           //

#elif LULU_TYPE == 23
#define LULU_STRIP_SIZE 60
#define L_NAME "Cube_elp"
#define DMXFIXTURE_PATCHSIZE 7         //  20 = sk_pw / 16 = strobe led / 5 = par led / 20 = cube strobe dmx / 9 = cube par led dmx / 13 = cube minikolor / = elp
#define LULU_MEMNOWIFI_MASTER 255
#include "macro/Type/4pwm/mem_4pwm.h" // defo
#include "macro/Type/elp/mem_elp.h"   // defo
#include "macro/mem_cube_elp.h"       //

#elif LULU_TYPE == 30
#define LULU_STRIP_SIZE 60
#define L_NAME "Sucette_parled"
#define DMXFIXTURE_PATCHSIZE 9         // 20 = sk_pw / 16 = strobe led / 5 = par led / 20 = cube strobe dmx / 9 = cube par led dmx / 13 = cube minikolor
#define LULU_MEMNOWIFI_MASTER 82        // 82 niveau pour les statics baronnie
#include "macro/Type/parled/mem_parled.h"

// #include "macro/Type/4pwm/mem_4pwm.h"             // defo
// #include "macro/mem_sucette_parled.h"             // defo

//////////////////////////////// Baronie
// #include "macro/Show/Baro/mem_pwm_baro_131.h"     // vincent
// #include "macro/Show/Baro/mem_sucette_baro_131.h"

#include "macro/Show/Baro/mem_pwm_baro_132.h"        // jerome
#include "macro/Show/Baro/mem_sucette_baro_132.h"

//////////////////////////////// Esch
// #include "macro/Show/esch/mem_pwm_esch.h"
// #include "macro/Show/esch/mem_sucette_esch.h"

#elif LULU_TYPE == 31
#define LULU_STRIP_SIZE 60
#define L_NAME "Sucette_strobe"
#define DMXFIXTURE_PATCHSIZE 9        // 20 = sk_pw / 16 = strobe led / 5 = par led / 20 = cube strobe dmx / 9 = cube par led dmx / 13 = cube minikolor
#define LULU_MEMNOWIFI_MASTER 255     //
#include "macro/Type/strobe/mem_strobe.h" // defo

#include "macro/Type/4pwm/mem_4pwm.h" // defo
#include "macro/mem_sucette_strobe.h"

#elif LULU_TYPE == 32
#define LULU_STRIP_SIZE 60
#define L_NAME "Sucette_MiniKolor"
#define DMXFIXTURE_PATCHSIZE 9        // 20 = sk_pw / 16 = strobe led / 5 = par led / 20 = cube strobe dmx / 9 = cube par led dmx / 13 = cube minikolor
#define LULU_MEMNOWIFI_MASTER 255     //
#include "macro/Type/minikolor/mem_minikolor.h" // defo

#include "macro/Type/4pwm/mem_4pwm.h" // defo
#include "macro/mem_sucette_minikolor.h"

#elif LULU_TYPE == 33
#define LULU_STRIP_SIZE 60
#define L_NAME "Sucette_Elp"
#define DMXFIXTURE_PATCHSIZE 9      // 20 = sk_pw / 16 = strobe led / 5 = par led / 20 = cube strobe dmx / 9 = cube par led dmx / 13 = cube minikolor
#define LULU_MEMNOWIFI_MASTER 255   //
#include "macro/Type/elp/mem_elp.h" // defo

#include "macro/Type/4pwm/mem_4pwm.h" // defo
#include "macro/mem_sucette_elp.h"

#elif LULU_TYPE == 34
#define LULU_STRIP_SIZE 60
#define L_NAME "Banc_parled"
#define LULU_MEMNOWIFI_MASTER 127 // 82 niveau pour les statics baronnie
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
#define LULU_STRIP_SIZE 73 / 20 = newfluo
#define LULU_MEMNOWIFI_MASTER 255                //
#include "macro/Type/4pwm/mem_4pwm.h" // defo
#include "macro/Type/SK/mem_fluo.h"

#include "macro/mem_new_fluo_pwm.h"

#elif LULU_TYPE == 50
#define L_NAME "elp_DMX"
#define LULU_STRIP_SIZE 50
#define DMXOUT_ADDR 20
#define DMXFIXTURE_PATCHSIZE LULU_STRIP_SIZE

#include "macro/Type/4pwm/mem_4pwm.h" // defo
// #include "macro/Type/SK/mem_sk.h"     // defo
// #include "macro/mem_barre_pwm.h"

// #include "macro/Show/Baro/mem_sk_baro.h"
// #include "macro/Show/Baro/mem_barre_pwm_baro.h"

#include "macro/Show/Baro/mem_sk_elp_baro.h"
#include "macro/Show/Baro/mem_barre_pwm_elp_baro.h"

#elif LULU_TYPE == 60
#define L_NAME "lyre_DMX"
#define LULU_STRIP_SIZE 27
#define DMXFIXTURE_PATCHSIZE 16

#include "macro/Type/4pwm/mem_4pwm.h" // defo
#include "macro/Type/SK/mem_sk.h"     // defo
#include "macro/mem_barre_pwm.h"

#elif LULU_TYPE == 80
#include "type/80-maree.h"

#endif
#endif


