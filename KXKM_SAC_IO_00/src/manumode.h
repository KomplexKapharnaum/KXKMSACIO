
void manu_frame(int mem)
{
  mem = mem % NUMBER_OF_MEM;

  if (mem == NUMBER_OF_MEM - 1)
  {
    state_btn_stm = false;
    LOG(" state_btn_stm FALSE ");
  }

  if (mem_call != mem)
  {
    mem_call = mem;
    if (mem == 8)
    {
      k32->modulo_fadein->setParam(0, 3000); // fade time
      k32->modulo_fadein->setParam(1, 0);    // start value
      k32->modulo_fadein->setParam(2, 255);  // end value
      k32->modulo_fadein->play;
    }
    if (mem == 10)
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
  }
  const int frameSize = adr + LULU_PATCHSIZE;
  uint8_t fakeframe[frameSize];

  for (int i = 0; i < LULU_PATCHSIZE; i++)
    fakeframe[adr + i - 1] = MEM[mem][i];

  if (k32->remote->getLamp() >= 0)
  {
    fakeframe[adr + 17 - 1] = k32->remote->getLamp();
    fakeframe[adr + 18 - 1] = k32->remote->getLamp();
  }

  if (mem == 8)
  {
    fakeframe[adr - 1] = k32->modulo_fadein->getValue();
  }
  else if (mem == 10)
  {
    fakeframe[adr + 16 - 1] = k32->modulo_sinus->getValue();
  }
  else if (mem == 11)
  {
    fakeframe[adr + 1 - 1] = k32->modulo_phase->getValue_1();
    fakeframe[adr + 2 - 1] = k32->modulo_phase->getValue_2();
    fakeframe[adr + 3 - 1] = k32->modulo_phase->getValue_3();
  }

  onDmxFrame(LULU_uni, adr + LULU_PATCHSIZE, 0, fakeframe);

  int p = 0;
  for (int i = NUM_LEDS_PER_STRIP_max + 8; i < NUM_LEDS_PER_STRIP_max + 14; i++)
  {
    strands[1]->pixels[i] = pixelFromRGBW((MEM_PREV[mem][p] * COEF_PREV), (MEM_PREV[mem][p + 1] * COEF_PREV), (MEM_PREV[mem][p + 2] * COEF_PREV), (MEM_PREV[mem][p + 3] * COEF_PREV));
    p = p + 4;
  }

} // manu_frame

void active_frame(int mem)
{

  const int frameSize = adr + LULU_PATCHSIZE;
  uint8_t fakeframe[frameSize];

  for (int i = 0; i < LULU_PATCHSIZE; i++)
    fakeframe[adr + i - 1] = MEM[mem][i];
  onDmxFrame(LULU_uni, adr + LULU_PATCHSIZE, 0, fakeframe);

} // active_frame

void preview_frame(int mem)
{

  int p = 0;
  for (int i = NUM_LEDS_PER_STRIP_max + 8; i < NUM_LEDS_PER_STRIP_max + 14; i++)
  {
    strands[1]->pixels[i] = pixelFromRGBW((MEM_PREV[mem][p] * COEF_PREV), (MEM_PREV[mem][p + 1] * COEF_PREV), (MEM_PREV[mem][p + 2] * COEF_PREV), (MEM_PREV[mem][p + 3] * COEF_PREV));
    p = p + 4;
  }

} // preview_frame

void remote_status(remoteState state)
{
  if (state == REMOTE_AUTO)
    strands[1]->pixels[NUM_LEDS_PER_STRIP_max + 14] = pixelFromRGBW(0, 0, 0, 0); // noir
  else if (state == REMOTE_MANU)
    strands[1]->pixels[NUM_LEDS_PER_STRIP_max + 14] = pixelFromRGBW(0, 127, 0, 0); // vert
  else if (state == REMOTE_MANULOCK)
    strands[1]->pixels[NUM_LEDS_PER_STRIP_max + 14] = pixelFromRGBW(127, 0, 0, 0); // rouge
}
