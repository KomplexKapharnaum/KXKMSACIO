
void eff_modulo()
{
  float fade_coef = 10;
  unsigned long t_now = millis();

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////// modulo 30 -> 36  ////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  if (type_modulo == 30)
  {
    for (int i = 0; i < NUM_LEDS_PER_STRIP; i++)
    {
      if (i <= N_L_P_S)
      {
        di = i;
      }
      else if (i <= N_L_P_S * 2 && i >= N_L_P_S)
      {
        di = map(i, N_L_P_S + 1, N_L_P_S * 2, N_L_P_S, 0);
      }
      else if (i <= N_L_P_S * 3 && i >= N_L_P_S * 2)
      {
        di = map(i, (N_L_P_S * 2) + 1, N_L_P_S * 3, 0, N_L_P_S);
      }
      else if (i <= N_L_P_S * 4 && i >= N_L_P_S * 3)
      {
        di = map(i, (N_L_P_S * 3) + 1, N_L_P_S * 4, N_L_P_S, 0);
      }
      zo_pi_n_1_r[i] = pi_n_1_r[di];
      zo_pi_n_1_g[i] = pi_n_1_g[di];
      zo_pi_n_1_b[i] = pi_n_1_b[di];
      zo_pi_n_1_w[i] = pi_n_1_w[di];
    } //for i
  }   //modulo 30

  else if (type_modulo == 31)
  {
    if (str == 0 && t_now - str_ws_last > str_ws)
    {
      str_ws_last = t_now;
      str = 1;
    }
    else if (str == 1 && t_now - str_ws_last > STROB_ON_MS)
    {
      str_ws_last = t_now;
      str = 0;
    }
    else
    {
      return;
    }
    for (int i = 0; i < NUM_LEDS_PER_STRIP; i++)
    {
      if (i <= N_L_P_S)
      {
        di = i;
      }
      else if (i <= N_L_P_S * 2 && i >= N_L_P_S)
      {
        di = map(i, N_L_P_S + 1, N_L_P_S * 2, N_L_P_S, 0);
      }
      else if (i <= N_L_P_S * 3 && i >= N_L_P_S * 2)
      {
        di = map(i, (N_L_P_S * 2) + 1, N_L_P_S * 3, 0, N_L_P_S);
      }
      else if (i <= N_L_P_S * 4 && i >= N_L_P_S * 3)
      {
        di = map(i, (N_L_P_S * 3) + 1, N_L_P_S * 4, N_L_P_S, 0);
      }
      zo_pi_n_1_r[i] = pi_n_1_r[di] * str;
      zo_pi_n_1_g[i] = pi_n_1_g[di] * str;
      zo_pi_n_1_b[i] = pi_n_1_b[di] * str;
      zo_pi_n_1_w[i] = pi_n_1_w[di] * str;
    } //for i
  }   //modulo 31

  else if (type_modulo == 32)
  {
    if (str_ws <= 0)
      str_ws = 1;
    float time_modulo = str_ws * fade_coef;
    int t_modulo = str_ws * fade_coef;
    float module = 2 * abs((t_now % t_modulo) - time_modulo / 2) / time_modulo;
    module *= module;
    for (int i = 0; i < NUM_LEDS_PER_STRIP; i++)
    {
      if (i <= N_L_P_S)
      {
        di = i;
      }
      else if (i <= N_L_P_S * 2 && i >= N_L_P_S)
      {
        di = map(i, N_L_P_S + 1, N_L_P_S * 2, N_L_P_S, 0);
      }
      else if (i <= N_L_P_S * 3 && i >= N_L_P_S * 2)
      {
        di = map(i, (N_L_P_S * 2) + 1, N_L_P_S * 3, 0, N_L_P_S);
      }
      else if (i <= N_L_P_S * 4 && i >= N_L_P_S * 3)
      {
        di = map(i, (N_L_P_S * 3) + 1, N_L_P_S * 4, N_L_P_S, 0);
      }
      zo_pi_n_1_r[i] = pi_n_1_r[di] * module;
      zo_pi_n_1_g[i] = pi_n_1_g[di] * module;
      zo_pi_n_1_b[i] = pi_n_1_b[di] * module;
      zo_pi_n_1_w[i] = pi_n_1_w[di] * module;
    } //for i
  }   // modulo 32

  else if (type_modulo == 33)
  {
    if (str == 0 && t_now - str_ws_last > str_ws)
    {
      str_ws_last = t_now;
      str = 1;
    }
    else if (str == 1 && t_now - str_ws_last > STROB_ON_MS)
    {
      str_ws_last = t_now;
      str = 0;
      Black();
    }
    else
    {
      return;
    }
    int n_led_to_show = (min(NUM_LEDS_PER_STRIP - 8, S_seuil));

    for (int i = 0; i < n_led_to_show; i++)
    {
      do
      {
        a = random(0, NUM_LEDS_PER_STRIP);

      } while (zo_pi_n_1_r[a] != 0 || zo_pi_n_1_g[a] != 0 || zo_pi_n_1_b[a] != 0 || zo_pi_n_1_w[a] != 0);

      if (a <= N_L_P_S)
      {
        di = a;
      }
      else if (a <= N_L_P_S * 2 && a >= N_L_P_S)
      {
        di = map(a, N_L_P_S + 1, N_L_P_S * 2, N_L_P_S, 0);
      }
      else if (a <= N_L_P_S * 3 && a >= N_L_P_S * 2)
      {
        di = map(a, (N_L_P_S * 2) + 1, N_L_P_S * 3, 0, N_L_P_S);
      }
      else if (a <= N_L_P_S * 4 && a >= N_L_P_S * 3)
      {
        di = map(a, (N_L_P_S * 3) + 1, N_L_P_S * 4, N_L_P_S, 0);
      }
      zo_pi_n_1_r[a] = pi_n_1_r[di] * str;
      zo_pi_n_1_g[a] = pi_n_1_g[di] * str;
      zo_pi_n_1_b[a] = pi_n_1_b[di] * str;
      zo_pi_n_1_w[a] = pi_n_1_w[di] * str;
    } //for i
  }   //modulo 33

  else if (type_modulo == 34)
  {
    if (str == 0 && str_ws_last < t_now && t_now - str_ws_last > str_ws / (str_blind_ws * str_blind_ws))
    {
      str_ws_last = t_now;
      str = 1;
      str_blind_ws = str_blind_ws + 0.05;
      if (str_blind_ws >= 3)
      {
        str_blind_ws = 1;
        // Noir pendant 1 sec (dans le futur)
        str = 0;
        str_ws_last = t_now + 1000;
      }
    }
    else if (str == 1 && str_ws_last < t_now && t_now - str_ws_last > (STROB_ON_MS))
    {
      str_ws_last = t_now;
      str = 0;
    }
    else
    {
      return;
    }
    for (int i = 0; i < NUM_LEDS_PER_STRIP; i++)
    {
      if (i <= N_L_P_S)
      {
        di = i;
      }
      else if (i <= N_L_P_S * 2 && i >= N_L_P_S)
      {
        di = map(i, N_L_P_S + 1, N_L_P_S * 2, N_L_P_S, 0);
      }
      else if (i <= N_L_P_S * 3 && i >= N_L_P_S * 2)
      {
        di = map(i, (N_L_P_S * 2) + 1, N_L_P_S * 3, 0, N_L_P_S);
      }
      else if (i <= N_L_P_S * 4 && i >= N_L_P_S * 3)
      {
        di = map(i, (N_L_P_S * 3) + 1, N_L_P_S * 4, N_L_P_S, 0);
      }
      zo_pi_n_1_r[i] = pi_n_1_r[di] * str;
      zo_pi_n_1_g[i] = pi_n_1_g[di] * str;
      zo_pi_n_1_b[i] = pi_n_1_b[di] * str;
      zo_pi_n_1_w[i] = pi_n_1_w[di] * str;
    } //for i
  }   //modulo 34

  else if (type_modulo == 35)
  {

    if (str == 0 && str_ws_last < t_now && t_now - str_ws_last > str_ws / (str_blind_ws * str_blind_ws))
    {
      str_ws_last = t_now;
      str = 1;
      str_blind_ws = str_blind_ws + 0.05;
      if (str_blind_ws >= 3)
      {
        str_blind_ws = 1;
        // Noir pendant 1 sec (dans le futur)
        str = 0;
        str_ws_last = t_now + 1000;
      }
    }
    else if (str == 1 && str_ws_last < t_now && t_now - str_ws_last > (STROB_ON_MS))
    {
      str_ws_last = t_now;
      str = 0;
      Black();
    }
    else
    {
      return;
    }
    int n_led_to_show = min(NUM_LEDS_PER_STRIP - 8, S_seuil);

    for (int i = 0; i < n_led_to_show; i++)
    {
      do
      {
        a = random(0, NUM_LEDS_PER_STRIP);

      } while (zo_pi_n_1_r[a] != 0 || zo_pi_n_1_g[a] != 0 || zo_pi_n_1_b[a] != 0 || zo_pi_n_1_w[a] != 0);

      if (a <= N_L_P_S)
      {
        di = a;
      }
      else if (a <= N_L_P_S * 2 && a >= N_L_P_S)
      {
        di = map(a, N_L_P_S + 1, N_L_P_S * 2, N_L_P_S, 0);
      }
      else if (a <= N_L_P_S * 3 && a >= N_L_P_S * 2)
      {
        di = map(a, (N_L_P_S * 2) + 1, N_L_P_S * 3, 0, N_L_P_S);
      }
      else if (a <= N_L_P_S * 4 && a >= N_L_P_S * 3)
      {
        di = map(a, (N_L_P_S * 3) + 1, N_L_P_S * 4, N_L_P_S, 0);
      }
      zo_pi_n_1_r[a] = pi_n_1_r[di] * str;
      zo_pi_n_1_g[a] = pi_n_1_g[di] * str;
      zo_pi_n_1_b[a] = pi_n_1_b[di] * str;
      zo_pi_n_1_w[a] = pi_n_1_w[di] * str;
    } //for i
  }   //modulo 35

  else if (type_modulo == 36)
  {
    if (old_S_seuil != S_seuil)
    {
      Black();
      old_S_seuil = S_seuil;
    }

    int n_led_to_show = min(NUM_LEDS_PER_STRIP - 8, S_seuil);

    for (int i = 0; i < n_led_to_show; i++)
    {
      do
      {
        a = random(0, NUM_LEDS_PER_STRIP);

      } while (zo_pi_n_1_r[a] != 0 || zo_pi_n_1_g[a] != 0 || zo_pi_n_1_b[a] != 0 || zo_pi_n_1_w[a] != 0);

      if (a <= N_L_P_S)
      {
        di = a;
      }
      else if (a <= N_L_P_S * 2 && a >= N_L_P_S)
      {
        di = map(a, N_L_P_S + 1, N_L_P_S * 2, N_L_P_S, 0);
      }
      else if (a <= N_L_P_S * 3 && a >= N_L_P_S * 2)
      {
        di = map(a, (N_L_P_S * 2) + 1, N_L_P_S * 3, 0, N_L_P_S);
      }
      else if (a <= N_L_P_S * 4 && a >= N_L_P_S * 3)
      {
        di = map(a, (N_L_P_S * 3) + 1, N_L_P_S * 4, N_L_P_S, 0);
      }
      zo_pi_n_1_r[a] = pi_n_1_r[di];
      zo_pi_n_1_g[a] = pi_n_1_g[di];
      zo_pi_n_1_b[a] = pi_n_1_b[di];
      zo_pi_n_1_w[a] = pi_n_1_w[di];
    } //for i
    old_S_seuil = S_seuil - 1;
  } //modulo 36

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////// modulo 60 -> 66 /////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  else if (type_modulo == 60)
  {
    for (int i = 0; i < NUM_LEDS_PER_STRIP; i++)
    {
      if (i <= N_L_P_S)
      {
        di = i;
      }
      else if (i <= N_L_P_S * 2 && i >= N_L_P_S)
      {
        di = map(i, N_L_P_S + 1, N_L_P_S * 2, 0, N_L_P_S);
      }
      else if (i <= N_L_P_S * 3 && i >= N_L_P_S * 2)
      {
        di = map(i, (N_L_P_S * 2) + 1, N_L_P_S * 3, 0, N_L_P_S);
      }
      else if (i <= N_L_P_S * 4 && i >= N_L_P_S * 3)
      {
        di = map(i, (N_L_P_S * 3) + 1, N_L_P_S * 4, 0, N_L_P_S);
      }
      zo_pi_n_1_r[i] = pi_n_1_r[di];
      zo_pi_n_1_g[i] = pi_n_1_g[di];
      zo_pi_n_1_b[i] = pi_n_1_b[di];
      zo_pi_n_1_w[i] = pi_n_1_w[di];
    } //for i
  }   //modulo 60

  else if (type_modulo == 61)
  {
    if (str == 0 && t_now - str_ws_last > str_ws)
    {
      str_ws_last = t_now;
      str = 1;
    }
    else if (str == 1 && t_now - str_ws_last > STROB_ON_MS)
    {
      str_ws_last = t_now;
      str = 0;
    }
    else
    {
      return;
    }
    for (int i = 0; i < NUM_LEDS_PER_STRIP; i++)
    {
      if (i <= N_L_P_S)
      {
        di = i;
      }
      else if (i <= N_L_P_S * 2 && i >= N_L_P_S)
      {
        di = map(i, N_L_P_S + 1, N_L_P_S * 2, 0, N_L_P_S);
      }
      else if (i <= N_L_P_S * 3 && i >= N_L_P_S * 2)
      {
        di = map(i, (N_L_P_S * 2) + 1, N_L_P_S * 3, 0, N_L_P_S);
      }
      else if (i <= N_L_P_S * 4 && i >= N_L_P_S * 3)
      {
        di = map(i, (N_L_P_S * 3) + 1, N_L_P_S * 4, 0, N_L_P_S);
      }
      zo_pi_n_1_r[i] = pi_n_1_r[di] * str;
      zo_pi_n_1_g[i] = pi_n_1_g[di] * str;
      zo_pi_n_1_b[i] = pi_n_1_b[di] * str;
      zo_pi_n_1_w[i] = pi_n_1_w[di] * str;
    } //for i
  }   //modulo 61

  else if (type_modulo == 62)
  {
    if (str_ws <= 0)
      str_ws = 1;
    float time_modulo = str_ws * fade_coef;
    int t_modulo = str_ws * fade_coef;
    float module = 2 * abs((t_now % t_modulo) - time_modulo / 2) / time_modulo;
    module *= module;
    for (int i = 0; i < NUM_LEDS_PER_STRIP; i++)
    {
      if (i <= N_L_P_S)
      {
        di = i;
      }
      else if (i <= N_L_P_S * 2 && i >= N_L_P_S)
      {
        di = map(i, N_L_P_S + 1, N_L_P_S * 2, 0, N_L_P_S);
      }
      else if (i <= N_L_P_S * 3 && i >= N_L_P_S * 2)
      {
        di = map(i, (N_L_P_S * 2) + 1, N_L_P_S * 3, 0, N_L_P_S);
      }
      else if (i <= N_L_P_S * 4 && i >= N_L_P_S * 3)
      {
        di = map(i, (N_L_P_S * 3) + 1, N_L_P_S * 4, 0, N_L_P_S);
      }
      zo_pi_n_1_r[i] = pi_n_1_r[di] * module;
      zo_pi_n_1_g[i] = pi_n_1_g[di] * module;
      zo_pi_n_1_b[i] = pi_n_1_b[di] * module;
      zo_pi_n_1_w[i] = pi_n_1_w[di] * module;
    } //for i
  }   // modulo 62

  else if (type_modulo == 63)
  {
    if (str == 0 && t_now - str_ws_last > str_ws)
    {
      str_ws_last = t_now;
      str = 1;
    }
    else if (str == 1 && t_now - str_ws_last > STROB_ON_MS)
    {
      str_ws_last = t_now;
      str = 0;
      Black();
    }
    else
    {
      return;
    }
    int n_led_to_show = (min(NUM_LEDS_PER_STRIP - 8, S_seuil));

    for (int i = 0; i < n_led_to_show; i++)
    {
      do
      {
        a = random(0, NUM_LEDS_PER_STRIP);

      } while (zo_pi_n_1_r[a] != 0 || zo_pi_n_1_g[a] != 0 || zo_pi_n_1_b[a] != 0 || zo_pi_n_1_w[a] != 0);

      if (a <= N_L_P_S)
      {
        di = a;
      }
      else if (a <= N_L_P_S * 2 && a >= N_L_P_S)
      {
        di = map(a, N_L_P_S + 1, N_L_P_S * 2, 0, N_L_P_S);
      }
      else if (a <= N_L_P_S * 3 && a >= N_L_P_S * 2)
      {
        di = map(a, (N_L_P_S * 2) + 1, N_L_P_S * 3, 0, N_L_P_S);
      }
      else if (a <= N_L_P_S * 4 && a >= N_L_P_S * 3)
      {
        di = map(a, (N_L_P_S * 3) + 1, N_L_P_S * 4, 0, N_L_P_S);
      }
      zo_pi_n_1_r[a] = pi_n_1_r[di] * str;
      zo_pi_n_1_g[a] = pi_n_1_g[di] * str;
      zo_pi_n_1_b[a] = pi_n_1_b[di] * str;
      zo_pi_n_1_w[a] = pi_n_1_w[di] * str;
    } //for i
  }   //modulo 63

  else if (type_modulo == 64)
  {
    if (str == 0 && str_ws_last < t_now && t_now - str_ws_last > str_ws / (str_blind_ws * str_blind_ws))
    {
      str_ws_last = t_now;
      str = 1;
      str_blind_ws = str_blind_ws + 0.05;
      if (str_blind_ws >= 3)
      {
        str_blind_ws = 1;
        // Noir pendant 1 sec (dans le futur)
        str = 0;
        str_ws_last = t_now + 1000;
      }
    }
    else if (str == 1 && str_ws_last < t_now && t_now - str_ws_last > (STROB_ON_MS))
    {
      str_ws_last = t_now;
      str = 0;
    }
    else
    {
      return;
    }
    for (int i = 0; i < NUM_LEDS_PER_STRIP; i++)
    {
      if (i <= N_L_P_S)
      {
        di = i;
      }
      else if (i <= N_L_P_S * 2 && i >= N_L_P_S)
      {
        di = map(i, N_L_P_S + 1, N_L_P_S * 2, 0, N_L_P_S);
      }
      else if (i <= N_L_P_S * 3 && i >= N_L_P_S * 2)
      {
        di = map(i, (N_L_P_S * 2) + 1, N_L_P_S * 3, 0, N_L_P_S);
      }
      else if (i <= N_L_P_S * 4 && i >= N_L_P_S * 3)
      {
        di = map(i, (N_L_P_S * 3) + 1, N_L_P_S * 4, 0, N_L_P_S);
      }
      zo_pi_n_1_r[i] = pi_n_1_r[di] * str;
      zo_pi_n_1_g[i] = pi_n_1_g[di] * str;
      zo_pi_n_1_b[i] = pi_n_1_b[di] * str;
      zo_pi_n_1_w[i] = pi_n_1_w[di] * str;
    } //for i
  }   //modulo 64

  else if (type_modulo == 65)
  {

    if (str == 0 && str_ws_last < t_now && t_now - str_ws_last > str_ws / (str_blind_ws * str_blind_ws))
    {
      str_ws_last = t_now;
      str = 1;
      str_blind_ws = str_blind_ws + 0.05;
      if (str_blind_ws >= 3)
      {
        str_blind_ws = 1;
        // Noir pendant 1 sec (dans le futur)
        str = 0;
        str_ws_last = t_now + 1000;
      }
    }
    else if (str == 1 && str_ws_last < t_now && t_now - str_ws_last > (STROB_ON_MS))
    {
      str_ws_last = t_now;
      str = 0;
      Black();
    }
    else
    {
      return;
    }
    int n_led_to_show = min(NUM_LEDS_PER_STRIP - 8, S_seuil);

    for (int i = 0; i < n_led_to_show; i++)
    {
      do
      {
        a = random(0, NUM_LEDS_PER_STRIP);

      } while (zo_pi_n_1_r[a] != 0 || zo_pi_n_1_g[a] != 0 || zo_pi_n_1_b[a] != 0 || zo_pi_n_1_w[a] != 0);

      if (a <= N_L_P_S)
      {
        di = a;
      }
      else if (a <= N_L_P_S * 2 && a >= N_L_P_S)
      {
        di = map(a, N_L_P_S + 1, N_L_P_S * 2, 0, N_L_P_S);
      }
      else if (a <= N_L_P_S * 3 && a >= N_L_P_S * 2)
      {
        di = map(a, (N_L_P_S * 2) + 1, N_L_P_S * 3, 0, N_L_P_S);
      }
      else if (a <= N_L_P_S * 4 && a >= N_L_P_S * 3)
      {
        di = map(a, (N_L_P_S * 3) + 1, N_L_P_S * 4, 0, N_L_P_S);
      }
      zo_pi_n_1_r[a] = pi_n_1_r[di] * str;
      zo_pi_n_1_g[a] = pi_n_1_g[di] * str;
      zo_pi_n_1_b[a] = pi_n_1_b[di] * str;
      zo_pi_n_1_w[a] = pi_n_1_w[di] * str;
    } //for i
  }   //modulo 65

  else if (type_modulo == 66)
  {
    if (old_S_seuil != S_seuil)
    {
      Black();
      old_S_seuil = S_seuil;
    }

    int n_led_to_show = min(NUM_LEDS_PER_STRIP - 8, S_seuil);

    for (int i = 0; i < n_led_to_show; i++)
    {
      do
      {
        a = random(0, NUM_LEDS_PER_STRIP);

      } while (zo_pi_n_1_r[a] != 0 || zo_pi_n_1_g[a] != 0 || zo_pi_n_1_b[a] != 0 || zo_pi_n_1_w[a] != 0);

      if (a <= N_L_P_S)
      {
        di = a;
      }
      else if (a <= N_L_P_S * 2 && a >= N_L_P_S)
      {
        di = map(a, N_L_P_S + 1, N_L_P_S * 2, 0, N_L_P_S);
      }
      else if (a <= N_L_P_S * 3 && a >= N_L_P_S * 2)
      {
        di = map(a, (N_L_P_S * 2) + 1, N_L_P_S * 3, 0, N_L_P_S);
      }
      else if (a <= N_L_P_S * 4 && a >= N_L_P_S * 3)
      {
        di = map(a, (N_L_P_S * 3) + 1, N_L_P_S * 4, 0, N_L_P_S);
      }
      zo_pi_n_1_r[a] = pi_n_1_r[di];
      zo_pi_n_1_g[a] = pi_n_1_g[di];
      zo_pi_n_1_b[a] = pi_n_1_b[di];
      zo_pi_n_1_w[a] = pi_n_1_w[di];
    } //for i
    old_S_seuil = S_seuil - 1;
  } //modulo 66
  do_zoom();
} //eff_modulo