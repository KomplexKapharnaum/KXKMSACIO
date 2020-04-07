
#define More_Pixel 20
int test_led_niv = 50;

void leds_show()
{
  digitalLeds_updatePixels(strands[0]);
  digitalLeds_updatePixels(strands[1]);
} //leds_show

void ledBlack()
{
#ifdef DEBUG
  LOG("ledBlack()");
#endif
  active_frame(NUMBER_OF_MEM - 1);
} //ledBlack

void initTest()
{
#ifdef DEBUG
  LOG("initTest()");
#endif
  Black();
  k32->pwm->setAll(0);
  leds_show();
  delay(500);
  for (int i = 0; i < NUM_LEDS_PER_STRIP + More_Pixel; i++)
  {
    strands[0]->pixels[i] = pixelFromRGBW(test_led_niv, 0, 0, 0);
    strands[1]->pixels[i] = pixelFromRGBW(test_led_niv, 0, 0, 0);
  } //for i
  k32->pwm->set(0, test_led_niv);
  k32->pwm->set(1, 0);
  leds_show();
  delay(500);
  for (int i = 0; i < NUM_LEDS_PER_STRIP + More_Pixel; i++)
  {
    strands[0]->pixels[i] = pixelFromRGBW(0, test_led_niv, 0, 0);
    strands[1]->pixels[i] = pixelFromRGBW(0, test_led_niv, 0, 0);
  } //for i
  k32->pwm->set(0, 0);
  k32->pwm->set(1, test_led_niv);
  leds_show();
  delay(500);
  for (int i = 0; i < NUM_LEDS_PER_STRIP + More_Pixel; i++)
  {
    strands[0]->pixels[i] = pixelFromRGBW(0, 0, test_led_niv, 0);
    strands[1]->pixels[i] = pixelFromRGBW(0, 0, test_led_niv, 0);
  } //for i
  k32->pwm->setAll(0);
  leds_show();
  delay(500);
  for (int i = 0; i < NUM_LEDS_PER_STRIP + More_Pixel; i++)
  {
    strands[0]->pixels[i] = pixelFromRGBW(0, 0, 0, test_led_niv);
    strands[1]->pixels[i] = pixelFromRGBW(0, 0, 0, test_led_niv);
  } //for i
  k32->pwm->setAll(test_led_niv);
  leds_show();
  delay(500);
  for (int i = 0; i < NUM_LEDS_PER_STRIP + More_Pixel; i++)
  {
    strands[0]->pixels[i] = pixelFromRGBW(0, 0, 0, 0);
    strands[1]->pixels[i] = pixelFromRGBW(0, 0, 0, 0);
  } //for i
  k32->pwm->setAll(0);
  Black();
  leds_show();
} //initest

void leds_init()
{
  int Ltype = k32->system->preferences.getUInt("LULU_ruban", LED_SK6812W_V1);
  digitalLeds_init();
  for (int k = 0; k < NUM_STRIPS; k++)
  {
    STRANDS[k] = {.rmtChannel = k, .gpioNum = k32->system->ledpin(k), .ledType = Ltype, .brightLimit = 32, .numPixels = NUM_LEDS_PER_STRIP + More_Pixel, .pixels = nullptr, ._stateVars = nullptr};
    strands[k] = digitalLeds_addStrand(STRANDS[k]);
  }

#ifdef DEBUG
  LOG("Init complete");
#endif
} //leds_init