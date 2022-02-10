
#define L_NAME "Maree"

#define LULU_STRIP_SIZE     300                                  // 5 pour tester avec les jauges de monitoring
#define LULU_STRIP_TYPE     LED_SK6812W_V1                       // Strip type

#define ARTNET_ENABLE       0

void setup_device()  
{
    //
    // FIXTURES 
    //

    // LED STRIPS fixtures
    K32_fixture* strips[LED_N_STRIPS] = {nullptr};
    for(int k=0; k<LED_N_STRIPS; k++)
        strips[k] = new K32_ledstrip(k, LEDS_PIN[k32->system->hw()][k], (led_types)LULU_STRIP_TYPE, LULU_STRIP_SIZE);    
    light->addFixtures( strips, LED_N_STRIPS );


    //
    // TEST Sequence
    //

        // INIT TEST STRIPS
            light->anim( "test-strip", new Anim_test_strip, LULU_STRIP_SIZE )
                ->drawTo(strips, LED_N_STRIPS)
                ->push(300)
                ->master(LULU_PREV_MASTER)
                ->play()->wait();

    // 
    // ANIM
    //

    // ANIM leds - artnet
    light->anim("maree", new Anim_maree, LULU_STRIP_SIZE)
        ->drawTo(strips, LED_N_STRIPS)
        ->remote(true)
        ->push(0)
        ->play();


}








