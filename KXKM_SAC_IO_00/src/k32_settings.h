
/////////////////////////////////////////def RUBAN_TYPE & LULU_TYPE /////////////////////////////////////////

#ifdef LULU_TYPE
#if LULU_TYPE == 1
#define NUM_LEDS_PER_STRIP_MAX 120
#define L_TYPE "Sac"
#elif LULU_TYPE == 2
#define NUM_LEDS_PER_STRIP_MAX 120
#define L_TYPE "Barre"
#elif LULU_TYPE == 3
#define NUM_LEDS_PER_STRIP_MAX 17
#define L_TYPE "Pince"
#elif LULU_TYPE == 4
#define NUM_LEDS_PER_STRIP_MAX 73
#define L_TYPE "Fluo"
#elif LULU_TYPE == 5
#define NUM_LEDS_PER_STRIP_MAX 186
#define L_TYPE "Flex"
#elif LULU_TYPE == 6
#define NUM_LEDS_PER_STRIP_MAX 60
#define L_TYPE "HideSee"
#elif LULU_TYPE == 7
#define NUM_LEDS_PER_STRIP_MAX 35
#define L_TYPE "Phone"
#elif LULU_TYPE == 8
#define NUM_LEDS_PER_STRIP_MAX 25
#define L_TYPE "Atom"
#endif
#endif

void k32_settings()
{

// Save to EEPROM if DEFINE
#ifdef LULU_ID
  k32->system->preferences.putUInt("LULU_id", LULU_ID);
  LULU_id = LULU_ID;
#else
  LULU_id = k32->system->preferences.getUInt("LULU_id", 1);
#endif

#ifdef LULU_TYPE
  k32->system->preferences.putUInt("LULU_type", LULU_TYPE);
  LULU_type = LULU_TYPE;
#else
  LULU_type = k32->system->preferences.getUInt("LULU_type", 5);
#endif

#ifdef LULU_UNI
  k32->system->preferences.putUInt("LULU_uni", LULU_UNI);
  LULU_uni = LULU_UNI;
#else
  LULU_uni = k32->system->preferences.getUInt("LULU_uni", 0);
#endif

#ifdef RUBAN_TYPE
  k32->system->preferences.putUInt("LULU_ruban", RUBAN_TYPE);
  RUBAN_type = RUBAN_TYPE;
#else
  RUBAN_type = k32->system->preferences.getUInt("LULU_ruban", LED_SK6812W_V1);
#endif

#ifdef L_TYPE
  k32->system->preferences.putString("L_type", L_TYPE);
  L_type = L_TYPE;
#else
  L_type = k32->system->preferences.getString("L_type", "Flex");
#endif

#ifdef NUM_LEDS_PER_STRIP_MAX
  k32->system->preferences.putUInt("NUM_leds", NUM_LEDS_PER_STRIP_MAX);
  NUM_LEDS_PER_STRIP_max = NUM_LEDS_PER_STRIP_MAX;
#else
  NUM_LEDS_PER_STRIP_max = k32->system->preferences.getUInt("NUM_leds", LEDS_ABSOLUTE_MAX);
#endif

  // Calculate adr // channels
  adr = (1 + (LULU_id - 1) * (LULU_PATCHSIZE));
  numberOfChannels = NUM_STRIPS * NUM_LEDS_PER_STRIP_max * 4;
  maxUniverses = numberOfChannels / 512 + ((numberOfChannels % 512) ? 1 : 0);
  startUniverse = LULU_uni;

  // Calculate NUM leds MAX & L/R TYPE
  NUM_LEDS_PER_STRIP = NUM_LEDS_PER_STRIP_max;
  N_L_P_S = NUM_LEDS_PER_STRIP_max;

  // NAME
  nodeName = L_type;
  if (RUBAN_type == LED_SK6812_V1)
    nodeName += "_SK";
  else if (RUBAN_type == LED_SK6812W_V1)
    nodeName += "_SKW";
  else
    nodeName += "_WS";
  nodeName += "-" + String(LULU_id) + "-v" + String(LULU_VER);

} //k32_settings()