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
    
    remote->setState(REMOTE_AUTO);
    remote->lock();

    if (k32->system->hw() >= 3)
        pinMode(39, INPUT_PULLUP);
}

void boutons_loop()
{
    //////////////////     Click on ESP   ////////////////////
    if (stm32 && stm32->clicked()) remote->stmNext();

    //////////////////    Click on Atom    ////////////////////
    if (k32->system->hw() >= 3 )
    {
        int btn = digitalRead(39);
        if (didChange(W_ATOMBTN, btn) && btn == 0)
            remote->stmNext();
    }

    //////////////////////  REMOTE CONTROL   ///////////////////////////

    // ACTIVE Macro
    int activeMacro = remote->getActiveMacro();
    if (didChange(W_ACTIVEMACRO, activeMacro))
    {
        LOGF("REMOTE: -> set Active Macro = %d\n", activeMacro);

        #if LULU_TYPE == 12 // FIX
            light->anim("mem-dmxfix")->mem(activeMacro);
        #else
            light->anim("mem-strip")->mem(activeMacro);
            light->anim("mem-pwm")->mem(activeMacro);
        #endif
    }

    // PREVIEW Macro
    int previewMacro = remote->getPreviewMacro();
    if (didChange(W_PREVMACRO, previewMacro))
    {
        LOGF("REMOTE: -> set Preview Macro = %d\n", previewMacro);
        light->anim("memprev-strip")->mem(previewMacro);
    }

    // STATE Changed
    remoteState stateR = remote->getState();
    if (didChange(W_STATE, stateR))
    {
        // AUTO
        if (stateR == REMOTE_AUTO)
        {
            light->anim("mem-strip")->stop();
            light->anim("memprev-strip")->stop();
            light->anim("artnet-strip")->play();
            LOG("REMOTE: -> Mode AUTO");
        }

        // STM
        else if (stateR == REMOTE_MANU_STM)
        {
            light->anim("artnet-strip")->stop();
            light->anim("memprev-strip")->play();
            light->anim("mem-strip")->play();
            LOG("REMOTE: -> Mode STM");
        }

        // MANU
        else if (stateR == REMOTE_MANU || stateR == REMOTE_MANU_LAMP)
        {
            light->anim("memprev-strip")->play();
            LOG("REMOTE: -> Mode MANU");
        }
    }

    // GO Active Macro
    if (remote->getSendMacro())
        if (stateR == REMOTE_MANU || stateR == REMOTE_MANU_LAMP)
        {
            light->anim("artnet-strip")->stop();
            light->anim("mem-strip")->play();
            LOG("REMOTE: -> MANU -> GO Macro !");
        }

    // LAMP
    int lamp = remote->getLamp();
    if (didChange(W_LAMP, lamp))
    {
        if (lamp >= 0) {
            // light->pwm->set(0, lamp);
            // light->pwm->set(1, lamp);
        }
        else
        {
            light->anim("artnet-strip")->push();
            light->anim("mem-strip")->push();
        }
        LOGF("REMOTE: -> getLAMP @%d\n", lamp);
    }

} // void boutons();

#endif