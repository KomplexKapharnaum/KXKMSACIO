
#define L_NAME "PotSon"

String potChannel = "pot0";   // pot + channel
int volume = 40;    // TODO: volume in CONF

void setup_device()
{
    // /////////////////////////////////////////////// AUDIO //////////////////////////////////////
    #if HW_ENABLE_AUDIO != 1
        #error "HW_ENABLE_AUDIO must be enabled to use audio"
    #endif

    potChannel = "pot"+String(k32->system->channel());

    // INTERNAL BTN
    k32->on("stm32/btn-click", [](Orderz* order) { 
        if (audio->isPlaying()) audio->stop();
        else {
            audio->loop(true);
            audio->play("/"+potChannel+".wav", volume); 
        }
    });

    // EXETERNAL BTN
    buttons->add(13, "inter");
    k32->on("btn/inter-on", [](Orderz *order) { 
        audio->play("/"+potChannel+"-on.wav", volume); 
    });
    k32->on("btn/inter-off", [](Orderz *order) { 
        audio->play("/"+potChannel+"-off.wav", volume); 
    });
}
