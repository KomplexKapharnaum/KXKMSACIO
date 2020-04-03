
#define Start_Preview 8

/////////////////////////////////////////active_frame/////////////////////////////////////

void active_frame(int mem)
{

  mem = mem % NUMBER_OF_MEM;

  if (mem == NUMBER_OF_MEM - 1 && k32->remote->getState() == REMOTE_MANU_STM)
  {
    state_btn = false;
    manu_counter = NUMBER_OF_MEM - 1;
    k32->remote->setAuto();
  }
  if (mem_call != mem)
  {
    mem_call = mem;

    if (mem == 0)
    {
      k32->modulo_sinus->setParam(0, 10000); // periode
      k32->modulo_sinus->setParam(1, 127);   // value min
      k32->modulo_sinus->setParam(2, 127);   // value max
      k32->modulo_sinus->play();
    }
    else if (mem == 8)
    {
      k32->modulo_fade->setParam(0, 5000); // fade time
      k32->modulo_fade->setParam(1, 255);  // start value
      k32->modulo_fade->setParam(2, 0);    // end value
      k32->modulo_fade->play();
    }
    else if (mem == 10)
    {
      k32->modulo_sinus->setParam(0, 1000); // periode
      k32->modulo_sinus->setParam(1, 0);    // value min
      k32->modulo_sinus->setParam(2, 255);  // value max
      k32->modulo_sinus->play();
    }
    else if (mem == 11)
    {
      k32->modulo_phase->setParam(0, 5000); // periode
      k32->modulo_phase->setParam(1, 0);    // value min
      k32->modulo_phase->setParam(2, 255);  // value max
      k32->modulo_phase->play();
    }
  } // (mem_call != mem)

  const int frameSize = adr + LULU_PATCHSIZE;
  uint8_t fakeframe[frameSize];

  for (int i = 0; i < LULU_PATCHSIZE; i++)
    fakeframe[adr + i - 1] = MEM[mem][i];

  if (k32->remote->getLamp() >= 0)
  {
    fakeframe[adr + 16 - 1] = k32->remote->getLamp();
    fakeframe[adr + 17 - 1] = k32->remote->getLamp();
  }

  if (mem == 0)
  {
    fakeframe[adr + 7 - 1] = k32->modulo_sinus->getValue();
  }
  else if (mem == 8)
  {
    fakeframe[adr - 1] = k32->modulo_fade->getValue();
    fakeframe[adr + 16 - 1] = k32->modulo_fade->getValue();
    fakeframe[adr + 17 - 1] = k32->modulo_fade->getValue();
  }
  else if (mem == 10)
  {
    fakeframe[adr + 15 - 1] = k32->modulo_sinus->getValue();
  }
  else if (mem == 11)
  {
    fakeframe[adr + 1 - 1] = k32->modulo_phase->getValue_1();
    fakeframe[adr + 2 - 1] = k32->modulo_phase->getValue_2();
    fakeframe[adr + 3 - 1] = k32->modulo_phase->getValue_3();
    fakeframe[adr + 16 - 1] = k32->modulo_phase->getValue_1();
    fakeframe[adr + 17 - 1] = k32->modulo_phase->getValue_1();
  }

  onDmxFrame(LULU_uni, adr + LULU_PATCHSIZE, 0, fakeframe);

} // active_frame

/////////////////////////////////////////preview_frame/////////////////////////////////////

void preview_frame(int mem)
{
  mem = mem % NUMBER_OF_MEM;
#ifdef DEBUG_btn
  LOGF(" preview_frame = %d\n", mem);
#endif

  int p = 0;
  for (int i = NUM_LEDS_PER_STRIP_max + Start_Preview; i < NUM_LEDS_PER_STRIP_max + Start_Preview + 6; i++)
  {
    strands[1]->pixels[i] = pixelFromRGBW((MEM_PREV[mem][p] * COEF_PREV), (MEM_PREV[mem][p + 1] * COEF_PREV), (MEM_PREV[mem][p + 2] * COEF_PREV), (MEM_PREV[mem][p + 3] * COEF_PREV));
    p = p + 4;
  }

} // preview_frame

/////////////////////////////////////////remote & wifi status/////////////////////////////////////

void remote_status(remoteState state)
{
  if (state == REMOTE_AUTO)
  {
    strands[1]->pixels[NUM_LEDS_PER_STRIP_max + Start_Preview - 2] = pixelFromRGBW(0, COEF_PREV, 0, 0); // green
    strands[1]->pixels[NUM_LEDS_PER_STRIP_max + Start_Preview + 7] = pixelFromRGBW(0, 0, 0, 0);         // black
  }
  else if (state == REMOTE_AUTO_LOCK)
  {
    strands[1]->pixels[NUM_LEDS_PER_STRIP_max + Start_Preview - 2] = pixelFromRGBW(COEF_PREV, 0, 0, 0); // red
    strands[1]->pixels[NUM_LEDS_PER_STRIP_max + Start_Preview + 7] = pixelFromRGBW(0, 0, 0, 0);         // black
  }
  else if (state == REMOTE_MANU)
  {
    strands[1]->pixels[NUM_LEDS_PER_STRIP_max + Start_Preview - 2] = pixelFromRGBW(0, COEF_PREV, 0, 0); // green
    strands[1]->pixels[NUM_LEDS_PER_STRIP_max + Start_Preview + 7] = pixelFromRGBW(0, COEF_PREV, 0, 0); // green
  }
  else if (state == REMOTE_MANU_LOCK)
  {
    strands[1]->pixels[NUM_LEDS_PER_STRIP_max + Start_Preview - 2] = pixelFromRGBW(COEF_PREV, 0, 0, 0); // red
    strands[1]->pixels[NUM_LEDS_PER_STRIP_max + Start_Preview + 7] = pixelFromRGBW(0, COEF_PREV, 0, 0); // green
  }
  else if (state == REMOTE_MANU_STM)
  {
    strands[1]->pixels[NUM_LEDS_PER_STRIP_max + Start_Preview - 2] = pixelFromRGBW(0, 0, COEF_PREV, 0); // blue
    strands[1]->pixels[NUM_LEDS_PER_STRIP_max + Start_Preview + 7] = pixelFromRGBW(0, 0, COEF_PREV, 0); // blue
  }
  else if (state == REMOTE_MANU_STM_LOCK)
  {
    strands[1]->pixels[NUM_LEDS_PER_STRIP_max + Start_Preview - 2] = pixelFromRGBW(COEF_PREV, 0, 0, 0); // red
    strands[1]->pixels[NUM_LEDS_PER_STRIP_max + Start_Preview + 7] = pixelFromRGBW(0, 0, COEF_PREV, 0); // blue
  }
  else if (state == REMOTE_MANU_LAMP)
  {
    strands[1]->pixels[NUM_LEDS_PER_STRIP_max + Start_Preview - 2] = pixelFromRGBW(0, COEF_PREV, 0, 0);             // green
    strands[1]->pixels[NUM_LEDS_PER_STRIP_max + Start_Preview + 7] = pixelFromRGBW(0, COEF_PREV / 2, 0, COEF_PREV); // white green
  }
} // remote_status

void wifi_status(int Wifi_Status)
{
  if (Wifi_Status > -45)
    strands[1]->pixels[NUM_LEDS_PER_STRIP_max + Start_Preview + 9] = pixelFromRGBW(0, COEF_PREV * 2, 0, 0);
  else if (Wifi_Status > -58)
    strands[1]->pixels[NUM_LEDS_PER_STRIP_max + Start_Preview + 9] = pixelFromRGBW(0, COEF_PREV, 0, 0);
  else if (Wifi_Status > -71)
    strands[1]->pixels[NUM_LEDS_PER_STRIP_max + Start_Preview + 9] = pixelFromRGBW(COEF_PREV, COEF_PREV / 2, 0, 0);
  else if (Wifi_Status > -80)
    strands[1]->pixels[NUM_LEDS_PER_STRIP_max + Start_Preview + 9] = pixelFromRGBW(COEF_PREV, 0, 0, 0);
  else if (Wifi_Status == 100)
    strands[1]->pixels[NUM_LEDS_PER_STRIP_max + Start_Preview + 9] = pixelFromRGBW(0, 0, COEF_PREV, 0);
} //wifi_status