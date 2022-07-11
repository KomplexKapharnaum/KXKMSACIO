////////////////// DEFAULT VALUE (can be overriden) /////////////////

#define L_NAME "Unknown"

#define LULU_PATCHSIZE 20 // Size of artnet frame to listen to

#define DMXOUT_ADDR 1           // DMX output start address
#define DMXFIXTURE_PATCHSIZE 32 // DMX fixture patch size

#define PWR_FAKE_CURRENT 0 // Courant virtuel si gauge adaptative désactivée

#define LULU_STRIP_TYPE LED_SK6812W_V1 // Type de strip led
#define LULU_STRIP_SIZE 5

#define LULU_PREV_SIZE 6    // Nbr pixel prévisu
#define LULU_PREV_MASTER 40 // Luminosité prévisu

#define LULU_MEMNOWIFI_MASTER 0 // Luminosité Preset NOWIFI

#define ARTNET_ENABLE 1  // enable/disable ArtNet
#define ARTNET_DMXNODE 0 // send Artnet full-frame -> DmxOut (NODE)

#define HAS_LED_STRIPS 0   //
#define HAS_DMX_FIXTURES 0 //
#define HAS_PWM_FIXTURES 0 //

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
#include <fixtures/K32_dmxfixture.h>

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
#include "type/12-parled.h"

#elif LULU_TYPE == 13
#include "type/13-node_DMX.h"

#elif LULU_TYPE == 20
#include "type/20-cube-strobe.h"

#elif LULU_TYPE == 21
#include "type/21-cube-par.h"

#elif LULU_TYPE == 22
#define LULU_STRIP_SIZE 60
#define L_NAME "Cube_minikolor"
#define DMXFIXTURE_PATCHSIZE 13 //  20 = sk_pw / 16 = strobe led / 5 = par led / 20 = cube strobe dmx / 9 = cube par led dmx / 13 = cube minikolor
#define LULU_MEMNOWIFI_MASTER 255
#include "macro/type/4pwm/mem_4pwm.h"           // defo
#include "macro/type/minikolor/mem_minikolor.h" // defo
#include "macro/mem_cube_minikolor.h"           //

#elif LULU_TYPE == 23
#define LULU_STRIP_SIZE 60
#define L_NAME "Cube_elp"
#define DMXFIXTURE_PATCHSIZE 7 //  20 = sk_pw / 16 = strobe led / 5 = par led / 20 = cube strobe dmx / 9 = cube par led dmx / 13 = cube minikolor / = elp
#define LULU_MEMNOWIFI_MASTER 255
#include "macro/type/4pwm/mem_4pwm.h" // defo
#include "macro/type/elp/mem_elp.h"   // defo
#include "macro/mem_cube_elp.h"       //

#elif LULU_TYPE == 30
#include "type/30-table-lumineuse-par.h"
// #define LULU_STRIP_SIZE 60
// #define L_NAME "Sucette_parled"
// #define DMXFIXTURE_PATCHSIZE 9         // 20 = sk_pw / 16 = strobe led / 5 = par led / 20 = cube strobe dmx / 9 = cube par led dmx / 13 = cube minikolor
// #define LULU_MEMNOWIFI_MASTER 82        // 82 niveau pour les statics baronnie
// #include "macro/type/parled/mem_parled.h"

// // #include "macro/type/4pwm/mem_4pwm.h"             // defo
// // #include "macro/mem_sucette_parled.h"             // defo

// //////////////////////////////// Baronie
// // #include "macro/Show/Baro/mem_pwm_baro_131.h"     // vincent
// // #include "macro/Show/Baro/mem_sucette_baro_131.h"

// #include "macro/Show/Baro/mem_pwm_baro_132.h"        // jerome
// #include "macro/Show/Baro/mem_sucette_baro_132.h"

// //////////////////////////////// Esch
// // #include "macro/Show/esch/mem_pwm_esch.h"
// // #include "macro/Show/esch/mem_sucette_esch.h"

#elif LULU_TYPE == 31
#include "type/31-table-lumineuse-strobe.h"
// #define LULU_STRIP_SIZE 60
// #define L_NAME "Sucette_strobe"
// #define DMXFIXTURE_PATCHSIZE 9            // 20 = sk_pw / 16 = strobe led / 5 = par led / 20 = cube strobe dmx / 9 = cube par led dmx / 13 = cube minikolor
// #define LULU_MEMNOWIFI_MASTER 255         //
// #include "macro/type/strobe/mem_strobe.h" // defo

// #include "macro/type/4pwm/mem_4pwm.h" // defo
// #include "macro/mem_sucette_strobe.h"

#elif LULU_TYPE == 32
#define LULU_STRIP_SIZE 60
#define L_NAME "Sucette_MiniKolor"
#define DMXFIXTURE_PATCHSIZE 9                  // 20 = sk_pw / 16 = strobe led / 5 = par led / 20 = cube strobe dmx / 9 = cube par led dmx / 13 = cube minikolor
#define LULU_MEMNOWIFI_MASTER 255               //
#include "macro/type/minikolor/mem_minikolor.h" // defo

#include "macro/type/4pwm/mem_4pwm.h" // defo
#include "macro/mem_sucette_minikolor.h"

#elif LULU_TYPE == 33
#define LULU_STRIP_SIZE 60
#define L_NAME "Sucette_Elp"
#define DMXFIXTURE_PATCHSIZE 9      // 20 = sk_pw / 16 = strobe led / 5 = par led / 20 = cube strobe dmx / 9 = cube par led dmx / 13 = cube minikolor
#define LULU_MEMNOWIFI_MASTER 255   //
#include "macro/type/elp/mem_elp.h" // defo

#include "macro/type/4pwm/mem_4pwm.h" // defo
#include "macro/mem_sucette_elp.h"

#elif LULU_TYPE == 34
#include "type/34-banc-par.h"
// #define LULU_STRIP_SIZE 60
// #define L_NAME "Banc_parled"
// #define LULU_MEMNOWIFI_MASTER 127 // 82 niveau pour les statics baronnie
// #include "macro/type/parled/mem_parled.h"

// // #include "macro/type/4pwm/mem_4pwm.h"            // defo
// // #include "macro/mem_sucette_parled.h"

// //////////////////////////////// Baronie
// // #include "macro/Show/Baro/mem_pwm_baro_131.h"     // vincent
// // #include "macro/Show/Baro/mem_sucette_baro_131.h"

// // #include "macro/Show/Baro/mem_pwm_baro_132.h"     // jerome
// // #include "macro/Show/Baro/mem_sucette_baro_132.h"

// //////////////////////////////// Esch
// #include "macro/Show/esch/mem_pwm_esch.h"
// #include "macro/Show/esch/mem_sucette_esch.h"

#elif LULU_TYPE == 38
#include "type/38-table-lumineuse-par.h"

#elif LULU_TYPE == 40
#define L_NAME "New_Fluo"
#define LULU_STRIP_SIZE 73 / 20 = newfluo
#define LULU_MEMNOWIFI_MASTER 255     //
#include "macro/type/4pwm/mem_4pwm.h" // defo
#include "macro/type/SK/mem_fluo.h"

#include "macro/mem_new_fluo_pwm.h"

#elif LULU_TYPE == 50
#include "type/50-elp_DMX.h"

#elif LULU_TYPE == 60
#define L_NAME "lyre_DMX"
#define LULU_STRIP_SIZE 27
#define DMXFIXTURE_PATCHSIZE 16

#include "macro/type/4pwm/mem_4pwm.h" // defo
#include "macro/type/SK/mem_sk.h"     // defo
#include "macro/mem_barre_pwm.h"

#elif LULU_TYPE == 71
#include "type/71-4strobes.h"

#elif LULU_TYPE == 72
#include "type/72-5parled.h"

#elif LULU_TYPE == 80
#include "type/80-maree.h"

#elif LULU_TYPE == 81
#include "type/81-buzzer.h"

#endif
#endif
