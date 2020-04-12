



void light_tests() {

    // INIT TEST
    k32->light->anim( 0, "test0",   new K32_anim_test )->push(300)->master(MASTER_PREV)->play();
    k32->light->anim( 1, "test1",   new K32_anim_test )->push(300)->master(MASTER_PREV)->play()->wait();

  // COLOR TEST
    // k32->light->anim("colorA", new K32_anim_color, 0, 10, 5 )->push(50, 255, 200, 0, 0)->play(1000);

  // DMX TEST
    // K32_anim* artnet = k32->light->anim("artnet");
    // artnet->push(MEM[8], LULU_PATCHSIZE)->push(100);
    // artnet->mod("saw",    new K32_mod_sinus)  ->at(0)->play();
    // artnet->mod("triangle", new K32_mod_triangle)   ->at(15)->period(10000)->play();
    // artnet->mod("fadeout",  new K32_mod_fadeout)    ->at(0)->period(1000)->play();
    
}