
/////////////////////////////////////////def RUBAN_TYPE & LULU_TYPE /////////////////////////////////////////

#ifdef LULU_TYPE
#if LULU_TYPE == 1
#define RUBAN_SIZE 120
#define L_TYPE "Sac"
#elif LULU_TYPE == 2
#define RUBAN_SIZE 120
#define L_TYPE "Barre"
#elif LULU_TYPE == 3
#define RUBAN_SIZE 17
#define L_TYPE "Pince"
#elif LULU_TYPE == 4
#define RUBAN_SIZE 73
#define L_TYPE "Fluo"
#elif LULU_TYPE == 5
#define RUBAN_SIZE 186
#define L_TYPE "Flex"
#elif LULU_TYPE == 6
#define RUBAN_SIZE 60
#define L_TYPE "HideSee"
#elif LULU_TYPE == 7
#define RUBAN_SIZE 35
#define L_TYPE "Phone"
#elif LULU_TYPE == 8
#define RUBAN_SIZE 25 // 5 pour tester avec les jauges de monitoring
#define L_TYPE "Atom"
#elif LULU_TYPE == 9
#define RUBAN_SIZE 120
#define L_TYPE "Chariot"
#elif LULU_TYPE == 10
#define L_TYPE "Power"
#endif
#endif

void settings()
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

  // NAME
  nodeName = "Power";

  nodeName += "-" + String(LULU_id) + "-v" + String(LULU_VER);

} //k32_settings()