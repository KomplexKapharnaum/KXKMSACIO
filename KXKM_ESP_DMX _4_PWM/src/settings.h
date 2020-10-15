
/////////////////////////////////////////def RUBAN_TYPE & LULU_TYPE /////////////////////////////////////////

#ifdef LULU_TYPE

  #if LULU_TYPE == 1
    #define L_TYPE "Sac"
    #define RUBAN_SIZE 120
    #define LULU_PATCHSIZE 18 // 18 = sk_pw / 16 = strobe led / 5 = par led / 20 = cube strobe dmx / 9 = cube par led dmx / 13 = cube minikolor
    #define LULU_UNI 0   // Univers DMX   0=SAC 1=Barre 2=Chariot 3=Dmx 4=Cube_strobe 5=Cube_parled 6=Sucette 7=minikolor
    #define FAKE_CURRENT 12500
    #include "macro/Type/SK/mem.h" 

  #elif LULU_TYPE == 2
    #define L_TYPE "Barre" 
    #define RUBAN_SIZE 120
    #define LULU_PATCHSIZE 18 // Taille du patch DMX pour cet Fixture ** 18 = sk_pw / 16 = strobe led / 5 = par led / 20 = cube strobe dmx / 9 = cube par led dmx
    #define LULU_UNI 1   // Univers DMX   0=SAC 1=Barre 2=Chariot 3=Dmx 4=Cube_strobe 5=Cube_parled 6=Sucette 7=minikolor
    #define FAKE_CURRENT 0
    #include "macro/Type/SK/mem.h" 

  #elif LULU_TYPE == 3
    #define L_TYPE "Pince"
    #define RUBAN_SIZE 17
    #define LULU_PATCHSIZE 18 // 18 = sk_pw / 16 = strobe led / 5 = par led / 20 = cube strobe dmx / 9 = cube par led dmx / 13 = cube minikolor
    #define LULU_UNI 7   // Univers DMX   0=SAC 1=Barre 2=Chariot 3=Dmx 4=Cube_strobe 5=Cube_parled 6=Sucette 7=minikolor
    #define FAKE_CURRENT 0
    #include "macro/Type/SK/mem.h" 

  #elif LULU_TYPE == 4
    #define L_TYPE "Fluo"
    #define RUBAN_SIZE 73
    #define LULU_PATCHSIZE 18 // 18 = sk_pw / 16 = strobe led / 5 = par led / 20 = cube strobe dmx / 9 = cube par led dmx / 13 = cube minikolor
    #define LULU_UNI 6   // Univers DMX   0=SAC 1=Barre 2=Chariot 3=Dmx 4=Cube_strobe 5=Cube_parled 6=Sucette 7=minikolor
    #define FAKE_CURRENT 0
    #include "macro/Type/SK/mem.h" 

  #elif LULU_TYPE == 5
    #define L_TYPE "Flex"
    #define RUBAN_SIZE 186
    #define LULU_PATCHSIZE 18 // 18 = sk_pw / 16 = strobe led / 5 = par led / 20 = cube strobe dmx / 9 = cube par led dmx / 13 = cube minikolor
    #define LULU_UNI 1   // Univers DMX   0=SAC 1=Barre 2=Chariot 3=Dmx 4=Cube_strobe 5=Cube_parled 6=Sucette 7=minikolor
    #define FAKE_CURRENT 0
    #include "macro/Type/SK/mem.h" 

  #elif LULU_TYPE == 6
    #define L_TYPE "Barrette" 
    #define RUBAN_SIZE 60
    #define LULU_PATCHSIZE 18 // 18 = sk_pw / 16 = strobe led / 5 = par led / 20 = cube strobe dmx / 9 = cube par led dmx / 13 = cube minikolor
    #define LULU_UNI 1   // Univers DMX   0=SAC 1=Barre 2=Chariot 3=Dmx 4=Cube_strobe 5=Cube_parled 6=Sucette 7=minikolor
    #define FAKE_CURRENT 0
    #include "macro/Type/SK/mem.h" 

  #elif LULU_TYPE == 7
    #define L_TYPE "Phone"
    #define RUBAN_SIZE 35
    #define LULU_PATCHSIZE 18 // 18 = sk_pw / 16 = strobe led / 5 = par led / 20 = cube strobe dmx / 9 = cube par led dmx / 13 = cube minikolor
    #define LULU_UNI 1   // Univers DMX   0=SAC 1=Barre 2=Chariot 3=Dmx 4=Cube_strobe 5=Cube_parled 6=Sucette 7=minikolor
    #define FAKE_CURRENT 0
    #include "macro/Type/SK/mem.h" 

  #elif LULU_TYPE == 8
    #define L_TYPE "Atom" 
    #define RUBAN_SIZE 25 // 5 pour tester avec les jauges de monitoring
    #define LULU_PATCHSIZE 18 // 18 = sk_pw / 16 = strobe led / 5 = par led / 20 = cube strobe dmx / 9 = cube par led dmx / 13 = cube minikolor
    #define LULU_UNI 1   // Univers DMX   0=SAC 1=Barre 2=Chariot 3=Dmx 4=Cube_strobe 5=Cube_parled 6=Sucette 7=minikolor
    #define FAKE_CURRENT 0
    #include "macro/Type/SK/mem.h" 

  #elif LULU_TYPE == 9
    #define L_TYPE "Chariot"
    #define RUBAN_SIZE 120
    #define LULU_PATCHSIZE 18 // 18 = sk_pw / 16 = strobe led / 5 = par led / 20 = cube strobe dmx / 9 = cube par led dmx / 13 = cube minikolor
    #define LULU_UNI 2   // Univers DMX   0=SAC 1=Barre 2=Chariot 3=Dmx 4=Cube_strobe 5=Cube_parled 6=Sucette 7=minikolor
    #define FAKE_CURRENT 0
    #include "macro/Show/H&S/mem_h&s.h" 

  #elif LULU_TYPE == 10
    #define L_TYPE "Power" 
    #define RUBAN_SIZE 120
    #define LULU_PATCHSIZE 18 // 18 = sk_pw / 16 = strobe led / 5 = par led / 20 = cube strobe dmx / 9 = cube par led dmx / 13 = cube minikolor
    #define LULU_UNI 0   // Univers DMX   0=SAC 1=Barre 2=Chariot 3=Dmx 4=Cube_strobe 5=Cube_parled 6=Sucette 7=minikolor
    #define FAKE_CURRENT 0
    #include "macro/Type/SK/mem.h" 

  #elif LULU_TYPE == 11
    #define L_TYPE "Dmx_strobe"
    #define RUBAN_SIZE 0
    #define LULU_PATCHSIZE 16 // 18 = sk_pw / 16 = strobe led / 5 = par led / 20 = cube strobe dmx / 9 = cube par led dmx / 13 = cube minikolor
    #define LULU_UNI 4   // Univers DMX   0=SAC 1=Barre 2=Chariot 3=Dmx 4=Cube_strobe 5=Cube_parled 6=Sucette 7=minikolor
    #define FAKE_CURRENT 0 
    #include "macro/Type/strobe/mem_strobe.h"

  #elif LULU_TYPE == 12
    #define RUBAN_SIZE 0
    #define L_TYPE "Dmx_par"
    #define LULU_PATCHSIZE 5 // 18 = sk_pw / 16 = strobe led / 5 = par led / 20 = cube strobe dmx / 9 = cube par led dmx / 13 = cube minikolor
    #define LULU_UNI 5   // Univers DMX   0=SAC 1=Barre 2=Chariot 3=Dmx 4=Cube_strobe 5=Cube_parled 6=Sucette 7=minikolor
    #define FAKE_CURRENT 0
    #include "macro/Type/parled/mem_parled.h" 

  #elif LULU_TYPE == 20
    #define RUBAN_SIZE 60
    #define L_TYPE "Cube_str"
    #define LULU_PATCHSIZE 20 // 18 = sk_pw / 16 = strobe led / 5 = par led / 20 = cube strobe dmx / 9 = cube par led dmx / 13 = cube minikolor
    #define LULU_UNI 4   // Univers DMX   0=SAC 1=Barre 2=Chariot 3=Dmx 4=Cube_strobe 5=Cube_parled 6=Sucette 7=minikolor
    #define FAKE_CURRENT 0
    #define ON_NO_WIFI 255
    #include "macro/Type/strobe/mem_pwm_strobe_dmx.h"

  #elif LULU_TYPE == 21
    #define RUBAN_SIZE 60
    #define L_TYPE "Cube_par"
    #define LULU_PATCHSIZE 9 // 18 = sk_pw / 16 = strobe led / 5 = par led / 20 = cube strobe dmx / 9 = cube par led dmx / 13 = cube minikolor
    #define LULU_UNI 5   // Univers DMX   0=SAC 1=Barre 2=Chariot 3=Dmx 4=Cube_strobe 5=Cube_parled 6=Sucette 7=minikolor
    #define FAKE_CURRENT 0
    #define ON_NO_WIFI 255
    #include "macro/Type/parled/mem_parled.h"

    #include "macro/Show/Baro/mem_pwm_baro_127.h"   // cube 1 3 5 7 9
    #include "macro/mem_cube_baro_127.h"

    // #include "macro/Show/Baro/mem_pwm_baro_125.h"   // cube 2 4 6 8 10
    // #include "macro/mem_cube_baro_125.h"

  #elif LULU_TYPE == 22
    #define RUBAN_SIZE 60
    #define L_TYPE "Cube_minikolor"
    #define LULU_PATCHSIZE 13 //  18 = sk_pw / 16 = strobe led / 5 = par led / 20 = cube strobe dmx / 9 = cube par led dmx / 13 = cube minikolor
    #define LULU_UNI 7   // Univers DMX   0=SAC 1=Barre 2=Chariot 3=Dmx 4=Cube_strobe 5=Cube_parled 6=Sucette 7=minikolor
    #define FAKE_CURRENT 0
    #define ON_NO_WIFI 255
    // #include "macro/Type/minikolor/mem_pwm_minikolor_dmx.h"       //
    #include "macro/Type/4pwm/mem_4pwm_base.h"          // 
    #include "macro/Type/minikolor/mem_minikolor_dmx.h" //
    #include "macro/mem_pwm_minikolor_dmx.h"     // 

  #elif LULU_TYPE == 23
    #define RUBAN_SIZE 60
    #define L_TYPE "Cube_elp"
    #define LULU_PATCHSIZE 7 //  18 = sk_pw / 16 = strobe led / 5 = par led / 20 = cube strobe dmx / 9 = cube par led dmx / 13 = cube minikolor / = elp
    #define LULU_UNI 7   // Univers DMX   0=SAC 1=Barre 2=Chariot 3=Dmx 4=Cube_strobe 5=Cube_parled 6=Sucette 7=minikolor 8=elp
    #define FAKE_CURRENT 0
    #define ON_NO_WIFI 255
    #include "macro/Type/4pwm/mem_4pwm_base.h"          // 
    #include "macro/Type/elp/mem_elp.h" //
    #include "macro/mem_pwm_elp_dmx.h"     //   

#elif LULU_TYPE == 30
    #define RUBAN_SIZE 60
    #define L_TYPE "Sucette"
    #define LULU_PATCHSIZE 9 // 18 = sk_pw / 16 = strobe led / 5 = par led / 20 = cube strobe dmx / 9 = cube par led dmx / 13 = cube minikolor
    #define LULU_UNI 6   // Univers DMX   0=SAC 1=Barre 2=Chariot 3=Dmx 4=Cube_strobe 5=Cube_parled 6=Sucette 7=minikolor
    #define FAKE_CURRENT 0
    #define ON_NO_WIFI 255 // 82 niveau pour les statics baronnie
    #include "macro/Type/parled/mem_parled.h"

    // #include "macro/Type/parled/mem_pwm_parled_sucette.h"     // base
    
    
    // #include "macro/Show/Baro/mem_pwm_baro_131.h"   // vincent
    // #include "macro/mem_sucette_baro_131.h"
    
    #include "macro/Show/Baro/mem_pwm_baro_132.h"   // jerome
    #include "macro/mem_sucette_baro_132.h"


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