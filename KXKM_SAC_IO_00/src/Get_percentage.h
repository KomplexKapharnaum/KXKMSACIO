
void get_percentage()
{
  percentage = k32->system->stm32->battery();
  if (percentage > 50)
  {
    //3ledverte
    for (int i = NUM_LEDS_PER_STRIP_max + 2; i < NUM_LEDS_PER_STRIP_max + 6; i++)
    {
      strands[1]->pixels[i] = pixelFromRGB(0, COEF_PREV, 0);
    } //for i
  }
  else if (percentage > 33)
  {
    //3ledorange
    for (int i = NUM_LEDS_PER_STRIP_max + 2; i < NUM_LEDS_PER_STRIP_max + 6; i++)
    {
      strands[1]->pixels[i] = pixelFromRGB(COEF_PREV, (COEF_PREV / 3), 0);
    } //for i
  }
  else if (percentage > 16)
  {
    //3ledrouge
    for (int i = NUM_LEDS_PER_STRIP_max + 2; i < NUM_LEDS_PER_STRIP_max + 6; i++)
    {
      strands[1]->pixels[i] = pixelFromRGB(127, 0, 0);
    } //for i
  }
  else if (percentage >= 1)
  {
    //3ledrouge clignote
    if (etat_r != 1)
    {
      for (int i = NUM_LEDS_PER_STRIP_max + 2; i < NUM_LEDS_PER_STRIP_max + 6; i++)
      {
        strands[1]->pixels[i] = pixelFromRGB(255, 0, 0);
      }
      etat_r = 1;
    }
    else if (etat_r != 0)
    {
      for (int i = NUM_LEDS_PER_STRIP_max + 2; i < NUM_LEDS_PER_STRIP_max + 6; i++)
      {
        strands[1]->pixels[i] = pixelFromRGB(0, 0, 0);
      }
      etat_r = 0;
    }
  }
}