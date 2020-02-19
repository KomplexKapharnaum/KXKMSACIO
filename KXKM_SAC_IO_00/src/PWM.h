int freq = 40000;
int resol = 8;

void ledSetup() {
  //// Setup LED for Testing
  ledcSetup(1, freq, resol);
  ledcSetup(2, freq, resol);
  ledcAttachPin(17, 1);
  ledcAttachPin(16, 2);
  pinMode(4, OUTPUT);
  digitalWrite(4, HIGH);
}


void channelOne() {
  ledcWrite(1, ledChannelOne);
}

void channelTwo() {
  ledcWrite(2, ledChannelTwo);
}

//// Setup PWM for LED(s)
void leds() {
  channelOne();
  channelTwo();
}