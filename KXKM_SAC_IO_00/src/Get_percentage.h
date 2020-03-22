
bool etat_r = false;

void get_percentage()
{
  percentage = k32->system->stm32->battery();


  /////////////////////  GREEN   ///////////////////////

  if (percentage > 86)
  {
    //4ledverte
    for (int i = NUM_LEDS_PER_STRIP_max + 2; i < NUM_LEDS_PER_STRIP_max + 6; i++)
    {
      strands[1]->pixels[i] = pixelFromRGB(0, COEF_PREV, 0);
    } //for i
  }
  else if (percentage > 74)
  {
    //3ledverte
    for (int i = NUM_LEDS_PER_STRIP_max + 2; i < NUM_LEDS_PER_STRIP_max + 6; i++)
    {
      if (i < NUM_LEDS_PER_STRIP_max + 5)
      {
        strands[1]->pixels[i] = pixelFromRGB(0, COEF_PREV, 0);
      }
      else
      {
        strands[1]->pixels[i] = pixelFromRGB(0, 0, 0);
      }
    } //for i
  }
    else if (percentage > 62)
  {
    //2ledverte
    for (int i = NUM_LEDS_PER_STRIP_max + 2; i < NUM_LEDS_PER_STRIP_max + 6; i++)
    {
      if (i < NUM_LEDS_PER_STRIP_max + 4)
      {
        strands[1]->pixels[i] = pixelFromRGB(0, COEF_PREV, 0);
      }
      else
      {
        strands[1]->pixels[i] = pixelFromRGB(0, 0, 0);
      }
    } //for i
  }
      else if (percentage > 50)
  {
    //1ledverte
    for (int i = NUM_LEDS_PER_STRIP_max + 2; i < NUM_LEDS_PER_STRIP_max + 6; i++)
    {
      if (i < NUM_LEDS_PER_STRIP_max + 3)
      {
        strands[1]->pixels[i] = pixelFromRGB(0, COEF_PREV, 0);
      }
      else
      {
        strands[1]->pixels[i] = pixelFromRGB(0, 0, 0);
      }
    } //for i
  }

  /////////////////////  ORANGE   ///////////////////////

  else if (percentage > 46)
  {
    //4ledorange
    for (int i = NUM_LEDS_PER_STRIP_max + 2; i < NUM_LEDS_PER_STRIP_max + 6; i++)
    {
      strands[1]->pixels[i] = pixelFromRGB(COEF_PREV, COEF_PREV / 1.5, 0);
    } //for i
  }
    else if (percentage > 42)
  {
    //3ledorange
    for (int i = NUM_LEDS_PER_STRIP_max + 2; i < NUM_LEDS_PER_STRIP_max + 6; i++)
    {
      if (i < NUM_LEDS_PER_STRIP_max + 5)
      {
        strands[1]->pixels[i] = pixelFromRGB(COEF_PREV, COEF_PREV / 1.5, 0);
      }
      else
      {
        strands[1]->pixels[i] = pixelFromRGB(0, 0, 0);
      }
    } //for i
  }
    else if (percentage > 38)
  {
    //2ledorange
    for (int i = NUM_LEDS_PER_STRIP_max + 2; i < NUM_LEDS_PER_STRIP_max + 6; i++)
    {
      if (i < NUM_LEDS_PER_STRIP_max + 4)
      {
        strands[1]->pixels[i] = pixelFromRGB(COEF_PREV, COEF_PREV / 1.5, 0);
      }
      else
      {
        strands[1]->pixels[i] = pixelFromRGB(0, 0, 0);
      }
    } //for i
  }
   else if (percentage > 33)
  {
    //1ledorange
    for (int i = NUM_LEDS_PER_STRIP_max + 2; i < NUM_LEDS_PER_STRIP_max + 6; i++)
    {
      if (i < NUM_LEDS_PER_STRIP_max + 3)
      {
        strands[1]->pixels[i] = pixelFromRGB(COEF_PREV, COEF_PREV / 1.5, 0);
      }
      else
      {
        strands[1]->pixels[i] = pixelFromRGB(0, 0, 0);
      }
    } //for i
  }

  /////////////////////    RED     ///////////////////////

  else if (percentage > 29)
  {
    //4ledrouge
    for (int i = NUM_LEDS_PER_STRIP_max + 2; i < NUM_LEDS_PER_STRIP_max + 6; i++)
    {
      strands[1]->pixels[i] = pixelFromRGB(127, 0, 0);
    } //for i
  }
   else if (percentage > 25)
  {
    //3ledrouge
    for (int i = NUM_LEDS_PER_STRIP_max + 2; i < NUM_LEDS_PER_STRIP_max + 6; i++)
    {
      if (i < NUM_LEDS_PER_STRIP_max + 5)
      {
        strands[1]->pixels[i] = pixelFromRGB(127, 0, 0);
      }
      else
      {
        strands[1]->pixels[i] = pixelFromRGB(0, 0, 0);
      }
    } //for i
  }
    else if (percentage > 20)
  {
    //2ledrouge
    for (int i = NUM_LEDS_PER_STRIP_max + 2; i < NUM_LEDS_PER_STRIP_max + 6; i++)
    {
      if (i < NUM_LEDS_PER_STRIP_max + 4)
      {
        strands[1]->pixels[i] = pixelFromRGB(127, 0, 0);
      }
      else
      {
        strands[1]->pixels[i] = pixelFromRGB(0, 0, 0);
      }
    } //for i
  }
    else if (percentage > 16)
  {
    //1ledrouge
    for (int i = NUM_LEDS_PER_STRIP_max + 2; i < NUM_LEDS_PER_STRIP_max + 6; i++)
    {
      if (i < NUM_LEDS_PER_STRIP_max + 3)
      {
        strands[1]->pixels[i] = pixelFromRGB(127, 0, 0);
      }
      else
      {
        strands[1]->pixels[i] = pixelFromRGB(0, 0, 0);
      }
    } //for i
  }


  /////////////////////  BLINK   ///////////////////////

  else if (percentage >= 1)
  {
    //4ledrouge clignote
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