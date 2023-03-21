



void light_tests() {

  int timeStep = 300;
  
  // INIT TEST
    k32->light->anim( 0, "test0",   new K32_anim_test )->push(timeStep)->master(MASTER_PREV)->play();
    k32->light->anim( 1, "test1",   new K32_anim_test )->push(timeStep)->master(MASTER_PREV)->play();

  // PWM TEST
    k32->pwm->set(0, 50);
    k32->pwm->set(1, 0);
    delay(timeStep);
    k32->pwm->set(0, 0);
    k32->pwm->set(1, 50);
    delay(timeStep);
    k32->pwm->set(0, 50);
    k32->pwm->set(1, 50);
    delay(timeStep);
    k32->pwm->set(0, 0);
    k32->pwm->set(1, 0);

  // WAIT END
    k32->light->anim("test0")->wait();
  
  // COLOR TEST
    // k32->light->anim(0, "colorA", new K32_anim_color, 10, 0)->push(50, 255, 200, 0, 0)->play(1000)->wait();

  // DMX TEST
    // K32_anim* artnet = k32->light->anim("artnet");
    // artnet->push(MEM[8], LULU_PATCHSIZE)->push(100);
    // artnet->mod("saw",    new K32_mod_sinus)  ->at(0)->play();
    // artnet->mod("triangle", new K32_mod_triangle)   ->at(15)->period(10000)->play();
    // artnet->mod("fadeout",  new K32_mod_fadeout)    ->at(0)->period(1000)->play();
    
}