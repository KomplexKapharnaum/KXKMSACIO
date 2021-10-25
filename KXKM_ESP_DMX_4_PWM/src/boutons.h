/////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////  BOUTONS   ///////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

#ifndef boutons_h
#define boutons_h

#define WATCH_SLOTS 8

enum watchSlot
{
    W_STATE,
    W_PREVMACRO,
    W_ACTIVEMACRO,
    W_LAMP,
    W_ATOMBTN
};

static int watchValues[WATCH_SLOTS];

bool didChange(watchSlot k, int value)
{
    if (k < WATCH_SLOTS && watchValues[k] != value)
    {
        watchValues[k] = value;
        return true;
    }
    return false;
}

void boutons_init()
{
    for (int i = 0; i < WATCH_SLOTS; i++)
        watchValues[i] = -128;

    if (k32->system->hw() >= 3)
        pinMode(39, INPUT_PULLUP);
}

void boutons_loop()
{
    //////////////////    Click on Atom    ////////////////////
    if (k32->system->hw() >= 3 )
    {
        int btn = digitalRead(39);
        if (didChange(W_ATOMBTN, btn) && btn == 0)
            k32->emit("atom/btn-click");
    }

    //////////////////////  REMOTE CONTROL   ///////////////////////////


    // // GO Active Macro
    // if (remote->getSendMacro())
    //     if (stateR == REMOTE_MANU || stateR == REMOTE_MANU_LAMP)
    //     {
    //         #if ARTNET_ENABLE  // FIX
    //             light->anim("artnet-strip")->stop();
    //             light->anim("mem-strip")->play();
    //             LOG("REMOTE: -> MANU -> GO Macro !");
    //         #endif
    //     }

    // LAMP /// FIX
    // int lamp = remote->getLamp();
    // if (didChange(W_LAMP, lamp))
    // {
    //     if (lamp >= 0) {
    //         // light->pwm->set(0, lamp);
    //         // light->pwm->set(1, lamp);
    //     }
    //     else
    //     {
    //         light->anim("artnet-strip")->push();    // FIX
    //         light->anim("mem-strip")->push();       // FIX
    //     }
    //     LOGF("REMOTE: -> getLAMP @%d\n", lamp);
    // }

} // void boutons();

#endif