void bat_custom_on()
{
  int Ulow = 21700; // rouge clignote
  int U1 = 23100;   // rouge low
  int U2 = 23500;   // orange
  int U3 = 24500;
  int U4 = 26500;
  int U5 = 28000;
  int Umax = 29400; //vert
  
  k32->system->stm32->custom(Ulow, U1, U2, U3, U4, U5, Umax); // set CUSTOM profile

} // void bat_custom_on()


void bat_custom_off()
{
  int Ulow = 21700; // rouge clignote
  int U1 = 23100;   // rouge low
  int U2 = 23500;   // orange
  int U3 = 24500;
  int U4 = 26500;
  int U5 = 28000;
  int Umax = 29400; //vert

  k32->system->stm32->custom(Ulow, U1, U2, U3, U4, U5, Umax); // set CUSTOM profile

} // void bat_custom_off()