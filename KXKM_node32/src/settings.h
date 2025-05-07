////////////////// DEFAULT VALUE (can be overriden) /////////////////

#define L_NAME "Unknown"

#define LULU_PATCHSIZE 20 // Size of artnet frame to listen to

#define DMXOUT_ADDR 1           // DMX output start address
#define DMXFIXTURE_PATCHSIZE 32 // DMX fixture patch size

#define PWR_FAKE_CURRENT 0 // Courant virtuel si gauge adaptative désactivée

#define LULU_STRIP_TYPE LED_SK6812W_V1 // Type de strip led
// #define LULU_STRIP_SIZE 5

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
#include "type/06-potson.h"

#elif LULU_TYPE == 7
#include "type/07-phone.h"

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

#elif LULU_TYPE == 14
#include "type/14-smoke.h"

#elif LULU_TYPE == 20
#include "type/20-cube-strobe.h"

#elif LULU_TYPE == 21
#include "type/21-cube-par.h"

#elif LULU_TYPE == 24
#include "type/24-cube-sk.h"

#elif LULU_TYPE == 34
#include "type/34-banc.h"

#elif LULU_TYPE == 50
#include "type/50-elp_DMX.h"

#elif LULU_TYPE == 71
#include "type/71-4strobes.h"

#elif LULU_TYPE == 72
#include "type/72-5parled.h"


#elif LULU_TYPE == 80
#include "type/80-atom.h"

#elif LULU_TYPE == 82
#include "type/82-relais.h"

#elif LULU_TYPE == 83
#include "type/83-cloud.h"

#elif LULU_TYPE == 84
#include "type/84-maree.h"

#elif LULU_TYPE == 91
#include "type/91-ST-buzzer.h"

#elif LULU_TYPE == 301
#include "type/301-dmx-fixture.h"

#elif LULU_TYPE == 302
#include "type/302-multiflex.h"

#elif LULU_TYPE == 303
#include "type/303-manuflex.h"

#elif LULU_TYPE == 304
#include "type/304-hotteflex.h"

#endif
#endif
