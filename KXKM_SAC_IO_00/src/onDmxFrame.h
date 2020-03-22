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

    srr = (data[adr + 9] * data[adr + 9]) / 255;
    sgg = (data[adr + 10] * data[adr + 10]) / 255;
    sbb = (data[adr + 11] * data[adr + 11]) / 255;
    sww = (data[adr + 12] * data[adr + 12]) / 255;

    color_mode = data[adr + 13];
    mirror = data[adr + 14];

    zoom = (NUM_LEDS_PER_STRIP_max * data[adr + 15]) / 255;
    if (zoom <= 0)
      zoom = 1;
    NUM_LEDS_PER_STRIP = zoom;
    offset = (NUM_LEDS_PER_STRIP_max - zoom) / 2;

    if (k32->remote->getLamp() == -1)
    {
      k32->pwm->set(0, (data[adr + 16] * data[adr + 16]) / 255);
      k32->pwm->set(1, (data[adr + 17] * data[adr + 17]) / 255);
    }
    else if (k32->remote->getLamp() >= 0)
    {
      k32->pwm->setAll(k32->remote->getLamp());
    }

    if (color_mode >= 11 && color_mode <= 20)
    {
      pix_start = -1;
    }
    else
    {
      if ((pix_mod >= 0 && pix_mod <= 20) || (pix_mod >= 31 && pix_mod <= 230))
      {
        pix_start = ((data[adr + 5] * N_L_P_S) / 255) - 1;
        pix_end = pix_start + pix_start;
        pix_pos = (((pix_start + N_L_P_S + pix_end) * pix_pos_v) / 255) - (pix_end + 1);
      }
      else if (pix_mod >= 21 && pix_mod <= 30)
      {
        pix_start = data[adr + 5] - 1;
        pix_end = pix_start + pix_start;
        pix_pos = (((pix_start + N_L_P_S + pix_end) * pix_pos_v) / 255) - (pix_end + 1);
      }
      else if (pix_mod >= 231 && pix_mod <= 250)
      {
        pix_start = ((data[adr + 5] * N_L_P_S) / 255) - 1;
        pix_end = pix_start + pix_start;
        pix_pos = map(pix_pos_v, 0, 255, -NUM_LEDS_PER_STRIP + 1, NUM_LEDS_PER_STRIP + 1);
        color_rgbw(0, data[adr]);
        color_rgbw(1, data[adr + 1]);
        color_rgbw(2, data[adr + 2]);
        color_rgbw(3, data[adr + 3]);
      }
    }

    
    
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
  LOG("data [1] = " + data[1]);
  LOG("data [2] = " + data[2]);
  LOG("master = " + master);
  LOG("r = " + rr);
  LOG("g = " + gg);
  LOG("b = " + bb);
  LOG("w = " + ww);
  LOG("pix_mod = " + pix_mod);
  LOG("pix_start = " + pix_start);
  LOG("pix_center = " + pix_center);
  LOG("pix_end = " + pix_end);
  LOG("pix_pos = " + pix_pos);
  LOG("modulo = " + modulo);
  LOG("str_ws = " + str_ws);
  LOG(" srr = " + srr);
  LOG(" sgg = " + sgg);
  LOG(" sbb = " + sbb);
  LOG(" sww = " + sww);
  LOG(" color_mode = " + color_mode);
  LOG(" mirror = " + mirror);
  LOG(" pwm0 = " + k32->pwm->get(0));
  LOG(" pwm1 = " + k32->pwm->get(1));
#endif
} //onframedmx

void onArtNetFrame(uint16_t universe, uint16_t length, uint8_t sequence, uint8_t *data)
{
  if (k32->remote->getState() == REMOTE_MANU)
    k32->remote->setAuto();
  if (k32->remote->getState() == REMOTE_AUTO)
    onDmxFrame(universe, length, sequence, data);
}
