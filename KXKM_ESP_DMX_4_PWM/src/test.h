



void light_tests() {

  int timeStep = 300;
  
  // INIT TEST STRIPS
    light->anim( strip[0], "test0",   new K32_anim_test )->push(timeStep)->master(MASTER_PREV)->play();
    light->anim( strip[1], "test1",   new K32_anim_test )->push(timeStep)->master(MASTER_PREV)->play();

  // DMX TEST
    // light->anim( strip[0], "testDMX",   new Anim_dmx_test )->push(timeStep)->master(MASTER_PREV)->play();

  // PWM TEST
    light->pwm->set(0, 255);
    light->pwm->set(1, 0);
    light->pwm->set(2, 255);
    light->pwm->set(3, 0);    
    delay(timeStep);
    light->pwm->set(0, 0);
    light->pwm->set(1, 255);
    light->pwm->set(2, 0);
    light->pwm->set(3, 255); 
    delay(timeStep);
    light->pwm->set(0, 127);
    light->pwm->set(1, 127);
    light->pwm->set(2, 127);
    light->pwm->set(3, 127); 
    delay(timeStep);
    light->pwm->set(0, 0);
    light->pwm->set(1, 0);
    light->pwm->set(2, 0);
    light->pwm->set(3, 0); 

  // WAIT END
    light->anim("test0")->wait();
    light->anim("test1")->wait();
    // light->anim("testDMX")->wait();
  
  // COLOR TEST
    // light->anim(0, "colorA", new K32_anim_color, 10, 0)->push(50, 255, 200, 0, 0)->play(1000)->wait();

  // DMX TEST
    // K32_anim* artnet = light->anim("artnet");
    // artnet->push(MEM[8], LULU_PATCHSIZE)->push(100);
    // artnet->mod("saw",    new K32_mod_sinus)  ->at(0)->play();
    // artnet->mod("triangle", new K32_mod_triangle)   ->at(15)->period(10000)->play();
    // artnet->mod("fadeout",  new K32_mod_fadeout)    ->at(0)->period(1000)->play();
    
}