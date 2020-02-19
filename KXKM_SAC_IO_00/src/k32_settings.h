
void k32_settings() {

#ifdef K32_SET_NODEID
  k32->system->id(K32_SET_NODEID);
#endif
#ifdef K32_SET_HWREVISION
  k32->system->hw(K32_SET_HWREVISION);
#endif

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
  k32->system->preferences.putUInt("RUBAN_type", RUBAN_TYPE);
  RUBAN_type = RUBAN_TYPE;
#else
  RUBAN_type = k32->system->preferences.getUInt("RUBAN_type", LED_SK6812W_V1);
#endif

#ifdef R_TYPE
  k32->system->preferences.putString("R_type", R_TYPE);
  R_type = R_TYPE;
#else
  R_type = k32->system->preferences.getString("R_type", "_SK");
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
  NUM_LEDS_PER_STRIP_max = k32->system->preferences.getUInt("NUM_leds", 186);
#endif


  // Calculate adr // channels
  adr = (1 + (LULU_id - 1) * (LULU_PATCHSIZE));
  numberOfChannels = NUM_STRIPS * NUM_LEDS_PER_STRIP_max * 4;
  maxUniverses = numberOfChannels / 512 + ((numberOfChannels % 512) ? 1 : 0);
  startUniverse = LULU_uni;

  // Calculate NUM leds MAX & L/R TYPE
  NUM_LEDS_PER_STRIP = NUM_LEDS_PER_STRIP_max;
  N_L_P_S = NUM_LEDS_PER_STRIP_max;

  // Make name and PINS
  nodeName += L_type + R_type + "-" + String(LULU_id) + "-v" + String(LULU_VER);
  PINS[0] = k32->system->ledpin(0);
  PINS[1] = k32->system->ledpin(1);

}//k32_settings()