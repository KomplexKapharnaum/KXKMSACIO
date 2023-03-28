
#define L_NAME "PotSon"


void setup_device()
{



    // /////////////////////////////////////////////// AUDIO //////////////////////////////////////
    #if HW_ENABLE_AUDIO != 1
        #error "HW_ENABLE_AUDIO must be enabled to use audio"
    #endif
    
    // INTERNAL BTN
    k32->on("stm32/btn-click", [](Orderz* order)
    {
        audio->loop(false);
        audio->play("/1_muslim.mp3", 5);
    });

    // EXETERNAL BTN
    buttons->add(13, "inter");

    k32->on("btn/inter-on", [](Orderz *order) { 
        audio->loop(true);
        audio->play("/1_muslim.mp3", 5);
    });

    k32->on("btn/inter-off", [](Orderz *order) { 
        audio->stop();
    });
}
