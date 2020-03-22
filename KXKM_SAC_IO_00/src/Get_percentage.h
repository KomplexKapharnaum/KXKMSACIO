
bool etat_r = false;

void get_percentage()
{
  pixelColor_t pixel;
  int percentage = k32->system->stm32->battery();

  if (percentage > 50)        pixel = pixelFromRGB( 0, COEF_PREV, 0 );                  //3ledverte
  else if (percentage > 33)   pixel = pixelFromRGB( COEF_PREV, (COEF_PREV / 3), 0 );    //3ledorange
  else if (percentage > 16)   pixel = pixelFromRGB( 127, 0, 0 );                        //3ledrouge
  else                        pixel = pixelFromRGB( 255*(etat_r++) , 0, 0 );            //3ledrouge clignote

  for (int i = NUM_LEDS_PER_STRIP_max + 2; i < NUM_LEDS_PER_STRIP_max + 6; i++)
    strands[1]->pixels[i] = pixel;

}