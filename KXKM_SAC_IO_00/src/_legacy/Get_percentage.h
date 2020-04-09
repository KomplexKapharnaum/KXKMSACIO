
#define Jauge_Start 1
bool etat_r = false;
int lrc = 0;

void get_percentage()                                               // !!! IMPLEMENT
{
  int percentage = k32->system->stm32->battery();

  /////////////////////  GREEN   ///////////////////////

  if (percentage > 86)
  {
    //4ledverte
    for (int i = NUM_LEDS_PER_STRIP_max + Jauge_Start; i < NUM_LEDS_PER_STRIP_max + Jauge_Start + 4; i++)
    {
      strands[1]->pixels[i] = pixelFromRGB(0, COEF_PREV, 0);
    } //for i
  }
  else if (percentage > 74)
  {
    //3ledverte
    for (int i = NUM_LEDS_PER_STRIP_max + Jauge_Start; i < NUM_LEDS_PER_STRIP_max + Jauge_Start + 4; i++)
    {
      if (i < NUM_LEDS_PER_STRIP_max + Jauge_Start + 3)
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
    for (int i = NUM_LEDS_PER_STRIP_max + Jauge_Start; i < NUM_LEDS_PER_STRIP_max + Jauge_Start + 4; i++)
    {
      if (i < NUM_LEDS_PER_STRIP_max + Jauge_Start + 2)
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
    for (int i = NUM_LEDS_PER_STRIP_max + Jauge_Start; i < NUM_LEDS_PER_STRIP_max + Jauge_Start + 4; i++)
    {
      if (i < NUM_LEDS_PER_STRIP_max + Jauge_Start + 1)
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
    for (int i = NUM_LEDS_PER_STRIP_max + Jauge_Start; i < NUM_LEDS_PER_STRIP_max + Jauge_Start + 4; i++)
    {
      strands[1]->pixels[i] = pixelFromRGB(COEF_PREV, COEF_PREV / 1.5, 0);
    } //for i
  }
  else if (percentage > 42)
  {
    //3ledorange
    for (int i = NUM_LEDS_PER_STRIP_max + Jauge_Start; i < NUM_LEDS_PER_STRIP_max + Jauge_Start + 4; i++)
    {
      if (i < NUM_LEDS_PER_STRIP_max + Jauge_Start + 3)
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
    for (int i = NUM_LEDS_PER_STRIP_max + Jauge_Start; i < NUM_LEDS_PER_STRIP_max + Jauge_Start + 4; i++)
    {
      if (i < NUM_LEDS_PER_STRIP_max + Jauge_Start + 2)
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
    for (int i = NUM_LEDS_PER_STRIP_max + Jauge_Start; i < NUM_LEDS_PER_STRIP_max + Jauge_Start + 4; i++)
    {
      if (i < NUM_LEDS_PER_STRIP_max + Jauge_Start + 1)
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
    for (int i = NUM_LEDS_PER_STRIP_max + Jauge_Start; i < NUM_LEDS_PER_STRIP_max + Jauge_Start + 4; i++)
    {
      strands[1]->pixels[i] = pixelFromRGB(127, 0, 0);
    } //for i
  }
  else if (percentage > 25)
  {
    //3ledrouge
    for (int i = NUM_LEDS_PER_STRIP_max + Jauge_Start; i < NUM_LEDS_PER_STRIP_max + Jauge_Start + 4; i++)
    {
      if (i < NUM_LEDS_PER_STRIP_max + Jauge_Start + 3)
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
    for (int i = NUM_LEDS_PER_STRIP_max + Jauge_Start; i < NUM_LEDS_PER_STRIP_max + Jauge_Start + 4; i++)
    {
      if (i < NUM_LEDS_PER_STRIP_max + Jauge_Start + 2)
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
    for (int i = NUM_LEDS_PER_STRIP_max + Jauge_Start; i < NUM_LEDS_PER_STRIP_max + Jauge_Start + 4; i++)
    {
      if (i < NUM_LEDS_PER_STRIP_max + Jauge_Start + 1)
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

  else if (percentage > 14)
  {
    //4ledrouge clignote
    if (etat_r != 1)
    {
      for (int i = NUM_LEDS_PER_STRIP_max + Jauge_Start; i < NUM_LEDS_PER_STRIP_max + Jauge_Start + 4; i++)
      {
        strands[1]->pixels[i] = pixelFromRGB(255, 0, 0);
      }
      etat_r = 1;
    }
    else if (etat_r != 0)
    {
      for (int i = NUM_LEDS_PER_STRIP_max + Jauge_Start; i < NUM_LEDS_PER_STRIP_max + Jauge_Start + 4; i++)
      {
        strands[1]->pixels[i] = pixelFromRGB(0, 0, 0);
      }
      etat_r = 0;
    }
  }
  else if (percentage > 13)
  {
    //3ledrouge clignote
    if (etat_r != 1)
    {
      for (int i = NUM_LEDS_PER_STRIP_max + Jauge_Start; i < NUM_LEDS_PER_STRIP_max + Jauge_Start + 3; i++)
      {
        strands[1]->pixels[i] = pixelFromRGB(255, 0, 0);
      }
      etat_r = 1;
    }
    else if (etat_r != 0)
    {
      for (int i = NUM_LEDS_PER_STRIP_max + Jauge_Start; i < NUM_LEDS_PER_STRIP_max + Jauge_Start + 4; i++)
      {
        strands[1]->pixels[i] = pixelFromRGB(0, 0, 0);
      }
      etat_r = 0;
    }
  }
  else if (percentage > 12)
  {
    //2ledrouge clignote
    if (etat_r != 1)
    {
      for (int i = NUM_LEDS_PER_STRIP_max + Jauge_Start; i < NUM_LEDS_PER_STRIP_max + Jauge_Start + 2; i++)
      {
        strands[1]->pixels[i] = pixelFromRGB(255, 0, 0);
      }
      etat_r = 1;
    }
    else if (etat_r != 0)
    {
      for (int i = NUM_LEDS_PER_STRIP_max + Jauge_Start; i < NUM_LEDS_PER_STRIP_max + Jauge_Start + 4; i++)
      {
        strands[1]->pixels[i] = pixelFromRGB(0, 0, 0);
      }
      etat_r = 0;
    }
  }
  else if (percentage > 11)
  {
    //1ledrouge clignote
    if (etat_r != 1)
    {
      for (int i = NUM_LEDS_PER_STRIP_max + Jauge_Start; i < NUM_LEDS_PER_STRIP_max + Jauge_Start + 1; i++)
      {
        strands[1]->pixels[i] = pixelFromRGB(255, 0, 0);
      }
      etat_r = 1;
    }
    else if (etat_r != 0)
    {
      for (int i = NUM_LEDS_PER_STRIP_max + Jauge_Start; i < NUM_LEDS_PER_STRIP_max + Jauge_Start + 4; i++)
      {
        strands[1]->pixels[i] = pixelFromRGB(0, 0, 0);
      }
      etat_r = 0;
    }
  }
  else if (percentage >= 1)
  {
    //---> ledrouge clignote
    if (etat_r != 1)
    {
      lrc++;
      if (lrc > 3)
        lrc = 0;

      for (int i = NUM_LEDS_PER_STRIP_max + Jauge_Start + lrc; i < NUM_LEDS_PER_STRIP_max + Jauge_Start + 1 + lrc; i++)
      {
        strands[1]->pixels[i] = pixelFromRGB(255, 0, 0);
      }
      etat_r = 1;
    }
    else if (etat_r != 0)
    {
      for (int i = NUM_LEDS_PER_STRIP_max + Jauge_Start; i < NUM_LEDS_PER_STRIP_max + Jauge_Start + 4; i++)
      {
        strands[1]->pixels[i] = pixelFromRGB(0, 0, 0);
      }
      etat_r = 0;
    }
  }
}
