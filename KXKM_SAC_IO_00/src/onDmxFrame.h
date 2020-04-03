//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////// onDmxFrame //////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
void onDmxFrame(uint16_t universe, uint16_t length, uint8_t sequence, uint8_t *data)
{
  sendFrame = 1;

  if (universe == LULU_uni)
  {

#ifdef DEBUG_dmxframe
    LOGINL("dmx frame: ");
    for (int i = 0; i < length; i++)
    {
      LOGINL(data[i]);
      LOGINL(" ");
    }
    LOG("");
#endif

    master = data[adr - 1];
    rr = (data[adr] * data[adr]) / 255;
    gg = (data[adr + 1] * data[adr + 1]) / 255;
    bb = (data[adr + 2] * data[adr + 2]) / 255;
    ww = (data[adr + 3] * data[adr + 3]) / 255;

    pix_mod = data[adr + 4];
    pix_pos_v = data[adr + 6];

    modulo = data[adr + 7];
    str_ws = (data[adr + 8] * data[adr + 8]) / 33;

    start_color = data[adr + 9];
    end_color = data[adr + 10];
    srr = (data[adr + 9] * data[adr + 9]) / 255;
    sgg = (data[adr + 10] * data[adr + 10]) / 255;
    sbb = (data[adr + 11] * data[adr + 11]) / 255;
    sww = (data[adr + 12] * data[adr + 12]) / 255;

    color_mode = data[adr + 13];
    mirror = data[adr + 14];

    zoom = ((NUM_LEDS_PER_STRIP_max * data[adr + 15]) / 255) * 1.0;
    if (zoom <= 0)
      zoom = 1;
    NUM_LEDS_PER_STRIP = nearbyint(zoom);
    offset = ((NUM_LEDS_PER_STRIP_max - zoom) / 2) * 1.0;

    /////////////////////////////////////////LAMP/////////////////////////////////////////
    if (k32->remote->getState() != REMOTE_MANU_LAMP)
    {
      if (k32->remote->getLamp() == -1)
      {
        k32->pwm->set(0, (data[adr + 16] * data[adr + 16]) / 255);
        k32->pwm->set(1, (data[adr + 17] * data[adr + 17]) / 255);
      }
      else if (k32->remote->getLamp() >= 0)
      {
        k32->pwm->setAll(k32->remote->getLamp());
      }
    }
    else
    {
      k32->pwm->setAll(k32->remote->getLampGrad());
    }

    /////////////////////////////////////////MODE/////////////////////////////////////////

    if ((pix_mod >= 0 && pix_mod <= 20))
    {
      pix_start = (((data[adr + 5] * N_L_P_S) / 255) - 1);
      pix_end = pix_start + pix_start;
      pix_pos = map(pix_pos_v, 0, 255, -N_L_P_S, N_L_P_S);
    }
    else if (pix_mod >= 21 && pix_mod <= 30)
    {
      pix_start = (((data[adr + 5] * N_L_P_S) / 255) - 1);
      pix_pos = map(pix_pos_v, 0, 255, 0, N_L_P_S);
    }
    else if (pix_mod >= 31 && pix_mod <= 60)
    {
      rap_tri = ((data[adr + 5] * N_L_P_S) / 255);
      pix_start = ((rap_tri - 1) * 2);
      pix_end = pix_start + pix_start;
      pix_pos = (N_L_P_S / 2) + map(pix_pos_v, 0, 255, -(N_L_P_S + pix_end + 1), pix_start + N_L_P_S + 1);
    }
    else if (pix_mod >= 231 && pix_mod <= 250)
    {
      pix_start = (((data[adr + 5] * N_L_P_S) / 255) - 1);
      pix_end = pix_start + pix_start;
      rap_tri = map(data[adr + 5], 0, 255, 0, NUM_LEDS_PER_STRIP * 2);
      pix_pos = ((NUM_LEDS_PER_STRIP / 2 - rap_tri / 2) + map(pix_pos_v, 0, 255, -NUM_LEDS_PER_STRIP + 1, NUM_LEDS_PER_STRIP + 1));
      color_rgbw(0, data[adr]);
      color_rgbw(1, data[adr + 1]);
      color_rgbw(2, data[adr + 2]);
      color_rgbw(3, data[adr + 3]);
    }
    // }

    pix_center = ((pix_start) / 2) + pix_pos;

    //&& mirror
    if (mirror >= 0 && mirror <= 10)
    { // no mirror
      N_L_P_S = (NUM_LEDS_PER_STRIP);
    }
    else if (mirror >= 11 && mirror <= 20)
    { // mirror <>
      N_L_P_S = (NUM_LEDS_PER_STRIP / 2);
    }
    else if (mirror >= 21 && mirror <= 30)
    { // mirror <><
      N_L_P_S = (NUM_LEDS_PER_STRIP / 3);
    }
    else if (mirror >= 31 && mirror <= 40)
    { // mirror <><>
      N_L_P_S = (NUM_LEDS_PER_STRIP / 4);
    }
    else if (mirror >= 41 && mirror <= 50)
    { // mirror <<
      N_L_P_S = (NUM_LEDS_PER_STRIP / 2);
    }
    else if (mirror >= 51 && mirror <= 60)
    { // mirror <<<
      N_L_P_S = (NUM_LEDS_PER_STRIP / 3);
    }
    else if (mirror >= 61 && mirror <= 70)
    { // mirror <<<<
      N_L_P_S = (NUM_LEDS_PER_STRIP / 4);
    }

    // modulo mode
    if (mirror >= 0 && mirror <= 40)
    {
      if ((modulo >= 0) && modulo <= 10)
      {
        type_modulo = 30;
      }
      else if ((modulo >= 11) && modulo <= 20)
      {
        type_modulo = 31;
      }
      else if ((modulo >= 21) && modulo <= 30)
      {
        type_modulo = 32;
      }
      else if ((modulo >= 31) && modulo <= 110)
      {
        Black();
        type_modulo = 33;
        S_seuil = (modulo - 30) * 4;
        //    type_effet = 255;
      }
      else if ((modulo >= 111) && modulo <= 120)
      {
        type_modulo = 34;
      }
      else if ((modulo >= 121) && modulo <= 200)
      {
        Black();
        type_modulo = 35;
        S_seuil = (modulo - 120) * 4;
        //    type_effet = 255;
      }
      else if ((modulo >= 201) && modulo <= 255)
      {
        type_modulo = 36;
        S_seuil = (modulo - 200) * 4;
        //    type_effet = 255;
      }
    }
    else if (mirror >= 41 && mirror <= 70)
    {
      if ((modulo >= 0) && modulo <= 10)
      {
        type_modulo = 60;
      }
      else if ((modulo >= 11) && modulo <= 20)
      {
        type_modulo = 61;
      }
      else if ((modulo >= 21) && modulo <= 30)
      {
        type_modulo = 62;
      }
      else if ((modulo >= 31) && modulo <= 110)
      {
        Black();
        type_modulo = 63;
        S_seuil = (modulo - 30) * 4;
        //    type_effet = 255;
      }
      else if ((modulo >= 111) && modulo <= 120)
      {
        type_modulo = 64;
      }
      else if ((modulo >= 121) && modulo <= 200)
      {
        Black();
        type_modulo = 65;
        S_seuil = (modulo - 120) * 4;
        //    type_effet = 255;
      }
      else if ((modulo >= 201) && modulo <= 255)
      {
        type_modulo = 66;
        S_seuil = (modulo - 200) * 4;
        //    type_effet = 255;
      }
    }
  } // if universe == LULU_uni

  previousDataLength = length;

  if (sendFrame)
  {
    // Reset universeReceived to 0
    memset(universesReceived, 0, maxUniverses);
  } //sendFrame

#ifdef DEBUG_dmx
  LOGF("data [1] = %d\n", data[1]);
  LOGF("data [2] = %d\n", data[2]);
  LOGF("master = %d\n", master);
  LOGF("r = %d\n", rr);
  LOGF("g = %d\n", gg);
  LOGF("b = %d\n", bb);
  LOGF("w = %d\n", ww);
  LOGF("pix_mod = %d\n", pix_mod);
  LOGF("pix_start = %d\n", pix_start);
  LOGF("pix_center = %d\n", pix_center);
  LOGF("pix_end = %d\n", pix_end);
  LOGF("pix_pos = %d\n", pix_pos);
  LOGF("modulo = %d\n", modulo);
  LOGF("str_ws = %d\n", str_ws);
  LOGF(" srr = %d\n", srr);
  LOGF(" sgg = %d\n", sgg);
  LOGF(" sbb = %d\n", sbb);
  LOGF(" sww = %d\n", sww);
  LOGF(" color_mode = %d\n", color_mode);
  LOGF(" mirror = %d\n", mirror);
  LOGF(" zoom = %d\n", zoom);
  LOGF(" pwm0 = %d\n", k32->pwm->get(0));
  LOGF(" pwm1 = %d\n", k32->pwm->get(1));
#endif
} //onframedmx

//////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////// onArtNetFrame //////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////

void onArtNetFrame(uint16_t universe, uint16_t length, uint8_t sequence, uint8_t *data)
{
  if (data[adr + 14] >= 251)
  {
    k32->remote->setAuto_Lock();
  }
  if (k32->remote->getState() < 2 || k32->remote->getState() == REMOTE_MANU_LAMP) // == REMOTE_AUTO || REMOTE_AUTO_LOCK
  {
    onDmxFrame(universe, length, sequence, data);
  }
}
