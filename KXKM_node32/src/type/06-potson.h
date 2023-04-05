
#define L_NAME "PotSon"

String potChannel = "pot0";   // pot + channel
int velocity[6] = {100, 50, 50, 50, 70, 55};    // TODO: velocity in CONF
int volume = 33;   // TODO: volume in CONF
int velo = 100;

void setup_device()
{
    // /////////////////////////////////////////////// AUDIO //////////////////////////////////////
    #if HW_ENABLE_AUDIO != 1
        #error "HW_ENABLE_AUDIO must be enabled to use audio"
    #endif

    potChannel = "pot"+String(k32->system->channel());

    if (k32->system->channel() < 6) velo = velocity[k32->system->channel()];
    audio->volume(volume);

    // INTERNAL BTN
    k32->on("stm32/btn-click", [](Orderz* order) { 
        if (audio->isPlaying()) audio->stop();
        else {
            audio->loop(true);
            audio->play("/"+potChannel+".wav", velo); 
        }
    });

    // EXETERNAL BTN
    buttons->add(13, "inter");
    k32->on("btn/inter-on", [](Orderz *order) { 
        audio->loop(false);
        audio->play("/"+potChannel+"-on.wav", velo); 
    });
    k32->on("btn/inter-off", [](Orderz *order) { 
        audio->loop(false);
        audio->play("/"+potChannel+"-off.wav", velo); 
    });
}
