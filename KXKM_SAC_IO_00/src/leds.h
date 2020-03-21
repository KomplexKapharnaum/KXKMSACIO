
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
  manu_frame(0);
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
  for (int i = 0; i < NUM_LEDS_PER_STRIP + 4; i++)
  {
    strands[0]->pixels[i] = pixelFromRGBW(test_led_niv, 0, 0, 0);
    strands[1]->pixels[i] = pixelFromRGBW(test_led_niv, 0, 0, 0);
  } //for i
  k32->pwm->set(0, test_led_niv);
  k32->pwm->set(1, 0);
  leds_show();
  delay(500);
  for (int i = 0; i < NUM_LEDS_PER_STRIP + 4; i++)
  {
    strands[0]->pixels[i] = pixelFromRGBW(0, test_led_niv, 0, 0);
    strands[1]->pixels[i] = pixelFromRGBW(0, test_led_niv, 0, 0);
  } //for i
  k32->pwm->set(0, 0);
  k32->pwm->set(1, test_led_niv);
  leds_show();
  delay(500);
  for (int i = 0; i < NUM_LEDS_PER_STRIP + 4; i++)
  {
    strands[0]->pixels[i] = pixelFromRGBW(0, 0, test_led_niv, 0);
    strands[1]->pixels[i] = pixelFromRGBW(0, 0, test_led_niv, 0);
  } //for i
  k32->pwm->setAll(0);
  leds_show();
  delay(500);
  for (int i = 0; i < NUM_LEDS_PER_STRIP + 4; i++)
  {
    strands[0]->pixels[i] = pixelFromRGBW(0, 0, 0, test_led_niv);
    strands[1]->pixels[i] = pixelFromRGBW(0, 0, 0, test_led_niv);
  } //for i
  k32->pwm->setAll(test_led_niv);
  leds_show();
  delay(500);
  for (int i = 0; i < NUM_LEDS_PER_STRIP + 4; i++)
  {
    strands[0]->pixels[i] = pixelFromRGBW(0, 0, 0, 0);
    strands[1]->pixels[i] = pixelFromRGBW(0, 0, 0, 0);
  } //for i
  k32->pwm->setAll(0);
  Black();
  leds_show();
} //initest

void gpioSetup(int gpioNum, int gpioMode, int gpioVal)
{
#if defined(ARDUINO) && ARDUINO >= 100
  pinMode(gpioNum, gpioMode);
  digitalWrite(gpioNum, gpioVal);
#elif defined(ESP_PLATFORM)
  gpio_num_t gpioNumNative = static_cast<gpio_num_t>(gpioNum);
  gpio_mode_t gpioModeNative = static_cast<gpio_mode_t>(gpioMode);
  gpio_pad_select_gpio(gpioNumNative);
  gpio_set_direction(gpioNumNative, gpioModeNative);
  gpio_set_level(gpioNumNative, gpioVal);
#endif
} // gpioSetup

void leds_init()
{
  int Ltype = k32->system->preferences.getUInt("LULU_ruban", LED_SK6812W_V1);
  for (int k = 0; k < NUM_STRIPS; k++)
  {
    STRANDS[k] = {.rmtChannel = k, .gpioNum = k32->system->ledpin(k), .ledType = Ltype, .brightLimit = 32, .numPixels = NUM_LEDS_PER_STRIP + 16, .pixels = nullptr, ._stateVars = nullptr};
    gpioSetup(k32->system->ledpin(k), OUTPUT, LOW);
  }
  int STRANDCNT = sizeof(STRANDS) / sizeof(STRANDS[0]);
  if (digitalLeds_initStrands(STRANDS, STRANDCNT))
  {
#ifdef DEBUG
    LOG("Init FAILURE: halting");
    delay(1000);
#endif
    ESP.restart();
  }
#ifdef DEBUG
  LOG("Init complete");
#endif
} //leds_init