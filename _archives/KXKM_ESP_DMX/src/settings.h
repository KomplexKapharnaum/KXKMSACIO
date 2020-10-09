
/////////////////////////////////////////def RUBAN_TYPE & LULU_TYPE /////////////////////////////////////////

#ifdef LULU_TYPE
  #if LULU_TYPE == 1
    #define RUBAN_SIZE 120
    #define L_TYPE "Sac"
    #define LULU_PATCHSIZE 18 // Taille du patch DMX pour cet Fixture ** 18 = sk_pw / 16 = strobe led / 5 = par led / 20 = cube strobe dmx / 9 = cube par led dmx 
    #define LULU_UNI 0   // Univers DM    0=SAC 1=Barre 2=Chariot 3=Dmx 4=Cube_strobe 5=Cube_parled
    #define FAKE_CURRENT 12500
  #elif LULU_TYPE == 2
    #define RUBAN_SIZE 120
    #define LULU_PATCHSIZE 18 // Taille du patch DMX pour cet Fixture ** 18 = sk_pw / 16 = strobe led / 5 = par led / 20 = cube strobe dmx / 9 = cube par led dmx
    #define LULU_UNI 1   // Univers DM    0=SAC 1=Barre 2=Chariot 3=Dmx 4=Cube_strobe 5=Cube_parled
    #define L_TYPE "Barre" 
  #elif LULU_TYPE == 3
    #define RUBAN_SIZE 17
    #define LULU_PATCHSIZE 18 // Taille du patch DMX pour cet Fixture ** 18 = sk_pw / 16 = strobe led / 5 = par led / 20 = cube strobe dmx / 9 = cube par led dmx 
    #define LULU_UNI 7   // Univers DM    0=SAC 1=Barre 2=Chariot 3=Dmx 4=Cube_strobe 5=Cube_parled
    #define L_TYPE "Pince"
  #elif LULU_TYPE == 4
    #define RUBAN_SIZE 73
    #define LULU_PATCHSIZE 18 // Taille du patch DMX pour cet Fixture ** 18 = sk_pw / 16 = strobe led / 5 = par led / 20 = cube strobe dmx / 9 = cube par led dmx 
    #define LULU_UNI 6   // Univers DM    0=SAC 1=Barre 2=Chariot 3=Dmx 4=Cube_strobe 5=Cube_parled
    #define L_TYPE "Fluo"
  #elif LULU_TYPE == 5
    #define RUBAN_SIZE 186
    #define LULU_PATCHSIZE 18 // Taille du patch DMX pour cet Fixture ** 18 = sk_pw / 16 = strobe led / 5 = par led / 20 = cube strobe dmx / 9 = cube par led dmx 
    #define LULU_UNI 1   // Univers DM    0=SAC 1=Barre 2=Chariot 3=Dmx 4=Cube_strobe 5=Cube_parled
    #define L_TYPE "Flex"
  #elif LULU_TYPE == 6
    #define RUBAN_SIZE 60
    #define LULU_PATCHSIZE 18 // Taille du patch DMX pour cet Fixture ** 18 = sk_pw / 16 = strobe led / 5 = par led / 20 = cube strobe dmx / 9 = cube par led dmx 
    #define LULU_UNI 1   // Univers DM    0=SAC 1=Barre 2=Chariot 3=Dmx 4=Cube_strobe 5=Cube_parled
    #define L_TYPE "HideSee"
  #elif LULU_TYPE == 7
    #define RUBAN_SIZE 35
    #define LULU_PATCHSIZE 18 // Taille du patch DMX pour cet Fixture ** 18 = sk_pw / 16 = strobe led / 5 = par led / 20 = cube strobe dmx / 9 = cube par led dmx 
    #define LULU_UNI 1   // Univers DM    0=SAC 1=Barre 2=Chariot 3=Dmx 4=Cube_strobe 5=Cube_parled
    #define L_TYPE "Phone"
  #elif LULU_TYPE == 8
    #define RUBAN_SIZE 25 // 5 pour tester avec les jauges de monitoring
    #define LULU_PATCHSIZE 18 // Taille du patch DMX pour cet Fixture ** 18 = sk_pw / 16 = strobe led / 5 = par led / 20 = cube strobe dmx / 9 = cube par led dmx
    #define LULU_UNI 1   // Univers DM    0=SAC 1=Barre 2=Chariot 3=Dmx 4=Cube_strobe 5=Cube_parled
    #define L_TYPE "Atom" 
  #elif LULU_TYPE == 9
    #define RUBAN_SIZE 120
    #define LULU_PATCHSIZE 18 // Taille du patch DMX pour cet Fixture ** 18 = sk_pw / 16 = strobe led / 5 = par led / 20 = cube strobe dmx / 9 = cube par led dmx 
    #define LULU_UNI 2   // Univers DM    0=SAC 1=Barre 2=Chariot 3=Dmx 4=Cube_strobe 5=Cube_parled
    #define L_TYPE "Chariot"
  #elif LULU_TYPE == 10
    #define RUBAN_SIZE 120
    #define LULU_PATCHSIZE 18 // Taille du patch DMX pour cet Fixture ** 18 = sk_pw / 16 = strobe led / 5 = par led / 20 = cube strobe dmx / 9 = cube par led dmx
    #define LULU_UNI 0   // Univers DM    0=SAC 1=Barre 2=Chariot 3=Dmx 4=Cube_strobe 5=Cube_parled
    #define L_TYPE "Power" 
  #elif LULU_TYPE == 11
    #define RUBAN_SIZE 0
    #define L_TYPE "Dmx_strobe"
    #define LULU_PATCHSIZE 16 // Taille du patch DMX pour cet Fixture ** 18 = sk_pw / 16 = strobe led / 5 = par led / 20 = cube strobe dmx / 9 = cube par led dmx
    #define LULU_UNI 4   // Univers DM    0=SAC 1=Barre 2=Chariot 3=Dmx 4=Cube_strobe 5=Cube_parled 
    #include "macro/mem_strobe.h"
  #elif LULU_TYPE == 12
    #define RUBAN_SIZE 0
    #define L_TYPE "Dmx_par"
    #define LULU_PATCHSIZE 5 // Taille du patch DMX pour cet Fixture ** 18 = sk_pw / 16 = strobe led / 5 = par led / 20 = cube strobe dmx / 9 = cube par led dmx
    #define LULU_UNI 5   // Univers DM    0=SAC 1=Barre 2=Chariot 3=Dmx 4=Cube_strobe 5=Cube_parled
    #include "macro/mem_parled.h" 
  #elif LULU_TYPE == 13
    #define RUBAN_SIZE 60
    #define L_TYPE "Cube_str"
    #define LULU_PATCHSIZE 20 // Taille du patch DMX pour cet Fixture ** 18 = sk_pw / 16 = strobe led / 5 = par led / 20 = cube strobe dmx / 9 = cube par led dmx 
    #define LULU_UNI 4   // Univers DM    0=SAC 1=Barre 2=Chariot 3=Dmx 4=Cube_strobe 5=Cube_parled
    #include "macro/mem_pwm_strobe_dmx.h"
  #elif LULU_TYPE == 14
    #define RUBAN_SIZE 60
    #define L_TYPE "Cube_par"
    #define LULU_PATCHSIZE 9 // Taille du patch DMX pour cet Fixture ** 18 = sk_pw / 16 = strobe led / 5 = par led / 20 = cube strobe dmx / 9 = cube par led dmx 
    #define LULU_UNI 5   // Univers DM    0=SAC 1=Barre 2=Chariot 3=Dmx 4=Cube_strobe 5=Cube_parled
    #include "macro/mem_pwm_parled_dmx.h"
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

  String L_type;
#ifdef L_TYPE
  k32->system->preferences.putString("L_type", L_TYPE);
  L_type = L_TYPE;
#else
  L_type = k32->system->preferences.getString("L_type", "Flex");
#endif

#ifdef RUBAN_SIZE
  k32->system->preferences.putUInt("RUBAN_size", RUBAN_SIZE);
  RUBAN_size = RUBAN_SIZE;
#else
  RUBAN_size = k32->system->preferences.getUInt("RUBAN_size", 300);
#endif

#ifdef FAKE_CURRENT
  k32->system->preferences.putUInt("FAKE_current", FAKE_CURRENT);
  FAKE_current = FAKE_CURRENT;
#else
  FAKE_current = k32->system->preferences.getUInt("FAKE_current", 0);
#endif

  // Calculate adr // channels
  LULU_adr = (1 + (LULU_id - 1) * (LULU_PATCHSIZE));

  // NAME
  nodeName = L_type;
  if (RUBAN_type == LED_SK6812_V1)
    nodeName += "-SK";
  else if (RUBAN_type == LED_SK6812W_V1)
    nodeName += "-SKW";
  else
    nodeName += "-WS";
  nodeName += "-" + String(LULU_id) + "-v" + String(LULU_VER);

} //k32_settings()